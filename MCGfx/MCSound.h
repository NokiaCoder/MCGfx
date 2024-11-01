#pragma once
#include <windows.h>
#include <dsound.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <stdexcept>
#include <fstream>
#include <iostream>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")

class AudioPlayer 
{
public:
    AudioPlayer() 
    {
		isInitialized = false;
    }

    HRESULT Initialize(HWND hwnd)
    {
        // Initialize DirectSound
        HRESULT hr = DirectSoundCreate8(NULL, &pDirectSound, NULL);
        if (FAILED(hr)) 
        {
            throw std::runtime_error("Failed to initialize DirectSound.");
        }

        // Set cooperative level
        hr = pDirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
        if (FAILED(hr)) 
        {
            pDirectSound->Release();
            throw std::runtime_error("Failed to set cooperative level.");
        }

        // Create the primary buffer
        DSBUFFERDESC bufferDesc = {};
        bufferDesc.dwSize = sizeof(DSBUFFERDESC);
        bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
        hr = pDirectSound->CreateSoundBuffer(&bufferDesc, &pPrimaryBuffer, NULL);
        if (FAILED(hr)) 
        {
            pDirectSound->Release();
            throw std::runtime_error("Failed to create primary sound buffer.");
        }

		isInitialized = true;
        return hr;
    }

    bool IsActive()
	{
        return isInitialized;
	}
    // Loads a .wav file and creates a secondary buffer
    int Preload(const std::string& filename) 
    {
        std::lock_guard<std::mutex> lock(mutex_);
        WAVEFORMATEX waveFormat;
        std::vector<char> waveData;

        if (!ReadWavFile(filename, waveFormat, waveData)) 
        {
            std::cerr << "Failed to read .wav file.\n";
            return -1;
        }

        // Create the secondary buffer
        DSBUFFERDESC bufferDesc = {};
        bufferDesc.dwSize = sizeof(DSBUFFERDESC);
        bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
        bufferDesc.dwBufferBytes = static_cast<uint32_t>(waveData.size());
        bufferDesc.lpwfxFormat = &waveFormat;

        IDirectSoundBuffer* pSecondaryBuffer;
        HRESULT hr = pDirectSound->CreateSoundBuffer(&bufferDesc, &pSecondaryBuffer, NULL);
        if (FAILED(hr)) 
        {
            std::cerr << "Failed to create secondary buffer.\n";
            return -1;
        }

        // Copy data to the buffer
        void* bufferPtr;
        DWORD bufferSize;
        hr = pSecondaryBuffer->Lock(0, static_cast<uint32_t>(waveData.size()), &bufferPtr, &bufferSize, NULL, NULL, 0);
        if (SUCCEEDED(hr)) 
        {
            memcpy(bufferPtr, waveData.data(), bufferSize);
            pSecondaryBuffer->Unlock(bufferPtr, bufferSize, NULL, 0);
        }
        else 
        {
            std::cerr << "Failed to lock buffer.\n";
            pSecondaryBuffer->Release();
            return -1;
        }

        // Store the buffer with a unique ID
        int soundId = ++currentId_;
        soundBuffers_[soundId] = pSecondaryBuffer;
        return soundId;
    }

    // Plays the loaded .wav file
    void Play(int id, bool loop = false) 
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (soundBuffers_.find(id) == soundBuffers_.end()) 
        {
            std::cerr << "Sound ID " << id << " not found.\n";
            return;
        }

        IDirectSoundBuffer* pSecondaryBuffer = soundBuffers_[id];
        pSecondaryBuffer->SetCurrentPosition(0);
        pSecondaryBuffer->Play(0, 0, loop ? DSBPLAY_LOOPING : 0);
    }

    // Stops a specific sound by its ID
    void Stop(int id) 
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (soundBuffers_.find(id) != soundBuffers_.end()) 
        {
            soundBuffers_[id]->Stop();
        }
    }

    ~AudioPlayer() 
    {
        // Release all secondary buffers
        for (auto it = soundBuffers_.begin(); it != soundBuffers_.end(); ++it) 
        {
            if (it->second) 
            {
                it->second->Release();
            }
        }
        if (pPrimaryBuffer) 
        {
            pPrimaryBuffer->Release();
        }
        if (pDirectSound) 
        {
            pDirectSound->Release();
        }
    }

private:
    bool isInitialized = false;
    IDirectSound8* pDirectSound;
    IDirectSoundBuffer* pPrimaryBuffer;
    std::unordered_map<int, IDirectSoundBuffer*> soundBuffers_;
    std::mutex mutex_;
    int currentId_ = 0;

    // Reads a .wav file and returns its format and data
    bool ReadWavFile(const std::string& filename, WAVEFORMATEX& waveFormat, std::vector<char>& waveData) 
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file) return false;

        // Read RIFF header
        file.seekg(0, std::ios::end);
        size_t fileSize = file.tellg();
        file.seekg(0, std::ios::beg);
        waveData.resize(fileSize);
        file.read(waveData.data(), fileSize);

        // Check RIFF header
        if (memcmp(waveData.data(), "RIFF", 4) != 0 || memcmp(waveData.data() + 8, "WAVE", 4) != 0) 
        {
            return false;
        }

        // Find the "fmt " chunk and read the WAVEFORMATEX structure
        size_t offset = 12;
        while (offset < fileSize) 
        {
            char* chunkId = waveData.data() + offset;
            DWORD chunkSize = *reinterpret_cast<DWORD*>(waveData.data() + offset + 4);
            if (memcmp(chunkId, "fmt ", 4) == 0) 
            {
                memcpy(&waveFormat, waveData.data() + offset + 8, sizeof(WAVEFORMATEX));
            }
            else if (memcmp(chunkId, "data", 4) == 0) 
            {
                // Found data chunk
                waveData.erase(waveData.begin(), waveData.begin() + offset + 8);
                waveData.resize(chunkSize);
                break;
            }
            offset += chunkSize + 8;
        }

        return true;
    }
};

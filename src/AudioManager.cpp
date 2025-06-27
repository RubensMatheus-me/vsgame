#include "AudioManager.h"
#include <iostream>
#include <algorithm> // para std::clamp

AudioManager &AudioManager::getInstance()
{
    static AudioManager instance;
    return instance;
}

bool AudioManager::init()
{
    // frequencia, formato (automatico para o 16 bit),  canal (1 = mono, 2 = estereo), tamanho buffer
    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4000) < 0)
    {
        std::cerr << "SDL_mixer error: " << Mix_GetError() << "\n";
        return false;
    }

    Mix_AllocateChannels(16);

    setMusicVolume(0.2f);
    setEffectsVolume(0.2f);

    return true;
}

void AudioManager::clean()
{
    for (auto &pair : soundEffects)
    {
        Mix_FreeChunk(pair.second);
    }
    soundEffects.clear();

    if (currentMusic)
    {
        Mix_FreeMusic(currentMusic);
        currentMusic = nullptr;
    }

    Mix_CloseAudio();
}

void AudioManager::playMusic(const std::string &filePath, int loops)
{
    if (currentMusic)
    {
        Mix_FreeMusic(currentMusic);
        currentMusic = nullptr;
    }

    currentMusic = Mix_LoadMUS(filePath.c_str());
    if (!currentMusic)
    {
        std::cerr << "Erro ao carregar música: " << Mix_GetError() << "\n";
        return;
    }

    Mix_PlayMusic(currentMusic, loops);
}

void AudioManager::stopMusic()
{
    Mix_HaltMusic();
}

void AudioManager::loadSound(const std::string &id, const std::string &filePath)
{
    Mix_Chunk *chunk = Mix_LoadWAV(filePath.c_str());
    if (!chunk)
    {
        std::cerr << "Erro ao carregar som: " << Mix_GetError() << "\n";
        return;
    }
    soundEffects[id] = chunk;
}

void AudioManager::playSound(const std::string &id, int loops)
{
    if (soundEffects.count(id) > 0)
    {
        Mix_PlayChannel(-1, soundEffects[id], loops);
    }
}

void AudioManager::setMusicVolume(float percent)
{
    percent = std::clamp(percent, 0.0f, 1.0f);
    Mix_VolumeMusic(static_cast<int>(percent * MIX_MAX_VOLUME));
}

void AudioManager::setEffectsVolume(float percent)
{
    percent = std::clamp(percent, 0.0f, 1.0f);
    Mix_Volume(-1, static_cast<int>(percent * MIX_MAX_VOLUME));
}

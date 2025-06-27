#include "AudioManager.h"
#include <iostream>
#include <algorithm>

AudioManager &AudioManager::getInstance()
{
    static AudioManager instance;
    return instance;
}

bool AudioManager::init(int frequency, Uint16 format, int channels, int chunkSize, int numChannels)
{
    if (Mix_OpenAudio(frequency, format, channels, chunkSize) < 0)
    {
        std::cerr << "SDL_mixer error: " << Mix_GetError() << "\n";
        return false;
    }
    Mix_AllocateChannels(numChannels);
    setMusicVolume(0.1f);
    setEffectsVolume(1.0f);
    return true;
}

void AudioManager::clean()
{
    for (auto &[id, chunk] : soundEffects)
        Mix_FreeChunk(chunk);
    soundEffects.clear();

    for (auto &[id, music] : musics)
        Mix_FreeMusic(music);
    musics.clear();

    Mix_CloseAudio();
}

bool AudioManager::loadSound(const std::string &id, const std::string &filePath)
{
    Mix_Chunk *chunk = Mix_LoadWAV(filePath.c_str());
    if (!chunk)
    {
        std::cerr << "Erro ao carregar efeito sonoro: " << Mix_GetError() << "\n";
        return false;
    }
    soundEffects[id] = chunk;
    return true;
}

bool AudioManager::loadMusic(const std::string &id, const std::string &filePath)
{
    Mix_Music *music = Mix_LoadMUS(filePath.c_str());
    if (!music)
    {
        std::cerr << "Erro ao carregar musica: " << Mix_GetError() << "\n";
        return false;
    }
    musics[id] = music;
    return true;
}

void AudioManager::playSound(const std::string &id, int loops)
{
    auto it = soundEffects.find(id);
    if (it != soundEffects.end())
        Mix_PlayChannel(-1, it->second, loops);
}

void AudioManager::playMusic(const std::string &id, int loops)
{
    auto it = musics.find(id);
    if (it != musics.end())
        Mix_PlayMusic(it->second, loops);
}

void AudioManager::stopMusic()
{
    Mix_HaltMusic();
}

void AudioManager::stopAllSounds()
{
    Mix_HaltChannel(-1);
}

void AudioManager::setMusicVolume(float percent)
{
    musicVolume = std::clamp(percent, 0.0f, 1.0f);
    Mix_VolumeMusic(static_cast<int>(musicVolume * MIX_MAX_VOLUME));
}

void AudioManager::setEffectsVolume(float percent)
{
    effectsVolume = std::clamp(percent, 0.0f, 1.0f);
    Mix_Volume(-1, static_cast<int>(effectsVolume * MIX_MAX_VOLUME));
}

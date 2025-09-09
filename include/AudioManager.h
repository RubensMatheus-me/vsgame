#pragma once
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <string_view>

class AudioManager
{
public:
    static AudioManager &getInstance();
    // frequenia valores (22050, 44100, 48000) buffer size(512 ,1024, 2048, 4096, 8192, 16384)
    bool init(int frequency = 44100, Uint16 format = MIX_DEFAULT_FORMAT, int channels = 2, int chunkSize = 4096, int numChannels = 32);
    void clean();

    bool loadSound(const std::string &id, const std::string &filePath);
    bool loadMusic(const std::string &id, const std::string &filePath);

    void playSound(const std::string &id, int loops = 0);
    void playMusic(const std::string &id, int loops = -1);
    void stopMusic();
    void stopAllSounds();

    void setMusicVolume(float percent);
    void setEffectsVolume(float percent);

private:
    AudioManager() = default;
    ~AudioManager() = default;

    AudioManager(const AudioManager &) = delete;
    AudioManager &operator=(const AudioManager &) = delete;

    std::unordered_map<std::string, Mix_Chunk *> soundEffects;
    std::unordered_map<std::string, Mix_Music *> musics;

    float musicVolume = 1.0f;
    float effectsVolume = 1.0f;
};

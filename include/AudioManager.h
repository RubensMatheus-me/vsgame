#pragma once
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>

class AudioManager
{
public:
    static AudioManager &getInstance();

    bool init();
    void clean();

    void playMusic(const std::string &filePath, int loops = -1);
    void stopMusic();

    void loadSound(const std::string &id, const std::string &filePath);
    void playSound(const std::string &id, int loops = 0);

    void setMusicVolume(float percent);
    void setEffectsVolume(float percent);

private:
    AudioManager() = default;
    ~AudioManager() = default;

    Mix_Music *currentMusic = nullptr;
    std::unordered_map<std::string, Mix_Chunk *> soundEffects;
};

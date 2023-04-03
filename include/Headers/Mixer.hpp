#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>

class Audio
{
private:
    int volume;
    std::vector<Mix_Music*> musics;
    std::vector<Mix_Chunk*> sounds;
public:
    Audio(int p_volume, std::vector<const char*>& p_sounds, std::vector<const char*>& p_musics);
    Audio(); ~Audio();
    int loadMusic(const char* p_file);
    int loadSound(const char* p_file);
    void playMusic(int p_music, int p_loopAmount);
    void playSound(int p_sound, int p_loopAmount, int p_channel);
    void stopMusic();
    void setVolume(int p_volume);
    int getVolume();
    void pause();
};

enum SongIds {
    SOUND_Collision, SOUND_Point, SOUND_Click
};

enum MusicIds {
    MUSIC_Victory, MUSIC_Admin
};
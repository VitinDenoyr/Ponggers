#include <Mixer.hpp>

Audio::Audio(int p_volume, std::vector<const char*>& p_sounds, std::vector<const char*>& p_musics)
: volume(p_volume)
{
    for(const char* s : p_sounds){
        loadSound(s);
    }
    for(const char* m : p_musics){
        loadMusic(m);
    }
}

Audio::Audio() : volume(100) {}

Audio::~Audio(){
    for(Mix_Music* m : musics){
        Mix_FreeMusic(m);
    }
    for(Mix_Chunk* c : sounds){
        Mix_FreeChunk(c);
    }
}

int Audio::loadMusic(const char* p_file){
    Mix_Music* music = NULL;
    music = Mix_LoadMUS(p_file);
    if(music == NULL){
        std::cout << "Falha no carregamento da música. Erro: " << SDL_GetError() << std::endl;
        return -1;
    }
    musics.push_back(music);
    return musics.size()-1;
}

int Audio::loadSound(const char* p_file){
    Mix_Chunk* sound = NULL;
    sound = Mix_LoadWAV(p_file);
    if(sound == NULL){
        std::cout << "Falha no carregamento do som. Erro: " << SDL_GetError() << std::endl;
        return -1;
    }
    sounds.push_back(sound);
    return sounds.size()-1;
}

void Audio::playMusic(int p_music, int p_loopAmount){
    Mix_VolumeMusic(volume);
    Mix_PlayMusic(musics[p_music],p_loopAmount);
}

void Audio::playSound(int p_sound, int p_loopAmount, int p_channel){
    Mix_Volume(-1,volume);
    Mix_PlayChannel(p_channel,sounds[p_sound],p_loopAmount);
}

void Audio::stopMusic(){
    if(Mix_PlayingMusic){
        Mix_HaltMusic();
    }
}

void Audio::setVolume(int p_percent){
    volume = (MIX_MAX_VOLUME*p_percent)/100;
}

int Audio::getVolume(){
    return volume;
}

void Audio::pause(){
    if(Mix_PausedMusic()){
        Mix_ResumeMusic();
    } else {
        Mix_PauseMusic();
    }
}
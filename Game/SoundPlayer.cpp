#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include "SoundPlayer.h"

#pragma comment(lib, "winmm.lib")

void SoundPlayer::Initialize()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void SoundPlayer::Cleanup()
{
    Mix_Quit();
    SDL_Quit();
}

void SoundPlayer::Play(const char *filePath, bool loop, bool async)
{
    Mix_Chunk *sound = Mix_LoadWAV(filePath);
    if (sound == nullptr)
    {
        std::cerr << "Failed to load sound: " << Mix_GetError() << std::endl;
        return;
    }

    int loops = loop ? -1 : 0; // -1 means loop indefinitely
    if (async)
    {
        // Play sound in a new thread
        std::thread([sound, loops]()
                    {
                        Mix_PlayChannel(-1, sound, loops);
                        SDL_Delay(500); // Give a moment for async sound to start
                    })
            .detach();
    }
    else
    {
        // Play sound on the main thread
        Mix_PlayChannel(-1, sound, loops);
    }
}
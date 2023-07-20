//
// Created by hartl on 25/06/2023.
//

#include <cstdint>
#include <cstdio>
#include <SDL.h>

#ifndef I8080EMULATOR_DISPLAY_H
#define I8080EMULATOR_DISPLAY_H

class Display {
public:
    Display(const char* Title, uint16_t _width, uint16_t _height);
    void Update(uint8_t* VRAM);
private:
    int height;
    int width;
    void* pixels[256 * 224 * 32]{};
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;

    void UpdatePixel(int x, int y, Uint32 color);
};

#endif //I8080EMULATOR_DISPLAY_H

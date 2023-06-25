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
    Display(const char* Title, uint16_t _width, uint16_t _height, uint16_t _pixelSize);
    void Update(uint8_t* VRAM);
private:
    uint16_t pixelSize;
    uint16_t height;
    uint16_t width;
    uint16_t pixels[224 * 256]{};
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};

#endif //I8080EMULATOR_DISPLAY_H

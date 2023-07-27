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
    Display(const char* Title, int _width, int _height, int _pixelSize);
    ~Display();
    void updateScreen(uint8_t* VRAM);
private:
    int screenHeight;
    int screenWidth;
    int pixelSize;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* screenTexture;
    uint32_t mapPixelValueToColor(uint8_t pixelValue);
};

#endif //I8080EMULATOR_DISPLAY_H

//
// Created by hartl on 25/06/2023.
//

#include "Display.h"

const uint16_t colors[2] = {0xf000, 0xffff};

Display::Display(const char* Title, uint16_t _width, uint16_t _height, uint16_t _pixelSize) {
    width = _width;
    height = _height;
    pixelSize = _pixelSize;

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              width * pixelSize, height * pixelSize, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_SetWindowMinimumSize(window, width * pixelSize, height * pixelSize);
    SDL_RenderSetLogicalSize(renderer, width * pixelSize, height * pixelSize);
    SDL_RenderSetIntegerScale(renderer, static_cast<SDL_bool>(1));

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR4444,
                                SDL_TEXTUREACCESS_STREAMING, height * pixelSize, width * pixelSize);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
}

void Display::Update(uint8_t *VRAM) {
    uint16_t ColorToDraw;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y += 8) {
            uint8_t VRAMByte = VRAM[x * (height >> 3) + (y >> 3)];

            for (int bit = 0; bit < 8; bit++) {
                ColorToDraw = colors[((VRAMByte >> bit) & 1)];

                uint8_t CoordX = x;
                uint8_t CoordY = (height - 1 - (y + bit));
                pixels[CoordY * width + CoordX] = ColorToDraw;
            }
        }
    }

    SDL_UpdateTexture(texture, nullptr, pixels, 2*width);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}
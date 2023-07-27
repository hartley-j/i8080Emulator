//
// Created by hartl on 25/06/2023.
//

#include "Display/Display.h"

Display::Display(const char* Title, int _width, int _height, int _pixelSize) {
    screenWidth = _width;
    screenHeight = _height;
    pixelSize = _pixelSize;

    printf("[INFO] Initialising SDL");
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              screenWidth * pixelSize, screenHeight * pixelSize, 0);
    printf(".");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    printf(".");

    SDL_SetWindowMinimumSize(window, screenWidth, screenHeight);
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
    SDL_RenderSetIntegerScale(renderer, static_cast<SDL_bool>(1));

    screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      screenWidth,
                                      screenHeight);
    printf(".");

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    printf("OK\n");
}

Display::~Display() {
    SDL_DestroyTexture(screenTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::updateScreen(uint8_t* VRAM) {
    void* texturePixels;
    int texturePitch;
    SDL_LockTexture(screenTexture, nullptr, &texturePixels, &texturePitch);

    for (int y=0; y < screenHeight; ++y) {
        for (int x=0; x < screenWidth; ++x) {
            int vramIndex = y * (screenWidth / 8) + (x/8);
            int bitOffset = 7 - (x%8);

            uint8_t pixelValue = (VRAM[vramIndex] >> bitOffset & 0x01);
            uint32_t* pixelData = static_cast<uint32_t *>(texturePixels);
            pixelData[y * (texturePitch / sizeof(uint32_t)) + x] = mapPixelValueToColor(pixelValue);
        }
    }

    SDL_UnlockTexture(screenTexture);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, screenTexture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

uint32_t Display::mapPixelValueToColor(uint8_t pixelValue) {
    return pixelValue == 0 ? 0xFF000000 : 0xFFFFFFFF;
}
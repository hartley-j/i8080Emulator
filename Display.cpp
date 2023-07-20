//
// Created by hartl on 25/06/2023.
//

#include "Display.h"

const uint16_t colors[2] = {0xf000, 0xffff};

Display::Display(const char* Title, uint16_t _width, uint16_t _height) {
    width = _width;
    height = _height;

    memset(pixels, 0, sizeof(pixels));

    printf("[INFO] Initialising SDL");
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              width, height, 0);
    printf(".");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    printf(".");

    SDL_SetWindowMinimumSize(window, width, height);
    SDL_RenderSetLogicalSize(renderer, width, height);
    SDL_RenderSetIntegerScale(renderer, static_cast<SDL_bool>(1));

    surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, 32, (width * 4),
                                       0xFF000000,
                                       0x00FF0000,
                                       0x0000FF00,
                                       0x000000FF);
    printf(".");

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    printf("OK\n");
}

void Display::Update(uint8_t *VRAM) {
    Uint32 ColorToDraw = 0x000000FF;
    Uint8 ColorByte;

    for (int x = 0; x < (width); x++) {
        for (int y = 0; y < (height); y++) {
            ColorByte = VRAM[(x * width) + y];

            for (int bit = 0; bit < 8; bit++) {
                if (((ColorByte >> bit) & 1)) {
                    ColorToDraw = 0xFFFFFFFF;
                }
                int x_coord = x;
                int y_coord = (height - 1 - (y+bit));
                Display::UpdatePixel(x_coord, y_coord, ColorToDraw);
            }
        }
    }
}

void Display::UpdatePixel(int x, int y, Uint32 color) {
    auto * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
            + y * surface->pitch
            + x * surface->format->BytesPerPixel);
    *target_pixel = color;
}
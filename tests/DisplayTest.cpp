//
// Created by joehartley on 27/07/23.
//

// DisplayTest.cpp

#include <gtest/gtest.h>
#include "Display/Display.h"

class DisplayTest : public ::testing::Test {
protected:
    int screenWidth = 224;  // Adjust according to your Space Invaders screen width
    int screenHeight = 256; // Adjust according to your Space Invaders screen height
    int pixelSize = 2;      // Adjust the pixel size for the SDL window

    void SetUp() override {
        // Initialize SDL for the tests
        SDL_Init(SDL_INIT_VIDEO);
    }

    void TearDown() override {
        // Clean up SDL after the tests
        SDL_Quit();
    }
};

// Helper function to get the color of a specific pixel on the SDL window
/*
uint32_t getPixelColor(SDL_Renderer* renderer, int x, int y) {
    uint32_t pixelColor = 0;
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_RenderReadPixels(renderer, &SDL_Rect{ x, y, 1, 1 }, SDL_PIXELFORMAT_ARGB8888, &pixelColor, sizeof(uint32_t));
    return pixelColor;
}
*/

TEST_F(DisplayTest, UpdateScreenTest) {
    Display display("Display Test",screenWidth, screenHeight, pixelSize);

    uint8_t vram[screenWidth * screenHeight / 8];
    memset(vram, 0, sizeof vram);

    vram[20 * (screenWidth / 8) + (10 / 8)] |= 0x80 >> (10 % 8);

    display.updateScreen(vram);
}

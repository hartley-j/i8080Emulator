#include "Display/include/Display/Display.h"
#include "MMU/include/MMU/MMU.h"
#include <chrono>
#include <thread>
#include <SDL.h>
#include <cstdio>

#define HEIGHT 256
#define WIDTH 224

int main(int argc, char** argv) {
    Display Disp = Display("Display Test", WIDTH, HEIGHT);
    MMU mmu = MMU(1);

    SDL_Event ev;
    int windowOpen = 1;

    while(windowOpen) {
        Disp.Update(mmu.VRAM);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        SDL_PollEvent(&ev);
        if(ev.type == SDL_QUIT) {
            windowOpen = 0;
        }
    }

    return 0;
}

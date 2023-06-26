#include "Display.h"
#include "MMU.h"
#include <chrono>
#include <thread>
#include <SDL.h>

#define HEIGHT 400
#define WIDTH 200

int main(int argc, char** argv) {
    Display Disp = Display("Display Test", WIDTH, HEIGHT, 10);
    MMU mmu = MMU(1);

    SDL_Event ev;

    while(ev.type != SDL_QUIT) {
        Disp.Update(mmu.VRAM);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        mmu.testVRAMFlash(HEIGHT, WIDTH);

        SDL_PollEvent(&ev);
    }

    return 0;
}

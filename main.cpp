#include "Display.h"
#include "MMU.h"
#include <chrono>
#include <thread>
#include <SDL.h>

#define HEIGHT 256
#define WIDTH 224

int main(int argc, char** argv) {
    Display Disp = Display("Display Test", WIDTH, HEIGHT);
    MMU mmu = MMU(1);

    SDL_Event ev;

    while(ev.type != SDL_QUIT) {
        Disp.Update(mmu.VRAM);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        SDL_PollEvent(&ev);
    }

    return 0;
}

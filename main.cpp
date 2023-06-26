#include "Display.h"
#include "MMU.h"
#include <chrono>
#include <thread>

#define HEIGHT 400
#define WIDTH 200

int main() {
    Display Disp = Display("Display Test", WIDTH, HEIGHT, 10);
    MMU mmu = MMU(1);
    int count = 0;

    while(count < 1200) {
        Disp.Update(mmu.VRAM);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        mmu.testVRAMFlash(HEIGHT, WIDTH);
        count += 1;
    }

    return 0;
}

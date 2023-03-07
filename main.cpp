#include "features/misc.h"
#include "features/visuals.h"

#include <thread>
#include <iostream>

int main() {
    std::cout << "TPBYHOOK\n\n";

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // bhop
        Misc::bunnyhop();

        //glow
        Visuals::GlowColor glow_color = { 1.f, 0.f, 0.f};
        Visuals::glow(glow_color, true, true);
    }

    return 0;
}
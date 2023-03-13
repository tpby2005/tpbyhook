#include "features/misc.h"
#include "features/visuals.h"
#include "features/legit.h"

#include <thread>
#include <iostream>

int main() {
    std::cout << "TPBYHOOK\n\n";
    std::cout << "Autohop:\t\tEnabled\n";
    std::cout << "Glow:\t\t\tEnabled\n";
    std::cout << "Radar:\t\t\tEnabled\n";
    std::cout << "Triggerbot:\t\tEnabled\n";

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // bhop
        Misc::bunnyhop();

        // glow
        Visuals::GlowColor glow_color = {1.f, 0.f, 0.f};
        Visuals::glow(glow_color, true, true);

        // radar
        Visuals::radar();

        // triggerbot
        Legit::triggerbot();
    }

    return 0;
}
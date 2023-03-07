#include "features/misc.h"

#include <thread>
#include <iostream>

int main() {
    std::cout << "TPBYHOOK\n\n";

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        Misc::bunnyhop();
    }

    return 0;
}
//
// Created by tobyb on 3/12/2023.
//

#include "misc.h"

void Misc::bunnyhop() {
    auto csgo = Memory{"csgo.exe" };
    const auto client = csgo.getModuleAddress("client.dll");

    const auto local_player = csgo.read<uintptr_t>(client + offsets::local_player);
    const auto on_ground = csgo.read<bool>(local_player + offsets::flags);

    if (local_player) {
        if (GetAsyncKeyState(VK_SPACE) && on_ground & (1 << 0)) {
            csgo.write<BYTE>(client + offsets::force_jump, 6);
        }
    }
}
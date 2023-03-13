//
// Created by tobyb on 3/12/2023.
//

#include "legit.h"

void Legit::triggerbot() {
    if (!GetAsyncKeyState(VK_SHIFT)) {
        return;
    }

    auto csgo = Memory{ "csgo.exe" };
    const auto client = csgo.getModuleAddress("client.dll");

    const auto local_player = csgo.read<uintptr_t>(client + offsets::local_player);
    const auto local_health = csgo.read<int32_t>(local_player + offsets::health);

    // player dead
    if (!local_health) {
        return;
    }

    const auto crosshair_id = csgo.read<int32_t>(local_player + offsets::crosshair_id);

    if (!crosshair_id || crosshair_id > 64) {
        return;
    }

    const auto target = csgo.read<uintptr_t>(client + offsets::entity_list + (crosshair_id - 1) * 0x10);

    // target dead
    if (!csgo.read<int32_t>(target + offsets::health)) {
        return;
    }

    // target on same team
    if (csgo.read<int32_t>(target + offsets::team_num) == csgo.read<int32_t>(local_player + offsets::team_num)) {
        return;
    }

    csgo.write<uintptr_t>(client + offsets::force_attack, 6);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    csgo.write<uintptr_t>(client + offsets::force_attack, 4);
}
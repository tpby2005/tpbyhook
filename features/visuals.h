//
// Created by tobyb on 3/7/2023.
//

#ifndef TPBY_HOOK_VISUALS_H
#define TPBY_HOOK_VISUALS_H

#include "../memory.h"
#include "../offsets.h"

namespace Visuals {
    struct GlowColor {
        constexpr GlowColor(float r, float g, float b, float a = 1.f) noexcept:
            r(r), g(g), b(b), a(a) { }

        float r, g, b, a;
    };

    void glow(GlowColor glow_color, bool occluded, bool nonOccluded) {
        auto csgo = Memory { "csgo.exe" };
        const auto client = csgo.getModuleAddress("client.dll");

        const auto local_player = csgo.read<uintptr_t>(client + offsets::local_player);
        const auto glow_object_manager = csgo.read<uintptr_t>(client + offsets::glow_object_manager);

        for (auto i = 0; i < 128; i++) {
            const auto entity = csgo.read<uintptr_t>(client + offsets::entity_list + i + 0x10);

            if (csgo.read<uintptr_t>(entity + offsets::team_num) == csgo.read<uintptr_t>(local_player +
            offsets::team_num)) {
                continue;
            }

            const auto glow_index = csgo.read<int32_t>(entity + offsets::glow_index);

            csgo.write<GlowColor>(glow_object_manager + (glow_index * 0x38) + 0x8, glow_color);

            csgo.write<bool>(glow_object_manager + (glow_index * 0x38) + 0x27, occluded);
            csgo.write<bool>(glow_object_manager + (glow_index * 0x38) + 0x28, nonOccluded);
        }
    }
}

#endif //TPBY_HOOK_VISUALS_H

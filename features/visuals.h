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

    void glow(GlowColor glow_color, bool occluded, bool nonOccluded);

    void radar();
}

#endif //TPBY_HOOK_VISUALS_H

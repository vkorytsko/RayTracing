#pragma once

#include "vec3.h"

#include <iostream>

int to_color(float value) {
    // Translate normalized value to [0,255] range.
    return static_cast<int>(255.999 * value);
}

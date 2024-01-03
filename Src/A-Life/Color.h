#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/color_space.hpp>

using color3_t  = glm::vec3;
using color4_t  = glm::vec4;
using rgba_t    = uint32_t;

inline float linearToGamma(float linear)
{
    return sqrt(linear);
}

inline color3_t hsvToRGB(float h, float s, float v)
{
    return glm::rgbColor(glm::vec3{ h, s, v });
}

inline color4_t rgbaToColor4(const rgba_t& rgba)
{
    color4_t color;

    color.r = ((rgba >> 24) & 0xff) / 255.0f;
    color.g = ((rgba >> 16) & 0xff) / 255.0f;
    color.b = ((rgba >>  8) & 0xff) / 255.0f;
    color.a = ((rgba >>  0) & 0xff) / 255.0f;

    return color;
}

inline rgba_t color4ToRGBA(const color4_t& color)
{
    rgba_t rgba = 0;

    rgba |= uint8_t(glm::clamp(linearToGamma(color.r), 0.0f, 1.0f) * 255) << 24;
    rgba |= uint8_t(glm::clamp(linearToGamma(color.g), 0.0f, 1.0f) * 255) << 16;
    rgba |= uint8_t(glm::clamp(linearToGamma(color.b), 0.0f, 1.0f) * 255) << 8;
    rgba |= uint8_t(glm::clamp(color.a, 0.0f, 1.0f) * 255) << 0;

    return rgba;
}

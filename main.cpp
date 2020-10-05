#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb_image_write.h"

#include "color.h"
#include "ray.h"
#include "vec3.h"


color ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


int main() {

    // Image

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render

#define CHANNEL_NUM 3
    uint8_t* pixels = new uint8_t[image_width * image_height * CHANNEL_NUM];

    int index = 0;
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r);

            pixels[index++] = to_color(pixel_color.x());
            pixels[index++] = to_color(pixel_color.y());
            pixels[index++] = to_color(pixel_color.z());
        }
    }

    std::cerr << "\nDone.\n";

    stbi_write_png("image.png", image_width, image_height, CHANNEL_NUM, pixels, image_width * CHANNEL_NUM);
    delete[] pixels;

    return 0;
}

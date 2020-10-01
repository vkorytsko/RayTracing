#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb_image_write.h"

#include "color.h"
#include "vec3.h"


int main() {

    // Image

    const int image_width = 256;
    const int image_height = 256;
#define CHANNEL_NUM 3

    // Render

    uint8_t* pixels = new uint8_t[image_width * image_height * CHANNEL_NUM];

    int index = 0;
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);

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

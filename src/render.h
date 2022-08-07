#pragma once
#include <fstream>
#include "trace.h"

#define M_PI 3.141592653589793f

void render(const std::vector<Sphere> &spheres)
{
    unsigned width = 640, height = 400;
    Vec3f *image = new Vec3f[width * height], *pixel = image;
    
    float invWidth = 1 / float(width), invHeight = 1 / float(height);
    float fov = 30, aspectratio = width / float(height);
    float angle = tan(M_PI * 0.5f * fov / 180);

    // Trace rays
    for (unsigned y = 0; y < height; ++y) 
    {
        for (unsigned x = 0; x < width; ++x, ++pixel) 
        {
            float xx = (2 * ((x + 0.5f) * invWidth) - 1) * angle * aspectratio;
            float yy = (1 - 2 * ((y + 0.5f) * invHeight)) * angle;

            Vec3f raydir(xx, yy, -1);
            raydir.normalize();
            *pixel = trace(Vec3f(0), raydir, spheres, 0);
        }
    }
}

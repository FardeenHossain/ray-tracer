#pragma once
#include "sphere.h"

#define MAX_RAY_DEPTH 5

float mix(const float &a, const float &b, const float &mix)
{
    return b * mix + a * (1 - mix);
}

Vec3f trace(const Vec3f &rayorig, const Vec3f &raydir, const std::vector<Sphere> &spheres, const int &depth)
{
    float tnear = INFINITY;
    const Sphere* sphere = NULL;

    // Find intersection of this ray with the sphere in the scene
    for (unsigned i = 0; i < spheres.size(); ++i) 
    {
        float t0 = INFINITY, t1 = INFINITY;

        if (spheres[i].intersect(rayorig, raydir, t0, t1)) 
        {
            if (t0 < 0) 
            {
                t0 = t1;
            }

            if (t0 < tnear) 
            {
                tnear = t0;
                sphere = &spheres[i];
            }
        }
    }

    // If there's no intersection return black or background color
    if (!sphere) 
    {
        return Vec3f(2);
    }
}

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

    Vec3f surfaceColor = 0;                   // Color of the ray/surfaceof the object intersected by the ray
    Vec3f phit = rayorig + raydir * tnear;    // Point of intersection
    Vec3f nhit = phit - sphere->center;       // Normal at the intersection point
    nhit.normalize();                         // Normalize normal direction

    // If the normal and the view direction are not opposite to each other, reverse the normal direction. That also 
    // means we are inside the sphere so set the inside bool to true. Finally reverse the sign of IdotN which we want
    // positive.

    float bias = 1e-4f;    // Add some bias to the point from which we will be tracing
    bool inside = false;

    if (raydir.dot(nhit) > 0) 
    {
        nhit = -nhit, inside = true;
    }

    if ((sphere->transparency > 0 || sphere->reflection > 0) && depth < MAX_RAY_DEPTH) 
    {
        float facingratio = -raydir.dot(nhit);

        // Change the mix value to tweak the effect
        float fresneleffect = mix(powf(1 - facingratio, 3), 1, 0.1f);

        // Compute reflection direction (no need to normalize because all vectors are already normalized)
        Vec3f refldir = raydir - nhit * 2 * raydir.dot(nhit);
        refldir.normalize();

        Vec3f reflection = trace(phit + nhit * bias, refldir, spheres, depth + 1);
        Vec3f refraction = 0;

        // If the sphere is also transparent compute refraction ray (transmission)
        if (sphere->transparency) 
        {
            float ior = 1.1f, eta = (inside) ? ior : 1 / ior;    // Inside or outside the surface?
            float cosi = -nhit.dot(raydir);
            float k = 1 - eta * eta * (1 - cosi * cosi);

            Vec3f refrdir = raydir * eta + nhit * (eta *  cosi - sqrt(k));
            refrdir.normalize();
            refraction = trace(phit - nhit * bias, refrdir, spheres, depth + 1);
        }

        // The result is a mix of reflection and refraction (if the sphere is transparent)
        surfaceColor = (reflection * fresneleffect + 
        refraction * (1 - fresneleffect) * sphere->transparency) * sphere->surfaceColor;
    }
}

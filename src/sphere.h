#pragma once
#include <vector>
#include "vec3.h"

class Sphere
{
public:
    Vec3f center;                         // Position of the sphere
    float radius, radius2;                // Sphere radius and radius^2
    Vec3f surfaceColor, emissionColor;    // Surface color and emission (light)
    float transparency, reflection;       // Surface transparency and reflectivity

    Sphere(const Vec3f &c,
           const float &r,
           const Vec3f &sc,
           const float &refl = 0,
           const float &transp = 0,
           const Vec3f &ec = 0) : center(c), radius(r), radius2(r * r), surfaceColor(sc), emissionColor(ec), 
           transparency(transp), reflection(refl) {}
};

#include <vector>
#include "render.h"

int main(int argc, char **argv)
{
    printf("Loading...\n");
    std::vector<Sphere> spheres;

    // Position, radius, surface color, reflectivity, transparency, and emission color
    spheres.push_back(Sphere(Vec3f( 0.0f ,-10004 , -20), 10000, Vec3f(0.25f, 0.25f, 0.25f), 0.0f, 0.0f));
    spheres.push_back(Sphere(Vec3f( 0.0f , 0     , -20), 4,     Vec3f(1.00f, 0.25f, 0.25f), 1.0f, 0.5f));
    spheres.push_back(Sphere(Vec3f( 5.0f ,-1     , -15), 2,     Vec3f(0.25f, 1.00f, 0.50f), 1.0f, 0.0f));
    spheres.push_back(Sphere(Vec3f( 5.0f , 0     , -25), 3,     Vec3f(0.25f, 0.50f, 1.00f), 1.0f, 0.0f));
    spheres.push_back(Sphere(Vec3f(-5.5f , 0     , -15), 3,     Vec3f(1.00f, 1.00f, 1.00f), 1.0f, 0.0f));

    // Light
    spheres.push_back(Sphere(Vec3f( 0.0f , 20    , -25), 3,     Vec3f(0.00f, 0.00f, 0.00f), 0.0f, 0.0f, Vec3f(3)));
    
    printf("Writing file: render.ppm\n");
    render(spheres);
    
    printf("Finished!\n");
    return 0;
}

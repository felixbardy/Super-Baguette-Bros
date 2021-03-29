#ifndef CONSOLERENDERER_H
#define CONSOLERENDERER_H

#include <iostream>

#include "core/World.h"

class ConsoleRenderer
{
private:
    World* world;
    int image_height;
    int image_width;
    int camera_offset;
    float tile_width;
    char** image;

    void fill(char c);
    void draw_line(int sx, int sy, int ex, int ey, char c);
    void draw_rectangle(int minx, int miny, int maxx, int maxy, char c);

    bool is_in_bounds(Vec2f point);
public:
    ConsoleRenderer(World* world, int width, int height, float scale);
    ~ConsoleRenderer();

    void render();
};





#endif //CONSOLERENDERER_H
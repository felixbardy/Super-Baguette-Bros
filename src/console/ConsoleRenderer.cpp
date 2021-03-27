#include "ConsoleRenderer.h"
#include <cassert>
using namespace std;

ConsoleRenderer::ConsoleRenderer(World* world, int height, int width, float scale)
: world(world), image_height(height), image_width(width), tile_width(scale)
{
    image = new char*[image_height];
    for (int i = 0; i < image_height; i++)
        image[i] = new char[image_width];
        
    
}

ConsoleRenderer::~ConsoleRenderer()
{
    for (int i = 0; i < image_height; i++)
        delete [] image[i];
    
    delete [] image;
}


void ConsoleRenderer::render()
{
    cout << "\x1B[2J\x1B[H";
    fill('*');
    
    Platform** platforms = world->getPlatforms();
    const int* nPlatforms = world->getPlatformsSizes();
    const Player& player = world->getPlayer();

    //FIXME Récupérer la vraie fin du monde
    float world_end = 1000000; 

    // Si le joueur est trop proche du bord, la caméra se bloque
    // Sinon, elle suit le joueur
    int camera_offset = max( (image_width/2) * tile_width, min( player.getPosition().x, world_end - (image_width/2) * tile_width));

	for (int y = 0; y < image_height; y++)
	{
        for (int x = 0; x < image_width; x++)
        {
            cout << image[y][x] << image[y][x];
        }
        cout << endl;
    }
}

void ConsoleRenderer::fill(char c)
{
    draw_rectangle(0,0,image_width-1,image_height-1,c);
}

void ConsoleRenderer::draw_line(int sx, int sy, int ex, int ey, char c)
{
    assert(0 <= sx && sx < image_width);
    assert(0 <= ex && ex < image_width);
    assert(0 <= sy && sy < image_height);
    assert(0 <= ey && ey < image_height);
    
    int tmp;
    if (ey < sy) {tmp=ey; ey=sy; sy=tmp;}
    if (ex < sx) {tmp=ex; ex=sx; sx=tmp;}

    if (sx == ex) // Vertical
    {
        for (int i = sy; i < ey; i++)
            image[i][sx] = c;
    }
    else if (sy == ey) // Horizontal
    {
        for (int i = sx; i < ex; i++)
        {
            std::cout<<i<<std::endl;
            image[i][sy] = c;
        }
    }
    else // Where the shit hits the fan
    {
        //FIXME Il y a sûrement un meilleur moyen de dessiner une diagonale
        Vec2f start(sx,sy);
        Vec2f end(ex,ey);
        Vec2f current;
        int steps = int( (end-start).getLength() ) + 1;
        for (int i = 0; i <= steps; i++)
        {
            float t = (i/(float)steps);
            current = end * t + start * (1 - t);
            image[int(current.y)][int(current.x)] = c;
        }
    }
}

void ConsoleRenderer::draw_rectangle(int minx, int miny, int maxx, int maxy, char c)
{
    assert(0 <= minx && minx < image_width);
    assert(0 <= maxx && maxx < image_width);
    assert(0 <= miny && miny < image_height);
    assert(0 <= maxy && maxy < image_height);

    int tmp;
    if (maxy < miny) {tmp=maxy; maxy=miny; miny=tmp;}
    if (maxx < minx) {tmp=maxx; maxy=minx; minx=tmp;}

    for(int y = miny; y <= maxy; y++)
        for(int x = minx; x <= maxx; x++)
            image[y][x] = c;

}
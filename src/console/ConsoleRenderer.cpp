#include "ConsoleRenderer.h"
#include <cassert>
using namespace std;

ConsoleRenderer::ConsoleRenderer(World* world, int width, int height, float scale)
: world(world), image_height(height), image_width(width), tile_width(scale), camera_offset(0)
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
    fill(' ');
    
    Platform** platforms = world->getPlatforms();
    const int* nPlatforms = world->getPlatformsSizes();
    const Player& player = world->getPlayer();

    //FIXME Récupérer la vraie fin du monde
    float world_end = 1000000; 

    // Si le joueur est trop proche du bord, la caméra se bloque
    // Sinon, elle suit le joueur
    this->camera_offset = max( 0.0f, min( player.getPosition().x - image_width/2, world_end - image_width * tile_width));

    for (int i = 0; i < 3; i++)
    {
        Platform* current_platforms = platforms[i];
        const int n = nPlatforms[i];
        for (int j = 0; j < n; j++)
        {
            cout << "Plateforme " << j << " du segment " << i << ": ";
            const Platform&  current_platform = current_platforms[j];
            Vec2f position = current_platform.getPosition();
            float width = current_platform.getWidth();
            draw_line(position.x, position.y, position.x+width, position.y, '=');
        }
    }

	for (int y = image_height-1; y >= 0; y--)
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
    Vec2f start(sx - camera_offset, sy), end(ex - camera_offset, ey);
    
    int tmp;
    if (end.y < start.y) {tmp=end.y; end.y=start.y; start.y=tmp;}
    if (end.x < start.x) {tmp=end.x; end.x=start.x; start.x=tmp;}

    if (start.x == end.x) // Vertical
    {
        for (int i = start.y; i < end.y; i++)
            if ( is_in_bounds( Vec2f(start.x, i) ) )
                image[i][int(start.x)] = c;
    }
    else if (start.y == end.y) // Horizontal
    {
        cout << "horizontal line: " << endl;;
        for (int i = start.x; i < end.x; i++)
        {
            cout << "(" << i << ", " << start.y << ")" << endl;
            if ( is_in_bounds( Vec2f(i, start.y) ) )
            {
                cout << "(" << i << ", " << start.y << ") is in bounds" << endl;
                image[int(start.y)][i] = c;
            }
        }
    }
    else // Where the shit hits the fan
    {
        //FIXME Il y a sûrement un meilleur moyen de dessiner une diagonale
        Vec2f current;
        int steps = int( (end-start).getLength() ) + 1;
        for (int i = 0; i <= steps; i++)
        {
            float t = (i/(float)steps);
            current = end * t + start * (1 - t);
            if ( is_in_bounds(current) )
                image[int(current.y)][int(current.x)] = c;
        }
    }
    cout << "dessiné!" << endl;
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

bool ConsoleRenderer::is_in_bounds(Vec2f point)
{
    return !((point.x >= image_width  || point.x < 0) || (point.y >= image_height || point.y < 0));
}
#include "console/ConsoleRenderer.h"

int main()
{
    World w;
    ConsoleRenderer cr = ConsoleRenderer(&w, 20, 50, 1);

    cr.render();
    return 0;
}
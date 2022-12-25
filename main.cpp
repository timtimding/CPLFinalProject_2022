#include "SDL_total.h"
#include "Texture.h"
#include "game.h"
#include "fileManager.h"

Game *game = NULL;

int main( int argc, char* args[] )
{
    game->initialize();
    playMusic();
    game->startSurface();
    saveProgress(&GetProgress());
	close();
    return 0;
}

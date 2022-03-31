#include "Mesa.h"
#include "Gark.h"
#include "Player.h"
#include "globals.h"
#include "Game.h"
#include "History.h"
using namespace std;




int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(3, 4, 2);

    // Play the game
    g.play();
}



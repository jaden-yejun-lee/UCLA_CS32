#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    std::vector<Actor> myActors;
}

int StudentWorld::init()
{
   
    Level lev(assetPath());
    string level_file = "level01.txt";
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
        return GWSTATUS_LEVEL_ERROR;
    else if (result == Level::load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR;
    else if (result == Level::load_success)
    {
        Level::GridEntry ge;
        for (int x = 0; x < 32; x++) {
            for (int y = 0; y < 32; y++) {
                ge = lev.getContentsOf(x, y);
                switch (ge)
                {
                case Level::empty:
                    break;

                case Level::peach:
                    m_peach = new Peach(IID_PEACH, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, 0, 0, 1, this);
                    break;

                case Level::block:
                    myActors.push_back(new Block(IID_BLOCK, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, 0, 2, 1, this));
                    break;
                }
            }
        }
     
    }

    return GWSTATUS_CONTINUE_GAME;
}


StudentWorld::~StudentWorld() {
    cleanUp();
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
    //return GWSTATUS_PLAYER_DIED;

    // iterate through vector and have each actor doSomething()
    vector<Actor*> ::iterator it;
    it = myActors.begin();
   
    while (it != myActors.end()) {

        if ((*it)->isAlive()) {

            (*it)->doSomething();

            // if peach died during this tick
            if (!m_peach->isAlive()) {
                playSound(SOUND_PLAYER_DIE);
                return GWSTATUS_PLAYER_DIED;
    
            }

            // if peach reached mario
            // if peach has reached a flag

        }

        it++;
    }

    m_peach->doSomething();

    // Remove dead actors
    // Update game status line
    
    
    // continue playing the current level
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_peach;
    vector<Actor*> ::iterator it;
    it = myActors.begin();

    while (it != myActors.end()) {
        Actor* temp;
        temp = (*it);
        it = myActors.erase(it);
        delete temp;
    }
}

                       //  
bool StudentWorld::overlap(double x, double y, char dir) {
    vector<Actor*> ::iterator it;
    it = myActors.begin();

    // iterate through all actors
    while (it != myActors.end()) {
      
        // if (*it) is on the left hand side of object calling this function
        if (dir == 'l') {
            if (x <= (*it)->getX() + SPRITE_WIDTH  && x >= (*it)->getX()  &&  y >= (*it)->getY() && y <= (*it)->getY() + SPRITE_HEIGHT - 1 ) {
                std::cout << "Blocked by left";
                return true;
            }
        }

        // if (*it) is on the right hand side of object calling this function
        else if (dir == 'r') {
 

            if (x + SPRITE_WIDTH >= (*it)->getX() && x + SPRITE_WIDTH <= (*it)->getX() + SPRITE_WIDTH - 1 && y >= (*it)->getY() && y <= (*it)->getY() + SPRITE_HEIGHT - 1) {
                return true;
            }

        }


        // if (*it) blocks movement  if it overlaps with targetx and target y
        else if (dir == 'm') {

            if (  ((x >= (*it)->getX()  && x <= (*it)-> getX() + SPRITE_WIDTH - 1) || (x + SPRITE_WIDTH - 1 >= (*it)->getX() && x + SPRITE_WIDTH - 1 <= (*it)->getX() + SPRITE_WIDTH - 1) ) 
                && y + SPRITE_HEIGHT - 1 >= (*it)->getY() && y + SPRITE_HEIGHT - 1 <= (*it)->getY() + SPRITE_HEIGHT - 1 ) {
                if ((*it)->blocksMovement()) {
                    return true;
                }
            }
        }
       

        // if any three pixels below (*it) blocks movement
        else if (dir == 'c') {
     
            if (((x >= (*it)->getX() && x <= (*it)->getX() + SPRITE_WIDTH - 1) || (x + SPRITE_WIDTH - 1 >= (*it)->getX() && x + SPRITE_WIDTH - 1 <= (*it)->getX() + SPRITE_WIDTH - 1)) 
                && y <= (*it)->getY() + SPRITE_HEIGHT + 2 && y >= (*it)->getY() + SPRITE_HEIGHT - 1) {
                return true;
            }
        }

        it++;
    }
    return false;
}


// if there is an object that would block one pixel below
bool StudentWorld::objectCanBlock() {
    
    double x = m_peach->getX();
    double y = m_peach->getY();

    vector<Actor*>::iterator it;
    it = myActors.begin();
    while (it != myActors.end()) {
        // should encompass a range of x values and a range of y values

        if (x >= (*it)->getX() && x <= (*it)->getX() + SPRITE_WIDTH - 1) {
            if (y <= (*it)->getY() + SPRITE_HEIGHT && y >= (*it)->getY()) {
                if ((*it)->blocksMovement()) {
                    return true;
                }
            }
        }

        it++;
    }

    return false;
}

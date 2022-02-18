#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <vector>



// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Block;
class Peach;
class Actor;

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  virtual ~StudentWorld();
  bool overlap(double x, double y, char dir);

  // object at position x, y
  bool objectCanBlock();

private:
	std::vector<Actor*> myActors;
	Peach* m_peach;
	StudentWorld* studentWorld;
};

#endif // STUDENTWORLD_H_

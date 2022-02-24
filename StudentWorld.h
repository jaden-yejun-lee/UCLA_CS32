#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <list>



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
 
  // object at position x, y

   bool overlap(double x, double y, bool shouldBonk);
   bool overlapGoomba(double x, double y, bool shouldBonk, char dir);
   bool overlapWithPeach(double x, double y, char object);
   bool overlapWithPowerup(double x, double y, char goodie);

  bool objectCanBlock();
  void introduceNewObject(Actor* a);
  bool checkPower(char goodie);
  void changePower(bool b, char goodie);
  void changeInvincibility(int i);
  void changeHP(int i);
  void peachBonk();

private:
	std::list<Actor*> myActors;
	Peach* m_peach;
	StudentWorld* studentWorld;
	bool m_levelOver;
};

#endif // STUDENTWORLD_H_

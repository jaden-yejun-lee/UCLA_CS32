#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

// base class
class Actor : public GraphObject {
  public:
	  Actor(int imageID, int startX, int startY, int dir, int depth, double size, bool isAlive, StudentWorld* world); 

	  virtual ~Actor();
	  virtual void doSomething() = 0;
	  void kill();
	  bool isAlive();
	  StudentWorld* getWorld();
	  virtual bool isDamageable() = 0;
	  virtual void attemptToDamage() = 0;
	  virtual void bonk() = 0;
	  virtual bool blocksMovement() = 0;
	
	 


  private:
	  bool m_alive;
	  StudentWorld* m_studentWorld;
	  
};


class Block : public Actor {
  public: 
	  Block(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world);
	  virtual ~Block();
	  virtual void doSomething(); 
	  virtual bool isDamageable();
	  virtual void attemptToDamage();
	  virtual void bonk();
	  virtual bool blocksMovement();



  private: 
	
};

class Peach : public Actor {
  public: 
	  Peach(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world);
	  virtual ~Peach();
	  virtual void doSomething();
	  virtual bool isDamageable();
	  virtual void attemptToDamage();
	  virtual void bonk();
	  virtual bool blocksMovement();
	 


  private: 
	  int m_hp;
	  bool m_invincibility;
	  int m_jump_distance;
};


#endif // ACTOR_H_


// common parts they share and implement shared parts
// after implement specific things

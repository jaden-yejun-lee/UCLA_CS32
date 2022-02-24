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
	  Block(int imageID, int startX, int startY, int dir, int depth, double size, int goodie, StudentWorld* world);
	  virtual ~Block();
	  virtual void doSomething(); 
	  virtual bool isDamageable();
	  virtual void attemptToDamage();
	  virtual void bonk();
	  virtual bool blocksMovement();


  private: 
	 
	  int m_goodie;
	  // 0 equals no goodie
	  // 1 equals flower goodie
	  // 2 equals mushroom goodie
	  // 3 equals star goodie
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
	  void changeInvincibility(int i);
	  bool checkInvincibility();
	  void changePower(bool b, char goodie);
	  bool checkPower(char goodie);
	  void changeHP(int i);
	 


  private: 
	  int m_hp;
	  int m_invincibility;
	  int m_temp_invincibility;
	  int m_jump_distance;
	  bool m_shoot_power;
	  bool m_jump_power;
	  int m_time_to_recharge;
};

class Pipe :public Actor {
  public:
  	Pipe(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world);
	virtual void doSomething();
	virtual bool isDamageable();
	virtual void attemptToDamage();
	virtual void bonk();
	virtual bool blocksMovement();
	virtual ~Pipe();

};

class Flag : public Actor {
	public:
		Flag(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world);
		virtual void doSomething();
		virtual bool isDamageable();
		virtual void attemptToDamage();
		virtual void bonk();
		virtual bool blocksMovement();
		virtual ~Flag();
		
private:
	
};

class Flower : public Actor {
public:
	Flower(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world);
	virtual void doSomething();
	virtual bool isDamageable();
	virtual void attemptToDamage();
	virtual void bonk();
	virtual bool blocksMovement();
	virtual ~Flower();
};

class PeachFireball : public Actor {
public:
	PeachFireball(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world);
	virtual void doSomething();
	virtual bool isDamageable();
	virtual void attemptToDamage();
	virtual void bonk();
	virtual bool blocksMovement();
	virtual ~PeachFireball();
};

class Mushroom : public Actor {
public:
	Mushroom(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world);
	virtual void doSomething();
	virtual bool isDamageable();
	virtual void attemptToDamage();
	virtual void bonk();
	virtual bool blocksMovement();
	virtual ~Mushroom();
};

class Star : public Actor {
public:
	Star(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world);
	virtual void doSomething();
	virtual bool isDamageable();
	virtual void attemptToDamage();
	virtual void bonk();
	virtual bool blocksMovement();
	virtual ~Star();
};

class Goomba : public Actor {
public:
	Goomba(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world);
	virtual void doSomething();
	virtual bool isDamageable();
	virtual void attemptToDamage();
	virtual void bonk();
	virtual bool blocksMovement();
	virtual ~Goomba();
};


#endif // ACTOR_H_


// common parts they share and implement shared parts
// after implement specific things

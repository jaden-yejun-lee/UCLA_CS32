#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>



// ACTOR
Actor::Actor(int imageID, int startX, int startY, int dir, int depth, double size, bool isAlive, StudentWorld* world) : GraphObject(imageID, startX, startY, dir, depth, size) {
	m_alive = isAlive;
	m_studentWorld = world;
	
}

void Actor::kill() {
	m_alive = false;
}

bool Actor::isAlive() {
	if (m_alive) {
		return true;
	}

	return false;
}

StudentWorld* Actor::getWorld() {
	return m_studentWorld;
}

Actor::~Actor() {

}



// BLOCK
Block::Block(int imageID, int startX, int startY, int dir, int depth, double size, int goodie, StudentWorld* world) : Actor(imageID, startX, startY, 0, 2, 1, true, world) {
	m_goodie = goodie;
}

void Block::doSomething() {

}

bool Block::isDamageable() {
	return false;
}

void Block::attemptToDamage() {

}

void Block::bonk() {



	if (m_goodie == 0) {
		getWorld()->playSound(SOUND_PLAYER_BONK);
	}

	else {
		getWorld()->playSound(SOUND_POWERUP_APPEARS);
		
		switch (m_goodie) {

		// flower goodie
		case 1: 
			// introduce a new flower object
			getWorld()->introduceNewObject(new Flower(IID_FLOWER, getX(), getY() + 8, 0, 2, 1, getWorld()));
			break;
		case 2:
			// introdue a new mushroom object
			getWorld()->introduceNewObject(new Mushroom(IID_MUSHROOM, getX(), getY() + 8, 0, 1, 1, getWorld()));
			break;
		case 3:
			// introduce a new star object
			getWorld()->introduceNewObject(new Star(IID_STAR, getX(), getY() + 8, 0, 1, 1, getWorld()));
			break;
		}

		m_goodie = 0;
	}

}

bool Block::blocksMovement() {
	return true;
}

Block::~Block() {

}


// PEACH
Peach::Peach(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world) : Actor(imageID, startX, startY, 0, 0, 1, true, world) {
	m_hp = 1;
	m_temp_invincibility = 0;
	m_invincibility = 0;
	m_jump_distance = 0;
	m_shoot_power = false;
	m_jump_power = false;
	m_time_to_recharge = 0;
}

void Peach::doSomething() {

	double curX = getX();
	double curY = getY();

	int ch;




	if (isAlive()) {

		// check if currently invincible (STAR POWER)
		if (m_invincibility > 0) {
			m_invincibility--;
			
		}
		
		//check if currently temporarily invincible (FIRE POWER OR JUMP POWER)
		if (m_temp_invincibility > 0) {
			m_temp_invincibility--;
		}

		// check recharge mode with shoot power
		if (m_time_to_recharge > 0) {
			m_time_to_recharge--;
		}



		// if peach currently overlaps with any game object, she must bonk the object
		if (getWorld()->overlap(curX, curY, true)) {
			// *it gets bonked in overlap
		}

		// if peach previously initiated a jump
		if (m_jump_distance > 0) {

			double targetX = getX();
			double targetY = getY() + 4;

			// peach tries to move upward
			if (getWorld()->overlap(targetX, targetY, true)) {
				// bonk is called in overlap
				m_jump_distance = 0;
			}
			else {
				moveTo(targetX, targetY);
				m_jump_distance--;
			}

		}

		// peach is not actively jumping
		else if (m_jump_distance == 0) {

			int count = 0;
			for (int i = 0; i <= 3; i++) {
				if (!getWorld()->overlap(curX, curY - i, false)) {
					count++;
				}
			}
			if (count == 4) {
				moveTo(curX, curY - 4);
			}
			
		}

		if (getWorld()->getKey(ch)) {
			switch (ch) {
			case KEY_PRESS_LEFT:
				// move Peach left
				setDirection(180);

				if (getWorld()->overlap(getX() - 4, getY(), true)) {

				}
				else {
					moveTo(getX() - 4, getY());
				}

				break;

			case KEY_PRESS_RIGHT:
				// move Peach right
				setDirection(0);

				if (getWorld()->overlap(getX() + 4, getY(), true)) {

				}
				else {
					moveTo(getX() + 4, getY());
				}


				break;

			case KEY_PRESS_UP:
				// make Peach jump

				// if there is an object that would block one pixel below
				if (getWorld()->objectCanBlock()) {

					if (m_jump_power == false) {
						m_jump_distance = 8;
					}
					else if (m_jump_power == true) {
						m_jump_distance = 12;
					}
					getWorld()->playSound(SOUND_PLAYER_JUMP);
					
				}
				break;

			case KEY_PRESS_SPACE:
				if (m_shoot_power == false) {
					
				}
				else if (m_time_to_recharge > 0) {
					
				}
				else {
	

					getWorld()->playSound(SOUND_PLAYER_FIRE);
					m_time_to_recharge = 8;
					if (getDirection() == 0) {
						getWorld()->introduceNewObject(new PeachFireball(IID_PEACH_FIRE, getX() + 4, getY(), 0, 1, 1, getWorld()));
					}
					else if (getDirection() == 180) {
						getWorld()->introduceNewObject(new PeachFireball(IID_PEACH_FIRE, getX() - 4, getY(), 180, 1, 1, getWorld()));
					}
					
				}





			}
		}

	}



}

bool Peach::isDamageable() {
	return true;
}

void Peach::attemptToDamage() {
	this->bonk();
}

void Peach::bonk() {
	if (m_temp_invincibility > 0 || m_invincibility > 0) {
		return;
	}
	else {
		m_hp--;
		m_temp_invincibility = 10;
		changePower(false, 'f');
		changePower(false, 'm');
		if (m_hp >= 1) {
			getWorld()->playSound(SOUND_PLAYER_HURT);
		}
		else if (m_hp <= 0) {
			kill();

		}
	}

}

bool Peach::blocksMovement() {
	return false;
}

void Peach::changePower(bool b, char goodie) {
	

	switch (goodie) {
	case 'f':
		m_shoot_power = b;
		break;
	case 'm':
		m_jump_power = b;
		break;
	case 's':
		break;
	}

}

bool Peach::checkPower(char goodie) {

	switch (goodie) {
	case 'f':
		if (m_shoot_power == true) {
			return true;
		}
		return false;
		break;
	case 'm':
		if (m_jump_power == true) {
			return true;
		}
		return false;
		break;
	}

	
}

void Peach::changeHP(int i) {
	m_hp = i;
}

void Peach::changeInvincibility(int i) {
	m_invincibility = i;
}

bool Peach::checkInvincibility() {
	if (m_invincibility > 0) {
		return true;
	}
	
	return false;
}

Peach::~Peach() {

}



// PIPE
Pipe::Pipe(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world) : Actor(imageID, startX, startY, 0, 2, 1, true, world) {

}

void Pipe::doSomething() {

}

bool Pipe::isDamageable() {
	return false;
}

void Pipe::attemptToDamage() {

}

void Pipe::bonk() {
	getWorld()->playSound(SOUND_PLAYER_BONK);
}

bool Pipe::blocksMovement() {
	return true;
}

Pipe::~Pipe() {

}

// FLAG
Flag::Flag(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world) : Actor(imageID, startX, startY, 0, 1, 1, true, world) {
	
}

void Flag::doSomething() {
	if (this->isAlive()) {
		if (getWorld()->overlapWithPeach(getX(), getY(), 'f')) {
			getWorld()->increaseScore(1000);
			this->kill();
		}
	}
}

bool Flag::isDamageable() {
	return false;
}

void Flag::attemptToDamage() {

}

void Flag::bonk() {
	
}

bool Flag::blocksMovement() {
	return false;
}


Flag::~Flag() {

}

// FLOWER
Flower::Flower(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world) : Actor(imageID, startX, startY, 0, 1, 1, true, world) {
	
}

void Flower::doSomething() {
	// if flower overlaps with peach
	if (getWorld()->overlapWithPeach(getX(), getY(), ' ')) {
		getWorld()->increaseScore(50);
		getWorld()->changePower(true, 'f');
		getWorld()->changeHP(2);
		this->kill();
		getWorld()->playSound(SOUND_PLAYER_POWERUP);
	}
	// else move
	else {
		// check two pixels below
		if (!getWorld()->overlap(getX(), getY() - 2, false)) {
			moveTo(getX(), getY() - 2);
		}
		
		double targetX1 = getX() + 2;
		double targetX2 = getX() - 2;
		double targetY = getY();

		if (getDirection() == 0) {
			// check two pixels to the right
			if (getWorld()->overlap(getX() + 2, getY(), false)) {
				setDirection(180);
				return;
			}
			else {
				moveTo(targetX1, targetY);
			}


		}
		else if (getDirection() == 180) {
			//check two pixels to the left
			if (getWorld()->overlap(getX() - 2, getY(), false)) {
				setDirection(0);
				return;
			}
			else {
				moveTo(targetX2, targetY);
			}
		}


	}

}

bool Flower::isDamageable() {
	return false;
}

void Flower::attemptToDamage() {

}

void Flower::bonk() {

}

bool Flower::blocksMovement() {
	return false;
}

Flower::~Flower() {

}

// PEACH FIREBALL
PeachFireball::PeachFireball(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world) : Actor(imageID, startX, startY, dir, 1, 1, true, world) {

}

void PeachFireball::doSomething() {
	// check if peach fireball currently overlaps with a damageable object
	if (getWorld()->overlapWithPowerup(getX(), getY(), 'f')) {
		// inform object that it has been damaged (done in overlap function)	
		kill();
		return;
	}
	else {
		// check if there is object blocking two pixels downward
		
		if (!getWorld()->overlap(getX(), getY() - 2, false)) {
			moveTo(getX(), getY() - 2);
			
		}

		if (getDirection() == 0) {
			
			if (getWorld()->overlap(getX() + 2, getY(), false)) {
				
				kill();
				return;
			}
			else {
				
				moveTo(getX() + 2, getY());
			}

		}
		else if (getDirection() == 180) {
			if (getWorld()->overlap(getX() - 2, getY(), false)) {
				kill();
				return;
			}
			else {
				moveTo(getX() - 2, getY());
			}
		}



	}
}

bool PeachFireball::isDamageable() {
	return false;
}

void PeachFireball::attemptToDamage() {

}

void PeachFireball::bonk() {

}

bool PeachFireball::blocksMovement() {
	return false;
}

PeachFireball::~PeachFireball() {

}

// MUSHROOM
Mushroom::Mushroom(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world) : Actor(imageID, startX, startY, 0, 1, 1, true, world) {

}

void Mushroom::doSomething() {
	// if mushroom overlaps with peach
	if (getWorld()->overlapWithPeach(getX(), getY(), ' ')) {
		getWorld()->increaseScore(75);
		getWorld()->changePower(true, 'm');
		getWorld()->changeHP(2);
		kill();
		getWorld()->playSound(SOUND_PLAYER_POWERUP);
		return;
	}
	else {
		// check two pixels below
		if (!getWorld()->overlap(getX(), getY() - 2, false)) {
			moveTo(getX(), getY() - 2);
		}

		double targetX1 = getX() + 2;
		double targetX2 = getX() - 2;
		double targetY = getY();

		if (getDirection() == 0) {
			// check two pixels to the right
			if (getWorld()->overlap(getX() + 2, getY(), false)) {
				setDirection(180);
				return;
			}
			else {
				moveTo(targetX1, targetY);
			}


		}
		else if (getDirection() == 180) {
			//check two pixels to the left
			if (getWorld()->overlap(getX() - 2, getY(), false)) {
				setDirection(0);
				return;
			}
			else {
				moveTo(targetX2, targetY);
			}
		}
	}
}

bool Mushroom::isDamageable() {
	return false;
}

void Mushroom::attemptToDamage() {

}

void Mushroom::bonk() {

}

bool Mushroom::blocksMovement() {
	return false;
}

Mushroom::~Mushroom() {

}


// STAR
Star::Star(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world) : Actor(imageID, startX, startY, 0, 1, 1, true, world) {

}

void Star::doSomething() {
	// if star overlaps with peach
	if (getWorld()->overlapWithPeach(getX(), getY(), ' ')) {
		getWorld()->increaseScore(100);
		getWorld()->changeInvincibility(150);
		kill();
		getWorld()->playSound(SOUND_PLAYER_POWERUP);
		return;
	}
	else {
		// check two pixels below
		if (!getWorld()->overlap(getX(), getY() - 2, false)) {
			moveTo(getX(), getY() - 2);
		}

		double targetX1 = getX() + 2;
		double targetX2 = getX() - 2;
		double targetY = getY();

		if (getDirection() == 0) {
			// check two pixels to the right
			if (getWorld()->overlap(getX() + 2, getY(), false)) {
				setDirection(180);
				return;
			}
			else {
				moveTo(targetX1, targetY);
			}


		}
		else if (getDirection() == 180) {
			//check two pixels to the left
			if (getWorld()->overlap(getX() - 2, getY(), false)) {
				setDirection(0);
				return;
			}
			else {
				moveTo(targetX2, targetY);
			}
		}
	}
}

bool Star::isDamageable() {
	return false;
}

void Star::attemptToDamage() {

}

void Star::bonk() {

}

bool Star::blocksMovement() {
	return false;
}

Star::~Star() {
	
}


// GOOMBA
Goomba::Goomba(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world) : Actor(imageID, startX, startY, dir, 0, 1, true, world) {
	
}

void Goomba::doSomething() {
	// if goomba is alive
	// 
	
	if (isAlive()) {
		// if goomba overlaps with peach
		if (getWorld()->overlapWithPeach(getX(), getY(), ' ')) {
			getWorld()->peachBonk();
			return;
		}

		// if goomba can move 1 pixel in current direction
		if (getDirection() == 0) {
			if (!getWorld()->overlapGoomba(getX() + 2, getY(), false, 'r')) {

			}
			else {

				setDirection(180);
			}

		}

		else if (getDirection() == 180) {
			if (!getWorld()->overlapGoomba(getX() - 2, getY(), false, 'l')) {


			}
			else {

				setDirection(0);
			}
		}

		// TODO
		// determine if goomba can move 1 pixel in current direction without stepping off platform


		if (getDirection() == 0) {
			if (!getWorld()->overlapGoomba(getX() + 2, getY(), false, 'r')) {
				moveTo(getX() + 1, getY());
			}
			else {

				return;
			}

		}

		else if (getDirection() == 180) {
			if (!getWorld()->overlapGoomba(getX() - 2, getY(), false, 'l')) {
				moveTo(getX() - 1, getY());

			}
			else {

				return;
			}
		}




	}
}

bool Goomba::isDamageable() {
	return true;
}

void Goomba::attemptToDamage() {
	getWorld()->increaseScore(100);
	kill();
}

void Goomba::bonk() {
	// if bonker is peach
	if (getWorld()->overlapWithPeach(getX(), getY(), ' ')) {
		// if peach has star power (invincibility)
		if (getWorld()->checkPower('s')) {
			getWorld()->playSound(SOUND_PLAYER_KICK);
			getWorld()->increaseScore(100);
			kill();
		}
	}

}

bool Goomba::blocksMovement() {
	return false;
}

Goomba::~Goomba() {
	
}



// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


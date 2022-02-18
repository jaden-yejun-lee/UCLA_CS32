#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>


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

Block::Block(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world) : Actor(imageID, startX, startY, 0, 2, 1, true, world) {

}

void Block::doSomething() {

}

bool Block::isDamageable() {
	return false;
}

void Block::attemptToDamage() {

}

void Block::bonk() {

}

bool Block::blocksMovement() {
	return true;
}

Block::~Block() {

}

Peach::Peach(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world) : Actor(imageID, startX, startY, 0, 0, 1, true, world) {
	m_hp = 1;
	m_invincibility = false;
	m_jump_distance = 0;
}

void Peach::doSomething() {

	double curX = getX();
	double curY = getY();



	int ch;

	if (isAlive()) {

		// if peach previously initiated a jump
		if (m_jump_distance > 0) {

			double targetX = getX();
			double targetY = getY() + 4;

			if (getWorld()->overlap(targetX, targetY, 'm')) {
				//bonk
				m_jump_distance = 0;
			}
			else {
				moveTo(targetX, targetY);
				m_jump_distance--;
			}

		}

		// peach is not actively jumping
		else if (m_jump_distance == 0) {
			
			if (!getWorld()->overlap(curX, curY, 'c')) {
				moveTo(getX(), getY() - 4); 
			}
		}

		if (getWorld()->getKey(ch)) {
			switch (ch) {
			case KEY_PRESS_LEFT:
				// move Peach left
				setDirection(180);

				if (getWorld()->overlap(curX, curY, 'l')) {
					
				}
				else {
					moveTo(curX - 4, curY);
				}

				break;

			case KEY_PRESS_RIGHT:
				// move Peach right
				setDirection(0);

				if (getWorld()->overlap(curX, curY, 'r')) {
					
				}

				else {
					moveTo(curX + 4, curY);
				}

				break;

			case KEY_PRESS_UP:
				// make Peach jump

				// if there is an object that would block one pixel below
				if (getWorld()->objectCanBlock()) {
					m_jump_distance = 15;
					getWorld()->playSound(SOUND_PLAYER_JUMP);
					
				}
				break;
			}
		}

	}



}

bool Peach::isDamageable() {
	return true;
}

void Peach::attemptToDamage() {

}

void Peach::bonk() {

}

bool Peach::blocksMovement() {
	return false;
}

Peach::~Peach() {

}



// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

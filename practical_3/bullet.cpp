#include "bullet.h"
#include "game.h"
using namespace sf;
using namespace std;

//Create definition for the constructor
//basic constructor
Bullet::Bullet() {};

//real constructor
Bullet::Bullet(const sf::Vector2f& pos, const bool mode) {
	setPosition(pos);
	_mode = mode;
};


void Bullet::Update(const float& dt) {
	move(Vector2f(0, dt * 200.0f * (_mode ? 1.0f : -1.0f)));
}
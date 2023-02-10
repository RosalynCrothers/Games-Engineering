#include "ship.h"
#include "game.h"
#include <iostream>

using namespace sf;
using namespace std;

const Keyboard::Key controls[2] = {
	Keyboard::A,
	Keyboard::D
};

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
}

void Ship::Update(const float &dt) {

}

Ship::~Ship() = default;

void Ship::MoveDown() { move(Vector2f(0.0f, 0.0f)); };



//invader code
Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(Vector2f(16.f, 16.f));;
	setPosition(pos);
}

void Invader::Update(const float& dt) {
	Ship::Update(dt);

	move(Vector2((direction ? 1.0f : -1.0f) * speed, 0.0f));

	if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 0; i < ships.size(); ++i)
		{
			ships[i]->MoveDown();
		}
	}

	//cerr << "Ships moving!" << std::endl;
}

void Invader::MoveDown() {

	move(Vector2f(0.0f, 24.0f));

}

bool Invader::direction;
float Invader::speed;



Player::Player() : Ship(IntRect(Vector2(160, 32), Vector2(32, 32))) {
	setPosition({ gameWidth * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt) {
	Ship::Update(dt);
	//Move left
	if (Keyboard::isKeyPressed(controls[0]) && getPosition().x > 0)
	{
		move(Vector2f(-0.05f, 0.f));
	}
		//Move Right
	if (Keyboard::isKeyPressed(controls[1]) && getPosition().x < (gameWidth - 32))
	{
		move(Vector2f(0.05f, 0.f));
	}

	//cerr << "ship move" << endl;
}
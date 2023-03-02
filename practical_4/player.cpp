#include "player.h"

using namespace sf;
using namespace std;

void Player::Update(double dt) {
	//inputs

	//keyboard press w
	if (Keyboard::isKeyPressed(Keyboard::W))
		move(Vector2f(0.f, -_speed));
	//keyboard press a
	if (Keyboard::isKeyPressed(Keyboard::A))
		move(Vector2f(-_speed, 0.f));
	//keyboard press s
	if (Keyboard::isKeyPressed(Keyboard::S))
		move(Vector2f(0.f, _speed));
	//keyboard press d
	if (Keyboard::isKeyPressed(Keyboard::D))
		move(Vector2f(_speed, 0.f));
	Entity::Update(dt);
}
Player::Player()
	: _speed(0.2f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
}
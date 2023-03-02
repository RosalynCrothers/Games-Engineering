#include <SFML/Graphics.hpp>
#include "player.h"
#include <memory>
#include <iostream>

using namespace std;
using namespace sf;

unique_ptr<Player> player;

void Load() {
	player = make_unique<Player>();

	player->setPosition(Vector2f(400.f, 400.f));
}

void Update(const double& dt) {
	//for (auto& e : entities) {
	//	e.Update(dt);
	//}

	player->Update(dt);
}

void Render(RenderWindow& window) {
	//for (const auto& e : entities)
	//{
	//	e.Render(window);
	//}

	player->Render(window);
}


int main() {
	sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "SFML works!");
	
	static Clock clock;
	float dt = clock.restart().asSeconds();

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Blue);

	Load();

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		Update(dt);
		Render(window);
		window.display();
	}
	return 0;
}
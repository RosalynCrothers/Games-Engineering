#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"

using namespace sf;
using namespace std;


Texture spritesheet;
Sprite invader;

vector<Ship*> ships;

int invaders_rows = 3;
int invaders_columns = 8;

void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(IntRect(Vector2(0, 0), Vector2(32, 32)));

	Invader::speed = 0.2f;
	Invader::direction = true;

	for (int r = 0; r < invaders_rows; ++r) {
		auto rect = IntRect(Vector2(0, 0), Vector2(32, 32));

		for (int c = 0; c < invaders_columns; ++c) {
			Vector2f position = Vector2f((c * 32.f) + 32.f, (r * 32.f) + 32.f);
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}

	auto player = new Player();
	ships.push_back(player);


	//Invader* inv = new Invader(sf::IntRect(Vector2(0, 0), Vector2(32, 32)), { 100,100 });
	//Invader* inv2 = new Invader(sf::IntRect(Vector2(64, 0), Vector2(32, 32)), { 132,100 });

	//ships.push_back(inv);
	//ships.push_back(inv2);
}

void Render(RenderWindow& window) {
	for (const auto& s : ships)
	{
		window.draw(*s);
	}
}

void Update(const float& dt) {

	for (auto& s : ships) {
		s->Update(dt);
	}
}

int main() {
	sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Galactic Trespassers");
	static Clock clock;
	float dt = clock.restart().asSeconds();
	
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Blue);
	

	Load();

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		//window.clear();
		//window.draw(shape);
		//window.display();
		window.clear();
		Update(dt);
		Render(window);
		window.display();
	}
	return 0;
}
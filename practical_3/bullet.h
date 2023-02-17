
#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {

public:
	Bullet(const sf::Vector2f& pos, const bool mode);
	~Bullet() = default;

	//updates all bullets (by calling _Update() on all bullets in the pool)
	static void Update(const float& dt);

	//Render's all bullets (uses a similar trick to the ship renderer but on the bullet pool)
	static void Render(sf::RenderWindow& window);

	//Chose an inactive bullet and use it.
	static void Fire(const sf::Vector2f& pos, const bool mode);

	//Set all the bullets to -100, -100, set the spritesheet, set origin
	static void Init();

protected:
	//false=player bullet, true=Enemy bullet
	bool _mode;
	static unsigned char bulletPointer;
	static Bullet bullets[256];

	//Called by the static Update()
	void _Update(const float& dt);

	//never called
	Bullet();
};
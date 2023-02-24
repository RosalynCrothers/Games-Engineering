#include "bullet.h"
#include "game.h"
#include "ship.h"
using namespace sf;
using namespace std;




static Bullet* bullets[256];
static unsigned char bulletPointer;

//Create definition for the constructor


//basic constructor
Bullet::Bullet() {};




//real constructor
Bullet::Bullet(const sf::Vector2f& pos, const bool mode) {
	setPosition(pos);
	_mode = mode;
}
void Bullet::Update(const float& dt)
{
    for (int i = 0; i < 256; i++)
    {
        bullets[i]->_Update(dt);
    }
}
void Bullet::Render(sf::RenderWindow& window)
{
    for (int i=0; i<256; i++)
    {
        window.draw(*bullets[i]);
    }
}
void Bullet::Fire(const sf::Vector2f& pos, const bool mode)
{
    return;
}
void Bullet::Init()
{

    for (int i = 0; i < 256; i++)
    {
        bullets[i]->setPosition(sf::Vector2f{ 20.f,20.f });
    }
   
}



void Bullet::_Update(const float& dt) {
    /*if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
        //off screen - do nothing
        return;
    }
    else {
        move(Vector2f(0, dt * 200.0f * (_mode ? 1.0f : -1.0f)));
        const FloatRect boundingBox = getGlobalBounds();

        for (auto s : ships) {
            if (!_mode && dynamic_cast<Player*>(s) != NULL) {
                //player bulelts don't collide with player
                continue;
            }
            if (_mode && s != dynamic_cast<Player*>(s) == NULL) {
                //invader bullets don't collide with other invaders
                continue;
            }
            if (!s->is_exploded() &&
                s->getGlobalBounds().findIntersection(boundingBox)) {
                //Explode the ship
                s->Explode();
                //warp bullet off-screen
                setPosition(Vector2f(-100, -100));
                return;
            }
            
            
        }
    }*/
}

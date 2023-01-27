void Update(double dt) {
	// Update Everything
}
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::W,
	Keyboard::S,
	Keyboard::Up,
	Keyboard::Down
};

const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

CircleShape ball;
RectangleShape paddles[2];

void Load() {

	for (auto& p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}

	ball.setRadius(ballRadius);
	ball.setOrigin(ball.getScale() / 2.0f);

	paddles[0].setPosition(Vector2(10.f + paddleSize.x / 2.0f, gameHeight / 2.f));
	paddles[1].setPosition(Vector2(gameWidth - 10.0f - paddleSize.x / 2.0f, gameHeight / 2.f));

	ball.setPosition(Vector2(gameWidth/2.0f, gameHeight/2.0f));

}

void Update(RenderWindow &window) {
	static Clock clock;
	float dt = clock.restart().asSeconds();

	Event event;
	while (window.pollEvent(event))
	{
		if(event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		direction++;
	}
	paddles[0].move(Vector2(0.f, direction * paddleSpeed * dt));
}

void Render(RenderWindow &window) {
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}

int main() {
	RenderWindow window(VideoMode({ gameWidth, gameHeight }), "Pongchamp");
	Load();

	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}
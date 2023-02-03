
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int screen = 0;

const Keyboard::Key controls[5] = {
	Keyboard::W,
	Keyboard::S,
	Keyboard::Up,
	Keyboard::Down,
	Keyboard::P
};

const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
Vector2f ballVelocity;
bool server = false;
bool changeMode = false;
bool mp = false;

float by;
float old_pos;

Font font;
Text text;
Text player_type;
Text HowToPlay;


int p1_score = 0;
int p2_score = 0;

CircleShape ball;
RectangleShape paddles[2];

void Load() {



	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };

	for (auto& p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}

	ball.setRadius(ballRadius);
	ball.setOrigin(ball.getScale() / 2.0f);

	by = gameHeight / 2.0f;

	paddles[0].setPosition(Vector2(10.f + paddleSize.x / 2.0f, gameHeight / 2.f));
	paddles[1].setPosition(Vector2(gameWidth - 10.0f - paddleSize.x / 2.0f, gameHeight / 2.f));

	ball.setPosition(Vector2(gameWidth/2.0f, gameHeight/2.0f));

	font.loadFromFile("res/fonts/RobotoMono-VariableFont_wght.ttf");
	text.setFont(font);
	text.setCharacterSize(24);


	// Load font-face from res dir
	font.loadFromFile("res/fonts/RobotoMono-VariableFont_wght.ttf");
	// Set text element to use font
	text.setFont(font);
	// set the character size to 24 pixels
	text.setCharacterSize(24);

}

void Reset(bool scorer){


	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };

	paddles[0].setPosition(Vector2(10.f + paddleSize.x / 2.0f, gameHeight / 2.f));
	paddles[1].setPosition(Vector2(gameWidth - 10.0f - paddleSize.x / 2.0f, gameHeight / 2.f));

	ball.setPosition(Vector2(gameWidth / 2.0f, gameHeight / 2.0f));
	
	if (scorer) {
		p1_score++;
	}
	else if (!scorer)
	{
		p2_score++;
	}




	text.setString("Score: " + to_string(p1_score) + " - " + to_string(p2_score));


	text.setPosition({ (gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0 });

	if (changeMode) {
		mp = !mp;
		changeMode = false;
	}

	server = !server;


}

void Title(RenderWindow& window)
{
	static Clock clock;
	float dt = clock.restart().asSeconds();
	Event event;

	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	if (Keyboard::isKeyPressed(controls[4]))
	{
		mp = !mp;
		sleep(seconds(0.1f));
	}

	player_type.setPosition({ (gameWidth / 2.5), 0});
	player_type.setFont(font);
	player_type.setCharacterSize(24);


	HowToPlay.setPosition({ (gameWidth * 0.1f), 100 });
	HowToPlay.setFont(font);
	HowToPlay.setCharacterSize(18);

	HowToPlay.setString("Welcome to Pong! \n\n To control the player 1 (Left) paddle, use W/S \n To control the player 2 paddle (Right) press up/down \n\n to change game mode, press p. \n\n To begin, press space.");


	if (mp) {
		player_type.setString("Multi player");
	}


	else {

		player_type.setString("Single player");
	}



	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		sleep(seconds(1));
		screen = 1;
	}

}

void Update(RenderWindow& window) {
	//declarations
	static Clock clock;
	float dt = clock.restart().asSeconds();
	Event event;
	const float bx = ball.getPosition().x;

	old_pos = by;
	by = ball.getPosition().y;

	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	if (by > gameHeight) {
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(Vector2(0.0f, -10.0f));
	}

	if (by < 0) {
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(Vector2(0.0f, 10.0f));
	}

	if (bx < 0) {
		Reset(0);
	}
	else if (bx > gameWidth) {
		Reset(1);
	}


	int direction = 0;
	if (Keyboard::isKeyPressed(controls[0]) && paddles[0].getPosition().y - (paddleSize.y * 0.5) > 0) {

		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1]) && paddles[0].getPosition().y + (paddleSize.y * 0.5) < gameHeight) {
		direction++;
	}
	paddles[0].move(Vector2(0.f, direction * paddleSpeed * dt));

	int direction2 = 0;
	if (mp) {

		if (Keyboard::isKeyPressed(controls[2]) && paddles[1].getPosition().y - (paddleSize.y * 0.5) > 0) {
			direction2--;
		}
		if (Keyboard::isKeyPressed(controls[3]) && paddles[1].getPosition().y + (paddleSize.y * 0.5) < gameHeight) {
			direction2++;
		}
	}
	else {
		if (by < paddles[1].getPosition().y && paddles[1].getPosition().y - (paddleSize.y * 0.5) > 0)
		{
			direction2--;
		}

		else if (by > paddles[1].getPosition().y && paddles[1].getPosition().y + (paddleSize.y * 0.5) < gameHeight)
		{
			direction2++;
		}
	}


	paddles[1].move(Vector2(0.f, direction2 * paddleSpeed * dt));

	if (
		//ball is inline or behind paddle
		bx < paddleSize.x &&
		//AND ball is below top edge of paddle
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
		) {

		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(Vector2(10.0f, 0.0f));
		switch (direction) {
		case -1:
			ballVelocity.y -= 100.f;
			break;
		case 0:
			break;
		case 1:
			ballVelocity.y += 100.f;
			break;
		}
	}

	if (
		bx > gameWidth - paddleSize.x - 20 &&

		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&

		by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
		) {

		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(Vector2(-10.0f, 0.0f));

		switch (direction2) {
		case -1:
			ballVelocity.y -= 100.f;
			break;
		case 0:
			break;
		case 1:
			ballVelocity.y += 100.f;
			break;
		}
	}
	

	ball.move(ballVelocity * dt);

	if (Keyboard::isKeyPressed(controls[4]))
	{
		changeMode = true;
	}
}

void Render(RenderWindow &window) {

	switch (screen) {

	case 0:
		window.draw(player_type);
		window.draw(HowToPlay);

		break;
	case 1:
		window.draw(paddles[0]);
		window.draw(paddles[1]);
		window.draw(ball);
		window.draw(text);
		break;
	}
}

int main() {
	RenderWindow window(VideoMode({ gameWidth, gameHeight }), "Pong");
	Load();

	while (window.isOpen()) {
		window.clear();
		switch (screen) {

		case 0:

			Title(window);
			break;
		case 1:

			Update(window);
			break;
		}
		Render(window);
		window.display();
	}
	return 0;
}

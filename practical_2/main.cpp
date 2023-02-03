
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

<<<<<<< HEAD
int screen = 0;
=======

>>>>>>> f79e86aa4ae67629051f170bdafe65b49f510469

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

<<<<<<< HEAD
float by;
float old_pos;

Font font;
Text text;
Text player_type;
Text HowToPlay;

=======
Font font;
Text text;
>>>>>>> f79e86aa4ae67629051f170bdafe65b49f510469

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

<<<<<<< HEAD
	font.loadFromFile("res/fonts/RobotoMono-VariableFont_wght.ttf");
	text.setFont(font);
	text.setCharacterSize(24);

	text.setPosition({ (gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0 });


=======
	// Load font-face from res dir
	font.loadFromFile("res/fonts/RobotoMono-VariableFont_wght.ttf");
	// Set text element to use font
	text.setFont(font);
	// set the character size to 24 pixels
	text.setCharacterSize(24);

>>>>>>> f79e86aa4ae67629051f170bdafe65b49f510469
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


<<<<<<< HEAD
=======


	text.setPosition({ (gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0 });

>>>>>>> f79e86aa4ae67629051f170bdafe65b49f510469
	text.setString("Score: " + to_string(p1_score) + " - " + to_string(p2_score));

	if (changeMode) {
		mp = !mp;
		changeMode = false;
	}

	server = !server;

<<<<<<< HEAD
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
		sleep(seconds(0.1));
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

=======
>>>>>>> f79e86aa4ae67629051f170bdafe65b49f510469
}

void Update(RenderWindow &window) {

	//declarations
	static Clock clock;
	float dt = clock.restart().asSeconds();
	Event event;
	const float bx = ball.getPosition().x;
<<<<<<< HEAD
	old_pos = by;
	by = ball.getPosition().y;
=======
	const float by = ball.getPosition().y;
>>>>>>> f79e86aa4ae67629051f170bdafe65b49f510469
	
	while (window.pollEvent(event))
	{
		if(event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	if (by > gameHeight){
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
<<<<<<< HEAD


	int direction = 0;
	if (Keyboard::isKeyPressed(controls[0]) && paddles[0].getPosition().y - (paddleSize.y * 0.5) > 0) {
=======
	else if (
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
	}

	else if (
		bx > gameWidth - paddleSize.x - 20 &&

		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&

		by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
		) {

		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(Vector2(-10.0f, 0.0f));
	}


	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
>>>>>>> f79e86aa4ae67629051f170bdafe65b49f510469
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1]) && paddles[0].getPosition().y + (paddleSize.y * 0.5) < gameHeight) {
		direction++;
	}
	paddles[0].move(Vector2(0.f, direction * paddleSpeed * dt));

<<<<<<< HEAD
	int direction2 = 0;
	if (mp) {

		if (Keyboard::isKeyPressed(controls[2]) && paddles[1].getPosition().y - (paddleSize.y * 0.5) > 0) {
			direction2--;
		}
		if (Keyboard::isKeyPressed(controls[3]) && paddles[1].getPosition().y + (paddleSize.y * 0.5) < gameHeight) {
			direction2++;
=======
	direction = 0.0f;
	if (mp) {

		if (Keyboard::isKeyPressed(controls[2])) {
			direction--;
		}
		if (Keyboard::isKeyPressed(controls[3])) {
			direction++;
>>>>>>> f79e86aa4ae67629051f170bdafe65b49f510469
		}
	}
	else{

<<<<<<< HEAD
		if (by < paddles[1].getPosition().y && paddles[1].getPosition().y - (paddleSize.y * 0.5) > 0)
		{
			direction2--;
		}

		else if (by > paddles[1].getPosition().y && paddles[1].getPosition().y + (paddleSize.y * 0.5) < gameHeight)
		{
			direction2++;
		}
	}

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
				if (old_pos < by) {
					ballVelocity.y += 25.f;
				}

				else if (old_pos > by) {
					ballVelocity.y -= 25.f;
				}

				break;
			case 0:
				break;
			case 1:
				if (old_pos < by) {
					ballVelocity.y -= 25.f;
				}

				else if (old_pos > by) {
					ballVelocity.y += 25.f;
				}
				break;
		}

		/*PSEUDO:
		store previous ball y as float

		check if paddle going up or down

		if going up, check if ball going up or down

		if 
		
		*/
	}

	else if (
		bx > gameWidth - paddleSize.x - 20 &&

		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&

		by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
		) {

		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(Vector2(-10.0f, 0.0f));
	}

	paddles[1].move(Vector2(0.f, direction2 * paddleSpeed * dt));
=======
		if (by < paddles[1].getPosition().y)
		{
			direction--;
		}

		else if (by > paddles[1].getPosition().y)
		{
			direction++;
		}
	}

	paddles[1].move(Vector2(0.f, direction * paddleSpeed * dt));
>>>>>>> f79e86aa4ae67629051f170bdafe65b49f510469

	ball.move(ballVelocity * dt);

	if (Keyboard::isKeyPressed(controls[4]))
	{
		changeMode = true;
	}
}

void Render(RenderWindow &window) {
<<<<<<< HEAD

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
=======
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(text);
>>>>>>> f79e86aa4ae67629051f170bdafe65b49f510469
}

int main() {
	RenderWindow window(VideoMode({ gameWidth, gameHeight }), "Pongchamp");
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
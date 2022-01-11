// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tool.hpp"
#include "Utility.hpp"
//#include "Bullet.hpp"
#include "Entity.hpp"
#include <SFML/Audio.hpp>
#include "Block.hpp"
#include "Particles.hpp"

EntityManager repo;

#pragma region Functions
void drawParticles(sf::RenderWindow& window, sf::CircleShape particles[])
{

	window.draw(particles[1]);
}

#pragma endregion

int main()
{
#pragma region Variables

	//Window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Untitled Space Game");
	window.setVerticalSyncEnabled(true);
	sf::Vector2i windowPosition = window.getPosition();
	sf::View view(sf::Vector2f(1280/2, 720/2), sf::Vector2f(300.f, 200.f));
	view.setCenter(1280 / 2, 720 / 2);
	view.setSize(1280.f, 720.f);

	//Time
	sf::Clock clock;
	float spawnCooldown = 1.5;
	float spawnCooldownTimer;
	float textTimer;
	sf::Time elapsedTime;

	//Block Array
	Block* block[30];


	//Sound
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("WallBounce.wav"))
		return -1;
	sf::Sound bounceSound;
	bounceSound.setBuffer(buffer);

	sf::SoundBuffer buffer2;
	if (!buffer2.loadFromFile("explosion.wav"))
		return -1;
	sf::Sound explodeSound;
	explodeSound.setBuffer(buffer2);

	sf::SoundBuffer buffer3;
	if (!buffer3.loadFromFile("Piou.wav"))
		return -1;
	sf::Sound shootSound;
	shootSound.setBuffer(buffer3);

	//music
	sf::Music music;
	if (!music.openFromFile("Fish_Song.wav"))
		return -1;
	music.play();
	music.setLoop(true);

	//Load Font
	sf::Font font;
	font.loadFromFile("Game Of Squids.ttf");

	//particles

	//Pad
	sf::RectangleShape pad(sf::Vector2f(60, 40));
	pad.setFillColor(sf::Color::Black);
	pad.setOutlineThickness(3);
	pad.setOutlineColor(sf::Color::White);
	sf::Vector2f shapePosition = pad.getPosition();
	pad.setOrigin(580, 280);
	pad.setPosition(580, 630);
	sf::FloatRect playerHitbox = pad.getGlobalBounds();
	bool playerAlive = false;

	//Gun
	sf::RectangleShape gun(sf::Vector2f(70, 20));
	gun.setFillColor(sf::Color::Black);
	gun.setOutlineThickness(3);
	gun.setOutlineColor(sf::Color::White);
	bool canFire = true;

	//origin
	sf::CircleShape originShape(5.f);
	originShape.setFillColor(sf::Color::Blue);
	sf::Vector2f originPosition = pad.getOrigin();
	originShape.setPosition(originPosition);

	//Mouse
	sf::CircleShape mouseShape(5.f);
	mouseShape.setFillColor(sf::Color::White);

	//Bullet
	sf::CircleShape bullet(8.f);
	bullet.setFillColor(sf::Color::Magenta);
	sf::FloatRect bulletHitbox = bullet.getGlobalBounds();

	sf::Vector2f bulletPos;
	int reversedx = 1;
	int reversedy = 1;

	//Background
	sf::Texture texture;
	texture.loadFromFile("Texture.jpg", sf::IntRect(0, 0, 1280, 720));
	texture.setSmooth(true);
	sf::Sprite background;
	background.setTexture(texture);

	//Text
	sf::Text text("0", font);
	text.setPosition(10, 0);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Yellow);
	int score = 0;
	sf::String scoretext;

	//Game Over Text
	sf::Text gameOverText("Untitled Space Game", font);
	gameOverText.setCharacterSize(80);
	gameOverText.setStyle(sf::Text::Bold);
	gameOverText.setFillColor(sf::Color::White);
	sf::FloatRect textRect = gameOverText.getLocalBounds();
	gameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	gameOverText.setPosition(1280/2,200);

	sf::Text restartText("Press R to start", font);
	restartText.setCharacterSize(60);
	restartText.setStyle(sf::Text::Bold);
	restartText.setFillColor(sf::Color::Red);
	sf::FloatRect restartTextRect = restartText.getLocalBounds();
	restartText.setOrigin(restartTextRect.left + restartTextRect.width / 2.0f, restartTextRect.top + restartTextRect.height / 2.0f);
	restartText.setPosition(1280 / 2, 400);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

	bool hasBeenCalled = false;
	bool brickAlternate = false;

	int blockIdx = 0;
	bool aliveBullet = false;

	//test Collision
	float left1 = playerHitbox.left;
	float right1 = playerHitbox.left + playerHitbox.width;

#pragma endregion

	while (window.isOpen())
	{
		double dt = tEnterFrame - tExitFrame;

		//create blocks
		if (hasBeenCalled == false)
		{
			for (int i = 0; i < 3; i++)
			{
				float posY = 100 * i + 60;
				for (int j = 0; j < 14; j++)
				{
					float posX = 90 * j + 60;
					Block* b = new Block(posX, posY);
					block[j + i*14] = b;
				}
			}
			hasBeenCalled = true;
		}

#pragma region Collisions Bricks
		//Check collisions
		bulletHitbox = bullet.getGlobalBounds();
		playerHitbox = pad.getGlobalBounds();

		bool touched = false;
		for (int i = 0; i < 42; i++)
		{
			if (playerAlive)
			block[i]->update(dt,pad.getPosition().x, pad.getPosition().y);

			if (block[i]->alive == true && block[i]->collided(bulletHitbox) && aliveBullet == true)
			{
				explodeSound.play();
				block[i]->killed();
				score += 100;
				char numstr[10];
				//sprintf(numstr, "%i", score);
				scoretext = (to_string(score));
				text.setString(scoretext);
				touched = true;

				canFire = true;
				aliveBullet = false;

			}
			if (block[i]->alive == true && block[i]->collided(playerHitbox) && playerAlive == true)
			{
				explodeSound.play();
				playerAlive = false;
			}
		}
		if (touched)
		{
			reversedy *= -1.1;
		}
#pragma endregion

#pragma region Controls
		//get mouse position
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		mouseShape.setPosition(mousePos.x, mousePos.y);

		sf::Vector2f offset = pad.getPosition();
		offset.x -= mousePos.x;
		offset.y -= mousePos.y;

		auto pos = pad.getPosition();
		if (playerAlive)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pad.getPosition().x > 10)
			{
				pad.move(-5, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pad.getPosition().x < 1270)
			{
				pad.move(5, 0);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pad.getPosition().y > 10)
			{
				pad.move(0, -5);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pad.getPosition().y < 710)
			{
				pad.move(0, 5);
			}
		}
		if (!playerAlive)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				pad.setPosition(580, 630);
				for (int i = 0; i < 42; i++)
				{
					block[i]->alive = false;
				}
				float spawnCooldown = 2.5;
				score = 0;
				scoretext = (to_string(score));
				text.setString(scoretext);
				playerAlive = true;

				//Text
				restartText.setString("Press R to restart");
				restartTextRect = restartText.getLocalBounds();
				restartText.setOrigin(restartTextRect.left + restartTextRect.width / 2.0f, restartTextRect.top + restartTextRect.height / 2.0f);

				gameOverText.setString("Game Over");
				textRect = gameOverText.getLocalBounds();
				gameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

			}
		}

#pragma endregion

#pragma region Shooting

		if (aliveBullet)
		{
			//Move Bullet
			float projRad = 3.14 / 180 * bullet.getRotation();
			float x = 8.0f * cos(projRad);
			float y = 8.0f * sin(projRad);

			if ((bullet.getPosition().y < 0 || bullet.getPosition().y > window.getSize().y))
			{
				//reversedy *= -1.1;
				bounceSound.play();
				aliveBullet = false;
				canFire = true;
			}
			if ((bullet.getPosition().x < 0 || bullet.getPosition().x > window.getSize().x))
			{
				//reversedx *= -1.9;
				bounceSound.play();
				aliveBullet = false;
				canFire = true;
			}

			bullet.move(x * reversedx, y * reversedy);
		}

#pragma endregion
		
#pragma region Spawning


		elapsedTime = clock.getElapsedTime();
		spawnCooldownTimer = elapsedTime.asSeconds();
		textTimer = elapsedTime.asSeconds();

		//printf("%f \n", spawnCooldownTimer);
		if (spawnCooldown <= spawnCooldownTimer && playerAlive)
		{
			clock.restart();
			block[blockIdx]->spawn(rand() % 1200 + 10, 10);
			blockIdx += 1;

			//Cooldown Reducing
			if (spawnCooldown > 0.5)
			spawnCooldown -= 0.05;

			if (blockIdx >= 29)
			{
				blockIdx = 0;
			}
		}


#pragma endregion


		//set Center
		pad.setOrigin(pad.getLocalBounds().width / 2.0f, pad.getLocalBounds().height / 2.0f);

		//rotate Gun
		float angle = atan2(-offset.y, -offset.x) * (360 / (3.14 * 2));
		gun.setRotation(angle);
		gun.setOrigin(0, gun.getLocalBounds().height / 2.0f);
		gun.setPosition(pad.getPosition());

		sf::Event event;
		while (window.pollEvent(event))
		{


			if (event.type == sf::Event::Closed)
			window.close();

			//mouse gun
			if (event.type == sf::Event::MouseButtonPressed && canFire && playerAlive)
			{
				shootSound.play();
				reversedx = 1;
				reversedy = 1;

				bullet.setPosition(gun.getPosition().x, gun.getPosition().y);
				bullet.setRotation(gun.getRotation());
				aliveBullet = true;
				canFire = false;

			}
		}

		window.clear();
		window.draw(background);

		//Menu

		//InGame

		if (aliveBullet)
		{
			window.draw(bullet);
		}


		if (playerAlive)
		{
			window.draw(pad);
			window.draw(gun);
		}

		for (int i = 0; i < 42; i++)
		{
			block[i]->draw(window);
		}

		if (!playerAlive)
		{
			window.draw(gameOverText);
			if (textTimer > 0.4)
			{
				window.draw(restartText);
				if (textTimer > 1.4)
					clock.restart();
			}
		}

		window.draw(text);

		window.display();

	}

	return 0;
}
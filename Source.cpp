#include <SFML/Graphics.hpp>
#include<ctime>
#include<iostream>

const int H = 20; // Высота нашего поля
const int W = 15; // Ширина нашего поля

int pole[H][W] = { 0 };

bool end = false;

int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

struct Points
{
	int x, y;
};

Points a[4], b[4]; // а[4] массивчик для нахождения точек, b[4] вспомогательный массивчик 

bool check()
{
	for (int i = 0; i < 4; i++)
	{
		if (a[i].x < 0 || a[i].x >= W || a[i].y >= H)
		{
			return 0;
		}
		else if (pole[a[i].y][a[i].x])
		{
			if (a[i].y <= 0)
			{
				end = true;
			}
			return 0;
		}
	}
		return 1;
}

bool EndGame()
{
	for (int i = 0; i < W; i++)
	{
		if (pole[1][i] == true)
		{
			return 0;
		}
		return 1;
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Tetris");

	window.setFramerateLimit(10);

	sf::Texture texture;
	texture.loadFromFile("image/tile.png");
	sf::Sprite sprite(texture);

	sf::Texture texture_setka;
	texture_setka.loadFromFile("image/setka.png");
	sf::Sprite sprite_setka(texture_setka);

	srand(time(NULL));

	sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));

	bool rotate = false, begin = true;

	int dx = 0, colorNum = rand() % 6;

	int n = rand() % 6;

	float timer = 0, delay = 0.3;

	sf::Clock clock;

	sprite_setka.move(520, 140);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			rotate = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			dx = -1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			dx = 1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			delay = 0.05;
		}

		for (int i = 0; i < 4; i++)
		{
			b[i] = a[i];
			a[i].x += dx;
		}

		if (check() == false)
		{
			for (int i = 0; i < 4; i++)
			{
				a[i] = b[i];
			}
		}

		if (rotate == true)
		{
			Points t = a[1];
			for (int i = 0; i < 4; i++)
			{
				int x, y;
				x = a[i].y - t.y;
				y = a[i].x - t.x;
				a[i].x = t.x - x;
				a[i].y = t.y + y;
			}

			if (check() == false)
			{
				for (int i = 0; i < 4; i++)
				{
					a[i] = b[i];
				}
			}
		}

		if (timer > delay)
		{
			for (int i = 0; i < 4; i++)
			{
				b[i] = a[i];
				a[i].y += 1;
			}

			if (check() == false)
			{
				for (int i = 0; i < 4; i++)
				{
					if (colorNum == 0)
					{
						pole[b[i].y][b[i].x] = 231; // Уникальный код для нуля из-за поля именно для синего цвета
					}
					else
					{
						pole[b[i].y][b[i].x] = colorNum;
					}
				}
				colorNum = rand() % 6;
				n = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					a[i].x = figures[n][i] % 2 + 6;
					a[i].y = figures[n][i] / 2 - 5;
				}
			}
			timer = 0;
		}

		int k = H - 1;
		for (int i = H - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < W; j++)
			{
				if (pole[i][j])
				{
					count++;
				}
				pole[k][j] = pole[i][j];
			}
			if (count < W)
			{
				k--;
			}
		}

		if (begin == true)
		{
			begin = false;

			n = rand() % 7;

			for (int i = 0; i < 4; i++)
			{
				a[i].x = figures[n][i] % 2 + 6; // С помощью этого цикла переводим координаты в "видимые" нам
				a[i].y = figures[n][i] / 2 - 5;
			}
		}

		dx = 0;
		rotate = false;
		delay = 0.3;
	
		window.clear(sf::Color::White);

		window.draw(sprite_setka);
		

		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if (pole[i][j] == 0)
				{
					continue;
				}
				else if (pole[i][j] == 231)
				{
					sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
				}
				else
				{
					sprite.setTextureRect(sf::IntRect(pole[i][j] * 40, 0, 40, 40));
				}

				sprite.setPosition(j * 40, i * 40);
				sprite.move(520, 140);
				window.draw(sprite);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			sprite.setTextureRect(sf::IntRect(colorNum * 40, 0, 40, 40));

			sprite.setPosition(a[i].x * 40, a[i].y * 40); // А с помощью этого выводим их на экран

			sprite.move(520, 140);

			window.draw(sprite);
		}

		if (EndGame() == false || end == true)
		{
			window.close();
		}

		window.display();
	}

	system("pause");
	return 0;
}
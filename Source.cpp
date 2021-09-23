#include <SFML/Graphics.hpp>
#include<ctime>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Tetris");

	window.setFramerateLimit(10);

	sf::Texture texture;
	texture.loadFromFile("image/tile.png");
	sf::Sprite sprite(texture);

	srand(time(NULL));

	sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));

	const int H = 20; // Высота нашего поля
	const int W = 10; // Ширина нашего поля

	int pole[H][W] = { 0 };

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

	struct Point
	{
		int x, y;
	};

	Point a[4]; // массивчик для нахождения точек

	bool s = true, rotate = false;

	int dx = 0, dy = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

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
			dy = 2;
		}

		for (int i = 0; i < 4; i++)
		{
			a[i].x += dx;
		}

		for (int i = 0; i < 4; i++)
		{
			a[i].y += dy;
		}

		if (rotate == true)
		{
			Point t = a[1];
			for (int i = 0; i < 4; i++)
			{
				int x, y;
				x = a[i].y - t.y;
				y = a[i].x - t.x;
				a[i].x = t.x - x;
				a[i].y = t.y + y;
			}
		}

		int n = 2;

		if (s == true)
		{
			for (int i = 0; i < 4; i++)
			{
				a[i].x = figures[n][i] % 2; // С помощью этого цикла переводим координаты в "видимые" нам
				a[i].y = figures[n][i] / 2;
			}
			s = false;
		}

		dx = 0;
		rotate = false;
		
	
		window.clear();

		for (int i = 0; i < 4; i++)
		{
			sprite.setPosition(a[i].x * 40, a[i].y * 40); // А с помощью этого выводим их на экран

			window.draw(sprite);
		}

		window.display();
	}

	system("pause");
	return 0;
}
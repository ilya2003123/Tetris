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
		else if (a[i].y >= 0 && pole[a[i].y][a[i].x])
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

bool endGame()
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

void menu(sf::RenderWindow& window)
{
	sf::Texture menu1, menu2, menu3;
	menu1.loadFromFile("image/111.png");
	menu2.loadFromFile("image/222.png");
	menu3.loadFromFile("image/333.png");
	sf::Sprite menu1s(menu1), menu2s(menu2), menu3s(menu3);

	bool isMenu = true;
	int menuNum = 0;

	sf::Texture texture_fon;
	texture_fon.loadFromFile("image/fon1.png");
	sf::Sprite sprite_fon(texture_fon);

	menu1s.setPosition(100, 80);
	menu2s.setPosition(100, 200);
	menu3s.setPosition(100, 320);

	while (isMenu == true)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		menu1s.setColor(sf::Color::White);
		menu2s.setColor(sf::Color::White);
		menu3s.setColor(sf::Color::White);
		menuNum = 0;

		if (sf::IntRect(100, 80, 300, 100).contains(sf::Mouse::getPosition(window)))
		{
			menu1s.setColor(sf::Color::Red);
			menuNum = 1;
		}
		else if (sf::IntRect(100, 200, 300, 100).contains(sf::Mouse::getPosition(window)))
		{
			menu2s.setColor(sf::Color::Red);
			menuNum = 2;
		}
		else if (sf::IntRect(100, 320, 300, 100).contains(sf::Mouse::getPosition(window)))
		{
			menu3s.setColor(sf::Color::Red);
			menuNum = 3;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (menuNum == 1)
			{
				isMenu = false;
			}
			if (menuNum == 2)
			{

			}
			if (menuNum == 3)
			{
				window.close();
			}
		}
		

		

		window.draw(sprite_fon);
		window.draw(menu1s);
		window.draw(menu2s);
		window.draw(menu3s);
		window.display();
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Tetris");
	
	window.setFramerateLimit(10);

	menu(window);

	srand(time(NULL));

	sf::Texture texture;
	texture.loadFromFile("image/tile.png");
	sf::Sprite sprite(texture);

	sf::Texture texture_setka;
	texture_setka.loadFromFile("image/setka.png");
	sf::Sprite sprite_setka(texture_setka);

	sf::Texture texture_fon;
	texture_fon.loadFromFile("image/fon1.png");
	sf::Sprite sprite_fon(texture_fon);

	sf::Texture texture_score;
	texture_score.loadFromFile("image/Score.png");
	sf::Sprite sprite_score(texture_score);

	sf::Texture texture_next;
	texture_next.loadFromFile("image/Next.png");
	sf::Sprite sprite_next(texture_next);

	sf::Font font;
	font.loadFromFile("rus.ttf");

	font.loadFromFile("rus.ttf");

	sf::Text txt;
	txt.setFont(font);
	txt.setCharacterSize(62);
	txt.setFillColor(sf::Color::Red);

	bool rotate = false, begin = true;

	int dx = 0, colorNum = rand() % 6, score = 0;

	float timer = 0, delay = 0.3;

	//nt n = rand() % 7;

	//
	//1 2
	//-1 2
	//int k = 0
	//
	int current = 0;
	int rnd[2] = { rand() % 7 , rand() % 7  };

	sf::Clock clock;

	sprite_setka.move(560, 140);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

		end = false;

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
				for (int i = 0; i < 4; i++)
				{
					a[i].x = figures[rnd[current]][i] % 2 + 6;
					a[i].y = figures[rnd[current]][i] / 2 - 5;
				}
				if (current == 0){
						current = 1;
						rnd[0] = rand() % 7;
					}else if(current == 1){
						current = 0;
						rnd[1] = rand() % 7;
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
			if (count == 15)
			{
				score += 50;
			}
			if (count == 30)
			{
				score += 150;
			}
			if (count == 45)
			{
				score += 250;
			}
			if (count == 60)
			{
				score += 400;
			}
		}

		if (begin == true)
		{
			begin = false;

			//n = rand() % 7;

			for (int i = 0; i < 4; i++)
			{
				//a[i].x = figures[n][i] % 2 + 6; // С помощью этого цикла переводим координаты в "видимые" нам
				//a[i].y = figures[n][i] / 2 - 5;
				a[i].x = figures[rnd[current]][i] % 2 + 6;
			    a[i].y = figures[rnd[current]][i] / 2 - 5;
			    
			}
		}

		dx = 0;
		rotate = false;
		delay = 0.3;
	
		window.clear();

		window.draw(sprite_fon);

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
				sprite.move(600, 140);
				window.draw(sprite);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			sprite.setTextureRect(sf::IntRect(colorNum * 40, 0, 40, 40));

			sprite.setPosition(a[i].x * 40, a[i].y * 40); // А с помощью этого выводим их на экран

			sprite.move(600, 140);

			window.draw(sprite);
		}

		if (endGame() == false || end == true)
		{	
			menu(window);

			end = false;

			rotate = false;

			begin = true;

			dx = 0;

			colorNum = rand() % 6;

			//n = rand() % 7;

			score = 0;

			timer = 0, delay = 0.3;

			for (int i = 0; i < 4; i++)
			{
				a[i] = { 0,0 }; // x и y в нули
				b[i] = { 0,0 };
			}

			for (int i = 0; i < H; i++)
			{
				for (int j = 0; j < W; j++)
				{
					pole[i][j] = 0;
				}
			}
		}

		sprite_score.setPosition(1230, 100);

		window.draw(sprite_score);

		txt.setString(std::to_string(score) + " NextFig = " + std::to_string(rnd[(current)?0:1]));
		txt.setPosition(1480, 130);

		sprite_next.setPosition(300, 100);
		window.draw(sprite_next);
		window.draw(txt);

		window.display();
	}

	system("pause");
	return 0;
}
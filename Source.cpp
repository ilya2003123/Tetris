#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>

const int H = 20; // Высота нашего поля
const int W = 15; // Ширина нашего поля

int l = 0, hscore = 0, score = 0;

int volume = 50;

sf::Texture texture_fon;

int pole[H][W] = { 0 };

sf::Music music;
sf::Music music1;
sf::Music sory;

void menu(sf::RenderWindow& window);

bool end = false, gameOver = false, isMenu = true, isoptions = false;

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

Points a[4], b[4], c[4]; // а[4] массивчик для нахождения точек, b[4] вспомогательный массивчик 

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


void options(sf::RenderWindow& window)
{
	sf::Texture texture_exit;
	texture_exit.loadFromFile("image/exit.png");
	sf::Sprite sprite_exit(texture_exit);

	sf::CircleShape triangle(40.f, 3);
	sf::CircleShape triangle1(40.f, 3);

	sf::Font font1;
	font1.loadFromFile("rus.ttf");

	sf::Font font2;
	font2.loadFromFile("rus.ttf");
	
	sf::Font font3;
	font3.loadFromFile("rus.ttf");

	sf::Text txt1;
	txt1.setFont(font1);
	txt1.setCharacterSize(62);
	txt1.setFillColor(sf::Color::Red);

	sf::Text txt2;
	txt2.setFont(font2);
	txt2.setCharacterSize(110);
	txt2.setFillColor(sf::Color::Red);

	sf::Text txt3;
	txt3.setFont(font3);
	txt3.setCharacterSize(110);
	txt3.setFillColor(sf::Color::Red);

	texture_fon.loadFromFile("image/fon1.png");
	sf::Sprite sprite_fon(texture_fon);

	int f = 0;

	while (isoptions == true)
	{
		sprite_exit.setColor(sf::Color::White);

		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::IntRect(728, 377, 50, 50).contains(sf::Mouse::getPosition(window)))
			{
				f = 1;
			}

			if (sf::IntRect(940, 377, 50, 50).contains(sf::Mouse::getPosition(window)))
			{
				f = 2;
			}

			if (sf::IntRect(50, 900, 200, 100).contains(sf::Mouse::getPosition(window)))
			{
				sprite_exit.setColor(sf::Color::Red);

				f = 3;
			}

			if (sf::IntRect(740, 520, 50, 50).contains(sf::Mouse::getPosition(window)))
			{
				f = 4;
			}

			if (sf::IntRect(1000, 520, 50, 50).contains(sf::Mouse::getPosition(window)))
			{
				f = 5;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (f == 1 && l > 0)
				{
					l -= 1;
				}
				if (f == 2 && l < 9)
				{
					l += 1;
				}
				if (f == 3)
				{
					music.setVolume(volume);

					music1.setVolume(volume);

					sory.setVolume(volume);

					isoptions = false;
				}
				if (f == 4 && volume > 0 )
				{
					volume -= 10;
				}
				if (f == 5 && volume < 100)
				{
					volume += 10;
				}
			}
		}
		
		f = 0;

		triangle.setFillColor(sf::Color::Red);
		triangle.setPosition(720, 443);
		triangle.setRotation(270.f);

		triangle1.setFillColor(sf::Color::Red);
		triangle1.setPosition(1000, 363);
		triangle1.setRotation(90.f);

		window.clear();

		window.draw(sprite_fon);

		window.draw(triangle);

		window.draw(triangle1);

		txt1.setString(std::to_string(l));
		txt1.setPosition(840, 365);
		
		window.draw(txt1);

		txt3.setString("Level:");
		txt3.setPosition(400, 322);

		window.draw(txt3);

		txt2.setString("Music:");
		txt2.setPosition(400, 465);

		window.draw(txt2);

		txt1.setString(std::to_string(volume));
		txt1.setPosition(850, 500);

		window.draw(txt1);

		sprite_exit.setPosition(50, 900);

		window.draw(sprite_exit);
		
		triangle.setFillColor(sf::Color::Red);
		triangle.setPosition(730, 585);
		triangle.setRotation(270.f);

		triangle1.setFillColor(sf::Color::Red);
		triangle1.setPosition(1060, 505);
		triangle1.setRotation(90.f);

		window.draw(triangle);

		window.draw(triangle1);
		
		window.display();
	}

}

void menu(sf::RenderWindow& window)
{
	sf::Texture menu1, menu2, menu3;
	menu1.loadFromFile("image/111.png");
	menu2.loadFromFile("image/222.png");
	menu3.loadFromFile("image/exit.png");
	sf::Sprite menu1s(menu1), menu2s(menu2), menu3s(menu3);

	int menuNum = 0;

	sory.stop();

	texture_fon.loadFromFile("image/fon1.png");
	sf::Sprite sprite_fon(texture_fon);

	sf::Texture texture_fon1;
	texture_fon1.loadFromFile("image/fon.png");
	sf::Sprite sprite_fon1(texture_fon1);

	sf::Texture texture_ps;
	texture_ps.loadFromFile("image/ps.png");
	sf::Sprite sprite_ps(texture_ps);

	music.openFromFile("music/menu.wav");
	music.setVolume(volume);
	music.play();

	menu1s.setPosition(100, 80);
	menu2s.setPosition(150, 200);
	menu3s.setPosition(150, 320);

	isMenu = true;

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

		if (sf::IntRect(100, 80, 340, 80).contains(sf::Mouse::getPosition(window)))
		{
			menu1s.setColor(sf::Color::Red);
			menuNum = 1;
		}
		else if (sf::IntRect(150, 220, 240, 60).contains(sf::Mouse::getPosition(window)))
		{
			menu2s.setColor(sf::Color::Red);
			menuNum = 2;
		}
		else if (sf::IntRect(210, 350, 140, 60).contains(sf::Mouse::getPosition(window)))
		{
			menu3s.setColor(sf::Color::Red);
			menuNum = 3;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (menuNum == 1)
			{
				music.stop();

				isMenu = false;
			}
			if (menuNum == 2)
			{
				isoptions = true;

				options(window);
			}
			if (menuNum == 3)
			{
				music.stop();

				music1.stop();
				
				sory.stop();

				if (score > hscore)
				{
					std::ofstream out("Hscore.txt", std::ios::trunc); // окрываем файл для записи
					if (out.is_open())
					{
						out << score; // Записываем в файл high score игрока
					}
					out.close();     // закрываем файл
				}
				
				window.close();

				exit(0);
			}
		}
		
		sprite_fon1.setPosition(1050, 60);

		window.draw(sprite_fon);
		
		window.draw(sprite_fon1);

		sprite_ps.setPosition(50, 500);

		window.draw(sprite_ps);
		
		window.draw(menu1s);
		
		window.draw(menu2s);
		
		window.draw(menu3s);
		
		window.display();
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Tetris", sf::Style::Fullscreen);
	
	window.setFramerateLimit(10);

	menu(window);

	srand(time(NULL));

	sf::Texture texture_k1;
	texture_k1.loadFromFile("image/tile.png");
	sf::Sprite sprite_k1(texture_k1);

	sf::Texture texture_k2;
	texture_k2.loadFromFile("image/tile.png");
	sf::Sprite sprite_k2(texture_k2);

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

	sf::Texture texture_game_over;
	texture_game_over.loadFromFile("image/gameover.png");
	sf::Sprite sprite_gameOver(texture_game_over);

	sory.openFromFile("music/sory.wav");

	music1.openFromFile("music/tetris.wav");

	sf::Font font;
	font.loadFromFile("rus.ttf");
	
	sf::Text txt;
	txt.setFont(font);
	txt.setCharacterSize(62);
	txt.setFillColor(sf::Color::Red);

	bool rotate = false, begin = true, chek = false;

	int dx = 0, colorNum1 = rand() % 6, colorNum2 = rand() % 6;

	double timer = 0, delay = 0.3f / (l + 1);

	int k1 = rand() % 7;

	int k2 = rand() % 7;

	sf::Clock clock;

	sprite_setka.move(560, 140);

	std::ifstream in("Hscore.txt"); // окрываем файл для чтения
	if (in.is_open())
	{
		in >> hscore; // считываем с файла high score
	}
	in.close();     // закрываем файл

	while (window.isOpen())
	{
		window.setFramerateLimit(10 + l * 5);

		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (music1.getStatus() != 2)
		{
			music1.setVolume(volume);
			music1.play();
		}
	

		end = false;

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && gameOver == false)
		{
			rotate = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && gameOver == false)
		{
			dx = -1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && gameOver == false)
		{
			dx = 1;
		}

		delay = 0.3f / (l + 1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && gameOver == false)
		{
			delay = 0.05f / (l + 1);
		}

		for (int i = 0; i < 4 && gameOver == false; i++)
		{
			b[i] = a[i];
			a[i].x += dx;
		}

		if (check() == false && gameOver == false)
		{
			for (int i = 0; i < 4; i++)
			{
				a[i] = b[i];
			}
		}

		if (rotate == true && gameOver == false)
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

			if (check() == false && gameOver == false)
			{
				for (int i = 0; i < 4; i++)
				{
					a[i] = b[i];
				}
			}
		}

		if (timer > delay && gameOver == false)
		{
			for (int i = 0; i < 4; i++)
			{
				b[i] = a[i];
				a[i].y += 1;
			}

			if (check() == false && gameOver == false)
			{
				for (int i = 0; i < 4; i++)
				{
					if (colorNum1 == 0)
					{
						pole[b[i].y][b[i].x] = 231; // Уникальный код для нуля из-за поля, именно для синего цвета
					}
					else
					{
						pole[b[i].y][b[i].x] = colorNum1;
					}
				}
				colorNum1 = colorNum2;
				colorNum2 = rand() % 6;
				k2 = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					a[i].x = c[i].x + 1;
					a[i].y = c[i].y - 6;
				}
				for (int i = 0; i < 4; i++)
				{
					c[i].x = figures[k2][i] % 2 + 5;
					c[i].y = figures[k2][i] / 2 + 1;
				}
			}
			timer = 0;
		}

		int globalcount = 0;
		int k = H - 1;
		for (int i = H - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < W; j++)
			{
				if (pole[i][j] && gameOver == false)
				{
					count++;
				}
				pole[k][j] = pole[i][j];
			}
			if (count < W && gameOver == false)
			{
				k--;
			}
			if (count == 15 && gameOver == false)
			{
				globalcount += count;
			}
		}

		if (globalcount >= 15 && gameOver == false)
		{
			score += 25 + 25 * (globalcount / 15 - 1) * globalcount / 15;
		}
		globalcount = 0;

		if (begin == true && gameOver == false)
		{
			begin = false;

			k1 = rand() % 7;

			k2 = rand() % 7;

			for (int i = 0; i < 4; i++)
			{
				a[i].x = figures[k1][i] % 2 + 6; // С помощью этого цикла переводим координаты в "видимые" нам
				a[i].y = figures[k1][i] / 2 - 5;
			}
			for (int i = 0; i < 4; i++)
			{
				c[i].x = figures[k2][i] % 2 + 5;
				c[i].y = figures[k2][i] / 2 + 1;
			}
		}

		dx = 0;
		rotate = false;
	
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
					sprite_k1.setTextureRect(sf::IntRect(0, 0, 40, 40));
				}
				else
				{
					sprite_k1.setTextureRect(sf::IntRect(pole[i][j] * 40, 0, 40, 40));
				}

				sprite_k1.setPosition(j * 40, i * 40);
				sprite_k1.move(600, 140);
				window.draw(sprite_k1);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			sprite_k1.setTextureRect(sf::IntRect(colorNum1 * 40, 0, 40, 40));

			sprite_k1.setPosition(a[i].x * 40, a[i].y * 40); // А с помощью этого выводим их на экран

			sprite_k1.move(600, 140);

			window.draw(sprite_k1);
		}

		for (int i = 0; i < 4; i++)
		{
			sprite_k2.setTextureRect(sf::IntRect(colorNum2 * 40, 0, 40, 40));

			sprite_k2.setPosition(c[i].x * 40, c[i].y * 40); // А с помощью этого выводим их на экран

			sprite_k2.move(200, 150);

			window.draw(sprite_k2);
		}

		if (endGame() == false || end == true || gameOver == true)
		{
			delay = 0 / (l + 1);

			sprite_gameOver.setPosition(650, 400);

			window.draw(sprite_gameOver);

			gameOver = true;

			music1.stop();

			if(sory.getStatus() != 2)
			{
				sory.setVolume(volume);
				sory.play();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				menu(window);

				gameOver = false;

				end = false;

				rotate = false;

				begin = true;

				dx = 0;

				colorNum1 = rand() % 6;

				k1 = rand() % 7;

				k2 = rand() % 7;

				if (score > hscore)
				{
					hscore = score;
				}
				score = 0;

				timer = 0, delay = 0.3 / (l+1);

				for (int i = 0; i < 4; i++)
				{
					a[i] = { 0,0 }; // x и y в нули
					b[i] = { 0,0 };
					c[i] = { 0,0 };
				}

				for (int i = 0; i < H; i++)
				{
					for (int j = 0; j < W; j++)
					{
						pole[i][j] = 0;
					}
				}
			}
		}

		sprite_score.setPosition(1230, 100);

		window.draw(sprite_score);

		txt.setString(std::to_string(score));
		txt.setPosition(1480, 130);

		window.draw(txt);

		txt.setString("\nHigh score:" + std::to_string(hscore));
		txt.setPosition(1270, 130);

		sprite_next.setPosition(300, 80);

		window.draw(sprite_next);
		
		window.draw(txt);

		window.display();
	}

	return 0;
}
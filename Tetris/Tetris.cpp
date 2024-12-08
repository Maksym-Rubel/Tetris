#include "Tetris.h"

bool Tetris::checkboundx()
{
	for (int i = 0; i < 4; i++)
	{
		if (a[i].x < 0 || a[i].x >= N)
		{
			return 0;
		}
		else if (field[a[i].y][a[i].x]) return 0;
	}
	return 1;
}

bool Tetris::checkboundy()
{
	
	for (int i = 0; i < 4; i++)
	{
		if (a[i].y >= M)
		{
			return 0;
			
		}
		else if (field[a[i].y][a[i].x]) return 0;
	}
	return 1;
	
	
}

void Tetris::draw()
{
	
	window.clear(Color::Black);

	
	for (int k = 0; k < 4; k++)
	{
		
		sprite.setPosition(a[k].x * 36, a[k].y * 36);
		window.draw(sprite);
		
	}
	
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (field[i][j] == 0) continue;
			sprite.setPosition(j * 36, i * 36);
			window.draw(sprite);
		}
	}



		

	window.display();
}
void Tetris::generate()
{
	
	srand(time(0));


	
	int n = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
	}
	

}
void Tetris::move()
{
	for (int i = 0; i < 4; i++)
	{
		b[i] = a[i];
		a[i].x += dx;
	}
	if (!this->checkboundx()) {
		for (int i = 0; i < 4; i++)
			a[i] = b[i];
	}
	dx = 0;
	
}

void Tetris::fall()
{
	float time = clock.getElapsedTime().asSeconds();
	
	
	if (time > 0.3)  
	{
	
		clock.restart();
		dy = 1;  
	}
	for (int i = 0; i < 4; i++)
	{
		b[i] = a[i];
		a[i].y += dy;
	}

	if (!this->checkboundy()) {

		for (int i = 0; i < 4; i++)
		{
			a[i] = b[i];

		}
		
		for (int i = 0; i < 4; i++) {
			field[a[i].y][a[i].x] = 1;
		}
	
		int n = rand() % 7;
		for (int i = 0; i < 4; i++)
		{
			a[i].x = figures[n][i] % 2;
			a[i].y = figures[n][i] / 2;
		}
		generate();
	}
	dy = 0;
}

void Tetris::fullline()
{
	int k = M - 1;
	for (int i = M - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < N; j++)
		{
			if (field[i][j]) count++;
			field[k][j] = field[i][j];
			 if (count == N)
				{
					counttetris += 1;
				}

		}
		
		if (count < N)
		{
			k--;
			
		}
		
	}
	
}

void Tetris::Gameover()
{
	
		
	bool isFin = false;
		for (int j = 0; j < N; j++)
		{
			if (field[1][j])
			{
				window.close();
				cout << "Game over: You noob" << endl;
				cout << "Your count --> " << counttetris << endl;
				cout << "Your Record --> " << readFromFileArray("Record.txt") << endl;
				return;
			}
		}
	
}


void Tetris::writeToFileArray(const string& pathFile)
{
	ofstream file;
	file.open(pathFile);
	if (!file.good())
	{
		cout << "Error. File not open" << endl;
		return;
	}
	if(countrecord < counttetris)
		file << counttetris << "\n";
	
}

int Tetris::readFromFileArray(const string& pathFile)
{
	fstream file(pathFile, ios_base::in);
	if (!file.is_open())
	{
		return 0;
	}
	int value;
	while (file >> value)
	{
		return value;
	}
}

void Tetris::game()
{
	for (int i = 0; i < 4; i++)
	{
		a[i].x = 0;
		a[i].y = 0;
	}
	generate();
	while (window.isOpen())
	{
		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
				
			if (event.type == Event::KeyPressed)
			{
				
				if (event.key.code == Keyboard::Left)
				{
					dx = -1;
					

				}
				else if (event.key.code == Keyboard::Right)
				{
					dx = 1;
				
					
				}
				else if (event.key.code == Keyboard::Down)
				{
					dy = 1;


				}
				
				
			}
		}
		Gameover();
		move();
		fall();
		draw();
		fullline();
		if (countrecord < counttetris)
		{
			writeToFileArray("Record.txt");
		}
		srand(time(0));
	


		
		
	}
}

Tetris::Tetris()
	:window(VideoMode(360, 720), "Tetris Game")
{
	if (!texture.loadFromFile("C:\\Users\\Maksym\\source\\repos\\Tetris\\x64\\Debug\\TerrisTexture.png"))
	{
		cout << "Pominyate shlah na sviy" << endl;
	}



	sprite.setTexture(texture);

	sprite.setTextureRect(IntRect(0, 0, 36, 36));
	
	currentFigure = 0;  
	generate();
	

}



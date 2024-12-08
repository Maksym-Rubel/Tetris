#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;
using namespace sf;
class Tetris
{
private:
	RenderWindow window;
	Texture texture;

	Sprite sprite;
	


	const int M = 20;
	const int N = 10; 
	int field[20][10] = { 0 };
	int figures[7][4] =
	{
		1,3,5,7,
		2,4,5,7,
		3,5,4,6,
		3,5,4,7,
		2,3,5,7,
		3,5,7,6,
		2,3,4,5,
	};
	struct Point
	{
		int x, y;
	} a[4], b[4];
	

	
	int dx = 0;
	int dy = 0;
	int colornum = 1;

	int counttetris = 0;
	int countrecord = readFromFileArray("Record.txt");
	int currentFigure = 3;
	Clock clock;


	bool checkboundx();
	bool checkboundy();

	void draw();
	void generate();
	void move();
	void rotate();
	void fall();
	void fullline();
	void Gameover();


	void writeToFileArray(const string& pathFile);
	int readFromFileArray(const string& pathFile);

public:
	Tetris();
	void game();
	
};


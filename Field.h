#pragma once
#include "Block.h"
#include <functional>

enum GameStatus {Continue, Win, Loose};

class Field
{
	private:
		Block field[4][4];
		Block prevField[4][4];
		void createRandomBlocks();
		bool isPrevAndCurrFieldsSame();
		int getScore();
	public:
		Block* getFieldStatus();
		void onLeft();
		void onRight();
		void onUp();
		void onDown();
		Field();
		void loadLastField(int* lastValues);
		int isGameEnd();
		~Field();
};


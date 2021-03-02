#pragma once
#include <string>
#include <vector>

struct Player {
	std::string name;
	int currentScore = 0;
};

class ScoreTable
{
	private:
		ScoreTable();
		static ScoreTable* table;
	public:
		Player user;
		static ScoreTable* Initilize();
		void saveResults();
		void saveLastField(int*);
		bool isLastGameExists();
		int* loadLastGame();
		std::vector<std::string> getScoreTable();
};
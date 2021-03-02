#pragma once
#include "View.h"
#include "Field.h"
#include "ScoreTable.h"

class Application
{
	private:
		View* userInterface;
		Field* field;
		ScoreTable* scoreTable;
		Application();
		static Application* application;
	public:
		static Application* Initilize();
		void start();
		int* getFieldValues();
		Player getPlayer();
		void onQuit();
		void onShowScoreTable();
		~Application();
};
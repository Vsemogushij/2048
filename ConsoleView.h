#pragma once
#include "View.h"
#include <string>
#include <vector>
class ConsoleView : public View
{
	public:
		ConsoleView(std::function<void()> onLeft, std::function<void()> onRight, std::function<void()> onUp, std::function<void()> onDown)
			: View(onLeft, onRight, onUp, onDown) {}
		void show();
		void onUpdate();
		void showWin();
		void showLoose();
		void showScoreTable(std::vector<std::string> records);
		std::string getUsername();
		bool loadLastGame();
};


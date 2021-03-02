#pragma once
#include <functional>
#include <string>
#include <vector>

class View
{
	protected:
		std::function<void()> onLeft;
		std::function<void()> onRight;
		std::function<void()> onUp;
		std::function<void()> onDown;
	public:
		View(std::function<void()> onLeft, std::function<void()> onRight, std::function<void()> onUp, std::function<void()> onDown);
		virtual void show() = 0;
		virtual void onUpdate() = 0;
		virtual void showWin() = 0;
		virtual void showLoose() = 0;
		virtual std::string getUsername() = 0;
		virtual void showScoreTable(std::vector<std::string> records) = 0;
		virtual bool loadLastGame() = 0;
};


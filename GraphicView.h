#pragma once
#include "View.h"
#include <SFML/Graphics.hpp>
#include <vector>

class GraphicView : public View
{
	private:
		sf::RenderWindow* window;
		std::vector<sf::Shape*> shapes;
		void createShapes();
		void redrawBlocks();
	public:
		GraphicView(std::function<void()> onLeft, std::function<void()> onRight, std::function<void()> onUp, std::function<void()> onDown)
			: View(onLeft, onRight, onUp, onDown) {}
		void show();
		void onUpdate();
		void showWin();
		void showLoose();
		void showScoreTable(std::vector<std::string> records);
		std::string getUsername();
		bool loadLastGame();
		~GraphicView();
};
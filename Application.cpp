#include "Application.h"
//For console UI
#include "ConsoleView.h"
//For GUI
#include "GraphicView.h"

Application* Application::application = nullptr;

Application::Application()
{
	field = new Field();
	std::function<void()> onLeft = std::bind(&Field::onLeft, field);
	std::function<void()> onRight = std::bind(&Field::onRight, field);
	std::function<void()> onUp = std::bind(&Field::onUp, field);
	std::function<void()> onDown = std::bind(&Field::onDown, field);
	//userInterface = new ConsoleView(onLeft, onRight, onUp, onDown);
	userInterface = new GraphicView(onLeft, onRight, onUp, onDown);
	scoreTable = ScoreTable::Initilize();
}

Application* Application::Initilize()
{
	if (application == nullptr) {
		application = new Application();
	}
	return application;
}

void Application::start()
{
	userInterface->show();
	scoreTable->user.name = userInterface->getUsername();
	if (scoreTable->user.name == "") {
		scoreTable->user.name = "NONAME";
	}

	if (scoreTable->isLastGameExists())
		if (userInterface->loadLastGame())
			field->loadLastField(scoreTable->loadLastGame()); 
	
	while (field->isGameEnd() == Continue) {
		userInterface->onUpdate();
	}
	if (field->isGameEnd() == Win)
		userInterface->showWin();
	else
		userInterface->showLoose();
}

int* Application::getFieldValues()
{
	int* values = new int[16];
	Block* blocks = field->getFieldStatus();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			*(values + i + j * 4) = (blocks + i + j * 4)->value;
	return values;
}

Player Application::getPlayer()
{
	return ScoreTable::Initilize()->user;
}

Application::~Application()
{
	delete userInterface;
	delete scoreTable;
	delete field;
}

void Application::onQuit()
{
	scoreTable->saveResults();
	scoreTable->saveLastField(getFieldValues());
	exit(0);
}

void Application::onShowScoreTable()
{
	userInterface->showScoreTable(scoreTable->getScoreTable());
}

#include "View.h"

View::View(std::function<void()> onLeft, std::function<void()> onRight, std::function<void()> onUp, std::function<void()> onDown)
{
	this->onLeft = onLeft;
	this->onRight = onRight;
	this->onDown = onDown;
	this->onUp = onUp;
}


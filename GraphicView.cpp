#include "GraphicView.h"
#include "Application.h"
#include "DimensionsOfGUI.h"
#include <codecvt>
 
void GraphicView::createShapes()
{
    //background
    sf::RectangleShape* background = new sf::RectangleShape();
    background->setFillColor(sf::Color(backgroundColor));
    background->setPosition(sf::Vector2f(0, 0));
    background->setSize(sf::Vector2f(width, height));
    shapes.push_back(background);
    //field
    sf::RectangleShape* field = new sf::RectangleShape();
    field->setFillColor(sf::Color(fieldColor));
    field->setPosition(sf::Vector2f(23, 230));
    field->setSize(sf::Vector2f(260, 260));
    field->setOutlineThickness(1);
    field->setOutlineColor(sf::Color(0, 0, 0));
    shapes.push_back(field);
    //empty blocks
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            sf::RectangleShape* emptyBlock = new sf::RectangleShape();
            emptyBlock->setFillColor(sf::Color(emptyBlockColor));
            emptyBlock->setPosition(sf::Vector2f(35 + 62 * i, 242 + 62 * j));
            emptyBlock->setSize(sf::Vector2f(50, 50));
            emptyBlock->setOutlineThickness(1);
            emptyBlock->setOutlineColor(sf::Color(0, 0, 0));
            shapes.push_back(emptyBlock);
        }
}

void GraphicView::redrawBlocks()
{
    int* blocks = Application::Initilize()->getFieldValues();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            sf::Color color;
            switch (*(blocks + i + j * 4))
            {
                case 0:
                    color = sf::Color(emptyBlockColor);
                    break;
                case 2:
                    color = sf::Color(color2);
                    break;
                case 4:
                    color = sf::Color(color4);
                    break;
                case 8:
                    color = sf::Color(color8);
                    break;
                case 16:
                    color = sf::Color(color16);
                    break;
                case 32:
                    color = sf::Color(color32);
                    break;
                case 64:
                    color = sf::Color(color64);
                    break;
                case 128:
                    color = sf::Color(color128);
                    break;
                case 256:
                    color = sf::Color(color256);
                    break;
                case 512:
                    color = sf::Color(color512);
                    break;
                case 1024:
                    color = sf::Color(color1024);
                    break;
                case 2048:
                    color = sf::Color(color2048);
                    break;
            default:
                break;
            }
            shapes[2 + i + j * 4]->setFillColor(color);
        }

    delete blocks;
}

void GraphicView::show()
{
    window = new sf::RenderWindow(sf::VideoMode(width, height), "2048", sf::Style::Close);
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);

    createShapes();
}

void GraphicView::onUpdate()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            window->close();
            Application::Initilize()->onQuit();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                onUp();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                onDown();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                onRight();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                onLeft();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
                Application::Initilize()->onShowScoreTable();
        }
        
    }
    window->clear();
    redrawBlocks();
    for (int i = 0; i < shapes.size(); i++)
        window->draw(*shapes[i]);
    //font for text
    sf::Font font;
    font.loadFromFile("OpenSans-Light.ttf");
    //username
    sf::Text username;
    sf::String buff;
    buff += L"Игрок: ";
    std::string str = Application::Initilize()->getPlayer().name;
    
    std::wstring wstr(str.begin(), str.end());
    buff += wstr;

    username.setString(buff);
    username.setCharacterSize(16);
    username.setFillColor(sf::Color(0, 0, 0));
    username.setFont(font);
    username.setPosition(sf::Vector2f(25, 35+25));
    window->draw(username);
    
    sf::Text score;
    buff.clear();
    buff += L"Текущий рекорд: ";
    buff += std::to_string(Application::Initilize()->getPlayer().currentScore).c_str();
    score.setString(buff);
    score.setCharacterSize(16);
    score.setFillColor(sf::Color(0, 0, 0));
    score.setFont(font);
    score.setPosition(sf::Vector2f(25, 35 + 10 + 16 + 25));
    window->draw(score);

    sf::Text value;
    value.setCharacterSize(16);
    value.setFillColor(sf::Color(0, 0, 0));
    value.setFont(font);
    int* field = Application::Initilize()->getFieldValues();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (*(field + i + j * 4) != 0) {
                std::string num = std::to_string(*(field + i + j * 4));
                value.setString(num);
                value.setPosition(sf::Vector2f(35 + 62 * j + 8 * (6-num.length()) / 2, 242 + 62 * i + 17));
                window->draw(value);
            }
    delete field;
    window->display();
}

void GraphicView::showWin()
{
    sf::Font font;
    bool f = font.loadFromFile("OpenSans-Light.ttf");

    sf::RenderWindow questionWindow(sf::VideoMode(width, height / 3), L"Конец игры");
    sf::RectangleShape* buttonYes = new sf::RectangleShape();
    
    buttonYes->setFillColor(sf::Color(fieldColor));  
    buttonYes->setOutlineThickness(1);               
    buttonYes->setOutlineColor(sf::Color(0, 0, 0));  
    buttonYes->setPosition(sf::Vector2f(15, height / 3 - 15 - 50)); 
    buttonYes->setSize(sf::Vector2f(75, 50));

    sf::RectangleShape* background = new sf::RectangleShape();
    background->setFillColor(sf::Color(backgroundColor));
    background->setPosition(sf::Vector2f(0, 0));
    background->setSize(sf::Vector2f(width, height / 3));

    while (questionWindow.isOpen()) {
        sf::Event event;
        while (questionWindow.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                delete background;
                delete buttonYes;
                questionWindow.close();
                Application::Initilize()->onQuit();
                return;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    if (sf::Mouse::getPosition(questionWindow).x >= 15 && sf::Mouse::getPosition(questionWindow).x <= 90
                        && sf::Mouse::getPosition(questionWindow).y >= height / 3 - 15 - 50 && sf::Mouse::getPosition(questionWindow).y <= height / 3 - 15) {
                        delete background;
                        delete buttonYes;
                        questionWindow.close();
                        Application::Initilize()->onQuit();
                        return;
                    }
                }
            }
        }
        questionWindow.clear();
        questionWindow.draw(*background);
        questionWindow.draw(*buttonYes);
        sf::Text text;
        text.setString(L"ВЫ ПОБЕДИЛИ, ПОЗДРАВЛЯЕМ!!!");
        text.setFont(font);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color(0, 0, 0));
        text.setPosition(sf::Vector2f(7, height / 12));
        questionWindow.draw(text);
        text.setCharacterSize(20);
        text.setString(L"Ок");
        text.setPosition(sf::Vector2f(15 + 25, height / 3 - 15 - 40));
        questionWindow.draw(text);
        questionWindow.display();
    }
}

void GraphicView::showLoose()
{
    sf::Font font;
    bool f = font.loadFromFile("OpenSans-Light.ttf");

    sf::RenderWindow questionWindow(sf::VideoMode(width, height / 3), L"Конец игры");
    sf::RectangleShape* buttonYes = new sf::RectangleShape();

    buttonYes->setFillColor(sf::Color(fieldColor));
    buttonYes->setOutlineThickness(1);
    buttonYes->setOutlineColor(sf::Color(0, 0, 0));
    buttonYes->setPosition(sf::Vector2f(15, height / 3 - 15 - 50));
    buttonYes->setSize(sf::Vector2f(75, 50));

    sf::RectangleShape* background = new sf::RectangleShape();
    background->setFillColor(sf::Color(backgroundColor));
    background->setPosition(sf::Vector2f(0, 0));
    background->setSize(sf::Vector2f(width, height / 3));

    while (questionWindow.isOpen()) {
        sf::Event event;
        while (questionWindow.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                delete background;
                delete buttonYes;
                questionWindow.close();
                Application::Initilize()->onQuit();
                return;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    if (sf::Mouse::getPosition(questionWindow).x >= 15 && sf::Mouse::getPosition(questionWindow).x <= 90
                        && sf::Mouse::getPosition(questionWindow).y >= height / 3 - 15 - 50 && sf::Mouse::getPosition(questionWindow).y <= height / 3 - 15) {
                        delete background;
                        delete buttonYes;
                        questionWindow.close();
                        Application::Initilize()->onQuit();
                        return;
                    }
                   
                }
            }
        }
        questionWindow.clear();
        questionWindow.draw(*background);
        questionWindow.draw(*buttonYes);
        sf::Text text;
        text.setString(L"ВЫ ПРОИГРАЛИ, ПОВЕЗЕТ В ДРУГОЙ РАЗ.");
        text.setFont(font);
        text.setCharacterSize(15);
        text.setFillColor(sf::Color(0, 0, 0));
        text.setPosition(sf::Vector2f(7, height / 12));
        questionWindow.draw(text);
        text.setCharacterSize(20);
        text.setString(L"Ок");
        text.setPosition(sf::Vector2f(15 + 25, height / 3 - 15 - 40));
        questionWindow.draw(text);
        questionWindow.display();
    }
}

void GraphicView::showScoreTable(std::vector<std::string> records)
{
    sf::RectangleShape* background = new sf::RectangleShape();
    sf::RenderWindow scoreTable(sf::VideoMode(width, height), L"Таблица рекордов", sf::Style::Close);
    sf::Event event;
    while (scoreTable.isOpen()) {
        while (scoreTable.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                scoreTable.close();
                delete background;
                return;
            }
        }
        scoreTable.clear();

        sf::Text text;
        sf::Font font;
        font.loadFromFile("OpenSans-Light.ttf");
        text.setCharacterSize(16);
        text.setFillColor(sf::Color(0, 0, 0));
        text.setFont(font);
        text.setPosition(sf::Vector2f(width / 2 - 70, 20));
        text.setString(L"Таблица рекордов");

        
        background->setFillColor(sf::Color(backgroundColor));
        background->setPosition(sf::Vector2f(0, 0));
        background->setSize(sf::Vector2f(width, height));

        scoreTable.draw(*background);
        scoreTable.draw(text);
        
        text.setPosition(sf::Vector2f(5, 40));
        sf::String table;
        for (int i = 0; i < records.size(); i++)
        {
            table += std::to_string(i + 1) + ". " + records[i] + "\n";
        }
        text.setString(table);
        scoreTable.draw(text);
        scoreTable.display();
    }
}

std::string GraphicView::getUsername()
{
    sf::String buff;
    sf::String name;
    buff += L"Введите имя пользователя: ";
    sf::Font font;
    bool f = font.loadFromFile("OpenSans-Light.ttf");

    sf::RenderWindow questionWindow(sf::VideoMode(width, height / 3), L"Имя пользователя");
    sf::RectangleShape* buttonYes = new sf::RectangleShape();

    buttonYes->setFillColor(sf::Color(fieldColor));
    buttonYes->setOutlineThickness(1);
    buttonYes->setOutlineColor(sf::Color(0, 0, 0));
    buttonYes->setPosition(sf::Vector2f(15, height / 3 - 15 - 50));
    buttonYes->setSize(sf::Vector2f(75, 50));

    sf::RectangleShape* background = new sf::RectangleShape();
    background->setFillColor(sf::Color(backgroundColor));
    background->setPosition(sf::Vector2f(0, 0));
    background->setSize(sf::Vector2f(width, height / 3));

    while (questionWindow.isOpen()) {
        sf::Event event;
        while (questionWindow.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                delete background;
                delete buttonYes;
                questionWindow.close();

                return name.toAnsiString(std::locale("Russian"));
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    if (sf::Mouse::getPosition(questionWindow).x >= 15 && sf::Mouse::getPosition(questionWindow).x <= 90
                        && sf::Mouse::getPosition(questionWindow).y >= height / 3 - 15 - 50 && sf::Mouse::getPosition(questionWindow).y <= height / 3 - 15) {
                        delete background;
                        delete buttonYes;
                        questionWindow.close();
                        
                        return name.toAnsiString(std::locale("Russian"));
                    }
                }
            }
            if (event.type == sf::Event::TextEntered) {
                buff += (wchar_t)event.text.unicode;
                name += (wchar_t)event.text.unicode;
            }
        }
        questionWindow.clear();
        questionWindow.draw(*background);
        questionWindow.draw(*buttonYes);
        sf::Text text;
        //buff += (const wchar_t*)username.c_str();
        text.setString(buff);
        text.setFont(font);
        text.setCharacterSize(15);
        text.setFillColor(sf::Color(0, 0, 0));
        text.setPosition(sf::Vector2f(7, height / 12));
        questionWindow.draw(text);
        text.setCharacterSize(20);
        text.setString(L"Ок");
        text.setPosition(sf::Vector2f(15 + 25, height / 3 - 15 - 40));
        questionWindow.draw(text);
        questionWindow.display();
    }
    return buff;
}

bool GraphicView::loadLastGame()
{
    sf::Font font;
    bool f = font.loadFromFile("OpenSans-Light.ttf");

    sf::RenderWindow questionWindow(sf::VideoMode(width, height / 3), L"Загрузка");
    sf::RectangleShape* buttonYes = new sf::RectangleShape();
    sf::RectangleShape* buttonNo = new sf::RectangleShape();
    buttonYes->setFillColor(sf::Color(fieldColor));   buttonNo->setFillColor(sf::Color(fieldColor));
    buttonYes->setOutlineThickness(1);                buttonNo->setOutlineThickness(1);
    buttonYes->setOutlineColor(sf::Color(0, 0, 0));   buttonNo->setOutlineColor(sf::Color(0, 0, 0));
    buttonYes->setPosition(sf::Vector2f(15, height / 3 - 15 - 50)); buttonNo->setPosition(sf::Vector2f(width - 15 - 75, height / 3 - 15 - 50));
    buttonYes->setSize(sf::Vector2f(75, 50)); buttonNo->setSize(sf::Vector2f(75, 50));

    sf::RectangleShape* background = new sf::RectangleShape();
    background->setFillColor(sf::Color(backgroundColor));
    background->setPosition(sf::Vector2f(0, 0));
    background->setSize(sf::Vector2f(width, height / 3));

    while (questionWindow.isOpen()) {
        sf::Event event;
        while (questionWindow.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                delete background;
                delete buttonYes;
                delete buttonNo;
                questionWindow.close();
                window->setActive(true);
                return false;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    if (sf::Mouse::getPosition(questionWindow).x >= 15 && sf::Mouse::getPosition(questionWindow).x <= 90
                        && sf::Mouse::getPosition(questionWindow).y >= height / 3 - 15 - 50 && sf::Mouse::getPosition(questionWindow).y <= height / 3 - 15) {
                        delete background;
                        delete buttonYes;
                        delete buttonNo;
                        questionWindow.close();
                        window->setActive(true);
                        return true;
                    }
                    if (sf::Mouse::getPosition(questionWindow).x >= width - 15 - 75 && sf::Mouse::getPosition(questionWindow).x <= width - 15 - 25
                        && sf::Mouse::getPosition(questionWindow).y >= height / 3 - 15 - 50 && sf::Mouse::getPosition(questionWindow).y <= height / 3 - 15) {
                        delete background;
                        delete buttonYes;
                        delete buttonNo;
                        questionWindow.close();
                        window->setActive(true);
                        return false;
                    }
                }
            }
        }
        questionWindow.clear();
        questionWindow.draw(*background);
        questionWindow.draw(*buttonYes);
        questionWindow.draw(*buttonNo);
        sf::Text text;
        text.setString(L"  Вы хотите продолжить игру ?");
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color(0, 0, 0));
        text.setPosition(sf::Vector2f(7, height / 12));
        questionWindow.draw(text);
        text.setString(L"Да");
        text.setPosition(sf::Vector2f(15 + 25, height / 3 - 15 - 40));
        questionWindow.draw(text);
        text.setString(L"Нет");
        text.setPosition(sf::Vector2f(width - 67, height / 3 - 15 - 40));
        questionWindow.draw(text);
        questionWindow.display();
    }
}

GraphicView::~GraphicView()
{
    for (int i = 0; i < shapes.size(); i++)
        delete shapes[i];
}

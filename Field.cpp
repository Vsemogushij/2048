#include "Field.h"
#include <random>
#include <time.h>
#include "ScoreTable.h"

Block* Field::getFieldStatus()
{
	return (Block*)field;
}

void Field::createRandomBlocks()
{
    Block* randomer[16];
    int x[16], y[16];
    int n = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (field[i][j].value == 0) {
                randomer[n] = &(field[i][j]);
                x[n] = i;
                y[n] = j;
                n++;
            }
    srand(time(0));
    if (n != 0) {
        int l = rand() % n;
        (randomer[l])->value = 4 - (rand() % 2) * 2;
    }
}

bool Field::isPrevAndCurrFieldsSame()
{
    bool isSame = true;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (prevField[i][j].value != field[i][j].value) {
                isSame = false;
                break;
            }
    return isSame;
}

int Field::getScore()
{
    int sum = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            sum += field[i][j].value;
    return sum;
}

void Field::onUp() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (field[i][j].value != 0) {
                int x = j;
                for (int l = j - 1; l >= 0; l--) {
                    if (field[i][l].value == 0) {
                        field[i][l].value = field[i][x].value;
                        field[i][x].value = 0;
                        x = l;
                        continue;
                    }
                    if (field[i][l].value == field[i][x].value) {
                        field[i][l].value *= 2;
                        field[i][x].value = 0;
                        break;
                    }
                    if (field[i][l].value != 0) {
                        break;
                    }
                }
            }
    
}

void Field::onDown()
{
    for (int i = 3; i >= 0; i--)
        for (int j = 3; j >= 0; j--)
            if (field[i][j].value != 0) {
                int x = j;
                for (int l = j + 1; l < 4; l++) {
                    if (field[i][l].value == 0) {
                        field[i][l].value = field[i][x].value;
                        field[i][x].value = 0;
                        x = l;
                        continue;
                    }
                    if (field[i][l].value == field[i][x].value) {
                        field[i][l].value *= 2;
                        field[i][x].value = 0;
                        break;
                    }
                    if (field[i][l].value != 0) {
                        break;
                    }
                }
            }
}

void Field::onLeft()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (field[i][j].value != 0) {
                int x = i;
                for (int l = i - 1; l >= 0; l--) {
                    if (field[l][j].value == 0) {
                        field[l][j].value = field[x][j].value;
                        field[x][j].value = 0;
                        x = l;
                        continue;
                    }
                    if (field[l][j].value == field[x][j].value) {
                        field[l][j].value *= 2;
                        field[x][j].value = 0;
                        break;
                    }
                    if (field[l][j].value != 0) {
                        break;
                    }
                }
            }
}

void Field::onRight()
{
    for (int i = 3; i >= 0; i--)
        for (int j = 3; j >= 0; j--)
            if (field[i][j].value != 0) {
                int x = i;
                for (int l = i + 1; l < 4; l++) {
                    if (field[l][j].value == 0) {
                        field[l][j].value = field[x][j].value;
                        field[x][j].value = 0;
                        x = l;
                        continue;
                    }
                    if (field[l][j].value == field[x][j].value) {
                        field[l][j].value *= 2;
                        field[x][j].value = 0;
                        break;
                    }
                    if (field[l][j].value != 0) {
                        break;
                    }
                }
            }
}


Field::Field() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            field[i][j].value = 0;
    createRandomBlocks();
}

void Field::loadLastField(int* lastValues)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            field[i][j].value = *(lastValues + i + j * 4);
    ScoreTable::Initilize()->user.currentScore = *(lastValues + 16);
    delete lastValues;
}

Field::~Field()
{
}

int Field::isGameEnd() {
    //Проверка на победу
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (field[i][j].value == 2048) {
                ScoreTable::Initilize()->user.currentScore = getScore();
                return Win;
            }
    //Сохраняем текущее значение поля в буфер
    Block buff[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            buff[i][j].value = field[i][j].value;
        }
    //Делаем несколько ходов в основном поле
    onUp();
    createRandomBlocks();
    onDown();
    createRandomBlocks();
    onLeft();
    createRandomBlocks();
    onRight();
    //Проверяем изменилось ли поле после нескольких ходов(да - продолжаем играть / нет - поражение) 
    if (isPrevAndCurrFieldsSame()) {
        ScoreTable::Initilize()->user.currentScore = getScore();
        return Loose;
    }
    else {
        //Загружаем текущее поле из буфера
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) 
                field[i][j].value = buff[i][j].value;
        //Если текущее поле равно предыдущему, значит ход ни на что не повлиял, и генерировать новые блоки не нужно
        if (!isPrevAndCurrFieldsSame()) {
            createRandomBlocks();
            //Заносим текущее значение поля в предыдущее перед следующим ходом
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++) {
                    prevField[i][j].value = field[i][j].value;
                }
        }
        ScoreTable::Initilize()->user.currentScore = getScore();
        return Continue;
    }
}
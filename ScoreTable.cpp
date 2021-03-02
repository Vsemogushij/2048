#include "ScoreTable.h"

ScoreTable* ScoreTable::table = nullptr;

ScoreTable::ScoreTable() {
	user.name = "NONAME";
	user.currentScore = 0;
}

ScoreTable* ScoreTable::Initilize()
{
	if (table == nullptr)
		table = new ScoreTable();
	return table;
}

void ScoreTable::saveResults()
{
	FILE* save = fopen("ScoreTable.dat", "a");
	std::string record = user.name + " ";
	record += std::to_string(user.currentScore) + '\n';
	fprintf(save, record.c_str());
	fclose(save);
}

void ScoreTable::saveLastField(int* field)
{
	FILE* save = fopen("LastField.dat", "w");
	std::string record;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			record += std::to_string(*(field + i + j * 4)) + " ";
	record += std::to_string(user.currentScore);
	fprintf(save, record.c_str());
	fclose(save);
}

bool ScoreTable::isLastGameExists()
{
	FILE* save = fopen("LastField.dat", "r");
	if (save == nullptr) {
		return false;
	}
	else {
		fclose(save);
		return true;
	}
}

int* ScoreTable::loadLastGame()
{
	int* field = new int[17];
	FILE* save = fopen("LastField.dat", "r");
	for (int i = 0; i < 17; i++)
		fscanf(save, "%d ", (field + i));
	fclose(save);
	return field;
}

std::vector<std::string> ScoreTable::getScoreTable()
{
	std::vector<std::string> records;
	FILE* save = fopen("ScoreTable.dat", "r");
	if (save != nullptr) {
		char* buff = new char[64];

		char* res = fgets(buff, 64, save);
		while (res != nullptr) {
			*(res + strlen(res) - 1) = '\0';
			std::string x = res;
			records.push_back(x);
			res = fgets(buff, 64, save);
		}
		fclose(save);
	}
	return records;
}

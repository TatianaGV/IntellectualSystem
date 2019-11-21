#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>

#include <algorithm>
#include <fstream>


using namespace std;

vector<bool> board(64, false); //для проверки занята ли конкретная позиция

pair<int, int> answer;

//структура набора шашек
struct checkers
{
	checkers * parent;
	std::vector<int> position;
	int num_player;

	checkers(std::string s, int num_player, checkers * par = nullptr):parent(par)
	{
		this->num_player = num_player;
		for (int i = 0; i < 12; ++i)
		{
			position.push_back((s[i * 2] - 'A') + (s[i * 2 + 1] - '1') * 8);
			board[(s[i * 2] - 'A') + (s[i * 2 + 1] - '1') * 8] = true; //указываем, что данная клетка теперь занята
		}
	}

	checkers(std::vector<int> pos, int numPlayer, checkers * par = nullptr) :parent(par), position(pos), num_player(numPlayer) {}

	//создает дочерний узел с разницей в 1 шаг
	checkers * step(int num_check, int new_positions)
	{
		std::vector<int> v = position;

		board[v[num_check]] = false;  //изменяем board
		board[new_positions] = true;

		v[num_check] = new_positions;
		return new checkers(v, num_player, this);
	}

	//свободна ли позиция справа 
	bool right_free(int our_pos) 
	{
		if (our_pos % 8 != 7)
			if (!board[our_pos + 1])
				return true;
		return false;
	}

	//свободна ли позиция слева
	bool left_free(int our_pos)
	{
		if (our_pos % 8 != 0)
			if (!board[our_pos - 1])
				return true;
		return false;
	}

	//свободна ли позиция снизу
	bool down_free(int our_pos)
	{
		if (our_pos / 8 != 0)
			if (!board[our_pos - 8])
				return true;
		return false;
	}

	//свободна ли позиция сверху
	bool up_free(int our_pos)
	{
		if (our_pos / 8 != 7)
			if (!board[our_pos + 8])
				return true;
		return false;
	}


	//внутренняя функция для variants_of_positions, проверяет возможность прыжков
	void new_variants_of_steps(int our_pos, std::set<int> & steps, std::list<int> & new_steps)
	{

		if (our_pos % 8 != 7 && !right_free(our_pos)) //проверяем прыжок вправо
		{
			int new_pos = our_pos + 1;
			if (right_free(new_pos) && steps.find(new_pos + 1) == steps.end() && find(new_steps.begin(), new_steps.end(), new_pos + 1) == new_steps.end())
			{
				new_steps.push_back(new_pos + 1);
				new_pos += 1;
				new_variants_of_steps(new_pos, steps, new_steps);
			}
		}

		if (our_pos % 8 != 0 && !left_free(our_pos)) //проверяем прыжок влево
		{
			int new_pos = our_pos -  1;
			if (left_free(new_pos) && steps.find(new_pos - 1) == steps.end() && find(new_steps.begin(), new_steps.end(), new_pos - 1) == new_steps.end())
			{
				new_steps.push_back(new_pos - 1);
				new_pos -= 1;
				new_variants_of_steps(new_pos, steps, new_steps);
			}
		}

		if (our_pos / 8 != 7 && !up_free(our_pos)) //проверяем прыжок вверх
		{
			int new_pos = our_pos + 8;
			if (up_free(new_pos) && steps.find(new_pos + 8) == steps.end() && find(new_steps.begin(), new_steps.end(), new_pos + 8) == new_steps.end())
			{
				new_steps.push_back(new_pos + 8);
				new_pos += 8;
				new_variants_of_steps(new_pos, steps, new_steps);
			}
		}

		if (our_pos / 8 != 0 && !down_free(our_pos)) //проверяем прыжок вниз
		{
			int new_pos = our_pos - 8;
			if (down_free(new_pos) && steps.find(new_pos - 8) == steps.end() && find(new_steps.begin(), new_steps.end(), new_pos - 8) == new_steps.end())
			{
				new_steps.push_back(new_pos - 8);
				new_pos -= 8;
				new_variants_of_steps(new_pos, steps, new_steps);
			}
		}
	}

public:

	//выдает список всех позиций, которые можно получить за 1 ход из текущей
	std::list<int> variants_of_steps(int our_pos)
	{
		std::list<int> new_steps;
		std::set<int> steps;

		steps.insert(our_pos); // запоминаем позицию, чтобы не зациклиться

		if (right_free(our_pos)) //проверяем, свободна ли позиция справа
		{
			new_steps.push_back(our_pos + 1); //если да, то делаем шаг вправо
			steps.insert(our_pos + 1); // запоминаем позицию, чтобы не зациклиться
		}
		/*else
			if (our_pos % 8 != 7) //если позиция занята
			{
				int new_pos = our_pos + 1;
				if (right_free(new_pos) && steps.find(our_pos + 1) == steps.end()) //если после правой свободно, то перепрыгиваем и смотрим
				{																  //можно ли сделать еще прыжки
					new_steps.push_back(new_pos + 1);
					new_pos += 1;
					new_variants_of_steps(new_pos, steps, new_steps);
				}
			}*/

		if (left_free(our_pos)) //проверяем также для левой стороны
		{
			new_steps.push_back(our_pos - 1);
			steps.insert(our_pos - 1);
		}
		/*else
			if (our_pos % 8 != 0)
			{
				int new_pos = our_pos - 1;
				if (left_free(new_pos) && steps.find(our_pos - 1) == steps.end())
				{
					new_steps.push_back(new_pos - 1);
					new_pos -= 1;
					new_variants_of_steps(new_pos, steps, new_steps);
				}
			}
*/
		if (up_free(our_pos)) //проверяем верх
		{
			new_steps.push_back(our_pos + 8);
			steps.insert(our_pos + 8);
		}
		/*else
			if (our_pos / 8 != 7)
			{
				int new_pos = our_pos + 8;
				if (up_free(new_pos) && steps.find(our_pos + 8) == steps.end())
				{
					new_steps.push_back(new_pos + 8);
					new_pos += 8;
					new_variants_of_steps(new_pos, steps, new_steps);
				}
			}
*/
		if (down_free(our_pos)) //проверяем низ
		{
			new_steps.push_back(our_pos - 8);
			steps.insert(our_pos - 8);
		}
		/*else
			if (our_pos / 8 != 0)
			{
				int new_pos = our_pos - 8;
				if (down_free(new_pos) && steps.find(our_pos - 8) == steps.end())
				{
					new_steps.push_back(new_pos - 8);
					new_pos -= 8;
					new_variants_of_steps(new_pos, steps, new_steps);
				}
			}*/
		return new_steps;
	}

	//является ли данная расстановка конечной
	bool isEnd()
	{
		if (num_player == 1)
		{
			for (int i = 0; i < 12; ++i)
				if (position[i] % 8 < 4 || position[i] / 8 < 5)
					return false;
		}
		else
		{
			for (int i = 0; i < 12; ++i)
				if (position[i] % 8 > 3 || position[i] / 8 > 2)
					return false;
		}

		return true;
	}

	friend bool operator==(checkers c1, checkers c2)
	{
		return c1.position == c2.position && c1.parent == c2.parent;
	}
};

checkers * me, *rival;



vector<int> variants_of_best_position(30);

void fill_variants(int num_player) {
	variants_of_best_position[0] = 0;
	variants_of_best_position[1] = 1;
	variants_of_best_position[2] = 8;
	variants_of_best_position[3] = 2;
	variants_of_best_position[4] = 9;
	variants_of_best_position[5] = 16;
	variants_of_best_position[6] = 3;
	variants_of_best_position[7] = 10;
	variants_of_best_position[8] = 17;
	variants_of_best_position[9] = 11;
	variants_of_best_position[10] = 18;
	variants_of_best_position[11] = 19;
	variants_of_best_position[12] = 24;
	variants_of_best_position[13] = 4;
	variants_of_best_position[14] = 25;
	variants_of_best_position[15] = 12;
	variants_of_best_position[16] = 26;
	variants_of_best_position[17] = 20;
	variants_of_best_position[18] = 27;
	variants_of_best_position[19] = 28;
	variants_of_best_position[20] = 32;
	variants_of_best_position[21] = 5;
	variants_of_best_position[22] = 33;
	variants_of_best_position[23] = 13;
	variants_of_best_position[24] = 34;
	variants_of_best_position[25] = 21;
	variants_of_best_position[26] = 35;
	variants_of_best_position[27] = 29;
	variants_of_best_position[28] = 36;
	variants_of_best_position[29] = 37;
}

//Свободная позиция, которая ближе всего к целевому прямоугольнику
int closest_to_goal_free_position(vector<bool>& curr_board, int num_player, int curr_pos)
{
	fill_variants(num_player);

	for (int i = 0; i < variants_of_best_position.size(); ++i)
	{
		if (curr_pos == variants_of_best_position[i])
			return curr_pos;
		if (!curr_board[variants_of_best_position[i]])
			return variants_of_best_position[i];
	}
	return 0;
}


int cntInHouse(checkers* curr_player)
{
	int cnt = 0;
	if (curr_player->num_player == 2) {
		for (auto pos : curr_player->position) {
			if ((pos % 8 > 3) && (pos / 8 > 4))
				++cnt;
		}
	}

	return cnt;
}

bool checker_in_contrary_home(checkers* curr_player, int num)
{
	int pos = curr_player->position[num];
	if (curr_player->num_player == 2) {
		if ((pos % 8 < 4) && (pos / 8 < 3))
			return true;
	}
	return false;
}

int h_in_contrary(int num_p, int pos)
{
	if (num_p == 2) {
		if (pos == 0)
			return 1;
		if (pos == 1 || pos == 8)
			return 2;
		if (pos == 2 || pos == 9 || pos == 16)
			return 3;
		if (pos == 3 || pos == 10 || pos == 17)
			return 4;
		if (pos == 11 || pos == 18)
			return 5;
		if (pos == 19)
			return 6;
	}
	else {
		if (pos == 63)
			return 1;
		if (pos == 62 || pos == 55)
			return 2;
		if (pos == 61 || pos == 54 || pos == 47)
			return 3;
		if (pos == 60 || pos == 53 || pos == 46)
			return 4;
		if (pos == 52 || pos == 45)
			return 5;
		if (pos == 44)
			return 6;
	}
}


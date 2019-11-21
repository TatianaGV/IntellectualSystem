#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <queue>
#include <algorithm>
#include <fstream>
#include <QtMath>

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

		board[v[num_check]] = false;  //не забываем изменить board
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

private:

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
        else
        if (our_pos % 8 != 7) //если позиция занята
        {
            int new_pos = our_pos + 1;
            if (right_free(new_pos) && steps.find(our_pos + 1) == steps.end()) //если после правой свободно, то перепрыгиваем и смотрим
            { //можно ли сделать еще прыжки
                new_steps.push_back(new_pos + 1);
                steps.insert(new_pos + 1);
                //new_pos += 1;
                //new_variants_of_steps(new_pos, steps, new_steps);
            }
        }

        if (left_free(our_pos)) //проверяем также для левой стороны
        {
            new_steps.push_back(our_pos - 1);
            steps.insert(our_pos - 1);
        }
        else
        if (our_pos % 8 != 0)
        {
            int new_pos = our_pos - 1;
            if (left_free(new_pos) && steps.find(our_pos - 1) == steps.end())
            {
                new_steps.push_back(new_pos - 1);
                steps.insert(new_pos - 1);
                //new_pos -= 1;
                //new_variants_of_steps(new_pos, steps, new_steps);
            }
        }

        if (up_free(our_pos)) //проверяем верх
        {
            new_steps.push_back(our_pos + 8);
            steps.insert(our_pos + 8);
        }
        else
        if (our_pos / 8 != 7)
        {
            int new_pos = our_pos + 8;
            if (up_free(new_pos) && steps.find(our_pos + 8) == steps.end())
            {
                new_steps.push_back(new_pos + 8);
                steps.insert(new_pos + 8);
                //new_pos += 8;
                //new_variants_of_steps(new_pos, steps, new_steps);
            }
        }

        if (down_free(our_pos)) //проверяем низ
        {
            new_steps.push_back(our_pos - 8);
            steps.insert(our_pos - 8);
        }
        else
        if (our_pos / 8 != 0)
        {
            int new_pos = our_pos - 8;
            if (down_free(new_pos) && steps.find(our_pos - 8) == steps.end())
            {
                new_steps.push_back(new_pos - 8);
                steps.insert(new_pos - 8);
                //new_pos -= 8;
                //new_variants_of_steps(new_pos, steps, new_steps);
            }
        }
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

kidfhlwfhw
checkers * me, *rival;

int manhattan_dist(int curr_pos, int goal_pos) {
	return abs(goal_pos - curr_pos) / 8 + abs(goal_pos - curr_pos) % 8;
}

//<Позиция, манхэттэнское расстояниe до goal_pos>
vector<pair<int, int>> get_manh_distances(list<int>& variants, int goal_pos) {
	//Позиция, манх расстояние
	vector<pair<int, int>> manh_distances(variants.size());

	int i = 0;
	for (int curr_var_pos: variants)
	{
		manh_distances[i] = make_pair(curr_var_pos, manhattan_dist(curr_var_pos, goal_pos));
		++i;
	}

	//Сортировка по расстояниям
	sort(manh_distances.begin(), manh_distances.end(),
		[](pair<int, int> p1, pair<int, int> p2) {return p1.second < p2.second; });

	return manh_distances;
}



vector<int> variants_of_best_position(30);

void fill_variants(int num_player) {
	if (num_player == 1)
	{
		//Внутри целевого прямоугольника
		//variants_of_best_position = {63, 62, 55, 61, 54, 47, 60, 53, 46, 52, 45, 44,
			//Ближайшие к целевому прямоугольнику
			//39, 59, 38, 51, 37, 43, 36, 35, 31, 58, 30, 50, 29, 42, 28, 34, 27, 26};
		variants_of_best_position[0] = 63;
		variants_of_best_position[1] = 62;
		variants_of_best_position[2] = 55;
		variants_of_best_position[3] = 61;
		variants_of_best_position[4] = 54;
		variants_of_best_position[5] = 47;
		variants_of_best_position[6] = 60;
		variants_of_best_position[7] = 53;
		variants_of_best_position[8] = 46;
		variants_of_best_position[9] = 52;
		variants_of_best_position[10] = 45;
		variants_of_best_position[11] = 44;
		variants_of_best_position[12] = 39;
		variants_of_best_position[13] = 59;
		variants_of_best_position[14] = 38;
		variants_of_best_position[15] = 51;
		variants_of_best_position[16] = 37;
		variants_of_best_position[17] = 43;
		variants_of_best_position[18] = 36;
		variants_of_best_position[19] = 35;
		variants_of_best_position[20] = 31;
		variants_of_best_position[21] = 58;
		variants_of_best_position[22] = 30;
		variants_of_best_position[23] = 50;
		variants_of_best_position[24] = 29;
		variants_of_best_position[25] = 42;
		variants_of_best_position[26] = 28;
		variants_of_best_position[27] = 34;
		variants_of_best_position[28] = 27;
		variants_of_best_position[29] = 26;
	}
	else
	{
		//Внутри целевого прямоугольника
		//variants_of_best_position = { 0, 1, 8, 2, 9, 16, 3, 10, 17, 11, 18, 19,
			//Ближайшие к целевому прямоугольнику
		//	24, 4, 25, 12, 26, 20, 27, 28, 32, 5, 33, 13, 34, 21, 35, 29, 36, 37};

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

//Количество шагов от текущей позиции до свободной, ближайшей к прямоугольнику 
int cnt_steps_to_best_free_pos(vector<bool>& curr_board, checkers * curr_player, int curr_num)
{
	
	
	int curr_pos = curr_player->position[curr_num];

	int best_pos = closest_to_goal_free_position(curr_board, curr_player->num_player, curr_pos);

	if (curr_pos == best_pos)
		return 0;



	list<int> vars = curr_player->variants_of_steps(curr_pos);
	if (vars.size() == 0)
	{
		return 16;
	}

	//Позиции, которые уже использовались
	set<int> used_positions;
	used_positions.insert(curr_pos);

	int cnt_steps = 0;
	while (true)
	{
		if (curr_pos == best_pos)
			return cnt_steps;

		//Поиск лучшего шага для текущей позиции
		vars = curr_player->variants_of_steps(curr_pos);
		vector<pair<int, int>> manh_distances = get_manh_distances(vars, best_pos);
		//Первая неиспользованная позиция в списке возможных ходов. Список отсортирован по манх расстоянию
		int best_step = -1;
		for (auto& p : manh_distances)
		{
			auto it = used_positions.find(p.first);
			if (it == used_positions.end())
			{
				used_positions.insert(p.first);
				best_step = p.first;
				break;
			}
		}

		//Зацикливание
		if (best_step == -1)
			return 16;//throw exception("No variants for doing step; curr_pos = " + curr_pos);

		
		//Обновить игрока (сделать шаг)
		checkers * new_player_step = curr_player->step(curr_num, best_step);
		curr_player = new_player_step;
		//Обновить текущую позицию
		curr_pos = best_step;
		//Увеличить счётчик
		++cnt_steps;
	}
	return cnt_steps;
}


int heuristic1(vector<bool> curr_board, checkers * curr_player)
{
	//Запоминание предыдущих board и player
	vector<bool> old_board = board;
	board = curr_board;
	checkers * old_player = new checkers(curr_player->position, curr_player->num_player, curr_player->parent);

	//Стоимость - сумма чисел шагов для каждой шашки, которые нужны чтобы шашка попала в целевой прямоугольник
	int sum_cost = 0;
	for (int i = 0; i < 12; ++i)
	{
		sum_cost += cnt_steps_to_best_free_pos(board, curr_player, i);
	}

	//Восстановление предыдущих board и player
	board = old_board;
	curr_player = old_player;

	return -sum_cost;
}

int cntInHouse(checkers* curr_player)
{
	int cnt = 0;
	if (curr_player->num_player == 1)
	{
		for (auto pos : curr_player->position)
		{
			if ((pos % 8 < 4) && (pos / 8 < 3))
				++cnt;
		}
	}
	if (curr_player->num_player == 2)
	{
		for (auto pos : curr_player->position)
		{
			if ((pos % 8 > 3) && (pos / 8 > 4))
				++cnt;
		}
	}

	return cnt;
}

bool checker_in_contrary_home(checkers* curr_player, int num)
{
	int pos = curr_player->position[num];
	if (curr_player->num_player == 2)
	{
		if ((pos % 8 < 4) && (pos / 8 < 3))
			return true;
	}
	if (curr_player->num_player == 1)
	{
		if ((pos % 8 > 3) && (pos / 8 > 4))
			return true;
	}
	return false;
}

int h_in_contrary(int num_p, int pos)
{
	if (num_p == 2)
	{
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
	else
	{
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

long long heuristic2(vector<bool> curr_board, checkers * curr_player)
{
	
	long long sum_cost = 1;
	long long cnt = cntInHouse(curr_player);

	//int best_pos = curr_player->num_player == 1 ? 1 : 2;
	for (int i = 0; i < 12; ++i)
	{
		long long cur;
		if(checker_in_contrary_home(curr_player, i))
		{ 
			cur = h_in_contrary(curr_player->num_player, curr_player->position[i]);

		}
		else
		{
			cur = (manhattan_dist(curr_player->position[i],
				closest_to_goal_free_position(curr_board, curr_player->num_player, curr_player->position[i])) + 7);
		}
		sum_cost *= cur;//pow(cur, 0.5);
	}

	return -sum_cost - pow(cnt + 1, 4); //* (cnt+1);
}


const int ddepth = 3;
auto heuristic = heuristic2;
checkers* m1;
checkers* r1;

void step(vector<bool> & cur_board, checkers* cur, int num_check, int new_positions) {
	cur_board[cur->position[num_check]] = false;
	cur_board[new_positions] = true;
	cur->position[num_check] = new_positions;
}

void additionalAB(vector<bool> cboard, checkers * player1, checkers * player2, 
	int depth, bool comp, long long & a, long long & b)
{
	if (depth == 0)
	{
		a = heuristic(cboard, new checkers(player1->position, player1->num_player));
		b = heuristic(cboard, new checkers(player2->position, player2->num_player));
		return;
	}

	if (comp)
	{
		for (int x = 0; x < 12; ++x)
		{
			auto v = player1->variants_of_steps(player1->position[x]);
			for (auto y : v)
			{
				checkers * c = new checkers(player1->position, player1->num_player);
				checkers * c1 = new checkers(player2->position, player2->num_player);

				vector<bool> bcopy = cboard;
				step(cboard, c, x, y);
				long long a1 = a;
				long long b1 = b;
				additionalAB(cboard, c, c1, depth - 1, !comp, a1, b1);

				cboard = bcopy;
				delete c;
				delete c1;

				if (a1 > a)
					a = a1;
				if (b1 > b)
					b = b1;
			}
			
		}
	}
	else
	{
		for (int x = 0; x < 12; ++x)
		{
			auto v = player2->variants_of_steps(player2->position[x]);
			for (auto y : v)
			{
				checkers * c1 = new checkers(player1->position, player1->num_player);
				checkers * c = new checkers(player2->position, player2->num_player);
				vector<bool> bcopy = cboard;

				step(cboard, c, x, y);
				long long a1 = a;
				long long b1 = b;
				additionalAB(cboard, c1, c, depth - 1, !comp, a1, b1);

				cboard = bcopy;
				delete c;
				delete c1;

				if (b1 > b)
					b = b1;
				if (a1 > a)
					a = a1;

			}
			
		}
	}
}

pair<int, int> abAlgorithm(checkers * player, vector<bool> curboard, long long a, long long b)
{
	pair<int, int> nanswer(-1, -1);
	
	for (int x = 0; x < 12; ++x)
	{
		checkers * c = new checkers(player->position, player->num_player);
		auto v = player->variants_of_steps(player->position[x]);
		for (auto y : v)
		{
			vector<bool> bcopy = curboard;
			step(curboard, c, x, y);
			long long a1 = a;
			long long b1 = b;

			checkers * newrival = new checkers(r1->position, r1->num_player);
			additionalAB(curboard, c, newrival, ddepth - 1, false, a1, b1);

			curboard = bcopy;
			delete newrival;

			if (a1 > a)
			{
				a = a1;
				nanswer.first = x;
				nanswer.second = y;
			}
			if (b1 > b)
				b = b1;

		}

		delete c;
	}
	return nanswer;
}



class node{
public:

	vector<bool> curr_board;

	node(vector<bool> bd): curr_board(bd){
	}
};

node* next_move;

unsigned long long newminimax(node* cur, checkers* curr_p, vector<bool> cur_board, bool comp, int depth, unsigned long long a, unsigned long long b){
	unsigned long long test = -1;
	node* best_move = nullptr;
	int score = 0;
	vector<bool> oldb = cur_board;
	if(comp){ //TRUE - компьютер
		if(depth == 0 || curr_p->isEnd())
			return heuristic2(cur->curr_board, curr_p);
		score = INT_MIN;
		for (int x = 0; x < curr_p->position.size(); ++x){
			list<int> v = curr_p->variants_of_steps(curr_p->position[x]);
			for (int y : v) {
				step(cur_board,curr_p, x, y);
				node* next = new node(cur_board);			
				test = newminimax(next,r1,cur_board,0,depth-1,a,b); //Здесь надо копию противника
				if(test > score){
					score = test;
					best_move = next;
				}
				a = max(a, test);
				if (a >= b) goto br;
			}
		}
	}
	else{
		if(depth == 0 || curr_p->isEnd())
			return heuristic2(cur->curr_board, curr_p);
		score = INT_MAX;
		for (int x = 0; x < curr_p->position.size(); ++x){
			list<int> v = curr_p->variants_of_steps(curr_p->position[x]);
			for (int y : v) {
				step(cur_board,curr_p, x, y);
				node* next = new node(cur_board);			
				test = newminimax(next,m1,cur_board,1,depth-1,a,b); //Здесь надо копию нас
				if(test <= score){
					score = test;
					best_move = next;
				}
				b = min(b, test);
				if (a >= b) goto br;
			}
		}
	}

	br:
	if (depth == ddepth && best_move != nullptr){
		next_move = best_move;
		cout << endl <<"best_move" << endl;
		for(int i = 0; i < best_move->curr_board.size(); ++ i)
			cout << best_move->curr_board[i] << " ";
		cout << endl;
	}
	return score;
} 

void newstart(){
	node* st = new node(board);
	m1 = new checkers(*me);
	r1 = new checkers(*rival);
	answer = abAlgorithm(m1, board, LLONG_MIN, LLONG_MIN);
}

pair<int, int> find_step(vector<bool> oldboard, vector<bool> newboard) { 
	int old_pos, new_pos; 

	for (int i = 0; i < 64; ++i){
		if (oldboard[i] != newboard[i]) 
		if (oldboard[i]) 
			old_pos = i; 
		else 
			new_pos = i; 
	}
	return pair<int, int>(old_pos, new_pos); 
}

int find_index(vector<int> vpos, int pos) { 
	int indx = -1;

	for (int i = 0; i < 12; ++i) 
		if (vpos[i] == pos) 
		indx = i; 
	return indx; 
}
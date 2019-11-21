#include "Ugolki.h"
#include "border.h"


int main(int argc, char* argv[])
{

	based_template();
	InputData();
	bool end = false, fl = false;
	int step = 2;

	print_board();

	if (rival->num_player == 1)
	{
		step++;
		cout << endl << "Number of step: " << step / 2 << endl;
		pair<char, string> p = get_correct_step();
		rival_step(p.first, p.second);
		print_board();
		end = rival->isEnd();
		fl = true;
	}

	while (!end)
	{
		newstart();

		print_string_step_by_answer();

		step++;
		me = me->step(answer.first, answer.second);


		cout << "Number of step: " << step / 2 << endl;
		print_board();
		end = me->isEnd();
		if (step / 2 > 79 && inhome(me))
		{
			fl = true;
			break;
		}

		if (end)
		{
			cout << "Player" + to_string(rival->num_player) + " lose" << endl;
			fl = false;
			break;
		}
		else
		{
			step++;
			cout << endl << "Number of step: " << step / 2 << endl;
			pair<char, string> p = get_correct_step();
			rival_step(p.first, p.second);

			print_board();
			end = rival->isEnd();
			fl = true;

			if (step / 2 > 79 && inhome(rival))
			{
				fl = false;
				break;

			}
		}
	}

	if (fl)
		cout << "Player" + to_string(me->num_player) + " lose" << endl;
	else
		cout << "Player" + to_string(rival->num_player) + " lose" << endl;
	system("Pause");
}
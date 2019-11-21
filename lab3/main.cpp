#include "Ugolki.h"
#include "gameBorder.h"1

int main()
{

    BorderInstall::based_template();
    BorderInstall::InputData();
	bool end = false, fl = false;
	int step = 2;

    BorderInstall::print_board();

    step++;
    cout << endl << "Number of step: " << step / 2 << endl;
    pair<char, string> p = CorrectSteps::get_correct_step();
    CorrectSteps::rival_step(p.first, p.second);
    BorderInstall::print_board();
    end = rival->isEnd();
    fl = true;


	while (!end)
	{
		newstart();

		step++;
		me = me->step(answer.first, answer.second);

		cout << "Number of step: " << step / 2 << endl;
        BorderInstall::print_board();

		if (step / 2 > 39 && BorderInstall::inhome(me))
		{
			fl = true;
			break;
		}
        end = me->isEnd();

		if (end)
		{
			cout << "Second" + to_string(rival->num_player) + " lose" << endl;
			fl = false;
			break;
		}
		else
		{
			step++;
			cout << endl << "Number of step: " << step / 2 << endl;
			pair<char, string> p = CorrectSteps::get_correct_step();
            CorrectSteps::rival_step(p.first, p.second);

            BorderInstall::print_board();
			end = rival->isEnd();
			fl = true;

			if (step / 2 > 10 && BorderInstall::inhome(rival))
			{
				fl = false;
				break;
			}
		}
	}

	if (!fl)
		cout << "First Player" + to_string(me->num_player) + " lose" << endl;
	else
		cout << "Second Player" + to_string(rival->num_player) + " lose" << endl;

}
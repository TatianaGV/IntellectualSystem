#include "Ugolki.h"


std::vector<string> print_info(11);
std::vector<int> home1(12);
std::vector<int> home2(12);

void based_template()
{
    print_info[0] = "  A B C D E F G H ";
    print_info[1] = "-------------------";
    print_info[10] = print_info[1];

    for (int i = 0; i < 8; ++i)
        print_info[i + 2] = to_string(i + 1) + "|_|_|_|_|_|_|_|_|";

    for (int i = 0; i < 4; ++i)
    {
        home1[i] = i;
        home1[i + 4] = i + 8;
        home1[i + 8] = i + 16;

        home2[i] = 63 - i;
        home2[i + 4] = 63 - (i + 8);
        home2[i + 8] = 63 - (i + 16);
    }
}

void delete_info()
{
    for (int i = 0; i < 8; ++i)
        print_info[i + 2] = to_string(i + 1) + "|_|_|_|_|_|_|_|_|";
}

void find_pos()
{
    int m = 2;
    delete_info();
    for (int i = 0; i < 12; ++i)
    {
        print_info[2 + (me->position[i]) / 8][(1 + (me->position[i]) % 8) * 2] = '0';
        if(i > 8)
            print_info[2 + (rival->position[i]) / 8][(1 + (rival->position[i]) % 8) * 2] = (char)('a' + i-9);
        else
            print_info[2 + (rival->position[i]) / 8][(1 + (rival->position[i]) % 8) * 2] = (char)('1' + i);
    }
}

void print_board()
{
    find_pos();
    for (int i = 0; i < 11; ++i)
        cout << print_info[i] << endl;
}

void InputData()
{
    std::cout << "Will you be player 1 or 2? :  ";
    int num_p;
    std::cin >> num_p;

    if (num_p == 2)
    {
        me = new checkers("A1B1C1D1A2B2C2D2A3B3C3D3", 1);
        rival = new checkers("H8G8F8E8H7G7F7E7H6G6F6E6", 2);
    }
    else
    {
        {
            rival = new checkers("A1B1C1D1A2B2C2D2A3B3C3D3", 1);
            me = new checkers("H8G8F8E8H7G7F7E7H6G6F6E6", 2);
        }
    }
}

bool inhome(checkers * c1)
{
    if (c1->num_player == 1)
    {
        for (int i = 0; i < 12; ++i)
            if (find(home1.begin(), home1.end(), c1->position[i]) != home1.end())
                return true;
    }
    else
        for (int i = 0; i < 12; ++i)
            if (find(home2.begin(), home2.end(), c1->position[i]) != home2.end())
                return true;

    return false;
}

pair<char, string> chose_step()
{
    cout << "Choose cheker: ";
    char c;
    cin >> c;
    cout << endl << "Make step: " << endl;
    string s;
    cin >> s;

    return make_pair(c, s);
}

pair<int, int> correct_step_to_digits(pair<char, string> step)
{
    char c = step.first;
    string s = step.second;

    int n = 0;
    if (isdigit(c))
        n = c - '1';
    else
    {
        if (c == 'a' || c == 'b' || c == 'c' || c == 'd')
            n = c - 'a' + 9;
    }
    int n_p = (s[0] - 'A') + (s[1] - '1') * 8;

    return make_pair(n, n_p);
}

bool is_correct_step(pair<char, string> step)
{
    char c = step.first;
    char c1 = step.second[0];
    char c2 = step.second[1];

    if (!isdigit(c) && c != 'a' && c != 'b' && c != 'c')
    {
        return false;
    }

    if (c1 != 'A' && c1 != 'B' && c1 != 'C' && c1 != 'D' &&
        c1 != 'E' && c1 != 'F' && c1 != 'G' && c1 != 'H')
    {
        return false;
    }

    if (c2 != '1' && c2 != '2' && c2 != '3' && c2 != '4' &&
        c2 != '5' && c2 != '6' && c2 != '7' && c2 != '8')
    {
        return false;
    }

    pair<int, int> p = correct_step_to_digits(step);
    list<int> l = rival->variants_of_steps(rival->position[p.first]);
    auto it = find(l.begin(), l.end(), p.second);
    if (it == l.end())
        return false;

    return true;
}

pair<char, string> get_correct_step()
{
    pair<char, string> p = chose_step();
    while (!is_correct_step(p))
    {
        cout << "Incorrect step. Try again" << endl;
        p = chose_step();
    }
    return p;
}

void rival_step(char c, string s)
{
    pair<int, int> p = correct_step_to_digits(make_pair(c, s));
    rival = rival->step(p.first, p.second);
}

string get_string_step_by_int_step(int step)
{
    step = step;
    int letter = step % 8;
    int digit = step / 8;

    string s;
    s += ('A' + letter);
    s += ('1' + digit);

    return s;
}

void print_string_step_by_answer() {
    int p1 = me->position[answer.first];
    int p2 = answer.second;

    string s1 = get_string_step_by_int_step(p1);
    string s2 = get_string_step_by_int_step(p2);

    cout << "Step: " << s1 << " => " << s2 << endl;
}
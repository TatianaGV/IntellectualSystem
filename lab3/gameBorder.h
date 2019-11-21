#pragma once
#include "Ugolki.h"
#include "algoritmIDS.h"

std::vector<string> print_info(11);
std::vector<int> playersHome1(12);
std::vector<int> playersHome2(12);


class BorderInstall {

public:

    //base template on desc
    static void based_template();

    static void delete_info();

    static void find_pos();

    static void print_board();

    static void InputData();

    static bool inhome(checkers * c1);

};

class CorrectSteps {
public:
    static pair<char, string> chose_step();

    static pair<int, int> correct_step_to_digits(pair<char, string> step);

    static bool is_correct_step(pair<char, string> step);

    static pair<char, string> get_correct_step();

    static void rival_step(char c, string s);
};


void BorderInstall::based_template() {
    print_info[0] = "  A B C D E F G H ";
    print_info[1] = "-------------------";
    print_info[10] = print_info[1];

    for (int i = 0; i < 8; ++i)
        print_info[i + 2] = to_string(i + 1) + "|_|_|_|_|_|_|_|_|";

    for (int i = 0; i < 4; ++i)
    {
        playersHome1[i] = i;
        playersHome1[i + 4] = i + 8;
        playersHome1[i + 8] = i + 16;

        playersHome2[i] = 63 - i;
        playersHome2[i + 4] = 63 - (i + 8);
        playersHome2[i + 8] = 63 - (i + 16);
    }
}


void BorderInstall::delete_info() {
    for (int i = 0; i < 8; ++i)
        print_info[i + 2] = to_string(i + 1) + "|_|_|_|_|_|_|_|_|";
}

void BorderInstall::find_pos() {
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

void BorderInstall::print_board() {
    find_pos();
    for (int i = 0; i < 11; ++i)
        cout << print_info[i] << endl;
}

void BorderInstall::InputData() {
    std::cout << "You are the first player. Please, press 1 that start game." << endl;
    int num_p;
    std::cin >> num_p;
    rival = new checkers("A1B1C1D1A2B2C2D2A3B3C3D3", 1);
    me = new checkers("H8G8F8E8H7G7F7E7H6G6F6E6", 2);
}

bool BorderInstall::inhome(checkers * c1) {
    for (int i = 0; i < 12; ++i)
        if (find(playersHome1.begin(), playersHome1.end(), c1->position[i]) != playersHome1.end())
            return true;
}

pair<char, string> CorrectSteps::chose_step() {
    cout << "Choose cheker which you will move: ";
    char c;
    cin >> c;
    cout << endl << "Make step: " << endl;
    string s;
    cin >> s;

    return make_pair(c, s);
}

pair<int, int> CorrectSteps::correct_step_to_digits(pair<char, string> step) {
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

bool CorrectSteps::is_correct_step(pair<char, string> step) {
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

pair<char, string> CorrectSteps::get_correct_step() {
    pair<char, string> p = chose_step();
    while (!is_correct_step(p))
    {
        cout << "Wrong move. Try again" << endl;
        p = chose_step();
    }
    return p;
}

void CorrectSteps::rival_step(char c, string s) {
    pair<int, int> p = correct_step_to_digits(make_pair(c, s));
    rival = rival->step(p.first, p.second);
}
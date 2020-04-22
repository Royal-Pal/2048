#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int board[4][4]; //Board for 2048

//mapping the pressed key
int dir_line[] = {1, 0, -1};
int dir_col[] = {0, 1, 0, -1};

pair<int, int> generate_unoccupied_pos()
{
    int occupied = 1;
    int line, column;
    while(occupied)
    {
        line = rand() % 4;
        column = rand() % 4;
        if(board[line][column] == 0)
            occupied = 0;
    }
    return make_pair(line, column);
}

void add_piece()
{
    pair<int, int> pos = generate_unoccupied_pos();
    board[pos.first][pos.second] = 2;

    return;
}

void new_game()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            board[i][j] = 0;
    }
    add_piece();
    return;
}

void printUI()
{
    system("cls");
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(board[i][j] == 0)
                cout << "* ";
            else
                cout << board[i][j] << " ";
        }
        cout << endl;
    }

    //Instructions to the user
    cout << "Instructions : " << endl;
    cout << "n : new game, w : up, s : down, a : left, d : right, q : quit" << endl;

    return;
}

bool can_do_move(int line, int clm, int next_line, int next_clm)
{
    if(next_line < 0 or next_clm < 0 or next_clm >= 4 or next_line >= 4 or
        (board[line][clm] != board[next_line][next_clm] and board[next_line][next_clm] != 0))
        return false;

    return true;
}

void apply_move(int direction)
{
    int start_line = 0, start_clm = 0, line_step = 1, clm_step = 1;
    if(direction == 0)
    {
        start_line = 3;
        line_step = -1;
    }
    if(direction == 1)
    {
        start_clm = 3;
        clm_step = -1;
    }

    int move_possible = 0;
    for(int i = start_line; i >=0 and i < 4; i += line_step)
    {
        for(int j = start_clm; j >= 0 and j < 4; j += clm_step)
        {
            int next_i  =i + dir_line[direction], next_j = j + dir_col[direction];
            if(can_do_move(i, j, next_i, next_j))
            {
                board[next_i][next_j] += board[i][j];
                board[i][j] = 0;
                move_possible = 1;
            }
        }
        if(move_possible)
            add_piece();
    }
    return;
}

int main()
{
    char command_to_dir[128];
    command_to_dir['s'] = 0;
    command_to_dir['d'] = 1;
    command_to_dir['w'] = 2;
    command_to_dir['a'] = 3;

    new_game();
    while(true)
    {
        printUI();
        char command;   cin >> command;
        if(command == 'n')
            new_game();
        else if(command == 'q')
            break;
        else
        {
            int curr_dir = command_to_dir[command];
            //cout << curr_dir << endl;
            apply_move(curr_dir);
        }
    }
}

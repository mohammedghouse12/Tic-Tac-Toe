#include <bits/stdc++.h>
#include <stdlib.h>
#include <Windows.h>
#include <unistd.h>
using namespace std;

class Board
{
private:
    char board[3][3];
    char player, computer;

public:
    Board()
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = ' ';
        cout << "Enter your choice to play (X/O): ";
        cin >> player;
        player = 'X';
        computer = otherplayer(player);
        cout << "Enter row number and column number in 0 index to place your pin!!\n";
    }
    char getCell(int i, int j)
    {
        return board[i][j];
    }
    void setCell(int i, int j, char player)
    {
        assert(board[i][j] = ' ');
        board[i][j] = player;
    }
    inline char otherplayer(char player)
    {
        return (player ^ 'X' ^ 'O');
    }
    char check_finish()
    {
        for (int i = 0; i < 3; i++)
            if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
                return board[i][0];
        for (int i = 0; i < 3; i++)
            if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ')
                return board[0][i];
        if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ')
            return board[0][0];
        if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ')
            return board[0][2];
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == ' ')
                    return 'C';
        return 'D';
    }
    char decide_state(char player)
    {
        char flag = check_finish();
        if (flag != 'C')
        {
            if (flag == player)
                return 'W';
            if (flag == 'D')
                return 'D';
            return 'L';
        }
        int possible_moves = 0, losing_moves = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    possible_moves++;
                    setCell(i, j, player);
                    char result = decide_state(otherplayer(player));
                    setCell(i, j, ' ');
                    if (result == 'L')
                        return 'W';
                    if (result == 'W')
                        losing_moves++;
                }
            }
        }
        if (possible_moves == losing_moves)
            return 'L';
        return 'D';
    }
    void print_board()
    {
        cout << "\n     0    1    2\n";
        cout << "   _________________\n";
        cout << "  |     |     |     |\n";
        cout << "0 |  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  |\n";
        cout << "  |_____|_____|_____|\n";
        cout << "  |     |     |     |\n";
        cout << "1 |  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  |\n";
        cout << "  |_____|_____|_____|\n";
        cout << "  |     |     |     |\n";
        cout << "2 |  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  |\n";
        cout << "  |_____|_____|_____|\n";
        cout << endl
             << endl;
    }
    void play()
    {
        int row, column;
        cout << "Enter your move: ";
        cin >> row >> column;
        cout << row << " " << column << endl;
        cout << board[row][column] << endl;
        if (board[row][column] != ' ')
        {
            cout << "Invalid move!\n";
            return;
        }

        setCell(row, column, player);
        print_board();
        if (check_finish() != 'C')
            return;
        pair<int, int> draw_pair;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    setCell(i, j, computer);
                    char flag = decide_state(player);
                    if (flag == 'L')
                        return;
                    if (flag == 'D')
                        draw_pair = make_pair(i, j);
                    setCell(i, j, ' ');
                }
            }
        }
        setCell(draw_pair.first, draw_pair.second, computer);
        return;
    }
    void judge()
    {
        if (check_finish() == computer)
        {
            cout << " YOU LOOSE " << endl;
        }
        else if (check_finish() == 'D')
        {
            cout << "It's a draw " << endl;
        }
        else
        {
            cout << "  YOU WINN !!!" << endl;
        }
    }
};
int main()
{
    Board board;
    board.print_board();
    while (board.check_finish() == 'C')
    {
        board.play();
        sleep(2);
        board.print_board();
    }
    board.judge();
    sleep(6);
    return 0;
}
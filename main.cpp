#include <iostream>
using namespace std;

char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

void displayBoard()
{
    cout << "\n";
    cout << "     |     |     \n";
    cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "\n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "\n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "\n";
    cout << "     |     |     \n";
    cout << "\n";
}

bool checkWin(char player)
{
    // Rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player &&
            board[i][1] == player &&
            board[i][2] == player)
        {
            return true;
        }
    }

    // Columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == player &&
            board[1][i] == player &&
            board[2][i] == player)
        {
            return true;
        }
    }

    // Diagonals
    if (board[0][0] == player &&
        board[1][1] == player &&
        board[2][2] == player)
    {
        return true;
    }

    if (board[0][2] == player &&
        board[1][1] == player &&
        board[2][0] == player)
    {
        return true;
    }

    return false;
}

bool isDraw()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
            {
                return false;
            }
        }
    }

    return true;
}

bool makeMove(int position, char player)
{
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    if (position < 1 || position > 9)
    {
        return false;
    }

    if (board[row][col] == 'X' || board[row][col] == 'O')
    {
        return false;
    }

    board[row][col] = player;
    return true;
}

int main()
{
    char currentPlayer = 'X';
    int position;

    cout << "=========================\n";
    cout << "      TIC-TAC-TOE\n";
    cout << "=========================\n";

    while (true)
    {
        displayBoard();

        cout << "Player " << currentPlayer;
        cout << ", choose a position (1-9): ";
        cin >> position;

        if (!makeMove(position, currentPlayer))
        {
            cout << "\nInvalid move! Try again.\n";
            continue;
        }

        if (checkWin(currentPlayer))
        {
            displayBoard();
            cout << "Player " << currentPlayer << " wins! 🎉\n";
            break;
        }

        if (isDraw())
        {
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}
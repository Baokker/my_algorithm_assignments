#include <iostream>
#include <vector>
#include <string>

#define kSudokuSize 9

const char BLANK = ' ';

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// find all possible solutions to a particular position
void findAllPossibleNums(const vector<vector<char>> &board, int x, int y, bool *possibleNums)
{
    for (int i = 0; i <= kSudokuSize; i++)
        possibleNums[i] = true;

    // row and line
    for (int i = 0; i < kSudokuSize; i++)
    {
        if (board[i][y] != BLANK)
            possibleNums[board[i][y] - '0'] = false;
        if (board[x][i] != BLANK)
            possibleNums[board[x][i] - '0'] = false;
    }

    // 3 * 3 square
    for (int i = (x / 3) * 3; i < (x / 3) * 3 + 3; i++)
        for (int j = (y / 3) * 3; j < (y / 3) * 3 + 3; j++)
        {
            if (board[i][j] != BLANK)
                possibleNums[board[i][j] - '0'] = false;
        }
}

// backtracking
bool backTracking(vector<vector<char>> &board, const int count)
{
    // end condition
    if (count == 0)
        return true;

    // find the first position to fill
    int i, j;
    bool flag = false;
    for (i = 0; i < kSudokuSize; i++)
    {
        for (j = 0; j < kSudokuSize; j++)
            if (board[i][j] == BLANK)
            {
                flag = true;
                break;
            }
        if (flag)
            break;
    }

    bool possibleNums[kSudokuSize + 1];
    // find all possible numbers
    findAllPossibleNums(board, i, j, possibleNums);

    for (int m = 1; m <= kSudokuSize; m++)
    {
        if (possibleNums[m] == false)
            continue;

        board[i][j] = '0' + m;

        if (backTracking(board, count - 1))
            return true;
    }

    // fail to find a result
    // reset
    board[i][j] = BLANK;
    return false;
}

void sudokuPuzzleSolver(vector<vector<char>> &board)
{
    // count how many numbers need to solve
    int count = 0;
    for (int i = 0; i < kSudokuSize; i++)
    {
        for (int j = 0; j < kSudokuSize; j++)
        {
            if (board[i][j] == BLANK)
                count++;
        }
    }

    // backtrack
    backTracking(board, count);
}

void printBoard(const vector<vector<char>> &board)
{
    for (const auto &i : board)
    {
        for (const char &j : i)
            cout << j << " ";
        cout << endl;
    }
}

int main()
{
    vector<vector<char>> board(kSudokuSize, vector<char>(kSudokuSize, BLANK));

    // input the board
    // the input should be like the code below
    // input every row with a new line as interval
    // e.g.
    /*
1  456372
7368    5
 2 7 91 8
64   875
 82  5
5 16 38
357291 84
   5 7  3
2  38
    */
    for (int i = 0; i < kSudokuSize; i++)
    {
        string str;
        getline(cin, str);
        for (int j = 0; j < kSudokuSize; j++)
        {
            board[i][j] = str[j];
        }
    }

    // calculate
    sudokuPuzzleSolver(board);

    // print the result
    printBoard(board);

    return 0;
}

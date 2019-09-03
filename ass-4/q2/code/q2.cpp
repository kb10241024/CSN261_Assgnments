#include <iostream>
using namespace std;

/// Variable that counts number of different combinations possible
static int count = 0;

/**
* This method will be used to print the given board for Nquen problem.
* @param board n*n 2-d binary array for arrangements of queens
* @param n integer length ,dimension of board n*n;
* @author Kavya Barnwal
* @date 20/08/2019
*/
void printBoard(int *board[], int n)
{
    count++;
    cout << "Combination " << count << " for NQueen Problem" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << board[i][j] << " ";
        cout << "\n";
    }
}
/**
* This method will be used to check the validity of placement of new queen at ith row and jth cloumn.
* @param board n*n 2-d binary array for arrangements of queens.
* @param i , row number at which new queen is to be placed.
* @param j , column number at which new queen is to be placed.
* @param n integer length ,dimension of board n*n;
* @author Kavya Barnwal
* @date 20/08/2019
*/
bool noConflict(int *board[], int i, int j, int n)
{
    for (int row = i - 1, col1 = j - 1, col2 = j + 1; row >= 0; row--, col1--, col2++)
    {
        if (board[row][j] == 1)
            return false;
        if (col1 >= 0 && board[row][col1] == 1)
            return false;
        if (col2 < n && board[row][col2] == 1)
            return false;
    }
    return true;
}

/**
* Helper method for NQueen problem.
* @param board n*n 2-d binary array for arrangements of queens.
* @param i , row number at which new queen is to be placed.
* @param n integer length ,dimension of board n*n;
* @author Kavya Barnwal
* @date 20/08/2019
*/
void NQ(int *board[], int i, int n)
{
    if (i == n)
        return;

    for (int j = 0; j < n; j++)
    {
        if (noConflict(board, i, j, n))
        {
            board[i][j] = 1;
            if (i == n - 1)
            {
                printBoard(board, n);
            }
            else
            {
                NQ(board, i + 1, n);
            }
            board[i][j] = 0;
        }
    }
    return;
}

/**
* This method Will print all the solution for NQueen Problem.
* @param n integer length ,dimension of board n*n;
* @author Kavya Barnwal
* @date 20/08/2019
*/
void NQueen(int n)
{
    if (n > 3)
    {
        int *board[n];
        for (int i = 0; i < n; i++)
            board[i] = new int[n];
        NQ(board, 0, n);
    }
    else
        cout << "Arrangement not possible";
}
// Driver Code
int main()
{
    double time = 0.0;
    clock_t starting = clock();

    cout << "Enter the value n for NQueen Problem" << endl;
    int n;
    cin >> n;
    NQueen(n);

    clock_t ending = clock();
    time += (double)(ending - starting) / CLOCKS_PER_SEC;
    printf("\nTotal Execution time is : %f (sec)\n", time);

    return 0;
}
// C++ program to make a game of Connect-4
// with dynamic dimesion of board and connect piece
#include <iostream>

using namespace std;

// Traverse the board(2D array)
void traverse(char *board, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        cout << "\t\t|";
        for (int j = 0; j < c; j++)
        {
            // Printing values of the memory block
            cout << *(board + i * c + j) << "|";
        }

        // Seprating horizontal line(-----)
        cout << "\n\t\t-";
        for (int k = 0; k < c; k++)
        {
            cout << "--";
        }
        cout << endl;
    }
    cout << endl;
}

// Piece is putting on the board using Column Chosen by Player(ccp) parameter
void putPieceByPlayer(char *board, int r, int c, int ccp, char piece)
{
    for (int i = r - 1; i >= 0; i--)
    {
        // If place is already occupied then specified piece is placing above
        if (*(board + i * c + ccp) != ' ')
            continue;

        // Placing the piece on the board then break out from for loop
        *(board + i * c + ccp) = piece;
        break;
    }

    // Traversing board after placing piece by player
    traverse(board, r, c);
}

// To check horizontal win for player
int checkHorizontal(char *board, int r, int c, int p, char piece)
{
    // Declaring the horizontal counter
    // parameter emp is used to determine if entire row is empty.
    int h, emp;

    // Traversing from lower row to upper row in the 2D matrix
    for (int i = r - 1; i >= 0; i--)
    {
        // Initial value of h and emp are zero in the starting of each row
        h = 0;
        emp = 0;

        // Traversing from left to right in a row
        for (int j = 0; j < c; j++)
        {
            // To determine the state of rows(empty/occupied)
            if (*(board + i * c + j) == ' ')
            {
                emp++;
                h = 0;

                // If a row is empty then return 0 to the calling function
                if (emp == c)
                    return 0;
            }
            // If remaining space in a row is less than number of connecting piece
            // and horizontal counter is zero then break out from the loop.
            else if (j > (c - p) && h == 0)
                break;
            else if (*(board + i * c + j) == piece)
            {
                h++;

                // If horizontal counter becomes equal to connecting piece
                // then return 1 to calling function.
                if (h == p)
                    return 1;
            }
            else
                h = 0;
        }
    }
    return 0;
}

// To check vertical win for player
int checkVertical(char *board, int r, int c, int p, char piece)
{
    // Declaring vertical counter
    int v;

    // Traversing from right to left in bottom row
    for (int j = 0; j < c; j++)
    {
        // Intial value of vertical counter is zero for every new column
        v = 0;

        // Traversing from lower row to upper row in a column
        for (int i = r - 1; i >= 0; i--)
        {
            // If block is empty or remaining space in column is
            // less than number of connecting piece and vertical
            // counter is zero then  break out of loop.
            if ((i < (p - 1) && v < 1) || *(board + i * c + j) == ' ')
                break;
            else if (*(board + i * c + j) == piece)
            {
                v++;

                // If vertical counter becomes equal to connecting piece
                // then return 1 to calling function.
                if (v == p)
                    return 1;
            }
            else
                v = 0;
        }
    }
    return 0;
}

// To check diagonal win from right to left for player
int checkDiagonalRTL(char *board, int r, int c, int p, char piece)
{
    // Declaring diagonal counter and cartesian point to move diagonally
    int d, x, y;
    int counter;

    // Traversing from lower to upper row
    for (int i = r - 1; i >= 0; i--)
    {
        // Traversing from right to left in a row
        for (int j = c - 1; j >= 0; j--)
        {
            // Intial value of diagonal counter is zero for each block in a row
            d = 0;

            // If remaining space is less than number of connecting piece
            // then break out of loop.
            if (j < (p - 1))
                break;

            // Intializing cartesian point
            x = i;
            y = j;
            counter = 0;
            while (counter != p)
            {
                if (*(board + x * c + y) == piece)
                {
                    d++;

                    // If diagonal counter becomes equal to connecting piece
                    // then return 1 to calling function.
                    if (d == p)
                        return 1;
                }
                else
                    break;
                x--;
                y--;
                counter++;
            }
        }

        // If remaining space is less than number of connecting piece
        // then return 0 to the calling function
        if (i < (p - 1))
            return 0;
    }
}

// To check diagonal win from left to right for player
int checkDiagonalLTR(char *board, int r, int c, int p, char piece)
{
    // Declaring diagonal counter and cartesian point to move diagonally
    int d, x, y;
    int counter;

    // Traversing from lower to upper row
    for (int i = r - 1; i >= 0; i--)
    {
        // Traversing from left to right in a row
        for (int j = 0; j < c; j++)
        {
            // Intial value of diagonal counter is zero for each block in a row
            d = 0;

            // If remaining space is less than number of connecting piece
            // then break out of loop.
            if (j > (c - p))
                break;

            // Intializing cartesian point
            x = i;
            y = j;
            counter = 0;
            while (counter != p)
            {
                if (*(board + x * c + y) == piece)
                {
                    d++;

                    // If diagonal counter becomes equal to connecting piece
                    // then return 1 to calling function.
                    if (d == p)
                        return 1;
                }
                else
                    break;
                x--;
                y++;
                counter++;
            }
        }

        // If remaining space is less than number of connecting piece
        // then return 0 to the calling function
        if (i < (p - 1))
            return 0;
    }
}

// To check the status of board after placing the piece
// Check horizontaly, verticaly and diagonally for each player
int checkStatus(char *board, int r, int c, int p, char piece)
{
    if (checkHorizontal(board, r, c, p, piece))
        return 1;
    if (checkVertical(board, r, c, p, piece))
        return 1;
    if (checkDiagonalRTL(board, r, c, p, piece))
        return 1;
    if (checkDiagonalLTR(board, r, c, p, piece))
        return 1;
    return 0;
}

//Driver Code
int main()
{
    // Declaring dimesions for setting up the board for connect-4 Game
    int r, c, p;

    // To check if player want to play new game.
    int pga = 1;

    // To check if player want to change the dimesion of board
    // And number of connecting piece to win
    int flag = 1;

    cout << "\n\n\t\t\tWelcome to this exciting game called"
         << "\n\n\t\t\t\tGAME OF CONNECT\n\n"
         << endl;
    while (pga == 1)
    {
        if (flag)
        {
            cout << "Enter the integer value of rows and columns respectively that you want in your board: ";
            do
            {
                // Taking input from player
                // Number of rows and column to set up board
                cin >> r >> c;

                // Checking input given by player is positve and non-zero integer
                if (r <= 0 || c <= 0)
                {
                    cout << "Board with negative or zero dimensional value is not possible." << endl;
                    cout << "Please enter a positive, non-zero integer value of rows and columns that you want in your board: ";
                }
            } while (r <= 0 || c <= 0);

            cout << "Enter the integer for the number of pieces you like to connect to win this game: ";
            do
            {
                // Taking input from player
                // Number of connecing piece to win the game
                cin >> p;

                // Checking input given by player is non-zero integer
                if (p == 0)
                {
                    cout << "You can not have 0 pieces to connect." << endl;
                    cout << "Please enter a positive, non-zero integer for the"
                         << "number of pieces you like to connect to win this game: ";
                }
                // Checking input given by player is positve
                else if (p < 0)
                {
                    cout << "You can not have negative value for pieces to connect." << endl;
                    cout << "Please enter a positive, non-zero integer for the "
                         << "number of pieces you like to connect to win this game: ";
                }
            } while (p <= 0);
        }

        // Declaring parameters to assign color of piece chosen by player
        char p1, p2;
        do
        {
            cout << "\nPlayer 1: "
                 << "Do you want red or yellow(r or y)?\t";

            // Take piece's color input chosen by player 1
            cin >> p1;

            // Validating input given by player
            // Against allowed value
            if (p1 != 'r' && p1 != 'y' && p1 != 'R' && p1 != 'Y')
                cout << "Please enter a valid credentials" << endl;
        } while (p1 != 'r' && p1 != 'y' && p1 != 'R' && p1 != 'Y');

        // Assigning piece's color to the other player
        // On the basis of color chosen by first player
        if (p1 == 'r' || p1 == 'R')
        {
            p1 = 'r';
            cout << "\nPlayer 1 has chosen RED." << endl
                 << "Therefore, Player 2 has given YELLOW." << endl;
            p2 = 'y';
        }
        else
        {
            p1 = 'y';
            cout << "\nPlayer 1 has chosen YELLOW." << endl
                 << "Therefore, Player 2 has given RED." << endl;
            p2 = 'r';
        }

        // To keep track of status of block of board and run while loop
        int block = r * c;

        // Declaring memory block of size of r*c
        // Setting up the board
        char *board = new char[r * c];

        // Traversing the board(2D array)
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                // Assinging blank values to the memory block
                *(board + i * c + j) = ' ';
            }
        }

        cout << "\n\t\tNow begin the game.\n\n"
             << endl;

        // Traversing the board(2D array)
        // After assinging blank value to it
        traverse(board, r, c);

        // Initializing counter which make sure that main called checkStatus
        // function only when there is atleast specified number of connecting
        //  piece given by player are present on board of same color
        int counter = 0;

        // Running while loop until either one of player won the game
        // or board is completly filled
        while (block > 0)
        {

            // Take the input of column number chosen by player
            int ccp;

            counter++;
            cout << "Player 1: What column do you want to put your piece?\t";
            do
            {
                // Take input from player 1
                // Number of column in which he/she want to place his/her piece
                cin >> ccp;
                ccp--;

                // Check the input given by player 1 is valid or not
                // Against board dimension
                if (ccp > (c - 1) || ccp < 0)
                    cout << "Player 1, Please enter integer value between 1 and " << c << ".\nColumn?\t";
                //Checking given column is occupied or not
                else if (*(board + ccp) != ' ')
                {
                    cout << "This column is already filled.\nPlayer 1, Please choose any other column than " << (ccp + 1) << ".\nColumn?\t";
                    ccp = -1;
                }
            } while (ccp > (c - 1) || ccp < 0);

            cout << endl;

            // Call a funtion to place the piece on the board
            putPieceByPlayer(board, r, c, ccp, p1);

            // Checking status(win or not) of board for player 1
            if (counter >= p && checkStatus(board, r, c, p, p1))
            {
                cout << "Player 1 has won this game." << endl;
                break;
            }

            // Decrement of block
            // With every player's turn
            block--;
            if (block == 0)
            {
                cout << "Board is completly filled now.\n It's been a draw match" << endl;
                break;
            }

            cout << "Player 2: What column do you want to put your piece?\t";
            do
            {
                // Take input from player 2
                // Number of column in which he/she want to place his/her piece
                cin >> ccp;
                ccp--;

                // Check the input given by player 2 is valid or not
                // Against board dimension
                if (ccp > (c - 1) || ccp < 0)
                    cout << "Player 2, Please enter integer between 1 and " << c << ".\nColumn?\t";
                //Checking given column is occupied or not
                else if (*(board + ccp) != ' ')
                {
                    cout << "This column is already filled.\nPlayer 2, Please choose any other column than " << (ccp + 1) << ".\nColumn?\t";
                    ccp = -1;
                }
            } while (ccp > (c - 1) || ccp < 0);

            cout << endl;

            // Call a funtion to place the piece on the board
            putPieceByPlayer(board, r, c, ccp, p2);

            // Checking status(win or not) of board for player 1
            if (counter >= p && checkStatus(board, r, c, p, p2))
            {
                cout << "Player 2 has won this game." << endl;
                break;
            }

            // Decrement of block
            // With every player's turn
            block--;
            if (block == 0)
            {
                cout << "Board is completly filled now.\n It's been a draw match" << endl;
                break;
            }
        }

        cout << "I hope you had fun playing this wonderful game.\n"
             << endl;
        do
        {
            // Asking to players if they want to play again or not
            cout << "Do you like to play again(0 - No, 1 - Yes)?  ";

            // Taking input from the player
            cin >> pga;

            // Validating input given by player
            // Against allowed value
            if (pga != 0 && pga != 1)
                cout << "\nWrong Input. Please enter the specified credential." << endl;
            else if (pga == 1)
            {
                do
                {
                    // Asking to players if they like to change
                    // dimensions of board or not
                    cout << "Would you like to change the dimension(setup) of board?"
                         << endl
                         << "0. No\n1. Yes\t";

                    // Taking input from player
                    cin >> flag;

                    // Validating input given by player
                    // Against allowed value
                    if (flag != 0 && flag != 1)
                        cout << "\nWrong Input.  Please enter the specified credential." << endl;
                } while (flag != 0 && flag != 1);
            }
        } while (pga != 0 && pga != 1);
        delete[] board;
    }
    cout << "\n\n\t\t\tThank you for playing this wonderful game.\n\n\n"
         << endl;
    return 0;
}
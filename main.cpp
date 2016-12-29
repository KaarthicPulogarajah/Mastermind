#include <iostream>
#include <stdlib.h> // rand and srand
#include <stdio.h> // NULL
#include <time.h> // time
#include <algorithm> // random shuffle

using namespace std;

bool evaluate (char key[4], char a[4], int r, char b[10][9])
{
    char ans[4] = {' ',' ',' ',' '};

    for(int i = 0 ; i < 4 ; i++)
    {
        if (a[i] == key[i])
            ans[i] = '2';
        else
        {
            for(int j = 0 ; j < 4 ; j++)
            {
                if (i != j)
                {
                    if(a[i] == key[j])
                        ans[i] = '1';
                }
            }
        }
    }
    // randomize elements


    //implement into board array
    for (int i = 0 ; i < 4 ; i++)
        b[r][i+5] = ans[i];

    for(int i = 0 ; i < 4 ; i++)
        if(ans[i] != '2')
            return false;
    return true;
}

void print (char a[4])
{
    for(int i = 0 ; i < 4 ; i++)
        cout << a[i] << " ";
}

void print(char a[10][9])
{
    for(int i = 9 ; i >= 0 ; i--)
    {
        for(int j = 0 ; j < 9 ; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

bool check(char a[4], char x)
{
    for(int i = 0 ; i < 4 ; i++)
    {
        if (a[i] == x)
            return false;
    }
    return true;
}

int main()
{
    // let computer choose sequence
    char key[4] = {' ',' ',' ',' '}, select;
    srand(time(NULL));

    for(int i = 0 ; i < 4 ; i++)
    {
        do{
            int a = rand()% 6;
            if (a == 0)
                select = 'R';
            else if (a == 1)
                select = 'G';
            else if (a == 2)
                select = 'Y';
            else if (a == 3)
                select = 'B';
            else if (a == 4)
                select = 'W';
            else if (a ==5)
                select = 'P';
        }
        while (!check(key,select));
        key[i] = select;
    }

    // set up grid

    char board[10][9] = {{' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '}};

    //cout << "Welcome to Mastermind! The CPU has selected 4 unique colours from the following:\nRed (R)\nGreen (G)\nYellow (Y)\nBlue (B)\nWhite (W)\nPink (P)\nYou must deduce the colours and the order.\nEach turn you must select 4 colours each turn and you will obtain the accuracy of your guess at the end of your turn:\n1 means right colour, wrong place\n 2 means right colour, right place";
    cout << "Possible colours are R G B Y W P\n";
    char input[4];
    for (int r = 0 ; r < 10 ; r++)
    {
        cout << "\nEnter your colours: ";
        for(int i = 0 ; i < 4 ; i++)
        {
            cin >> input[i];

            while(input[i] != 'R' && input[i] != 'G' && input[i] != 'B' && input[i] != 'Y' && input[i] != 'W' && input[i] != 'P' )
            {
                cout << "Enter a possible colour: ";
                cin >> input[i];
            }
            board[r][i] = input [i];
        }

        bool win = evaluate(key, input, r, board);
        print(board);
        if(win)
        {
            cout << "\nKey: ";
            print (key);
            cout << "\nYOU WIN!\n";
            r = 10;
        }
        //print(key);
    }

    return 0;
}

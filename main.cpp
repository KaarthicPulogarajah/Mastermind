#include <iostream>
#include <stdlib.h> // rand and srand
#include <stdio.h> // NULL
#include <time.h> // time
#include <algorithm> // random shuffle
#include <vector>
#include <windows.h>

using namespace std;

//initialize colours
static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

bool evaluate (char key[4], char a[4], int r, char b[10][9])
{
    srand(time(NULL));
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
    char real[4];
    vector<int> v;

    for(int i = 0 ; i< 4 ;i++)
    {
        int n = rand() %4;
        for(int j = 0 ; j < v.size() ; j++)
        {
            while(n == v.at(j))
            {
                n = rand() %4;
                j = 0;
            }
        }
        v.push_back(n);
    }

    for(int i = 0 ; i < 4 ; i++)
        real[i] = ans[v.at(i)];

    //implement into board array
    for (int i = 0 ; i < 4 ; i++)
        b[r][i+5] = real[i];

    for(int i = 0 ; i < 4 ; i++)
        if(real[i] != '2')
            return false;
    return true;
}

void print (char a[4])
{
    for(int i = 0 ; i < 4 ; i++)
        cout << a[i] << " ";
}

void print(char a[10][9], int turn)
{
    cout << "\nTurn " << turn << ":\n";
    for(int i = 9 ; i >= 0 ; i--)
    {
        for(int j = 0 ; j < 9 ; j++)
        {
            if(a[i][j]== 'R')
                SetConsoleTextAttribute(h,12);
            else if(a[i][j]== 'G')
                SetConsoleTextAttribute(h,10);
            else if(a[i][j]== 'B')
                SetConsoleTextAttribute(h,9);
            else if(a[i][j]== 'Y')
                SetConsoleTextAttribute(h,14);
            else if(a[i][j]== 'W')
                SetConsoleTextAttribute(h,7);
            else if(a[i][j]== 'P')
                SetConsoleTextAttribute(h,13);
            cout << a[i][j] << " ";
            SetConsoleTextAttribute(h,15);
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
    // set etxt colour to white
    SetConsoleTextAttribute(h,15);
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

    cout << "Welcome to Mastermind!\nThe CPU has selected 4 unique colours from the following:\nRed (R)\nGreen (G)\nYellow (Y)\nBlue (B)\nWhite (W)\nPink (P)\nYou have 10 turns to deduce the correct colours in the correct order.\n\nEach turn you must select 4 colours each turn and you will obtain the accuracy of your guess:\n1 means right colour, wrong place\n2 means right colour, right place\nNote: the order of the key does NOT correspond to the entered colours";
    cout << "\n\nPossible colours are R G B Y W P (case sensitive)\n";
    char input[4];
    int turn = 1;
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

        // determine if code has been cracked
        bool win = evaluate(key, input, r, board);
        print(board, turn);
        if(win)
        {
            cout << "\nKey: ";
            print (key);
            cout << "\nYOU WIN!\n";
            r = 10;
        }
        if(!win && turn == 10)
        {
            cout << "\nYOU LOSE!\nKey: ";
            print(key);
        }

        turn++;
    }

    return 0;
}

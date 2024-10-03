#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int checkwin(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return board[i][0];
        }
        else if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return board[0][i];
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return board[0][2];
    }

    return ' ';
}

int checkdraw(char board[3][3])
{
    int freespace = 9;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                freespace--;
            }
        }
    }

    if (freespace == 0)
    {
        return 1;
    }

    return 0;
}

void displayboard(char board[3][3])
{
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

char chooseplayer(char *player1, char *player2)
{
    printf("Player 1, Choose what you want [X or O]: ");
    scanf(" %c", player1);

    if (*player1 == 'X' || *player1 == 'x')
    {
        *player1 = 'X';
        printf("Player 1 is: %c\n", *player1);
        *player2 = 'O';
        printf("Player 2 is: %c\n", *player2);
    }
    else if (*player1 == 'O' || *player1 == 'o')
    {
        *player1 = 'O';
        printf("Player 1 is: %c\n", *player1);
        *player2 = 'X';
        printf("Player 2 is: %c\n", *player2);
    }
    else
    {
        printf("Invalid Input...\n");
        chooseplayer(player1, player2);
    }
}

int playerMove(int number, char board[3][3], char player)
{
    switch (number)
    {
    case 1:
        board[0][0] = player;
        break;
    case 2:
        board[0][1] = player;
        break;
    case 3:
        board[0][2] = player;
        break;
    case 4:
        board[1][0] = player;
        break;
    case 5:
        board[1][1] = player;
        break;
    case 6:
        board[1][2] = player;
        break;
    case 7:
        board[2][0] = player;
        break;
    case 8:
        board[2][1] = player;
        break;
    case 9:
        board[2][2] = player;
        break;
    }
}

void resetboard(char board[3][3])
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

int main()
{
    char player1, player2;
    char dpboard[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

    static int ply1 = 0, ply2 = 0;
    int *ptrnum1 = &ply1;
    int *ptrnum2 = &ply2;

    chooseplayer(&player1, &player2);
    displayboard(dpboard);

    printf("Remember the numbers placing.\n");
    printf("Press Any Key To Start.");
    getch();
    printf("\n");

    int i = 1, gameloop = 1;
    int num, gamewin = 0, gamedraw = 0;
    while (1)
    {
        i++;
        if (i % 2 == 0)
        {
            do
            {
                printf("Player 1, your turn: ");
                scanf("%d", &num);
                if (num >= 10)
                {
                    printf("\nInvalid Input.\n");
                }
                else if (board[(num - 1) / 3][(num - 1) % 3] != ' ')
                {
                    printf("Position is occupied.\n");
                }
                else
                {
                    break;
                }
            } while (num >= 10 || board[(num - 1) / 3][(num - 1) % 3] != ' ');
            playerMove(num, board, player1);
            displayboard(board);
            gamedraw = checkdraw(board);
            if (gamedraw)
            {
                printf("Match draw.\n");
                break;
            }
            gamewin = checkwin(board);
            if (gamewin != ' ')
            {
                printf("Player %c has won the match.\n", player1);
                (*ptrnum1)++;
                break;
            }
        }
        else
        {
            do
            {
                printf("Player 2, your turn: ");
                scanf("%d", &num);
                if (num >= 10)
                {
                    printf("\nInvalid Input.\n");
                }
                else if (board[(num - 1) / 3][(num - 1) % 3] != ' ')
                {
                    printf("Position is occupied.\n");
                }
                else
                {
                    break;
                }
            } while (num >= 10 || board[(num - 1) / 3][(num - 1) % 3] != ' ');
            playerMove(num, board, player2);
            displayboard(board);
            gamedraw = checkdraw(board);
            if (gamedraw)
            {
                printf("Match draw.\n");
                break;
            }
            gamewin = checkwin(board);
            if (gamewin != ' ')
            {
                printf("Player %c has won the match.\n", player2);
                (*ptrnum2)++;
                break;
            }
        }
    }

    printf("Player 1 score = %d \t Player 2 score = %d\n", ply1, ply2);

    printf("Press 1 to start a new game. OR Press 0 to Exit: ");
    scanf("%d", &gameloop);

    if (gameloop == 0)
    {
        return 0;
    }
    else
    {
        resetboard(board);
        return main();
    }

    return 0;
}

//BINGO PROBLEM............
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
        int num;
        int key;
    } element;
element bingo[5][5];

int bingo_count = 0, player_count, call, row[5], col[5], dd[2];         //dd, col, row to keep track of which row or col or dd is cut
char BINGO[6] = "BINGO";

void print();               //prints matrix
void shuffle();             //shuffles the matrix and sets row, col, dd matrix  to 0
void cut();
void print_BINGO();
short int row_check();
short int col_check();
short int diagonal_check();

int main()
{
    srand(time(NULL));
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0 ; j<5 ; j++)
        {
            bingo[i][j].num = 5*i+j+1;
            bingo[i][j].key = 1;
        }
    }
    shuffle();
    print();

    player_input:
    printf("Do you want to play first (type 0) or let your opponent play first? (type 1) \n");
    scanf("%d", &player_count);
    while (bingo_count < 5)
    {
        if (player_count == 0)
        {
            printf("Your Number: ");
            player_count++;
        }
        else if (player_count == 1)
        {
            printf("Opponent's Number: ");
            player_count--;
        }
        else
        {
            printf("Wrong Entry, Please Input again....\n");
            goto player_input;
        }
        cut();

        printf("\n\n");
        print();
        printf("\n\n");
        
        if (row_check())
        {
            bingo_count++;
            print_BINGO();
        }
        if (col_check())
        {
            bingo_count++;
            print_BINGO();
        }
        if (diagonal_check())
        {
            bingo_count++;
            print_BINGO();
        }

    }
    printf("You Won........\n");

}

void print()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (bingo[i][j].key == 1)
            printf("%d\t", bingo[i][j].num);
            else
            printf("*\t");
        }
        printf("\n\n");
    }
}

void shuffle()
{
    int s, t, temp;
    for (int i = 0; i < 100; i++)
    {
        s = (rand()%25);
        t = (rand()%25);

        temp = bingo[s/5][s%5].num;
        bingo[s/5][s%5].num = bingo[t/5][t%5].num;
        bingo[t/5][t%5].num = temp;
     
    }
    for (int i = 0; i < 5; i++)
    {
        col[i] = 0; row[i] = 0;
    }
    dd[0] = 0;
    dd[1] = 0;
}

void cut()
{
    input_call_again:
        scanf("%d", &call);
        if (call > 25 || call <= 0)
        {
            printf("Wrong Entry, Please Input again....\n");
            goto input_call_again;
        }
        for (int i = 0; i < 5; i ++)
        {
            for (int j = 0 ; j < 5; j++)
            {
                if ((bingo[i][j].num == call)&&(bingo[i][j].key == 1))
                {
                    bingo[i][j].key = 0;
                }
                else if ((bingo[i][j].num == call)&&(bingo[i][j].key == 0))
                {
                    printf("Wrong Entry, Please Input again....\n");
                    goto input_call_again;
                }
            }
        }
}

short int col_check()
{
    int counter = 0;
    for (int i = 0; i < 5; i++)
    {
        if (col[i] == 1)
            continue;
             
        for (int j = 0; j < 5; j++)
        {
            if (bingo[j][i].key == 1)
                break;
            else if (bingo[j][i].key == 0)
            {
                counter++;
                if (counter == 5)
                {
                    col[i] = 1;
                    return 1;
                }
                else 
                    continue;
            }
        }
        counter = 0;
    }
    return 0;
}

short int row_check()
{
    int counter = 0;
    for (int i = 0; i < 5; i++)
    {
        if (row[i] == 1)
            continue;
        for (int j = 0; j < 5; j++)
        {
            if (bingo[i][j].key == 1)
                break;
            else if (bingo[i][j].key == 0)
            {
                counter++;
                if (counter == 5)
                {
                    row[i] = 1;
                    return 1;
                }
                else 
                    continue;
            }
        }
        counter = 0;
    }
    return 0;
}

short int diagonal_check()
{
    int counter = 0;
    if (dd[0] == 0)
    {
        for (int i = 0; i < 5; i++)
        {
            if (bingo[i][i].key == 0)
            {
                counter++;
                if (counter == 5)
                {
                    dd[0] = 1;
                    return 1;
                }
            }
        }
        counter = 0;
    }
    if (dd[1] == 0)
    {
        for (int i = 0; i < 5; i++)
        {
            if (bingo[i][4-i].key == 0)
            {
                counter++;
                if (counter == 5)
                {
                    dd[1] = 1;
                    return 1;
                }
            }
            else
                break;
        }
        counter = 0;
    }
    return 0;
}

void print_BINGO()
{
    printf("\n");
    for (int i = 0; i < bingo_count ; i++)
    {
        printf("%c\t", BINGO[i]);
    }
    printf("\n\n");
}
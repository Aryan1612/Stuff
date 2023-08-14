//BINGO PROBLEM ADVANCED............
// here I am trying to know if a randomly generated matrix for bingo has higher chances of winning than an orderly generated matrix
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


typedef struct {
        int num;
        int key;
    } element;
element bingo_unordered[5][5], bingo_ordered[5][5];

int bingo_count1[3] = {1, 0, 0}, bingo_count2[3] = {2, 0, 0}, call, row1[5], col1[5], dd1[2], row2[5], col2[5], dd2[5], count = 100, tie = 0;         //dd, col, row to keep track of which row or col or dd is cut
//char BINGO[6] = "BINGO";

void print();               //prints matrix
void shuffle();             //shuffles the matrix and sets row, col, dd matrix  to 0
void cut();
//void print_BINGO(int bingo_count[2]);
short int row_check(element bingo[5][5], int row[5]);
short int col_check(element bingo[5][5], int col[5]);
short int diagonal_check(element bingo[5][5], int dd[2]);

int main()
{
    while(count--)
    {
        sleep(1);
        srand(time(NULL));
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0 ; j<5 ; j++)
        {
            bingo_unordered[i][j].num = 5*i+j+1;    bingo_ordered[i][j].num = 5*i+j+1;
            bingo_unordered[i][j].key = 1;          bingo_ordered[i][j].key = 1;
        }
    }
    shuffle();
    //printf("\n\n");
    //print();

    //printf("Enter a Number \n");
    while (1)
    {
        cut();

        //printf("\n\n");
        //print();
        //printf("\n\n");
        
        if (row_check(bingo_unordered, row1))
        {
            bingo_count1[1]++;
            //print_BINGO(bingo_count1);
        }
        if (col_check(bingo_unordered, col1))
        {
            bingo_count1[1]++;
            //print_BINGO(bingo_count1);
        }
        if (diagonal_check(bingo_unordered, dd1))
        {
            bingo_count1[1]++;
            //print_BINGO(bingo_count1);
        }
        if (row_check(bingo_ordered, row2))
        {
            bingo_count2[1]++;
            //print_BINGO(bingo_count2);
        }
        if (col_check(bingo_unordered, col2))
        {
            bingo_count2[1]++;
            //print_BINGO(bingo_count2);
        }
        if (diagonal_check(bingo_ordered, dd2))
        {
            bingo_count2[1]++;
            //print_BINGO(bingo_count2);
        }

        if (bingo_count1[1] >= 5 && bingo_count2[1] >= 5) 
        {
            //printf("Both WON simultaneously.\n");
            tie++;
            bingo_count1[1] = bingo_count2[1] = 0;
            break;
        } 
        else if (bingo_count1[1] >= 5) 
        {
            //printf("Unordered wins!!!\n");
            bingo_count1[2]++;
            bingo_count1[1] = bingo_count2[1] = 0;
            break;
        } 
        else if (bingo_count2[1] >= 5) 
        {
            //printf("Ordered wins!!!\n");
            bingo_count2[2]++;
            bingo_count1[1] = bingo_count2[1] = 0;
            break;
        }
    }

}
printf("RANDOM - %d\nORDERED - %d\nTIE - %d\n\n", bingo_count1[2], bingo_count2[2], tie);
}


void print()
{
    printf("UNORDERED...\t\t\t\t\t\tORDERED...\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (bingo_unordered[i][j].key == 1)
            printf("%d\t", bingo_unordered[i][j].num);
            else
            printf("*\t");
        }
        printf("\t\t");
        for (int j = 0; j < 5; j++)
        {
            if (bingo_ordered[i][j].key == 1)
            printf("%d\t", bingo_ordered[i][j].num);
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

        temp = bingo_unordered[s/5][s%5].num;
        bingo_unordered[s/5][s%5].num = bingo_unordered[t/5][t%5].num;
        bingo_unordered[t/5][t%5].num = temp;
     
    }
    for (int i = 0; i < 5; i++)
    {
        col1[i] = 0; row1[i] = 0; col2[i] = 0; row2[i] = 0;
    }
    dd1[0] = 0; dd2[0] = 0;
    dd2[1] = 0; dd2[1] = 0;
}

void cut()
{
    input_call_again:
        call = (rand()%25);
        //scanf("%d", &call);
        if (call > 25 || call <= 0)
        {
            //printf("Wrong Entry, Please Input again....\n");
            goto input_call_again;
        }
        //printf("call = %d\n", call);
        for (int i = 0; i < 5; i ++)
        {
            for (int j = 0 ; j < 5; j++)
            {
                if ((bingo_unordered[i][j].num == call)&&(bingo_unordered[i][j].key == 1))
                {
                    bingo_unordered[i][j].key = 0;
                }
                else if ((bingo_unordered[i][j].num == call)&&(bingo_unordered[i][j].key == 0))
                {
                    //printf("Already Cut!!!!\n");
                    goto input_call_again;
                }
                if ((bingo_ordered[i][j].num == call)&&(bingo_ordered[i][j].key == 1))
                {
                    bingo_ordered[i][j].key = 0;
                }
                else if ((bingo_ordered[i][j].num == call)&&(bingo_ordered[i][j].key == 0))
                {
                    //printf("Already Cut!!!!\n");
                    goto input_call_again;
                }
            }
        }
}

short int col_check(element bingo[5][5], int col[5])
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

short int row_check(element bingo[5][5], int row[5])
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

short int diagonal_check(element bingo[5][5], int dd[2])
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

/*void print_BINGO(int bingo_count[2])
{
    printf("\n");
     if ( bingo_count[0] == 1)
        {
            printf("For Unordered Matrix: \n\n");
        }
    else if (bingo_count[0] == 2)
        {
            printf("For Ordered Matrix: \n\n");
        }
    for (int i = 0; i < bingo_count[1] ; i++)
    {
        printf("%c\t\t",BINGO[i]);
    }
    printf("\n");
}*/

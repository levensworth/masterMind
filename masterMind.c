#include <stdio.h>
#include "getnum.h"
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
// this game was created by Santiago Bassani for educational purposes
// function prototypes

int amountCorrect(int input[], int num[]);
int amountRegular(int input[], int num[]);
int matchNumber(int input[], int num[]);
int readNumber(int num[], int lvl);
int verifyNum(int num[]);
int askNum(int num[],int lvl);
int choseLvl(void);
void generateRandom(int num[],int lvl);
void printWelcome(void);
int main (void)
{
  printWelcome();

  int lvl = choseLvl();
  int num[lvl];
  int jug[lvl];

  generateRandom(num,lvl);

  printf("\n" );
  int playing = 1;
  int counter = 0;
  while(playing)
  {
    readNumber(jug,lvl);
    if(counter == lvl)
      playing = 0;

    if(matchNumber(jug, num))
    {
        printf("WIN!!!\n");
        playing = 0;
    }
    else
      counter++;

  }

  printf("END OF GAME , LOSER!\n" );
  return 0;
}

void printWelcome(void)
{
  printf("MASTER MIND\n" );
  printf("created by Santiago Bassani\n" );
  printf("date: 10/9/2016\n" );

  printf("RULES:\n");
  printf("-> SELECT A LEVEL ( THIS WILL SET THE AMOUNT OF CHANCES YOU CAN GUESS)\n");
  printf("-> THE COMPUTER WILL TELL EACH TIME HOW MANY NUMBERS YOU GOT RIGHT (CORRECTS)\n");
  printf("    AND HOW MANY ARE IN THE NUMBER BUT IN OTHER POSSITION (REGULAR).\n");
  printf("-> HAVE FUN!\n");

}

int amountCorrect(int input[], int num[])
{
  int counter = 0;
  for(int i = 0; input[i] >= 0; i++)
    if(input[i] == num[i])
      counter++;

  return counter;
}

int amountRegular(int input[], int num[])
{
  int counter = 0;

  for(int i = 0; input[i] >= 0; i++)
    for(int j = 0; num[j] >= 0; j++)
      if(num[j] == input[i] && i!=j)
        counter++;

  return counter;
}

int matchNumber(int input[], int num[])
{
  int good = amountCorrect(input, num);
  int regular = amountRegular(input,num);
  int wrong = 0;

  int found = 0;
  for(int i = 0; input[i] >= 0; i++)
  {
    found = 0;
    for(int j = 0; num[j] >= 0 && !found; j++)
      if(input[i] == num[j])
        found = 1;

    if(!found)
      wrong++;

  }// end for


  if(wrong == 0)
    return 1;
  else
    printf("%d correct %d regular\n", good, regular );
  return 0;
}

int readNumber(int num[],int lvl)
{
  printf("Enter a positive %d digits positive int with no equal digits \n",lvl );
  int check;
  do
  {
      check = askNum(num,lvl);
      if(check)
        check = verifyNum(num);
        if(!check)
          printf("invalid number\n" );




  }while( !check);

  return 1;
}

int verifyNum(int num[])
{
  int i, j, found = 0;

  for(i = 0; num[i] >= 0; i++)
  {
    found = 0;
    for(j = i; num[j] >= 0 && !found; j++)
      if(num[j] == num[i] && i != j)
        found = 1;

    if(found)
      return 0;
  }//end for

  return 1;
}


int askNum(int num[],int lvl)
{
  int c;
  int valid = 1;
  int i = 0;
  while((c = getchar()) != '\n' && valid)
  {
    if(isdigit(c) && i <= lvl)
      num[i++] = c - '0';
    else
      valid = 0;

  }

  if(valid)
    num[i] = -1;
  else
    return 0;


  return 1;
}


int choseLvl(void)
{
  int choice = -1;

  while(choice < 0 || choice > 10)
    choice = getint("enter the level number [1 - 10] =  ");

  return choice;
}

void generateRandom(int num[],int lvl)
{
  int i, j;
  int aux, index;
  srand(time(NULL));
  for(i = rand(), j=0; j < lvl; j++, i++)
    num[j] = i % 10;

  for(i = 0; i < lvl; i++)
  {
    aux = num[i];
    index = rand() % lvl;
    num[i] = num[index];
    num[index] = aux;

  }
  num[i] = -1;
}

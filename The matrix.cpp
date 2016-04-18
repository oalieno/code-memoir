#include<iostream>
#include<time.h>
#include<windows.h>
#define HIGH 25
#define WEIGH 40

using namespace std;

struct{
  COORD where;
  int length_total;
  int length_now;
  int color_change;
  int color_now;
  int control;//increase or decrease
}matrix[WEIGH];

int main()
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    int i,j;
    int word;
    srand(time(NULL));
    for(i=0;i<WEIGH;i++){
        matrix[i].length_now=0;
        matrix[i].where.X=2*i;
        matrix[i].length_now=1;
        matrix[i].control=1;
        matrix[i].color_now=10;
        matrix[i].where.Y=rand()%HIGH;
        matrix[i].length_total=rand()%(HIGH-matrix[i].where.Y)+1;
        matrix[i].color_change=matrix[i].where.Y+rand()%(matrix[i].length_total+1);
    }
    while(1){
        for(i=0;i<WEIGH;i++){
            if(matrix[i].length_now < 0){
                matrix[i].length_now=1;
                matrix[i].control=1;
                matrix[i].color_now=2;
                matrix[i].where.Y=rand()%HIGH;
                matrix[i].length_total=rand()%(HIGH-matrix[i].where.Y)+1;
                matrix[i].color_change=matrix[i].where.Y+rand()%(matrix[i].length_total+1);
            }
            if(matrix[i].control == 1){
                SetConsoleTextAttribute(hout,15);
                SetConsoleCursorPosition(hout,matrix[i].where);
                cout << rand()%2;
                if(matrix[i].length_now != 1){
                     SetConsoleTextAttribute(hout,matrix[i].color_now);
                     matrix[i].where.Y--;
                     SetConsoleCursorPosition(hout,matrix[i].where);
                     cout << rand()%2;
                     matrix[i].where.Y++;
                }
            }
            else{
                SetConsoleCursorPosition(hout,matrix[i].where);
                cout << " ";
            }
            if(matrix[i].length_now == matrix[i].length_total){
            matrix[i].control=-1;
            matrix[i].where.Y-=matrix[i].length_total;
            }
            matrix[i].length_now+=matrix[i].control;
            matrix[i].where.Y+=1;
            if(matrix[i].where.Y+1 >= matrix[i].color_change){
                matrix[i].color_now=12-matrix[i].color_now;
                matrix[i].color_change=100;
            }
        }
        Sleep(100);
    }
    return 0;
}

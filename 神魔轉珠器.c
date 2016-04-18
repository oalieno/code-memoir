#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define PACE 15
//上 0 下 1 左 2 右 3
//水 0 火 1 木 2 光 3 暗 4 心 5
void in();
void out();
void slip(int,int,int);
void change(int,int,int,int);
void dig(int,int);
int clear();

int map[5][6];
int imap[5][6];
int jmap[5][6];
int best_map[5][6];
int block[5][6]; 
int pace[25];
int best_pace[25];
int max=0;
int hand_x,hand_y;
int act;
int study;
int my;
int block_len;
int block_x[10];
int block_y[10]; 
int color[7];
int best_color[6];
int limit;

int main(int argc, char *argv[])
{
  int i,j;
  char action;  
  color[6]=1;
  printf("=============== 說明書 ===============\n\n");
  printf("座標x為直的\n座標y為橫的\n\n");
  printf("屬性轉數字表如下:\n水 0 火 1 木 2 光 3 暗 4 心 5");
  printf("\n\n(按任意鍵繼續)");
  action=getch();
  system("cls");
  while(1){
    max=0;
    my=0;
    in();
    for(i=0;i<5;i++){
      for(j=0;j<6;j++){
        if(block[i][j] == 0){ 
          slip(i,j,0);        
        } 
      }      
    }
    out();
  }
  return 0;
}
void in(void){
  int i,j;
  printf("請輸入珠珠圖:\n");
  for(i=0;i<5;i++){
    for(j=0;j<6;j++){
      scanf("%d",&map[i][j]);      
    }      
  }
  printf("最多要幾combo?");
  scanf("%d",&study);     
  printf("有幾顆風化珠?(沒有請輸入0)");
  scanf("%d",&block_len); 
  if(block_len > 0 && block_len <= 10){
    for(i=0;i<block_len;i++){
      printf("第%d組風化珠(x,y):",i+1); 
      scanf("%d %d",&block_x[i],&block_y[i]);
      block_x[i]--;
      block_y[i]--;      
    }         
  }
  else{
    block_len=0;     
  }
  for(i=0;i<5;i++){
    for(j=0;j<6;j++){
      block[i][j]=0;      
    }      
  }
  for(i=0;i<block_len;i++){
    block[block_x[i]][block_y[i]]=1;      
  } 
  printf("你有一定要消啥嗎?(沒有請輸6)");
  scanf("%d",&limit); 
}
void out(void){
  int i,j;
  printf("combo最高:%d\n",max);
  printf("起手珠:%d %d",hand_x,hand_y);
  printf("路徑如下:");
  for(i=0;i<act;i++){
    if(best_pace[i] == 0){
      printf("上");     
    }
    if(best_pace[i] == 1){
      printf("下");     
    }
    if(best_pace[i] == 2){
      printf("左");     
    }
    if(best_pace[i] == 3){
      printf("右");     
    }      
  }
  printf("\n");
  printf("完成圖:\n");
  for(i=0;i<5;i++){
    for(j=0;j<6;j++){
      printf("%d ",best_map[i][j]);      
    }
    printf("\n");      
  }
  printf("\n");
  printf("水屬性消了%dcombo\n",best_color[0]);
  printf("火屬性消了%dcombo\n",best_color[1]);
  printf("木屬性消了%dcombo\n",best_color[2]);
  printf("光屬性消了%dcombo\n",best_color[3]);
  printf("暗屬性消了%dcombo\n",best_color[4]);
  printf("心屬性消了%dcombo\n",best_color[5]);  
  printf("\n");  
}
void slip(int x,int y,int move){
  int combo;
  int bug;
  int i,j;
  combo=0;
  if(max < study){
    combo=clear();
  }
  if(max == study){
    move=100;     
  }
  if(combo > max && color[limit] != 0){
    for(i=0;i<6;i++){
      best_color[i]=color[i];      
    }
    act=move;
    max=combo;     
    for(i=0;i<move;i++){
      best_pace[i]=pace[i];      
    }
    hand_x=x+1;
    hand_y=y+1;
    for(i=move-1;i>=0;i--){
      if(pace[i] == 0){
        hand_x++;     
      }
      else if(pace[i] == 1){
        hand_x--;     
      }
      else if(pace[i] == 2){
        hand_y++;     
      }
      else if(pace[i] == 3){
        hand_y--;     
      }      
    }
    for(i=0;i<5;i++){
      for(j=0;j<6;j++){
        best_map[i][j]=map[i][j];      
      }      
    }
    if(my < 1){
      max=0;
      my++;     
    }
  }
  bug=move-1;
  if(bug >= 0){
    bug=pace[bug];       
  }
  else{
    bug=100;
  }
  if(move < PACE){
    if(x > 0 && bug != 1 && block[x-1][y] == 0){
      pace[move]=0;
      change(x,y,x-1,y);
      slip(x-1,y,move+1);
      change(x,y,x-1,y);     
    } 
    if(x < 4 && bug != 0 && block[x+1][y] == 0){
      pace[move]=1;
      change(x,y,x+1,y);
      slip(x+1,y,move+1);
      change(x,y,x+1,y);     
    }
    if(y > 0 && bug != 3 && block[x][y-1] == 0){
      pace[move]=2;
      change(x,y,x,y-1);
      slip(x,y-1,move+1);
      change(x,y,x,y-1);     
    }
    if(y < 5 && bug != 2 && block[x][y+1] == 0){
      pace[move]=3;
      change(x,y,x,y+1);
      slip(x,y+1,move+1);
      change(x,y,x,y+1);     
    }       
  }   
}
int clear(void){
  int i,j,k;
  int key;
  int combo;
  for(i=0;i<6;i++){
    color[i]=0;      
  }
  combo=0;
  for(i=0;i<5;i++){
    for(j=0;j<6;j++){
      jmap[i][j]=map[i][j];      
    }      
  }
  while(1){
           
  key=0;
  for(i=0;i<5;i++){
    for(j=0;j<6;j++){
      imap[i][j]=6;      
    }      
  }
  for(i=0;i<5;i++){
    for(j=0;j<6;j++){
      if(jmap[i][j] == 6){
        continue;     
      }
      if(i > 0 && i < 4){
        if(jmap[i][j] == jmap[i+1][j] && jmap[i][j] == jmap[i-1][j]){
          imap[i][j]=jmap[i][j];
          key++;
          continue;       
        }     
      }
      if(j > 0 && j < 5){
        if(jmap[i][j] == jmap[i][j+1] && jmap[i][j] == jmap[i][j-1]){
          imap[i][j]=jmap[i][j];
          key++;
          continue;     
        }      
      }
      if(i > 1){
        if(jmap[i][j] == jmap[i-1][j] && jmap[i][j] == jmap[i-2][j]){
          imap[i][j]=jmap[i][j];
          key++; 
          continue;    
        }     
      }
      if(i < 3){
        if(jmap[i][j] == jmap[i+1][j] && jmap[i][j] == jmap[i+2][j]){
          imap[i][j]=jmap[i][j];
          key++;
          continue;     
        }     
      }
      if(j > 1){
        if(jmap[i][j] == jmap[i][j-1] && jmap[i][j] == jmap[i][j-2]){
          imap[i][j]=jmap[i][j];
          key++;
          continue;     
        }      
      }
      if(j < 4){
        if(jmap[i][j] == jmap[i][j+1] && jmap[i][j] == jmap[i][j+2]){
          imap[i][j]=jmap[i][j];
          key++;
          continue;     
        }     
      }      
    }      
  }
  if(key == 0){
    break;     
  }
  for(i=0;i<5;i++){
    for(j=0;j<6;j++){
      if(imap[i][j] != 6){
        for(k=i-1;k>=0;k--){
          jmap[k+1][j]=jmap[k][j];        
        }
        jmap[0][j]=6;       
      }      
    }      
  }
  for(i=0;i<5;i++){
    for(j=0;j<6;j++){
      if(imap[i][j] != 6){
        color[imap[i][j]]++;
        dig(i,j);
        combo++;       
      }      
    }      
  }
  
  }
  return combo;                 
}
void change(int x,int y,int m,int n){
  int a;
  a=map[x][y];
  map[x][y]=map[m][n];
  map[m][n]=a;         
}
void dig(int x,int y){
  int a;
  a=imap[x][y];
  imap[x][y]=6;
  if(x < 4 && a == imap[x+1][y]){
    dig(x+1,y);     
  }
  if(x > 0 && a == imap[x-1][y]){
    dig(x-1,y);     
  }
  if(y < 5 && a == imap[x][y+1]){
    dig(x,y+1);     
  }
  if(x > 0 && a == imap[x][y-1]){
    dig(x,y-1);     
  }         
}

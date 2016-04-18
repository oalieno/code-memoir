#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <conio.h>
////////////////////////////////神獸基本資料格式//////////////////////////////// 
struct God{
  char name[10];
  int hp;
  int attack;
  int level;
  int exp;
  int no;
  struct God *next;
  struct God *prev;
};
////////////////////////////////神獸基本資料格式////////////////////////////////



///////////////////////////////////子函數定義/////////////////////////////////// 
void monster_transfer(struct God*,struct God*);
void monster_information();
void packets_information();
void shop_information();
void first_shop();
void second_shop();
void start_word(int);
void guidebook();
void hit_monster();
void level_up();
void stop();
struct God* monster_no_address(int);
///////////////////////////////////子函數定義/////////////////////////////////// 



////////////////////////////////////全域變數//////////////////////////////////// 
int i=0;
int money;
int ball_normal;
int ball_super;
int monster_amount;
int monster_max;
FILE *file; 
struct God *temp;
struct God *monster_head;
struct God *monster_end;
struct God *monster_main;
struct God enemy_table[10]={{"網路",250,25,1,5,1},
                    {"歷史",150,25,1,5,2},
                    {"數學",400,20,1,5,3},
                    {"英文",200,30,1,5,4},
                    {"公民",150,40,1,5,5},
                    {"一中",350,20,1,5,6},
                    {"205",300,30,1,5,7},
                    {"外星人",400,35,1,5,8},
                    {"奇行種",100,100,1,5,9},
                    {"哈哈",2000,5,1,5,10}};
////////////////////////////////////全域變數//////////////////////////////////// 



/////////////////////////////////////主函式///////////////////////////////////// 
int main()
{ 
  ////////////////////////////////////////
  srand(time(NULL));
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  monster_head=(struct God*)malloc(sizeof(struct God));
  monster_end=monster_head;
  monster_main=monster_head;
  monster_head->next=NULL;
  monster_head->prev=NULL;
  ////////////////////////////////////////
  
  //////////////讀入神獸資料////////////// 
  file=fopen("monster_data.txt","r");
  if(file == NULL){ 
    fclose(file);          
    strcpy(monster_head->name,"鋼鐵人");
    monster_head->hp=500;
    monster_head->attack=30;
    monster_head->level=1;
    monster_head->exp=5;
    monster_head->no=0;
    monster_amount=1;
    guidebook();
    system("cls");
    printf("\n\n\n\n\n\n新手歡迎喔~\n\n享受你的旅程吧!!\n\n\nby 趙偉捷......"); 
  }/*沒有資料->初始*/
  else{
    i=0; 
    while(fscanf(file,"%s\t%d\t%d\t%d\t%d\t%d",monster_end->name,&monster_end->hp,&monster_end->attack,&monster_end->level,&monster_end->exp,&monster_end->no) != EOF){
      i++;
      monster_end->next=(struct God*)malloc(sizeof(struct God));
      monster_end->next->prev=monster_end;
      monster_end=monster_end->next;         
    }
    monster_amount=i;               
    monster_end=monster_end->prev;
    free(monster_end->next);
    monster_end->next=NULL;
    fclose(file);
  }/*有資料->讀入*/
  //////////////讀入神獸資料////////////// 
  
  //////////////讀入背包資料////////////// 
  file=fopen("packets.txt","r");
  if(file == NULL){
    fclose(file);
    money=0;
    monster_max=5;
    ball_normal=0;
    ball_super=0;       
  }/*沒有資料->初始*/
  else{
    fscanf(file,"%d\t%d\t%d\t%d",&monster_max,&money,&ball_normal,&ball_super);
    fclose(file);     
  }/*有資料->讀入*/
  //////////////讀入背包資料////////////// 
  
  ////////////////////////////////////////
  char action;
  int arrowhead=1;
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  while(1){
    ////////////////////
    system("cls");
    start_word(arrowhead);
    ////////////////////
    
    ////////////////////
    action=getch();
    ////////////////////
    
    ////////離開////////
    if(action == 'X'){
      system("cls"); 
      printf("\n真的要離開?");
      action=getch();
      if(action == 'Z'){
        break;     
      }    
    }
    ////////離開////////
    
    ////////確定////////
    else if(action == 'Z'){
      //////////
      if(arrowhead == 1){
        system("cls");
        hit_monster();
        stop();
      }
      //////////
      
      ////////// 
      else if(arrowhead == 2){
        monster_information();         
      }
      //////////
      
      //////////
      else if(arrowhead == 3){
        packets_information();     
      }
      //////////
      
      //////////
      else if(arrowhead == 4){
        shop_information();       
      }
      //////////
      
      //////////
      else if(arrowhead == 5){
        system("cls");
        printf("===============圖鑑===============");
        printf("\n\n");
        printf("編號\t名稱\t等級\t生命值\t攻擊力\n");
        printf("0\t鋼鐵人\t1\t500\t30\n");
        for(i=0;i<10;i++){
          printf("%d\t%s\t1\t%d\t%d\t\n",i+1,enemy_table[i].name,enemy_table[i].hp,enemy_table[i].attack);      
        }
        stop();        
      }
      //////////
      
      //////////
      else if(arrowhead == 6){
        file=fopen("monster_data.txt","w");
        temp=monster_head;
        for(i=0;i<monster_amount;i++){
          fprintf(file,"%s\t%d\t%d\t%d\t%d\t%d\r\n",temp->name,temp->hp,temp->attack,temp->level,temp->exp,temp->no);
          temp=temp->next;      
        }
        fclose(file);
        file=fopen("packets.txt","w");
        fprintf(file,"%d\t%d\t%d\t%d",monster_max,money,ball_normal,ball_super);
        fclose(file);     
      }
      //////////       
      
      //////////
      else if(arrowhead == 7){
        guidebook();  
      }
      //////////
    }
    ////////確定////////
    
    /////////上///////// 
    else if(action == 'I'){
      if(arrowhead > 1)
      arrowhead--;          
    }
    /////////上/////////
    
    /////////下/////////
    else if(action == 'K'){
      if(arrowhead < 7)
      arrowhead++;  
    }
    /////////下/////////
  }
  ////////////////////////////////////////
  
  ///////////////釋放記憶體/////////////// 
  temp=monster_end;
  for(i=0;i<monster_amount-1;i++){
    temp=temp->prev;
    free(temp->next);      
  }
  free(monster_head);
  ///////////////釋放記憶體/////////////// 
  
  ////////////////離開程式//////////////// 
  system("cls");
  printf("\n下次再見囉!\n\n");
  system("pause");
  return 0;
  ////////////////離開程式////////////////  
}
/////////////////////////////////////主函式///////////////////////////////////// 



//////////////////////////////子函式(顯示背包資料)////////////////////////////// 
void packets_information(void){
  ////////////////////////////////////////
  char action;
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  system("cls");
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  printf("===============背包資料===============");
  printf("\n\n");
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  printf("錢:%d\n",money);
  printf("普通球:%d顆\n",ball_normal);
  printf("高級球:%d顆",ball_super);
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  stop();
  ////////////////////////////////////////
}
//////////////////////////////子函式(顯示背包資料)////////////////////////////// 



////////////////////////////////子函式(顯示商店)////////////////////////////////
void shop_information(void){
  ////////////////////////////////////////
  char action;
  int arrowhead=1;
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  while(1){
    ////////////////////
    system("cls");
    ////////////////////      
           
    ////////////////////
    printf("===============歡迎光臨商店街===============");
    printf("\n\n");
    ////////////////////
    
    ////////////////////
    if(arrowhead == 1){
      printf("*");
    }
    else{
      printf(" ");
    }
    printf("1.神獸球專賣店\n");
    ////////////////////
    
    ////////////////////
    if(arrowhead == 2){
      printf("*");
    }
    else{
      printf(" ");
    }
    printf("2.道具專賣店\n");
    ////////////////////
    
    ////////////////////
    action=getch();
    ////////////////////
    
    ////////////////////
    if(action == 'Z'){
      //////////
      if(arrowhead == 1){
        first_shop();     
      }
      //////////
      
      //////////
      else if(arrowhead == 2){
        system("cls"); 
        printf("\n(尚未開張)\n");
        action=getch();     
      }     
      //////////
    }
    ////////////////////
   
    ////////////////////
    else if(action == 'X'){
      break;     
    }
    ////////////////////
    
    ////////////////////
    else if(action == 'I'){
      if(arrowhead > 1){
        arrowhead--;     
      }     
    }
    ////////////////////
    
    ////////////////////
    else if(action == 'K'){
      if(arrowhead < 2){
        arrowhead++;     
      }     
    }
    ////////////////////
  }
  ////////////////////////////////////////     
} 
////////////////////////////////子函式(顯示商店)////////////////////////////////



////////////////////////////////子函式(第一家店)////////////////////////////////
void first_shop(void){
  ////////////////////////////////////////
  char action;
  int arrowhead=1;
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  printf("\n你好!我是阿超!\n");
  action=getch();
  printf("你想買點什麼嗎?");
  action=getch(); 
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  while(1){
    ////////////////////
    system("cls");    
    ////////////////////
    
    ////////////////////
    printf("===============神獸球專賣店===============");
    printf("\n\n");
    //////////////////// 
    
    ////////////////////
    if(arrowhead == 1){
      printf("*");
    }
    else{
      printf(" ");
    }
    printf("1.普通球:300元\n");
    ////////////////////  
    
    ////////////////////
    if(arrowhead == 2){
      printf("*");
    }
    else{
      printf(" ");
    }
    printf("2.高級球:500元\n");
    ////////////////////
    
    ////////////////////
    action=getch();
    ////////////////////
    
    ////////////////////
    if(action == 'X'){
      printf("\n要再回來喔!");
      action=getch();
      break;     
    }
    ////////////////////
    
    ////////////////////
    else if(action == 'Z'){
      if(arrowhead == 1){
        if(money >= 300){
          printf("\n你買了一個普通球!");     
          ball_normal++;
          money-=300;
          stop();
        }
        else{
          printf("\n錢不夠!!");
          stop();     
        }     
      }
      else if(arrowhead == 2){
        if(money >= 500){
          printf("\n你買了一個高級球!");     
          ball_super++;
          money-=500;
          stop();
        }
        else{
          printf("\n錢不夠!!");
          stop();     
        }     
      }     
    }
    ////////////////////
    
    ////////////////////
    else if(action == 'I'){
      if(arrowhead > 1){
        arrowhead--;     
      }     
    }
    ////////////////////
    
    //////////////////// 
    else if(action == 'K'){
      if(arrowhead < 2){
        arrowhead++;     
      }      
    }
    ////////////////////
  }
  ////////////////////////////////////////     
}
////////////////////////////////子函式(第一家店)////////////////////////////////



////////////////////////////////子函式(第二家店)////////////////////////////////
void second_shop(void){
  ////////////////////////////////////////
  char action;
  int arrowhead=1;
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  while(1){
    ////////////////////
    system("cls");    
    ////////////////////
    
    ////////////////////
    printf("===============道具專賣店===============");
    printf("\n\n");
    ////////////////////
    
    ////////////////////
    if(arrowhead == 1){
      printf("*");
    }
    else{
      printf(" ");
    }
    printf("1.\n");
    ////////////////////  
    
    ////////////////////
    action=getch();
    ////////////////////
    
    ////////////////////
    if(action == 'X'){
      printf("\n要再回來喔!");
      action=getch();
      break;     
    }
    ////////////////////
    
    ////////////////////
    else if(action == 'Z'){
      if(arrowhead == 1){
             
      }     
    }
    ////////////////////
    
    ////////////////////
    else if(action == 'I'){
      if(arrowhead > 1){
        arrowhead--;     
      }     
    }
    ////////////////////
    
    //////////////////// 
    else if(action == 'K'){
      if(arrowhead < 1){
        arrowhead++;     
      }      
    }
    ////////////////////    
  }
  ////////////////////////////////////////          
}
////////////////////////////////子函式(第二家店)////////////////////////////////



//////////////////////////////////子函式(暫停)////////////////////////////////// 
void stop(void){
  ////////////////////////////////////////
  char stop;
  stop=getch();
  ////////////////////////////////////////     
}
//////////////////////////////////子函式(暫停)////////////////////////////////// 



////////////////////////////////子函式(等級上升)//////////////////////////////// 
void level_up(void){
  ////////////////////////////////////////
  monster_main->level++;
  monster_main->exp+=monster_main->level*5;
  monster_main->hp+=monster_main->level*10;
  monster_main->attack+=monster_main->level;
  ////////////////////////////////////////      
}
////////////////////////////////子函式(等級上升)////////////////////////////////



//////////////////////////////子函式(神獸資料轉移)////////////////////////////// 
void monster_transfer(struct God *origin,struct God *copy){
  ////////////////////////////////////////
  strcpy(copy->name,origin->name);
  copy->hp=origin->hp;
  copy->attack=origin->attack;
  copy->level=origin->level;
  copy->exp=origin->exp;
  copy->no=origin->no;
  ////////////////////////////////////////     
}
//////////////////////////////子函式(神獸資料轉移)////////////////////////////// 



///////////////////////////子函式(神獸編號與位置轉移)/////////////////////////// 
struct God* monster_no_address(int num){
  ////////////////////////////////////////
  temp=monster_head;
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  for(i=0;i<num-1;i++){
    temp=temp->next;
  }
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  return temp;      
  ////////////////////////////////////////
}
///////////////////////////子函式(神獸編號與位置轉換)/////////////////////////// 



////////////////////////////////子函式(開頭文字)//////////////////////////////// 
void start_word(int arrowhead){
  ////////////////////////////////////////
  printf("===============歡迎來到神獸世界!!==============="); 
  printf("\n\n");
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  if(arrowhead == 1){
    printf("*");
  }
  else{
    printf(" ");
  }
  printf("1.打怪\n");
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  if(arrowhead == 2){
    printf("*");
  }
  else{
    printf(" ");
  }
  printf("2.神獸\n");
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  if(arrowhead == 3){
    printf("*");
  }
  else{
    printf(" ");
  }
  printf("3.背包\n");
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  if(arrowhead == 4){
    printf("*");
  }
  else{
    printf(" ");
  }
  printf("4.商店\n");
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  if(arrowhead == 5){
    printf("*");
  }
  else{
    printf(" ");
  }
  printf("5.圖鑑\n");
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  if(arrowhead == 6){
    printf("*");
  }
  else{
    printf(" ");
  }
  printf("6.存檔\n");
  ////////////////////////////////////////    
  
  ////////////////////////////////////////
  if(arrowhead == 7){
    printf("*");
  }
  else{
    printf(" ");
  }
  printf("7.說明書\n");
  ////////////////////////////////////////
}
////////////////////////////////子函式(開頭文字)//////////////////////////////// 



//////////////////////////////子函式(顯示神獸資料)////////////////////////////// 
void monster_information(void){
  ////////////////////////////////////////
  char action;
  char fuck[5]="%0";
  int a=0;
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  while(1){
    ////////////////////
    system("cls");
    ////////////////////
    
    ////////////////////
    printf("===============神獸資料===============");
    printf("\n\n");
    ////////////////////
    
    printf("背包有%d格\n\n",monster_max);
    
    ////////////////////
    printf("編號\t名稱\t等級\t生命值\t攻擊力\n");
    ////////////////////
    
    ////////////////////
    temp=monster_head;
    for(i=0;i<monster_amount;i++){
      if(temp == monster_main){
        printf("*");     
      }
      else{
        printf(" ");     
      }
      printf("%d\t%s\t%d\t%d\t%d\t\n",temp->no,temp->name,temp->level,temp->hp,temp->attack);
      if(i != monster_amount-1){
        temp=temp->next;
      }      
   }
     ////////////////////
   
    /////////////////////
    action=getch();
    /////////////////////
    
    /////////////////////
    if(action == 'X'){
      break;     
    }
    ////////////////////
    
    ////////////////////
    else if(action == 'Z'){
      //////////
      system("cls");
      //////////
      
      //////////
      if(monster_main->no == 0){
        if(monster_main->level < 5){
          printf("\n等級太低不能看小知識喔~");     
        }
        if(monster_main->level >= 5){
          printf("\n你知道嗎?\n\n鋼鐵人首次出場於(懸疑故事)第39期(1963年3月)");     
        }
        if(monster_main->level >= 15){
             
        }
        stop();     
      }
      //////////
      
      //////////
      else if(monster_main->no == 1){
        if(monster_main->level < 5){
          printf("\n等級太低不能看小知識喔~");     
        }
        if(monster_main->level >= 5){
          printf("\n你知道嗎?\n\n用https能更安全的上網喔\n下次用他看臉書吧!!");     
        }
        if(monster_main->level >= 15){
             
        }
        stop();          
      }
      //////////
      
      //////////
      else if(monster_main->no == 2){
        if(monster_main->level < 5){
          printf("\n等級太低不能看小知識喔~");     
        }
        if(monster_main->level >= 5){
             
        }
        if(monster_main->level >= 15){
             
        }
        stop();          
      }
      //////////
      
      //////////
      else if(monster_main->no == 3){
        if(monster_main->level < 5){
          printf("\n等級太低不能看小知識喔~");     
        }
        if(monster_main->level >= 5){
             
        }
        if(monster_main->level >= 15){
             
        }
        stop();          
      }
      //////////
      
      //////////
      else if(monster_main->no == 4){
        if(monster_main->level < 5){
          printf("\n等級太低不能看小知識喔~");     
        }
        if(monster_main->level >= 5){
             
        }
        if(monster_main->level >= 15){
             
        }
        stop();          
      }
      //////////
      
      //////////
      else if(monster_main->no == 5){
        if(monster_main->level < 5){
          printf("\n等級太低不能看小知識喔~");     
        }
        if(monster_main->level >= 5){
             
        }
        if(monster_main->level >= 15){
             
        }          
      }
      //////////
      
      //////////
      else if(monster_main->no == 6){
        if(monster_main->level < 5){
          printf("\n等級太低不能看小知識喔~");     
        }
        if(monster_main->level >= 5){
          printf("\n你知道嗎?\n\n台中一中孕育了好多好多的天才 ex:趙偉捷XD");     
        }
        if(monster_main->level >= 15){
             
        }
        stop();          
      }
      //////////
      
      //////////
      else if(monster_main->no == 7){
        if(monster_main->level < 5){
          printf("\n等級太低不能看小知識喔~");     
        }
        if(monster_main->level >= 5){
                                    
        }
        if(monster_main->level >= 15){
             
        }
        stop();          
      }
      //////////
      
      //////////
      else if(monster_main->no == 8){
        if(monster_main->level < 5){
          printf("\n等級太低不能看小知識喔~");     
        }
        if(monster_main->level >= 5){
          printf("\n你知道嗎?\n\n每天向外星人禱告可以獲得祝福喔~");     
        }
        if(monster_main->level >= 15){
             
        }
        stop();          
      }
      //////////
      
      //////////
      else if(monster_main->no == 9){
        if(monster_main->level < 5){
          printf("\n等級太低不能看小知識喔~");     
        }
        if(monster_main->level >= 5){
          printf("\n你知道嗎\n\n...BJ4");     
        }
        if(monster_main->level >= 15){
             
        }
        stop();          
      }
      //////////
      
      //////////
      else if(monster_main->no == 10){
        if(monster_main->level < 5){
          printf("\n等級太低不能看小知識喔~");     
        }
        if(monster_main->level >= 5){
          printf("\n你知道嗎?\n\n每天多笑能活得更長壽喔，讓我們一起大笑三聲吧!!");     
        }
        if(monster_main->level >= 15){
             
        }
        stop();          
      }
      //////////       
    }
    ////////////////////
   
    ////////////////////
    else if(action == 'I'){
      if(monster_main->prev != NULL){
      monster_main=monster_main->prev;     
      }
    }
    ////////////////////
  
    ////////////////////
    else if(action == 'K'){ 
      if(monster_main->next != NULL){
        monster_main=monster_main->next;                                     
      }
    }
    ////////////////////
  
    ////////////////////
    else if(action == 'A'){
      //////////
      printf("\n擴增背包2000元??");
      //////////
    
      //////////
      action=getch();
      //////////
    
      //////////
      if(action == 'Z'){
        if(money >= 2000){
          printf("\n你擴增了背包!!");
          money-=2000;
          monster_max++;     
        }
        else{
          printf("\n錢不夠!!");     
        }   
      }
      //////////
      
      //////////
      else if(action == 'X'){
        printf("\n沒有擴增背包!!");     
      }
      //////////
    
      //////////
      printf("\n(再按一下回神獸資料)");
      stop();
      //////////     
    }
    ////////////////////
    
    ////////////////////
    else if(action == 'S'){
      printf("你想把%s放生嗎?\n",monster_main->name);
      action=getch();
      if(action == 'Z'){
        if(monster_main == monster_head){
          a++;
          printf("\n你確定要這樣做????");
          action=getch();
          if(action == 'Z'){
            printf("\n\n(按任意鍵去吃屎!!)");
            stop();
            file=fopen("0000.cmd","w");
            fprintf(file,"start \"吃屎吧\" %s",fuck);
            fclose(file);
            system("start """" 0000.cmd");
            system("del 0000.cmd");          
          }
          else{
            if(monster_main == monster_head){
              printf("\n\n偉大的鋼鐵人勉強接受了你的道歉!!");
              stop();     
            }     
          }     
        }
        else if(monster_main == monster_end){
          printf("再見了%s!",monster_main->name);
          monster_end=monster_end->prev;
          monster_main=monster_main->prev;
          free(monster_end->next);
          monster_end->next=NULL;     
        }
        else{
          printf("再見了%s!",monster_main->name); 
          temp=monster_main;      
          monster_main=temp->next;
          temp->prev->next=monster_main;
          monster_main->prev=temp->prev;
          free(temp);
        }
        if(a == 0){
          monster_amount--;
          stop();
        }
      }
      else{
        printf("\n%s高興得撲向你的懷抱!!",monster_main->name);
        stop();     
      }
      a=0;       
    }
    ////////////////////
  }
  ////////////////////////////////////////
}
//////////////////////////////子函式(顯示神獸資料)////////////////////////////// 



//////////////////////////////////子函式(打怪)////////////////////////////////// 
void hit_monster(void){
  ////////////////////////////////////////
  int round;
  int enemy_no;
  int whether_catch;
  char action;
  struct God enemy;
  struct God me;
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  printf("===============進入戰鬥===============");
  printf("\n\n");
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  enemy_no=rand()%10;
  round=1;
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  monster_transfer(&enemy_table[enemy_no],&enemy);
  monster_transfer(monster_main,&me);
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  printf("你碰到%s了\n",enemy.name);
  printf("你派出了%s應戰\n",me.name);
  ////////////////////////////////////////
  
  ////////////////////////////////////////
  while(1){
    ////////////////////
    action=getch();
    ////////////////////
    
    ////////////////////
    if(action == 'X'){
      printf("\n(在按一下回主畫面)");
      break;     
    }
    ////////////////////
    
    ////////////////////
    else if(action == 'Z'){
      //////////
      printf("\nRound%d:\n",round);
      //////////
      
      //////////
      if(enemy.hp < me.attack){
        enemy.hp=0;      
      }
      else{
        enemy.hp-=me.attack;     
      }
      //////////
      
      //////////
      printf("你攻擊對方%d點\n",me.attack);
      printf("你剩%d滴血\t%s剩%d滴血\n",me.hp,enemy.name,enemy.hp);
      //////////
      
      //////////
      if(enemy.hp == 0){
        printf("\n%s獲勝!!\n",me.name);
        monster_main->exp-=5;
        if(monster_main->exp <= 0){
          level_up();
          printf("\n@@@等級上升了@@@\n");     
        }
        money+=20; 
        break;       
      }
      //////////
      
      //////////
      if(me.hp < enemy.attack){
        me.hp=0;      
      }
      else{
        me.hp-=enemy.attack;     
      }
      //////////
      
      //////////
      printf("%s攻擊你%d點\n",enemy.name,enemy.attack);
      printf("你剩%d滴血\t%s剩%d滴血\n",me.hp,enemy.name,enemy.hp);          
      //////////
      
      //////////
      if(me.hp == 0){
        printf("\n%s陣亡!!\n",me.name);
        break;       
      }
      //////////
      
      //////////
      round++; 
      //////////
    }
    ////////////////////
    
    ////////////////////
    else if(action == 'A'){
      if(monster_amount == monster_max){
        printf("\n你的袋子滿了!\n\n");     
      }
      else{
        printf("\n你要使用什麼球呢(1:普通球 2:高級球)?");     
        action=getche();
        if(action == 49){
          if(ball_normal < 1){
            printf("\n沒有普通球了!\n\n");     
          }
          else{
            whether_catch=rand()%10;
            if(whether_catch == 0){
              monster_end->next=(struct God*)malloc(sizeof(struct God));
              monster_end->next->prev=monster_end;
              monster_end=monster_end->next;
              monster_end->next=NULL;
              monster_transfer(&enemy_table[enemy_no],monster_end);
              monster_amount++;
              ball_normal--;
              printf("\n恭喜你捉到了%s!!\n\n",enemy.name);
              break;       
            }
            else{
              ball_normal--; 
              printf("\n捕捉失敗!!\n\n");     
            }       
          }     
        }
        else if(action == 50){
          if(ball_super < 1){
            printf("\n沒有高級球了!\n\n");     
          }
          else{
            whether_catch=rand()%5;
            if(whether_catch == 0){
              monster_end->next=(struct God*)malloc(sizeof(struct God));
              monster_end->next->prev=monster_end;
              monster_end=monster_end->next;
              monster_end->next=NULL;
              monster_transfer(&enemy_table[enemy_no],monster_end);
              monster_amount++;
              ball_super--;
              printf("\n恭喜你捉到了%s!!\n\n",enemy.name);
              break;       
            }
            else{
              ball_super--;
              printf("\n捕捉失敗!!\n\n");     
            }     
          }     
        }
      }
    }
    ////////////////////
  }
  ////////////////////////////////////////       
} 
//////////////////////////////////子函式(打怪)//////////////////////////////////
 
/////////////////////////////////子函式(說明書)/////////////////////////////////  
void guidebook(void){
  system("cls");
  printf("===============說明書===============");
  printf("\n\n");
  printf("所有頁面中:\n按Z:確定\n按X:離開\n按I:上\n按K:下\n\n(以下是特殊鍵)\n\n在背包時:\n按A:擴增背包\n按S:丟棄神獸\n\n在打怪時:\n按A:抓怪");        
  printf("\n\n在神獸達一定等級時可以按神獸看偉捷小常識喔:))");
  stop();
}
/////////////////////////////////子函式(說明書)/////////////////////////////////

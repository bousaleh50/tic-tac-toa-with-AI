#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <cstdlib>
using namespace std;
char board[3][3]={
   {'1','2','3'},
   {'4','5','6'},
   {'7','8','9'}
};
char brd[3][3];
int lenght=9;
char is_draw[9];
char player='x';
bool gameOver=false;
bool draw=false;

class pos{
 public:
     int i,j;
};

/*-----------------------------START---------------------------------------------------------------------------------------*/
bool ismoveleft(char T[3][3]){
 for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
        if(T[i][j]!='o' && T[i][j]!='x')
            return true;
    }
 }
 return false;
}

char winner(char board[3][3]){
 if(board[0][0]==board[0][1] && board[0][1]==board[0][2]){
    return board[0][0];
  }else if(board[1][0]==board[1][1] && board[1][1]==board[1][2]){
    return board[1][0];
  }else if(board[2][0]==board[2][1] && board[2][1]==board[2][2]){
    return board[2][0];
  }else if(board[0][0]==board[1][0] && board[1][0]== board[2][0]){
    return board[0][0];
  }else if(board[0][1]==board[1][1] && board[1][1]==board[2][1]){
     return board[0][1];
  }else if(board[0][2]==board[1][2] && board[1][2]==board[2][2]){
    return board[0][2];
  }else if(board[0][0]==board[1][1] && board[1][1]==board[2][2]){
      return board[0][0];
  }else if(board[0][2]==board[1][1] && board[1][1]==board[2][0]){
     return board[0][2];
  }

//this the problem that i faced the winner function should at list return something if there is no winner
  return ' ';
}

int minimax(char T[3][3],int depth,bool ismax){
 if(winner(T)=='x'){
    return 10-depth;
 }
 if(winner(T)=='o')
    return -10+depth;
 if(ismoveleft(T)==false)
    return 0;
 if(ismax){
    int bestscore=-1000;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(T[i][j]!='x' && T[i][j]!='o'){
                char cp=T[i][j];
                T[i][j]='x';
                bestscore=max(bestscore,minimax(T,depth+1,false));
                T[i][j]=cp;
            }
        }
    }
    return bestscore;
 }else{
    int bestscore=1000;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(T[i][j]!='x' && T[i][j]!='o'){
                char cp=T[i][j];
                T[i][j]='o';
                bestscore=min(bestscore,minimax(T,depth+1,true));
                T[i][j]=cp;
            }
        }
    }
    return bestscore;
 }
}

pos findebestmove(char T[3][3]){
  int bestscore=1000;
  pos mov;
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
        if(T[i][j]!='x' && T[i][j]!='o'){
            char cp=board[i][j];
            board[i][j]='o';
            int score=minimax(T,0,true);
            board[i][j]=cp;
            if(score<bestscore){
                bestscore=score;
                mov.i=i;
                mov.j=j;
            }
        }
    }
  }
  return mov;
}

/*-----------------------------END---------------------------------------------------------------------------------------*/

/*----------------------------- get the available  position from the board and stocking it in the is_draw array-----------*/



void fullarray(){
   int cpt=0;
   for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
        if(board[i][j]!='o' && board[i][j]!='x'){
            is_draw[cpt]=board[i][j];
        }
        cpt++;
    }
   }
}
void Delete(char x){
   for(int i=0;i<lenght;i++){
    if(is_draw[i]==x){
        is_draw[i]=is_draw[lenght-1];
        lenght--;
    }
   }
}
/*--------------------------------------------------END-------------------------------------------------*/
void copy_board(){
   for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
        brd[i][j]=board[i][j];
    }
   }
}
void pnt(){
   system("cls");
   for(int i=0;i<3;i++){;
        cout<<"--------------"<<endl;

    for(int j=0;j<3;j++){
        cout<<board[i][j]<<"   |";
    }
    cout<<endl;
   }
   cout<<"--------------"<<endl;
}

void inpt(char plr){
    char ch;
//AI choice random spot to play
    if(plr=='o'){
        /*srand(time(0));
        int choise=rand()%lenght;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]==is_draw[choise]){
                    board[i][j]='o';
                    Delete(is_draw[choise]);
                    return;
                }
            }
        }*/

//if you want to make this AI smarter just comment the above code and uncomment this one
        pos t=findebestmove(board);
        board[t.i][t.j]='o';
        int ctr=0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(i==t.i && j==t.j){
                    Delete(is_draw[ctr]);
                }
                ctr++;
            }
        }
        return;
    }
    cout<<"player "<<plr<<" your turn"<<endl;
    cin>>ch;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(ch==board[i][j]){
                    board[i][j]=plr;
                    Delete(ch);
                    return;
                }
            }
        }
}

char check_winner(){

// locking for a winner

 if(board[0][0]==board[0][1] && board[0][1]==board[0][2]){
    gameOver=true;
    return board[0][0];
  }else if(board[1][0]==board[1][1] && board[1][1]==board[1][2]){
    gameOver=true;
    return board[1][0];
  }else if(board[2][0]==board[2][1] && board[2][1]==board[2][2]){
    gameOver=true;
    return board[2][0];
  }else if(board[0][0]==board[1][0] && board[1][0]== board[2][0]){
    gameOver=true;
    return board[0][0];
  }else if(board[0][1]==board[1][1] && board[1][1]==board[2][1]){
     gameOver=true;
     return board[0][1];
  }else if(board[0][2]==board[1][2] && board[1][2]==board[2][2]){
    gameOver=true;
    return board[0][2];
  }else if(board[0][0]==board[1][1] && board[1][1]==board[2][2]){
      gameOver=true;
      return board[0][0];
  }else if(board[0][2]==board[1][1] && board[1][1]==board[2][0]){
     gameOver=true;
     return board[0][2];
  }else{
       //switch between the players
       //next turn
        if(player=='o'){
         player='x';
       }else{
         player='o';
       }
  }
}


//restart the game if there is a draw
void reset(){
  char restart;
      cout<<endl<<"Do you want to restart the game [y/n]"<<endl;
      cin>>restart;
      if(restart!='y' && restart!='n')
        reset();
      if(restart=='y'){
        lenght=9;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                board[i][j]=brd[i][j];
            }
        }
        fullarray();
      }else{
        draw=true;
        gameOver=true;
      }
}




int main()
{
    //full is_draw array with available positions or moves
    fullarray();

    //copy the original board array in another array to restart the game later
    copy_board();

    while(!gameOver){
        //if the length of the is_draw arra less or equal to 0 that is mean there is no available moves
        //if that so and there is no winner that is mean is draw case and then restart the game

        if(lenght<=0){
            cout<<"\n\n\noops! its draw Nice game"<<endl;
            reset();
        }
        pnt();
        inpt(player);
        check_winner();
    }
    pnt();
    if(draw){
        cout<<"\n\n\ngame over its a draw"<<endl;
    }else{
        cout<<"\n\n\ngame over player "<<player<<" is the winner"<<endl;

    }
    return 0;
}

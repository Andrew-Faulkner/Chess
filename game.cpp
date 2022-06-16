/// change the name to work w coloured pieces
/// generate piece list from board
/// get board and peices in position w bounding boxes
// get piece selection working
// add game logic
// ability to check mate

#include <math.h>
#include "mathLib3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void printboard(string board[8][8]){
  for(int x=0; x<8;x++){
      cout<<"["<<board[x][0]<<","<<board[x][1]<<","<<board[x][2]<<","<<board[x][3]<<","<<board[x][4]<<","<<board[x][5]<<","<<board[x][6]<<","<<board[x][7]<<"]"<<endl;
    }
}
void copyboard(string board1[8][8],string board2[8][8]){
    for(int x=0; x<8;x++){
        for(int y=0; y<8;y++){
          board2[x][y]=board1[x][y];
        }
    }

}
void FillPM(string Posboard[8][8],vector<string>& validmoves ){
    for(int x=0; x<8;x++){
        for(int y=0; y<8;y++){
          if(Posboard[x][y]=="C"||Posboard[x][y]=="X"){
            string Sx=to_string(x+1);
            string Sy=to_string(y+1);
            string move=Sx+","+Sy;
            validmoves.push_back(move);
          }
        }
    }
  //  for (string i :validmoves ) {
//        cout << i << "  ";
  //    }
}

///Shows all posible moves with captures highlighted w a "C"
void showMoves(string board[8][8],string tile, vector<string>&possiblemoves){
int x=-1+(tile[0]-'0');
int y=-1+(tile[2]-'0');
bool white = true;
bool enemy = true;  /// where this is use replace w a check of is this piece opposite colour
bool firstmove= true;
string possibleboard[8][8];
copyboard(board,possibleboard);
cout<<possibleboard[x][y]<<endl;


/// black pawn moves
if(possibleboard[x][y]=="P" && white==true){
  if(x+1<=7){
  if(possibleboard[x+1][y]=="O"){
    possibleboard[x+1][y]="X";
  }}
  if(x+2<=7){
  if(possibleboard[x+2][y]=="O" && white==true && x==1){
    possibleboard[x+2][y]="X";
  }}
  if(y+1<=7 && x+1<=7){
  if(possibleboard[x+1][y+1]!="O"&& white==true && enemy==true){
    possibleboard[x+1][y+1]="C";
  }}
  if(y-1>=0 && x+1<=7){
    if(possibleboard[x+1][y-1]!="O"&& white==true && enemy==true){
      possibleboard[x+1][y-1]="C";
    }
  }
}
///Possible knight moves
if(possibleboard[x][y]=="N"){
  if(x+2<=7 && y+1<=7){
  if(possibleboard[x+2][y+1]=="O"){
    possibleboard[x+2][y+1]="X";
    if(enemy==true){possibleboard[x+2][y+1]="C";}
  }
}
if(x+2<=7 && y-1>=0){
if(possibleboard[x+2][y-1]=="O"||enemy==true){
  possibleboard[x+2][y-1]="X";
  if(enemy==true){possibleboard[x+2][y-1]="C";}
}}
if(x-2>=0 && y+1<=7){
if(possibleboard[x-2][y+1]=="O"||enemy==true){
  possibleboard[x-2][y+1]="X";
  if(enemy==true){possibleboard[x-2][y+1]="C";}
}}
if(x-2>=0 && y-1>=0){
if(possibleboard[x-2][y-1]=="O"||enemy==true){
  possibleboard[x-2][y-1]="X";
  if(enemy==true){possibleboard[x-2][y-1]="C";}
}}
if(x-1>=0 && y+2<=7){
if(possibleboard[x-1][y+2]=="O"||enemy==true){
  possibleboard[x-1][y+2]="X";
  if(enemy==true){possibleboard[x-1][y+2]="C";}
}}
if(x-1>=0 && y-2>=0){
if(possibleboard[x-1][y-2]=="O"||enemy==true){
  possibleboard[x-1][y-2]="X";
  if(enemy==true){possibleboard[x-1][y-2]="C";}
}}
if(x+1<=7 && y+2<=7){
if(possibleboard[x+1][y+2]=="O"||enemy==true){
  possibleboard[x+1][y+2]="X";
  if(enemy==true){possibleboard[x+1][y+2]="C";}
}}

if(x+1<=7 && y-2>=0){
if(possibleboard[x+1][y-2]=="O"||enemy==true){
  possibleboard[x+1][y-2]="X";
  if(enemy==true){possibleboard[x+1][y-2]="C";}
}}
}
/// ROOK MOVES  3
if(possibleboard[x][y]=="R"||possibleboard[x][y]=="Q"||possibleboard[x][y]=="K"){

  for(int i=x+1;i<=7;i++){
    if(possibleboard[i][y]=="O"){
      possibleboard[i][y]="X";
      if(possibleboard[x][y]=="K"){break;}}
    else{
      // recognize allys or enenmies
      possibleboard[i][y]="C";
      break;
    }}

    for(int i=x-1;i>=0;i--){
      if(possibleboard[i][y]=="O"){
        possibleboard[i][y]="X";
      if(possibleboard[x][y]=="K"){break;}}
      else{
        possibleboard[i][y]="C";
        break;
      }}

      for(int i=y+1;i<=7;i++){
        if(possibleboard[x][i]=="O"){
          possibleboard[x][i]="X";
        if(possibleboard[x][y]=="K"){break;}}
        else{
          possibleboard[x][i]="C";
          break;
        }}
        for(int i=y-1;i>=0;i--){
          if(possibleboard[x][i]=="O"){
            possibleboard[x][i]="X";
          if(possibleboard[x][y]=="K"){break;}}
          else{
            possibleboard[x][i]="C";
            break;
          }}


}
/// BISHOP MOVES
if(possibleboard[x][y]=="B"||possibleboard[x][y]=="Q"||possibleboard[x][y]=="K"){

  for(int i=1;x+i<=7 && y+i<=7;i++){
    if(possibleboard[x+i][y+i]=="O"){
      possibleboard[x+i][y+i]="X";
    if(possibleboard[x][y]=="K"){break;}}
    else{
      possibleboard[x+i][y+i]="C";
      break;
    }}
    for(int i=1;x-i>=0 && y-i>=0;i++){
      if(possibleboard[x-i][y-i]=="O"){
        possibleboard[x-i][y-i]="X";
      if(possibleboard[x][y]=="K"){break;}}
      else{
        possibleboard[x-i][y-i]="C";
        break;
      }}
      for(int i=1;x-i>=0 && y+i<=7;i++){
        if(possibleboard[x-i][y+i]=="O"){
          possibleboard[x-i][y+i]="X";
        if(possibleboard[x][y]=="K"){break;}}
        else{
          possibleboard[x-i][y+i]="C";
          break;
        }}
        for(int i=1;x+i<=7 && y-i>=0 ;i++){
          if(possibleboard[x+i][y-i]=="O"){
            possibleboard[x+i][y-i]="X";
          if(possibleboard[x][y]=="K"){break;}}
          else{
            possibleboard[x+i][y-i]="C";
            break;
          }}

}


//printboard(possibleboard);
FillPM(possibleboard,possiblemoves);
}

/// shows all squares where an enemy could capture to be used for checkmating
void showDanger(string board[8][8],string tile, vector<string>&possiblemoves){
int x=-1+(tile[0]-'0');
int y=-1+(tile[2]-'0');
bool white = true;
bool enemy = true;  /// where this is use replace w a check of is this piece opposite colour
bool firstmove= true;
string possibleboard[8][8];
copyboard(board,possibleboard);
cout<<possibleboard[x][y]<<endl;


/// black pawn moves
if(possibleboard[x][y]=="P" && white==true){
  if(y+1<=7 && x+1<=7){
  if(possibleboard[x+1][y+1]!="O"&& white==true && enemy==true){
    possibleboard[x+1][y+1]="C";
  }}
  if(y-1>=0 && x+1<=7){
    if(possibleboard[x+1][y-1]!="O"&& white==true && enemy==true){
      possibleboard[x+1][y-1]="C";
    }
  }
}
///Possible knight moves
if(possibleboard[x][y]=="N"){
  if(x+2<=7 && y+1<=7){
  if(possibleboard[x+2][y+1]=="O"){
    possibleboard[x+2][y+1]="C";
    if(enemy==true){possibleboard[x+2][y+1]="C";}
  }
}
if(x+2<=7 && y-1>=0){
if(possibleboard[x+2][y-1]=="O"||enemy==true){
  possibleboard[x+2][y-1]="C";
  if(enemy==true){possibleboard[x+2][y-1]="C";}
}}
if(x-2>=0 && y+1<=7){
if(possibleboard[x-2][y+1]=="O"||enemy==true){
  possibleboard[x-2][y+1]="C";
  if(enemy==true){possibleboard[x-2][y+1]="C";}
}}
if(x-2>=0 && y-1>=0){
if(possibleboard[x-2][y-1]=="O"||enemy==true){
  possibleboard[x-2][y-1]="C";
  if(enemy==true){possibleboard[x-2][y-1]="C";}
}}
if(x-1>=0 && y+2<=7){
if(possibleboard[x-1][y+2]=="O"||enemy==true){
  possibleboard[x-1][y+2]="C";
  if(enemy==true){possibleboard[x-1][y+2]="C";}
}}
if(x-1>=0 && y-2>=0){
if(possibleboard[x-1][y-2]=="O"||enemy==true){
  possibleboard[x-1][y-2]="C";
  if(enemy==true){possibleboard[x-1][y-2]="C";}
}}
if(x+1<=7 && y+2<=7){
if(possibleboard[x+1][y+2]=="O"||enemy==true){
  possibleboard[x+1][y+2]="C";
  if(enemy==true){possibleboard[x+1][y+2]="C";}
}}

if(x+1<=7 && y-2>=0){
if(possibleboard[x+1][y-2]=="O"||enemy==true){
  possibleboard[x+1][y-2]="C";
  if(enemy==true){possibleboard[x+1][y-2]="C";}
}}
}
/// ROOK MOVES  3
if(possibleboard[x][y]=="R"||possibleboard[x][y]=="Q"||possibleboard[x][y]=="K"){

  for(int i=x+1;i<=7;i++){
    if(possibleboard[i][y]=="O"){
      possibleboard[i][y]="C";
      if(possibleboard[x][y]=="K"){break;}}
    else{
      // recognize allys or enenmies
      possibleboard[i][y]="C";
      break;
    }}

    for(int i=x-1;i>=0;i--){
      if(possibleboard[i][y]=="O"){
        possibleboard[i][y]="C";
      if(possibleboard[x][y]=="K"){break;}}
      else{
        possibleboard[i][y]="C";
        break;
      }}

      for(int i=y+1;i<=7;i++){
        if(possibleboard[x][i]=="O"){
          possibleboard[x][i]="C";
        if(possibleboard[x][y]=="K"){break;}}
        else{
          possibleboard[x][i]="C";
          break;
        }}
        for(int i=y-1;i>=0;i--){
          if(possibleboard[x][i]=="O"){
            possibleboard[x][i]="C";
          if(possibleboard[x][y]=="K"){break;}}
          else{
            possibleboard[x][i]="C";
            break;
          }}


}
/// BISHOP MOVES
if(possibleboard[x][y]=="B"||possibleboard[x][y]=="Q"||possibleboard[x][y]=="K"){

  for(int i=1;x+i<=7 && y+i<=7;i++){
    if(possibleboard[x+i][y+i]=="O"){
      possibleboard[x+i][y+i]="C";
    if(possibleboard[x][y]=="K"){break;}}
    else{
      possibleboard[x+i][y+i]="C";
      break;
    }}
    for(int i=1;x-i>=0 && y-i>=0;i++){
      if(possibleboard[x-i][y-i]=="O"){
        possibleboard[x-i][y-i]="C";
      if(possibleboard[x][y]=="K"){break;}}
      else{
        possibleboard[x-i][y-i]="C";
        break;
      }}
      for(int i=1;x-i>=0 && y+i<=7;i++){
        if(possibleboard[x-i][y+i]=="O"){
          possibleboard[x-i][y+i]="C";
        if(possibleboard[x][y]=="K"){break;}}
        else{
          possibleboard[x-i][y+i]="C";
          break;
        }}
        for(int i=1;x+i<=7 && y-i>=0 ;i++){
          if(possibleboard[x+i][y-i]=="O"){
            possibleboard[x+i][y-i]="C";
          if(possibleboard[x][y]=="K"){break;}}
          else{
            possibleboard[x+i][y-i]="C";
            break;
          }}

}


//printboard(possibleboard);
FillPM(possibleboard,possiblemoves);
}

bool findmove(string tile,vector<string>&moves){

  bool found=false;
  for (string i :moves ) {

      if(i[0]==tile[0]){

        found=true;
        return found;
      }
    }
  return false;
}
void makeMove(string board[8][8],string tile,string tile2, vector<string>& moves){
  int x1=-1+(tile[0]-'0');
  int y1=-1+(tile[2]-'0');
  int x2=-1+(tile2[0]-'0');
  int y2=-1+(tile2[2]-'0');
  printf("make move ran");
  if(findmove(tile2,moves)==true){
  board[x2][y2]=board[x1][y1];
  board[x1][y1]="O";}

  else
  printf("move not valid!!!");

}

void listpiecelocations(string board[8][8],vector<string>&Locations,bool white){
  for(int x=0; x<8;x++){
      for(int y=0; y<8;y++){
        if(board[x][y]!="O"&& white==true){
          string Sx=to_string(x+1);
          string Sy=to_string(y+1);
          string Piece=Sx+","+Sy;
          Locations.push_back(Piece);
        }
      }
  }
}
void generatealldangertiles(string board[8][8],vector<string>&Locations,vector<string>&allpossiblemoves){

  listpiecelocations(board,Locations,true);
    for (string i :Locations ) {
        cout << i << "  ";
      }

  for (string i : Locations ) {
      showMoves(board,i,allpossiblemoves);
    }
    /// all possible moves is filled with every move that can be made

    printf("\n now display all possible moves");
    for (string i :allpossiblemoves ) {
        cout << i << "  ";
      }
}

int main(int argc, char** argv)
{
string n,n1;
string board[8][8]={
{"R","N","B","K","Q","B","N","R"},
{"P","P","P","P","P","P","P","P"},
{"O","O","O","O","O","O","O","O"},
{"O","O","O","O","O","O","O","O"},
{"O","O","O","O","O","O","O","O"},
{"O","O","O","O","O","O","O","O"},
{"O","O","O","O","O","O","O","O"},
{"O","O","O","K","O","O","O","O"}};
vector<string> possiblemoves;
vector<string> locations;


//while(true){
printboard(board);
possiblemoves.clear();
locations.clear();
generatealldangertiles(board,locations,possiblemoves);

//cout << "See possible moves for: "; // no flush needed
//cin >> n1;
//showMoves(board,n1,possiblemoves);
//cout << "What move would you like to make: "; // no flush needed
//cin >> n;
//makeMove(board,n1,n,possiblemoves);
//possiblemoves.clear();


printf("\n");
//}
	return(0);					//return may not be necessary on all compilers
}

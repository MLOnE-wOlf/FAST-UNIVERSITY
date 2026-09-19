#include <iostream>
#include <cstdlib>
#include "Connect4Game.h"

using namespace std;

void Connect4Game::initBoard(int size){
  this->SIZE = size;
  this->board = new int*[size];
  for(int i=0; i<size; i++){
    this->board[i] = new int[size];
    for(int j=0; j<size; j++)
      this->board[i][j] = 0;
  }
}

void Connect4Game::showBoard(){
   for (int r = 0; r < SIZE; r++){
      cout << "+";
      for (int c = 0; c < SIZE; c++)
         cout << "---+";
      cout << "\n";

      cout << "| ";
      for (int c = 0; c < SIZE; c++)
         cout << board[r][c] << " | ";
      cout << "\n";
    }

   cout << "+";
   for (int c = 0; c < SIZE; c++)
      cout << "---+";
   cout << "\n";

   cout << "  ";
   for (int c = 0; c < SIZE; c++)
      cout << c << "   ";
   cout << "\n\n";
}

void Connect4Game::insertValue(int pos){
  int row = rowsLeft(pos);
  if(pos < 0 || pos >= SIZE || row < 0){
    cout << "Invalid Position. Try again.";
    return;
  }
  this->board[row][pos] = getTurn();
}

void Connect4Game::start(){
  system("cls");
  cout << "\t\t\t************************************\n"
       << "\t\t\t*    Welcome to Connect-4-Game     *\n"
       << "\t\t\t************************************\n";
  showBoard();
  this->turn = PLAYER1;
}

int Connect4Game::getTurn(){
  return this->turn;
}

void Connect4Game::switchTurn(int player){
  if(player == PLAYER1) this->turn = PLAYER2;
  else this->turn = PLAYER1;
}

int Connect4Game::rowsLeft(int pos){
  for(int row = this->SIZE - 1; row >= 0; row--){
    if(this->board[row][pos] == 0)
      return row;
  }
  return -1;
}

bool Connect4Game::isWin(int player){
  int i, j, k;
  for(j=0;j<SIZE;j++)
    for(i=0;i<SIZE;i++)
      if(this->board[i][j] == player){
        int count = 0;
        for(k=0;k<4;k++)
          if((i+k) < SIZE && this->board[i+k][j] == player)
            count++;
        if(count == 4)  return true;

        count = 0;
        for(k=0;k<4;k++)
          if((j+k) < SIZE && this->board[i][j+k] == player)
            count++;
        if(count == 4)  return true;

        count = 0;
        for(k=0;k<4;k++)
          if((i+k) < SIZE && (j+k) < SIZE && this->board[i+k][j+k] == player)
            count++;
        if(count == 4)  return true;

        count = 0;
        for(k=0;k<4;k++)
          if((i-k) >= 0 && (j+k) < SIZE && this->board[i-k][j+k] == player)
            count++;
        if(count == 4)  return true;
      }
  return false;
}

bool Connect4Game::isBoardFull(){
  for(int i=0; i<this->SIZE; i++)
    for(int j=0; j<this->SIZE; j++)
      if(this->board[i][j] == 0) return false;
  return true;
}

void printLastMsg(){
  cout << "\t\t\t************************************\n"
       << "\t\t\t*      Thank you for playing       *\n"
       << "\t\t\t************************************\n";
  system("pause");
}

int main(){

  Connect4Game game;
  int pos, choice;
  bool win=false;
  game.initBoard(BOARD_SIZE);
  game.start();
  cout << '\n';
  int i=0;

  while(!(game.isBoardFull() || win)){
    cout << "Player:" << game.getTurn() << '\n';
    cout << "Enter Column No (0-6): ";
    cin >> pos;
    if(game.rowsLeft(pos) < 0){
      cout << "Column has filled up. Select any other.\n";
      continue;
    }
    game.insertValue(pos);
    win = game.isWin(game.getTurn());
    system("cls");
    game.showBoard();
    game.switchTurn(game.getTurn());
  }
  if(game.isWin(PLAYER1))
    cout << "\n"
         << "Player 1 has won the game.\n";
  else
    cout << "\n"
         << "Player 2 has won the game.\n";
  cout << "Ener 1 to play again: ";
  cin >> choice;
  if(choice==1)  main();
  return 0;
}
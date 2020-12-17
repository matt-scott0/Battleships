#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H

int playerWon = 0;

struct SHIP {
  char *name;
  int length;
  int hits;
  int sunk;
};

enum letters{A, B, C, D, E, F, G, H};

void printBoard(char board[][8]);

void initialiseBoard(char board[][8]);

void setUpShips(char board[][8], struct SHIP ship);

int validShipPos(char board[][8], int xcoord, int ycoord, int shipLength, char orien);

int fire(char enemyShipBoard[][8], char playerHitBoard[][8], int xCo, int yCo, int playerTurn, struct SHIP p1Array[], struct SHIP p2Array[]);

#endif

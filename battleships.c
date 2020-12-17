#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "battleships.h"

//enum letters {A, B, C, D, E, F, G, H};

void printBoard(char board[][8]) {
  printf("  1 2 3 4 5 6 7 8\n");
//  for(int i = 65; i < 73; i++) {
//    printf("%c", i);
  for(int i = 0; i < 8; i++) {
    printf("%c|", i + 65); /* This is to print out the letters at the start of the map,
                          I couldn't be bothered to do a switch case or an array with the ENUM,
                          so I just do the ASCII value of A + whatever the value of i is.
                          Bit dodgy but hey, anything to keep being lazy. */
    for(int j = 0; j < 8; j++) {
      printf("%c|", board[i][j]);
    }
    printf("\n");
  }
}

void initialiseBoard(char board[][8]) {
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      board[i][j] = ' ';
    }
  }
  return;
}

int validShipPos(char board[][8], int xcoord, int ycoord, int shipLength, char orien) {
/*  if( ((coord + shipLength) > 8) || (coord < 0) ) { // this will test to see if the ship will go over the limits of the board
    return 0;
  }
*/
  if(orien == 'V') {
    if( ((ycoord + shipLength) > 8) || (ycoord < 0) ) { // this will test to see if the ship will go over the limits of the board
      return 0;
    }
    for(int i = ycoord; i < (ycoord + shipLength); i++){ //This will test to see if there is a ship already at the location
      if(board[i][xcoord] == 'C' || board[i][xcoord] == 'S' || board[i][xcoord] == 'D' || board[i][xcoord] == 'B' || board[i][xcoord] == 'P'){
        return 0;
      }
    }
  } else if (orien == 'H') {
    if( ((xcoord + shipLength) > 8) || (xcoord < 0) ) { // this will test to see if the ship will go over the limits of the board
      return 0;
    }
    for(int i = xcoord; i < (xcoord + shipLength); i++){ //This will test to see if there is a ship already at the location
      if(board[ycoord][i] == 'C' || board[ycoord][i] == 'S' || board[ycoord][i] == 'D' || board[ycoord][i] == 'B' || board[ycoord][i] == 'P') {
        return 0;
      }
    }
  }

  return 1;
}

void setUpShips(char board[][8], struct SHIP ship) {
  char yCord;
  int xCord;
  char orientation;
  int validPos = 0;
  char inputLine[20];
//  int yCordInt;
  while(validPos == 0) {


    printf("%s: ", ship.name);
    fgets(inputLine, sizeof(inputLine), stdin);
    sscanf(inputLine, "%c %d %c",  &yCord, &xCord, &orientation);
    yCord = yCord - 65;

    if(orientation == 'V'){
      /*
      if((yCord + ship.length) > 7) {
        printf("Invalid ship configuration\n");
      } else {
        validPos = 1;
      }
      */
      validPos = validShipPos(board, xCord-1, yCord, ship.length, 'V');
    } else if (orientation == 'H') {
      /*
      if((xCord + ship.length) > 7) {
        printf("Invalid ship configuration\n");
      } else {
        validPos = 1;
      }
      */
      validPos = validShipPos(board, xCord-1, yCord, ship.length, 'H');
    }

    if(validPos == 0) {
      printf("Invalid ship configuration\n");
    }

  }
//  printf("yCord: %d, xCord: %d, Orientation: %c\n", yCord, xCord, orientation);
  if(orientation == 'V') {
    for(int i = yCord; i < (yCord + ship.length); i++){
      board[i][xCord-1] = ship.name[0];
    }
  } else if (orientation == 'H') {
    for(int i = xCord; i < (xCord + ship.length); i++){
      board[yCord][i-1] = ship.name[0];
    }
  }

  return;

}

void hasPlayerWon(int playerTurn, struct SHIP enemyShipArray[]) {
  int sunkCount = 0;
  for(int i = 0; i < 5; i++) {
    if(enemyShipArray[i].sunk == 1){
      sunkCount++;
    }
  }
  if(sunkCount == 5) {
    printf("\nPlayer %d wins!\n", playerTurn);
    exit(1);
  }
  return;
}

int isSunk(struct SHIP *ship){ // returns 1 if the ship is sunk, returns 0 if it is not.
  if(ship->hits == ship->length) {
    ship->sunk = 1;
    printf("\nWe have sunk your %s!\n", ship->name);
    return 1;
  }
  return 0;
}

int fire(char enemyShipBoard[][8], char playerHitBoard[][8], int yCo, int xCo, int playerTurn, struct SHIP p1Array[], struct SHIP p2Array[]) {
    if(enemyShipBoard[yCo][xCo] == 'C') {
      if(playerTurn == 1) {
        p2Array[0].hits++;
        int isSunkRet = isSunk(&p2Array[0]);
        if(isSunkRet == 0) {
            printf("\nWe have hit the target!\n");
        } else if (isSunkRet == 1) {
          hasPlayerWon(playerTurn, p2Array);
        }
      } else if (playerTurn == 2) {
        p1Array[0].hits++;
        int isSunkRet = isSunk(&p1Array[0]);
        if(isSunkRet == 0) {
            printf("\nWe have hit the target!\n");
        } else if (isSunkRet == 1) {
          hasPlayerWon(playerTurn, p1Array);
        }
      }
      playerHitBoard[yCo][xCo] = 'X';
      return 1;
    } else if (enemyShipBoard[yCo][xCo] == 'B') {
        if(playerTurn == 1) {
          p2Array[1].hits++;
          int isSunkRet = isSunk(&p2Array[1]);
          if(isSunkRet == 0) {
              printf("\nWe have hit the target!\n");
          } else if (isSunkRet == 1) {
            hasPlayerWon(playerTurn, p2Array);
          }
        } else if (playerTurn == 2) {
          p1Array[1].hits++;
          int isSunkRet = isSunk(&p1Array[1]);
          if(isSunkRet == 0) {
              printf("\nWe have hit the target!\n");
          } else if (isSunkRet == 1) {
            hasPlayerWon(playerTurn, p1Array);
          }
        }
        playerHitBoard[yCo][xCo] = 'X';
        return 1;
    } else if (enemyShipBoard[yCo][xCo] == 'D') {
        if(playerTurn == 1) {
          p2Array[2].hits++;
          int isSunkRet = isSunk(&p2Array[2]);
          if(isSunkRet == 0) {
              printf("\nWe have hit the target!\n");
          } else if (isSunkRet == 1) {
            hasPlayerWon(playerTurn, p2Array);
          }
        } else if (playerTurn == 2) {
          p1Array[2].hits++;
          int isSunkRet = isSunk(&p1Array[2]);
          if(isSunkRet == 0) {
              printf("\nWe have hit the target!\n");
          } else if (isSunkRet == 1) {
            hasPlayerWon(playerTurn, p1Array);
          }
        }
        playerHitBoard[yCo][xCo] = 'X';
        return 1;
    } else if (enemyShipBoard[yCo][xCo] == 'S') {
        if(playerTurn == 1) {
          p2Array[3].hits++;
          int isSunkRet = isSunk(&p2Array[3]);
          if(isSunkRet == 0) {
              printf("\nWe have hit the target!\n");
          } else if (isSunkRet == 1) {
            hasPlayerWon(playerTurn, p2Array);
          }
        } else if (playerTurn == 2) {
          p1Array[3].hits++;
          int isSunkRet = isSunk(&p1Array[3]);
          if(isSunkRet == 0) {
              printf("\nWe have hit the target!\n");
          } else if (isSunkRet == 1) {
            hasPlayerWon(playerTurn, p1Array);
          }
        }
        playerHitBoard[yCo][xCo] = 'X';
        return 1;
    } else if (enemyShipBoard[yCo][xCo] == 'P') {
        if(playerTurn == 1) {
          p2Array[4].hits++;
          int isSunkRet = isSunk(&p2Array[4]);
          if(isSunkRet == 0) {
              printf("\nWe have hit the target!\n");
          } else if (isSunkRet == 1) {
            hasPlayerWon(playerTurn, p2Array);
          }
        } else if (playerTurn == 2) {
          p1Array[4].hits++;
          int isSunkRet = isSunk(&p1Array[4]);
          if(isSunkRet == 0) {
              printf("\nWe have hit the target!\n");
          } else if (isSunkRet == 1) {
            hasPlayerWon(playerTurn, p1Array);
          }
        }
        playerHitBoard[yCo][xCo] = 'X';
        return 1;
    } else {
      printf("\nYou have missed!\n");
      playerHitBoard[yCo][xCo] = '0';
      return 0;
    }
  return 0;
}

int main() {

  char playerOneHitBoard[8][8];
  char playerOneShipBoard[8][8];
  char playerTwoHitBoard[8][8];
  char playerTwoShipBoard[8][8];

  struct SHIP p1Carrier = {.name = "Carrier", .length = 5, .hits = 0, .sunk = 0};
  struct SHIP p1Battleship = {.name = "Battleship", .length = 4, .hits = 0, .sunk = 0};
  struct SHIP p1Destroyer = {.name = "Destroyer", .length = 3, .hits = 0, .sunk = 0};
  struct SHIP p1Submarine = {.name = "Submarine", .length = 2, .hits = 0, .sunk = 0};
  struct SHIP p1Patrol = {.name = "Patrol Boat", .length = 2, .hits = 0, .sunk = 0};

  struct SHIP p2Carrier = {.name = "Carrier", .length = 5, .hits = 0, .sunk = 0};
  struct SHIP p2Battleship = {.name = "Battleship", .length = 4, .hits = 0, .sunk = 0};
  struct SHIP p2Destroyer = {.name = "Destroyer", .length = 3, .hits = 0, .sunk = 0};
  struct SHIP p2Submarine = {.name = "Submarine", .length = 2, .hits = 0, .sunk = 0};
  struct SHIP p2Patrol = {.name = "Patrol Boat", .length = 2, .hits = 0, .sunk = 0};

  struct SHIP p1Array[5];
  struct SHIP p2Array[5];

  p1Array[0] = p1Carrier;
  p1Array[1] = p1Battleship;
  p1Array[2] = p1Destroyer;
  p1Array[3] = p1Submarine;
  p1Array[4] = p1Patrol;

  p2Array[0] = p2Carrier;
  p2Array[1] = p2Battleship;
  p2Array[2] = p2Destroyer;
  p2Array[3] = p2Submarine;
  p2Array[4] = p2Patrol;


  initialiseBoard(playerOneHitBoard);
  initialiseBoard(playerOneShipBoard);
  initialiseBoard(playerTwoHitBoard);
  initialiseBoard(playerTwoShipBoard);

  // this could be sped up a lot by making an array of these structs

  printf("Player 1, please set up your ships (y, x, orientation)\n");
  for(int i = 0; i < 5; i++){
    setUpShips(playerOneShipBoard, p1Array[i]);
  }
/*  setUpShips(playerOneShipBoard, p1Carrier);
  setUpShips(playerOneShipBoard, p1Battleship);
  setUpShips(playerOneShipBoard, p1Destroyer);
  setUpShips(playerOneShipBoard, p1Submarine);
  setUpShips(playerOneShipBoard, p1Patrol);
*/
  printf("\n\n");
  printf("Player 2, please set up your ships (y, x, orientation)\n");
  for(int i = 0; i < 5; i++){
    setUpShips(playerTwoShipBoard, p2Array[i]);
  }
  /*
  setUpShips(playerTwoShipBoard, p2Carrier);
  setUpShips(playerTwoShipBoard, p2Battleship);
  setUpShips(playerTwoShipBoard, p2Destroyer);
  setUpShips(playerTwoShipBoard, p2Submarine);
  setUpShips(playerTwoShipBoard, p2Patrol);
  */


  int j = 0;
  int playerTurn = 1;
  char inputLine[25];
  char inputCommand[20];
  char yCoordInput;
  int yCoordInputInt;
  int xCoordInput;
  /*int retFire;
  int retShot;
  int retExit;
  int validCoords = 0;*/


  while(playerWon == 0) {
    if(j % 2 == 0) {
      //Player 1 goes
      if(j == 0) {
        printf("\nAll boats set up, Player 1 can now strike.\n\n");
      } else {
        printf("\nPlayer 1's turn\n\n");
      }
      playerTurn = 1;

      fseek(stdin, 0, SEEK_END);

      int endOfTurn = 0;
      while(endOfTurn == 0) {
        fgets(inputLine, sizeof(inputLine), stdin);
        sscanf(inputLine, "%s %c %d", inputCommand, &yCoordInput, &xCoordInput);
        yCoordInputInt = yCoordInput - 65;

        if(strcmp("exit", inputCommand) == 0){
          exit(1);
        } else if(strcmp("shots", inputCommand) == 0) {
          printf("\n");
          printBoard(playerOneHitBoard);
          printf("\n");
          continue;
        }
        if(strcmp("fire", inputCommand) == 0){
          if(yCoordInputInt > 7 || yCoordInputInt < 0 || xCoordInput > 8 || xCoordInput < 1) {
            printf("Invalid coordinates\n");
            continue;
          } else if (playerOneHitBoard[yCoordInputInt][xCoordInput-1] == 'X' || playerOneHitBoard[yCoordInputInt][xCoordInput-1] == '0'){
            printf("You have already fired at this location\n");
            continue;
          } else {
            fire(playerTwoShipBoard, playerOneHitBoard, yCoordInputInt, xCoordInput-1, playerTurn, p1Array, p2Array);
            endOfTurn = 1;
          }
        } else {
          printf("Unrecognised command\n");
          continue;
        }
      }


/*
      int validCommand = 0;

      while(validCommand == 0){
        fgets(inputLine, sizeof(inputLine), stdin);
        sscanf(inputLine, "%s %c %d", inputCommand, &yCoordInput, &xCoordInput);
        yCoordInput = yCoordInput - 65;

        retFire = strcmp("fire", inputCommand);
        retShot = strcmp("shots", inputCommand);
        retExit = strcmp("exit", inputCommand);

        if(retExit == 0){
          exit(1);
        }

        if(retFire != 0 && retShot != 0 && retExit != 0) {
          printf("Unrecognised command\n");
        } else if ((yCoordInput > 8 || yCoordInput < 0 || xCoordInput > 8 || xCoordInput <= 0) && retFire == 0) {
          printf("Invalid coordinates\n");
          validCoords = 0;
        } else if (playerOneHitBoard[yCoordInputInt][xCoordInput-1] == 'X'){
          printf("You have already fired at this location\n");
          validCoords = 0;
        } else {
          validCommand = 1;
          validCoords = 1;
        }
        if(retShot == 0) {
          printf("\n");
          printBoard(playerOneHitBoard);
          printf("\n");
          validCommand = 0; // While this is a valid command, setting it to 0 will send the loop back to the top of the while loop, continuing to get user input.
        } else if(retFire == 0 && validCoords == 1){
          fire(playerTwoShipBoard, playerOneHitBoard, yCoordInput, xCoordInput-1, playerTurn, p1Array, p2Array);
        }
      }

*/

    } else {
      //Player 2 goes
      printf("\nPlayer 2's turn\n\n");
      playerTurn = 2;

      fseek(stdin, 0, SEEK_END);

      int endOfTurn = 0;
      while(endOfTurn == 0) {
        fgets(inputLine, sizeof(inputLine), stdin);
        sscanf(inputLine, "%s %c %d", inputCommand, &yCoordInput, &xCoordInput);
        yCoordInputInt = yCoordInput - 65;

        if(strcmp("exit", inputCommand) == 0){
          exit(1);
        } else if(strcmp("shots", inputCommand) == 0) {
          printf("\n");
          printBoard(playerTwoHitBoard);
          printf("\n");
          continue;
        }
        if(strcmp("fire", inputCommand) == 0){
          if(yCoordInputInt > 7 || yCoordInputInt < 0 || xCoordInput > 8 || xCoordInput < 1) {
            printf("Invalid coordinates\n");
            continue;
          } else if (playerTwoHitBoard[yCoordInputInt][xCoordInput-1] == 'X' || playerTwoHitBoard[yCoordInputInt][xCoordInput-1] == '0'){
            printf("You have already fired at this location\n");
            continue;
          } else {
            fire(playerOneShipBoard, playerTwoHitBoard, yCoordInputInt, xCoordInput-1, playerTurn, p1Array, p2Array);
            endOfTurn = 1;
          }
        } else {
          printf("Unrecognised command\n");
          continue;
        }
      }


/*
      int validCommand = 0;

      while(validCommand == 0){
        fgets(inputLine, sizeof(inputLine), stdin);
        sscanf(inputLine, "%s %c %d", inputCommand, &yCoordInput, &xCoordInput);
        yCoordInputInt = yCoordInput - 65;

        retFire = strcmp("fire", inputCommand);
        retShot = strcmp("shots", inputCommand);
        retExit = strcmp("exit", inputCommand);

        if(retExit == 0){
          exit(1);
        }

        if(retFire != 0 && retShot != 0 && retExit != 0) {
          printf("Unrecognised command\n");
        } else if ((yCoordInput > 8 || yCoordInput < 0 || xCoordInput > 8 || xCoordInput <= 0) && retFire == 0) {
          printf("Invalid coordinates\n");
          validCoords = 0;
        } else if (playerTwoHitBoard[yCoordInputInt][xCoordInput-1] == 'X'){
          printf("You have already fired at this location\n");
          validCoords = 0;
        } else {
          validCommand = 1;
          validCoords = 1;
        }
        if(retShot == 0) {
          printf("\n");
          printBoard(playerTwoHitBoard);
          printf("\n");
          validCommand = 0;
        } else if(retFire == 0 && validCoords == 1){
          fire(playerOneShipBoard, playerTwoHitBoard, yCoordInput, xCoordInput-1, playerTurn, p1Array, p2Array);
        }
      }*/
    }
    j++;
  }
  return 0;
}

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/

bool NextToOpponent(Board board, int i, int j, int color){
    bool yes=false;
    if(board.get_cell_color(i,j+1)!=color && board.get_cell_color(i,j+1)!='w' && j<5)yes=true;
    else{
        if(board.get_cell_color(i,j-1)!=color && board.get_cell_color(i,j-1)!='w' && j>0)yes=true;
        else{
            if(board.get_cell_color(i+1,j)!=color && board.get_cell_color(i+1,j)!='w' && i<4)yes=true;
            else{
                if(board.get_cell_color(i-1,j)!=color && board.get_cell_color(i-1,j)!='w' && i>0)yes=true;
            }
        }
    }

    return yes;
}

bool Away(Board board, int i, int j, int color){
    bool yes=true;
    if(board.get_cell_color(i,j+1)==color && j==4 && (i==0 || i==4))yes=false;
    else{
        if(board.get_cell_color(i,j-1)==color && j==1 && (i==0 || i==4))yes=false;
        else{
            if(board.get_cell_color(i+1,j)==color && i==3 && (j==0 || j==5))yes=false;
            else{
                if(board.get_cell_color(i-1,j)==color && i==1 && (j==0 || j==5))yes=false;
                else{
                    if(board.get_cell_color(i,j)==color && (i==0 || i==4) && (j==0 || j==5))yes=false;
                }
            }
        }
    }

    return yes;
}

void algorithm_A(Board board, Player player, int index[]){

    // cout << board.get_capacity(0, 0) << endl;
    // cout << board.get_orbs_num(0, 0) << endl;
    // cout << board.get_cell_color(0, 0) << endl;
    // board.print_current_board(0, 0, 0);

    //////////// Random Algorithm ////////////
    // Here is the random algorithm for your reference, you can delete or comment it.
    /*srand(time(NULL));*/
    int row, col;
    int color = player.get_color();
    
    /*while(1){
        row = rand() % 5;
        col = rand() % 6;
        if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
    }*/

    /*bool corner=true; //One of the corners is empty for the player to place an orb.
    if(board.get_orbs_num(0, 0)==0){
        row=0;
        col=0;
    }
    else{
        if(board.get_orbs_num(0, 5)==0){
            row=0;
            col=5;
        }
        else{
            if(board.get_orbs_num(4, 0)==0){
                row=4;
                col=0;
            }
            else{
                if(board.get_orbs_num(4, 5)==0){
                    row=4;
                    col=5;
                }
                else{
                    corner=false;
                }
            }
        }
    }*/
    
    /*int dev=4;
    while(1){            
        for(int i=0; i<5; i++){
            for(int j=0; j<6; j++){
                if(board.get_cell_color(i,j)!=color && board.get_cell_color(i,j)!='w'){
                    if()
                }
            }
        }
    }*/

    //1. corner if it's empty
    bool corner=true; //The orb is placed on a corner.
    if(board.get_orbs_num(0, 0)==0){
        row=0;
        col=0;
    }
    else{
        if(board.get_orbs_num(0, 5)==0){
            row=0;
            col=5;
        }
        else{
            if(board.get_orbs_num(4, 0)==0){
                row=4;
                col=0;
            }
            else{
                if(board.get_orbs_num(4, 5)==0){
                    row=4;
                    col=5;
                }
                else{
                    corner=false;
                }
            }
        }
    }

    //2. corner's neighbor is orb-2 or not
if(!corner){
    corner=true;
    if(board.get_cell_color(0,0)==color && (board.get_orbs_num(0,1)==2 || board.get_orbs_num(1,0)==2)){
        row=0;
        col=0;
    }
    else{
        if(board.get_cell_color(0,5)==color && (board.get_orbs_num(0,4)==2 || board.get_orbs_num(1,5)==2)){
            row=0;
            col=5;
        }
        else{
            if(board.get_cell_color(4,0)==color && (board.get_orbs_num(3,0)==2 || board.get_orbs_num(4,1)==2)){
                row=4;
                col=0;
            }
            else{
                if(board.get_cell_color(4,5)==color && (board.get_orbs_num(3,5)==2 || board.get_orbs_num(4,4)==2)){
                    row=4;
                    col=5;
                }
                else{
                    corner=false;
                }
            }
        }
    }
}

    //3. not on opponent, place on min(Cap-Orb), next to opponent, away from oneself's corner
    int MinDev=4;
    bool placed=false;
    if(!corner){
        for(int i=0; i<5; i++){
            for(int j=0; j<6; j++){
                if((board.get_cell_color(i,j)==color || board.get_cell_color(i,j)=='w') && (board.get_capacity(i,j)-board.get_orbs_num(i,j))<=MinDev && (board.get_capacity(i,j)-board.get_orbs_num(i,j))>1 && NextToOpponent(board,i,j,color) && Away(board,i,j,color)){
                    row=i;
                    col=j;
                    MinDev=board.get_capacity(i,j)-board.get_orbs_num(i,j);
                    //cout << "dev=" << (board.get_capacity(i,j)-board.get_orbs_num(i,j))<< endl;
                    //cout << "i="<< i << ", j="<< j<< endl;
                    placed=true;
                }
            }
        }
    }

    //4. not on opponent, place on min(Cap-Orb), away from oneself's corner
    MinDev=4;
    if(!placed && !corner){
        for(int i=0; i<5; i++){
            for(int j=0; j<6; j++){
                if((board.get_cell_color(i,j)==color || board.get_cell_color(i,j)=='w') && (board.get_capacity(i,j)-board.get_orbs_num(i,j))<=MinDev && (board.get_capacity(i,j)-board.get_orbs_num(i,j))>1 && Away(board,i,j,color)){
                    row=i;
                    col=j;
                    MinDev=board.get_capacity(i,j)-board.get_orbs_num(i,j);
                    placed=true;
                }
            }
        }
    }

    //5. not on opponent, next to opponent, away from oneself's corner
    if(!placed && !corner){
        for(int i=0; i<5; i++){
            for(int j=0; j<6; j++){
                if((board.get_cell_color(i,j)==color || board.get_cell_color(i,j)=='w') && NextToOpponent(board,i,j,color) && Away(board,i,j,color)){
                    row=i;
                    col=j;
                    placed=true;
                }
            }
        }
    }

    index[0] = row;
    index[1] = col;
}
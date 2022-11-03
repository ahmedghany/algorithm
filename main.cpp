/*Name: Ahmed Abdel Ghany, NSHE ID: 2001445844, CS302 Assignment 2,
 *Description:  implement a game board in which the sudoku game can be played
 *Input: file name
 *Output: the sudoku game*/


/*Algorithm: reading the file name and check it is right, then finding the,
* empty space in the printed numbers from the file, using different functions,
* to check each cell in the sector, and go back to the previous cell if an,
* error is found in the cell after it*/

#include <iostream>
#include <unistd.h>
#include <cmath>
#include <cstdlib>
#include <string> 
#include <iomanip>
#include <fstream>

using namespace std; 

const int blank = 0;
 
/*function_identifier: check if we have the same number in each sector
*paarmeters: board[][], num, r, c
*return value: true, false */
bool sameNumInSector( int board[9][9], int r, int c, int num){

    int rowBox = r - r % 3;
    int colBox = c - c % 3;

    for (int i= rowBox; i< rowBox +3; i++)
        for (int j= colBox; j< colBox +3; j++)
            if (board[i][j] == num)
                return true;
           
    return false;

}

 
/*function_identifier: check if we have the same number in thr row
 * *paarmeters: board[][], num, r
*return value: true, false */
bool sameNumInRow( int board[9][9], int r, int num){

    for (int c=0; c<9; c++)
        if (board[r][c] == num)
            return true;

    return false;
}
 
/*function_identifier: check if we have the same number in thr colomn
*paarmeters: board[][], num, c
*return value: true, false */
bool sameNumInCol( int board[9][9], int c, int num){

    for (int r=0; r<9; r++)
        if (board[r][c] == num)
            return true;

    return false;
}
 
 
/*function_identifier: check if we have a vaild num
 * *paarmeters:c, num, r
*return value: true, false */
bool valid(int board[9][9], int r, int c, int num){

    return !sameNumInRow(board, r, num) && !sameNumInCol(board, c, num)
        && !sameNumInSector(board, r, c, num);
}

 
/*function_identifier: check if it is blank
 *paarmeters: board[][]
*return value: true, false */
bool isBlank( int board[9][9]){

    for (int i =0; i< 9; i++)
        for (int j =0; j < 9; j++)
            if ( board[i][j] == blank)
                return true;

    return false;

}

 
/*function_identifier: check if it is blank
 *paarmeters: board[][], c, r
*return value: true, false */
bool sudoku( int board[9][9], int r, int c){


    if ( r == 9)
        return true;

    if (board[r][c] != blank)
        return sudoku(board, r+(c == 8), (c+1) %9);

    for (int num =1; num <=9; num++)
        if (valid( board, r, c, num)){
            
            board[r][c] = num;
            if (sudoku(board, r+(c==8), (c+1) %9))
                return true;
        }
          
    board[r][c] = blank;
            
    return false;
       
}

 
/*function_identifier: print the sudoku game board
 *paarmeters: board
*return value: none */
void printSudoku(int board[9][9]){

    for ( int r=0; r <9; r++){
        if ( r %3 == 0)
            cout << "-------------------------------"<<endl;

        for (int c=0; c<9; c++){
            if ( c%3 == 0)
                cout<<"|";
            cout<<" "<< char (board[r][c] == blank? '-' : board[r][c]+'0')<<" "; 

        }
        cout <<"|"<<endl;
    }

    cout << "-------------------------------"<<endl;
}


int main() {
	

    //itialize variables
	ifstream fileName;
	string file;
   
    int board[9][9];
    

    while(true){
        cout<<endl;
        //open the file
        while (true){
            
            cout << "Enter initial sudoku board file: ";
            cin >> file;
            
            if ( file == "NO"){
                cout<<endl;
                return 0;
            }

            fileName.open(file);

            if (fileName.is_open())
                break;
        }
        
        cout <<endl<< "Initial board read in"<<endl<<endl;
        // getting number
        for (int r=0; r<9; r++)
            for (int c=0; c<9; c++)
                
                fileName >> board[r][c];
                

        printSudoku(board);        
    
        // close file     
        fileName.close();

        cout<<endl;

        
        if (sudoku(board, 0, 0)){
            cout <<endl<< "Sudoku puzzled solved"<<endl<<endl;
            printSudoku(board);
        }
        else
            cout <<endl<<"No solution"<<endl<<endl;

    }
    return 0;
}

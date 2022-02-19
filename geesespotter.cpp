#include "geesespotter_lib.h"
#include <iostream>



//function definition

//locate a char array with xdim * ydim elements and initialize each element with zero.
char *createBoard(std::size_t xdim, std::size_t ydim){

    std::size_t size_of_array {xdim * ydim};
    //size = xdim*ydim
    
    char * new_array {new char[size_of_array] {}}; // dynamic allocation             ********ask about this
    //new returns returns a value of where the memory allocation takes place

    //make every element = 0
    for(int x{0}; x < size_of_array; ++x){
        new_array[x] = 0x00;
    }

    return new_array;
    //return nullptr;  pointer that doesnt point to anything
}

//for a board that contains only the values 0 or 9, 
//compute the number of goose-neighboredfields.
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim){
//make function to find xloc and yloc, they shouldnt be negative
int size = xdim*ydim;

    for (int k{}; k < xdim*ydim; ++k){
        //if ((board[k] & 0b00001001) > 0) {
        if((board[k] & valueMask()) == 9){
        int xloc{};
        int yloc{};
            //find xloc and yloc of k
            yloc = k/xdim;
            xloc = k%xdim;

            //std::cout << xloc << yloc <<std::endl;
            

            // int a = k-xdim -1;
            // int b = k-xdim;
            // int c = k-xdim +1;
            // int d = k-1;
            // int e = k+1;
            // int f = k +xdim -1;
            // int g = k + xdim + 1;

            if (xloc != 0 && yloc != 0 && (k-xdim -1) >= 0 && board[k-xdim - 1] <= 8){
                board[k-xdim - 1] += 0x01; // top left of k
            }
            if (yloc != 0 && (k-xdim) >= 0 && board[k-xdim] <= 8){
                board[k-xdim] += 0x01; // above k
            }
            if (xloc != (xdim -1) && yloc != 0 && (k-xdim +1) >= 0 && board[k-xdim + 1] <= 8){
                board[k-xdim +1] += 0x01; // top right k
            } 
            if (xloc != 0 && (k-1)>=0 && board[k - 1] <= 8){
                board[k-1] = board[k-1] + 0x01; //left of k
            }
            if (xloc != (xdim - 1) && (k+1) <= size && board[k + 1] <= 8){
                board[k+1] = board[k+1] + 0x01; // right of k
            }
            if (xloc != 0 && yloc != (ydim - 1) && (k + xdim - 1) <= size && board[k + xdim - 1] <= 8){
                board[k + xdim - 1] += 0x01; // bottom left
            }
            if (yloc != (ydim - 1) && (k + xdim) <= size && board[k + xdim] <= 8){
                board[k+xdim] += 0x01; // bottom right
            }
            if (xloc != (xdim - 1) && yloc != (ydim - 1) && (k + xdim + 1) <= size && board[k + xdim + 1] <= 8){
                board[k+xdim +1] += 0x01; // bottom right
            }

        }

        }
    }



//Hide all the field values
void hideBoard(char *board, std::size_t xdim, std::size_t ydim){
    //board is a character array --> hidden fields
    for(int i{0}; i < xdim*ydim; ++i){
        board[i] = board[i] | hiddenBit();
    }
}

//to deallocate the given board
void cleanBoard(char *board){
    //dynamic allocation is responsible for initial allocation, and deallocate original - there will be memory leak if not done

    delete[] board;
    board = nullptr;

}

//print the content of the board to std::cout.A hidden field uses ‘*’,
// a marked field uses ‘M’,and otherwise the field value is displayed. 
void printBoard(char *board, std::size_t xdim, std::size_t ydim){
    std::size_t size{xdim * ydim};
    
int g{};
for(int y{}; y < ydim; ++y){
    
        for(int x{}; x < xdim; ++x){

            if ((board[g] & hiddenBit()) == 0){ //if visible 0000 0001
                //char newBoard[1]{};

                //newBoard[0] = newBoard[0] + (48 + (board[g] & valueMask()));
                std::cout << (char)(48 + (board[g] & valueMask()));
                //std::cout << newBoard[0]; 
            }

             else if( (board[g] & markedBit()) > 0){//if marked
                std::cout << "M";
            }
            else if ((board[g] | hiddenBit()) > 0){ //if hidden
                std::cout << "*";
                //std::cout << (char)(48 + (board[g] & valueMask()));
            
            } 
            ++g;
    }

    std::cout<<std::endl;
}
}

    //char array = {0x01,0x09,1,1,0,0}   look at ascii table

    /*
    19
    11
    00

    // if visible               0000 xxxx
    0x01 0x09
    0x01 0x01
    0x00 0x00

    19
    11
    00

    //if vnot visible(hidden)   0010 xxxx
    0x21 0x29
    0x21 0x21
    0x20 0x20

    **
    **
    **

    //if its marked             0011 xxxx
    0x21 0x39
    0x21 0x21
    0x20 0x20

    *M
    **
    **
    
    */


//reveal a hidden field. Return 1 if field is marked. Return 2 if field is 
//already revealed. Reveal 9 if the field contains goose. Return 0 otherwise.
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){

    int size = xdim*ydim;

    std::size_t k = yloc * xdim + xloc; // index of the position we want

    //for (int k{}; k < size; k++){

        if( (board[k] & markedBit()) > 0){//if marked
            return 1;
        } 
        else if ((board[k] & hiddenBit()) == 0){ //if visible 
            return 2;
        }
        else if ((board[k] & valueMask()) == 9){ // if theres a goose there
           board[k] &= valueMask();
            return 9;
            
        }else{
        
            board[k] &= valueMask();

        if((board[k] & valueMask()) == 0){ // if the field is empty
        //std::cout<<xloc << yloc<<std::endl;
            
            if (xloc != 0 && yloc != 0 && (k-xdim -1) >= 0 && (board[k-xdim - 1]& valueMask()) < 9){
                board[k-xdim - 1] &= valueMask();
            }
            if (yloc != 0 && (k-xdim) >= 0 && (board[k-xdim] & valueMask()) < 9){
                board[k-xdim] &= valueMask();
            }
            if (xloc != (xdim -1) && yloc != 0 && (k-xdim +1) >= 0 && (board[k-xdim + 1] & valueMask()) < 9){
                board[k-xdim +1] &= valueMask();
            } 
            if (xloc != 0 && (k-1)>=0 && (board[k - 1] & valueMask()) < 9){
                board[k-1] &= valueMask(); 
            }
            if (xloc != (xdim - 1) && (k+1) <= size && (board[k + 1] & valueMask()) < 9){
                board[k+1] &= valueMask();
            }
            if (xloc != 0 && yloc != (ydim - 1) && (k + xdim - 1) <= size && (board[k + xdim - 1] & valueMask()) < 9){
                board[k + xdim - 1] &= valueMask();
            }
            if (yloc != (ydim - 1) && (k + xdim) <= size && (board[k + xdim] & valueMask())< 9){
                board[k+xdim] &= valueMask();
            }
            if (xloc != (xdim - 1) && yloc != (ydim - 1) && (k + xdim + 1) <= size && (board[k + xdim + 1] & valueMask()) < 9){
                board[k+xdim +1] &= valueMask();
            }

            // for (int q{}; q< size ; ++q){
            //     if ((board[q] & hiddenBit()) == 0 ){

            // if (xloc != 0 && yloc != 0 && (q-xdim -1) >= 0 && (board[q-xdim - 1]& valueMask()) < 9){
            //     board[q -xdim - 1] &= valueMask();
            // }
            // if (yloc != 0 && (q-xdim) >= 0 && (board[q-xdim] & valueMask()) < 9){
            //     board[q-xdim] &= valueMask();
            // }
            // if (xloc != (xdim -1) && yloc != 0 && (q-xdim +1) >= 0 && (board[q-xdim + 1] & valueMask()) < 9){
            //     board[q-xdim +1] &= valueMask();
            // } 
            // if (xloc != 0 && (q-1)>=0 && (board[q - 1] & valueMask()) < 9){
            //     board[q-1] &= valueMask(); 
            // }
            // if (xloc != (xdim - 1) && (q+1) <= size && (board[q + 1] & valueMask()) < 9){
            //     board[q+1] &= valueMask();
            // }
            // if (xloc != 0 && yloc != (ydim - 1) && (q + xdim - 1) <= size && (board[q + xdim - 1] & valueMask()) < 9){
            //     board[q + xdim - 1] &= valueMask();
            // }
            // if (yloc != (ydim - 1) && (q + xdim) <= size && (board[q + xdim] & valueMask())< 9){
            //     board[q+xdim] &= valueMask();
            // }
            // if (xloc != (xdim - 1) && yloc != (ydim - 1) && (q + xdim + 1) <= size && (board[q + xdim + 1] & valueMask()) < 9){
            //     board[q+xdim +1] &= valueMask();
            // }
        
        }
        /*else if((board[k] & valueMask()) < 9){
            board[k] &= valueMask();
            
        }*/
        }
    //}

//}
  //      }
        return 0;
}
//mark the given field. Return 2 if the field is already revealed. Return
//0 otherwise.
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    /* array = {0,0,0,0,9,0,0,0,0}
    000
    090
    000
    xdim = 3
    ydim = 3
    xloc = 2
    yloc = 2
    element of array we want to mark = element 8
      yloc*xdim + xloc = element
    */
    //at element, make it marked field
    
    std::size_t element = yloc * xdim + xloc; // index of the position we want

    if((board[element] & markedBit()) > 0){ // if its already marked
        board[element] = board[element] ^ markedBit(); // unmark it
        if((board[element] & hiddenBit()) == 0){ // if it is not hidden
            board[element] = board[element] | hiddenBit();
        }
        return 2;
    }else{
        board[element] = (board[element] | markedBit());
        return 0;
    }


    

    // if not hidden/if revealed, return a 2
    //if its marked already, unmark it

    //return 0 otherwise

    //mark a specific coordinate on our board
    //find outhow to get the location value for board
    

}

//determine whether the board is in a won state
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim){

bool gameWon{true};

int size = xdim*ydim;

    for (int k{}; k < size; ++k){

        if ((board[k] & valueMask()) < 9){
            if ((board[k] & hiddenBit()) > 0) {
                gameWon = false;
            }
        }

    }
if (gameWon == false){
    return false;
} else {
    return true;
}
    
}

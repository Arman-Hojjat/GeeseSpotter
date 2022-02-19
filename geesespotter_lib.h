#ifndef GEESESPOTTER_LIB_H
#define GEESESPOTTER_LIB_H

#include <iostream>

int main();
bool game();
void startGame(char * & board, std::size_t & xdim, std::size_t & ydim, unsigned int & numgeese);
char getAction();
void actionShow(char * & board, std::size_t & xdim, std::size_t & ydim, unsigned int & numgeese);
void actionMark(char * board, std::size_t xdim, std::size_t ydim);
std::size_t readSizeT();
std::size_t xdim_max();
std::size_t ydim_max();
char markedBit(); //(0x10) 00010000  use 5th bith to tell us marked,
char hiddenBit(); //(0x20) 00100000  6th bit to use hidden
char valueMask(); //(0x0F) 00001111  use 4 right most bits, are value of how many adjacent geese there are
void spreadGeese(char * board, std::size_t xdim, std::size_t ydim, unsigned int numgeese);


/*
                            hidden bit is 6th bit from right
lets say the value at game_board[location_index] is 00010011
i want to change this value to 00110011

game_board[location_index] = game_board[location_index] | hiddenBit();

for print function
if (/hidden bit is on/  game_board[location_index] & hiddenBit() > 0){

}

how to store if there is a goose on specific element - last 4 bits would be 9


game_board[location_index] & valueMask() gives me the geese adjancey value -> use compute neighbours for calculation of all adjancency values

result of this bitwise and gives only 4 last bits
& thing gives us last 4 bits of the char

files
geesespotter.h is function declarations
geesespotter.cpp function definitions
geesespotter_lib.h function declarations of functions given to us
geesepotter_lib.cpp function definitions of functions given to us

set pointers to null after deallocating

to test our code, run main.exe. -> build with g++ -o main geesespotter.cpp geesespotter_lib.cpp -std=c++11 ->
then open exe in integrated terminal ./main.exe
*/
#endif

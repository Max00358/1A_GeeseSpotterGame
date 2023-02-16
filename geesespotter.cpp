#include "geesespotter_lib.h"
#include <iostream>

void index_to_xy(std::size_t index_value, std::size_t xdim, std::size_t ydim, int & x_value, int & y_value);
std::size_t xy_to_index(int x_value, int y_value, std::size_t xdim, std::size_t ydim);

//g++ -o main geesespotter.cpp geesespotter_lib.cpp -std=c++11
char *createBoard(std::size_t xdim, std::size_t ydim){

	char *board = new char[xdim * ydim];

	for(int i = 0; i < xdim * ydim; i++){
		board[i] = 0;
	}
	
	return board;
}

//g++ -o main geesespotter.cpp geesespotter_lib.cpp -std=c++11
void hideBoard(char *board, std::size_t xdim, std::size_t ydim){
	for(int i = 0; i < xdim * ydim; i++){
		board[i] = (board[i] | hiddenBit());
	} 

	return;
}

//g++ -o main geesespotter.cpp geesespotter_lib.cpp -std=c++11
void printBoard(char *board, std::size_t xdim, std::size_t ydim){
	
	int test = 1;
	
	for(int j = 0; j < xdim * ydim; j++){
		
		if( (board[j] & hiddenBit()) == hiddenBit() && (board[j] & markedBit()) == markedBit() ){
			std::cout << "M";
		}
		//need to be put at the end of else if statements
		/*
		else if( (board[j] & hiddenBit()) == hiddenBit() && (board[j] & valueMask()) == 0x09 ){
			std::cout << ".";
		}
		*/
		else if( (board[j] & hiddenBit()) == hiddenBit()){
			std::cout << "*";
		}
		else if( (board[j] & hiddenBit()) != hiddenBit() ){
			std::cout << (board[j] & valueMask());
		}
		
		if(j+1 == xdim * test){
			std::cout << "\n";
			test++;
		}
	}
	
	return;
}

//g++ -o main geesespotter.cpp geesespotter_lib.cpp -std=c++11
void cleanBoard(char *board){
	
	delete[] board;
	board = nullptr;
	return;
}

//g++ -o main geesespotter.cpp geesespotter_lib.cpp -std=c++11
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
	int chosen = yloc * xdim + xloc;

	//If already revealed, return 2
	if( (board[chosen] & hiddenBit()) != hiddenBit() ){
		return 2;
	}
	//If it isn't already marked && isn't revealed, mark it
	else if( (board[chosen] & hiddenBit()) == hiddenBit() && (board[chosen] & markedBit()) != markedBit() ){
		board[chosen] = (board[chosen] | markedBit());
		return 0;
	}
	//if it's marked again, unmark it
	else if( (board[chosen] & markedBit()) == markedBit() ){
		board[chosen] = (board[chosen] & ~markedBit());
		return 0;
	}
	return 0;
}

//g++ -o main geesespotter.cpp geesespotter_lib.cpp -std=c++11
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim){
	
	//char *num_board = new char[xdim * ydim];
	int num_board[xdim * ydim];
	int test = 1;

	for(int j = 0; j < xdim * ydim; j++){
		num_board[j] = 0;
	}

	for(int i = 0; i < xdim * ydim; i++){

		int x_value = 0;
		int y_value = 0;
		int count = 0;

		//if num_board[i] == 0x09
		if( ((board[i] & valueMask()) == 0x09) || (((board[i] | markedBit()) & valueMask()) == 0x09) || ((board[i] & 0x09) == 0x09) ){
			num_board[i] = 9;
		}
		else{
			index_to_xy(i, xdim, ydim, x_value, y_value);
			
			if( x_value - 1 >= 0 && y_value + 1 < ydim ){//if bottom left on board
				if( (board[xy_to_index(x_value-1, y_value+1, xdim, ydim)] & valueMask() ) == 0x09 ){
					count++;
				}
			}
			//index_to_xy(i, xdim, ydim, x_value, y_value);
			if(x_value + 1 < xdim && y_value + 1 < ydim ){//if bottom right on board
				if( (board[xy_to_index(x_value+1, y_value+1, xdim, ydim)] & valueMask() ) == 0x09 ){
					count++;
				}
			}
			//index_to_xy(i, xdim, ydim, x_value, y_value);
			if(x_value + 1 < xdim){//if right on board
				if( (board[xy_to_index(x_value+1, y_value, xdim, ydim)] & valueMask() ) == 0x09 ){
					count++;
				}
			}
			//index_to_xy(i, xdim, ydim, x_value, y_value);
			if(x_value - 1 >= 0){//if left on board
				if( (board[xy_to_index(x_value-1, y_value, xdim, ydim)] & valueMask() ) == 0x09 ){
					count++;
				}
			}
			//index_to_xy(i, xdim, ydim, x_value, y_value);
			if(y_value - 1 >= 0){//if top on board
				if( (board[xy_to_index(x_value, y_value-1, xdim, ydim)] & valueMask() ) == 0x09 ){
					count++;
				}
			}
			//index_to_xy(i, xdim, ydim, x_value, y_value);
			if(y_value + 1 < ydim){//if bottom on board
				if( (board[xy_to_index(x_value, y_value+1, xdim, ydim)] & valueMask() ) == 0x09 ){
					count++;
				}
			}
			//index_to_xy(i, xdim, ydim, x_value, y_value);
			if(x_value - 1 >= 0 && y_value - 1 >= 0){//if top left on board
				if( (board[xy_to_index(x_value-1, y_value-1, xdim, ydim)] & valueMask() ) == 0x09 ){
					count++;
				}
			}
			//index_to_xy(i, xdim, ydim, x_value, y_value);
			if(x_value + 1 < xdim && y_value - 1 >= 0 ){//if top right on board
				if( (board[xy_to_index(x_value+1, y_value-1, xdim, ydim)] & valueMask() ) == 0x09 ){
					count++;
				}
			}
			num_board[i] = count;
		}
	}

	for(int i = 0; i < xdim * ydim; i++){
		/*
		std::cout << num_board[i] << ",";
		if(i+1 == xdim * test){
			std::cout << "\n";
			test++;
		}
		*/
		board[i] = num_board[i];
	}
	
	return;
}

void index_to_xy(std::size_t index, std::size_t xdim, std::size_t ydim, int & x_value, int & y_value){
	x_value = index % xdim;
	y_value = (index - x_value) / xdim;
}
std::size_t xy_to_index(int x_value, int y_value, std::size_t xdim, std::size_t ydim){
	std::size_t index = y_value * xdim + x_value;
	return index;
}

bool has_goose(char *board, std::size_t xdim, std::size_t ydim, int xloc, int yloc);

bool has_goose(char *board, std::size_t xdim, std::size_t ydim, int xloc, int yloc){
	int chosen = yloc * xdim + xloc;
	int x_value = 0;
	int y_value = 0;

	if( (board[chosen] & valueMask()) == 0x09 ){
		return true;
	}
	else{
		index_to_xy(chosen, xdim, ydim, x_value, y_value);

		if( x_value - 1 >= 0 && y_value + 1 < ydim ){//if bottom left on board
			if( (board[xy_to_index(x_value-1, y_value+1, xdim, ydim)] & valueMask() ) == 0x09 ){
				return true;
			}
		}
		if(x_value + 1 < xdim && y_value + 1 < ydim ){//if bottom right on board
			if( (board[xy_to_index(x_value+1, y_value+1, xdim, ydim)] & valueMask() ) == 0x09 ){
				return true;
			}
		}
		if(x_value + 1 < xdim){//if right on board
			if( (board[xy_to_index(x_value+1, y_value, xdim, ydim)] & valueMask() ) == 0x09 ){
				return true;
			}
		}
		if(x_value - 1 >= 0){//if left on board
			if( (board[xy_to_index(x_value-1, y_value, xdim, ydim)] & valueMask() ) == 0x09 ){
				return true;
			}
		}
		if(y_value - 1 >= 0){//if top on board
			if( (board[xy_to_index(x_value, y_value-1, xdim, ydim)] & valueMask() ) == 0x09 ){
				return true;
			}
		}
		if(y_value + 1 < ydim){//if bottom on board
			if( (board[xy_to_index(x_value, y_value+1, xdim, ydim)] & valueMask() ) == 0x09 ){
				return true;
			}
		}
		if(x_value - 1 >= 0 && y_value - 1 >= 0){//if top left on board
			if( (board[xy_to_index(x_value-1, y_value-1, xdim, ydim)] & valueMask() ) == 0x09 ){
				return true;
			}
		}
		if(x_value + 1 < xdim && y_value - 1 >= 0 ){//if top right on board
			if( (board[xy_to_index(x_value+1, y_value-1, xdim, ydim)] & valueMask() ) == 0x09 ){
				return true;
			}
		}
		return false;
	}
}

//g++ -o main geesespotter.cpp geesespotter_lib.cpp -std=c++11
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
	int chosen = yloc * xdim + xloc;
	int x_value = 0;
	int y_value = 0;

	//if it's marked, return 1
	if( (board[chosen] & markedBit()) == markedBit() ){
		return 1;
	}
	//if already revealed, return 2
	else if( (board[chosen] & hiddenBit()) != hiddenBit() ){
		return 2;
	}
	//if contain a goose, reveal everything and return 9
	else if( (board[chosen] & valueMask()) == 0x09 ){
		/*
		for(int i = 0; i < xdim * ydim; i++){
			board[i] = (board[i] & ~hiddenBit());
		}
		*/
		board[chosen] = (board[chosen] & ~hiddenBit());
		return 9;
	}
	else{
		//Check if it has goose in all 8 neighboring locations
		//Call has_goose 8 times to check
		//Check if the neighbouring field is in the board or not, do it in has_goose function
		//if all of those returns false, then reveal all 8 neighbors
		//if any of those returns true, then return 0
		if(has_goose(board, xdim, ydim, xloc, yloc) == true){
			board[chosen] = (board[chosen] & ~hiddenBit());
			return 0;
		}
		else if(has_goose(board, xdim, ydim, xloc, yloc) == false){

			//if empty field is revealed, reveal non-geese neighbors
			board[chosen] = (board[chosen] & ~hiddenBit());

			index_to_xy(chosen, xdim, ydim, x_value, y_value);

			if( x_value - 1 >= 0 && y_value + 1 < ydim ){//if bottom left on board
				board[xy_to_index(x_value-1, y_value+1, xdim, ydim)] = 
				(board[xy_to_index(x_value-1, y_value+1, xdim, ydim)] & ~hiddenBit());
			}
			if(x_value + 1 < xdim && y_value + 1 < ydim ){//if bottom right on board
				board[xy_to_index(x_value+1, y_value+1, xdim, ydim)] =
				(board[xy_to_index(x_value+1, y_value+1, xdim, ydim)] & ~hiddenBit());
			}
			if(x_value + 1 < xdim){//if right on board
				board[xy_to_index(x_value+1, y_value, xdim, ydim)] =
				(board[xy_to_index(x_value+1, y_value, xdim, ydim)] & ~hiddenBit());
			}
			if(x_value - 1 >= 0){//if left on board
				board[xy_to_index(x_value-1, y_value, xdim, ydim)] = 
				(board[xy_to_index(x_value-1, y_value, xdim, ydim)] & ~hiddenBit());
			}
			if(y_value - 1 >= 0){//if top on board
				board[xy_to_index(x_value, y_value-1, xdim, ydim)] = 
				(board[xy_to_index(x_value, y_value-1, xdim, ydim)] & ~hiddenBit());
			}
			if(y_value + 1 < ydim){//if bottom on board
				board[xy_to_index(x_value, y_value+1, xdim, ydim)] = 
				(board[xy_to_index(x_value, y_value+1, xdim, ydim)] & ~hiddenBit());
			}
			if(x_value - 1 >= 0 && y_value - 1 >= 0){//if top left on board
				board[xy_to_index(x_value-1, y_value-1, xdim, ydim)] = 
				(board[xy_to_index(x_value-1, y_value-1, xdim, ydim)] & ~hiddenBit());
			}
			if(x_value + 1 < xdim && y_value - 1 >= 0 ){//if top right on board
				board[xy_to_index(x_value+1, y_value-1, xdim, ydim)] = 
				(board[xy_to_index(x_value+1, y_value-1, xdim, ydim)] & ~hiddenBit());
			}
			return 0;
		}
		return 0;
	}
}

//g++ -o main geesespotter.cpp geesespotter_lib.cpp -std=c++11
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim){
	int count = 0;
	int goose = 0;
	//if every entry except for goose are revealed, game won
	for(int i = 0; i < xdim * ydim; i++){
		if( (board[i] & 0x09) != 0x09 ){
			if( (board[i] & hiddenBit()) != hiddenBit() ){
				count++;
			}
		}
		else{
			goose++;
		}
	}
	if(count == xdim * ydim - goose){
		return true;
	}
	return false;
}

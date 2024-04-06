#pragma once

//Install Libraries
#include <iostream>
#include <fstream>
#include <random>

using namespace std;


void Sleep(); //Function to delay execution to the next
void CreateReadFileP1(int& x, int& y); //Function to read values sent from Player1 process.
void CreateReadFileP2(int& x, int& y); //Function to read values sent from Player2 process.

class ACTION
{
public:
	ACTION();           //Default and parameterized constructor 
	bool Ju1();         //Function to check if player1 wins
	bool Ju2();         //Function to check if player2 wins
	void Cal();         //Logic parts such as calculations
	void Cha();         //Function to create graphics 
	void Ini();         //Functions to initialize variables in the class
	int GetTur() {      //Function to return which turn it is (Even numbers are player1, Odd numbers are player2)
		return Tur;
	}
	struct                    //Structure to save the condition of the board
	{
		int Typ[ROWS][COLS];  //Status of the board(0 = Empty, 1 = Player1, 2 = player2)
		int X[ROWS][COLS];    //Save the location of the X-coordinate of each board.
		int Y[ROWS][COLS];    //Save the location of the Y-coordinate of each board.
	}Sto;
private:
	struct                    //Structure to store cursor location information
	{
		int X = 20;           //X-coordinate of cursor
		int Y = 45;           //Y-coordinate of cursor
	}Cur; //Cursor

	struct                    //Structure to receive information from the keyboard
	{
		bool Xr = 0;          //Initialize record of D botton pressed from keyboard
		bool Xl = 0;          //Initialize record of A botton pressed from keyboard
		bool Yu = 0;          //Initialize record of S botton pressed from keyboard
		bool Yd = 0;          //Initialize record of W botton pressed from keyboard
		bool Ent = 0;         //Initialize record of Enter botton pressed from keyboard
	}Fla; //Flag

	struct {                  //Structure to store information received from child processes
		int ReX = 0;          //X of 2D array
		int ReY = 0;          //Y of 2D array
	}Rea; //Read

	int Tur = 0;              //Variable is stored which player's turn it is(Even = player1, Odd = Player2)
	bool Link1(bool Used[ROWS][COLS], int x, int y);   //Check the status of the pieces around a piece. Use in the Ju1()
	bool Link2(bool Used[ROWS][COLS], int x, int y);   //Check the status of the pieces around a piece. Use in the Ju2()
};

////Default and parameterized constructor 
ACTION::ACTION() {
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 6; x++) {
			Sto.Typ[x][y] = 0;        //Each board get 0 because of empty
			Sto.X[x][y] = 20;         //Initial X-coordinate of the board in [0][0]
			Sto.Y[x][y] = 45;         //Initial Y-coordinate of the board in [0][0]
		}         
	}
	Cur.X = 20;                    //Initilize Cursol X
	Cur.Y = 45;                    //Initilize Cursol Y
	Tur = 0;                       //Initilize Turn
	Rea.ReX = 0;                   //Initilize Recive X from child process
	Rea.ReY = 0;                   //Initilize Recive Y from child process
}

//Initilize 
void ACTION::Ini() {
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 6; x++) {
			Sto.Typ[x][y] = 0;
			Sto.X[x][y] = 20;
			Sto.Y[x][y] = 45;
		}
	}
	Cur.X = 20;
	Cur.Y = 45;
	Tur = 0;
	Rea.ReX = 0;
	Rea.ReY = 0;
}

//Logic parts such as calculations 
void ACTION::Cal() {
	//Read File from Child Process
	if (Tur%2 == 0)    //If If it is player1's turn, read fille from Player1 Process                     
		CreateReadFileP1(Rea.ReX, Rea.ReY);

	else               //If If it is player2's turn, read fille from Player2 Process   
		CreateReadFileP2(Rea.ReX, Rea.ReY);

	Cur.X = Rea.ReX *70 + Rea.ReY * 35 + 20;    //Modify the cursor to the position 
	Cur.Y = Rea.ReY * 55 + 45;					//of the index received from the child process

	//Update the status of the board 
	//with the index information received 
	//from the child process in a double for loop.
	for (int y = 0; y < 6; y++) {                 
		for (int x = 0; x < 6; x++) {
			if (Cur.X == x * 70 + y * 35 + 20 &&
				Cur.Y == y * 55 + 45 &&
				Sto.Typ[x][y] == 0)
			{
				Tur = Tur + 1;            //Increment turn
				Sto.X[x][y] = Cur.X;      //
				Sto.Y[x][y] = Cur.Y;
				//Even number (player1's Turn)
				if (Tur % 2 == 0)
				{
					Sto.Typ[x][y] = 1;   //Update information
				}
				//Odd number (player1's Turn)
				else
				{        
					Sto.Typ[x][y] = 2;  //Update information
				}
			}
		}
	}
}

//Graphic part
void ACTION::Cha() {
	DrawGraph(0, 0, Pic.Background3, TRUE);                        //Draw the Backgrownd
	DrawExtendGraph(470, 50, 570, 80, Pic.Logo, TRUE);     //Draw the game title stirng
	DrawGraph(420, 400, Pic.Pl1, TRUE);                    //Draw character Image "Player1"
	DrawExtendGraph(20, 160, 60, 360, Pic.Pl2, TRUE);      //Draw character Image "Player2"(vertical)

	//Draw board and piece
	for (int y = 0; y < 6; y++)
		for (int x = 0; x < 6; x++) {
			DrawExtendGraph((x * 70 + y * 35 + 20),        //Draw the board
				(y * 55 + 45),                             
				(x * 70 + y * 35 + 90),
				(y * 55 + 115),
				Pic.Bor,
				TRUE);

			switch (Sto.Typ[x][y])
			{
			case 0:                                       //If the board status is 0, no pieces are placed.
				break;
			case 1:
				DrawExtendGraph(Sto.X[x][y] + 10,         //If the board status is 0, player1's pieces are placed
					Sto.Y[x][y] + 10,
					Sto.X[x][y] + 70 - 10,
					Sto.Y[x][y] + 70 - 10,
					Pic.Blu, TRUE);
				break;
			case 2:
				DrawExtendGraph(Sto.X[x][y] + 10,        //If the board status is 0, player2's pieces are placed
					Sto.Y[x][y] + 10,
					Sto.X[x][y] + 70 - 10,
					Sto.Y[x][y] + 70 - 10,
					Pic.Red,
					TRUE);
				break;
			}
		}
	
	//Cursol
	DrawExtendGraph(Cur.X, Cur.Y, Cur.X + 70, Cur.Y + 70, Pic.Cur, TRUE);  //Draw an image of the cursor
	                                                                       //The location corresponds to the index 
																		   //received from the child process.
	//Intilize Flag
	Fla.Xl = 0;
	Fla.Xr = 0;
	Fla.Yd = 0;
	Fla.Yu = 0;
	Fla.Ent = 0;
}

//Function to check if player1 wins
bool ACTION::Ju1() {
	//Declear
	bool Used[6][6];   //This variable is used to avoid checking again if a piece has already been checked.

	//Initialize
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++) {
			Used[i][j] = false;
		}

	//Examine the top row of the board.
	for (int x = 0; x < 6; x++) {
		if (Sto.Typ[x][0] == 1 && Link1(Used, x, 0)) //If there is a piece in state 1, 
			return true;                             //give the piece's index and used variable to the Link1 function parameters.                         
	}
	//If a value of 1 is not in the first row 
	//or a false value is returned from the Link function, return False.
	return false;   
}

//Check the status of the pieces around a piece. Use in the Ju1()
bool ACTION::Link1(bool Used[ROWS][COLS], int x, int y) {
	if (Used[x][y])        
		return false;  //Returns false if the piece has already been checked.
	if (y == 5)     
		return true;   //Returns false if the piece has already been checked.
	Used[x][y] = true; //The pieces currently being handled will be in Used condition
	
	//Check the status of all Player1 boards located next to the piece being handled. 
	//If there is a 1 status, that piece will be checked.
	if (x > 0 && Sto.Typ[x - 1][y] == 1 && Link1(Used, x - 1, y)) return true;                  //Check upper left neighbor
	if (x > 0 && y < 5 && Sto.Typ[x - 1][y + 1] == 1 && Link1(Used, x - 1, y + 1)) return true; //Check upper right neihbor
	if (y < 5 && Sto.Typ[x][y + 1] == 1 && Link1(Used, x, y + 1)) return true;                  //Check right neihbor
	if (x < 5 && Sto.Typ[x + 1][y] == 1 && Link1(Used, x + 1, y)) return true;                  //Check lower right neihbor
	if (x < 5 && y > 0 && Sto.Typ[x + 1][y - 1] == 1 && Link1(Used, x + 1, y - 1)) return true; //Check lower left neihbor
	if (y > 0 && Sto.Typ[x][y - 1] == 1 && Link1(Used, x, y - 1)) return true;                  //Check left neihbor

	return false; //If the linked piece is not in the last row, return false.
}

//Function to check if player1 wins
//almost same as Ju1
bool ACTION::Ju2() {
	//Declear
	bool Used[6][6];

	//Initialize
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++) {
			Used[i][j] = false;
		}

	//Examine the left colmn of the board. 
	for (int y = 0; y < 6; y++) {                      //If there is a piece in state 2, 
		if (Sto.Typ[0][y] == 2 && Link2(Used, 0, y))   //give the piece's index and used variable to the Link2 function parameters.     
			return true;
	}
	return false;
}

//Check the status of the pieces around a piece. Use in the Ju2()
bool ACTION::Link2(bool Used[ROWS][COLS], int x, int y) {
	if (Used[x][y])
		return false;       //Returns false if the piece has already been checked.
	if (x == 5)   
		return true;        //If the linked piece is in the right columns, return true.
	Used[x][y] = true;      //The pieces currently being handled will be in Used condition

	//Check the status of all Player2 boards located next to the piece being handled. 
	//If there is a 2 status, that piece will be checked.
	if (x > 0 && Sto.Typ[x - 1][y] == 2 && Link2(Used, x - 1, y))return true;                   //Check upper left neighbor
	if (x > 0 && y < 5 && Sto.Typ[x - 1][y + 1] == 2 && Link2(Used, x - 1, y + 1))return true;  //Check upper right neihbor
	if (y < 5 && Sto.Typ[x][y + 1] == 2 && Link2(Used, x, y + 1))return true;                   //Check right neihbor
	if (x < 5 && Sto.Typ[x + 1][y] == 2 && Link2(Used, x + 1, y))return true;                   //Check lower right neihbor
	if (x < 5 && Sto.Typ[x + 1][y - 1] == 2 && y > 0 && Link2(Used, x + 1, y - 1))return true;  //Check lower left neihbor
	if (y > 0 && Sto.Typ[x][y - 1] == 2 && Link2(Used, x, y - 1))return true;                   //Check left neihbor

	return false;
}

//Function to read values sent from Player1 process.
void CreateReadFileP1(int& x, int& y) {
	//Bytes of data to be read
	DWORD DWRead;
	//Declare variables to receive data
	char charDataX[16];      
	char charDataY[16];
	LPCSTR  lpFileName1 = "StatsXP1.txt";        //Specify the location of the file that will receive the X, Y value 
	LPCSTR  lpFileName2 = "StatsYP1.txt";        //from the player1 process
   
	//Create File for X index
	HANDLE hFileX = CreateFile(lpFileName1,             //Pointer to name of the file
						       GENERIC_READ,            //Acess (read-write) mode       
						       0,                       //Share mode
						       NULL,                    //Pointer to security attributes
						       OPEN_EXISTING,           //How to create
						       FILE_ATTRIBUTE_NORMAL,   //File attributes
						       NULL);                   //Handle to file with attributes to 

	if (hFileX == INVALID_HANDLE_VALUE)                 //If it fails to find the file, 
	{                                                   //the function is terminated.
		return;
	}	                                         

	//Create File for Y index
	HANDLE hFileY = CreateFile(lpFileName2,             //Pointer to name of the file   
							   GENERIC_READ,            //Acess (read-write) mode    
						       0,                       //Share mode
						       NULL,                    //Pointer to security attributes
							   OPEN_EXISTING,           //How to create
							   FILE_ATTRIBUTE_NORMAL,   //File attributes
							   NULL);                   //Handle to file with attributes to 
	
	if (hFileY == INVALID_HANDLE_VALUE)
	{
		return;
	}
	//Reads the index of the x index from the player1 child process.
	//If it fails to read, release the handle.
	if (!ReadFile(hFileX, 
				  charDataX, 
				  sizeof(charDataX), 
				  &DWRead, 
				  NULL))
	{
		CloseHandle(hFileX);
		return;
	}
	//Reads the index of the y index from the player1 child process.
	//If it fails to read, release the handle.
	if (!ReadFile(hFileY, 
				  charDataY, 
				  sizeof(charDataY), 
				  &DWRead, 
				  NULL))
	{
		CloseHandle(hFileY);
		return;
	}

	//Modifies received char type data to int type
	x = atoi(charDataX);            
	y = atoi(charDataY);

	//Release the handle.
	CloseHandle(hFileX);
	CloseHandle(hFileY);
}

//Function to read values sent from Player2 process.
//It is almost same as CreateReadFileP1
void CreateReadFileP2(int& x, int& y) {
	//Bytes of data to be read
	DWORD DWRead;

	//Declare variables to receive data
	char charDataX[16];
	char charDataY[16];
	LPCSTR  lpFileName1 = "StatsXP2.txt";   //Specify the location of the file that will receive the X, Y value
	LPCSTR  lpFileName2 = "StatsYP2.txt";   //from the player1 process

	//Create File for X index
	HANDLE hFileX = CreateFile(lpFileName1, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFileX == INVALID_HANDLE_VALUE)
	{
		return;
	}
	//Create File for Y index
	HANDLE hFileY = CreateFile(lpFileName2, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFileY == INVALID_HANDLE_VALUE)
	{
		return;
	}

	//Reads the index of the x index from the player2 child process.
	//If it fails to read, release the handle.
	if (!ReadFile(hFileX, charDataX, sizeof(charDataX), &DWRead, NULL))
	{
		CloseHandle(hFileX);
		return;
	}

	//Reads the index of the y index from the player2 child process.
	//If it fails to read, release the handle.
	if (!ReadFile(hFileY, charDataY, sizeof(charDataY), &DWRead, NULL))
	{
		CloseHandle(hFileY);
		return;
	}

	//Modifies received char type data to int type
	x = atoi(charDataX);
	y = atoi(charDataY);

	//Release the handle.
	CloseHandle(hFileX);
	CloseHandle(hFileY);
}


//Sleep about 5sec
void Sleep() {
	int count = 0;
	while (count < 800000000) {
		count++;
	}
}
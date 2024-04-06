#include <iostream>
#include <fstream>
#include <random>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

using namespace std;

//Define rows and cols
const int ROWS = 6;
const int COLS = 6;

//Function to read board data from this parent process through shared memory.
bool ReadFile(int Typ[ROWS][COLS]);
//Function to generate an index where Player1 places a piece.
void GenerateRandomPairs(int Typ[ROWS][COLS], int& x, int& y);
//Function to create and write a file to send the generated index to the parent process
void CreateWriteFile(int _x, int _y);
//WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int main()
{
	//cout << "Hello World" << endl;
	//If the Player1 process is launched, this sentence will be outoput.
	cout << "Successful Launch of Player1 Process" << endl;
	//Set up a bool function but set up an infinite loop 
	//since the parent process will stop this process.
	bool exit = false;
	while (!exit) {
		int Typ[6][6];  //Variable to receive board status from parent process
		int WX = 0;     //Variable to store the index of X to be sent to the parent process
		int WY = 0;     //Variable to store the index of Y to be sent to the parent process
		//If shared memory is opened from the parent process, the following is executed
		if (ReadFile(Typ)) {         
			GenerateRandomPairs(Typ, WX, WY); //Generate rondom index pairs
			CreateWriteFile(WX, WY);          //Send rondom index pairs to parent process
		}
	}
	return 0;
}

//Function to read board data from this parent process through shared memory.
bool ReadFile(int Typ[ROWS][COLS]) {
	int data[36];                   //Declare variable to pass to shared memory 
	const int SIZE = sizeof(data);  //Store the size of data variable in bytes 
	HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, 
									  FALSE, 
		                              TEXT("SharedMemoryP1")); //Name of file-mapping object
	
	int* pBuf = (int*)MapViewOfFile(hMapFile,               //A handle to a file mapping object. 
		                            FILE_MAP_ALL_ACCESS,    //The type of access to a file mapping object
		                            0,                      //A high-order DWORD of the file offset
		                            0,                      //A low-order DWORD of the file offset 
		                            SIZE);                  //The number of bytes of a file mapping to map to the view
	
	if (pBuf == NULL)                                       //If pBuf is NULL, release handle and terminate this function
	{
		CloseHandle(hMapFile);
		return false;
	}
	cout << "Successful Acsess Shared Memory " << endl; //if this process open shared memory, output this
	for (int x = 0; x < 6; x++)
		for (int y = 0; y < 6; y++) {
			Typ[x][y] = pBuf[6 * x + y];  //Store board status from parent process
		}
	
	UnmapViewOfFile(pBuf);    //Unmap of view file           
	CloseHandle(hMapFile);    //Release the handle
	return true;
}

//Function to generate an index where Player1 places a piece.
void GenerateRandomPairs(int _Typ[ROWS][COLS], int& _x, int& _y) {
	uniform_int_distribution<> dist(0, 5);  //Set a range of values
	random_device rd;          //Random number engine to generate random values     
	mt19937 gen(rd());         //Declare variables with data types to generate a complete random number 

	bool Used = true;          //Variable to check for pieces at a specific index on the board

	while (Used) {             //Repeat the run until an index is 
		_x = dist(gen);        //generated with no pieces on the board
		_y = dist(gen);
		if (_Typ[_x][_y] == 0) {
			Used = false;
		}
	}
	//Outputs the generated index
	cout << "Generate Unique Pair x = " << _x << " y = " << _y << endl;
}

//Function to create and write a file to send the generated index to the parent process
void CreateWriteFile(int _x, int _y) {
	DWORD dwBytesWritten;
	LPCSTR  lpFileName1 = "../Manager/StatsXP1.txt";  //Specify the location of the file 
	LPCSTR  lpFileName2 = "../Manager/StatsYP1.txt";  //that will write the X, Y value 
	//Declare variables to send data
	char charData1[16];
	char charData2[16];
	//Convert data type from int to char
	sprintf_s(charData1, "%d", _x);
	sprintf_s(charData2, "%d", _y);
	HANDLE hFileX = CreateFileA(lpFileName1,           //The name of the file 
		                        GENERIC_WRITE,         //The requested access to the file
		                        0,                     //The requested sharing mode of the file
		                        NULL,                  //Security Attributes
		                        CREATE_ALWAYS,         //An action to take on a file
		                        FILE_ATTRIBUTE_NORMAL, //The file or device attributes
		                        NULL);                 //A valid handle to a template file
	if (hFileX == INVALID_HANDLE_VALUE)                //Terminate this function if hFileX can not be opened
	{
		return;
	}
	cout << "Sucsessful Create File StatsXP1" << endl; //Output this strings if hFileX can be opend
	HANDLE hFileY = CreateFileA(lpFileName2, 
		                        GENERIC_WRITE,         //The name of the file 
		                        0,                     //The requested access to the file
		                        NULL,                  //The requested sharing mode of the file
		                        CREATE_ALWAYS,         //Security Attributes
		                        FILE_ATTRIBUTE_NORMAL, //The file or device attributes
		                        NULL);                 //A valid handle to a template file
	if (hFileX == INVALID_HANDLE_VALUE)                //Terminate this function if hFileX can not be opend
	{
		return;
	}
	cout << "Sucsessful Create File StatsYP1" << endl; //Output this strings if hFileY can be opend
	if (!WriteFile(hFileX,                //A handle to the file
		           charData1,             //A pointer to the buffer containing the data to be written to the file
		           strlen(charData1),     //The number of bytes to be written to the file 
		           &dwBytesWritten,       //A pointer to the variable that receives the number of bytes written
		           NULL))                 //Over lapped
	{
		//cout << "Can not write a file" << endl;
		return;
	}
	cout << "Sucsessful Write File StatsXP1" << endl; //Output this strings if successful send the data to the parent process
	if (!WriteFile(hFileY,                 //A handle to the file
		           charData2,              //A pointer to the buffer containing the data to be written to the file
		           strlen(charData2),      //The number of bytes to be written to the file 
		           &dwBytesWritten,        //A pointer to the variable that receives the number of bytes written
		           NULL))                  //Over lapped
	{
		//cout << "Can not write a file" << endl;
		return;
	}
	cout << "Sucsessful Write File StatsXP1" << endl;  //Output this strings if successful send the data to the parent process
	
	//Release Hnadle
	CloseHandle(hFileX);
	CloseHandle(hFileY);
}
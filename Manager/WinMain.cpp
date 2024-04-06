//Rentaro Tsunamura
//0466470
//March 3


//Preprocessor define 
#define WIN_MAX_X 1920   //Define 
#define WIN_MAX_Y 1080
#define WIN_POS_X 0
#define WIN_POS_Y 0
const int ROWS = 6;
const int COLS = 6;

//Install Libraries
#include "DxLib.h"    
#include "Sub.h"
#include "Pic.h"
#include "Act.h"
#include "End.h"
#include "ActHum.h"
#include "GameType.h"
#include "Title.h"

//Function that modify 1D array to 2D array
void D1toD2(int arr[6][6], int data[36]);

//Main Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	ChangeWindowMode(TRUE);                      //Switch to full screen mode
	DxLib_Init();                                //Initialize Library

	//Windows Initilize
	SetWindowInitPosition(WIN_POS_X, WIN_POS_Y); //Background position
	SetWindowText("HEX GAME");                   //Background titel
	SetGraphMode(WIN_MAX_X, WIN_POS_Y, 32);      //Background size
	SetBackgroundColor(255, 255, 255);           //Background color
	SetDrawScreen(DX_SCREEN_BACK);               //Selects the screen to draw on

	STARTUPINFO siP1;                            //Used to specify information for creating a process 
	PROCESS_INFORMATION piP1;                    //Holds information such as thread handles and thread IDs.
	STARTUPINFO siP2;                            //Used to specify information for creating a process
	PROCESS_INFORMATION piP2;                    //Holds information such as thread handles and thread IDs.

	ZeroMemory(&siP1, sizeof(siP1));    //Initialize STARTUPINFO structure
	siP1.cb = sizeof(siP1);
	ZeroMemory(&piP1, sizeof(piP1));    //Initialize PROCESS_INFORMATION structure

	ZeroMemory(&siP2, sizeof(siP2));    //Initialize STARTUPINFO structure
	siP1.cb = sizeof(siP1);
	ZeroMemory(&piP2, sizeof(piP2));    //Initialize PROCESS_INFORMATION structure

	LPCTSTR lpApplicationName1 = "../Player1/x64/Debug/Player1.exe";  //An executable file to start a new process
	LPCTSTR lpApplicationName2 = "../Player2/x64/Debug/Player2.exe";  //An executable file to start a new process

	//Start the child process Player1. 
	if (!CreateProcess(lpApplicationName1,   // No module name (use command line)
		NULL,           // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&siP1,          // Pointer to STARTUPINFO structure
		&piP1)          // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());        //Terminate execution if process creation fails
		return 0;
	}

	//Start the child process Player2. 
	if (!CreateProcess(lpApplicationName2,   // No module name (use command line)
		NULL,           // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&siP2,          // Pointer to STARTUPINFO structure
		&piP2)          // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());        //Terminate execution if process creation fails
		return 0;
	}
	
	//Load images
	Pic.Read();

	//Declare class functions
	TITLE Tit;      //For Title
	ACTIONH Acth;   //For Game Human vs Computer
	ACTION  Act;    //For Game COM VS COM
	END End;        //For Graphic after Game

	while (ScreenFlip() == 0 &&               //Function used to perform screen updates
		ClearDrawScreen() == 0 &&             //Function used to clear the drawn image
		ProcessMessage() == 0 &&              //Function used to process the message
		Key.Read() == 0 &&                    //Function to read keyboard input
		Key.Inf[KEY_INPUT_ESCAPE] == 0 &&    
		Tit.GetExi() == false) {
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (End.GetHUM() || Tit.GetHUM()) {
			Acth.Ini();             //Initilize ACTIO data type function 
			Tit.Ini();              //Initilize TITLE type function 
			End.Ini();              //Initilize END type function 
			Game.TITLE = false;     //Titel mode off
			Game.COMVS = false;     //Com Vs Com mode off
			Game.HUMVS = true;      //Hum Vs Com mode on
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (End.GetCOM() || Tit.GetCOM()) {
			Act.Ini();              //Initilize ACTIO data type function 
			Tit.Ini();              //Initilize TITLE type function 
			End.Ini();              //Initilize END type function 
			Game.TITLE = false;     //Titel mode off
			Game.COMVS = true;      //Com Vs Com mode off
			Game.HUMVS = false;     //Hum Vs Com mode on
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (End.GetTIT()) {
			End.Ini();
			Game.TITLE = true;     //Titel mode on
			Game.COMVS = false;    //Com Vs Com mode off
			Game.HUMVS = false;    //Hum Vs Com mode on
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (Game.TITLE) {
			Tit.Cal();     //Logic parts such as calculations for title
			Tit.Cha();     //Function to create graphics for title
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//If Game Human vs Computer mode on
		if (Game.HUMVS) {
			Acth.Cha();
			//Function to check if player1 win
			if (Acth.Ju1()) {
				End.Cal();   //Logic parts such as calculations for next action after game
				End.Win1();  //Function to display the wins of paleyer1
			}
			//Function to check if player2 win
			else if (Acth.Ju2()) {
				End.Cal();   //Logic parts such as calculations for next action after game
				End.Win2();  //Function to display the wins of paleyer2
			}
			//If the winner has not been decided and the pieces are not filled in board
			else {
				if (Acth.GetTur() % 2 != 0) {   
					int data[36];                   //Declare variable to pass to shared memory 
					D1toD2(Acth.Sto.Typ, data);     //Modify 1D array to 2D array and store the data into variable named data
					const int SIZE = sizeof(data);  //Store the size of data variable in bytes 
					
					//Creates or opens a named or unnamed file mapping object for a specified file.
					HANDLE hMapFileP2 = CreateFileMapping(INVALID_HANDLE_VALUE,    //Handle to file to map
														  NULL,                    //Optional security attributes
						                                  PAGE_READWRITE,          //Protection for mapping object
						                                  0,                       //High-order 32 bits of object size
						                                  SIZE,                    //Low-order 32 bits of object size
						                                  TEXT("SharedMemoryP2")); //Name of file-mapping object
					
					if (hMapFileP2 == NULL)                                        //If hMapFileP1 is null, terimnate execution
					{
						_tprintf(TEXT("Could not create file mapping object (%d).\n"),
							GetLastError());
						return 0;
					}
					LPCTSTR pBufP2 = (LPTSTR)MapViewOfFile(hMapFileP2,             //A handle to a file mapping object
						                                   FILE_MAP_ALL_ACCESS,    //Type of access to a file mapping object
						                                   0,                      //A high-order DWORD of the file offset
						                                   0,                      //A low-order DWORD of the file offset 
						                                   SIZE);                  //The number of bytes of a file mapping to map to the view
					//Maps a view of a file mapping into the address space of a calling process
					if (pBufP2 == NULL)
					{
						_tprintf(TEXT("Could not map view of file (%d).\n"),
							GetLastError());
						CloseHandle(hMapFileP2);
						return 0;
					}
					//Release the handle.
					memcpy((void*)pBufP2, data, SIZE);       //Copy data existing in memory to another memory area.
					UnmapViewOfFile(pBufP2);                 //Unmap of view file
					CloseHandle(hMapFileP2);                 //Release the handle
				}
				Acth.Cal();
				//Sleep();
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//If Game Computer vs Computer mode on
		if (Game.COMVS) {
			Act.Cha();
			if (Act.Ju1()) {          
				End.Cal();             //Logic parts such as calculations for next action after game
				End.Win1();            //Function to display the wins of paleyer1
			}
			else if (Act.Ju2()) {
				End.Cal();             //Logic parts such as calculations for next action after game
				End.Win2();            //Function to display the wins of paleyer1
			}
			else {
				if (Act.GetTur() % 2 == 0) {
					int data[36];                                                    //Declare variable to pass to shared memory 
					D1toD2(Act.Sto.Typ, data);                                       //Modify 1D array to 2D array and store the data into variable named data
					const int SIZE = sizeof(data);                                   //Store the size of data variable in bytes 

					//Creates or opens a named or unnamed file mapping object for a specified file.
					HANDLE hMapFileP1 = CreateFileMapping(INVALID_HANDLE_VALUE,      //Handle to file to map
						                                  NULL,                      //Optional security attributes
						                                  PAGE_READWRITE,            //Protection for mapping object
						                                  0,                         //High-order 32 bits of object size
						                                  SIZE,                      //Low-order 32 bits of object size
						                                  TEXT("SharedMemoryP1"));   //Name of file-mapping object
					
					if (hMapFileP1 == NULL)                                          //If hMapFileP1 is null, terimnate execution
					{
						_tprintf(TEXT("Could not create file mapping object (%d).\n"),
							GetLastError());
						return 0;
					}
					
					//Maps a view of a file mapping into the address space of a calling process
					LPCTSTR pBufP1 = (LPTSTR)MapViewOfFile(hMapFileP1,               //A handle to a file mapping object
						                                   FILE_MAP_ALL_ACCESS,      //Type of access to a file mapping object
						                                   0,                        //A high-order DWORD of the file offset
						                                   0,                        //A low-order DWORD of the file offset 
						                                   SIZE);                    //The number of bytes of a file mapping to map to the view
					
					if (pBufP1 == NULL)                                              //If pBufP2 is null, terimnate execution
					{
						_tprintf(TEXT("Could not map view of file (%d).\n"),
							GetLastError());
						CloseHandle(hMapFileP1);
						return 0;
					}
					memcpy((void*)pBufP1, data, SIZE);                               //Copy data existing in memory to another memory area.
					UnmapViewOfFile(pBufP1);                                         //Unmap of view file
					CloseHandle(hMapFileP1);                                         //Release the handle
				}
                
				else {
					int data[36];                                                    //Declare variable to pass to shared memory 
					D1toD2(Act.Sto.Typ, data);                                       //Modify 1D array to 2D array and store the data into variable named data
					const int SIZE = sizeof(data);                                   //Store the size of data variable in bytes

					//Creates or opens a named or unnamed file mapping object for a specified file.
					HANDLE hMapFileP2 = CreateFileMapping(INVALID_HANDLE_VALUE,      //Handle to file to map
						                                  NULL,                      //Optional security attributes
						                                  PAGE_READWRITE,            //Protection for mapping object
						                                  0,                         //High-order 32 bits of object size
						                                  SIZE,                      //Low-order 32 bits of object size
						                                  TEXT("SharedMemoryP2"));   //Name of file-mapping object
					
					if (hMapFileP2 == NULL)                                          //If hMapFileP1 is null, terimnate execution
					{
						_tprintf(TEXT("Could not create file mapping object (%d).\n"),
							GetLastError());
						return 0;
					}

					//Maps a view of a file mapping into the address space of a calling process
					LPCTSTR pBufP2 = (LPTSTR)MapViewOfFile(hMapFileP2,               //A handle to a file mapping object
						                                   FILE_MAP_ALL_ACCESS,      //Type of access to a file mapping object
						                                   0,                        //A high-order DWORD of the file offset
						                                   0,                        //A low-order DWORD of the file offset 
					                                       SIZE);                    //The number of bytes of a file mapping to map to the view

					if (pBufP2 == NULL)                                              //If pBufP2 is null, terimnate execution
					{
						_tprintf(TEXT("Could not map view of file (%d).\n"),
							GetLastError());
						CloseHandle(hMapFileP2);
						return 0;
					}
		
					memcpy((void*)pBufP2, data, SIZE);        //Copy data existing in memory to another memory area.
					UnmapViewOfFile(pBufP2);                  //Unmap of view file
					CloseHandle(hMapFileP2);                  //Release the handle
				}
				Act.Cal();
				//Sleep();
			}
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	TerminateProcess(piP1.hProcess, 0); //Stop process 1
	TerminateProcess(piP2.hProcess, 0); //Stop process 1
	
	//Release Handle
	CloseHandle(piP1.hProcess);   
	CloseHandle(piP1.hThread);
	CloseHandle(piP2.hProcess);
	CloseHandle(piP2.hThread);
	//WaitKey();				
	//DxLib_End();
	return 0;

}

//Function that modify 1D array to 2D array
void D1toD2(int arr[6][6], int data[36]) {
	int count = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			data[count] = arr[i][j];
			count++;
		}
	}
}
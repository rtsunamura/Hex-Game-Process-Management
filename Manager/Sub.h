#pragma once
//Class to retrieve information from the keyboard.
class
{
public:
	//Key Info
	int Inf[256];                            //Declear char data type Info                 
	int Read() {
		char allkey[256];                    //Declare an array called allkey of 256 characters
		GetHitKeyStateAll(allkey);           //Function to store information about the current state of each key on the keyboard in the allkey array.
		for (int i = 0; i < 256; i++) {      //Loop through all elements of the allkey array.
			if (allkey[i] == 1) {            //Increments the Inf array if allKEy[i] is 1.
				Inf[i] = Inf[i] + 1;
			}
			else if (allkey[i] == 0) {       //Initlize the Inf array, if allKEy[i] is o
				Inf[i] = 0;
			}
		}
		return 0;
	}
private:
}Key;
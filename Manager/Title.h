#pragma once

//Class for the display screen and logic in the title.
class TITLE {
public:
	void Cal();  //Logic parts such as calculations
	void Cha();  //Function to create graphics for titles
	void Ini();  //Functions to initialize variables in the class
	
	//Function to return the value of the private variable EXI
	bool GetExi() {
		return EXI;
	}
	//Function to return the value of the private variable HUM
	bool GetHUM() {
		return HUM;
	}
	//Function to return the value of the private variable COM
	bool GetCOM() {
		return COM;
	}
private:
	//Structure to place the cursor
	struct
	{
		int X = 190;    //Initialize X-coordinate
		int Y = 225;    //Initialize Y-coordinate
	}Cur;
	
	//Structure to receive information from the keyboard 
	struct
	{
		bool Yu = 0;    //Initialize record of S botton pressed from keyboard
		bool Yd = 0;    //Initialize record of W botton pressed from keyboard
		bool Ent1 = 0;  //Initialize record of Enter botton pressed from keyboard
		bool Ent2 = 0;  //Initialize record of Enter botton pressed from keyboard
	}Fla;

	bool EXI = false; //Exit Information
	bool HUM = false; //Information on HUMAN vs Computer
	bool COM = false; //Information on Computer vs Computer
};
//Functions to initialize variables in the class
void TITLE::Ini() {
	EXI = false;
	HUM = false;
	COM = false;
	Fla.Ent1 = 0;
	Fla.Ent2 = 0;
	Cur.X = 190;
	Cur.Y = 225;
}

//Logic part such as calculations 
void TITLE::Cal() {
	//If Fla.Ent1 is false and Enter is pressed from the keyboard, 
	//a value of true is stored in Fla.Ent1.
	if (Fla.Ent1 == 0) {
		if (Key.Inf[KEY_INPUT_NUMPADENTER] == 1)
		{
			Fla.Ent1 = true;
		}
	}

	//If Fla.Ent1 is true, the following calculations are executed.
	else {
		
		if (Key.Inf[KEY_INPUT_W] == 1) Fla.Yd = 1;       //If W is pressed from the keyboard, Fla.Yd will be ture.
		else if (Key.Inf[KEY_INPUT_S] == 1) Fla.Yu = 1;  //If S is pressed from the keyboard, Fla.Yd will be ture.
		
		//Cursol Move
		if (Fla.Yu == 1) {
			Cur.Y = Cur.Y + 30;        //If Fla.Yu is ture, 30 is added to Cur.Y.
		}
		else if (Fla.Yd == 1) {
			Cur.Y = Cur.Y - 30;        //If Fla.Yd is ture,  Cur.Y minus 30.
		} 

		//Control Cursol
		if (Cur.Y < 225) {             //Cur.Y is less than 225, return to previous Y-cordinate location
			Cur.Y += 30;                
		}
		else if (Cur.Y > 285) {
			Cur.Y -= 30;               //Cur.Y is bigger than 285, return to previous Y-cordinate location
		}

		if (Key.Inf[KEY_INPUT_NUMPADENTER] == 1)
		{
			Fla.Ent2 = 1;       //If Enter is pressed from the keyboard, 
		}						//a value of true is stored in Fla.Ent1.

		if (Cur.Y == 225 &&   
			Fla.Ent2 == 1)      //If Cur.Y is 225 and Fla.Ent2 is true,
		{                       //HUM is true, which means next action will be HUM vs Computer
			HUM = true;
		}
		else if (Cur.Y == 255 &&
			Fla.Ent2 == true) 
		{                        //If Cur.Y is 255 and Fla.Ent2 is true,
			COM = true;          //COM is true, which means next action will be Computer vs Computer
		}
		else if (Cur.Y == 285 &&
			Fla.Ent2 == true)    
		{                         //If Cur.Y is 285 and Fla.Ent2 is true,
			EXI = true;           //COM is true, which means the next action will be Exit
		}
	}
}

//Function to create graphics for titles
void TITLE::Cha() {
	DrawGraph(0, 0, Pic.Background1, TRUE);                            //Draw an image of the selection screen                     
	DrawExtendGraph(470, 50, 570, 80, Pic.Logo, TRUE);         //Draw the name of this game in the upper right corner.
	if (Fla.Ent1 == 0) 
	{                                                          //If Fla.Ent1 is true,
		DrawGraph(220, 200, Pic.Ent, TRUE);                    //The "ENTER" character is displayed in the middle of the screen
	}
	else
	{                                                          //If Fla.Ent1 is not true,
		DrawExtendGraph(210, 220, 420, 320, Pic.Tit, TRUE);    //Draw a selection screen image for the next action 
		DrawExtendGraph(Cur.X,                                 //and a cursor image.
						Cur.Y, 
						Cur.X + 25, 
						Cur.Y + 25, Pic.Sel, TRUE);
	}
	
	Fla.Yd = 0;                                                //Initialize W Button
	Fla.Yu = 0;                                                //Initialize X Button
}





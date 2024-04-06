#pragma once

//This class will be used for after finish some game
class END {
public:
	void Ini();                //Functions to initialize variables in the class
	void Win1();               //Function to create graphics in the case where player1 wins
	void Win2();               //Function to create graphics in the case where player2 wins
	void Cal();                //Logic parts such as calculations
	bool GetHUM() {     
		return HUM;            //Function to return the value of the private variable HUM
	}
	bool GetCOM() {
		return COM;            //Function to return the value of the private variable COM
	}
	bool GetTIT() {
		return TIT;            //Function to return the value of the private variable TIT
	}
private:
	//Structure to place the cursor
	struct {
		int X = 130;            //Initialize X-coordinate 
		int Y = 390;            //Initialize Y-coordinate
	}Cur;
	
	//Structure to receive information from the keyboard 
	struct {
		int Yu = 0;       //Initialize record of S botton pressed from keyboard
		int Yd = 0;       //Initialize record of W botton pressed from keyboard
		int Ent = 0;      //Initialize record of Enter botton pressed from keyboard
	}Fla;

	bool HUM = false;     //Exit Information
	bool COM = false;     //Information on HUMAN vs Computer
	bool TIT = false;     //Information on Computer vs Computer
};

//Functions to initialize variables in the class
void END::Ini() {
	Cur.X = 130;
	Cur.Y = 390;
	
	HUM = false;
	COM = false;
	TIT = false;
	Fla.Ent = 0;
	Fla.Yu = 0;
	Fla.Yd = 0;
}

//Logic part such as calculations 
void END::Cal() {
	//If W is pressed from the keyboard, Fla.Yd will be ture.
	//If S is pressed from the keyboard, Fla.Yd will be ture.
	if (Key.Inf[KEY_INPUT_W] == 1) Fla.Yu = 1;
	else if (Key.Inf[KEY_INPUT_S] == 1) Fla.Yd = 1;
	//Cursol move
	if (Fla.Yd == 1) {
		Cur.Y = Cur.Y + 30;  //If Fla.Yu is ture, 30 is added to Cur.Y.
	}
	else if (Fla.Yu == 1) {
		Cur.Y = Cur.Y - 30;  //If Fla.Yd is ture,  Cur.Y minus 30.
	}

	//Control
	if (Cur.Y < 390) {
		Cur.Y += 30;         //Cur.Y is less than 390, return to previous Y-cordinate location
	}
	else if (Cur.Y > 451) {
		Cur.Y -= 30;        //Cur.Y is bigger than 451, return to previous Y-cordinate location
	}

	//Set
	if (Key.Inf[KEY_INPUT_NUMPADENTER] == 1)
	{
		Fla.Ent = 1;           //If Enter is pressed from the keyboard, 
	}                          //a value of true is stored in Fla.Ent1.

	if (Cur.Y == 390 &&
		Fla.Ent == 1)
	{                          //If Cur.Y is 390 and Fla.Ent1 is true,  
		HUM = true;            //HUM is true, which means next action will be HUM vs Computer
	}
	else if (Cur.Y == 420 &&
		Fla.Ent == 1) {        //If Cur.Y is 420 and Fla.Ent1 is true,
		COM = true;            //COM is true, which means next action will be Computer vs Computer
	}
	else if (Cur.Y == 450 &&   
		Fla.Ent == 1)
	{                          //If Cur.Y is 450 and Fla.Ent1 is true,
		TIT = true;            //COM is true, which means the next action will be Title
	}
}

// if Player1 wins this function will be executed
void END::Win1() {
	DrawExtendGraph(0, 170, 700, 240, Pic.Yel, TRUE);                    //Draw BackGround Yellow
	DrawGraph(230, 170, Pic.Pl1, TRUE);                                  //Draw Winner player
	DrawExtendGraph(40, 185, 80, 225, Pic.Ball, TRUE);                   //Draw Balls
	DrawExtendGraph(100, 185, 140, 225, Pic.Ball, TRUE);                 //Draw Balls
	DrawExtendGraph(160, 185, 200, 225, Pic.Ball, TRUE);                 //Draw Balls
	DrawExtendGraph(430, 185, 470, 225, Pic.Ball, TRUE);                 //Draw Balls
	DrawExtendGraph(490, 185, 530, 225, Pic.Ball, TRUE);                 //Draw Balls
	DrawExtendGraph(550, 185, 590, 225, Pic.Ball, TRUE);                 //Draw Balls
	DrawExtendGraph(160, 385, 360, 485, Pic.End, TRUE);                  //Draw an image of the selection screen  
	DrawExtendGraph(Cur.X, Cur.Y, Cur.X + 25, Cur.Y+25, Pic.Sel, TRUE);
	Fla.Yd = 0;  //Initialize W Button
	Fla.Yu = 0;  //Initialize X Button
}

// if Player2 wins this function will be executed
void END::Win2() {
	DrawExtendGraph(0, 170, 700, 240, Pic.Yel, TRUE);                    //Draw BackGround Yellow
	DrawGraph(230, 170, Pic.Pl22, TRUE);                                 //Draw Winner player
	DrawExtendGraph(40, 185, 80, 225, Pic.Ball, TRUE);                   //Draw Balls
	DrawExtendGraph(100, 185, 140, 225, Pic.Ball, TRUE);                 //Draw Balls
	DrawExtendGraph(160, 185, 200, 225, Pic.Ball, TRUE);                 //Draw Balls
	DrawExtendGraph(430, 185, 470, 225, Pic.Ball, TRUE);                 //Draw Balls
	DrawExtendGraph(490, 185, 530, 225, Pic.Ball, TRUE);                 //Draw Balls
	DrawExtendGraph(550, 185, 590, 225, Pic.Ball, TRUE);                 //Draw Balls
	DrawExtendGraph(160, 385, 360, 485, Pic.End, TRUE);                  //Draw an image of the selection screen  
	DrawExtendGraph(Cur.X, Cur.Y, Cur.X + 25, Cur.Y+25, Pic.Sel, TRUE);  //Draw a cursor
	
	Fla.Yd = 0;  //Initialize W Button
	Fla.Yu = 0;  //Initialize X Button
}


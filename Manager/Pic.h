#pragma once
//This class is used to load or depict images.
class
{
public:
	//Declare variables for images
	int Bor;    //Game Board
	int Blu;    //Pice for Player1
	int Red;    //Pice for Player2
	int Cur;    //Move Cursor
	int Pl1;    //Character Image "Player1" 
	int Pl2;    //Character Image "Player2" (Horizontal)
	int Tit;    //Optional image at beginigng game "HUMAN VS COM", "COM vs COM" or "EXIT"
	int End;    //Optional image at end of game "HUMAN VS COM", "COM vs COM" or "Title"
	int Sel;    //Cursol for selecting something next action
	int Pl22;   //Character Image "Player2" (Vertical)
	int Yel;    //Yellow Background
	int Background1;    //Title Background
	int Ent;    //Character Image "Enter"
	int Logo;   //Character Image "Hex Game"
	int Background2;    //Game Background
	int Background3;   //Game Background
	int Ball;   //Ornament

	//Put the value of the image into a variable
	void Read() {
		Bor = LoadGraph("../images/pentagon.png");
		Blu = LoadGraph("../images/Blue.png");
		Red = LoadGraph("../images/Red.png");
		Cur = LoadGraph("../images/hexagon.png");
		Pl1 = LoadGraph("../images/Player1.png");
		Pl2 = LoadGraph("../images/Player2.png");
		Tit = LoadGraph("../images/Tit.png");
		End = LoadGraph("../images/End.png");
		Sel = LoadGraph("../images/Sel.png");
		Pl22 = LoadGraph("../images/Player2-2.png");
		Yel = LoadGraph("../images/yellow.png");
		Background1 = LoadGraph("../images/Background1.png");
		Ent = LoadGraph("../images/Enter.png");
		Logo = LoadGraph("../images/Logo.png");
		Background2 = LoadGraph("../images/Background2.png");
		Background3 = LoadGraph("../images/Background3.png");
		Ball = LoadGraph("../images/Ball.png");
	}
}Pic; //Class name
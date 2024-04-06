#pragma once
//The structure that determines 
//whether the current screen is the title 
//or which game is being played.
struct {
	bool TITLE = true;       //In the case of title 
	bool COMVS = false;      //In the case of Game Computer vs Computer
	bool HUMVS = false;      //In the case of Game Human vs Computer
}Game;
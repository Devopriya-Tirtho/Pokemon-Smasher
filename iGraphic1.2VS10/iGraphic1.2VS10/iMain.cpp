# include "iGraphics.h"
#include<string.h>
#include <time.h>
#include <stdlib.h>
/*
function iDraw() is called again and again by the system.
*/
void attack_list();		//defines the attacks
void pokemon_list();	//defines the pokemon
void setEnimPos();		//sets the initial positions of pokemons for each town

void game();			//game play
void instruction();		//instruction page
void credit();			//credits
void exit();			//close the game
void high();			//highscore page

void gameover();		//gameover screne
void battle();			//screen where the battle takes place
void town_map();		//screen that shows the town map
void screen_1();		//first screen to appear on at the start of the game
void choice();			//screen where the pokemon choosing takes place

void show_Town_1();		//shows the 1st town
void show_Town_2();		//shows the 2nd town
void show_Town_3();		//shows the 3rd town
void show_Town_4();		//shows the 4th town
void show_Town_5();		//shows the 5th town

void displayMove(struct attack move);				//displays the move selected by the user
void enemyDisplayMove(struct attack move);			//displays the move selected by the opponent
void showEnemy(struct pokemon pkmn, int x, int y);	//shows the pokemons

void moveAnimation();		//creates the animation for the move selected by the user
void eMoveAnimation();		//creates the animation for the move selected by the opponent
void opponentMovement();	//creates the movement of the opponent in the battle screen
void enimMove();			//creates the movement of the opponent in a specific town

double damage_calculation(struct pokemon offense_pokemon, struct pokemon deffense_pokemon, struct attack selected_move);	//does the calculation of how much damage a move will do taking the move, the defending pokemon and offensive pokemon's attribute into account
double type_advantage(struct pokemon pkmn_type, struct attack pkmn_atk);			//determines the type advantage a move gains depending on the pokemon's type and the move's type


int pointerX, pointerY, pointerRX, pointerRY, playerX=350, playerY=50, myPkmnX=50, myPkmnY=100,moveX=100,moveY=50;
int m = 5, m2 = 5;

boolean showTown = false, notBattle = true, fight = false, moving = true, set[5] = {true,true,true,true,true}, gameOver;
boolean townVisited[5], levelCompleted[5];
boolean emoving = true, done, notPause=true;
boolean choose = false, chosen;

double damage, enemyDamage;
double slope;// = 1.66;

int t, t3, t2, t4;
int removePokemon;
int moveNumber = 0, eMoveNumber=0;
int moveSpeedIncreaser=20 , moveFrequencyIncreaser=1000;
int j, x;
int screen = 0, b, town, scene=1;
int points;
int mode, len;

char str[100], scorers[5][100], strike[30], enemyStrike[30];
char score[10];

FILE *hscore;

struct enimMove {
	int x;
	int y;
	boolean show;
}movement,enem[5];

struct attack {
	char attk_name[30];
	double power;
	double type_identifier;
	int id;
}moves[20], selectedMove, enememyMove;


struct pokemon {
	char pokemon_name[30];
	struct attack move[4];
	double level;
	double health;
	double type_identifier;
	int id;
	double getHealth()
	{
		return health + (health*(level / 3));
	}
}characters[10], myPkmn_1, myPkmn_2, myPkmn_3, enemyPkmn;


struct moveAnimation {
	int x;
	int y;
	boolean show;
}moveAnim[1000],eMoveAnim[1000],a;


struct pokemonMovement {
	double x;
	double y;
	boolean show;
}myPokemonMovement, opponentMove;

struct highScore {
	int score;
	char name[50];
}top[6], playerInfo;

//myPokemonMovement.x = 300;


							//type identifier of grass=1
							//type identifier of fire=2
							//type identifier of water=3
							//type idnetifier of flying=4
							//type identifier of fight=5
							//type identifier of electric=6
							//type identifier of normal=7 

void opponentMovement() {
	opponentMove.y += m2;
	x+=5;
	if (opponentMove.y > 560)
		m2 = -5;
	
	if (opponentMove.y < 0)
		m2 = 5;
	
	if (x % moveFrequencyIncreaser == 0 ){
		j = rand() % 4;
		slope = ((opponentMove.y - myPokemonMovement.y) / (opponentMove.x - myPokemonMovement.x));
		enememyMove = enemyPkmn.move[j];
		
		eMoveNumber++;
		eMoveAnim[eMoveNumber - 1].x = opponentMove.x;
		eMoveAnim[eMoveNumber - 1].y = opponentMove.y;
		eMoveAnim[eMoveNumber - 1].show = true;
		
		//moving = false;
	
	}

}

void attack_list() {
	/*Ember*/
	strcpy(moves[0].attk_name, "Ember");
	moves[0].power = 40;
	moves[0].type_identifier = 2;
	moves[0].id = 0;
	
	/*Flamethrower*/
	strcpy(moves[1].attk_name, "Flamethrower");
	moves[1].power = 80;
	moves[1].type_identifier = 2;
	moves[1].id = 1;
	
	/*Fire Blast*/
	strcpy(moves[2].attk_name, "Fire Blast");
	moves[2].power = 110;
	moves[2].type_identifier = 2;
	moves[2].id = 2;
	
	/*Razor Leaf*/
	strcpy(moves[3].attk_name, "Razor Leaf");
	moves[3].power = 40;
	moves[3].type_identifier = 1;
	moves[3].id = 3;
	
	/*Seed Bomb*/
	strcpy(moves[4].attk_name, "Seed Bomb");
	moves[4].power = 80;
	moves[4].type_identifier = 1;
	moves[4].id = 4;

	/*Solar Beam*/
	strcpy(moves[5].attk_name, "Solar Beam");
	moves[5].power = 110;
	moves[5].type_identifier = 1;
	moves[5].id = 5;
	
	/*Water Gun*/
	strcpy(moves[6].attk_name, "Water Gun");
	moves[6].power = 40;
	moves[6].type_identifier = 3;
	moves[6].id = 6;
	
	/*Water Pulse*/
	strcpy(moves[7].attk_name, "Water Pulse");
	moves[7].power = 80;
	moves[7].type_identifier = 3;
	moves[7].id = 7;
	
	/*Hydro Pump*/
	strcpy(moves[8].attk_name, "Hydro Pump");
	moves[8].power = 110;
	moves[8].type_identifier = 3;
	moves[8].id = 8;

	/*Tackle*/
	strcpy(moves[9].attk_name, "Tackle");
	moves[9].power = 40;
	moves[9].type_identifier = 7;
	moves[9].id = 9;
	
	/*Quick Attack*/
	strcpy(moves[10].attk_name, "Swift");
	moves[10].power = 60;
	moves[10].type_identifier = 7;
	moves[10].id = 10;
	
	/*Thundershock*/
	strcpy(moves[11].attk_name, "Thundershock");
	moves[11].power = 50;
	moves[11].type_identifier = 6;
	moves[11].id = 11;
	
	/*Thunderbolt*/
	strcpy(moves[12].attk_name, "Thunderbolt");
	moves[12].power = 80;
	moves[12].type_identifier = 6;
	moves[12].id = 12;

	/*Carate Chop*/
	strcpy(moves[13].attk_name, "Karate Chop");
	moves[13].power = 50;
	moves[13].type_identifier = 5;
	moves[13].id = 13;
	
	/*Cross Chop*/
	strcpy(moves[14].attk_name, "Cross Chop");
	moves[14].power = 80;
	moves[14].type_identifier = 5;
	moves[14].id = 14;
	
	/*Gust*/
	strcpy(moves[15].attk_name, "Gust");
	moves[15].power = 40;
	moves[15].type_identifier = 4;
	moves[15].id = 15;
	
	/*Wing Attack*/
	strcpy(moves[16].attk_name, "Wing Attack");
	moves[16].power = 70;
	moves[16].type_identifier = 4;
	moves[16].id = 16;
}


double type_advantage(struct pokemon pkmn_type, struct attack pkmn_atk)
{
	//double type_advantage;
	int atk_type = pkmn_atk.type_identifier;
	if (pkmn_type.type_identifier == 1)
	{
		switch (atk_type)
		{
		case 1:
		case 3:
			return 0.5;
		case 2:
			return 2;
		default:
			return 1;
		}

	}
	if (pkmn_type.type_identifier == 2)
	{
		switch (atk_type)
		{
		case 2:
		case 1:
			return 0.5;
		case 3:
			return 2;
		default:
			return 1;
		}

	}
	if (pkmn_type.type_identifier == 3)
	{
		switch (atk_type)
		{
		case 1:
			return 2;
		case 3:
		case 2:
			return .5;
		default:
			return 1;
		}

	}
	if (pkmn_type.type_identifier == 4)
	{
		switch (atk_type)
		{
		case 6:
			return 2;
		case 5:
		case 4:
			return .5;
		default:
			return 1;
		}

	}
	if (pkmn_type.type_identifier == 5)
	{
		switch (atk_type)
		{
		case 4:
			return 2;
		case 7:
			return 0.5;
		default:
			return 1;
		}

	}
	if (pkmn_type.type_identifier == 6)
	{
		switch (atk_type)
		{
		case 7:
			return 2;
		case 3:
		case 1:
			return .5;
		default:
			return 1;
		}

	}
	if (pkmn_type.type_identifier == 7)
	{
		switch (atk_type)
		{
		case 5:
			return 2;
		default:
			return 1;
		}

	}
}

void pokemon_list() {
	/*Bulbasaur::ID 0*/
	strcpy(characters[0].pokemon_name, "Bulbasaur");
	characters[0].type_identifier = 1;
	characters[0].move[0] = moves[3]; //razor leaf
	characters[0].move[1] = moves[9]; //tackle
	characters[0].move[2] = moves[4]; //seed bomb
	characters[0].move[3] = moves[5]; //solar beam
	characters[0].health = 200;
	characters[0].id = 0;

	/*Charmander:: ID 1*/
	strcpy(characters[1].pokemon_name, "Charmander");
	characters[1].type_identifier = 2;
	characters[1].move[0] = moves[0]; //ember
	characters[1].move[1] = moves[10]; //quick attack
	characters[1].move[2] = moves[1]; //flamethrower
	characters[1].move[3] = moves[2]; //fire blast
	characters[1].health = 188;
	characters[1].id = 1;
	//characters[1].health = 190;

	/*Squirtel:: ID 2*/
	strcpy(characters[2].pokemon_name, "Squirtel");
	characters[2].type_identifier = 3;
	characters[2].move[0] = moves[6]; //water gun
	characters[2].move[1] = moves[9]; //tackle
	characters[2].move[2] = moves[7]; //water pulse
	characters[2].move[3] = moves[8]; //hydro pump
	characters[2].health = 198;
	characters[2].id = 2;

	/*Pikachu:: ID 3*/
	strcpy(characters[3].pokemon_name, "Pikachu");
	characters[3].type_identifier = 6;
	characters[3].move[0] = moves[11]; //thundershock
	characters[3].move[1] = moves[9]; //tackle
	characters[3].move[2] = moves[10]; //quick attack
	characters[3].move[3] = moves[12]; //thunderbolt
	characters[3].health = 180;
	characters[3].id = 3;

	/*Pidgey:: ID 4*/
	strcpy(characters[4].pokemon_name, "Pidgey");
	characters[4].type_identifier = 4;
	characters[4].move[0] = moves[9]; //tackle
	characters[4].move[1] = moves[15]; //gust
	characters[4].move[2] = moves[16]; //wing attack
	characters[4].move[3] = moves[10]; //quick attack
	characters[4].health = 190;
	characters[4].id = 4;

	/*Mankey:: ID 5*/
	strcpy(characters[5].pokemon_name, "Mankey");
	characters[5].type_identifier = 5;
	characters[5].move[0] = moves[9]; //tackle
	characters[5].move[1] = moves[13]; //carate chop
	characters[5].move[2] = moves[14]; //cross chop
	characters[5].move[3] = moves[10]; //quick attack
	characters[5].health = 190;
	characters[5].id = 5;

	/*Ponyta:: ID 6*/
	strcpy(characters[6].pokemon_name, "Ponyta");
	characters[6].type_identifier = 2;
	characters[6].move[0] = moves[9]; //tackle
	characters[6].move[1] = moves[10]; //quick attack
	characters[6].move[2] = moves[0]; //ember
	characters[6].move[3] = moves[1]; //flamethrower
	characters[6].health = 210;
	characters[6].id = 6;

	/*Porygon:: ID 7*/
	strcpy(characters[7].pokemon_name, "Porygon");
	characters[7].type_identifier = 7;
	characters[7].move[0] = moves[10]; //quick attack
	characters[7].move[1] = moves[9]; //tackle
	characters[7].move[2] = moves[12]; //thunderbolt
	characters[7].move[3] = moves[6]; //water gun
	characters[7].health = 240; 
	characters[7].id = 7;

	/*Exeggutor:: ID 8*/
	strcpy(characters[8].pokemon_name, "Exeggutor");
	characters[8].type_identifier = 1;
	characters[8].move[0] = moves[10]; //quick attack
	characters[8].move[1] = moves[4]; //seed bomb
	characters[8].move[2] = moves[5]; //solar beam
	characters[8].move[3] = moves[3]; //razor leaf
	characters[8].health = 300;
	characters[8].id = 8;

	/*Polywrath:: ID 9*/
	strcpy(characters[9].pokemon_name, "Polywrath");
	characters[9].type_identifier = 3;
	characters[9].move[0] = moves[7]; //water pulse
	characters[9].move[1] = moves[8]; //hydro pump
	characters[9].move[2] = moves[13]; //carate chop
	characters[9].move[3] = moves[14]; //cross chop
	characters[9].health = 290;
	characters[9].id = 9;

}


void showEnemy(struct pokemon pkmn,int x, int y)
{
	switch (pkmn.id) 
	{
	case 4:
		iShowBMP(x,y, "pidgey.bmp");
		break;
	case 1:
		iShowBMP(x,y, "charmander.bmp");
		break;
	case 0:
		iShowBMP(x, y, "bulbasaur.bmp");
		break;
	case 2:
		iShowBMP(x, y, "squirtel.bmp");
		break;
	case 3:
		iShowBMP(x, y, "pikachu.bmp");
		break;
	case 5:
		iShowBMP(x, y, "mankey.bmp");
		break;
	case 6:
		iShowBMP(x, y, "ponyta.bmp");
		break;
	case 7:
		iShowBMP(x, y, "porygon.bmp");
		break;
	case 8:
		iShowBMP(x, y, "exeguttor.bmp");
		break;
	case 9:
		iShowBMP(x, y, "polywrath.bmp");
		break;
	}
}

void displayMove(struct attack move) {
	switch (move.id) {
	case 0:
		for (int i=0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "ember.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 1:
		for (int i=0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "flamethrower.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 2:
		for (int i=0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "fireblast.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 3:
		for (int i = 0; i < moveNumber; i++) {
			if (moveAnim[i].show) {
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "razorleaf.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 4:
		for (int i = 0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "seedbomb.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 5:
		for (int i = 0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "solarbeam.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 6:
		for (int i = 0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "watergun.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 7:
		for (int i = 0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "waterpulse.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 8:
		for (int i = 0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "hydropump.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 9:		
		for (int i = 0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "tackle.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
	}
		break;
	case 10:
		for (int i = 0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "swift.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 11:
		for (int i = 0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "thundershock.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 12:
		for (int i = 0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "thunderbolt.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 13:
		for (int i = 0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "karatechop.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 14:
		for (int i = 0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "crosschop.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 15:
		for (int i = 0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "gust.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 16:
		for (int i = 0; i < moveNumber; i++) {
			if (moveAnim[i].show)
			{
				iShowBMP(moveAnim[i].x, moveAnim[i].y, "wingattack.bmp");
				iText(100, 600, strike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;

	}

}

void enemyDisplayMove(struct attack move) {
	switch (move.id) {
	case 0:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "ember.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 1:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "flamethrower.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 2:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "fireblast.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 3:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "razorleaf.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 4:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "seedbomb.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 5:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "solarbeam.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 6:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "watergun.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 7:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "waterpulse.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 8:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "hydropump.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 9:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "tackle.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 10:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "swift.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 11:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "thundershock.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 12:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "thunderbolt.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 13:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "karatechop.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 14:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "crosschop.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 15:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "gust.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;
	case 16:
		for (int i = 0; i < eMoveNumber; i++) {
			if (eMoveAnim[i].show)
			{
				iShowBMP(eMoveAnim[i].x, eMoveAnim[i].y, "wingattack.bmp");
				iText(750, 600, enemyStrike, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		break;

	}

}


void setEnimPos() 
{
		
	enem[0].x = 10;
	enem[0].y = rand()%40;
	enem[1].x = 70;
	enem[1].y = rand()%40+125;
	enem[2].x = 100;
	enem[2].y = rand()%40 +250;
	enem[3].x = 700;
	enem[3].y = rand()%40 + 370;
	enem[4].x = 80;
	enem[4].y = rand()%40 + 495;
	opponentMove.x = 700;
}

void enimMove() {
	for (int i = 0; i < 5; i++)
	{
		enem[i].x += m;
		if (enem[i].x > 900)
			enem[i].x = rand() % 300;
	}
}

double damage_calculation(struct pokemon offense_pokemon, struct pokemon deffense_pokemon, struct attack selected_move) {
	
	double damage;
	
	damage = ((selected_move.power+(selected_move.power*offense_pokemon.level/3))/deffense_pokemon.level)*type_advantage(deffense_pokemon,selected_move);
	
	return damage;
}


void moveAnimation() {
	for (int i = 0; i < moveNumber; i++)
	{
		if (moveAnim[i].show)
			moveAnim[i].x += 20;
		if (moveAnim[i].x > 960|| notBattle) {
			moveAnim[i].show = false;
			moveAnim[i].x = 9000;
		}
		if ((moveAnim[i].x + 64 > opponentMove.x&&moveAnim[i].x < opponentMove.x + 80) && (moveAnim[i].y + 64 > opponentMove.y&&moveAnim[i].y < opponentMove.y + 80))
		{
			moveAnim[i].show = false;
			moveAnim[i].x = 9000;
			damage += damage_calculation(myPkmn_1, enemyPkmn, selectedMove);
		}
	}
}

void eMoveAnimation() {
	for (int i = 0; i < eMoveNumber; i++)
	{
		if (eMoveAnim[i].show) {
			eMoveAnim[i].x -= moveSpeedIncreaser;
			eMoveAnim[i].y -= (slope * moveSpeedIncreaser);
		}
		
		if (eMoveAnim[i].x < 0||eMoveAnim[i].y<0||eMoveAnim[i].y>640) {
			eMoveAnim[i].show = false;
			eMoveAnim[i].x = -100;
		}
		
		if ((eMoveAnim[i].x < myPokemonMovement.x+80 && eMoveAnim[i].x +64 > myPokemonMovement.x) && (eMoveAnim[i].y + 64 > myPokemonMovement.y && eMoveAnim[i].y < myPokemonMovement.y + 80))
		{
			eMoveAnim[i].show = false;
			eMoveAnim[i].x = -100;
			enemyDamage += damage_calculation(enemyPkmn, myPkmn_1, enememyMove);
		}
	}
}

void battle() {
	iClear();
	iSetColor(255, 255, 255);
	iFilledRectangle(0, 0, 960, 640);
	showEnemy(enemyPkmn,opponentMove.x,opponentMove.y);
	showEnemy(myPkmn_1, myPokemonMovement.x, myPokemonMovement.y);
	iSetColor(23, 57, 200);
	iFilledRectangle(100, 150, (myPkmn_1.health-enemyDamage), 30);
	iFilledRectangle(600, 500, (enemyPkmn.health-damage), 30);
	
	iShowBMP(50, 80, "z.bmp");
	iShowBMP(200, 80, "x.bmp");
	iShowBMP(50, 40, "c.bmp");
	iShowBMP(200, 40, "v.bmp");

	iSetColor(88, 88, 88);
	iText(80, 80, myPkmn_1.move[0].attk_name,GLUT_BITMAP_HELVETICA_18);
	iText(230, 80, myPkmn_1.move[1].attk_name, GLUT_BITMAP_HELVETICA_18);
	
	if (myPkmn_1.level > 1)
		iText(80, 45, myPkmn_1.move[2].attk_name, GLUT_BITMAP_HELVETICA_18);
	else
		iText(80, 45, "BLOCKED!", GLUT_BITMAP_HELVETICA_18);
	
	
	if (myPkmn_1.level > 2)
		iText(230, 45, myPkmn_1.move[3].attk_name, GLUT_BITMAP_HELVETICA_18);
	else
		iText(230, 45, "BLOCKED!", GLUT_BITMAP_HELVETICA_18);

}


void show_Town_1() {
	townVisited[0] = true;
	int i;
	iClear();
	moveSpeedIncreaser = 20;
	moveFrequencyIncreaser = 1000;

	if (set[0]) {
		setEnimPos();
		set[0] = false;
	}
	iShowBMP(0, 0, "tut.bmp");
	iShowBMP2(playerX, playerY, "player.bmp", 0);
	iResumeTimer(t);
	iShowBMP(enem[0].x, enem[0].y, "pikachu.bmp");
	iShowBMP(enem[1].x, enem[1].y, "bulbasaur.bmp");
	iShowBMP(enem[2].x, enem[2].y, "pikachu.bmp");
	iShowBMP(enem[3].x, enem[3].y, "pidgey.bmp");
	iShowBMP(enem[4].x, enem[4].y, "mankey.bmp");
	
	iSetColor(63, 72, 204);
	iShowBMP(0, 600, "townmap.bmp");
	iText(800, 600, score, GLUT_BITMAP_HELVETICA_18);
	
	if ((pointerX > 0 && pointerX < 120) && (pointerY > 600 && pointerY < 640))
	{
		town_map();
	}

	if ((playerX +64> enem[3].x&&playerX < enem[3].x + 80) && (playerY+64 > enem[3].y&&playerX < enem[3].y + 80))
	{
		enemyPkmn = characters[4];
		enemyPkmn.level = 1;
		notBattle = false;
		iPauseTimer(t);
		iResumeTimer(t3);
		removePokemon = 3;
		//battle();
	}


	if ((playerX + 64> enem[0].x&&playerX < enem[0].x + 80) && (playerY + 64 > enem[0].y&&playerY < enem[0].y + 80))
	{
		enemyPkmn = characters[3];
		enemyPkmn.level = 1;
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 0;
		//battle();
	}
	
	
	if ((playerX + 64> enem[1].x&&playerX < enem[1].x + 80) && (playerY + 64 > enem[1].y&&playerY < enem[1].y + 80))
	{
		enemyPkmn = characters[0];
		enemyPkmn.level = 1;
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 1;
		//battle();
	}
	
	
	if ((playerX + 64> enem[2].x&&playerX < enem[2].x + 80) && (playerY + 64 > enem[2].y&&playerX < enem[2].y + 80))
	{
		enemyPkmn = characters[3];
		enemyPkmn.level = 1;
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 2;
		//battle();
	}
	
	
	if ((playerX + 64> enem[4].x&&playerX < enem[4].x + 80) && (playerY + 64 > enem[4].y&&playerX < enem[4].y + 80))
	{
		enemyPkmn = characters[5];
		enemyPkmn.level = 1;
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 4;
		//battle();
	}
	
	
	for (i = 0; i < 5; i++) 
	{
		if (enem[i].y > 2000)
			continue;
		else
			break;
	}
	if (i >= 5)
	{
		levelCompleted[0] = true;
		iSetColor(236, 28, 36);
		iText(380, 500, "Town Cleared", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	
	if (points < 0)
		gameOver = true;
}


void show_Town_2() {
	townVisited[1] = true;
	iClear();

	moveFrequencyIncreaser = 900;
	moveSpeedIncreaser = 22;

	if (set[1]) {
		setEnimPos();
		set [1]= false;
	}
	iShowBMP(0, 0, "town.bmp");
	iShowBMP2(playerX, playerY, "player.bmp", 0);
	iResumeTimer(t);
	
	iShowBMP(enem[0].x, enem[0].y, "bulbasaur.bmp");
	iShowBMP(enem[1].x, enem[1].y, "squirtel.bmp");
	iShowBMP(enem[2].x, enem[2].y, "pikachu.bmp");
	iShowBMP(enem[3].x, enem[3].y, "bulbasaur.bmp");
	iShowBMP(enem[4].x, enem[4].y, "ponyta.bmp");
	
	iSetColor(63, 72, 204);
	iShowBMP(0, 600, "townmap.bmp");
	iText(800, 600, score, GLUT_BITMAP_HELVETICA_18);
	
	if ((pointerX > 0 && pointerX < 120) && (pointerY > 600 && pointerY < 640))
	{
		town_map();
	}
	
	if ((playerX + 64> enem[3].x&&playerX < enem[3].x + 80) && (playerY + 64 > enem[3].y&&playerX < enem[3].y + 80))
	{
		enemyPkmn = characters[0];
		enemyPkmn.level = 1;
		notBattle = false;
		iPauseTimer(t);
		iResumeTimer(t3);
		removePokemon = 3;
		//battle();
	}
	
	
	if ((playerX + 64> enem[0].x&&playerX < enem[0].x + 80) && (playerY + 64 > enem[0].y&&playerY < enem[0].y + 80))
	{
		enemyPkmn = characters[0];
		enemyPkmn.level = 1;
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 0;
		//battle();
	}
	
	
	if ((playerX + 64> enem[1].x&&playerX < enem[1].x + 80) && (playerY + 64 > enem[1].y&&playerY < enem[1].y + 80))
	{
		enemyPkmn = characters[2];
		enemyPkmn.level = 1;
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 1;
		//battle();
	}
	
	
	if ((playerX + 64> enem[2].x&&playerX < enem[2].x + 80) && (playerY + 64 > enem[2].y&&playerY < enem[2].y + 80))
	{
		enemyPkmn = characters[3];
		enemyPkmn.level = 1;
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 2;
		//battle();
	}
	
	
	if ((playerX + 64 > enem[4].x&&playerX < enem[4].x + 80) && (playerY + 64 > enem[4].y&&playerX < enem[4].y + 80))
	{
		enemyPkmn = characters[6];
		enemyPkmn.level = 1;
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 4;
	}
	
	if (points < 2000)
		gameOver = true;
	int i;
	
	for (i = 0; i < 5; i++) {
		if (enem[i].y > 2000)
			continue;
		else
			break;
	}
	
	if (i >= 5)
	{
		levelCompleted[1] = true;
		iSetColor(236, 28, 36);
		iText(380, 500, "Town Cleared", GLUT_BITMAP_TIMES_ROMAN_24);
	}
}


void show_Town_3() {
	
	townVisited[2] = true;
	iClear();

	moveFrequencyIncreaser = 800;
	moveSpeedIncreaser = 24;
	if (set[2]) {
		setEnimPos();
		set[2] = false;
	}
	iShowBMP(0, 0, "town4.bmp");
	iShowBMP2(playerX, playerY, "player.bmp", 0);
	iResumeTimer(t);
	
	iShowBMP(enem[0].x, enem[0].y, "squirtel.bmp");
	iShowBMP(enem[1].x, enem[1].y, "charmander.bmp");
	iShowBMP(enem[2].x, enem[2].y, "pikachu.bmp");
	iShowBMP(enem[3].x, enem[3].y, "bulbasaur.bmp");
	iShowBMP(enem[4].x, enem[4].y, "mankey.bmp");
	
	iSetColor(63, 72, 204);
	iShowBMP(0, 600, "townmap.bmp");
	iText(800, 600, score, GLUT_BITMAP_HELVETICA_18);
	
	if ((pointerX > 0 && pointerX < 120) && (pointerY > 600 && pointerY < 640))
	{
		town_map();
	}

	if ((playerX + 64> enem[3].x&&playerX < enem[3].x + 80) && (playerY + 64 > enem[3].y&&playerX < enem[3].y + 80))
	{
		enemyPkmn = characters[0];
		enemyPkmn.level = 2;
		enemyPkmn.health = enemyPkmn.getHealth();
		notBattle = false;
		iPauseTimer(t);
		iResumeTimer(t3);
		removePokemon = 3;
		//battle();
	}
	
	
	if ((playerX + 64> enem[0].x&&playerX < enem[0].x + 80) && (playerY + 64 > enem[0].y&&playerY < enem[0].y + 80))
	{
		enemyPkmn = characters[2];
		enemyPkmn.level = 2;
		enemyPkmn.health = enemyPkmn.getHealth();
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 0;
		//battle();
	}
	
	
	if ((playerX + 64> enem[1].x&&playerX < enem[1].x + 80) && (playerY + 64 > enem[1].y&&playerY < enem[1].y + 80))
	{
		enemyPkmn = characters[1];
		enemyPkmn.level = 2;
		enemyPkmn.health = enemyPkmn.getHealth();
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 1;
		//battle();
	}
	
	
	if ((playerX + 64> enem[2].x&&playerX < enem[2].x + 80) && (playerY + 64 > enem[2].y&&playerX < enem[2].y + 80))
	{
		enemyPkmn = characters[3];
		enemyPkmn.level = 2;
		enemyPkmn.health = enemyPkmn.getHealth();
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 2;
		//battle();
	}
	
	
	if ((playerX + 64 > enem[4].x&&playerX < enem[4].x + 80) && (playerY + 64 > enem[4].y&&playerX < enem[4].y + 80))
	{
		enemyPkmn = characters[5];
		enemyPkmn.level = 2;
		enemyPkmn.health = enemyPkmn.getHealth();
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 4;
	}
	
	
	if (points < 5000)
		gameOver = true;
	int i;
	
	for (i = 0; i < 5; i++) {
		if (enem[i].y > 2000)
			continue;
		else
			break;
	}
	if (i >= 5)
	{
		levelCompleted[2] = true;
		iSetColor(236, 28, 36);
		iText(380, 500, "Town Cleared", GLUT_BITMAP_TIMES_ROMAN_24);
	}
}


void show_Town_4() {
	
	townVisited[3] = true;
	iClear();

	moveFrequencyIncreaser = 700;
	moveSpeedIncreaser = 26;
	if (set[3]) {
		setEnimPos();
		set[3] = false;
	}
	iShowBMP(0, 0, "town4.bmp");
	iShowBMP2(playerX, playerY, "player.bmp", 0);
	iResumeTimer(t);
	
	iShowBMP(enem[0].x, enem[0].y, "charmander.bmp");
	iShowBMP(enem[1].x, enem[1].y, "pidgey.bmp");
	iShowBMP(enem[2].x, enem[2].y, "mankey.bmp");
	iShowBMP(enem[3].x, enem[3].y, "ponyta.bmp");
	iShowBMP(enem[4].x, enem[4].y, "porygon.bmp");
	
	iSetColor(63, 72, 204);
	iShowBMP(0, 600, "townmap.bmp");
	iText(800, 600, score, GLUT_BITMAP_HELVETICA_18);
	
	if ((pointerX > 0 && pointerX < 120) && (pointerY > 600 && pointerY < 640))
	{
		town_map();
	}
	
	
	if ((playerX + 64> enem[3].x&&playerX < enem[3].x + 80) && (playerY + 64 > enem[3].y&&playerX < enem[3].y + 80))
	{
		enemyPkmn = characters[6];
		enemyPkmn.level = 2;
		enemyPkmn.health = enemyPkmn.getHealth();
		notBattle = false;
		iPauseTimer(t);
		iResumeTimer(t3);
		removePokemon = 3;
		//battle();
	}
	
	
	if ((playerX + 64> enem[0].x&&playerX < enem[0].x + 80) && (playerY + 64 > enem[0].y&&playerY < enem[0].y + 80))
	{
		enemyPkmn = characters[1];
		enemyPkmn.level = 3;
		enemyPkmn.health = enemyPkmn.getHealth();
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 0;
		//battle();
	}
	
	
	if ((playerX + 64> enem[1].x&&playerX < enem[1].x + 80) && (playerY + 64 > enem[1].y&&playerY < enem[1].y + 80))
	{
		enemyPkmn = characters[4];
		enemyPkmn.level = 2;
		enemyPkmn.health = enemyPkmn.getHealth();
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 1;
		//battle();
	}
	
	
	if ((playerX + 64> enem[2].x&&playerX < enem[2].x + 80) && (playerY + 64 > enem[2].y&&playerX < enem[2].y + 80))
	{
		enemyPkmn = characters[5];
		enemyPkmn.level = 3;
		enemyPkmn.health = enemyPkmn.getHealth();
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 2;
		//battle();
	}
	
	
	if ((playerX + 64 > enem[4].x&&playerX < enem[4].x + 80) && (playerY + 64 > enem[4].y&&playerX < enem[4].y + 80))
	{
		enemyPkmn = characters[7];
		enemyPkmn.level = 2;
		enemyPkmn.health = enemyPkmn.getHealth();
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 4;
	}
	
	if (points < 8000)
		gameOver = true;
	int i;
	
	for (i = 0; i < 5; i++) {
		if (enem[i].y > 2000)
			continue;
		else
			break;
	}
	if (i >= 5)
	{
		levelCompleted[3] = true;
		iSetColor(236, 28, 36);
		iText(380, 500, "Town Cleared", GLUT_BITMAP_TIMES_ROMAN_24);
	}
}


void show_Town_5() {
	iClear();

	townVisited[4] = true;
	moveFrequencyIncreaser = 500;
	moveSpeedIncreaser = 30;
	if (set[4]) {
		setEnimPos();
		set[4] = false;
	}
	iShowBMP(0, 0, "town5.bmp");
	iShowBMP2(playerX, playerY, "player.bmp", 0);
	iResumeTimer(t);
	
	iShowBMP(enem[0].x, enem[0].y, "exeguttor.bmp");
	iShowBMP(enem[1].x, enem[1].y, "polywrath.bmp");
	iShowBMP(enem[2].x, enem[2].y, "mankey.bmp");
	iShowBMP(enem[3].x, enem[3].y, "ponyta.bmp");
	iShowBMP(enem[4].x, enem[4].y, "porygon.bmp");
	
	iSetColor(63, 72, 204);
	iShowBMP(0, 600, "townmap.bmp");
	iText(800, 600, score, GLUT_BITMAP_HELVETICA_18);
	
	if ((pointerX > 0 && pointerX < 120) && (pointerY > 600 && pointerY < 640))
	{
		town_map();
	}
	
	
	if ((playerX + 64> enem[3].x&&playerX < enem[3].x + 80) && (playerY + 64 > enem[3].y&&playerX < enem[3].y + 80))
	{
		enemyPkmn = characters[6];
		enemyPkmn.level = 3;
		enemyPkmn.health = enemyPkmn.getHealth();
		notBattle = false;
		iPauseTimer(t);
		iResumeTimer(t3);
		removePokemon = 3;
		//battle();
	}
	
	
	if ((playerX + 64> enem[0].x&&playerX < enem[0].x + 80) && (playerY + 64 > enem[0].y&&playerY < enem[0].y + 80))
	{
		enemyPkmn = characters[8];
		enemyPkmn.level = 3;
		enemyPkmn.health = enemyPkmn.getHealth();
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 0;
		//battle();
	}
	
	
	if ((playerX + 64> enem[1].x&&playerX < enem[1].x + 80) && (playerY + 64 > enem[1].y&&playerY < enem[1].y + 80))
	{
		enemyPkmn = characters[9];
		enemyPkmn.level = 3;
		enemyPkmn.health = enemyPkmn.getHealth();
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 1;
		//battle();
	}
	
	
	if ((playerX + 64> enem[2].x&&playerX < enem[2].x + 80) && (playerY + 64 > enem[2].y&&playerX < enem[2].y + 80))
	{
		enemyPkmn = characters[5];
		enemyPkmn.level = 3;
		enemyPkmn.health = enemyPkmn.getHealth();
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 2;
		//battle();
	}
	
	
	if ((playerX + 64 > enem[4].x&&playerX < enem[4].x + 80) && (playerY + 64 > enem[4].y&&playerX < enem[4].y + 80))
	{
		enemyPkmn = characters[7];
		enemyPkmn.level = 2;
		enemyPkmn.health = enemyPkmn.getHealth();
		notBattle = false;
		iResumeTimer(t3);
		iPauseTimer(t);
		removePokemon = 4;
	}
	
	if (points <11000)
		gameOver = true;
	int i;
	
	for (i = 0; i < 5; i++) {
		if (enem[i].y > 2000)
			continue;
		else
			break;
	}
	
	if (i >= 5)
	{
		levelCompleted[4] = true;
		iSetColor(236, 28, 36);
		iText(380, 500, "Town Cleared", GLUT_BITMAP_TIMES_ROMAN_24);
	}
}


void town_map()
{
	iClear();
	//set = true;

	iSetColor(250, 250, 250);
	iFilledRectangle(0, 0, 960, 640);

	iSetColor(255, 0, 0);
	iFilledRectangle(438, 85, 60, 60);
	iFilledRectangle(53, 500, 60, 60);
	iFilledRectangle(847, 185, 60, 60);
	iFilledRectangle(847, 510, 60, 60);
	iFilledRectangle(313, 290, 60, 60);

	iSetColor(185, 122, 86);
	iFilledRectangle(113, 510, 110, 40);
	iFilledRectangle(183, 195, 40, 315);
	iFilledRectangle(223, 300, 90, 40);
	iFilledRectangle(857, 245, 40, 265);
	iFilledRectangle(183, 195, 664, 40);
	iFilledRectangle(448, 145, 40, 50);

	iSetColor(0, 168, 243);
	iFilledEllipse(529, 469, 230, 80);

	iSetColor(88, 88, 88);
	iText(695, 76, "Town Map", GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(63, 72, 204);
	iText(849, 170, "Pacific Lodge Town");
	iText(36, 489, "Sootopolis Town");
	iText(825, 577, "Little Room Town");
	iText(301, 273, "Vanderturf Town");
	iText(415, 69, "Dewford Town");

	iSetColor(14, 209, 69);
	iText(36, 469, "(Points Required:0)", GLUT_BITMAP_HELVETICA_10);
	iText(849, 150, "(Points Required:5000)", GLUT_BITMAP_HELVETICA_10);
	iText(295, 253, "(Points Required:2000)", GLUT_BITMAP_HELVETICA_10);

	iText(825, 597, "(Points Required:8000)", GLUT_BITMAP_HELVETICA_10);
	iText(410, 49, "(Points Required:11000)", GLUT_BITMAP_HELVETICA_10);

	iSetColor(63, 72, 204);
	iText(800, 600, score, GLUT_BITMAP_HELVETICA_18);

	
					/*Town Selection Portion*/
	if ((pointerX > 53 && pointerX < 113) && (pointerY > 500 && pointerY < 540))
	{
		show_Town_1();
	}
	if ((pointerX > 313 && pointerX < 373) && (pointerY > 290 && pointerY < 350))
	{
		if (points >= 2000||townVisited[1])
			show_Town_2();
		else
		{
			iSetColor(0, 0, 0);
			iText(120, 76, "Not Enough Points!!", GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
	if ((pointerX > 847 && pointerX < 907) && (pointerY > 185 && pointerY < 245))
	{
		if (points >= 5000|| townVisited[2])
			show_Town_3();
		else
		{
			iSetColor(0, 0, 0);
			iText(120, 76, "Not Enough Points!!", GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
	if ((pointerX > 847 && pointerX < 907) && (pointerY > 510 && pointerY < 570))
	{
		if (points >= 8000|| townVisited[3])
			show_Town_4();
		else
		{
			iSetColor(0, 0, 0);
			iText(120, 76, "Not Enough Points!!", GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
	if ((pointerX > 438 && pointerX < 498) && (pointerY > 85 && pointerY < 145))
	{
		if (points >= 11000|| townVisited[4])
			show_Town_5();
		else
		{
			iSetColor(0, 0, 0);
			iText(120, 76, "Not Enough Points!!", GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
}


void screen_1()
{
	iClear();
	iShowBMP(0, 0, "tut.bmp");


	iShowBMP2(playerX, playerY, "player.bmp", 0);
	iShowBMP(200, 300, "house_1.bmp");
	iShowBMP(600, 350, "house_2.bmp");

	if ((playerX > 200 && playerX < 400) && (playerY > 236 && playerY < 436))
	{
		if (chosen)
			showTown = true;
		else
			iText(300, 600, "Choose Pokemon First!!!", GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if ((playerX > 600 && playerX < 800) && (playerY > 286 && playerY < 486))
	{
		choose = true;
	}
}
void choice() {

	iClear();
	iSetColor(240, 240, 240);
	iFilledRectangle(0, 0, 960, 640);

	iShowBMP(200, 350, "bulbasaur.bmp");
	iShowBMP2(400, 350, "charmander.bmp",0);
	iShowBMP(600, 350, "squirtel.bmp");

	iSetColor(255, 0, 0);
	iText(320, 280, "Choose your Pokemon!", GLUT_BITMAP_TIMES_ROMAN_24);

	if ((pointerX > 200 && pointerX < 280) && (pointerY > 350 && pointerY < 430)) {
		myPkmn_1 = characters[0];
		myPkmn_1.level = 1;
		chosen = true;
		iSetColor(32, 64, 128);
		iText(320, 590, "You chose Bulbasaur!", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(600, 90, "23.bmp");
	}

	if ((pointerX > 400 && pointerX < 480) && (pointerY > 350 && pointerY < 430)) {
		myPkmn_1 = characters[1];
		myPkmn_1.level = 1;
		chosen = true;
		iSetColor(32, 64, 128);
		iText(320, 590, "You chose Charmander!", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(600, 90, "23.bmp");
	}

	if ((pointerX > 600 && pointerX < 680) && (pointerY > 350 && pointerY < 430)) {

		myPkmn_1 = characters[2];
		myPkmn_1.level = 1;
		chosen = true;
		iSetColor(32, 64, 128);
		iText(320, 590, "You chose Squirtel!", GLUT_BITMAP_TIMES_ROMAN_24);
		//iText(650, 90, "Press here to return to last screen");
		iShowBMP(600, 90, "23.bmp");
	}
}
void game() {
	iClear();
	
	_itoa(points, score, 10);
	if (scene == 1)
	{
		screen_1();
	}
	if (choose)
	{
		choice();
	}
	if ((pointerX > 600 && pointerX < 940) && (pointerY > 90 && pointerY < 130))
	{
		scene = 1;
		choose = false;
		screen_1();
	}

	if (showTown)
	{
		town_map();
	}
	if (points > 5000) {
		myPkmn_1.level = 2;
	}
	if (points > 10000) {
		myPkmn_1.level = 3;
	}
	if (!notBattle) {
		battle();
	}
	
	
	if (damage > enemyPkmn.health)
	{
		notBattle = true;
		iPauseTimer(t3);
		enem[removePokemon].y = 9000;
		iResumeTimer(t);
		damage = 0;
		enemyDamage = 0;
		eMoveNumber = 0;
		x = 0;
		points += 1000;
	}
	
	
	if (enemyDamage > myPkmn_1.health) {
		notBattle = true;
		iPauseTimer(t3);
		iResumeTimer(t);
		enem[removePokemon].y = 9000;
		damage = 0;
		enemyDamage = 0;
		eMoveNumber = 0;
		x = 0;
		points -= 500;
	}
	
	displayMove(selectedMove);
	sprintf(strike, "Used %s", selectedMove.attk_name);
	
	if (!notBattle)
	{
		enemyDisplayMove(enememyMove);
		sprintf(enemyStrike, "Used %s", enememyMove.attk_name);
	}
	
	int i;
	for (i = 0; i < 5; i++)
	{
		if (levelCompleted[i])
			continue;
		else
			break;
	}
	
	if (i >= 5)
		gameOver = true;
}
void menu() {
	iClear();

	iShowBMP(0, 0, "pkon.bmp");
	iShowBMP(370, 380, "play.bmp");
	iShowBMP(370, 310, "ins.bmp");
	iShowBMP(370, 240, "high.bmp");
	iShowBMP(370, 170, "credit.bmp");
	iShowBMP(370, 100, "exit.bmp");
}

void credit() {
	iClear();

	iShowBMP(0, 0, "credits.bmp");
	iShowBMP(750, 80, "back.bmp");
}

void instruction() {
	iClear();

	iShowBMP(0, 0, "instruction.bmp");
	iShowBMP(750, 70, "back.bmp");
}
void high() {
	iClear();

	iShowBMP(0, 0, "highscore.bmp");
	iShowBMP(370, 380, "box.bmp");
	iShowBMP(370, 310, "box.bmp");
	iShowBMP(370, 240, "box.bmp");
	iShowBMP(370, 170, "box.bmp");
	iShowBMP(370, 100, "box.bmp");
	iShowBMP(750, 80, "back.bmp");

	hscore = fopen("highscore.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(hscore, "%s %d\n", &top[i].name, &top[i].score);
		sprintf(scorers[i], "Name: %s Score:%d", top[i].name, top[i].score);
	}
	fclose(hscore);

	iSetColor(0, 168, 243);
	iText(380, 400, scorers[0], GLUT_BITMAP_HELVETICA_18);
	iText(380, 330, scorers[1], GLUT_BITMAP_HELVETICA_18);
	iText(380, 260, scorers[2], GLUT_BITMAP_HELVETICA_18);
	iText(380, 190, scorers[3], GLUT_BITMAP_HELVETICA_18);
	iText(380, 120, scorers[4], GLUT_BITMAP_HELVETICA_18);

}


void exit() {
	exit(0);
}
void gameover() {
	//screen = 14;
	struct highScore temp;
	iShowBMP(0, 0, "gameover.bmp");

	
	iShowBMP(370, 100, "box.bmp");
	iShowBMP(750, 50, "exit2.bmp");

	char tempScore[30];
	iSetColor(200, 200, 200);
	sprintf(tempScore, "Your Score is: %d", points);
	iText(370, 520, tempScore, GLUT_BITMAP_TIMES_ROMAN_24);
	
	if (mode == 1)
	{
		iSetColor(255, 255, 255);
		iText(375, 110, str);
	}
	if (done)
	{
		hscore = fopen("highscore.txt", "r");
		for (int p = 0; p < 5; p++) {
			fscanf(hscore, "%s %d\n", &top[p].name, &top[p].score);
		}
		fclose(hscore);
		playerInfo.score = points;

		if (playerInfo.score > top[4].score)
			top[5] = playerInfo;

		for (int i = 0; i < 6; i++) {
			for (int j = 1; j < 6 - i; j++) {
				if (top[j].score > top[j - 1].score) {
					temp = top[j - 1];
					top[j - 1] = top[j];
					top[j] = temp;
				}
			}
		}
		hscore = fopen("highscore.txt", "w");
		for (int p = 0; p < 5; p++) {
			fprintf(hscore, "%s %d\n", top[p].name, top[p].score);
		}
		fclose(hscore);
		done = false;
	}

	iText(310, 10, "Click to activate the box, enter to finish.");
}

void pause() {
	iShowBMP(0, 0, "pause.bmp");
	iShowBMP(370, 500, "resume.bmp");
	iShowBMP(750, 70, "back.bmp");
}

void iDraw()
{
	//place your drawing codes here	
	iClear();

	if (screen == 0)
		menu();
	if (screen == 9)
	{
		if (notPause)
		{
			game();
			iResumeTimer(t2);
			iResumeTimer(t4);
		}
		else
			pause();
	}
	if (screen == 10)
		instruction();
	if (screen == 11)
		high();
	if (screen == 12)
		credit();
	if (screen == 13)
		exit();
	if (gameOver)
		gameover();

}

void iMouseMove(int mx, int my)
{
	//place your codes here
}


void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
		pointerX = mx;
		pointerY = my;
		//printf("%d   %d\n", pointerX, pointerY);
		if (gameOver)
		{
			if ((pointerX > 370 && pointerX < 590) && (pointerY > 100 && pointerY < 150))
				mode = 1;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
		pointerRX = mx;
		pointerRY = my;
		if (screen == 0) {
			if ((pointerRX > 370 && pointerRX < 590) && (pointerRY > 380 && pointerRY < 430))
			{
				notPause = true;
				screen = 9;
			}
			if ((pointerRX > 370 && pointerRX < 590) && (pointerRY > 310 && pointerRY < 360))
				screen = 10;
			if ((pointerRX > 370 && pointerRX < 590) && (pointerRY > 240 && pointerRY < 290))
				screen = 11;
			if ((pointerRX > 370 && pointerRX < 590) && (pointerRY > 170 && pointerRY < 220))
				screen = 12;
			if ((pointerRX > 370 && pointerRX < 590) && (pointerRY > 100 && pointerRY < 150))
				screen = 13;
		}
		if (screen == 9) {
			if (!notPause) {
				if ((pointerRX > 750 && pointerRX < 900) && (pointerRY > 70 && pointerRY < 120))
					screen = 0;
				if ((pointerRX > 370 && pointerRX < 590) && (pointerRY > 500 && pointerRY < 550))
					notPause = true;
			}
		}
		if (screen == 10) {
			if ((pointerRX > 750 && pointerRX < 900) && (pointerRY > 70 && pointerRY < 120))
				screen = 0;
		}
		if (screen == 11) {
			if ((pointerRX > 750 && pointerRX < 900) && (pointerRY > 80 && pointerRY < 130))
				screen = 0;
		}
		if (screen == 12) {
			if ((pointerRX > 750 && pointerRX < 900) && (pointerRY > 80 && pointerRY < 130))
				screen = 0;
		}
		if (screen == 14) {
			if ((pointerRX > 750 && pointerRX < 900) && (pointerRY > 80 && pointerRY < 130))
				screen = 0;
		}
		if (gameOver)
		{
			if ((pointerRX > 750 && pointerRX < 900) && (pointerRY > 80 && pointerRY < 130))
				screen = 13;
		}
	}
}



void iPassiveMouseMove(int mx, int my)
{
	//place your code here

	if (mx == 2) {}        /*Something to do with mx*/
	else if (my == 2) {}   /*Something to do with my*/

}


void iKeyboard(unsigned char key)
{
	//if (b == 1) {
	int i;
	if (mode == 1) {
		if (key == '\r')
		{
			mode = 0;
			strcpy(playerInfo.name, str);
			done = true;
			printf("%s\n", playerInfo.name);
			for (i = 0; i < len; i++)
				str[i] = 0;
			len = 0;
		}
		else
		{
			str[len] = key;
			len++;
		}
	}
		if (key == 'p')
		{
			notPause = false;
			iPauseTimer(t);
			iPauseTimer(t2);
			iPauseTimer(t3);
			iPauseTimer(t4);
		}
		if (moving||!moveAnim[moveNumber-1].show) {
			if (key == 'z')
			{
				fight = true;
				selectedMove = myPkmn_1.move[0];
				moveNumber++;
				moveAnim[moveNumber - 1].x = myPokemonMovement.x;
				moveAnim[moveNumber - 1].y = myPokemonMovement.y;
				moveAnim[moveNumber - 1].show = true;
				//moveNumber=0;
				moving = false;
				//printf("used");

			}
			if (key == 'x')
			{
				fight = true;
				selectedMove = myPkmn_1.move[1];
				moveNumber++;
				moveAnim[moveNumber - 1].x = myPokemonMovement.x;
				moveAnim[moveNumber - 1].y = myPokemonMovement.y;
				moveAnim[moveNumber - 1].show = true;
				moving = false;
			}
			if (myPkmn_1.level > 1) 
			{
				if (key == 'c')
				{
					fight = true;
					selectedMove = myPkmn_1.move[2];
					moveNumber++;
					moveAnim[moveNumber - 1].x = myPokemonMovement.x;
					moveAnim[moveNumber - 1].y = myPokemonMovement.y;
					moveAnim[moveNumber - 1].show = true;
					moving = false;
				}
			}
			if (myPkmn_1.level > 2) 
			{
				if (key == 'v')
				{
					fight = true;
					selectedMove = myPkmn_1.move[3];
					moveNumber++;
					moveAnim[moveNumber - 1].x = myPokemonMovement.x;
					moveAnim[moveNumber - 1].y = myPokemonMovement.y;
					moveAnim[moveNumber - 1].show = true;
					moving = false;
				}
			}
		}
			if (key == 'w')
			{
				myPokemonMovement.y += 5;
			}
			if (key == 's') {
				myPokemonMovement.y -= 5;
			}
			if (key == 'a') {
				myPokemonMovement.x -= 5;
			}
			if (key == 'd') {
				if(myPokemonMovement.x<=300)
					myPokemonMovement.x += 5;
		}
	//place your codes for other keys here
}


void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	if (notBattle)
	{
		if (key == GLUT_KEY_UP)
			playerY += 5;
		if (key == GLUT_KEY_DOWN)
			playerY -= 5;
		if (key == GLUT_KEY_RIGHT)
			playerX += 5;
		if (key == GLUT_KEY_LEFT)
			playerX -= 5;
	}
	//place your codes for other keys here
}


int main()
{
	srand(time(NULL));
	str[0] = 0;
	attack_list();
	pokemon_list();
	t = iSetTimer(40, enimMove);
	iPauseTimer(t);
	t2 = iSetTimer(60, moveAnimation);
	t3 = iSetTimer(30, opponentMovement);
	iPauseTimer(t3);
	t4 = iSetTimer(50, eMoveAnimation);
	iInitialize(960, 640, "pokemon");
	return 0;
}
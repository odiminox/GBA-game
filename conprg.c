#include <stdio.h>

#include <gba_console.h>
#include <gba_video.h>
#include <gba_input.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>

#include "DISPCNT.h"
#include "VIDEO.h"

#include "playerData.h"
#include "exptiles.h"

int* KEYS = (int*)0x04000130; //Location of key data to manipulate

u16* temp;      //temporary storage pointer

u8 offsetX = 0;
u8 offsetY = 0;

typedef struct Bg 
{ 
	u16* tileData;       //pointer to tile data in VRAM  
	u16* mapData;     //pointer to map data in VRAM 
	u8 mosaic;             //enable mosaic effect 
	u8 colorMode;       //16 or 256 colours 
	u8 number;           //the background number 
	u16 size;       // background size  
	u8 charBaseBlock;      //specify which character block to use 
	u8 screenBaseBlock;  //specify which screen block to use 
	u8 wraparound;          //does map wrap at edges? 
	s16 x_scroll,y_scroll; //scrolling variables 
	s32 DX,DY;                  //rotation scrolling variable 
	s16 PA,PB,PC,PD;       //rotation attributes for a background 
}Bg;

Bg myBackground;  //define an instance of the background structure

//Player struct
typedef struct {

	u8 playerX;
	u8 playerY;

	u16 spriteFrameAnimation_1[4];
	u16 spriteFrameAnimation_2[4];
	u16 spriteFrameAnimation_3[4];
	u16 spriteFrameAnimation_4[4];
	u16 spriteFrameAnimation_5[4];

	int activeFrame;

	u8 attribute2;

	u8 flipSprite;

	u8 firstFrame;

} playerData;

playerData myPlayer;

//Enemy struct
typedef struct {

	int nextDest;

	u8 enemyX;
	u8 enemyY;

	u8 destinationX;
	u8 destinationY;

	u8 WaypointX[3];
	u8 WaypointY[3];

	u8 maxWayPoint;

	u16 spriteFrameAnimation_1[4];
	u16 spriteFrameAnimation_2[4];
	u16 spriteFrameAnimation_3[4];
	u16 spriteFrameAnimation_4[4];
	u16 spriteFrameAnimation_5[4];

	int activeFrame;

	u8 attribute2;

	u8 flipSprite;

} enemyData;

enemyData enemies[5];

//---------------------------------------------------------------------------------
// Function to enable player input of the game character and game
//---------------------------------------------------------------------------------
void playerInput(u8 enemyNum1, u8 enemyNum2) {
	//----------------------------------------
	//Manipulating the memory without black box functions, safer
	//----------------------------------------
	if(!((*KEYS) & KEY_RIGHT))//Acknowledge a key press
	{
		//player_animation_loop(2, 0);

		myPlayer.attribute2 = myPlayer.spriteFrameAnimation_1[myPlayer.activeFrame];
		myPlayer.activeFrame++;

		if(myPlayer.spriteFrameAnimation_1[myPlayer.activeFrame] == myPlayer.spriteFrameAnimation_1[2]){
			myPlayer.activeFrame = 0;
		}

		//myPlayer.playerX = myPlayer.playerX + 1;//Make the player slightly faster than enemies
		myPlayer.flipSprite = 1;

		//if(myPlayer.playerX >= 190)//Bounds testing to ensure the screen scrolls with the player
		myBackground.x_scroll++;
		offsetX = myBackground.x_scroll;

		/*if(myPlayer.playerX == exptiles_WIDTH/2)
			myPlayer.playerX = exptiles_WIDTH/2;*/
	}
	if(!((*KEYS) & KEY_LEFT))
	{
		//player_animation_loop(2, 0);

		myPlayer.attribute2 = myPlayer.spriteFrameAnimation_1[myPlayer.activeFrame];
		myPlayer.activeFrame++;

		if(myPlayer.spriteFrameAnimation_1[myPlayer.activeFrame] == myPlayer.spriteFrameAnimation_1[2]){
			myPlayer.activeFrame = 0;
		}

		myPlayer.flipSprite = 0;
		//myPlayer.playerX = myPlayer.playerX - 1;

		//if(myPlayer.playerX <= 40)

		myBackground.x_scroll--;
		offsetX = myBackground.x_scroll;

		/*if(myPlayer.playerX == exptiles_WIDTH)
			myPlayer.playerX = exptiles_WIDTH;*/
	}
	if(!((*KEYS) & KEY_UP))
	{
		myPlayer.attribute2 = myPlayer.spriteFrameAnimation_3[myPlayer.activeFrame];
		myPlayer.activeFrame++;

		if(myPlayer.spriteFrameAnimation_3[myPlayer.activeFrame] == myPlayer.spriteFrameAnimation_3[2]){
			myPlayer.activeFrame = 0;
		}


		//myPlayer.playerY = myPlayer.playerY - 1;

		//if(myPlayer.playerY <= 40)

		myBackground.y_scroll--;
		offsetY = myBackground.y_scroll;
	}
	if(!((*KEYS) & KEY_DOWN))
	{
		//player_animation_loop(7, 5);

		myPlayer.attribute2 = myPlayer.spriteFrameAnimation_2[myPlayer.activeFrame];
		myPlayer.activeFrame++;

		if(myPlayer.spriteFrameAnimation_2[myPlayer.activeFrame] == myPlayer.spriteFrameAnimation_2[2]){
			myPlayer.activeFrame = 0;
		}
	
		//myPlayer.playerY = myPlayer.playerY + 1;

		//if(myPlayer.playerY >= 90)
	
		myBackground.y_scroll++;
		offsetY = myBackground.y_scroll;
		/*myPlayer.playerY = 142;*/
	}

	if(!((*KEYS) & KEY_LEFT) && (!((*KEYS) & KEY_DOWN)))//Animate when diagonals are pressed
	{
		myPlayer.flipSprite = 0;

		myPlayer.attribute2 = myPlayer.spriteFrameAnimation_5[myPlayer.activeFrame];
		myPlayer.activeFrame++;

		if(myPlayer.spriteFrameAnimation_5[myPlayer.activeFrame] == myPlayer.spriteFrameAnimation_5[2]){
			myPlayer.activeFrame = 0;
		}
	}

	if(!((*KEYS) & KEY_LEFT) && (!((*KEYS) & KEY_UP)))
	{
		myPlayer.flipSprite = 0;

		myPlayer.attribute2 = myPlayer.spriteFrameAnimation_4[myPlayer.activeFrame];
		myPlayer.activeFrame++;

		if(myPlayer.spriteFrameAnimation_4[myPlayer.activeFrame] == myPlayer.spriteFrameAnimation_4[2]){
			myPlayer.activeFrame = 0;
		}
	}

	if(!((*KEYS) & KEY_RIGHT) && (!((*KEYS) & KEY_DOWN)))
	{
		myPlayer.flipSprite = 1;
		myPlayer.attribute2 = myPlayer.spriteFrameAnimation_5[myPlayer.activeFrame];
		myPlayer.activeFrame++;

		if(myPlayer.spriteFrameAnimation_5[myPlayer.activeFrame] == myPlayer.spriteFrameAnimation_5[2]){
			myPlayer.activeFrame = 0;
		}	
	}

	if(!((*KEYS) & KEY_RIGHT) && (!((*KEYS) & KEY_UP)))
	{
		myPlayer.flipSprite = 1;

		myPlayer.attribute2 = myPlayer.spriteFrameAnimation_4[myPlayer.activeFrame];
		myPlayer.activeFrame++;

		if(myPlayer.spriteFrameAnimation_4[myPlayer.activeFrame] == myPlayer.spriteFrameAnimation_4[2]){
			myPlayer.activeFrame = 0;
		}
	}
	
}

//Evaluate player X and Y position then adjust enemy X/Y and animate 
void enemy_FollowPlayer(u8 enemyNum, u8 playerPosX, u8 playerPosY){
		if( enemies[enemyNum].enemyX > playerPosX) {

			enemies[enemyNum].attribute2 = enemies[enemyNum].spriteFrameAnimation_1[enemies[enemyNum].activeFrame];
			enemies[enemyNum].activeFrame++;

			if(enemies[enemyNum].spriteFrameAnimation_1[enemies[enemyNum].activeFrame] == enemies[enemyNum].spriteFrameAnimation_1[2]){
				enemies[enemyNum].activeFrame = 0;
			}

			//enemy_animation_loop(enemyNum, 4);
			enemies[enemyNum].flipSprite = 0;
			enemies[enemyNum].enemyX--;
		}
		if (enemies[enemyNum].enemyX < playerPosX){

			enemies[enemyNum].attribute2 = enemies[enemyNum].spriteFrameAnimation_1[enemies[enemyNum].activeFrame];
			enemies[enemyNum].activeFrame++;

			if(enemies[enemyNum].spriteFrameAnimation_1[enemies[enemyNum].activeFrame] == enemies[enemyNum].spriteFrameAnimation_1[2]){
				enemies[enemyNum].activeFrame = 0;
			}

			//enemy_animation_loop(enemyNum, 4);
			enemies[enemyNum].flipSprite = 1;
			enemies[enemyNum].enemyX++;
		}
		if(enemies[enemyNum].enemyY > playerPosY) {
			enemies[enemyNum].attribute2 = enemies[enemyNum].spriteFrameAnimation_3[enemies[enemyNum].activeFrame];
			enemies[enemyNum].activeFrame++;

			if(enemies[enemyNum].spriteFrameAnimation_3[enemies[enemyNum].activeFrame] == enemies[enemyNum].spriteFrameAnimation_3[2]){
				enemies[enemyNum].activeFrame = 0;
			}

			enemies[enemyNum].flipSprite = 0;

			//enemy_animation_loop(enemyNum, 4);
			enemies[enemyNum].enemyY--;
		}
		if (enemies[enemyNum].enemyY < playerPosY){

			enemies[enemyNum].attribute2 = enemies[enemyNum].spriteFrameAnimation_2[enemies[enemyNum].activeFrame];
			enemies[enemyNum].activeFrame++;

			if(enemies[enemyNum].spriteFrameAnimation_2[enemies[enemyNum].activeFrame] == enemies[enemyNum].spriteFrameAnimation_2[2]){
				enemies[enemyNum].activeFrame = 0;
			}
			enemies[enemyNum].flipSprite = 1;

			//enemy_animation_loop(enemyNum, 4);
			enemies[enemyNum].enemyY++;
		}
}

//Scans for next way point in the way point list
void enemy_CheckDst(u8 enemyNum, u8 maxWaypoint){
if(enemies[enemyNum].enemyX == enemies[enemyNum].destinationX && enemies[enemyNum].enemyY == enemies[enemyNum].destinationY){
			
		enemies[enemyNum].nextDest++;
		enemies[enemyNum].destinationX = enemies[enemyNum].WaypointX[enemies[enemyNum].nextDest];//Increment X way point
		enemies[enemyNum].destinationY = enemies[enemyNum].WaypointY[enemies[enemyNum].nextDest];//Increment Y way point

		if(enemies[enemyNum].enemyX == enemies[enemyNum].WaypointX[maxWaypoint] && //Check if we're at the last way point
			enemies[enemyNum].enemyY == enemies[enemyNum].WaypointY[maxWaypoint])
		{
		enemies[enemyNum].nextDest = 0;//Send agent back to first way point to resume patrol
		}
	}
}

//Moves the agent and animates them accordingly to which way point in the way point list they are looking for
void enemy_patrol(u8 enemyNum){

	if(enemies[enemyNum].enemyX < enemies[enemyNum].destinationX){//If agent hasn't reached target destination, then approach

		enemies[enemyNum].attribute2 = enemies[enemyNum].spriteFrameAnimation_1[enemies[enemyNum].activeFrame];
		enemies[enemyNum].activeFrame++;

		if(enemies[enemyNum].spriteFrameAnimation_1[enemies[enemyNum].activeFrame] == enemies[enemyNum].spriteFrameAnimation_1[2]){
			enemies[enemyNum].activeFrame = 0;
		}
		//enemy_animation_loop(enemyNum, 4);//Animate whilst moving
		enemies[enemyNum].flipSprite = 1;
		enemies[enemyNum].enemyX++;
	}
	if(enemies[enemyNum].enemyY < enemies[enemyNum].destinationY){

		enemies[enemyNum].attribute2 = enemies[enemyNum].spriteFrameAnimation_2[enemies[enemyNum].activeFrame];
		enemies[enemyNum].activeFrame++;

		if(enemies[enemyNum].spriteFrameAnimation_2[enemies[enemyNum].activeFrame] == enemies[enemyNum].spriteFrameAnimation_2[2]){
			enemies[enemyNum].activeFrame = 0;
		}
		enemies[enemyNum].flipSprite = 1;
		//enemy_animation_loop(enemyNum, 4);
		enemies[enemyNum].enemyY++;
	}
	if(enemies[enemyNum].enemyX > enemies[enemyNum].destinationX){
		
		enemies[enemyNum].attribute2 = enemies[enemyNum].spriteFrameAnimation_1[enemies[enemyNum].activeFrame];
		enemies[enemyNum].activeFrame++;

		if(enemies[enemyNum].spriteFrameAnimation_1[enemies[enemyNum].activeFrame] == enemies[enemyNum].spriteFrameAnimation_1[2]){
			enemies[enemyNum].activeFrame = 0;
		}

		//enemy_animation_loop(enemyNum, 4);
		enemies[enemyNum].flipSprite = 0;
		enemies[enemyNum].enemyX--;
	}
	if(enemies[enemyNum].enemyY > enemies[enemyNum].destinationY){
		
		enemies[enemyNum].attribute2 = enemies[enemyNum].spriteFrameAnimation_3[enemies[enemyNum].activeFrame];
		enemies[enemyNum].activeFrame++;

		if(enemies[enemyNum].spriteFrameAnimation_3[enemies[enemyNum].activeFrame] == enemies[enemyNum].spriteFrameAnimation_3[2]){
			enemies[enemyNum].activeFrame = 0;
		}

		enemies[enemyNum].flipSprite = 0;
		//enemy_animation_loop(enemyNum, 4);
		enemies[enemyNum].enemyY--;
	}

}


void enemy_Init(u8 enemyNum){

	enemies[enemyNum].flipSprite = 0;

	//Assign the location of the enemy with the first way point
	enemies[enemyNum].enemyX = enemies[enemyNum].WaypointX[0];
	enemies[enemyNum].enemyY = enemies[enemyNum].WaypointY[0];
	//Assign the initial destX/Y values to the enemyX/Y
	enemies[enemyNum].destinationX = enemies[enemyNum].enemyX;
	enemies[enemyNum].destinationY = enemies[enemyNum].enemyX;
}

void enemy_CreateWayPoint(u8 enemyNum, u8 wayPointNum, u8 wayPointValueX, u8 wayPointValueY, u8 finalWayPoint){
	//HACK FIX: Assigned the third way point to the first to create a loop, otherwise the GBA data is assigned to some
	//arbitrary place? Agent ends up going for a stroll into VBlank space, and we all know dirty things happen in there...
	enemies[enemyNum].WaypointX[finalWayPoint] = enemies[enemyNum].WaypointX[0];
	enemies[enemyNum].WaypointY[finalWayPoint] = enemies[enemyNum].WaypointY[0];
	//Assign the value to the way point we are creating
	enemies[enemyNum].WaypointX[wayPointNum] = wayPointValueX;
	enemies[enemyNum].WaypointY[wayPointNum] = wayPointValueY;
}

void enemy_InitAnimation(u8 enemyNum){
	enemies[enemyNum].activeFrame = enemies[enemyNum].spriteFrameAnimation_1[0];

	enemies[enemyNum].spriteFrameAnimation_1[0] = 1; 
	enemies[enemyNum].spriteFrameAnimation_1[1] = 5;
	enemies[enemyNum].spriteFrameAnimation_1[2] = 9;
	enemies[enemyNum].spriteFrameAnimation_1[3] = 13;
	//Enemy down animation
	enemies[enemyNum].spriteFrameAnimation_2[0] = 17;
	enemies[enemyNum].spriteFrameAnimation_2[1] = 21;
	enemies[enemyNum].spriteFrameAnimation_2[2] = 25;
	enemies[enemyNum].spriteFrameAnimation_2[3] = 29;
	//Enemy up animation
	enemies[enemyNum].spriteFrameAnimation_3[0] = 33;
	enemies[enemyNum].spriteFrameAnimation_3[1] = 37;
	enemies[enemyNum].spriteFrameAnimation_3[2] = 41;
	enemies[enemyNum].spriteFrameAnimation_3[3] = 45;
	//Enemy left/up right/up animation 
	enemies[enemyNum].spriteFrameAnimation_4[0] = 49;
	enemies[enemyNum].spriteFrameAnimation_4[1] = 53;
	enemies[enemyNum].spriteFrameAnimation_4[2] = 57;
	enemies[enemyNum].spriteFrameAnimation_4[3] = 61;
	//Enemy left/down right/down animation
	enemies[enemyNum].spriteFrameAnimation_5[0] = 65;
	enemies[enemyNum].spriteFrameAnimation_5[1] = 69;
	enemies[enemyNum].spriteFrameAnimation_5[2] = 73;
	enemies[enemyNum].spriteFrameAnimation_5[3] = 77;

}

void player_InitAnimation(){
	//myPlayer.activeFrame = myPlayer.spriteFrame[0];//Init the first sprite frame
	//Player Left/Right animation
	myPlayer.spriteFrameAnimation_1[0] = 1; 
	myPlayer.spriteFrameAnimation_1[1] = 5;
	myPlayer.spriteFrameAnimation_1[2] = 9;
	myPlayer.spriteFrameAnimation_1[3] = 13;
	//Player down animation
	myPlayer.spriteFrameAnimation_2[0] = 17;
	myPlayer.spriteFrameAnimation_2[1] = 21;
	myPlayer.spriteFrameAnimation_2[2] = 25;
	myPlayer.spriteFrameAnimation_2[3] = 29;
	//Player up animation
	myPlayer.spriteFrameAnimation_3[0] = 33;
	myPlayer.spriteFrameAnimation_3[1] = 37;
	myPlayer.spriteFrameAnimation_3[2] = 41;
	myPlayer.spriteFrameAnimation_3[3] = 45;
	//Player left/up right/up animation 
	myPlayer.spriteFrameAnimation_4[0] = 49;
	myPlayer.spriteFrameAnimation_4[1] = 53;
	myPlayer.spriteFrameAnimation_4[2] = 57;
	myPlayer.spriteFrameAnimation_4[3] = 61;
	//player left/down right/down animation
	myPlayer.spriteFrameAnimation_5[0] = 65;
	myPlayer.spriteFrameAnimation_5[1] = 69;
	myPlayer.spriteFrameAnimation_5[2] = 73;
	myPlayer.spriteFrameAnimation_5[3] = 77;


	myPlayer.flipSprite = 0;
	myPlayer.attribute2 = myPlayer.spriteFrameAnimation_1[0];//Need this otherwise first frame is garbage
}

//TO DO: refine checking of player distance
void enemy_State(u8 enemyNum, playerData player){
	if(player.playerX == enemies[enemyNum].enemyX  || player.playerY == enemies[enemyNum].enemyY){
		enemy_FollowPlayer(enemyNum, player.playerX, player.playerY);
		BG_palettRAM[(0 *16) + 0] = RGB16_RGB(15, 0, 0);
	} else {
		enemy_CheckDst(enemyNum, 1);
		enemy_patrol(enemyNum);
		BG_palettRAM[(0 *16) + 0] = RGB16_RGB(10, 10, 5);
	}
}


//Need to fix this so I can use it instead of copying the code in for each key press
//myplayer.spriteFrameAnimation_1 I need to be able to parse in whatever animation
//So currently this cannot be used
void player_animation_loop(u8 maxFrames, u8 firstFrame){

	myPlayer.attribute2 = myPlayer.spriteFrameAnimation_1[myPlayer.activeFrame];
	myPlayer.activeFrame++;

	if(myPlayer.spriteFrameAnimation_1[myPlayer.activeFrame] == myPlayer.spriteFrameAnimation_1[maxFrames]){
		myPlayer.activeFrame = firstFrame;
	}
}

void UpdateBackground()
{
	REG_BG0HOFS = myBackground.x_scroll;
	REG_BG0VOFS = myBackground.y_scroll;
	
}



//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	enemy_InitAnimation(0);
	enemy_InitAnimation(1);

	player_InitAnimation();

	myPlayer.playerX = 120;//Set the first location our sprite appears
	myPlayer.playerY = 70;
	
	
	//Initialize our way points and enemy
	enemy_CreateWayPoint(0, 0, 10, 10, 2);//enemyNum, waypointNum, waypointvalueX, waypointvalueY, finalWayPoint
	enemy_CreateWayPoint(0, 1, 120, 10, 2);
	enemy_Init(0);//enemyNum

	enemy_CreateWayPoint(1, 0, 20, 20, 2);
	enemy_CreateWayPoint(1, 1, 20, 50, 2);
	enemy_Init(1);

	myBackground.charBaseBlock = 0;            //tile data position  
	myBackground.screenBaseBlock = 28;        //map data position  
	myBackground.colorMode = BG_256_COLOR;    //256-colour background 
	myBackground.size = ROTBG_SIZE_256x256;   //size of map 
	myBackground.mosaic = 0;                 //not enabled 
	myBackground.x_scroll = 120;             //x,y scroll positions 
	myBackground.y_scroll = 80;

	// the vblank interrupt must be enabled for VBlankIntrWait() to work
	// since the default dispatcher handles the bios flags no vblank handler
	// is required
	irqInit();
	irqEnable(IRQ_VBLANK);

	consoleDemoInit();

	//Defined in gba_video.h
	SetMode(MODE_0 | BG0_ENABLE |  OBJ_ENABLE | OBJ_MAP_1D);//MODE 0: 0x0, BG0 Enabled: 0x100, obj map 1D: 0x40

	myBackground.tileData = (u16*)CharBaseBlock(myBackground.charBaseBlock); 
	myBackground.mapData = (u16*)ScreenBaseBlock(myBackground.screenBaseBlock);
	REG_BG0CNT = ROTBG_SIZE_256x256 | myBackground.charBaseBlock << CHAR_SHIFT | myBackground.screenBaseBlock << SCREEN_SHIFT | BG_256_COLOR;

	//Load the sprite data in from the header file
	int n;
	for (n = 0; n < 256*8; n++){//4*8 tile size read in one tile at a time, 256 reads them in by 16X16
		OAMAddress[n+8] = fontData[n];
	}
	//background pallet
	int loop;
	for(loop = 0; loop < 256; loop++) 
		BG_palettRAM[loop] = exptilesPalette[loop];//Get our pallet data for the map
	
	int loop2;
	for(loop2 = 0; loop2 < exptiles_WIDTH * exptiles_HEIGHT /2; loop2++) 
		myBackground.tileData[loop2] = exptilesData[loop2];//get the tile data for the map

	//Enemy pallet
	OBJ_palletRAM[(2 *16) + 1] = RGB16_RGB(0, 0, 5); //0500:0200h
	OBJ_palletRAM[(2 *16) + 2] = RGB16_RGB(0, 8, 6);
	OBJ_palletRAM[(2 *16) + 4] = RGB16_RGB(0, 6, 8);
	OBJ_palletRAM[(2 *16) + 3] = RGB16_RGB(5, 5, 5); //Shadow colour

	//Player pallet
	OBJ_palletRAM[(1 *16) + 1] = RGB16_RGB(0, 0, 8);
	OBJ_palletRAM[(1 *16) + 2] = RGB16_RGB(8, 0, 0);
	OBJ_palletRAM[(1 *16) + 4] = RGB16_RGB(8, 5, 0); 
	OBJ_palletRAM[(1 *16) + 3] = RGB16_RGB(5, 5, 5);

	while (1) {

		UpdateBackground();

		playerInput();

		enemy_State(0, myPlayer);
		enemy_State(1, myPlayer);
		
		//Player Sprite
		drawSprite(1, myPlayer.playerX, myPlayer.playerY, myPlayer.attribute2, 1, myPlayer.flipSprite, 0);//u8 spAdr, u8 enemyX, u8 enemyY, u8 spNum, u8 pNum
		//enemy 1 patrol
		drawSprite(2, enemies[0].enemyX, enemies[0].enemyY, enemies[0].attribute2, 2, enemies[0].flipSprite , 0);
		//enemy 2 patrol
		drawSprite(3, enemies[1].enemyX, enemies[1].enemyY, enemies[1].attribute2, 2, enemies[1].flipSprite, 0);
		
		
		VBlankIntrWait();

	}
}
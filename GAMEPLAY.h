//Various junk and old code to use in report or analyse for experiments


//typedef struct{
//	u16 x[6];
//	u16 y[6];
//
//	int currentWP_X;
//	int currentWP_Y;
//
//} wayPointStruct;
//
//wayPointStruct wayPoint;

//typedef struct{
//	u8 posX;
//	u8 posY;
//} sprite;

//sprite playerSprite;
//sprite enemyStateSprite;
//sprite enemyFollowSprite;

//----------------------------------------
//unsigned short myKeysHeld = keysHeld();
//gba_input.h style of input
//----------------------------------------
	
//Right key
//if(((myKeysHeld >> 4) & 1) == 1){
//	posX++;
//}
////Left key
//if(((myKeysHeld >> 5) & 1) == 1){
//	posX--;
//}
////Up key
//if(((myKeysHeld >> 6) & 1) == 1){
//	posY--;
//}
////Down key
//if(((myKeysHeld >> 7) & 1)== 1){
//	posY++;
//}

//
//void enemy_FollowPlayer(){
//
//	/*Follow player*/
//	if( enemyFollowSprite.posX > playerSprite.posX) {
//		enemyFollowSprite.posX--;
//	}
//	if (enemyFollowSprite.posX < playerSprite.posX){
//		enemyFollowSprite.posX++;
//	}
//	if(enemyFollowSprite.posY > playerSprite.posY) {
//		enemyFollowSprite.posY--;
//	}
//	if (enemyFollowSprite.posY < playerSprite.posY){
//		enemyFollowSprite.posX++;
//	}
//}


//
//void enemy_FollowPlayer(){
//
//	//Follow player
//	if( enemyX > posX) {
//		enemyX--;
//	} else if (enemyX < posX){
//		enemyX++;
//	}
//	if(enemyY > posY) {
//		enemyY--;
//	} else if (enemyY < posY){
//		enemyY++;
//	}
//}

//void enemy_patrol(){
//
//	int counter = 0;
//
//	for(; counter < 3; counter++){
//
//		wayPoint.x[wayPoint.currentWP_X] = wayPoint.x[counter];
//		wayPoint.y[wayPoint.currentWP_X] = wayPoint.y[counter];
//
//		if(enemyStateSprite.posX <= wayPoint.x[wayPoint.currentWP_X]){
//			//enemyStateSprite.posX++; //blends all the values together
//			enemyStateSprite.posX += wayPoint.x[wayPoint.currentWP_X];
//		} else if(enemyStateSprite.posY <= wayPoint.y[wayPoint.currentWP_Y]){
//			//enemyStateSprite.posY++;
//			enemyStateSprite.posY += wayPoint.y[wayPoint.currentWP_Y];
//		}
//	}
//}


/*	if(enemyOne.enemyX == enemyOne.destinationX && enemyOne.enemyY == enemyOne.destinationY){
			
		enemyOne.nextDest++;
		enemyOne.destinationX = enemyOne.WaypointX[enemyOne.nextDest];
		enemyOne.destinationY = enemyOne.WaypointY[enemyOne.nextDest];

		if(enemyOne.enemyY == enemyOne.WaypointY[1] && enemyOne.enemyX == enemyOne.WaypointX[1]){
			enemyOne.destinationY =  enemyOne.WaypointY[0];
			enemyOne.destinationX =  enemyOne.WaypointX[0];
			enemyOne.nextDest = 0;
		}
	}*/

//
//void enemy_chekDest(currentPosX, currentPosY, destinationX, destinationY ){
//		if(currentPosX == destinationX && currentPosY == destinationY){
//			
//			nextDest++;
//			destinationX = WaypointX[nextDest];
//			destinationY = WaypointY[nextDest];
//			/*if(WaypointX[nextDest] == WaypointX[2] && WaypointY[nextDest] == WaypointY[2]){
//				nextDest = 0;
//			}*/
//		}
//}

//enemies[1].WaypointX[0] = 170;
//enemies[1].WaypointY[0] = 10;

//enemies[1].WaypointX[1] = 170;
//enemies[1].WaypointY[1] = 90;

//enemies[1].WaypointX[2] = enemies[1].WaypointX[0];
//enemies[1].WaypointY[2] = enemies[1].WaypointY[0];

//enemies[1].enemyX = enemies[1].WaypointX[0];
//enemies[1].enemyY = enemies[1].WaypointY[0];

//enemies[1].destinationX = enemies[1].enemyX;
//enemies[1].destinationY = enemies[1].enemyX;

//enemies[0].WaypointX[0] = 10;
//enemies[0].WaypointY[0] = 10;

//enemies[0].WaypointX[1] = 120;
//enemies[0].WaypointY[1] = 10;

//enemies[0].enemyX = enemies[0].WaypointX[0];
//enemies[0].enemyY = enemies[0].WaypointY[0];

//enemies[0].destinationX = enemies[0].enemyX;
//enemies[0].destinationY = enemies[0].enemyX;

////wayPoints
//drawSprite(3, enemies[0].WaypointX[0], enemies[0].WaypointY[0], 4, 1);
//drawSprite(4, enemies[0].WaypointX[1], enemies[0].WaypointY[1], 4, 2);
//drawSprite(5, enemies[0].WaypointX[2], enemies[0].WaypointY[2], 4, 3);

//drawSprite(7, enemies[1].WaypointX[0], enemies[1].WaypointY[0], 4, 1);
//drawSprite(8, enemies[1].WaypointX[1], enemies[1].WaypointY[1], 4, 2);
//drawSprite(9, enemies[1].WaypointX[2], enemies[1].WaypointY[2], 4, 3);
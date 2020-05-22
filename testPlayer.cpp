#include "DxLib.h"
#include "main.h"
#include "testPlayer.h"

//
int testPlayerImage;
CHARACTER testPlayer;

//
void testPlayerSystemInit(void) {
	testPlayerImage = LoadGraph("image/player.png");
}

//
void testPlayerGameInit(void)
{
	testPlayer.visible = 1;
	testPlayer.pos = { SCREEN_SIZE_X / 2 - 72,(SCREEN_SIZE_Y / 2) + 200 };
	testPlayer.size={ 32,32 };
	testPlayer.sizeOffset = { testPlayer.size.x / 2, testPlayer.size.y / 2 };
	testPlayer.moveSpeed = 2;
	testPlayer.life = 10;
	testPlayer.lifeMax = testPlayer.life;

}

//
void testPlayerCtrl(void)
{

}

//
void testPlayerDraw(void) {
	//
	if (testPlayer.visible) {
		DrawGraph(testPlayer.pos.x - testPlayer.sizeOffset.x,
			testPlayer.pos.y - testPlayer.sizeOffset.y, testPlayerImage,1);
	}
}
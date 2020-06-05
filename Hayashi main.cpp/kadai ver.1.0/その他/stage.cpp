#include "DxLib.h"
#include "main.h"
#include "stage.h"

// ”wŒi‰æ‘œ
int haikeiImage;
CHARACTER stage;

int spaceImage;
CHARACTER space;

// ”wŒi‰æ‘œ‰Šú‰»
void StageSystemInit(void)
{
	haikeiImage = LoadGraph("image/haikei.jpg");
	spaceImage = LoadGraph("image/nebula10.1.png");
}

// ”wŒi‚Ì•Ï”‰Šú‰»
void StageGameInit(void)
{
	stage.visible = true;
	stage.pos = { 0,0 };
	stage.size = { 4096, 4096 };
	stage.sizeOffset = { stage.size.x / 2, stage.size.y / 2 };
	stage.moveSpeed = 2;

	space.visible = true;
	space.pos = { 1300, 0 };
	space.size = { 1134, 1576 };
	space.sizeOffset = { space.size.x / 2, space.size.y / 2 };
	space.moveSpeed = 2;
}

// ”wŒi‘€ì
void StageControl(void)
{
	// ¯‚Ì”wŒi½¸Û°Ù“®ì
	if (stage.visible) {
		stage.pos.y += stage.moveSpeed;
		if (stage.pos.y == 2034) {
			stage.pos.y = 0;
		}
	}

	// ‰F’ˆ‚Ì”wŒi½¸Û°Ù“®ì
	if (space.visible) {
		space.pos.y += space.moveSpeed;
		if (space.pos.y == 2034) {
			space.pos.y = 0;
		}
	}
}

// ”wŒi•`‰æ
void StageDraw(void)
{
	// ˆê–‡–Ú•`‰æ(¯‚Ì”wŒi)
	if(stage.visible){
		DrawGraph(stage.pos.x - stage.sizeOffset.x,
			stage.pos.y - stage.sizeOffset.y, haikeiImage, false);
	}
	// “ñ–‡–Ú•`‰æ(¯‚Ì”wŒi)
	if (stage.visible) {
		DrawGraph(stage.pos.x - stage.sizeOffset.x,
			stage.pos.y - stage.sizeOffset.y - 2034, haikeiImage, false);
	}

	/* ˆê–‡–Ú•`‰æ(‰F’ˆ‚Ì”wŒi)
	if (space.visible) {
		DrawGraph(space.pos.x - space.sizeOffset.x,
			space.pos.y - space.sizeOffset.y, spaceImage, false);
	}
	// “ñ–‡–Ú•`‰æ(‰F’ˆ‚Ì”wŒi)
	if (space.visible) {
		DrawGraph(space.pos.x - space.sizeOffset.x,
			space.pos.y - space.sizeOffset.y - 2034, spaceImage, false);
	}*/

//	DrawFormatString(0, 20, 0xffffff, "stagePos = %d %d", space.pos);
}
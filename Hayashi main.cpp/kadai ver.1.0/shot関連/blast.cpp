#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "blast.h"


int blastImage[64];
int blastAnimCnt;
CHARACTER blast;


void BlastSystemInit(void)
{
	LoadDivGraph("image/16_sunburn_spritesheet.png", 64, 8, 8, 800, 800, blastImage, false);
}


void BlastGameInit(void)
{
	blastAnimCnt = 0;
	blast.visible = true;
	blast.pos = { 0, 0 };
	blast.size = { 100, 100 };
	blast.sizeOffset = { blast.size.x / 2, blast.size.y / 2 };
}


bool BlastGenerator(XY_F pos)
{
	if (blast.visible) {
		blastAnimCnt++;
		blast.pos = pos;

		if (blastAnimCnt > 60) {
			blast.visible = false;
		}
		return true;
	}
	return false;
}


void BlastDraw(void)
{
	if (blast.visible == true) {
		DrawGraph(blast.pos.x - blast.sizeOffset.x,
			blast.pos.x - blast.sizeOffset.y, blastImage[blastAnimCnt], true);
	}
}
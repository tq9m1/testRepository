#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "shot.h"
#include "player.h"
#include <math.h>

// •Ï”éŒ¾
int shotImage;
int shotCnt;
int shotTiming;
int eShotImage;

CHARACTER shot[SHOT_MAX];
CHARACTER eshot[SHOT_MAX];

int shotSe;

// ‰æ‘œ‰Šú‰»
void ShotSystemInit(void)
{
	shotImage = LoadGraph("image/shot.png");
}

// •Ï”‰Šú‰»
void ShotGameInit(void)
{
	// ÌßÚ²Ô°¼®¯Ä‚Ì•Ï”
	for(int i = 0; i < SHOT_MAX; i++){
		shot[i].visible = true;
		shot[i].pos = { 0,0 };
		shot[i].size = { 16,16 };
		shot[i].sizeOffset = { shot[i].size.x / 2, shot[i].size.y / 2 };
		shot[i].moveSpeed = 15;
	}
	shotCnt = 0;
	shotTiming = 3;
}

// ’e‚Ì‘€ì
void ShotControl(void)
{
	// ’e‚ÌˆÚ“®(ÌßÚ²Ô°)
	if(newKey[SPACE]){
		if (shotCnt > shotTiming) {
			for (int i = 0; i < SHOT_MAX; i++) {
				if (!shot[i].visible) {
					shot[i].pos = player.pos;
					shot[i].visible = true;
					shotCnt = 0;
					break;
				}
			}
		}
	}
	shotCnt++;

	for (int i = 0; i < SHOT_MAX; i++) {
		if (shot[i].visible) {
			shot[i].pos.y -= shot[i].moveSpeed;
		}
		if ((shot[i].pos.y < 0)||(player.visible == false)) {
//			StopSoundMem(shotSe);
			shot[i].visible = false;
		}
	}
}

// ’e‚Ì”­Ë(ÌßÚ²Ô°)
void Shoot(XY_F pPos)
{
	if (shotCnt > shotTiming) {
		for (int i = 0; i < SHOT_MAX; i++) {
			if (!shot[i].visible) {
				shot[i].pos = { pPos.x, pPos.y };
				shot[i].visible = true;
				shotCnt = 0;
			}
		}
	}
	shotCnt++;
}


// •`‰æ
void ShotDraw(void)
{
	// ÌßÚ²Ô°‚Ì’e
	for (int i = 0; i < SHOT_MAX; i++) {
		if (shot[i].visible) {
			DrawGraph(shot[i].pos.x - shot[i].sizeOffset.x,
				shot[i].pos.y - shot[i].sizeOffset.y, shotImage, true);
		}
	}
}

// ÌßÚ²Ô°‚Ì’e‚Ì•Ï”‚ÌŠl“¾
CHARACTER GetShot(int index)
{
	return shot[index];
}
// ÌßÚ²Ô°‚Ì’e‚ÌÁ‹
void ShotDelete(int index)
{
	shot[index].visible = false;
}

// ´ÈĞ°‚Ì’e‚Ì•Ï”‚ÌŠl“¾
CHARACTER GetShotE(int index)
{
	return eshot[index];
}
// ´ÈĞ°‚Ì’eÁ‹
void EShotDelete(int index)
{
	shot[index].visible = false;
}
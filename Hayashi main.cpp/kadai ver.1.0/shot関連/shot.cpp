#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "shot.h"
#include "player.h"
#include <math.h>

// �ϐ��錾
int shotImage;
int shotCnt;
int shotTiming;
int eShotImage;

CHARACTER shot[SHOT_MAX];
CHARACTER eshot[SHOT_MAX];

int shotSe;

// �摜������
void ShotSystemInit(void)
{
	shotImage = LoadGraph("image/shot.png");
}

// �ϐ�������
void ShotGameInit(void)
{
	// ��ڲ԰���Ă̕ϐ�
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

// �e�̑���
void ShotControl(void)
{
	// �e�̈ړ�(��ڲ԰)
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

// �e�̔���(��ڲ԰)
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


// �`��
void ShotDraw(void)
{
	// ��ڲ԰�̒e
	for (int i = 0; i < SHOT_MAX; i++) {
		if (shot[i].visible) {
			DrawGraph(shot[i].pos.x - shot[i].sizeOffset.x,
				shot[i].pos.y - shot[i].sizeOffset.y, shotImage, true);
		}
	}
}

// ��ڲ԰�̒e�̕ϐ��̊l��
CHARACTER GetShot(int index)
{
	return shot[index];
}
// ��ڲ԰�̒e�̏���
void ShotDelete(int index)
{
	shot[index].visible = false;
}

// ��а�̒e�̕ϐ��̊l��
CHARACTER GetShotE(int index)
{
	return eshot[index];
}
// ��а�̒e����
void EShotDelete(int index)
{
	shot[index].visible = false;
}
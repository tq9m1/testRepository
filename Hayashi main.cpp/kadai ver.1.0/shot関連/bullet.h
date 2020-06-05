#pragma once

// 定数
#define BULLET_MAX 500

extern CHARACTER bullet[BULLET_MAX];
extern CHARACTER testBullet[BULLET_MAX];

extern CHARACTER tama[BULLET_MAX];


/*----- プロトタイプ宣言 -----*/
void BulletSystemInit(void);
void BulletGameInit(void);
void BulletControl(void);
void BulletDraw(void);
void EShoot(XY_F ePos);
void tEShoot(XY_F tePos);
void tekiShoot(XY_F tekiPos);

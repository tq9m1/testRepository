#pragma once

#define ENEMY_MAX 1
#define TESTENEMY_MAX 1
//#define TEKI_MAX 1

/*------- プロトタイプ宣言 -------*/
void EnemySystemInit(void);
void EnemyAdd(void);
void EnemyGameInit(void);
void EnemyControl(void);
void EnemyDraw(void);
void tekiInit(void);
// 敵の当たり判定
bool EnemyHitCheck(XY_F sPos, XY_F sSize);
bool tesEnemyHitCheck(XY_F sPos, XY_F sSize);
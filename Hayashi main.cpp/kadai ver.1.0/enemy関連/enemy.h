#pragma once

#define ENEMY_MAX 1
#define TESTENEMY_MAX 1
//#define TEKI_MAX 1

/*------- �v���g�^�C�v�錾 -------*/
void EnemySystemInit(void);
void EnemyAdd(void);
void EnemyGameInit(void);
void EnemyControl(void);
void EnemyDraw(void);
void tekiInit(void);
// �G�̓����蔻��
bool EnemyHitCheck(XY_F sPos, XY_F sSize);
bool tesEnemyHitCheck(XY_F sPos, XY_F sSize);
#pragma once

// �萔
#define SHOT_MAX 20

extern CHARACTER shot[SHOT_MAX];
extern CHARACTER eshot[SHOT_MAX];

/* ------- �v���g�^�C�v�錾 -------*/
void ShotSystemInit(void);
void ShotGameInit(void);
void ShotControl(void);
void ShotDraw(void);
// -----�e�̔��ˊ֐�
// ��ڲ԰
void Shoot(XY_F pPos);

// ----- �e�̕ϐ���ʂ̏ꏊ�Ŏg�����߂̊֐�
// ��ڲ԰
CHARACTER GetShot(int index);
// ��а
CHARACTER GetShotE(int index);
// ----- �e���׸ނ�����
// ��ڲ԰
void ShotDelete(int index);
// ��а
void EShotDelete(int index);
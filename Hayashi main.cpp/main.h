#pragma once

#define SCREEN_SIZE_X 860
#define SCREEN_SIZE_Y 600

#define PI 3.141592

typedef struct {
	float x;
	float y;
}XY_F;

typedef struct {
	int x;
	int y;
}XY;

// ��׸��\����
typedef struct {
//	MOVE_DIR moveDir;	// �����Ă������
	XY_F pos;				// ��׸��̈ʒu(���S�j
	XY_F speed;
	XY_F size;			// ��׸��̉摜����
	XY_F sizeOffset;		// ��׸���������̍���ʒu
	XY hitPosS;			// �����蔻��p�̍���
	XY hitPosE;			// �����蔻��p�̉E��
//	bool runFlag;		// ��׸��̏��(�����Ă��邩�H�j
//	bool jumpFlag;		// ��׸��̏��(�W�����v���Ă��邩�H�j
	bool shotFlag;		// ��׸��̏��(�e�������Ă��邩�H�j
	bool damageFlag;	// ��׸��̏��(��Ұ�ނ��󂯂Ă��邩�H�j
	int moveSpeed;		// ��׸��̈ړ���
	int life;			// ��׸��̗̑�
	int lifeMax;		// ��׸��̍ő�̗�
	int animCnt;		// ��׸��̱�Ұ��ݗp����
//	int imgLockCnt;		// ��׸��̲Ұ�ތŒ�p����
	XY_F velocity;		// �ړ����x
	bool visible;		// �\�����
	int point;			// ������Z
//	int type;			// ���炩�̑������i�[�ł���
	int MovCnt;			// �G�̓��춳��
	double angle;		// �p�x
	XY mov;
}CHARACTER;

// ----- �������ߐ錾
// ���
void AddScore(int point);
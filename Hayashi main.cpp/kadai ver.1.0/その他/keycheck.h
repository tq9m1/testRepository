#pragma once

enum KEY_MODE {
	P1_UP,
	P1_RIGHT,
	P1_DOWN,
	P1_LEFT,
	P1_RCTR,
	P1_LCTR,

	P1_A,
	P1_B,
	P1_X,
	P1_Y,
	P1_R1,
	P1_L1,
	P1_R2,
	P1_L2,
	P1_START,
	P1_SELECT,
	P1_xTHUMB_R,//�E�X�e�B�b�N
	P1_xTHUMB_L,//���X�e�B�b�N
	P1_xRIGHT_TRIGGER,//�E�̃g���K�[�l
	P1_xLEFT_TRIGGER,//���̃g���K�[�l
	P1_xThumbRX,//�E�X�e�B�b�NX�l
	P1_xThumbRY,//�E�X�e�B�b�NY�l
	P1_xThumbLX,//���X�e�B�b�NX�l
	P1_xThumbLY,//���X�e�B�b�NY�l

	P2_UP,
	P2_RIGHT,
	P2_DOWN,
	P2_LEFT,

	PAUSE,
	SPACE,

	KEY_MAX
};

//struct XINPUT_STATE{
//	unsigned char Buttons[16];	//�{�^��16��
//								//�Y���ɂ�XINPUT_BUTTON_DPAD�����g�p����
//								//0:������Ă��Ȃ�
//								//1:������Ă���
//	unsigned char LeftTrigger;	//���g���K�[
//	unsigned char RightTrigeer;	//�E�g���K�[
//	short ThumbLX;				//���X�e�B�b�N����
//	short ThumbLY;				//���X�e�B�b�N�c��
//	short ThumbRX;				//�E�X�e�B�b�N����
//	short ThumbRY;				//�E�X�e�B�b�N�c��
//};
//
//// ��۰��ٕϐ�
//#define XINPUT_BUTTON_DPAD_UP
//#define XINPUT_BUTTON_DPAD_DOWN
//#define XINPUT_BUTTON_DPAD_LEFT
//#define XINPUT_BUTTON_DPAD_RIGHT
//#define XINPUT_BUTTON_DPAD_START
//#define XINPUT_BUTTON_DPAD_BACK
//#define XINPUT_BUTTON_DPAD_LEFT_THUMB
//#define XINPUT_BUTTON_DPAD_RIGHT_THUMB
//#define XINPUT_BUTTON_DPAD_LEFT_SHOULDER
//#define XINPUT_BUTTON_DPAD_RIGHT_SHOULDER
//#define XINPUT_BUTTON_A
//#define XINPUT_BUTTON_B
//#define XINPUT_BUTTON_X
//#define XINPUT_BUTTON_Y

extern bool newKey[KEY_MAX];
extern bool trgKey[KEY_MAX];
extern bool upKey[KEY_MAX];
extern bool oldKey[KEY_MAX];

// ----- �������ߐ錾
void KeyCheckSystemInit(void);
void KeyCheck(void);

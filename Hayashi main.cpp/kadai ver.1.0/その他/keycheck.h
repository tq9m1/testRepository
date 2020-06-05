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
	P1_xTHUMB_R,//右スティック
	P1_xTHUMB_L,//左スティック
	P1_xRIGHT_TRIGGER,//右のトリガー値
	P1_xLEFT_TRIGGER,//左のトリガー値
	P1_xThumbRX,//右スティックX値
	P1_xThumbRY,//右スティックY値
	P1_xThumbLX,//左スティックX値
	P1_xThumbLY,//左スティックY値

	P2_UP,
	P2_RIGHT,
	P2_DOWN,
	P2_LEFT,

	PAUSE,
	SPACE,

	KEY_MAX
};

//struct XINPUT_STATE{
//	unsigned char Buttons[16];	//ボタン16個
//								//添字にはXINPUT_BUTTON_DPAD等を使用する
//								//0:押されていない
//								//1:押されている
//	unsigned char LeftTrigger;	//左トリガー
//	unsigned char RightTrigeer;	//右トリガー
//	short ThumbLX;				//左スティック横軸
//	short ThumbLY;				//左スティック縦軸
//	short ThumbRX;				//右スティック横軸
//	short ThumbRY;				//右スティック縦軸
//};
//
//// ｸﾞﾛｰﾊﾞﾙ変数
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

// ----- ﾌﾟﾛﾄﾀｲﾌﾟ宣言
void KeyCheckSystemInit(void);
void KeyCheck(void);

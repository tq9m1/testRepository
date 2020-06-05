#include "DxLib.h"
#include "main.h"
#include "keyCheck.h"

bool newKey[KEY_MAX];
bool trgKey[KEY_MAX];
bool upKey[KEY_MAX];
bool oldKey[KEY_MAX];

XINPUT_STATE PS4input;
XINPUT_STATE xBox360input;

// ----- �Ƃ肠�����S���ر
void KeyCheckSystemInit(void)
{
	for (int i = 0; i < KEY_MAX; i++) {
		newKey[i] = false;
		trgKey[i] = false;
		upKey[i] = false;
		oldKey[i] = false;
	}
}

void KeyCheck(void)
{
	// ----- newKey
	for (int i = 0; i < KEY_MAX; i++) {
		newKey[i] = false;	// �S�������Ă��Ȃ����Ƃɂ���
		trgKey[i] = false;	// �S�������Ă��Ȃ����Ƃɂ���
		upKey[i] = false;	// �S�������Ă��Ȃ����Ƃɂ���
	}

	//keybord//
	if (CheckHitKey(KEY_INPUT_W)) newKey[P1_UP] = true;
	if (CheckHitKey(KEY_INPUT_D)) newKey[P1_RIGHT] = true;
	if (CheckHitKey(KEY_INPUT_S)) newKey[P1_DOWN] = true;
	if (CheckHitKey(KEY_INPUT_A)) newKey[P1_LEFT] = true;

	//if (CheckHitKey(KEY_INPUT_RCONTROL)) newKey[P1_RCTR] = true;
	//if (CheckHitKey(KEY_INPUT_LSHIFT)) newKey[P1_A] = 1;
	//if (CheckHitKey(KEY_INPUT_LCONTROL)) newKey[P1_B] = true;

	if (CheckHitKey(KEY_INPUT_P)) newKey[PAUSE] = true;
	if (CheckHitKey(KEY_INPUT_SPACE)) newKey[SPACE] = true;

	/* ======= ����͎g��Ȃ�
	if (CheckHitKey(KEY_INPUT_UP)) newKey[P2_UP] = true;
	if (CheckHitKey(KEY_INPUT_RIGHT)) newKey[P2_RIGHT] = true;
	if (CheckHitKey(KEY_INPUT_DOWN)) newKey[P2_DOWN] = true;
	if (CheckHitKey(KEY_INPUT_LEFT)) newKey[P2_LEFT] = true;

	if (CheckHitKey(KEY_INPUT_W)) newKey[P2_UP] = true;
	if (CheckHitKey(KEY_INPUT_D)) newKey[P2_RIGHT] = true;
	if (CheckHitKey(KEY_INPUT_S)) newKey[P2_DOWN] = true;
	if (CheckHitKey(KEY_INPUT_A)) newKey[P2_LEFT] = true;
*/

	//gamepad//
	//int PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);//pad�̌��o
	//if (PadInput & PAD_INPUT_UP) newKey[P1_UP] = 1;
	//if (PadInput & PAD_INPUT_LEFT) newKey[P1_LEFT] = 1;
	//if (PadInput & PAD_INPUT_DOWN) newKey[P1_DOWN] = 1;
	//if (PadInput & PAD_INPUT_RIGHT) newKey[P1_RIGHT] = 1;

	//GetJoypadXInputState(DX_INPUT_PAD1, &PS4input);
	//if (PS4input.Buttons[XINPUT_BUTTON_DPAD_UP]) newKey[P1_UP] = 1;//�����{�^����
	//if (PS4input.Buttons[XINPUT_BUTTON_DPAD_LEFT]) newKey[P1_LEFT] = 1;//�����{�^����
	//if (PS4input.Buttons[XINPUT_BUTTON_DPAD_DOWN]) newKey[P1_DOWN] = 1;//�����{�^����
	//if (PS4input.Buttons[XINPUT_BUTTON_DPAD_RIGHT]) newKey[P1_RIGHT] = 1;//�����{�^���E
	//newKey[P1_xLEFT_TRIGGER] = (int)xBoxoneinput.LeftTrigger;//���g���K�[
	//newKey[P1_xThumbLX] = (int)xBoxoneinput.ThumbLX;//���X�e�B�b�N����
	//newKey[P1_xThumbLY] = (int)xBoxoneinput.ThumbLY; //���X�e�B�b�N�c��

	// trgKey & upKey & oldKey
	for (int i = 0; i < KEY_MAX; i++) {
		trgKey[i] = newKey[i] & ~oldKey[i];	// trgKey
		upKey[i] = ~newKey[i] & oldKey[i];	// upKey
		oldKey[i] = newKey[i];		// oldKey
	}
}
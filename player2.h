#pragma once

extern CHARACTER player2;

/*-----�v���g�^�C�v�錾-----*/
void Player2SystemInit(void);
void Player2GameInit(void);
void Player2Control(void);
void Player2Draw(void);
// �����蔻��
bool Player2HitCheck(XY_F ePos, XY_F eSize);
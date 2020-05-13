#pragma once

extern CHARACTER player2;

/*-----プロトタイプ宣言-----*/
void Player2SystemInit(void);
void Player2GameInit(void);
void Player2Control(void);
void Player2Draw(void);
// 当たり判定
bool Player2HitCheck(XY_F ePos, XY_F eSize);
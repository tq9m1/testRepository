#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "player.h"
#include "shot.h"

// 変数宣言
int player2Image;
CHARACTER player2;


// 画像初期化
void Player2SystemInit(void)
{
	player2Image = LoadGraph("image/player.png");
}

// 変数初期化
void Player2GameInit(void)
{
	player2.visible = true;
	player2.pos = { SCREEN_SIZE_X / 2-72, 0 + player.size.x / 2 };
	player2.size = { 32,32 };
	player2.sizeOffset = { player.size.x / 2, player.size.y / 2 };
	player2.moveSpeed = 6;
	player2.life = 10;
	player2.lifeMax = player.life;
	player2.shotFlag = false;
	player2.damageFlag = false;
}

// 操作処理
void Player2Control(void)
{
	// ---------- ﾌﾟﾚｲﾔｰ操作
	bool player2Moved = false;
	// 右移動
	if (newKey[P2_RIGHT]) {
		player2Moved = true;
		player2.pos.x += player2.moveSpeed;
	}
	// 左移動
	if (newKey[P2_LEFT]) {
		player2Moved = true;
		player2.pos.x -= player2.moveSpeed;
	}
	/* 上移動
	if (newKey[P1_UP]) {
		playerMoved = true;
		player.pos.y -= player.moveSpeed;
	}
	// 下移動
	if (newKey[P1_DOWN]) {
		playerMoved = true;
		player.pos.y += player.moveSpeed;
	}*/

	// ----- 移動制限
	// 右
	if (player2.pos.x > SCREEN_SIZE_X - player2.size.x / 2 - 150) {
		player2.pos.x = SCREEN_SIZE_X - player2.size.x / 2 - 150;
	}
	// 左
	if (player2.pos.x < player2.size.x / 2) {
		player2.pos.x = player2.size.x / 2;
	}
	// 上
	if (player2.pos.y < player2.size.y / 2) {
		player2.pos.y = player2.size.y / 2;
	}
	// 下
	if (player2.pos.y > SCREEN_SIZE_Y - player2.size.y / 2) {
		player2.pos.y = SCREEN_SIZE_Y - player2.size.y / 2;
	}

	/* 弾の発射
	if (newKey[P1_RCTR]) {
		if(player.visible){
			player.shotFlag = true;
			Shoot(player.pos);

		}
	}*/
}

// 当たり判定
bool Player2HitCheck(XY_F ePos, XY_F eSize)
{
	if ((player2.visible) && (player2.damageFlag == false)) {
		if (((player2.pos.x + player2.sizeOffset.x - 14) >= (ePos.x - eSize.x))
			&& ((player2.pos.x - player2.sizeOffset.x + 14) <= (ePos.x + eSize.x))
			&& ((player2.pos.y + player2.sizeOffset.y - 13) >= (ePos.y - eSize.y))
			&& ((player2.pos.y - player2.sizeOffset.y + 13) <= (ePos.y + eSize.y)))
		{
			player2.damageFlag = true;
			if (player2.damageFlag == true) {
				player2.visible = false;
			}
			return true;
		}
	}
	return false;
}

// 描画処理
void Player2Draw(void)
{
	// ﾌﾟﾚｲﾔｰの表示
	if (player2.visible) {
		DrawGraph(player2.pos.x - player2.sizeOffset.x,
			player2.pos.y - player2.sizeOffset.y, player2Image, true);
	}

	/* ----- 当たり判定調整用
		DrawBox(player.pos.x - player.sizeOffset.x+14, player.pos.y + player.sizeOffset.y-13,
			player.pos.x + player.sizeOffset.x-14, player.pos.y - player.sizeOffset.y+13, 0xffffff, false);
	*/

	// ﾌﾟﾚｲﾔｰ座標の表示
//	DrawFormatString(0, 40, 0xffffff, "PLAYER = %d %d", player.pos);
}
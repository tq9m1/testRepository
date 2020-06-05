#pragma once

// 定数
#define SHOT_MAX 20

extern CHARACTER shot[SHOT_MAX];
extern CHARACTER eshot[SHOT_MAX];

/* ------- プロトタイプ宣言 -------*/
void ShotSystemInit(void);
void ShotGameInit(void);
void ShotControl(void);
void ShotDraw(void);
// -----弾の発射関数
// ﾌﾟﾚｲﾔｰ
void Shoot(XY_F pPos);

// ----- 弾の変数を別の場所で使うための関数
// ﾌﾟﾚｲﾔｰ
CHARACTER GetShot(int index);
// ｴﾈﾐｰ
CHARACTER GetShotE(int index);
// ----- 弾のﾌﾗｸﾞを消す
// ﾌﾟﾚｲﾔｰ
void ShotDelete(int index);
// ｴﾈﾐｰ
void EShotDelete(int index);
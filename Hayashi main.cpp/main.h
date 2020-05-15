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

// ｷｬﾗｸﾀ構造体
typedef struct {
//	MOVE_DIR moveDir;	// 向いている方向
	XY_F pos;				// ｷｬﾗｸﾀの位置(中心）
	XY_F speed;
	XY_F size;			// ｷｬﾗｸﾀの画像ｻｲｽﾞ
	XY_F sizeOffset;		// ｷｬﾗｸﾀ中央からの左上位置
	XY hitPosS;			// 当たり判定用の左上
	XY hitPosE;			// 当たり判定用の右下
//	bool runFlag;		// ｷｬﾗｸﾀの状態(走っているか？）
//	bool jumpFlag;		// ｷｬﾗｸﾀの状態(ジャンプしているか？）
	bool shotFlag;		// ｷｬﾗｸﾀの状態(弾を撃っているか？）
	bool damageFlag;	// ｷｬﾗｸﾀの状態(ﾀﾞﾒｰｼﾞを受けているか？）
	int moveSpeed;		// ｷｬﾗｸﾀの移動量
	int life;			// ｷｬﾗｸﾀの体力
	int lifeMax;		// ｷｬﾗｸﾀの最大体力
	int animCnt;		// ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ用ｶｳﾝﾀ
//	int imgLockCnt;		// ｷｬﾗｸﾀのｲﾒｰｼﾞ固定用ｶｳﾝﾀ
	XY_F velocity;		// 移動速度
	bool visible;		// 表示状態
	int point;			// ｽｺｱ加算
//	int type;			// 何らかの属性を格納できる
	int MovCnt;			// 敵の動作ｶｳﾝﾄ
	double angle;		// 角度
	XY mov;
}CHARACTER;

// ----- ﾌﾟﾛﾄﾀｲﾌﾟ宣言
// ｽｺｱ
void AddScore(int point);
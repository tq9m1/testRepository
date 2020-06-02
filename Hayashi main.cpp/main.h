#pragma once

#define SCREEN_SIZE_X 860
#define SCREEN_SIZE_Y 600

#define PI_F 3.141592

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
	float rad;
}CHARACTER;

// ----- ﾌﾟﾛﾄﾀｲﾌﾟ宣言
// ｽｺｱ
void AddScore(int point);

//サイズを表す構造体
struct Size {
	float w;//幅
	float h;//高さ
};

//2D座標・ベクトルを表す構造体
struct Vector2 {
	Vector2() :x(0), y(0) {}
	Vector2(float inx, float iny) :x(inx), y(iny) {}
	float x, y;
	///ベクトルの大きさを返します
	float Magnitude()const;

	///正規化(大きさを１に)します
	void Normalize();

	///正規化ベクトルを返します
	Vector2 Normalized();

	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
	void operator*=(float scale);
	Vector2 operator*(float scale);
	Vector2 operator-() {
		return Vector2(-x, -y);
	}
};

Vector2 operator+(const Vector2& va, const Vector2 vb);
Vector2 operator-(const Vector2& va, const Vector2 vb);

///内積を返す
float Dot(const Vector2& va, const Vector2& vb);

///外積を返す
float Cross(const Vector2& va, const Vector2& vb);

///内積演算子
float operator*(const Vector2& va, const Vector2& vb);

///外積演算子
float operator%(const Vector2& va, const Vector2& vb);

//とりあえず「座標」って意味だとベクタより
//Positionのほうがよくね？って理由でこの名前
typedef Vector2 Position2;


//3D座標・ベクトルを表す構造体
struct Vector3 {
	Vector3() :x(0), y(0), z(0) {}
	Vector3(float inx, float iny, float inz) :x(inx), y(iny), z(inz) {}
	float x, y, z;
	///ベクトルの大きさを返します
	float Magnitude()const;

	///正規化(大きさを１に)します
	void Normalize();

	///正規化ベクトルを返します
	Vector3 Normalized();

	void operator+=(const Vector3& v);
	void operator-=(const Vector3& v);
	void operator*=(float scale);
	Vector3 operator*(float scale)const;
	Vector3 operator-() {
		return Vector3(-x, -y, -z);
	}
};
Vector3 operator+(const Vector3& va, const Vector3 vb);
Vector3 operator-(const Vector3& va, const Vector3 vb);

///内積を返す
float Dot(const Vector3& va, const Vector3& vb);

///外積を返す
Vector3 Cross(const Vector3& va, const Vector3& vb);

///内積演算子
float operator*(const Vector3& va, const Vector3& vb);

///外積演算子
Vector3 operator%(const Vector3& va, const Vector3& vb);
typedef Vector3 Position3;

///円を表す構造体
struct Circle {
	float radius;//半径
	Position2 pos; //中心座標
	Circle() :radius(0), pos(0, 0) {}
	Circle(float r, Position2& p) :radius(r), pos(p) {}
};


///球を表す構造体
struct Sphere {
	float radius;//半径
	Position3 pos; //中心座標
	Sphere() :radius(0), pos(0, 0, 0) {}
	Sphere(float r, Position3& p) :radius(r), pos(p) {}
};

///矩形を表す構造体
struct Rect {
	Position2 pos; //中心座標
	int w, h;//幅,高さ
	Rect() : pos(0, 0), w(0), h(0) {}
	Rect(float x, float y, int inw, int inh) :
		pos(x, y), w(inw), h(inh) {}
	Rect(Position2& inpos, int inw, int inh) :
		pos(inpos), w(inw), h(inh)
	{}
	void SetCenter(float x, float y) {
		pos.x = x;
		pos.y = y;
	}
	void SetCenter(const Position2& inpos) {
		pos.x = inpos.x;
		pos.y = inpos.y;
	}
	Vector2 Center() {
		return pos;
	}
	float Left() { return pos.x - w / 2; }
	float Top() { return pos.y - h / 2; }
	float Right() { return pos.x + w / 2; }
	float Bottom() { return pos.y + h / 2; }
	void Draw();//自分の矩形を描画する
	void Draw(Vector2& offset);//自分の矩形を描画する(オフセット付き)
};

/*struct Bullet {
	Position2 pos;//座標
	Vector2 vel;//速度
	bool isActive = false;//生きてるか～？
};
Bullet bullets[100];
Position2 enemypos(100, -25);
Position2 playerpos(358, 500);//自機座標*/

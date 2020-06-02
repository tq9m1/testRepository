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
	float rad;
}CHARACTER;

// ----- �������ߐ錾
// ���
void AddScore(int point);

//�T�C�Y��\���\����
struct Size {
	float w;//��
	float h;//����
};

//2D���W�E�x�N�g����\���\����
struct Vector2 {
	Vector2() :x(0), y(0) {}
	Vector2(float inx, float iny) :x(inx), y(iny) {}
	float x, y;
	///�x�N�g���̑傫����Ԃ��܂�
	float Magnitude()const;

	///���K��(�傫�����P��)���܂�
	void Normalize();

	///���K���x�N�g����Ԃ��܂�
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

///���ς�Ԃ�
float Dot(const Vector2& va, const Vector2& vb);

///�O�ς�Ԃ�
float Cross(const Vector2& va, const Vector2& vb);

///���ω��Z�q
float operator*(const Vector2& va, const Vector2& vb);

///�O�ω��Z�q
float operator%(const Vector2& va, const Vector2& vb);

//�Ƃ肠�����u���W�v���ĈӖ����ƃx�N�^���
//Position�̂ق����悭�ˁH���ė��R�ł��̖��O
typedef Vector2 Position2;


//3D���W�E�x�N�g����\���\����
struct Vector3 {
	Vector3() :x(0), y(0), z(0) {}
	Vector3(float inx, float iny, float inz) :x(inx), y(iny), z(inz) {}
	float x, y, z;
	///�x�N�g���̑傫����Ԃ��܂�
	float Magnitude()const;

	///���K��(�傫�����P��)���܂�
	void Normalize();

	///���K���x�N�g����Ԃ��܂�
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

///���ς�Ԃ�
float Dot(const Vector3& va, const Vector3& vb);

///�O�ς�Ԃ�
Vector3 Cross(const Vector3& va, const Vector3& vb);

///���ω��Z�q
float operator*(const Vector3& va, const Vector3& vb);

///�O�ω��Z�q
Vector3 operator%(const Vector3& va, const Vector3& vb);
typedef Vector3 Position3;

///�~��\���\����
struct Circle {
	float radius;//���a
	Position2 pos; //���S���W
	Circle() :radius(0), pos(0, 0) {}
	Circle(float r, Position2& p) :radius(r), pos(p) {}
};


///����\���\����
struct Sphere {
	float radius;//���a
	Position3 pos; //���S���W
	Sphere() :radius(0), pos(0, 0, 0) {}
	Sphere(float r, Position3& p) :radius(r), pos(p) {}
};

///��`��\���\����
struct Rect {
	Position2 pos; //���S���W
	int w, h;//��,����
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
	void Draw();//�����̋�`��`�悷��
	void Draw(Vector2& offset);//�����̋�`��`�悷��(�I�t�Z�b�g�t��)
};

/*struct Bullet {
	Position2 pos;//���W
	Vector2 vel;//���x
	bool isActive = false;//�����Ă邩�`�H
};
Bullet bullets[100];
Position2 enemypos(100, -25);
Position2 playerpos(358, 500);//���@���W*/

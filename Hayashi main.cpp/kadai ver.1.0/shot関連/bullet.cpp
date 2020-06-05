#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "bullet.h"
#include "player.h"
#include <math.h>
#include "enemy.h"

// •Ï”éŒ¾
int bulletImage;
CHARACTER bullet[BULLET_MAX];
int testBulletImage;
CHARACTER testBullet[BULLET_MAX];

int tamaImage;
CHARACTER tama[BULLET_MAX];
/*struct Bullet {
	Position2 pos;//À•W
	Vector2 vel;//‘¬“x
	bool isActive = false;
};
Bullet bullets[100];*/

// “G’e‰æ‘œ‰Šú‰»
void BulletSystemInit(void)
{
	bulletImage = LoadGraph("image/eshot.png");
	testBulletImage = LoadGraph("image/shot.png");
	/*auto tama2 = LoadGraph("image/tama2.png");
	auto tama3 = LoadGraph("image/tama3.png");
	auto tama4 = LoadGraph("image/tama4.png");
	auto tama5 = LoadGraph("image/tama5.png");
	auto tama6 = LoadGraph("image/tama6.png");*/
	tamaImage = LoadGraph("image/tama2.png");
}

// “G’e•Ï”‰Šú‰»
void BulletGameInit(void)
{
	// ´ÈĞ°¼®¯Ä‚Ì•Ï”
	for (int i = 0; i < BULLET_MAX; i++) {
		bullet[i].visible = false;
		bullet[i].pos = { 0,0 };
		bullet[i].size = { 16,16 };
		bullet[i].sizeOffset = { bullet[i].size.x / 2, bullet[i].size.y / 2 };
		bullet[i].moveSpeed = 3;
		bullet[i].MovCnt = 0;
		bullet[i].angle = 0;
		bullet[i].mov = { 0, 0 };
	}

	for (int j = 0; j < BULLET_MAX; j++) {
		testBullet[j].visible = false;
		testBullet[j].pos = { 0,0 };
		testBullet[j].size = { 16,16 };
		testBullet[j].sizeOffset = { testBullet[j].size.x / 2,testBullet[j].size.y / 2 };
		testBullet[j].moveSpeed = 2;
		testBullet[j].MovCnt = 0;
		testBullet[j].angle = 0;
		testBullet[j].mov = { 0,0 };
	}

	for (int t = 0; t < BULLET_MAX; t++) {
		tama[t].visible = 0;
		tama[t].pos = { 0,0 };
		tama[t].size = { 32,32 };
		tama[t].sizeOffset = { 16,16 };
		tama[t].moveSpeed = 5;
		tama[t].MovCnt = 0;
		tama[t].angle = 0;
		tama[t].mov = { 0,0 };
	}
	
}

// “G’e‘€ì
void BulletControl(void){	
	// ’e‚ÌˆÚ“®(´ÈĞ°)
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bullet[i].visible) {
//			bullet[i].pos.x -= bullet[i].mov.x;
//			bullet[i].pos.y -= bullet[i].mov.y;
			bullet[i].pos.x += bullet[i].speed.x;
			bullet[i].pos.y += bullet[i].speed.y;
			if ((bullet[i].pos.x > SCREEN_SIZE_X - 160)
			  ||(bullet[i].pos.x < 0)
			  ||(bullet[i].pos.y > SCREEN_SIZE_Y)
			  ||(bullet[i].pos.y < 0)) 
			{
//				bullet[i].MovCnt = 0;
				bullet[i].visible = false;
			}
		}
	}

	// testEnemy
	for (int j = 0; j < BULLET_MAX; j++) {
		if (testBullet[j].visible) {
			testBullet[j].pos.x += testBullet[j].speed.x;
			testBullet[j].pos.y += testBullet[j].speed.y;
			if ((testBullet[j].pos.x > SCREEN_SIZE_X - 160)
				|| (testBullet[j].pos.x < 0)
				|| (testBullet[j].pos.y > SCREEN_SIZE_Y)
				|| (testBullet[j].pos.y < 0))
			{
				testBullet[j].visible = false;
			}
		}
	}

	//“Áê“G(teki)
	/*for (auto& b : bullets) {
		if (b.isActive) {
			continue;
		}
		b.pos = b.pos + b.vel;
		if (b.pos.x + 16 < 0 || b.pos.x - 16 > SCREEN_SIZE_X-160 ||
			b.pos.y + 24 < 0 || b.pos.y - 24 > SCREEN_SIZE_Y) {
			b.isActive = false;
		}
	}*/
	for (int t = 0; t < BULLET_MAX; t++){
		if (tama[t].visible) {
			tama[t].pos.x += tama[t].speed.x;
			tama[t].pos.y += tama[t].speed.y;
			if ((tama[t].pos.x > 700)
				|| (tama[t].pos.x < 0)
				|| (tama[t].pos.y > 600)
				|| (tama[t].pos.y < 0)) {
				tama[t].visible = 0;
			}
		}
	}
}

// ’e‚Ì”­Ë(´ÈĞ°)
void EShoot(XY_F ePos)
{
	for (int i = 0; i < BULLET_MAX; i++) {
		if (!bullet[i].visible) {
			bullet[i].pos = { ePos.x , ePos.y };
			bullet[i].visible = true;
			bullet[i].speed.x = 1;
			bullet[i].speed.y = 1;
		}
	}	
}

void tEShoot(XY_F tePos) {
	for (int j = 0; j < BULLET_MAX; j++) {
		if (!testBullet[j].visible) {
			testBullet[j].pos = { tePos.x,tePos.y };
			testBullet[j].visible = 1;
			testBullet[j].speed.x = 1;
			testBullet[j].speed.y = 1;
		}
	}
}

//’e‚Ì”­Ë(“Áê“G)		*À‘•‚Í‚µ‚Ä‚¢‚È‚¢
void tekiShoot(XY_F tekiPos) {
	for (int t = 0; t < BULLET_MAX; t++) {
		if (!tama[t].visible) {
			tama[t].pos = { tekiPos.x,tekiPos.y };
			tama[t].visible = 1;
			tama[t].speed.x = 1;
			tama[t].speed.x = 1;
		}
	}
}

// “G’e•`‰æ
void BulletDraw(void)
{
	// ´ÈĞ°‚Ì’e
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bullet[i].visible) {
			DrawGraph(bullet[i].pos.x - bullet[i].sizeOffset.x,
				bullet[i].pos.y - bullet[i].sizeOffset.y, bulletImage, true);
		}
	}

	for (int j = 0; j < BULLET_MAX; j++) {
		if (testBullet[j].visible) {
			DrawGraph(testBullet[j].pos.x - testBullet[j].sizeOffset.x,
				testBullet[j].pos.y - testBullet[j].sizeOffset.y, testBulletImage, true);
		}
	}

	/*for (auto& b : bullets) {
		if (!b.isActive) {
			continue;
		}
		b.pos = b.pos + b.vel;
		float angle2 = atan2(b.vel.y, b.vel.x);
		DrawRotaGraph(b.pos.x, b.pos.y, 1.0f, angle2, tamaImage, true);
	}*/
	for (int t = 0; t < BULLET_MAX; t++) {
		if (tama[t].visible) {
			DrawGraph(tama[t].pos.x - tama[t].sizeOffset.x,
				tama[t].pos.y - tama[t].sizeOffset.y, tamaImage, 1);
		}
	}
}
#include <math.h>
#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "enemy.h"
#include "bullet.h"
#include "player.h"
#include "blast.h"

// •Ï”
int enemyImage;
CHARACTER enemy[ENEMY_MAX];
int testEnemyImage;
CHARACTER testEnemy[TESTENEMY_MAX];

int enemyCounter;
int deathSe;
int testEnemyCnt;

unsigned int frame = 0;//ƒtƒŒ[ƒ€ŠÇ——p
int tekihyouji=1;
//int teki = GetRand(100);
//int teki2 = GetRand(100);
int enemyH[2];
int enemyH2[2];
int enemyH3[2];
int enemyH4[2];
int enemyH5[2];
float enemyRadius = 15.0f;
//Position2 enemypos(100, -25);

// ‰æ‘œ‰Šú‰»
void EnemySystemInit(void)
{
	enemyImage = LoadGraph("image/enemy.png");
	deathSe = LoadSoundMem("bgm/shoot1.mp3");
	testEnemyImage = LoadGraph("image/CUTE ufo.png");
	LoadDivGraph("image/teki1.png", 2, 2, 1, 32, 32, enemyH);
	LoadDivGraph("image/teki2.png", 2, 2, 1, 32, 32, enemyH2);
	LoadDivGraph("image/teki3.png", 2, 2, 1, 32, 32, enemyH3);
	LoadDivGraph("image/teki4.png", 2, 2, 1, 32, 32, enemyH4);
	LoadDivGraph("image/teki5.png", 2, 2, 1, 32, 32, enemyH5);
}

// “G‚Ì’Ç‰Áˆ—
void EnemyAdd(void)
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i].visible)
			continue;
		enemy[i].visible = true;
		enemy[i].size = { 52,50 };
		enemy[i].sizeOffset = { enemy[i].size.x / 2, enemy[i].size.y / 2 };
		enemy[i].pos = { SCREEN_SIZE_X / 2, 0 };
		enemy[i].pos.x = GetRand(SCREEN_SIZE_X - 160 - enemy[i].size.x);
		enemy[i].pos.y = -enemy[i].sizeOffset.y;
		enemy[i].moveSpeed = 2;
		enemy[i].animCnt = 0;
		enemy[i].damageFlag = false;
		enemy[i].shotFlag = false;
		enemy[i].point = 100;
		enemy[i].MovCnt = 0;
		return;
	}
	for (int j = 0; j < TESTENEMY_MAX; j++) {
		if (testEnemy[j].visible)
			continue;
		testEnemy[j].visible = true;
		testEnemy[j].size = { 36,36 };
		testEnemy[j].sizeOffset = { testEnemy[j].size.x / 2,testEnemy[j].size.y / 2 };
		testEnemy[j].pos = { SCREEN_SIZE_X / 2,20 };
		testEnemy[j].pos.x = GetRand(SCREEN_SIZE_X - 160 - testEnemy[j].size.x);
		testEnemy[j].pos.y = -testEnemy[j].sizeOffset.y;
		testEnemy[j].moveSpeed = 2;
		testEnemy[j].animCnt = 0;
		testEnemy[j].damageFlag = false;
		testEnemy[j].shotFlag = false;
		testEnemy[j].point = 50;
		testEnemy[j].MovCnt = 0;
		return;
	}
	
}

// •Ï”‰Šú‰»
void EnemyGameInit(void)
{
	// “G‚ÌŠî‘b•Ï”‰Šú‰»
	for (int i = 0; i < ENEMY_MAX; i++) {
		enemy[i].visible = true;
		enemy[i].size = { 52,50 };
		enemy[i].sizeOffset = { enemy[i].size.x / 2, enemy[i].size.y / 2 };
		enemy[i].pos = { SCREEN_SIZE_X / 2, 0 };
		enemy[i].pos.x = GetRand(SCREEN_SIZE_X - 160 - enemy[i].size.x);
		enemy[i].pos.y = -enemy[i].sizeOffset.y;
		enemy[i].moveSpeed = 2;
		enemy[i].animCnt = 0;
		enemy[i].damageFlag = false;
		enemy[i].shotFlag = false;
		enemy[i].point = 100;
		enemy[i].MovCnt = 0;
	}

	for (int j = 0; j < TESTENEMY_MAX; j++) {
		testEnemy[j].visible = true;
		testEnemy[j].size = { 36,36 };
		testEnemy[j].sizeOffset = { testEnemy[j].size.x / 2, testEnemy[j].size.y / 2 };
		testEnemy[j].pos = { SCREEN_SIZE_X / 2,20 };
		testEnemy[j].pos.x = GetRand(SCREEN_SIZE_X - 100 - testEnemy[j].size.x);
		testEnemy[j].pos.y = -testEnemy[j].sizeOffset.y;
		testEnemy[j].moveSpeed = 2;
		testEnemy[j].animCnt = 0;
		testEnemy[j].damageFlag = false;
		testEnemy[j].shotFlag = false;
		testEnemy[j].point = 50;
		testEnemy[j].MovCnt = 0;
	}
	for (int i = 0; i < 10; i++) {
		EnemyAdd();
	}
}

// “G‘€ì
void EnemyControl(void)
{
	// --------- “G‚Ì“®‚«
	for (int i = 0; i < ENEMY_MAX; i++) {
	  // “G‚ÌÀ•W‚ª70ˆÈ‰º‚È‚çˆÚ“®
		if (enemy[i].pos.y < 70) {
			enemy[i].pos.y += enemy[i].moveSpeed;
		}
		else { // “G‚Ì•\¦‚ªtrue‚©‚Â“G’e‚Ì•\¦‚ªfalse‚È‚ç“G‚ª’e‚ğŒ‚‚Â
			if ((enemy[i].visible)&&(bullet[i].visible == false)) {
				bullet[i].visible = true;
				bullet[i].pos = enemy[i].pos;
				bullet[i].speed.x = player.pos.x - enemy[i].pos.x;
				bullet[i].speed.y = player.pos.y - enemy[i].pos.y;
				float length = sqrt(bullet[i].speed.x * bullet[i].speed.x + bullet[i].speed.y * bullet[i].speed.y);
				bullet[i].speed.x /= length;
				bullet[i].speed.y /= length;
				bullet[i].speed.x *= bullet[i].moveSpeed;
				bullet[i].speed.y *= bullet[i].moveSpeed;
			}
		}
	}
	enemyCounter++;
	if (enemyCounter % 40 == 0) {
		for (int i = 0; i < 10; i++) {
			EnemyAdd();
		}
	}

	for (int j = 0; j < TESTENEMY_MAX; j++) {
		if (testEnemy[j].pos.y < 70) {
			testEnemy[j].pos.y += testEnemy[j].moveSpeed;
		}
		else if ((testEnemy[j].visible) && (testBullet[j].visible == 0)) {
			testBullet[j].visible = 1;
			testBullet[j].pos = testEnemy[j].pos;
			testBullet[j].speed.x = player.pos.x - testEnemy[j].pos.x;
			testBullet[j].speed.y = player.pos.y - testEnemy[j].pos.y;
			float length = sqrt(testBullet[j].speed.x * testBullet[j].speed.x + testBullet[j].speed.y * testBullet[j].speed.y);
			testBullet[j].speed.x /= length;
			testBullet[j].speed.y /= length;
			testBullet[j].speed.x *= testBullet[j].moveSpeed;
			testBullet[j].speed.y *= testBullet[j].moveSpeed;
		}		
	}
	testEnemyCnt++;
	if (testEnemyCnt % 40 == 0) {
		for (int j = 0; j < 10; j++) {
			EnemyAdd();
		}
	}
}

// “–‚½‚è”»’è
bool EnemyHitCheck(XY_F sPos, XY_F sSize)//enemy‚Æshot‚Ì“–‚½‚è”»’è
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if ((enemy[i].visible) && (enemy[i].damageFlag == false)) {
			if (((enemy[i].pos.x + enemy[i].sizeOffset.x - 7) >= (sPos.x - sSize.x))
				&& ((enemy[i].pos.x - enemy[i].sizeOffset.x + 7) <= (sPos.x + sSize.x))
				&& ((enemy[i].pos.y + enemy[i].sizeOffset.y - 7) >= (sPos.y - sSize.y))
				&& ((enemy[i].pos.y - enemy[i].sizeOffset.y + 7) <= (sPos.y + sSize.y))) 
			{
				enemy[i].damageFlag = true;
				if(enemy[i].damageFlag == true){
					enemy[i].visible = false;
					AddScore(enemy[i].point);					
					PlaySoundMem(deathSe, DX_PLAYTYPE_BACK);
					ChangeVolumeSoundMem(255 * 70 / 100, deathSe);
					BlastGenerator(enemy[i].pos);
				}
				return true;
			}
		}
	}
	return false;
}

bool tesEnemyHitCheck(XY_F sPos, XY_F sSize) {
	for (int j = 0; j < ENEMY_MAX; j++) {
		if ((testEnemy[j].visible) && (testEnemy[j].damageFlag == 0)) {
			if (((testEnemy[j].pos.x + testEnemy[j].sizeOffset.x - 7) >= (sPos.x - sSize.x))
				&&((testEnemy[j].pos.x-testEnemy[j].sizeOffset.x+7)<=(sPos.x+sSize.x))
				&&((testEnemy[j].pos.y+testEnemy[j].sizeOffset.y-7)>=(sPos.y+sSize.y))
				&& ((testEnemy[j].pos.y - testEnemy[j].sizeOffset.y + 7) <= (sPos.y + sSize.y))) {
				testEnemy[j].damageFlag = 1;
				if (testEnemy[j].damageFlag == 1) {
					testEnemy[j].visible = 0;
					AddScore(testEnemy[j].point);
					PlaySoundMem(deathSe, DX_PLAYTYPE_BACK);
					ChangeVolumeSoundMem(255 * 70 / 100, deathSe);
					BlastGenerator(testEnemy[j].pos);
				}
				return 1;
			}
		}
	}
	return 0;
}

// •`‰æ
void EnemyDraw(void)
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i].visible) {
			DrawGraph(enemy[i].pos.x - enemy[i].sizeOffset.x,
				enemy[i].pos.y - enemy[i].sizeOffset.y,
				enemyImage, true);
		}
	}
	for (int j = 0; j < 1; j++){
		if (testEnemy[j].visible){
			DrawGraph(testEnemy[j].pos.x - testEnemy[j].sizeOffset.x,
				testEnemy[j].pos.y - testEnemy[j].sizeOffset.y,
				testEnemyImage, 1);
		}
	}

	/*enemypos.x = abs((int)((frame + 320) % 1280) - 640);
	enemypos.y = enemypos.y + 3.0f;

	int eidx = (frame / 4 % 2);	

	if (tekihyouji == 1) {
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx], true);
	}	
	else if (tekihyouji == 2) {
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH2[eidx], true);
	}	
	else if (tekihyouji == 3) {
			DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH3[eidx], true);	
	}
	else if (tekihyouji == 4) {
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH4[eidx], true);
	}
	else if (tekihyouji == 5) {
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH5[eidx], true);
	}
	++frame;*/
}

//void tekiInit(void) {
//	typedef enum {
//		TEKI_INIT,
//		TAMA_MAIN,
//		TAMA_1,
//		TAMA_2,
//		TAMA_3,
//		TAMA_4,
//		TAMA_5,
//		TEKI_OWARI
//	}TEKI_MODE;
//	TEKI_MODE tekiMode;
//	switch (tekiMode) {
//	case TEKI_INIT:
//		teki = GetRand(100);
//		tekiMode = TAMA_MAIN;
//		break;
//	case TAMA_MAIN://enemy&bullet
//		if (teki >= 0 && teki <= 19) {
//			tekiMode = TAMA_1;
//		}
//		break;
//	case TAMA_1://bullet
//		tama = bulletH;
//		tekihyouji = 1;//enemy
//		for (int i = 0; i < 3; i++) {
//			if (frame % 12 == 0) {
//				for (auto& b : bullets) {//bullet
//					if (!b.isActive) {
//						b.pos = enemypos;//bullet&enemy
//						if (i == 0) {
//							angle += 0.2f;
//						}
//						else if (i == 1) {//bullet,player,enemy
//							angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
//						}
//						else {
//							angle -= 0.2f;
//						}
//						b.vel = Vector2(cos(angle), sin(angle)).Normalized() * 5;//DX_PI
//						b.isActive = true;
//						if (enemypos.y >= 600) tekiMode = TEKI_OWARI;
//						break;
//					}
//				}
//			}
//		}
//
//		break;
//	}
//}
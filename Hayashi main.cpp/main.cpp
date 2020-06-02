#include "DxLib.h"
#include <math.h>
#include "main.h"
#include "keyCheck.h"
#include "player.h"
#include "shot.h"
#include "enemy.h"
#include "bullet.h"
#include "stage.h"
#include "blast.h"

//#include "player2.h"
#include "testPlayer.h"

typedef enum {
	TEKI_INIT,
	TAMA_MAIN,
	TAMA_1,
	/*TAMA_2,
	TAMA_3,
	TAMA_4,
	TAMA_5,*/
	TEKI_OWARI,
	TEKI_MAX
}TEKI_MODE;
TEKI_MODE tekiMode;

typedef enum {
	GMODE_INIT,
	TEST_GMODE_INIT,
	GMODE_TITLE,
	GMODE_GAME,
	//TEKI_INIT,
	//TAMA_MAIN,
	//TAMA_1,
	//TAMA_2,
	//TAMA_3,
	//TAMA_4,
	//TAMA_5,
	//TEKI_OWARI,
	TEST_GMODE_GAME,
	GMODE_OVER,
	GMODE_MAX
}GAME_MODE;
GAME_MODE gameMode;

typedef struct {
	int data1;
	int hiscore;
}FILE_DATA;

LONGLONG timecnt;
XINPUT_STATE xBoxoneinput;

// ----- •Ï”’è‹`
int gameCounter;

// ÃŞ°À“Ç‚İ‚İ
char fileName[] = "data.dat";
FILE_DATA fileData;

// À²ÄÙ‰æ‘œ
int titleImage;
int titleBg;

// ¹Ş°Ñµ°ÊŞ°‰æ‘œ
int gOverImage;

// Ìª°ÄŞ
int fadeCnt;
bool fadeIn;
bool fadeOut;

// ˆê’â~‚ÌÌ×¸Ş(true:’â~)
bool pauseFlag;
// •¶š“_–Å¶³İÄ
int hitKeyCnt;

// BGM
int mainBgm;
int endBgm;

// ½º±
int score;
int hiScore;
int numImage[11];
int charImage[27];

char Key[256];

int testt=1;

int cnt = 0, test = 1;
int startTime;		// ƒXƒ^[ƒg‚ğ‹L‰¯‚µ‚Ä‚¨‚­
unsigned int color = GetColor(0, 255, 255);	// ƒJƒ‰[ƒf[ƒ^‚ÌŠi”[
bool flg = false;

int teki = GetRand(100);
int teki2 = GetRand(100);
bool IsHit(const Position2& posA, float radiusA, const Position2& posB, float radiusB) {
	return(hypot(posA.x - posB.x, posA.y - posB.y) < radiusA + radiusB);
}

// ----- ÌßÛÄÀ²ÌßéŒ¾
bool SystemInit(void);
void GameInit(void);
void testGameInit(void);
void GameMain(void);
void testGameMain(void);
void GameDraw(void);
void testGameDraw(void);
void GameTitle(void);
void GameOver(void);
void HitCheck(void);
bool FadeInScreen(int fadeStep);
bool FadeOutScreen(int fadeStep);
void DrawStatus(const char* title, int value, int top);
void DrawStatusMain(const char* title, int value, int top);
bool SaveData(void);
bool LoadData(void);


// ========== WinMainŠÖ”
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ¼½ÃÑ‚Ì‰Šú‰»
	if (SystemInit() == false){
		DxLib_End();
		return 0;
	}
	gameMode = GMODE_INIT;

	auto bulletH = LoadGraph("image/tama2.png");
	auto bulletH2 = LoadGraph("image/tama3.png");
	auto bulletH3 = LoadGraph("image/tama4.png");
	auto bulletH4 = LoadGraph("image/tama5.png");
	auto bulletH5 = LoadGraph("image/tama6.png");
	int tama = bulletH;

	int enemyH[2];
	int enemyH2[2];
	int enemyH3[2];
	int enemyH4[2];
	int enemyH5[2];
	LoadDivGraph("image/teki1.png", 2, 2, 1, 32, 32, enemyH);
	LoadDivGraph("image/teki2.png", 2, 2, 1, 32, 32, enemyH2);
	LoadDivGraph("image/teki3.png", 2, 2, 1, 32, 32, enemyH3);
	LoadDivGraph("image/teki4.png", 2, 2, 1, 32, 32, enemyH4);
	LoadDivGraph("image/teki5.png", 2, 2, 1, 32, 32, enemyH5);
	
	int tekihyouji = 1;
	bool isDebugMode = 0;
	struct Bullet {
		Position2 pos;//À•W
		Vector2 vel;//‘¬“x
		bool isActive = false;//¶‚«‚Ä‚é‚©`H
	};
	Bullet bullets[100];
	Position2 enemypos(100, -25);
	Position2 playerpos(358, 500);//©‹@À•W
	unsigned int frame = 0;
	//’e‚Ì”¼Œa
	float bulletRadius = 5.0f;
	//ƒvƒŒƒCƒ„[‚Ì”¼Œa
	float playerRadius = 10.0f;
	
	// Œ»İŒo‰ßŠÔ‚ğ“¾‚é
	startTime = GetNowCount();
	// ---------- ¹Ş°ÑÙ°Ìß
	while (ProcessMessage() == 0 && GetNowCount() - startTime &&CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	// ‰æ–ÊÁ‹
		KeyCheck();

		// Œ»İ‚ÌŒo‰ßŠÔ‚ğ•\¦
		if (true) {
			ClearDrawScreen();
			DrawFormatString(0, 10, color, " %d•b\n",
				(GetNowCount() - startTime) / 1000,
				GetNowCount() - startTime);
		}
		if (GetNowCount() - startTime <= 1000) {
			// ‰æ–Ê‚É•\¦
			ClearDrawScreen();
			test++;
			flg = true;
		}

		float angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
		int eidx = (frame / 4 % 2);
		/*switch (tekiMode)//“Gˆ—
		{
		case TEKI_INIT:
			teki = GetRand(100);
			tekiMode = TAMA_MAIN;
			break;
		case TAMA_MAIN:
			if (teki >= 0 && teki <= 19) {
				tekiMode = TAMA_1;
			}
			/*else if (teki >= 20 && teki <= 39) {
				tekiMode = TAMA_2;
			}
			else if (teki >= 40 && teki <= 59) {
				tekiMode = TAMA_3;
			}
			else if (teki >= 60 && teki <= 79) {
				tekiMode = TAMA_4;
			}
			else if (teki >= 80 && teki <= 100) {
				tekiMode = TAMA_5;
			}
			break;
		case TAMA_1://bullet
			tama = bulletH;
			tekihyouji = 1;//enemy
			for (int i = 0; i < 3; i++) {
				if (frame % 12 == 0) {
					for (auto& b : bullets) {//bullet
						if (!b.isActive) {
							b.pos = enemypos;//bullet&enemy
							if (i == 0) {
								angle += 0.2f;
							}
							else if (i == 1) {//bullet,player,enemy
								angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
							}
							else {
								angle -= 0.2f;
							}
							b.vel = Vector2(cos(angle), sin(angle)).Normalized() * 5;//DX_PI

							b.isActive = true;
							if (enemypos.y >= 600) tekiMode = TEKI_OWARI;
							break;
						}
					}
				}
			}
			break;*/
		/*case TAMA_2:
			tama = bulletH2;
			tekihyouji = 2;
			for (int i = 0; i < 50; i++) {
				if (frame % 12 == 0) {
					for (auto& b : bullets) {
						if (!b.isActive) {
							b.pos = enemypos;
							if (i == 0) {
								angle += 0.5f;
							}
							else if (i == 1) {
								angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
							}
							else {
								angle -= 0.5f;
							}
							b.vel = Vector2(cos(angle), sin(angle)).Normalized() * 5;//DX_PI
							 //b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI

							b.isActive = true;
							if (enemypos.y >= 600) tekiMode = TEKI_OWARI;
							break;
						}
					}
				}
			}

			break;
		case TAMA_3:
			tama = bulletH3;
			tekihyouji = 3;
			for (int i = 0; i < GetRand(300); i++) {
				if (frame % 12 == 0) {
					for (auto& b : bullets) {
						if (!b.isActive) {
							b.pos = enemypos;
							if (i == 0) {
								angle += 0.2f;
							}
							else if (i == 1) {
								angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
							}
							else {
								angle -= 0.2f;
							}
							b.vel = Vector2(cos(angle), sin(angle)).Normalized() * (GetRand(10) + 1);//DX_PI
							//b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI

							b.isActive = true;
							if (enemypos.y >= 600) tekiMode = TEKI_OWARI;
							break;
						}
					}
				}
			}
			if (enemypos.y >= 600) tekiMode = TEKI_OWARI;
			break;
		case TAMA_4:
			tama = bulletH4;
			tekihyouji = 4;
			for (int i = 0; i < 7; i++) {
				if (frame % 12 == 0) {
					for (auto& b : bullets) {
						if (!b.isActive) {
							b.pos = enemypos;
							if (i == 0) {
								angle += 0.2f;
							}
							else if (i == 1) {
								angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
							}
							else {
								angle -= 0.2f;
							}
							b.vel = Vector2(cos(angle), sin(angle)).Normalized() * 7;//DX_PI
							//b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI

							b.isActive = true;
							if (enemypos.y >= 600) tekiMode = TEKI_OWARI;
							break;
						}
					}
				}
			}

			break;
		case TAMA_5:
			tama = bulletH5;
			tekihyouji = 5;
			for (int i = 0; i < GetRand(30); i++) {
				if (frame % 12 == 0) {
					for (auto& b : bullets) {
						if (!b.isActive) {
							b.pos = enemypos;
							if (i == 0) {
								angle += 0.2f;
							}
							else if (i == 1) {
								angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
							}
							else {
								angle -= 0.2f;
							}
							b.vel = Vector2(cos(angle), sin(angle)).Normalized() * 3;//DX_PI
							//b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI

							b.isActive = true;
							if (enemypos.y >= 600) tekiMode = TEKI_OWARI;
							break;
						}
					}
				}
			}
			break;
		case TEKI_OWARI:
			enemypos.y = -60;
			teki2 = GetRand(100);
			teki = teki2;
			break;
		default:
			tekiMode = TAMA_MAIN;
			break;
		}*/

		switch (gameMode) {	// ƒƒCƒ“ˆ—
		case GMODE_INIT:			
			GameInit();
			gameMode = GMODE_TITLE;
			//PlaySoundMem(mainBgm, DX_PLAYTYPE_LOOP);	//BGM
			break;	
		case TEST_GMODE_INIT:
			testGameInit();
			gameMode = GMODE_TITLE;		
			//PlaySoundMem(mainBgm, DX_PLAYTYPE_LOOP);
			break;
		case GMODE_TITLE:
			//GetHitKeyStateAll(Key);
			if (fadeIn) {
				if (!FadeInScreen(2)) fadeIn = false;
			}
			else if (fadeOut) {
				if (!FadeOutScreen(2))
				{
					gameMode = GMODE_GAME;
					fadeOut = false;
					fadeIn = true;
				
				}
			}
			//else if (oldKey[P1_UP]&&trgKey[SPACE]) fadeOut = true;//W‰Ÿ‚µ‚È‚ª‚çSPACE‚ğ‰Ÿ‚·
			//else if (oldKey[P1_DOWN] && trgKey[SPACE]) fadeOut = 1;
			else if (CheckHitKey(KEY_INPUT_W) && CheckHitKey(KEY_INPUT_SPACE)||
				(xBoxoneinput.Buttons[XINPUT_BUTTON_DPAD_UP])) {
				fadeOut = 1;
				testt = 1;
			}
			GameTitle();
			if (fadeIn) {
				if (!FadeInScreen(2)) fadeIn = false;
			}
			else if (fadeOut) {
				if (!FadeOutScreen(2))
				{
					if (testt = 1) {
						gameMode = TEST_GMODE_GAME;
					}
					else if (testt = 2) {
						gameMode = TEST_GMODE_GAME;
					}
					fadeOut = false;
					fadeIn = true;
				}
			}
			else if (CheckHitKey(KEY_INPUT_S) && CheckHitKey(KEY_INPUT_SPACE))
			{
				fadeOut = 1;
				testt = 2;
			}
		break;
		case GMODE_GAME:
			if (fadeIn) {
				if (!FadeInScreen(5)) fadeIn = false;
			}
			else {
				if (fadeOut) {
					if (!FadeOutScreen(5)) {
						gameMode = GMODE_OVER;
						fadeOut = false;
						fadeIn = true;						
					}				
				}
				else if (player.visible == false) fadeOut = true;
			}

			enemypos.x = abs((int)((frame + 320) % 1280) - 640);
			enemypos.y = enemypos.y+5.0f;			
			DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx], true);

			LoadData();
			GameMain();
			//teki = GetRand(100);
			if (tekihyouji==1) {				
				tama = bulletH;				
				for (int i = 0; i < 3; i++) {
					if (frame % 12 == 0) {
						for (auto& b : bullets) {
							if (!b.isActive) {
								b.pos = enemypos;
								if (i == 0) {
									angle += 1.0f;
								}
								else if (i == 1) {
									angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
								}
								else {
									angle -= 1.0f;
								}
								b.vel = Vector2(cos(angle), sin(angle)).Normalized() * 3;//DX_PI
								b.isActive = true;
								if (enemypos.y >= 600)
									break;
							}
						}
					}
				}
			}
			break;
			enemypos.y = -60;
			teki = teki2;
			break;
			case TEST_GMODE_GAME:
			if (fadeIn) {
				if (!FadeInScreen(5)) fadeIn = false;
			}
			else {
				if (fadeOut) {
					if (!FadeOutScreen(5)) {
						gameMode = GMODE_OVER;
						fadeOut = false;
						fadeIn = true;
					}
				}
				else if (testPlayer.visible == false) fadeOut = true;
			}
			LoadData();
			testGameMain();
			break;
		case GMODE_OVER:
			if (fadeIn) {
				if (!FadeInScreen(5)) fadeIn = false;
			}
			else if(fadeOut){
				if(!FadeOutScreen(5)){
					gameMode = GMODE_TITLE;
					GameInit();
					fadeOut = false;
					fadeIn = true;
				}
			}
			else
			{
				if (trgKey[SPACE]) fadeOut = true;
			}
			GameOver();
			SaveData();
			break;
		default:
			gameMode = GMODE_INIT;
			GameInit();
			break;
		}
		for (auto& b : bullets) {
			if (!b.isActive) {
				continue;
			}
			b.pos = b.pos + b.vel;
			float angle2 = atan2(b.vel.y, b.vel.x);
			DrawRotaGraph(b.pos.x, b.pos.y, 1.0f, angle2, tama, true);
			/*if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {//“G‚Ì’e “–‚½‚è”»’è
				b.isActive = false;
			}*/
			if (isDebugMode) {
				//’e‚Ì–{‘Ì(“–‚½‚è”»’è)
				DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
			}
			//’e‚ğE‚·
			/*if (b.pos.x + 16 < 0 || b.pos.x - 16 > SCREEN_SIZE_X ||
				b.pos.y + 16 < 0 || b.pos.y - 16 > SCREEN_SIZE_Y) {
				b.isActive = false;
			}*/
		}
		/*enemypos.x = abs((int)((frame + 320) % 1280) - 640);
		enemypos.y = enemypos.y + 3.0f;
		int eidx = (frame / 4 % 2);
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx], true);*/

		gameCounter++;		
		ScreenFlip();		// — ‰æ–Ê‚ğ•\‰æ–Ê‚ÉuŠÔƒRƒs[
	}
	DxLib_End();			// DXƒ‰ƒCƒuƒ‰ƒŠ‚ÌI—¹ˆ—
	return 0;				// ‚±‚ÌƒvƒƒOƒ‰ƒ€‚ÌI—¹
}

/* -------ƒVƒXƒeƒ€‚Ì‰Šú‰»------- */
bool SystemInit(void)
{
	// ----- ¼½ÃÑˆ—
	SetWindowText("KaRi.exe");
	// ¼½ÃÑˆ—
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) {
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	KeyCheckSystemInit();

	/* ---------- ƒOƒ‰ƒtƒBƒbƒN‚Ì“o˜^ ---------- */
	// ÌßÚ²Ô°‰æ‘œ
	PlayerSystemInit();
	//Player2SystemInit();
	// ¼®¯Ä‰æ‘œ
	ShotSystemInit();
	// “G‰æ‘œ
	EnemySystemInit();
	// “G’e‰æ‘œ
	BulletSystemInit();
	// ”wŒi‰æ‘œ
	StageSystemInit();
	// ”š”j‰æ‘œ
	BlastSystemInit();
	// À²ÄÙ²Ò°¼Ş
	titleImage = LoadGraph("image/K a R i.png");
	titleBg = LoadGraph("image/haikei.png");
	// ¹Ş°Ñµ°ÊŞ°²Ò°¼Ş
	gOverImage = LoadGraph("image/gameover.png");
	// ½º±²Ò°¼Ş
	LoadDivGraph("image/number16pix.png", 11, 11, 1, 16, 16, numImage, false);
	LoadDivGraph("image/font16pix.png", 27, 27, 1, 16, 16, charImage, false);
	// BGM
	mainBgm = LoadSoundMem("bgm/main_bgm.mp3");
	endBgm = LoadSoundMem("bgm/end_bgm.mp3");

	return true;
}

/* -------ƒQ[ƒ€ƒ‹[ƒv“à‚Ì‰Šú‰»------- */
void GameInit(void)
{
	// Ìª°ÄŞ¶³İÄ
	fadeCnt = 0;
	// ½º±
	score = 0;

	// ÌßÚ²Ô°•Ï”‰Šú‰»
	PlayerGameInit();
	//Player2GameInit();
	// ¼®¯Ä•Ï”‰Šú‰»
	ShotGameInit();
	// “G•Ï”‰Šú‰»
	EnemyGameInit();
	// “G’e•Ï”‰Šú‰»
	BulletGameInit();
	// ”wŒi•Ï”‰Šú‰»
	StageGameInit();
	// ”š”j•Ï”‰Šú‰»
	BlastGameInit();
}
void testGameInit(void)
{
	PlayerGameInit();
}

// ƒ^ƒCƒgƒ‹‰æ–Êˆ—
void GameTitle(void)
{
	DrawGraph(0, 0, titleBg, true);
	//	DrawString(0, 0, "TITLE", 0xffffff);
	DrawGraph(DEFAULT_SCREEN_SIZE_X/2-100, SCREEN_SIZE_Y/2-100, titleImage, true);

	hitKeyCnt++;
	if (hitKeyCnt / 60 % 2 == 0) {
		DrawString(SCREEN_SIZE_X/2-130,SCREEN_SIZE_Y/2+200, "wƒL[•SPACEƒL[‚ÅsoloƒXƒ^[ƒgI", 0xffffff, true);
		//DrawString(320, 530, "sƒL[•SPACEƒL[‚ÅPvPƒXƒ^[ƒgI", 0xffffff, true);

	}
}

void GameMain(void)
{
	if (trgKey[PAUSE]) {
		pauseFlag = !pauseFlag;
	}
	if (pauseFlag) {
		SetDrawBright(128, 128, 128);
	}
	else {
		// ÌßÚ²Ô°‘€ìŠÖ”
		PlayerControl();
		// ¼®¯Ä‘€ìŠÖ”
		ShotControl();
		// “G‘€ìŠÖ”
		EnemyControl();
		// “G’e‘€ìŠÖ”
		BulletControl();
		// ”wŒi‘€ìŠÖ”
		StageControl();
		// “–‚½‚è”»’èŠÖ”
		HitCheck();
		
	}
	if (pauseFlag) {
		SetDrawBright(255, 255, 255);
		DrawString(360, 292, "‚o‚`‚t‚r‚d", 0xffffff);
	}
	// •`‰æŠÖ”
	GameDraw();
}

void testGameMain(void)
{
	// ÌßÚ²Ô°‘€ìŠÖ”
	testPlayerCtrl();
}

// ƒQ[ƒ€ƒI[ƒo[ˆ—
void GameOver(void)
{
	//	DrawString(0, 0, "GAMEOVER", 0xffffff);

	DrawGraph(180, 50, gOverImage, true);

	hitKeyCnt++;
	if (hitKeyCnt / 30 % 2 == 0) {
		DrawString(300, 450, "ƒXƒy[ƒXƒL[‚ğ‰Ÿ‚µ‚Ä‚ËI", 0xffffff, true);
	}

	// ½º±•`‰æ
	DrawStatus("SCORE", score, 200);
	DrawStatus("HISCORE", hiScore, 300);
}

// •`‰æˆ—
void GameDraw(void)
{
	// ”wŒi•`‰æ
	StageDraw();
	// “G•`‰æ
	EnemyDraw();
	// “G’e•`‰æ
	BulletDraw();
	// ÌßÚ²Ô°•`‰æ
	PlayerDraw();
	// ¼®¯Ä•`‰æ
	ShotDraw();
	// ½º±•`‰æ
	DrawStatusMain("SCORE", score, 50);
	// ”š”j•`‰æ
	BlastDraw();
	//cü
	DrawLine(716, 0, 716, SCREEN_SIZE_Y, 0xffffff);
}
void testGameDraw(void)
{
	//Player2Draw();
}
// “–‚½‚è”»’è
void HitCheck(void)
{
	// ´ÈĞ°‚ÆÌßÚ²Ô°‚Ì’e‚Æ‚Ì“–‚½‚è”»’è
	for (int i = 0; i < SHOT_MAX; i++) {
		//		CHARACTER shotTemp = GetShot(i);
		if (shot[i].visible) {
			if (EnemyHitCheck(shot[i].pos, shot[i].sizeOffset)) {
				shot[i].visible = false;
			}
			if (tesEnemyHitCheck(shot[i].pos, shot[i].sizeOffset)) {
				shot[i].visible = 0;
			}
		}
	}

	// ÌßÚ²Ô°‚Æ´ÈĞ°‚Ì’e‚Æ‚Ì“–‚½‚è”»’è
	for (int i = 0; i < BULLET_MAX; i++) {
		//		CHARACTER eShotTemp = GetShotE(i);
		if (bullet[i].visible) {
			if (PlayerHitCheck(bullet[i].pos, bullet[i].sizeOffset)) {
				bullet[i].visible = false;
			}
		}
	}
	for (int j = 0; j < BULLET_MAX; j++) {
		if (testBullet[j].visible) {
			if (PlayerHitCheck(testBullet[j].pos, testBullet[j].sizeOffset)) {
				testBullet[j].visible = false;
			}
		}
	}
}

// ----- Ìª°ÄŞ±³Äˆ—
bool FadeOutScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255) {
		SetDrawBright(255 - fadeCnt, 255 - fadeCnt, 255 - fadeCnt);
		return true;
	}
	else
	{
		SetDrawBright(0, 0, 0);
		fadeCnt = 0;
		return false;
	}
}

// ----- Ìª°ÄŞ²İˆ—
bool FadeInScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255) {
		SetDrawBright(fadeCnt, fadeCnt, fadeCnt);
		return true;
	}
	else {
		SetDrawBright(255, 255, 255);
		fadeCnt = 0;
		return false;
	}
}

void AddScore(int point)
{
	// ½º±‚Ì‰ÁZ
	score += point;
	// ½º±‚ªÊ²½º±‚æ‚è‘å‚«‚­‚È‚ê‚Î½º±‚ğÊ²½º±‚É‚·‚é
	if (hiScore < score) hiScore = score;
}

// ½º±‚Ì•\¦(¹Ş°Ñµ°ÊŞ°‰æ–Ê)
void DrawStatus(const char* title, int value, int top)
{
	int digit = 0;
	int numTemp = value;

	// •¶š‚Ì•`‰æ
	for (int i = 0; i < strlen(title); i++) {
		DrawGraph((290) + i * 16, top,
			charImage[*(title + i) - 64], true);
	}

	// ’l‚Ì•`‰æ
	while (numTemp > 0) {
		DrawGraph(440 - (digit + 1) * 16 - (10), top + 35,
			numImage[numTemp % 10 + 1], true);
		numTemp /= 10;
		digit++;
	}
}

// ½º±‚Ì•\¦(¹Ş°ÑÒ²İ‰æ–Ê)
void DrawStatusMain(const char* title, int value, int top)
{
	int digit = 0;
	int numTemp = value;

	// •¶š‚Ì•`‰æ
	for (int i = 0; i < strlen(title); i++) {
		DrawGraph((730) + i * 16, top,
			charImage[*(title + i) - 64], true);
	}

	// ’l‚Ì•`‰æ
	while (numTemp > 0) {
		DrawGraph(SCREEN_SIZE_X - (digit + 1) * 16 - (10), top + 35,
			numImage[numTemp % 10 + 1], true);
		numTemp /= 10;
		digit++;
	}
}

bool SaveData(void)
{
	FILE* fp;

	fopen_s(&fp, fileName, "wb");
	if (fp == NULL) {
		return false;
	}
	else {
		fwrite(&fileData, sizeof(fileData), 1, fp);
		fclose(fp);

		return true;
	}
}

bool LoadData(void)
{
	FILE* fp;

	fopen_s(&fp, fileName, "rb");
	if (fp == NULL) {
		return false;
	}
	else {
		fread(&fileData, sizeof(fileData), 1, fp);
		fclose(fp);

		return true;
	}
}
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

#include "testPlayer.h"


typedef enum {
	GMODE_INIT,
	TEST_GMODE_INIT,
	GMODE_TITLE,
	GMODE_GAME,
	TEST_GMODE_GAME,
	GMODE_OVER,
	GMODE_MAX
}GAME_MODE;
GAME_MODE gameMode;



typedef struct {
	int data1;
	int hiscore;
}FILE_DATA;

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
//	StopSoundMem(mainBgm);
	gameMode = GMODE_INIT;
	// ---------- ¹Ş°ÑÙ°Ìß
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	// ‰æ–ÊÁ‹
		KeyCheck();
		switch (gameMode) {	// ƒƒCƒ“ˆ—
		case GMODE_INIT:
			GameInit();
			gameMode = GMODE_TITLE;
			PlaySoundMem(mainBgm, DX_PLAYTYPE_LOOP);
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
			else if (CheckHitKey(KEY_INPUT_W) && CheckHitKey(KEY_INPUT_SPACE)) {
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
//						StopSoundMem(mainBgm);
//						PlaySoundMem(endBgm, DX_PLAYTYPE_BACK);
						fadeOut = false;
						fadeIn = true;
					}
				}
				else if (player.visible == false) fadeOut = true;
			}
			LoadData();
			GameMain();
			break;
		case TEST_GMODE_GAME:
			if (fadeIn) {
				if (!FadeInScreen(5)) fadeIn = false;
			}
			else {
				if (fadeOut) {
					if (!FadeOutScreen(5)) {
						gameMode = GMODE_OVER;
						//						StopSoundMem(mainBgm);
						//						PlaySoundMem(endBgm, DX_PLAYTYPE_BACK);
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
	SetWindowText("Shooting");
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
	testPlayerSystemInit();
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
	titleImage = LoadGraph("image/title2.png");
	titleBg = LoadGraph("image/stars.png");
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
	DrawGraph(0, 0, titleImage, true);

	hitKeyCnt++;
	if (hitKeyCnt / 60 % 2 == 0) {
		DrawString(320, 500, "wƒL[•SPACEƒL[‚ÅsoloƒXƒ^[ƒgI", 0xffffff, true);
		DrawString(320, 530, "sƒL[•SPACEƒL[‚ÅPvPƒXƒ^[ƒgI", 0xffffff, true);

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


	//	DrawString(0, 0, "MAIN", 0xffffff);
	// ¹Ş°Ñ¶³İÀ°•\¦
	//	DrawFormatString(0, 20, 0xffffff, "GameMain %d", gameCounter);
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

	DrawLine(716, 0, 716, SCREEN_SIZE_Y, 0xffffff);
}
void testGameDraw(void)
{
	testPlayerDraw();
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
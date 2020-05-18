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


LONGLONG timecnt;

// ----- 変数定義
int gameCounter;

// ﾃﾞｰﾀ読み込み
char fileName[] = "data.dat";
FILE_DATA fileData;

// ﾀｲﾄﾙ画像
int titleImage;
int titleBg;

// ｹﾞｰﾑｵｰﾊﾞｰ画像
int gOverImage;

// ﾌｪｰﾄﾞ
int fadeCnt;
bool fadeIn;
bool fadeOut;

// 一時停止のﾌﾗｸﾞ(true:停止)
bool pauseFlag;
// 文字点滅ｶｳﾝﾄ
int hitKeyCnt;

// BGM
int mainBgm;
int endBgm;

// ｽｺｱ
int score;
int hiScore;
int numImage[11];
int charImage[27];

char Key[256];

int testt=1;

int cnt = 0, test = 1;
int startTime;		// スタート時刻を記憶しておく
unsigned int color = GetColor(0, 0, 255);	// カラーデータの格納
bool flg = false;

// ----- ﾌﾟﾛﾄﾀｲﾌﾟ宣言
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


// ========== WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ｼｽﾃﾑの初期化
	if (SystemInit() == false){
		DxLib_End();
		return 0;
	}
//	StopSoundMem(mainBgm);
	gameMode = GMODE_INIT;

	// 現在経過時間を得る
	startTime = GetNowCount();
	// ---------- ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && GetNowCount() - startTime &&CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	// 画面消去
		KeyCheck();

		// 現在の経過時間を表示
		if (true) {
			ClearDrawScreen();
			DrawFormatString(250, 240, color, " %d秒%d \n",
				(GetNowCount() - startTime) / 1000,
				GetNowCount() - startTime);

		}
		if (GetNowCount() - startTime <= 1000) {
			// 画面に表示
			ClearDrawScreen();
			test++;
			flg = true;
		}

		switch (gameMode) {	// メイン処理
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
			//else if (oldKey[P1_UP]&&trgKey[SPACE]) fadeOut = true;//W押しながらSPACEを押す
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
		ScreenFlip();		// 裏画面を表画面に瞬間コピー
	}

	DxLib_End();			// DXライブラリの終了処理
	return 0;				// このプログラムの終了
}

/* -------システムの初期化------- */
bool SystemInit(void)
{
	// ----- ｼｽﾃﾑ処理
	SetWindowText("Shooting");
	// ｼｽﾃﾑ処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) {
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	KeyCheckSystemInit();

	/* ---------- グラフィックの登録 ---------- */
	// ﾌﾟﾚｲﾔｰ画像
	PlayerSystemInit();
	testPlayerSystemInit();
	// ｼｮｯﾄ画像
	ShotSystemInit();
	// 敵画像
	EnemySystemInit();
	// 敵弾画像
	BulletSystemInit();
	// 背景画像
	StageSystemInit();
	// 爆破画像
	BlastSystemInit();
	// ﾀｲﾄﾙｲﾒｰｼﾞ
	titleImage = LoadGraph("image/title2.png");
	titleBg = LoadGraph("image/stars.png");
	// ｹﾞｰﾑｵｰﾊﾞｰｲﾒｰｼﾞ
	gOverImage = LoadGraph("image/gameover.png");
	// ｽｺｱｲﾒｰｼﾞ
	LoadDivGraph("image/number16pix.png", 11, 11, 1, 16, 16, numImage, false);
	LoadDivGraph("image/font16pix.png", 27, 27, 1, 16, 16, charImage, false);
	// BGM
	mainBgm = LoadSoundMem("bgm/main_bgm.mp3");
	endBgm = LoadSoundMem("bgm/end_bgm.mp3");

	return true;
}

/* -------ゲームループ内の初期化------- */
void GameInit(void)
{
	// ﾌｪｰﾄﾞｶｳﾝﾄ
	fadeCnt = 0;
	// ｽｺｱ
	score = 0;

	// ﾌﾟﾚｲﾔｰ変数初期化
	PlayerGameInit();
	// ｼｮｯﾄ変数初期化
	ShotGameInit();
	// 敵変数初期化
	EnemyGameInit();
	// 敵弾変数初期化
	BulletGameInit();
	// 背景変数初期化
	StageGameInit();
	// 爆破変数初期化
	BlastGameInit();
}
void testGameInit(void)
{
	PlayerGameInit();
}

// タイトル画面処理
void GameTitle(void)
{
	DrawGraph(0, 0, titleBg, true);
	//	DrawString(0, 0, "TITLE", 0xffffff);
	DrawGraph(0, 0, titleImage, true);

	hitKeyCnt++;
	if (hitKeyCnt / 60 % 2 == 0) {
		DrawString(320, 500, "wキー＆SPACEキーでsoloスタート！", 0xffffff, true);
		DrawString(320, 530, "sキー＆SPACEキーでPvPスタート！", 0xffffff, true);

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
		// ﾌﾟﾚｲﾔｰ操作関数
		PlayerControl();
		// ｼｮｯﾄ操作関数
		ShotControl();
		// 敵操作関数
		EnemyControl();
		// 敵弾操作関数
		BulletControl();
		// 背景操作関数
		StageControl();
		// 当たり判定関数
		HitCheck();

	}

	if (pauseFlag) {
		SetDrawBright(255, 255, 255);
		DrawString(360, 292, "ＰＡＵＳＥ", 0xffffff);
	}

	// 描画関数
	GameDraw();


	//	DrawString(0, 0, "MAIN", 0xffffff);
	// ｹﾞｰﾑｶｳﾝﾀｰ表示
	//	DrawFormatString(0, 20, 0xffffff, "GameMain %d", gameCounter);
}
void testGameMain(void)
{
	// ﾌﾟﾚｲﾔｰ操作関数
	testPlayerCtrl();
}

// ゲームオーバー処理
void GameOver(void)
{
	//	DrawString(0, 0, "GAMEOVER", 0xffffff);

	DrawGraph(180, 50, gOverImage, true);

	hitKeyCnt++;
	if (hitKeyCnt / 30 % 2 == 0) {
		DrawString(300, 450, "スペースキーを押してね！", 0xffffff, true);
	}

	// ｽｺｱ描画
	DrawStatus("SCORE", score, 200);
	DrawStatus("HISCORE", hiScore, 300);
}

// 描画処理
void GameDraw(void)
{
	// 背景描画
	StageDraw();
	// 敵描画
	EnemyDraw();
	// 敵弾描画
	BulletDraw();
	// ﾌﾟﾚｲﾔｰ描画
	PlayerDraw();
	// ｼｮｯﾄ描画
	ShotDraw();
	// ｽｺｱ描画
	DrawStatusMain("SCORE", score, 50);
	// 爆破描画
	BlastDraw();

	DrawLine(716, 0, 716, SCREEN_SIZE_Y, 0xffffff);
}
void testGameDraw(void)
{
	testPlayerDraw();
}
// 当たり判定
void HitCheck(void)
{
	// ｴﾈﾐｰとﾌﾟﾚｲﾔｰの弾との当たり判定
	for (int i = 0; i < SHOT_MAX; i++) {
		//		CHARACTER shotTemp = GetShot(i);
		if (shot[i].visible) {
			if (EnemyHitCheck(shot[i].pos, shot[i].sizeOffset)) {
				shot[i].visible = false;
			}
		}
	}

	// ﾌﾟﾚｲﾔｰとｴﾈﾐｰの弾との当たり判定
	for (int i = 0; i < BULLET_MAX; i++) {
		//		CHARACTER eShotTemp = GetShotE(i);
		if (bullet[i].visible) {
			if (PlayerHitCheck(bullet[i].pos, bullet[i].sizeOffset)) {
				bullet[i].visible = false;
			}
		}
	}
}

// ----- ﾌｪｰﾄﾞｱｳﾄ処理
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

// ----- ﾌｪｰﾄﾞｲﾝ処理
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
	// ｽｺｱの加算
	score += point;
	// ｽｺｱがﾊｲｽｺｱより大きくなればｽｺｱをﾊｲｽｺｱにする
	if (hiScore < score) hiScore = score;
}

// ｽｺｱの表示(ｹﾞｰﾑｵｰﾊﾞｰ画面)
void DrawStatus(const char* title, int value, int top)
{
	int digit = 0;
	int numTemp = value;

	// 文字の描画
	for (int i = 0; i < strlen(title); i++) {
		DrawGraph((290) + i * 16, top,
			charImage[*(title + i) - 64], true);
	}

	// 値の描画
	while (numTemp > 0) {
		DrawGraph(440 - (digit + 1) * 16 - (10), top + 35,
			numImage[numTemp % 10 + 1], true);
		numTemp /= 10;
		digit++;
	}
}

// ｽｺｱの表示(ｹﾞｰﾑﾒｲﾝ画面)
void DrawStatusMain(const char* title, int value, int top)
{
	int digit = 0;
	int numTemp = value;

	// 文字の描画
	for (int i = 0; i < strlen(title); i++) {
		DrawGraph((730) + i * 16, top,
			charImage[*(title + i) - 64], true);
	}

	// 値の描画
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
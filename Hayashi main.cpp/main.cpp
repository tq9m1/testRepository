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
unsigned int color = GetColor(0, 255, 255);	// カラーデータの格納
bool flg = false;

int teki = GetRand(100);
int teki2 = GetRand(100);
bool IsHit(const Position2& posA, float radiusA, const Position2& posB, float radiusB) {
	return(hypot(posA.x - posB.x, posA.y - posB.y) < radiusA + radiusB);
}

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
		Position2 pos;//座標
		Vector2 vel;//速度
		bool isActive = false;//生きてるか〜？
	};
	Bullet bullets[100];
	Position2 enemypos(100, -25);
	Position2 playerpos(358, 500);//自機座標
	unsigned int frame = 0;
	//弾の半径
	float bulletRadius = 5.0f;
	//プレイヤーの半径
	float playerRadius = 10.0f;
	
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
			DrawFormatString(0, 10, color, " %d秒\n",
				(GetNowCount() - startTime) / 1000,
				GetNowCount() - startTime);
		}
		if (GetNowCount() - startTime <= 1000) {
			// 画面に表示
			ClearDrawScreen();
			test++;
			flg = true;
		}

		float angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
		int eidx = (frame / 4 % 2);
		/*switch (tekiMode)//敵処理
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

		switch (gameMode) {	// メイン処理
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
			//else if (oldKey[P1_UP]&&trgKey[SPACE]) fadeOut = true;//W押しながらSPACEを押す
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
			/*if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {//敵の弾 当たり判定
				b.isActive = false;
			}*/
			if (isDebugMode) {
				//弾の本体(当たり判定)
				DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
			}
			//弾を殺す
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
		ScreenFlip();		// 裏画面を表画面に瞬間コピー
	}
	DxLib_End();			// DXライブラリの終了処理
	return 0;				// このプログラムの終了
}

/* -------システムの初期化------- */
bool SystemInit(void)
{
	// ----- ｼｽﾃﾑ処理
	SetWindowText("KaRi.exe");
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
	//Player2SystemInit();
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
	titleImage = LoadGraph("image/K a R i.png");
	titleBg = LoadGraph("image/haikei.png");
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
	//Player2GameInit();
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
	DrawGraph(DEFAULT_SCREEN_SIZE_X/2-100, SCREEN_SIZE_Y/2-100, titleImage, true);

	hitKeyCnt++;
	if (hitKeyCnt / 60 % 2 == 0) {
		DrawString(SCREEN_SIZE_X/2-130,SCREEN_SIZE_Y/2+200, "wキー＆SPACEキーでsoloスタート！", 0xffffff, true);
		//DrawString(320, 530, "sキー＆SPACEキーでPvPスタート！", 0xffffff, true);

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
	//縦線
	DrawLine(716, 0, 716, SCREEN_SIZE_Y, 0xffffff);
}
void testGameDraw(void)
{
	//Player2Draw();
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
			if (tesEnemyHitCheck(shot[i].pos, shot[i].sizeOffset)) {
				shot[i].visible = 0;
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
	for (int j = 0; j < BULLET_MAX; j++) {
		if (testBullet[j].visible) {
			if (PlayerHitCheck(testBullet[j].pos, testBullet[j].sizeOffset)) {
				testBullet[j].visible = false;
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
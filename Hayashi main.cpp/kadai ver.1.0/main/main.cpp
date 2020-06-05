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

//typedef enum {
//	TEKI_INIT,
//	TAMA_MAIN,
//	TAMA_1,
//	TAMA_2,
//	TAMA_3,
//	TAMA_4,
//	TAMA_5,
//	TEKI_OWARI,
//	TEKI_MAX
//}TEKI_MODE;
//TEKI_MODE tekiMode;

typedef enum {
	GMODE_INIT,
	TEST_GMODE_INIT,
	GMODE_TITLE,
	GMODE_GAME,
	/*TAMA_1,
	TAMA_2,
	TAMA_3,
	TAMA_4,
	TAMA_5,
	TEKI_OWARI,*/
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

// ----- ïœêîíËã`
int gameCounter;

// √ﬁ∞¿ì«Ç›çûÇ›
char fileName[] = "data.dat";
FILE_DATA fileData;

// ¿≤ƒŸâÊëú
int titleImage;
int titleBg;

// πﬁ∞—µ∞ ﬁ∞âÊëú
int gOverImage;

// Ã™∞ƒﬁ
int fadeCnt;
bool fadeIn;
bool fadeOut;

// àÍéûí‚é~ÇÃÃ◊∏ﬁ(true:í‚é~)
bool pauseFlag;
// ï∂éöì_ñ≈∂≥›ƒ
int hitKeyCnt;

// BGM
int mainBgm;
int endBgm;

// Ω∫±
int score;
int hiScore;
int numImage[11];
int charImage[27];
int scoreImage;
int hiScoreImage;

char Key[256];

int testt=1;

int cnt = 0, test = 1;
int startTime;		// ÉXÉ^Å[ÉgéûçèÇãLâØÇµÇƒÇ®Ç≠
unsigned int color = GetColor(0, 255, 255);	// ÉJÉâÅ[ÉfÅ[É^ÇÃäiî[
bool flg = false;

int teki = GetRand(100);
int teki2 = GetRand(100);
bool IsHit(const Position2& posA, float radiusA, XY_F& posB, float radiusB) {
	return(hypot(posA.x - posB.x, posA.y - posB.y) < radiusA + radiusB);
}


// ----- Ãﬂ€ƒ¿≤ÃﬂêÈåæ
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


// ========== WinMainä÷êî
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ºΩ√—ÇÃèâä˙âª
	if (SystemInit() == false){
		DxLib_End();
		return 0;
	}
	gameMode = GMODE_INIT;

	auto bulletH = LoadGraph("image/tama5.png");
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
	
	int tekihyouji = enemyH[2];
	bool isDebugMode = 0;
	struct Bullet {
		Position2 pos;//ç¿ïW
		Vector2 vel;//ë¨ìx
		bool isActive = false;//ê∂Ç´ÇƒÇÈÇ©Å`ÅH
		float& Left();
		float& Top();
	};
	Bullet bullets[100];
	Position2 enemypos(100, -25);
	Position2 playerpos(358, 500);//é©ã@ç¿ïW
	unsigned int frame = 0;
	//íeÇÃîºåa
	float bulletRadius = 5.0f;
	//ÉvÉåÉCÉÑÅ[ÇÃîºåa
	//float playerRadius = 10.0f;
	//ìGÇÃîºåa
	float enemyRadius = 15.0f;
	// åªç›åoâﬂéûä‘ÇìæÇÈ
	startTime = GetNowCount();
	// ---------- πﬁ∞—Ÿ∞Ãﬂ
	while (ProcessMessage() == 0 && GetNowCount() - startTime &&CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	// âÊñ è¡ãé
		KeyCheck();

		// åªç›ÇÃåoâﬂéûä‘Çï\é¶
		if (true) {
			ClearDrawScreen();
			DrawFormatString(0, 10, color, " %dïb\n",
				(GetNowCount() - startTime) / 1000,
				GetNowCount() - startTime);
		}
		if (GetNowCount() - startTime <= 1000) {
			// âÊñ Ç…ï\é¶
			ClearDrawScreen();
			test++;
			flg = true;
		}

		float angle = atan2(player.pos.y - enemypos.y, player.pos.x - enemypos.x);
		int eidx = (frame / 4 % 2);
		
		switch (gameMode) {	// ÉÅÉCÉìèàóù
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
			//else if (oldKey[P1_UP]&&trgKey[SPACE]) fadeOut = true;//WâüÇµÇ»Ç™ÇÁSPACEÇâüÇ∑
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
		
			
			/*if (teki >= 0 && teki <= 19){
				tekihyouji;
				gameMode = TAMA_1;
			}
			else if (teki >= 20 && teki <= 39) {
				tekihyouji;
				gameMode = TAMA_2;
			}
			else if (teki >= 40 && teki <= 59) {
				tekihyouji;
				gameMode = TAMA_3;
			}
			else if (teki >= 60 && teki <= 79) {
				tekihyouji;
				gameMode = TAMA_4;
			}
			else if (teki >= 80 && teki <= 100) {
				tekihyouji;
				gameMode = TAMA_5;
			}
			break;*/
		/*case TAMA_1:*/
			
		//case TAMA_2:
		//	tama = bulletH2;
		//	for (int i = 0; i < 50; i++) {
		//		if (frame % 12 == 0) {
		//			for (auto& b : bullets) {
		//				if (!b.isActive) {
		//					b.pos = enemypos;
		//					if (i == 0) {
		//						angle += 0.5f;
		//					}
		//					else if (i == 1) {
		//						angle = atan2(player.pos.y - enemypos.y, player.pos.x - enemypos.x);
		//					}
		//					else {
		//						angle -= 0.5f;
		//					}
		//					b.vel = Vector2(cos(angle), sin(angle)).Normalized() * 1;//DX_PI
		//					b.isActive = true;
		//					if (enemypos.y >= 600) gameMode = TEKI_OWARI;
		//					break;
		//				}
		//			}
		//		}
		//	}				
		//	break;
		//case TAMA_3:				
		//	tama = bulletH3;
		//	for (int i = 0; i < GetRand(300); i++) {
		//		if (frame % 12 == 0) {
		//			for (auto& b : bullets) {
		//				if (!b.isActive) {
		//					b.pos = enemypos;
		//					if (i == 0) {
		//						angle += 0.2f;
		//					}
		//					else if (i == 1) {
		//						angle = atan2(player.pos.y - enemypos.y, player.pos.x - enemypos.x);
		//					}
		//					else {
		//						angle -= 0.2f;
		//					}
		//					b.vel = Vector2(cos(angle), sin(angle)).Normalized() * (GetRand(10) + 1);//DX_PI
		//					b.isActive = true;
		//					if (enemypos.y >= 600) gameMode = TEKI_OWARI;
		//					break;
		//				}
		//			}
		//		}
		//	}
		//	break;
		//case TAMA_4:				
		//	tama = bulletH4;
		//	for (int i = 0; i < 7; i++) {
		//		if (frame % 12 == 0) {
		//			for (auto& b : bullets) {
		//				if (!b.isActive) {
		//					b.pos = enemypos;
		//					if (i == 0) {
		//						angle += 0.2f;
		//					}
		//					else if (i == 1) {
		//						angle = atan2(player.pos.y - enemypos.y, player.pos.x - enemypos.x);
		//					}
		//					else {
		//						angle -= 0.2f;
		//					}
		//					b.vel = Vector2(cos(angle), sin(angle)).Normalized() * 1;//DX_PI
		//					b.isActive = true;
		//					if (enemypos.y >= 600) gameMode = TEKI_OWARI;
		//					break;
		//				}
		//			}
		//		}
		//	}
		//	break;
		//case TAMA_5:			
		//	tama = bulletH5;
		//	for (int i = 0; i < GetRand(30); i++) {
		//		if (frame % 12 == 0) {
		//			for (auto& b : bullets) {
		//				if (!b.isActive) {
		//					b.pos = enemypos;
		//					if (i == 0) {
		//						angle += 0.2f;
		//					}
		//					else if (i == 1) {
		//						angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
		//					}
		//					else {
		//						angle -= 0.2f;
		//					}
		//					b.vel = Vector2(cos(angle), sin(angle)).Normalized() * 3;//DX_PI
		//					b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI
		//					b.isActive = true;
		//					if (enemypos.y >= 600) gameMode = TEKI_OWARI;
		//					break;
		//					
		//				}
		//			}
		//		}
		//	}
		//	break;
		/*case TEKI_OWARI:
			enemypos.y = -60;
			teki2 = GetRand(100);
			teki = teki2;*/
			enemypos.x = abs((int)((frame + 320) % 1280) - 640);
			enemypos.y = enemypos.y + 2.3f;
			DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx], true);
			++frame;
			LoadData();
			GameMain();
			if (tekihyouji) {
				tama = bulletH;
				for (int i = 0; i < 3; i++) {
					if (frame % 32 == 0) {
						for (auto& b : bullets) {
							if (!b.isActive) {
								b.pos = enemypos;
								if (i == 0) {
									angle += 1.0f;
								}
								else if (i == 1) {
									angle = atan2(player.pos.y - enemypos.y, player.pos.x - enemypos.x);
								}
								else {
									angle -= 1.0f;
								}
								b.vel = Vector2(cos(angle), sin(angle)).Normalized() * 1;//DX_PI
								b.isActive = true;
								if (enemypos.y >= 600) 
									enemypos.y = -60;
								teki2 = GetRand(100);
								teki = teki2;
								break;
							}
							continue;
						}
					}
				}
			}			
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
			for (auto& b : bullets) {
				if (!b.isActive) {
					continue;
				}
				b.isActive = 0;
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
			//if (IsHit(b.pos, bulletRadius, player.pos, player.radius)) {//ìGÇÃíeÇ∆player ìñÇΩÇËîªíË
			//	b.isActive = false;
			//	player.damageFlag = 1;
			//	if (player.damageFlag == 1) {
			//		player.visible = 0;
			//	}
			//}
			for (int i = 0; i < SHOT_MAX; i++) {
				if (IsHit(b.pos, bulletRadius, shot[i].pos, shot[i].radius)) {
					b.isActive = 0;
					shot[i].visible = 0;
				}
			}
			if (isDebugMode) {
				//íeÇÃñ{ëÃ(ìñÇΩÇËîªíË)
				DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
			}
		
			if (IsHit(enemypos, enemyRadius, player.pos, player.radius)) {
				//ìñÇΩÇ¡ÇΩîΩâûÇèëÇ¢ÇƒÇ≠ÇæÇ≥Ç¢ÅB
				tekihyouji = 1;
				player.damageFlag = 1;
				if (player.damageFlag == 1) {
					player.visible = 0;
				}
			}
			if (isDebugMode) {
				//ìGÇÃñ{ëÃ(ìñÇΩÇËîªíË)
				DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
			}
		
		}

		gameCounter++;		
		ScreenFlip();		// ó†âÊñ Çï\âÊñ Ç…èuä‘ÉRÉsÅ[
	}
	DxLib_End();			// DXÉâÉCÉuÉâÉäÇÃèIóπèàóù
	return 0;				// Ç±ÇÃÉvÉçÉOÉâÉÄÇÃèIóπ
}

/* -------ÉVÉXÉeÉÄÇÃèâä˙âª------- */
bool SystemInit(void)
{
	// ----- ºΩ√—èàóù
	SetWindowText("KaRi.exe");
	// ºΩ√—èàóù
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) {
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	KeyCheckSystemInit();

	/* ---------- ÉOÉâÉtÉBÉbÉNÇÃìoò^ ---------- */
	// Ãﬂ⁄≤‘∞âÊëú
	PlayerSystemInit();
	//Player2SystemInit();
	// ºÆØƒâÊëú
	ShotSystemInit();
	// ìGâÊëú
	EnemySystemInit();
	// ìGíeâÊëú
	BulletSystemInit();
	// îwåiâÊëú
	StageSystemInit();
	// îöîjâÊëú
	BlastSystemInit();
	// ¿≤ƒŸ≤“∞ºﬁ
	titleImage = LoadGraph("image/K a R i.png");
	titleBg = LoadGraph("image/haikei.png");
	// πﬁ∞—µ∞ ﬁ∞≤“∞ºﬁ
	gOverImage = LoadGraph("image/Game Over2.png");
	// Ω∫±≤“∞ºﬁ
	scoreImage = LoadGraph("image/score.png");
	LoadDivGraph("image/number16pix.png", 11, 11, 1, 16, 16, numImage, false);
	hiScoreImage = LoadGraph("image/hiscore.png");
	// BGM
	mainBgm = LoadSoundMem("bgm/main_bgm.mp3");
	endBgm = LoadSoundMem("bgm/end_bgm.mp3");

	return true;
}

/* -------ÉQÅ[ÉÄÉãÅ[Évì‡ÇÃèâä˙âª------- */
void GameInit(void)
{
	// Ã™∞ƒﬁ∂≥›ƒ
	fadeCnt = 0;
	// Ω∫±
	score = 0;

	// Ãﬂ⁄≤‘∞ïœêîèâä˙âª
	PlayerGameInit();
	//Player2GameInit();
	// ºÆØƒïœêîèâä˙âª
	ShotGameInit();
	// ìGïœêîèâä˙âª
	EnemyGameInit();
	// ìGíeïœêîèâä˙âª
	BulletGameInit();
	// îwåiïœêîèâä˙âª
	StageGameInit();
	// îöîjïœêîèâä˙âª
	BlastGameInit();
}
void testGameInit(void)
{
	PlayerGameInit();
}

// É^ÉCÉgÉãâÊñ èàóù
void GameTitle(void)
{
	DrawGraph(0, 0, titleBg, true);
	//	DrawString(0, 0, "TITLE", 0xffffff);
	DrawGraph(DEFAULT_SCREEN_SIZE_X/2-100, SCREEN_SIZE_Y/2-100, titleImage, true);

	hitKeyCnt++;
	if (hitKeyCnt / 60 % 2 == 0) {
		DrawString(SCREEN_SIZE_X/2-130,SCREEN_SIZE_Y/2+200, "wÉLÅ[ÅïSPACEÉLÅ[Ç≈soloÉXÉ^Å[ÉgÅI", 0xffffff, true);
		//DrawString(320, 530, "sÉLÅ[ÅïSPACEÉLÅ[Ç≈PvPÉXÉ^Å[ÉgÅI", 0xffffff, true);

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
		// Ãﬂ⁄≤‘∞ëÄçÏä÷êî
		PlayerControl();
		// ºÆØƒëÄçÏä÷êî
		ShotControl();
		// ìGëÄçÏä÷êî
		EnemyControl();
		// ìGíeëÄçÏä÷êî
		BulletControl();
		// îwåiëÄçÏä÷êî
		StageControl();
		// ìñÇΩÇËîªíËä÷êî
		HitCheck();
		
	}
	if (pauseFlag) {
		SetDrawBright(255, 255, 255);
		DrawString(360, 292, "ÇoÇ`ÇtÇrÇd", 0xffffff);
	}
	// ï`âÊä÷êî
	GameDraw();
}

void testGameMain(void)
{
	// Ãﬂ⁄≤‘∞ëÄçÏä÷êî
	testPlayerCtrl();
}

// ÉQÅ[ÉÄÉIÅ[ÉoÅ[èàóù
void GameOver(void)
{
	//	DrawString(0, 0, "GAMEOVER", 0xffffff);

	DrawGraph(180, 100, gOverImage, true);

	hitKeyCnt++;
	if (hitKeyCnt / 30 % 2 == 0) {
		DrawString(350, 530, "ÉXÉyÅ[ÉXÉLÅ[ÇâüÇµÇƒÇÀÅI", 0xffffff, true);
	}

	// Ω∫±ï`âÊ
	DrawStatus("SCORE", score, 200);
	DrawStatus("HISCORE", hiScore, 300);
	DrawGraph(200, 220, scoreImage, 1);
	DrawGraph(180, 320, hiScoreImage, 1);
}

// ï`âÊèàóù
void GameDraw(void)
{
	// îwåiï`âÊ
	StageDraw();
	// ìGï`âÊ
	EnemyDraw();
	// ìGíeï`âÊ
	BulletDraw();
	// Ãﬂ⁄≤‘∞ï`âÊ
	PlayerDraw();
	// ºÆØƒï`âÊ
	ShotDraw();
	// Ω∫±ï`âÊ
	DrawGraph(720, 50, scoreImage, 1);
	// îöîjï`âÊ
	BlastDraw();
	//ècê¸
	DrawLine(716, 0, 716, SCREEN_SIZE_Y, 0xffffff);
}
void testGameDraw(void)
{
	//Player2Draw();
}
// ìñÇΩÇËîªíË
void HitCheck(void)
{
	// ¥»–∞Ç∆Ãﬂ⁄≤‘∞ÇÃíeÇ∆ÇÃìñÇΩÇËîªíË
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

	// Ãﬂ⁄≤‘∞Ç∆¥»–∞ÇÃíeÇ∆ÇÃìñÇΩÇËîªíË
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

// ----- Ã™∞ƒﬁ±≥ƒèàóù
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

// ----- Ã™∞ƒﬁ≤›èàóù
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
	// Ω∫±ÇÃâ¡éZ
	score += point;
	// Ω∫±Ç™ ≤Ω∫±ÇÊÇËëÂÇ´Ç≠Ç»ÇÍÇŒΩ∫±Ç ≤Ω∫±Ç…Ç∑ÇÈ
	if (hiScore < score) hiScore = score;
}

// Ω∫±ÇÃï\é¶(πﬁ∞—µ∞ ﬁ∞âÊñ )
void DrawStatus(const char* title, int value, int top)
{
	int digit = 0;
	int numTemp = value;

	// ï∂éöÇÃï`âÊ
	for (int i = 0; i < strlen(title); i++) {
		DrawGraph((290) + i * 16, top,
			charImage[*(title + i) - 64], true);
	}

	// ílÇÃï`âÊ
	while (numTemp > 0) {
		DrawGraph(440 - (digit + 1) * 16 - (10), top + 35,
			numImage[numTemp % 10 + 1], true);
		numTemp /= 10;
		digit++;
	}
}

// Ω∫±ÇÃï\é¶(πﬁ∞—“≤›âÊñ )
void DrawStatusMain(const char* title, int value, int top)
{
	int digit = 0;
	int numTemp = value;

	// ï∂éöÇÃï`âÊ
	for (int i = 0; i < strlen(title); i++) {
		DrawGraph((730) + i * 16, top,
			charImage[*(title + i) - 64], true);
	}

	// ílÇÃï`âÊ
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

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

// ----- �ϐ���`
int gameCounter;

// �ް��ǂݍ���
char fileName[] = "data.dat";
FILE_DATA fileData;

// ���ى摜
int titleImage;
int titleBg;

// �ްѵ��ް�摜
int gOverImage;

// ̪���
int fadeCnt;
bool fadeIn;
bool fadeOut;

// �ꎞ��~���׸�(true:��~)
bool pauseFlag;
// �����_�Ŷ���
int hitKeyCnt;

// BGM
int mainBgm;
int endBgm;

// ���
int score;
int hiScore;
int numImage[11];
int charImage[27];
int scoreImage;
int hiScoreImage;

char Key[256];

int testt=1;

int cnt = 0, test = 1;
int startTime;		// �X�^�[�g�������L�����Ă���
unsigned int color = GetColor(0, 255, 255);	// �J���[�f�[�^�̊i�[
bool flg = false;

int teki = GetRand(100);
int teki2 = GetRand(100);
bool IsHit(const Position2& posA, float radiusA, XY_F& posB, float radiusB) {
	return(hypot(posA.x - posB.x, posA.y - posB.y) < radiusA + radiusB);
}


// ----- �������ߐ錾
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


// ========== WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ���т̏�����
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
		Position2 pos;//���W
		Vector2 vel;//���x
		bool isActive = false;//�����Ă邩�`�H
		float& Left();
		float& Top();
	};
	Bullet bullets[100];
	Position2 enemypos(100, -25);
	Position2 playerpos(358, 500);//���@���W
	unsigned int frame = 0;
	//�e�̔��a
	float bulletRadius = 5.0f;
	//�v���C���[�̔��a
	//float playerRadius = 10.0f;
	//�G�̔��a
	float enemyRadius = 15.0f;
	// ���݌o�ߎ��Ԃ𓾂�
	startTime = GetNowCount();
	// ---------- �ް�ٰ��
	while (ProcessMessage() == 0 && GetNowCount() - startTime &&CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	// ��ʏ���
		KeyCheck();

		// ���݂̌o�ߎ��Ԃ�\��
		if (true) {
			ClearDrawScreen();
			DrawFormatString(0, 10, color, " %d�b\n",
				(GetNowCount() - startTime) / 1000,
				GetNowCount() - startTime);
		}
		if (GetNowCount() - startTime <= 1000) {
			// ��ʂɕ\��
			ClearDrawScreen();
			test++;
			flg = true;
		}

		float angle = atan2(player.pos.y - enemypos.y, player.pos.x - enemypos.x);
		int eidx = (frame / 4 % 2);
		
		switch (gameMode) {	// ���C������
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
			//else if (oldKey[P1_UP]&&trgKey[SPACE]) fadeOut = true;//W�����Ȃ���SPACE������
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
			//if (IsHit(b.pos, bulletRadius, player.pos, player.radius)) {//�G�̒e��player �����蔻��
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
				//�e�̖{��(�����蔻��)
				DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
			}
		
			if (IsHit(enemypos, enemyRadius, player.pos, player.radius)) {
				//�������������������Ă��������B
				tekihyouji = 1;
				player.damageFlag = 1;
				if (player.damageFlag == 1) {
					player.visible = 0;
				}
			}
			if (isDebugMode) {
				//�G�̖{��(�����蔻��)
				DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
			}
		
		}

		gameCounter++;		
		ScreenFlip();		// ����ʂ�\��ʂɏu�ԃR�s�[
	}
	DxLib_End();			// DX���C�u�����̏I������
	return 0;				// ���̃v���O�����̏I��
}

/* -------�V�X�e���̏�����------- */
bool SystemInit(void)
{
	// ----- ���я���
	SetWindowText("KaRi.exe");
	// ���я���
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) {
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	KeyCheckSystemInit();

	/* ---------- �O���t�B�b�N�̓o�^ ---------- */
	// ��ڲ԰�摜
	PlayerSystemInit();
	//Player2SystemInit();
	// ���ĉ摜
	ShotSystemInit();
	// �G�摜
	EnemySystemInit();
	// �G�e�摜
	BulletSystemInit();
	// �w�i�摜
	StageSystemInit();
	// ���j�摜
	BlastSystemInit();
	// ���ٲҰ��
	titleImage = LoadGraph("image/K a R i.png");
	titleBg = LoadGraph("image/haikei.png");
	// �ްѵ��ް�Ұ��
	gOverImage = LoadGraph("image/Game Over2.png");
	// ����Ұ��
	scoreImage = LoadGraph("image/score.png");
	LoadDivGraph("image/number16pix.png", 11, 11, 1, 16, 16, numImage, false);
	hiScoreImage = LoadGraph("image/hiscore.png");
	// BGM
	mainBgm = LoadSoundMem("bgm/main_bgm.mp3");
	endBgm = LoadSoundMem("bgm/end_bgm.mp3");

	return true;
}

/* -------�Q�[�����[�v���̏�����------- */
void GameInit(void)
{
	// ̪��޶���
	fadeCnt = 0;
	// ���
	score = 0;

	// ��ڲ԰�ϐ�������
	PlayerGameInit();
	//Player2GameInit();
	// ���ĕϐ�������
	ShotGameInit();
	// �G�ϐ�������
	EnemyGameInit();
	// �G�e�ϐ�������
	BulletGameInit();
	// �w�i�ϐ�������
	StageGameInit();
	// ���j�ϐ�������
	BlastGameInit();
}
void testGameInit(void)
{
	PlayerGameInit();
}

// �^�C�g����ʏ���
void GameTitle(void)
{
	DrawGraph(0, 0, titleBg, true);
	//	DrawString(0, 0, "TITLE", 0xffffff);
	DrawGraph(DEFAULT_SCREEN_SIZE_X/2-100, SCREEN_SIZE_Y/2-100, titleImage, true);

	hitKeyCnt++;
	if (hitKeyCnt / 60 % 2 == 0) {
		DrawString(SCREEN_SIZE_X/2-130,SCREEN_SIZE_Y/2+200, "w�L�[��SPACE�L�[��solo�X�^�[�g�I", 0xffffff, true);
		//DrawString(320, 530, "s�L�[��SPACE�L�[��PvP�X�^�[�g�I", 0xffffff, true);

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
		// ��ڲ԰����֐�
		PlayerControl();
		// ���đ���֐�
		ShotControl();
		// �G����֐�
		EnemyControl();
		// �G�e����֐�
		BulletControl();
		// �w�i����֐�
		StageControl();
		// �����蔻��֐�
		HitCheck();
		
	}
	if (pauseFlag) {
		SetDrawBright(255, 255, 255);
		DrawString(360, 292, "�o�`�t�r�d", 0xffffff);
	}
	// �`��֐�
	GameDraw();
}

void testGameMain(void)
{
	// ��ڲ԰����֐�
	testPlayerCtrl();
}

// �Q�[���I�[�o�[����
void GameOver(void)
{
	//	DrawString(0, 0, "GAMEOVER", 0xffffff);

	DrawGraph(180, 100, gOverImage, true);

	hitKeyCnt++;
	if (hitKeyCnt / 30 % 2 == 0) {
		DrawString(350, 530, "�X�y�[�X�L�[�������ĂˁI", 0xffffff, true);
	}

	// ����`��
	DrawStatus("SCORE", score, 200);
	DrawStatus("HISCORE", hiScore, 300);
	DrawGraph(200, 220, scoreImage, 1);
	DrawGraph(180, 320, hiScoreImage, 1);
}

// �`�揈��
void GameDraw(void)
{
	// �w�i�`��
	StageDraw();
	// �G�`��
	EnemyDraw();
	// �G�e�`��
	BulletDraw();
	// ��ڲ԰�`��
	PlayerDraw();
	// ���ĕ`��
	ShotDraw();
	// ����`��
	DrawGraph(720, 50, scoreImage, 1);
	// ���j�`��
	BlastDraw();
	//�c��
	DrawLine(716, 0, 716, SCREEN_SIZE_Y, 0xffffff);
}
void testGameDraw(void)
{
	//Player2Draw();
}
// �����蔻��
void HitCheck(void)
{
	// ��а����ڲ԰�̒e�Ƃ̓����蔻��
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

	// ��ڲ԰�ƴ�а�̒e�Ƃ̓����蔻��
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

// ----- ̪��ޱ�ď���
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

// ----- ̪��޲ݏ���
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
	// ����̉��Z
	score += point;
	// �����ʲ������傫���Ȃ�ν����ʲ����ɂ���
	if (hiScore < score) hiScore = score;
}

// ����̕\��(�ްѵ��ް���)
void DrawStatus(const char* title, int value, int top)
{
	int digit = 0;
	int numTemp = value;

	// �����̕`��
	for (int i = 0; i < strlen(title); i++) {
		DrawGraph((290) + i * 16, top,
			charImage[*(title + i) - 64], true);
	}

	// �l�̕`��
	while (numTemp > 0) {
		DrawGraph(440 - (digit + 1) * 16 - (10), top + 35,
			numImage[numTemp % 10 + 1], true);
		numTemp /= 10;
		digit++;
	}
}

// ����̕\��(�ް�Ҳ݉��)
void DrawStatusMain(const char* title, int value, int top)
{
	int digit = 0;
	int numTemp = value;

	// �����̕`��
	for (int i = 0; i < strlen(title); i++) {
		DrawGraph((730) + i * 16, top,
			charImage[*(title + i) - 64], true);
	}

	// �l�̕`��
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

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

char Key[256];

int testt=1;

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
//	StopSoundMem(mainBgm);
	gameMode = GMODE_INIT;
	// ---------- �ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	// ��ʏ���
		KeyCheck();
		switch (gameMode) {	// ���C������
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
			//else if (oldKey[P1_UP]&&trgKey[SPACE]) fadeOut = true;//W�����Ȃ���SPACE������
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
		ScreenFlip();		// ����ʂ�\��ʂɏu�ԃR�s�[
	}

	DxLib_End();			// DX���C�u�����̏I������
	return 0;				// ���̃v���O�����̏I��
}

/* -------�V�X�e���̏�����------- */
bool SystemInit(void)
{
	// ----- ���я���
	SetWindowText("Shooting");
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
	testPlayerSystemInit();
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
	titleImage = LoadGraph("image/title2.png");
	titleBg = LoadGraph("image/stars.png");
	// �ްѵ��ް�Ұ��
	gOverImage = LoadGraph("image/gameover.png");
	// ����Ұ��
	LoadDivGraph("image/number16pix.png", 11, 11, 1, 16, 16, numImage, false);
	LoadDivGraph("image/font16pix.png", 27, 27, 1, 16, 16, charImage, false);
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
	DrawGraph(0, 0, titleImage, true);

	hitKeyCnt++;
	if (hitKeyCnt / 60 % 2 == 0) {
		DrawString(320, 500, "w�L�[��SPACE�L�[��solo�X�^�[�g�I", 0xffffff, true);
		DrawString(320, 530, "s�L�[��SPACE�L�[��PvP�X�^�[�g�I", 0xffffff, true);

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


	//	DrawString(0, 0, "MAIN", 0xffffff);
	// �ްѶ�����\��
	//	DrawFormatString(0, 20, 0xffffff, "GameMain %d", gameCounter);
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

	DrawGraph(180, 50, gOverImage, true);

	hitKeyCnt++;
	if (hitKeyCnt / 30 % 2 == 0) {
		DrawString(300, 450, "�X�y�[�X�L�[�������ĂˁI", 0xffffff, true);
	}

	// ����`��
	DrawStatus("SCORE", score, 200);
	DrawStatus("HISCORE", hiScore, 300);
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
	DrawStatusMain("SCORE", score, 50);
	// ���j�`��
	BlastDraw();

	DrawLine(716, 0, 716, SCREEN_SIZE_Y, 0xffffff);
}
void testGameDraw(void)
{
	testPlayerDraw();
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
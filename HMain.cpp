#include"DxLib.h"
#include"HMain.h"
//#include"Haikei.h"

int haikei;
int hosi1;
int hosi2;
int hosi3;

int skyy = 0;
int skyy2 = 0;

int p = 50;
int pos = 0;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	
	//HaikeiInit();

	HSysInit();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();
		//DrawPixel(320, 240, GetColor(255, 255, 255));	// �_��ł�
	}

	if (CheckHitKey(KEY_INPUT_A))
	{
		pos += 10;
	}

	ScreenFlip();

	WaitKey();				// �L�[���͑҂�

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}


bool HSysInit(void)
{
	//���я���
	SetWindowText("haikeitest");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);	// 640�~480�ޯ�65536�FӰ�ސFӰ�ނɐݒ�
	ChangeWindowMode(true);							// true:WindowӰ��, false:�ٽ�ذ�
	if (DxLib_Init() == -1)
	{
		return false;								//DXײ���؏���������
	}
	haikei = LoadGraph("img/utyuu.png");
	hosi1 = LoadGraph("img/hosi1.png");
	hosi2 = LoadGraph("img/hosi2.png");
	hosi3 = LoadGraph("img/hosi3.jpg");

	pos++;
	HaikeiMain();
	
	SetDrawScreen(DX_SCREEN_BACK);
	
	//KeyCheckSysInit();
	SetTransColor(255, 0, 255);
	
	/*HaikeiMain();
	HaikeiDraw();*/
	return true;

}

void HaikeiMain(void)
{
	//DrawString(250, 240, "test", GetColor(0, 255, 100));
	
	
	p =30;
	
	
	
	HaikeiDraw();
}

void HaikeiDraw(void)
{
	DrawGraph(0, 0, haikei, true);
	//DrawGraph(100, 100, hosi1, true);
	//skyy = (skyy + 1) % 480;
	//skyy2 = (skyy2 + 2) % 480;
	
	
	DrawExtendGraph(p+pos, p, p*2+pos, p*2 , hosi1, true);

	DeleteGraph(hosi1);

	/*skyy = (skyy + 1) % 480;
	skyy2 = (skyy2 + 2) % 480;
	DrawExtendGraph(0, skyy, 640, skyy + 480, hosi1, true);
	DrawExtendGraph(0, skyy - 480, 640, skyy, hosi1, true);
	DrawExtendGraph(0, skyy2, 640, skyy2 + 480, hosi2, true);
	DrawExtendGraph(0, skyy2 - 480, 640, skyy2, hosi2, true);*/
	//DrawGraph(200, 200, hosi2, false);
	//DrawGraph(300, 300, hosi3, false);
	//DrawString(260, 230, "test", GetColor(0, 155, 100));
	//DrawPixel(320, 240, GetColor(255, 255, 255));	// �_��ł�
}
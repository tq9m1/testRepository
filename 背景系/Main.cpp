#include"DxLib.h"
#include"Main.h"
#include"Haikei.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	SysInit();
	HaikeiInit();

	Main();
	Draw();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
	
	}

	DrawPixel(320, 240, GetColor(255, 255, 255));	// �_��ł�

	WaitKey();				// �L�[���͑҂�

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}


bool SysInit(void)
{
	//���я���
	SetWindowText("ASO���b�N�}��");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);	// 640�~480�ޯ�65536�FӰ�ސFӰ�ނɐݒ�
	ChangeWindowMode(true);							// true:WindowӰ��, false:�ٽ�ذ�
	if (DxLib_Init() == -1)
	{
		return false;								//DXײ���؏���������
	}
	
	SetDrawScreen(DX_SCREEN_BACK);

	//KeyCheckSysInit();
	SetTransColor(255, 0, 255);
	

	return true;

}

void Main(void)
{
	HaikeiMain();
}

void Draw(void)
{
	HaikeiDraw();
}
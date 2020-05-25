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

	DrawPixel(320, 240, GetColor(255, 255, 255));	// 点を打つ

	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}


bool SysInit(void)
{
	//ｼｽﾃﾑ処理
	SetWindowText("ASOロックマン");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);	// 640×480ﾄﾞｯﾄ65536色ﾓｰﾄﾞ色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);							// true:Windowﾓｰﾄﾞ, false:ﾌﾙｽｸﾘｰﾝ
	if (DxLib_Init() == -1)
	{
		return false;								//DXﾗｲﾌﾞﾗﾘ初期化処理
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
#include"DxLib.h"
#include"Main.h"
#include"Haikei.h"

int hikei;

void HaikeiInit(void)
{
	
	hikei = LoadGraph("img/utyuu.png");
}
void HaikeiMain(void)
{

}
void HaikeiDraw(void)
{
	
	DrawGraph(SCREEN_SIZE_X/2,SCREEN_SIZE_Y/2, hikei,true);
}
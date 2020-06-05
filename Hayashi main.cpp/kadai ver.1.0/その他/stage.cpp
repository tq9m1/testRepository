#include "DxLib.h"
#include "main.h"
#include "stage.h"

// �w�i�摜
int haikeiImage;
CHARACTER stage;

int spaceImage;
CHARACTER space;

// �w�i�摜������
void StageSystemInit(void)
{
	haikeiImage = LoadGraph("image/haikei.jpg");
	spaceImage = LoadGraph("image/nebula10.1.png");
}

// �w�i�̕ϐ�������
void StageGameInit(void)
{
	stage.visible = true;
	stage.pos = { 0,0 };
	stage.size = { 4096, 4096 };
	stage.sizeOffset = { stage.size.x / 2, stage.size.y / 2 };
	stage.moveSpeed = 2;

	space.visible = true;
	space.pos = { 1300, 0 };
	space.size = { 1134, 1576 };
	space.sizeOffset = { space.size.x / 2, space.size.y / 2 };
	space.moveSpeed = 2;
}

// �w�i����
void StageControl(void)
{
	// ���̔w�i��۰ٓ���
	if (stage.visible) {
		stage.pos.y += stage.moveSpeed;
		if (stage.pos.y == 2034) {
			stage.pos.y = 0;
		}
	}

	// �F���̔w�i��۰ٓ���
	if (space.visible) {
		space.pos.y += space.moveSpeed;
		if (space.pos.y == 2034) {
			space.pos.y = 0;
		}
	}
}

// �w�i�`��
void StageDraw(void)
{
	// �ꖇ�ڕ`��(���̔w�i)
	if(stage.visible){
		DrawGraph(stage.pos.x - stage.sizeOffset.x,
			stage.pos.y - stage.sizeOffset.y, haikeiImage, false);
	}
	// �񖇖ڕ`��(���̔w�i)
	if (stage.visible) {
		DrawGraph(stage.pos.x - stage.sizeOffset.x,
			stage.pos.y - stage.sizeOffset.y - 2034, haikeiImage, false);
	}

	/* �ꖇ�ڕ`��(�F���̔w�i)
	if (space.visible) {
		DrawGraph(space.pos.x - space.sizeOffset.x,
			space.pos.y - space.sizeOffset.y, spaceImage, false);
	}
	// �񖇖ڕ`��(�F���̔w�i)
	if (space.visible) {
		DrawGraph(space.pos.x - space.sizeOffset.x,
			space.pos.y - space.sizeOffset.y - 2034, spaceImage, false);
	}*/

//	DrawFormatString(0, 20, 0xffffff, "stagePos = %d %d", space.pos);
}
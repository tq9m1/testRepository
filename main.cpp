#include<DxLib.h>
#include<cmath>
#include"main.h"
//#include"Enemy.h"

///“–‚½‚è”»’èŠÖ”
///@param posA A‚ÌÀ•W
///@param radiusA A‚Ì”¼Œa
///@param posB B‚ÌÀ•W
///@param radiusB B‚Ì”¼Œa
bool IsHit(const Position2& posA, float radiusA, const Position2& posB, float radiusB) {
	//“–‚½‚è”»’è‚ğÀ‘•‚µ‚Ä‚­‚¾‚³‚¢

	return(hypot(posA.x - posB.x, posA.y - posB.y)<radiusA + radiusB);
}
int timecont = 0;

//”wŒi
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetMainWindowText("1816240_¼Z—D‘¾");
	if (DxLib_Init() != 0) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	//”wŒi—p
	int bgH[4];
	LoadDivGraph("img/bganim.png", 4, 4, 1, 1024, 192, bgH);

	int skyH = LoadGraph("img/sky.png");
	int sky2H = LoadGraph("img/sky2.png");
	//int mekakushi= LoadGraph("img/tama.png");
	auto bulletH = LoadGraph("img/tama2.png");
	auto bulletH2 = LoadGraph("img/tama3.png");
	auto bulletH3 = LoadGraph("img/tama4.png");
	auto bulletH4 = LoadGraph("img/tama5.png");
	auto bulletH5 = LoadGraph("img/tama6.png");
	//int bulletyou;
	int playerH[10];
	LoadDivGraph("img/player.png", 10, 5, 2, 16, 24, playerH);

	int enemyH[2];
	int enemyH2[2];
	int enemyH3[2];
	int enemyH4[2];
	int enemyH5[2];
	LoadDivGraph("img/teki1.png", 2, 2, 1, 32, 32, enemyH);
	LoadDivGraph("img/teki2.png", 2, 2, 1, 32, 32, enemyH2);
	LoadDivGraph("img/teki3.png", 2, 2, 1, 32, 32, enemyH3);
	LoadDivGraph("img/teki4.png", 2, 2, 1, 32, 32, enemyH4);
	LoadDivGraph("img/teki5.png", 2, 2, 1, 32, 32, enemyH5);
	//LoadDivGraph("img/enemy.png", 2, 2, 1, 32, 32, enemyH);

	struct Bullet {
		Position2 pos;//À•W
		Vector2 vel;//‘¬“x
		bool isActive = false;//¶‚«‚Ä‚é‚©`H
	};

	int mekakusiposx = 0;
	int mekakusiposy = -100;
	//’e‚Ì”¼Œa
	float bulletRadius = 5.0f;

	//©‹@‚Ì”¼Œa
	float playerRadius = 10.0f;

	//“K“–‚É256ŒÂ‚­‚ç‚¢ì‚Á‚Æ‚­
	Bullet bullets[1000];

	//Position2 enemypos(320, 25);//“GÀ•W
	Position2 enemypos(100, -25);
	Position2 playerpos(320, 400);//©‹@À•W

	unsigned int frame = 0;//ƒtƒŒ[ƒ€ŠÇ——p

	char keystate[256];
	bool isDebugMode = false;
	int skyy = 0;
	int skyy2 = 0;
	int bgidx = 0;


	int spi = 1;
	//	int tomegu = 0;
	int tama = bulletH;
	int teki = 0;  //GetRand(5);
	int teki2 = teki;
	
	while (ProcessMessage() == 0) {
		ClearDrawScreen();

		GetHitKeyStateAll(keystate);

		isDebugMode = keystate[KEY_INPUT_P];

		DrawExtendGraph(0, 0, 640, 480, bgH[bgidx / 8], false);
		bgidx = (bgidx + 1) % 32;

		//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		skyy = (skyy + 1) % 480;
		skyy2 = (skyy2 + 2) % 480;
		DrawExtendGraph(0, skyy, 640, skyy + 480, skyH, true);
		DrawExtendGraph(0, skyy - 480, 640, skyy, skyH, true);
		DrawExtendGraph(0, skyy2, 640, skyy2 + 480, sky2H, true);
		DrawExtendGraph(0, skyy2 - 480, 640, skyy2, sky2H, true);


		//ƒvƒŒƒCƒ„[
		if (keystate[KEY_INPUT_RIGHT]) {
			playerpos.x = min(640, playerpos.x + 4);
		}
		else if (keystate[KEY_INPUT_LEFT]) {
			playerpos.x = max(0, playerpos.x - 4);
		}
		if (keystate[KEY_INPUT_UP]) {
			playerpos.y = max(0, playerpos.y - 4);
		}
		else if (keystate[KEY_INPUT_DOWN]) {
			playerpos.y = min(480, playerpos.y + 4);
		}

		int pidx = (frame / 4 % 2) * 5 + 3;
		DrawRotaGraph(playerpos.x, playerpos.y, 2.0f, 0.0f, playerH[pidx], true);
		if (isDebugMode) {
			//©‹@‚Ì–{‘Ì(“–‚½‚è”»’è)
			DrawCircle(playerpos.x, playerpos.y, playerRadius, 0xffaaaa, false, 3);
		}
		float angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
		//’e”­Ë

		//timecont++;

		if (teki2 = 0) //(timecont < 90 || timecont>340 && timecont>440)    CheckHitKey(KEY_INPUT_A)
		{


			tama = bulletH;
			for (int i = 0; i < 3; i++)
			{


				if (frame % 12 == 0)
				{
					for (auto& b : bullets) {
						if (!b.isActive) {
							b.pos = enemypos;
							if (i == 0)
							{
								angle += 0.2f;
							}
							else if (i == 1)
							{
								angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
							}
							else
							{
								angle -= 0.2f;
							}
							b.vel = Vector2(cos(angle), sin(angle)).Normalized() * 5;//DX_PI
																					 //b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI

							b.isActive = true;
							break;
						}
					}
				}
			}
		}


		if (teki2=1)//(timecont>170 && timecont<270)   CheckHitKey(KEY_INPUT_S)
		{
			tama = bulletH2;
			for (int i = 0; i < 50; i++)
			{


				if (frame % 12 == 0) {
					for (auto& b : bullets) {
						if (!b.isActive) {
							b.pos = enemypos;
							if (i == 0)
							{
								angle += 0.5f;
							}
							else if (i == 1)
							{
								angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
							}
							else
							{
								angle -= 0.5f;
							}
							b.vel = Vector2(cos(angle), sin(angle)).Normalized() * 5;//DX_PI
																					 //b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI

							b.isActive = true;
							break;
						}
					}
				}
			}
		}

		if (teki2=2)//(timecont > 440 && timecont < 550)  CheckHitKey(KEY_INPUT_D)
		{

			tama = bulletH3;
			for (int i = 0; i < GetRand(300); i++)
			{


				if (frame % 12 == 0) {
					for (auto& b : bullets) {
						if (!b.isActive) {
							b.pos = enemypos;
							if (i == 0)
							{
								angle += 0.2f;
							}
							else if (i == 1)
							{
								angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
							}
							else
							{
								angle -= 0.2f;
							}
							b.vel = Vector2(cos(angle), sin(angle)).Normalized() * (GetRand(10) + 1);//DX_PI
																									 //b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI

							b.isActive = true;
							break;
						}
					}
				}
			}
		}




		if (teki2=3) //(timecont < 90 || timecont>340 && timecont>440) CheckHitKey(KEY_INPUT_F)
		{

			tama = bulletH4;

			for (int i = 0; i < 7; i++)
			{


				if (frame % 12 == 0) {
					for (auto& b : bullets) {
						if (!b.isActive) {
							b.pos = enemypos;
							if (i == 0)
							{
								angle += 0.2f;
							}
							else if (i == 1)
							{
								angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
							}
							else
							{
								angle -= 0.2f;
							}
							b.vel = Vector2(cos(angle), sin(angle)).Normalized() * 7;//DX_PI
																							  //b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI

							b.isActive = true;
							break;
						}
					}
				}
			}
		}
		if (teki2=4) //(timecont < 90 || timecont>340 && timecont>440)  CheckHitKey(KEY_INPUT_G)
		{

			tama = bulletH5;

			for (int i = 0; i < GetRand(30); i++)
			{


				if (frame % 12 == 0) {
					for (auto& b : bullets) {
						if (!b.isActive) {
							b.pos = enemypos;
							if (i == 0)
							{
								angle += 0.2f;
							}
							else if (i == 1)
							{
								angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
							}
							else
							{
								angle -= 0.2f;
							}
							b.vel = Vector2(cos(angle), sin(angle)).Normalized() * 3;//DX_PI
																					 //b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI

							b.isActive = true;
							break;
						}
					}
				}
			}
		}

		mekakusiposx += (GetRand(30));
		mekakusiposy += (GetRand(30));
		/*if (timecont > 650)
		{
		timecont = 0;
		}*/
		//for (int i = 0; -1 < i < 3; i++) {}

		//’e‚ÌXV‚¨‚æ‚Ñ•\¦
		for (auto& b : bullets) {
			if (!b.isActive) {
				continue;
			}

			//’e‚ÌŒ»İÀ•W‚É’e‚ÌŒ»İ‘¬“x‚ğ‰ÁZ‚µ‚Ä‚­‚¾‚³‚¢
			b.pos = b.pos + b.vel;

			//’e‚ÌŠp“x‚ğatan2‚ÅŒvZ‚µ‚Ä‚­‚¾‚³‚¢Bangle‚É’l‚ğ“ü‚ê‚é‚ñ‚¾‚æƒIƒD
			float angle2 = atan2(b.vel.y, b.vel.x);
			
				DrawRotaGraph(b.pos.x, b.pos.y, 1.0f, angle2, tama, true);
			
			//DrawGraph(mekakusiposx, mekakusiposy,mekakushi, true);
			if (isDebugMode) {
				//’e‚Ì–{‘Ì(“–‚½‚è”»’è)
				DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
			}
			//’e‚ğE‚·
			if (b.pos.x + 16 < 0 || b.pos.x - 16 > 640 ||
				b.pos.y + 24 < 0 || b.pos.y - 24 > 480) {
				b.isActive = false;
			}
			if (mekakusiposx + 16 < 0 || mekakusiposx - 16 > 640 ||
				mekakusiposy - 100 < 0 || mekakusiposy - 24 > 480) {
				mekakusiposx = 0;
				mekakusiposy = -100;
			}
			//‚ ‚½‚èI
			//«‚ÌIsHit‚ÍÀ‘•‚ğ‘‚¢‚Ä‚Ü‚¹‚ñB©•ª‚Å‘‚¢‚Ä‚­‚¾‚³‚¢B
			if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {
				//“–‚½‚Á‚½”½‰‚ğ‘‚¢‚Ä‚­‚¾‚³‚¢B
				b.isActive = false;
			}
		}

		//“G‚Ì•\¦
		enemypos.x = abs((int)((frame + 320) % 1280) - 640);
		enemypos.y = enemypos.y+5.0f;
		if (enemypos.y >= 600)
		{
			enemypos.y = -40;
			teki2 +=1;
			//teki = GetRand(5);
			//teki2 = teki;
		}
		if (teki2 <= 5)
		{
			teki2 = 0;
		}
		int eidx = (frame / 4 % 2);
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx], true);

		if (isDebugMode) {
			//“G‚Ì–{‘Ì(“–‚½‚è”»’è)
			DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
		}
		++frame;
		ScreenFlip();
	}

	DxLib_End();

	return 0;
}
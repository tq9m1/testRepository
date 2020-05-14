#include<DxLib.h>
#include<cmath>
#include"main.h"
//#include"Enemy.h"

///当たり判定関数
///@param posA Aの座標
///@param radiusA Aの半径
///@param posB Bの座標
///@param radiusB Bの半径
bool IsHit(const Position2& posA, float radiusA, const Position2& posB, float radiusB) {
	//当たり判定を実装してください

	return(hypot(posA.x - posB.x, posA.y - posB.y)<radiusA + radiusB);
}
int timecont = 0;

//背景
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetMainWindowText("1816240_西住優太");
	if (DxLib_Init() != 0) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	//背景用
	int bgH[4];
	LoadDivGraph("img/bganim.png", 4, 4, 1, 1024, 192, bgH);

	int skyH = LoadGraph("img/sky.png");
	int sky2H = LoadGraph("img/sky2.png");
	//int mekakushi= LoadGraph("img/tama.png");
	auto bulletH = LoadGraph("img/tama2.png");
	auto bulletH2 = LoadGraph("img/tama3.png");
	auto bulletH3 = LoadGraph("img/tama4.png");
	auto bulletH4 = LoadGraph("img/tama5.png");
	int playerH[10];
	LoadDivGraph("img/player.png", 10, 5, 2, 16, 24, playerH);

	int enemyH[2];
	LoadDivGraph("img/enemy.png", 2, 2, 1, 32, 32, enemyH);

	struct Bullet {
		Position2 pos;//座標
		Vector2 vel;//速度
		bool isActive = false;//生きてるか～？
	};

	int mekakusiposx = 0;
	int mekakusiposy = -100;
	//弾の半径
	float bulletRadius = 5.0f;

	//自機の半径
	float playerRadius = 10.0f;

	//適当に256個くらい作っとく
	Bullet bullets[100];

	Position2 enemypos(320, 25);//敵座標
	Position2 playerpos(320, 400);//自機座標

	unsigned int frame = 0;//フレーム管理用

	char keystate[256];
	bool isDebugMode = false;
	int skyy = 0;
	int skyy2 = 0;
	int bgidx = 0;


	int spi = 1;
//	int tomegu = 0;
	int tama = 1;
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


		//プレイヤー
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
			//自機の本体(当たり判定)
			DrawCircle(playerpos.x, playerpos.y, playerRadius, 0xffaaaa, false, 3);
		}
		float angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
		//弾発射

		//timecont++;
		
			if (CheckHitKey(KEY_INPUT_A)) //(timecont < 90 || timecont>340 && timecont>440)
			{
				
				
				tama = 1;
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
		

		if (CheckHitKey(KEY_INPUT_S))//(timecont>170 && timecont<270)
		{
			tama = 2;
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

		if (CheckHitKey(KEY_INPUT_D))//(timecont > 440 && timecont < 550)
		{
			
			tama = 3;
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




		if (CheckHitKey(KEY_INPUT_F)) //(timecont < 90 || timecont>340 && timecont>440)
		{
			
			tama = 4;

			for (int i = 0; i < 4; i++)
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
							b.vel = Vector2(cos(angle), sin(angle)).Normalized() * (spi += 1);//DX_PI
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

		//弾の更新および表示
		for (auto& b : bullets) {
			if (!b.isActive) {
				continue;
			}

			//弾の現在座標に弾の現在速度を加算してください
			b.pos = b.pos + b.vel;

			//弾の角度をatan2で計算してください。angleに値を入れるんだよオゥ
			float angle2 = atan2(b.vel.y, b.vel.x);
			if (tama = 1)
			{
				DrawRotaGraph(b.pos.x, b.pos.y, 1.0f, angle2, bulletH, true);
			}
			if (tama = 2)
			{
				DrawRotaGraph(b.pos.x, b.pos.y, 1.0f, angle2, bulletH2, true);
			}
			if (tama = 3)
			{
				DrawRotaGraph(b.pos.x, b.pos.y, 1.0f, angle2, bulletH3, true);
			}
			if (tama = 4)
			{
				DrawRotaGraph(b.pos.x, b.pos.y, 1.0f, angle2, bulletH4, true);
			}
			//DrawGraph(mekakusiposx, mekakusiposy,mekakushi, true);
			if (isDebugMode) {
				//弾の本体(当たり判定)
				DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
			}
			//弾を殺す
			if (b.pos.x + 16 < 0 || b.pos.x - 16 > 640 ||
				b.pos.y + 24 < 0 || b.pos.y - 24 > 480) {
				b.isActive = false;
			}
			if (mekakusiposx + 16 < 0 || mekakusiposx - 16 > 640 ||
				mekakusiposy -100 < 0 || mekakusiposy - 24 > 480) {
				mekakusiposx = 0;
				mekakusiposy = -100;
			}
			//あたり！
			//↓のIsHitは実装を書いてません。自分で書いてください。
			if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {
				//当たった反応を書いてください。
				b.isActive = false;
			}
		}

		//敵の表示
		enemypos.x = abs((int)((frame + 320) % 1280) - 640);
		int eidx = (frame / 4 % 2);
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx], true);

		if (isDebugMode) {
			//敵の本体(当たり判定)
			DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
		}
		++frame;
		ScreenFlip();
	}

	DxLib_End();

	return 0;
}
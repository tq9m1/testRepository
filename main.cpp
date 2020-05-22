#include<DxLib.h>
#include<cmath>
#include"main.h"
//#include"Enemy.h"

///当たり判定関数
///@param posA Aの座標
///@param radiusA Aの半径
///@param posB Bの座標
///@param radiusB Bの半径

TEKI_MODE tekiMode;
PLAYER_MODE playerMode;

int teki2 = 0;
int teki = 0;//GetRand(100);

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
	auto bulletH5 = LoadGraph("img/tama6.png");

	auto playerblle = LoadGraph("img/tama2.png");
	auto playerblle2 = LoadGraph("img/tama3.png");
	auto playerblle3 = LoadGraph("img/tama4.png");
	auto playerblle4 = LoadGraph("img/tama5.png");
	auto playerblle5 = LoadGraph("img/tama6.png");
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
	int tekihyouji = 1;
	struct Bullet {
		Position2 pos;//座標
		Vector2 vel;//速度
		bool isActive = false;//生きてるか～？
	};

	struct PlayerBullet {
		Position2 pos;//座標
		Vector2 vel;//速度
		bool isActive = false;//生きてるか～？
	};

	int mekakusiposx = 0;
	int mekakusiposy = -100;
	//弾の半径
	float bulletRadius = 5.0f;

	//player
	float pbulletRadius = 5.0f;
	//自機の半径
	float playerRadius = 10.0f;

	//敵の半径
	float enemyRadius = 15.0f;
	//適当に256個くらい作っとく
	Bullet bullets[100];
	PlayerBullet pbullets[100];

	//Position2 enemypos(320, 25);//敵座標
	Position2 enemypos(100, -25);
	Position2 playerpos(320, 400);//自機座標

	unsigned int frame = 0;//フレーム管理用

	char keystate[256];
	bool isDebugMode = false;
	int skyy = 0;
	int skyy2 = 0;
	int bgidx = 0;


	int spi = 1;
	//	int tomegu = 0;
	int tama = bulletH;
	int tamaP = playerblle;
	
	int plyertama =0;

	bool tamaflog = false;

	//int tekiTime = 0;
	
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


		float pangle = atan2(enemypos.y - playerpos.y, enemypos.x - playerpos.x);
		//弾発射

		//timecont++;
		//mekakusiposx += (GetRand(30));
		//mekakusiposy += (GetRand(30));

		//for (int i = 0; -1 < i < 3; i++) {}

		//弾の更新および表示
		switch (tekiMode)//敵処理
		{
		case TEKI_INIT:
			teki = GetRand(100);
			//	teki = teki2;
			tekiMode = TAMA_MAIN;
			break;
		case TAMA_MAIN:
			if (teki >= 0 && teki <= 19)
			{
				tekiMode = TAMA_1;
			}
			else if (teki >= 20 && teki <= 39)
			{
				tekiMode = TAMA_2;
			}
			else if (teki >= 40 && teki <= 59)
			{
				tekiMode = TAMA_3;
			}
			else if (teki >= 60 && teki <= 79)
			{
				tekiMode = TAMA_4;
			}
			else if (teki >= 80 && teki <= 100)
			{
				tekiMode = TAMA_5;
			}
			break;
		case TAMA_1:
			tama = bulletH;
			tekihyouji = 1;
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
							if (enemypos.y >= 600) tekiMode = TEKI_OWARI;
							break;

						}
					}
				}
			}

			break;
		case TAMA_2:
			tama = bulletH2;
			tekihyouji = 2;
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
							if (enemypos.y >= 600) tekiMode = TEKI_OWARI;
							break;

						}
					}
				}
			}

			break;
		case TAMA_3:
			tama = bulletH3;
			tekihyouji = 3;
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
							if (enemypos.y >= 600) tekiMode = TEKI_OWARI;
							break;
						}
					}
				}
			}
			if (enemypos.y >= 600) tekiMode = TEKI_OWARI;
			break;
		case TAMA_4:
			tama = bulletH4;
			tekihyouji = 4;
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
							if (enemypos.y >= 600) tekiMode = TEKI_OWARI;
							break;
						}
					}
				}
			}

			break;
		case TAMA_5:
			tama = bulletH5;
			tekihyouji = 5;
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
							if (enemypos.y >= 600) tekiMode = TEKI_OWARI;
							break;
						}
					}
				}
			}

			break;
		case TEKI_OWARI:

			enemypos.y = -60;
			teki2 = GetRand(100);
			teki = teki2;
			tekiMode = TAMA_MAIN;


			break;
		}

		if (IsHit(enemypos, enemyRadius, playerpos, playerRadius))
		{
			//当たった反応を書いてください。
			enemypos.y = 1000;
			//playerMode = PLYER_INIT;

			tamaflog = true;
			plyertama = teki;
		}


		if (tamaflog = true)
		{
			if (plyertama >= 0 && plyertama <= 19)
			{
				if (keystate[KEY_INPUT_A])
				{
					tamaP = bulletH;

					for (int i = 0; i < 3; i++)
					{


						if (frame % 12 == 0)
						{
							for (auto& pb : pbullets)
							{
								if (!pb.isActive)
								{
									pb.pos = playerpos;
									if (i == 0)
									{
										pangle += 0.2f;
									}
									else if (i == 1)
									{
										pangle = atan2(enemypos.y - playerpos.y, enemypos.x - playerpos.x);
									}
									else
									{
										pangle -= 0.2f;
									}
									pb.vel = Vector2(cos(pangle), sin(pangle)).Normalized() * 5;//DX_PI
																								//b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI

									pb.isActive = true;
								}
							}
						}
					}
				}
			}
			else if (plyertama >= 20 && plyertama <= 39)
			{
				if (keystate[KEY_INPUT_A])
				{
					tamaP = bulletH2;

					for (int i = 0; i < 50; i++)
					{


						if (frame % 12 == 0) {
							for (auto& pb : pbullets) {
								if (!pb.isActive) {
									pb.pos = playerpos;
									if (i == 0)
									{
										pangle += 0.5f;
									}
									else if (i == 1)
									{
										pangle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
									}
									else
									{
										pangle -= 0.5f;
									}
									pb.vel = Vector2(cos(pangle), sin(pangle)).Normalized() * 5;//DX_PI
																							   //b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI


									pb.isActive = true;



									break;



								}
							}
						}
					}
				}
			}
			else if (plyertama >= 40 && plyertama <= 59)
			{
				if (keystate[KEY_INPUT_A])
				{
					tamaP = playerblle3;

					for (int i = 0; i < GetRand(300); i++)
					{


						if (frame % 12 == 0) {
							for (auto& pb : pbullets) {
								if (!pb.isActive) {
									pb.pos = playerpos;
									if (i == 0)
									{
										pangle += 0.2f;
									}
									else if (i == 1)
									{
										pangle = atan2(enemypos.y - playerpos.y, enemypos.x - playerpos.x);
									}
									else
									{
										pangle -= 0.2f;
									}
									pb.vel = Vector2(cos(pangle), sin(pangle)).Normalized() * (GetRand(10) + 1);//DX_PI
																												//b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI

									pb.isActive = true;



								}
							}
						}
					}
				}
			}
			else if (plyertama >= 60 && plyertama <= 79)
			{
				if (keystate[KEY_INPUT_A])
				{
					tamaP = playerblle4;

					for (int i = 0; i < 7; i++)
					{

						if (frame % 12 == 0)
						{
							for (auto& pb : pbullets) {
								if (!pb.isActive) {
									pb.pos = playerpos;
									if (i == 0)
									{
										pangle += 0.2f;
									}
									else if (i == 1)
									{
										pangle = atan2(enemypos.y - playerpos.y, enemypos.x - playerpos.x);
									}
									else
									{
										pangle -= 0.2f;
									}
									pb.vel = Vector2(cos(pangle), sin(pangle)).Normalized() * 7;//DX_PI



									pb.isActive = true;




									break;
								}
							}
						}
					}
				}
			}
			else if (plyertama >= 80 && plyertama <= 100)
			{
				if (keystate[KEY_INPUT_A])
				{
					tamaP = playerblle5;

					for (int i = 0; i < GetRand(30); i++)
					{

						if (frame % 12 == 0)
						{
							for (auto& pb : pbullets) {
								if (!pb.isActive) {
									pb.pos = playerpos;
									if (i == 0)
									{
										pangle += 0.2f;
									}
									else if (i == 1)
									{
										pangle = atan2(enemypos.y - playerpos.y, enemypos.x - playerpos.x);
									}
									else
									{
										pangle -= 0.2f;
									}
									pb.vel = Vector2(cos(pangle), sin(pangle)).Normalized() * 5;//DX_PI


									pb.isActive = true;



									break;
								}
							}
						}
					}
				}
			}


		}
		else
		{

		}
		//////////////////////////////////////////////////////////////////////////////
				//switch (playerMode)
				//{
				//case PLYER_INIT:

				//	if (IsHit(enemypos, enemyRadius, playerpos, playerRadius)) {
				//		//当たった反応を書いてください。
				//		//enemypos.y = 1000;
				//		// playerMode = PLYER_INIT;
				//		plyertama = teki;
				//	}
				//	if (plyertama >= 0 && plyertama <= 19)
				//	{
				//		tekiMode = TAMA_1;
				//	}
				//	else if (plyertama >= 20 && plyertama <= 39)
				//	{
				//		tekiMode = TAMA_2;
				//	}
				//	else if (plyertama >= 40 && plyertama <= 59)
				//	{
				//		tekiMode = TAMA_3;
				//	}
				//	else if (plyertama >= 60 && plyertama <= 79)
				//	{
				//		tekiMode = TAMA_4;
				//	}
				//	else if (plyertama >= 80 && plyertama <= 100)
				//	{
				//		tekiMode = TAMA_5;
				//	}
				//	break;
				//case PTAMA_1:
				//	tamaP = bulletH;

				//	for (int i = 0; i < 3; i++)
				//	{


				//		if (frame % 12 == 0)
				//		{
				//			for (auto& pb : pbullets) {
				//				if (!pb.isActive) {
				//					pb.pos = playerpos;
				//					if (i == 0)
				//					{
				//						pangle += 0.2f;
				//					}
				//					else if (i == 1)
				//					{
				//						pangle = atan2(enemypos.y - playerpos.y, enemypos.x - playerpos.x);
				//					}
				//					else
				//					{
				//						pangle -= 0.2f;
				//					}
				//					pb.vel = Vector2(cos(pangle), sin(pangle)).Normalized() * 5;//DX_PI
				//																				//b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI
				//					if (IsHit(enemypos, enemyRadius, playerpos, playerRadius)) {
				//						//当たった反応を書いてください。
				//						enemypos.y = 1000;
				//						playerMode = PLYER_INIT;
				//						plyertama = teki;
				//					}
				//					pb.isActive = true;

				//					

				//					break;

				//				}
				//			}
				//		}
				//	}
				//	break;
				//case PTAMA_2:
				//	tamaP = bulletH2;

				//	for (int i = 0; i < 50; i++)
				//	{


				//		if (frame % 12 == 0) {
				//			for (auto& b : pbullets) {
				//				if (!b.isActive) {
				//					b.pos = playerpos;
				//					if (i == 0)
				//					{
				//						pangle += 0.5f;
				//					}
				//					else if (i == 1)
				//					{
				//						pangle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);
				//					}
				//					else
				//					{
				//						pangle -= 0.5f;
				//					}
				//					b.vel = Vector2(cos(pangle), sin(pangle)).Normalized() * 5;//DX_PI
				//																			   //b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI
				//					

				//					b.isActive = true;

				//					

				//					break;



				//				}
				//			}
				//		}
				//	}
				//	break;
				//case PTAMA_3:
				//	tamaP = playerblle3;

				//	for (int i = 0; i < GetRand(300); i++)
				//	{


				//		if (frame % 12 == 0) {
				//			for (auto& pb : pbullets) {
				//				if (!pb.isActive) {
				//					pb.pos = playerpos;
				//					if (i == 0)
				//					{
				//						pangle += 0.2f;
				//					}
				//					else if (i == 1)
				//					{
				//						pangle = atan2(enemypos.y - playerpos.y, enemypos.x - playerpos.x);
				//					}
				//					else
				//					{
				//						pangle -= 0.2f;
				//					}
				//					pb.vel = Vector2(cos(pangle), sin(pangle)).Normalized() * (GetRand(10) + 1);//DX_PI
				//																								//b.vel = ((playerpos - enemypos).Normalized()*i)*5.0f;//DX_PI
				//					
				//					pb.isActive = true;

				//					aaa

				//				}
				//			}
				//		}
				//	}
				//	break;
				//case PTAMA_4:
				//	tamaP = playerblle4;

				//	for (int i = 0; i < 7; i++)
				//	{

				//		if (frame % 12 == 0)
				//		{
				//			for (auto& pb : pbullets) {
				//				if (!pb.isActive) {
				//					pb.pos = playerpos;
				//					if (i == 0)
				//					{
				//						pangle += 0.2f;
				//					}
				//					else if (i == 1)
				//					{
				//						pangle = atan2(enemypos.y - playerpos.y, enemypos.x - playerpos.x);
				//					}
				//					else
				//					{
				//						pangle -= 0.2f;
				//					}
				//					pb.vel = Vector2(cos(pangle), sin(pangle)).Normalized() * 7;//DX_PI

				//					

				//					pb.isActive = true;

				//					


				//					break;
				//				}
				//			}
				//		}
				//	}
				//	break;
				//case PTAMA_5:
				//	tamaP = playerblle5;

				//	for (int i = 0; i < GetRand(30); i++)
				//	{

				//		if (frame % 12 == 0)
				//		{
				//			for (auto& pb : pbullets) {
				//				if (!pb.isActive) {
				//					pb.pos = playerpos;
				//					if (i == 0)
				//					{
				//						pangle += 0.2f;
				//					}
				//					else if (i == 1)
				//					{
				//						pangle = atan2(enemypos.y - playerpos.y, enemypos.x - playerpos.x);
				//					}
				//					else
				//					{
				//						pangle -= 0.2f;
				//					}
				//					pb.vel = Vector2(cos(pangle), sin(pangle)).Normalized() * 5;//DX_PI


				//					pb.isActive = true;

				//					

				//					break;
				//				}
				//			}
				//		}
				//	}
				//	break;
				//}










				//player
		for (auto& pb : pbullets)
		{

			if (!pb.isActive) {
				continue;
			}
			//弾の現在座標に弾の現在速度を加算してくださいplayer
			pb.pos = pb.pos + pb.vel;
			//弾の角度をatan2で計算してください。angleに値を入れるんだよオゥ
			float pangle2 = atan2(pb.vel.y, pb.vel.x);
			//player
			DrawRotaGraph(pb.pos.x, pb.pos.y, 1.0f, pangle2, tamaP, true);
			//弾を殺す player
			if (pb.pos.x + 16 < 0 || pb.pos.x - 16 > 640 ||
				pb.pos.y + 24 < 0 || pb.pos.y - 24 > 480) {
				pb.isActive = false;
			}
			//player
			if (isDebugMode) {
				//弾の本体(当たり判定)
				DrawCircle(pb.pos.x, pb.pos.y, pbulletRadius, 0x0000ff, false, 3);
			}
		}
			//DrawGraph(mekakusiposx, mekakusiposy,mekakushi, true);
			
			//あたり！
			//↓のIsHitは実装を書いてません。自分で書いてください。
			//if (IsHit(pb.pos, pbulletRadius,enemypos, playerRadius)) {
			//	//当たった反応を書いてください。
			//	pb.isActive = false;
			//}


		


		//敵
			for (auto& b : bullets)
			{
				if (!b.isActive) {
					continue;
				}

			

				//弾の現在座標に弾の現在速度を加算してください
				b.pos = b.pos + b.vel;
				

				//弾の角度をatan2で計算してください。angleに値を入れるんだよオゥ
				float angle2 = atan2(b.vel.y, b.vel.x);
				//弾の現在座標に弾の現在速度を加算してくださいplayer
			//	pb.pos = pb.pos + pb.vel;

				


				DrawRotaGraph(b.pos.x, b.pos.y, 1.0f, angle2, tama, true);

				







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
				for (auto& pb : pbullets)
				{

					if (!pb.isActive) {
						continue;
					}
					if (IsHit(b.pos, bulletRadius,pb.pos, pbulletRadius)) {
						//当たった反応を書いてください。
						b.isActive = false;
						pb.isActive = false;
					}

				}

				/*if (mekakusiposx + 16 < 0 || mekakusiposx - 16 > 640 ||
					mekakusiposy - 100 < 0 || mekakusiposy - 24 > 480) {
					mekakusiposx = 0;
					mekakusiposy = -100;
				}*/
				//あたり！
				//↓のIsHitは実装を書いてません。自分で書いてください。
				if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {
					//当たった反応を書いてください。
					b.isActive = false;
				}

				//if (IsHit(b.pos, bulletRadius, pb.pos, pbulletRadius)) {
				//	//当たった反応を書いてください。
				//	b.isActive = false;
				//	pb.isActive = false;
				//}

				/////////////////////////////////////////////////////////////////////////////
				if (IsHit(enemypos, enemyRadius, playerpos, playerRadius)) {
					//当たった反応を書いてください。
					enemypos.y = 1000;
					//playerMode = PLYER_INIT;
					//plyertama = teki;
				}

			
		}
			//敵の表示

			enemypos.x = abs((int)((frame + 320) % 1280) - 640);
			enemypos.y = enemypos.y + 3.0f;
			/*if (enemypos.y >= 600)
			{
				enemypos.y = -40;
			}*/

			/*if (teki2 <= 5)
			{
				teki2 = 0;
			}*/
			int eidx = (frame / 4 % 2);

			if (tekihyouji = 1)
			{
				DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx], true);
			}
			else if (tekihyouji = 2)
			{
				DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH2[eidx], true);
			}
			else if (tekihyouji = 3)
			{
				DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH3[eidx], true);
			}
			else if (tekihyouji = 4)
			{
				DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH4[eidx], true);
			}
			else if (tekihyouji = 5)
			{
				DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH5[eidx], true);
			}

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
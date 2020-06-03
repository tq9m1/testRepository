#include<DxLib.h>
#include<cmath>
#include"main.h"
//#include"Enemy.h"

///“–‚½‚è”»’èŠÖ”
///@param posA A‚ÌÀ•W
///@param radiusA A‚Ì”¼Œa
///@param posB B‚ÌÀ•W
///@param radiusB B‚Ì”¼Œa

TEKI_MODE tekiMode;
//PLAYER_MODE playerMode;

int teki2 = 0;
int teki = 0;//GetRand(100);

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

	//”wŒi—p///////////////////////////////////////////////////
	int haikei = LoadGraph("img/utyuu.png");
	
	int hosi1 = LoadGraph("img/hosi1.png");
	int hosi2 = LoadGraph("img/hosi2.png");
	int hosi3 = LoadGraph("img/hosi3.png");
	int hosi4 = LoadGraph("img/hosi4.png");
//////////////////////////////////////////////////////////////
	//bgm
	int bgm1 = LoadSoundMem("sund/oke_song_kei_vegalost.mp3");
	int bgm2 = LoadSoundMem("sund/bgm_maoudamashii_orchestra24.mp3");
///////////////////////////////////////////////////
	//int bgH[4];
	//LoadDivGraph("img/bganim.png", 4, 4, 1, 1024, 192, bgH);

	//int skyH = LoadGraph("img/sky.png");
	//int sky2H = LoadGraph("img/sky2.png");
	////int mekakushi= LoadGraph("img/tama.png");
	//////////////////////////////////////////////////////
	auto bulletH = LoadGraph("img/tama2.png");
	auto bulletH2 = LoadGraph("img/tama3.png");
	auto bulletH3 = LoadGraph("img/tama4.png");
	auto bulletH4 = LoadGraph("img/tama5.png");
	auto bulletH5 = LoadGraph("img/tama6.png");
////////////////////////////////////////////////////////////////
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
		Position2 pos;//À•W
		Vector2 vel;//‘¬“x
		bool isActive = false;//¶‚«‚Ä‚é‚©`H
	};

	struct PlayerBullet {
		Position2 pos;//À•W
		Vector2 vel;//‘¬“x
		bool isActive = false;//¶‚«‚Ä‚é‚©`H
	};

	int mekakusiposx = 0;
	int mekakusiposy = -100;
	//’e‚Ì”¼Œa
	float bulletRadius = 5.0f;

	//player
	float pbulletRadius = 5.0f;
	//©‹@‚Ì”¼Œa
	float playerRadius = 10.0f;

	//“G‚Ì”¼Œa
	float enemyRadius = 15.0f;
	//“K“–‚É256ŒÂ‚­‚ç‚¢ì‚Á‚Æ‚­
	Bullet bullets[100];
	PlayerBullet pbullets[100];

	//Position2 enemypos(320, 25);//“GÀ•W
	Position2 enemypos(100, -25);
	Position2 playerpos(320, 400);//©‹@À•W

	unsigned int frame = 0;//ƒtƒŒ[ƒ€ŠÇ——p

	char keystate[256];
	bool isDebugMode = false;
	int skyy = 0;
	int skyy2 = 0;
	int skyy3 = 0;
	int bgidx = 0;


	int spi = 1;
	//	int tomegu = 0;
	int tama = bulletH;
	int tamaP = playerblle;

	int plyertama = 0;

	bool tamaflog = false;

	//////////////////////////////////////////
	//”wŒiŒn

	int px = 50;
	int py = px;
	int px1 = 0;
	int py1 = px1;
	int px2 = 100;
	int py2 = px2;
	int px3 = 400;
	int py3 = px3;
	//int pos = 0;
	int hosisyokix;
	int hosiposx;
	int hosiposy;
	int hosisyokix1;
	int hosiposx1;
	int hosiposy1;
	int hosiposx2;
	int hosiposy2;
	int hosiposx3;
	int hosiposy3;
	//float kousinnflg;
////////////////////////////////////////////////////////
	while (ProcessMessage() == 0) {
		ClearDrawScreen();

		GetHitKeyStateAll(keystate);

		isDebugMode = keystate[KEY_INPUT_P];

		
		bgidx = (bgidx + 1) % 32;
/////////////////////////////////////////////////////////////////////////////////
		PlaySoundMem(bgm2, DX_PLAYTYPE_BACK);
		PlaySoundMem(bgm1, DX_PLAYTYPE_BACK);

		

		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	
		
		skyy = (skyy + 5) % 640;
		skyy2 = (skyy2 + 1) % 640;
		skyy3 = (skyy3 + 5) % 640;
		

		/////////////////////////////////////////////////////////////////////////
		//”wŒi
		DrawGraph(0, 0, haikei, true);
		
		px3 = 400;
		py3 = px3;
		hosiposy3 = -100;
		hosiposx3 = 250;
		DrawExtendGraph(hosiposx3 + px3, hosiposy3 + py3 + skyy3, hosiposx3 + (px3 * 2), hosiposy3 + (py3 * 2) + skyy3, hosi4, true);
		px2 = 100;
		py2=px2;
		hosiposy2 = -200;
		hosiposx2 = 300;


		DrawExtendGraph(hosiposx2 + px2, hosiposy2 + py2 + skyy2, hosiposx2 + (px2 * 2), hosiposy2 + (py2 * 2) + skyy2, hosi3, true);
		//pos=pos+GetRand(100);
		{px = 30;
		py = px;
		hosiposy = -100;
		hosiposx = 500;
		


		
		
		DrawExtendGraph(hosiposx + px, hosiposy + py + skyy, hosiposx + (px * 2), hosiposy + (py * 2) + skyy, hosi1, true);
		}
		{
			
			px1 = px1 + 1;
			py1 = px1;
			hosiposy1 = 0;
			hosisyokix1 = 0;
			hosiposx1 = hosisyokix1;
			DrawExtendGraph(hosiposx1 + px1, hosiposy1 + py1 , hosiposx1 + (px1 * 2), hosiposy1 + (py1 * 2) , hosi2, true);
			if (px1 >= 800)
			{
				px1 = 0;
			}
		}
	//	DrawGraph(pos, pos, hosi2, true);

////////////////////////////////////////////////////////////////////////////////
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


		float pangle = atan2(enemypos.y - playerpos.y, enemypos.x - playerpos.x);
		//’e”­Ë

		//timecont++;
		//mekakusiposx += (GetRand(30));
		//mekakusiposy += (GetRand(30));

		//for (int i = 0; -1 < i < 3; i++) {}

		//’e‚ÌXV‚¨‚æ‚Ñ•\¦
		switch (tekiMode)//“Gˆ—
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
			//“–‚½‚Á‚½”½‰‚ğ‘‚¢‚Ä‚­‚¾‚³‚¢B
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
		//		//“–‚½‚Á‚½”½‰‚ğ‘‚¢‚Ä‚­‚¾‚³‚¢B
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
		//						//“–‚½‚Á‚½”½‰‚ğ‘‚¢‚Ä‚­‚¾‚³‚¢B
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
			//’e‚ÌŒ»İÀ•W‚É’e‚ÌŒ»İ‘¬“x‚ğ‰ÁZ‚µ‚Ä‚­‚¾‚³‚¢player
			pb.pos = pb.pos + pb.vel;
			//’e‚ÌŠp“x‚ğatan2‚ÅŒvZ‚µ‚Ä‚­‚¾‚³‚¢Bangle‚É’l‚ğ“ü‚ê‚é‚ñ‚¾‚æƒIƒD
			float pangle2 = atan2(pb.vel.y, pb.vel.x);
			//player
			DrawRotaGraph(pb.pos.x, pb.pos.y, 1.0f, pangle2, tamaP, true);
			//’e‚ğE‚· player
			if (pb.pos.x + 16 < 0 || pb.pos.x - 16 > 640 ||
				pb.pos.y + 24 < 0 || pb.pos.y - 24 > 480) {
				pb.isActive = false;
			}
			//player
			if (isDebugMode) {
				//’e‚Ì–{‘Ì(“–‚½‚è”»’è)
				DrawCircle(pb.pos.x, pb.pos.y, pbulletRadius, 0x0000ff, false, 3);
			}
		}
		//DrawGraph(mekakusiposx, mekakusiposy,mekakushi, true);

		//‚ ‚½‚èI
		//«‚ÌIsHit‚ÍÀ‘•‚ğ‘‚¢‚Ä‚Ü‚¹‚ñB©•ª‚Å‘‚¢‚Ä‚­‚¾‚³‚¢B
		//if (IsHit(pb.pos, pbulletRadius,enemypos, playerRadius)) {
		//	//“–‚½‚Á‚½”½‰‚ğ‘‚¢‚Ä‚­‚¾‚³‚¢B
		//	pb.isActive = false;
		//}





		//“G
		for (auto& b : bullets)
		{
			if (!b.isActive) {
				continue;
			}



			//’e‚ÌŒ»İÀ•W‚É’e‚ÌŒ»İ‘¬“x‚ğ‰ÁZ‚µ‚Ä‚­‚¾‚³‚¢
			b.pos = b.pos + b.vel;


			//’e‚ÌŠp“x‚ğatan2‚ÅŒvZ‚µ‚Ä‚­‚¾‚³‚¢Bangle‚É’l‚ğ“ü‚ê‚é‚ñ‚¾‚æƒIƒD
			float angle2 = atan2(b.vel.y, b.vel.x);
			//’e‚ÌŒ»İÀ•W‚É’e‚ÌŒ»İ‘¬“x‚ğ‰ÁZ‚µ‚Ä‚­‚¾‚³‚¢player
			//	pb.pos = pb.pos + pb.vel;




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
			for (auto& pb : pbullets)
			{

				if (!pb.isActive) {
					continue;
				}
				if (IsHit(b.pos, bulletRadius, pb.pos, pbulletRadius)) {
					//“–‚½‚Á‚½”½‰‚ğ‘‚¢‚Ä‚­‚¾‚³‚¢B
					b.isActive = false;
					pb.isActive = false;
				}

			}

			/*if (mekakusiposx + 16 < 0 || mekakusiposx - 16 > 640 ||
			mekakusiposy - 100 < 0 || mekakusiposy - 24 > 480) {
			mekakusiposx = 0;
			mekakusiposy = -100;
			}*/
			//‚ ‚½‚èI
			//«‚ÌIsHit‚ÍÀ‘•‚ğ‘‚¢‚Ä‚Ü‚¹‚ñB©•ª‚Å‘‚¢‚Ä‚­‚¾‚³‚¢B
			if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {
				//“–‚½‚Á‚½”½‰‚ğ‘‚¢‚Ä‚­‚¾‚³‚¢B
				b.isActive = false;
			}

			//if (IsHit(b.pos, bulletRadius, pb.pos, pbulletRadius)) {
			//	//“–‚½‚Á‚½”½‰‚ğ‘‚¢‚Ä‚­‚¾‚³‚¢B
			//	b.isActive = false;
			//	pb.isActive = false;
			//}

			/////////////////////////////////////////////////////////////////////////////
			if (IsHit(enemypos, enemyRadius, playerpos, playerRadius)) {
				//“–‚½‚Á‚½”½‰‚ğ‘‚¢‚Ä‚­‚¾‚³‚¢B
				enemypos.y = 1000;
				//playerMode = PLYER_INIT;
				//plyertama = teki;
			}


		}
		//“G‚Ì•\¦

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
			//“G‚Ì–{‘Ì(“–‚½‚è”»’è)
			DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
		}
		++frame;
		ScreenFlip();

	}

	DxLib_End();

	return 0;
}
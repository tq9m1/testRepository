#include<DxLib.h>
#include<cmath>
#include"main.h"
//#include"Enemy.h"

///ìñÇΩÇËîªíËä÷êî
///@param posA AÇÃç¿ïW
///@param radiusA AÇÃîºåa
///@param posB BÇÃç¿ïW
///@param radiusB BÇÃîºåa

TEKI_MODE tekiMode;
//PLAYER_MODE playerMode;

int teki2 = 0;
int teki = 0;//GetRand(100);

bool IsHit(const Position2& posA, float radiusA, const Position2& posB, float radiusB) {
	//ìñÇΩÇËîªíËÇé¿ëïÇµÇƒÇ≠ÇæÇ≥Ç¢

	return(hypot(posA.x - posB.x, posA.y - posB.y)<radiusA + radiusB);
}
int timecont = 0;

//îwåi
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetMainWindowText("1816240_êºèZóDëæ");
	if (DxLib_Init() != 0) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	//îwåióp///////////////////////////////////////////////////
	int haikei = LoadGraph("img/utyuu.png");
	
	int hosi1 = LoadGraph("img/hosi1.png");
	int hosi2 = LoadGraph("img/hosi2.png");
	int hosi3 = LoadGraph("img/hosi3.png");
	int hosi4 = LoadGraph("img/hosi4.png");
	int hosi5 = LoadGraph("img/hosi5.png");
	int hosi6 = LoadGraph("img/hosi6.png");
	int hosi7 = LoadGraph("img/hosi7.png");
	int hosi8 = LoadGraph("img/hosi8.png");
	int hosi9 = LoadGraph("img/hosi9.png");
	int hosi10 = LoadGraph("img/hosi10.png");
	int hosi11 = LoadGraph("img/hosi11.png");
	int hosi12 = LoadGraph("img/hosi12.png");
	int hosi13 = LoadGraph("img/hosi13.png");
	int hosi14 = LoadGraph("img/hosi14.png");
	int hosi15 = LoadGraph("img/hosi15.png");
	int hosi16 = LoadGraph("img/hosi16.png");
	int hosi17 = LoadGraph("img/hosi17.png");
	int hosi18 = LoadGraph("img/hosi18.png");
	int hosi19 = LoadGraph("img/hosi19.png");
	int hosi20 = LoadGraph("img/hosi20.png");
	int hosi21 = LoadGraph("img/hosi21.png");
	int hosi22 = LoadGraph("img/hosi22.png");
	int hosi23 = LoadGraph("img/hosi23.png");
	int hosi24 = LoadGraph("img/hosi24.png");
	int hosi25 = LoadGraph("img/hosi25.png");
	int hosi26 = LoadGraph("img/hosi26.png");
	int hosi27 = LoadGraph("img/hosi27.png");
	int hosi28 = LoadGraph("img/hosi28.png");
	int hosi29 = LoadGraph("img/hosi29.png");
	int hosi30 = LoadGraph("img/hosi30.png");
	int hosi31 = LoadGraph("img/hosi31.png");
	int hosi32 = LoadGraph("img/hosi32.png");
	
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
		Position2 pos;//ç¿ïW
		Vector2 vel;//ë¨ìx
		bool isActive = false;//ê∂Ç´ÇƒÇÈÇ©Å`ÅH
	};

	struct PlayerBullet {
		Position2 pos;//ç¿ïW
		Vector2 vel;//ë¨ìx
		bool isActive = false;//ê∂Ç´ÇƒÇÈÇ©Å`ÅH
	};

	int mekakusiposx = 0;
	int mekakusiposy = -100;
	//íeÇÃîºåa
	float bulletRadius = 5.0f;

	//player
	float pbulletRadius = 5.0f;
	//é©ã@ÇÃîºåa
	float playerRadius = 10.0f;

	//ìGÇÃîºåa
	float enemyRadius = 15.0f;
	//ìKìñÇ…256å¬Ç≠ÇÁÇ¢çÏÇ¡Ç∆Ç≠
	Bullet bullets[100];
	PlayerBullet pbullets[100];

	//Position2 enemypos(320, 25);//ìGç¿ïW
	Position2 enemypos(100, -25);
	Position2 playerpos(320, 400);//é©ã@ç¿ïW

	unsigned int frame = 0;//ÉtÉåÅ[ÉÄä«óùóp

	char keystate[256];
	bool isDebugMode = false;
	int skyy = 0;
	int skyy2 = 0;
	int skyy3 = 0;
	int skyy4 = 0;
	int skyy5 = 0;
	int skyy6 = 0;
	int skyy7 = 0;
	int skyy8 = 0;
	int skyy9 = 0;
	int skyy10 = 0;
	int skyy11 = 0;
	int skyy12 = 0;
	int skyy13 = 0;
	int skyy14 = 0;
	int skyy15 = 0; 
	int skyy16 = 0;
	int skyy17 = 0;
	int skyy18 = 0;
	int skyy19 = 0;
	int skyy20 = 0;
	int skyy21 = 0;
	int skyy22 = 0;
	int skyy23 = 0;
	int skyy24 = 0;
	int skyy25 = 0;
	int skyy26 = 0;
	int skyy27 = 0;
	int skyy28 = 0;
	int skyy29 = 0;
	int skyy30 = 0;
	int skyy31 = 0;
	int skyy32 = 0;
	int skyy33 = 0;
	int skyy34 = 0;
	int skyy35 = 0;
	int skyy36 = 0;
	int skyy37 = 0;
	int skyy38 = 0;
	int skyy39 = 0;
	int skyy40 = 0;
	int skyy41 = 0;



	int bgidx = 0;


	int spi = 1;
	//	int tomegu = 0;
	int tama = bulletH;
	int tamaP = playerblle;

	int plyertama = 0;

	bool tamaflog = false;

	//////////////////////////////////////////
	//îwåiån

	int px = 50;
	int py = px;;
	////////////////////////
	int px1 = 0;
	int py1 = px1;
	////////////////////////
	int px2 = 100;
	int py2 = px2;
	////////////////////////
	int px3 = 0;
	int py3 = 0;
	////////////////////////
	int px4 = 0;
	int py4 = 0;
	////////////////////////
	int px5 = 0;
	int py5 = 0;
	////////////////////////
	int px6 = 0;
	int py6 = 0;
	////////////////////////
	int px7 = 0;
	int py7 = 0;
	////////////////////////
	int px8 = 0;
	int py8 = 0;
	////////////////////////
	int px9 = 0;
	int py9 = 0;
	////////////////////////
	int px10 = 0;
	int py10 = 0;
	////////////////////////
	int px11 = 0;
	int py11 = 0;
	////////////////////////
	int px12 = 0;
	int py12 = 0;
	////////////////////////
	int px13 = 0;
	int py13 = 0;
	////////////////////////
	int px14 = 0;
	int py14 = 0;
	////////////////////////
	int px15 = 0;
	int py15 = 0;
	////////////////////////
	int px16 = 0;
	int py16 = 0;
	////////////////////////
	int px17 = 0;
	int py17 = 0;
	////////////////////////
	int px18 = 0;
	int py18 = 0;
	////////////////////////
	int px19 = 0;
	int py19 = 0;
	////////////////////////
	int px20 = 0;
	int py20 = 0;
	////////////////////////
	int px21 = 0;
	int py21 = 0;
	////////////////////////
	int px22 = 0;
	int py22 = 0;
	////////////////////////
	int px23 = 0;
	int py23 = 0;
	////////////////////////
	int px24 = 0;
	int py24 = 0;
	////////////////////////
	int px25 = 0;
	int py25 = 0;
	////////////////////////
	int px26 = 0;
	int py26 = 0;
	////////////////////////
	int px27 = 0;
	int py27 = 0;
	////////////////////////
	int px28 = 0;
	int py28 = 0;
	////////////////////////
	int px29 = 0;
	int py29 = 0;
	////////////////////////
	int px30 = 0;
	int py30 = 0;
	////////////////////////
	int px31 = 0;
	int py31 = 0;
	////////////////////////
	int px32 = 0;
	int py32 = 0;
	////////////////////////
	int px33 = 0;
	int py33 = 0;
	////////////////////////
	int px34 = 0;
	int py34 = 0;
	////////////////////////
	int px35 = 0;
	int py35 = 0;
	////////////////////////
	int px36 = 0;
	int py36 = 0;
	////////////////////////
	int px37 = 0;
	int py37 = 0;
	////////////////////////
	int px38 = 0;
	int py38 = 0;
	////////////////////////
	int px39 = 0;
	int py39 = 0;
	////////////////////////
	int px40 = 0;
	int py40 = 0;
	//int pos = 0;
	int hosisyokix;
	int hosiposx;
	int hosiposy;
	int hosisyokix1;
	////////////////////////
	int hosiposx1;
	int hosiposy1;
	////////////////////////
	int hosiposx2;
	int hosiposy2;
	////////////////////////
	int hosiposx3;
	int hosiposy3;
	////////////////////////
	int hosiposx4;
	int hosiposy4;
	////////////////////////
	int hosiposx5;
	int hosiposy5;
	////////////////////////
	int hosiposx6;
	int hosiposy6;
	////////////////////////
	int hosiposx7;
	int hosiposy7;
	////////////////////////
	int hosiposx8;
	int hosiposy8;
	////////////////////////
	int hosiposx9;
	int hosiposy9;
	////////////////////////
	int hosiposx10;
	int hosiposy10;
	////////////////////////
	int hosiposx11;
	int hosiposy11;
	////////////////////////
	int hosiposx12;
	int hosiposy12;
	////////////////////////
	int hosiposx13;
	int hosiposy13;
	////////////////////////
	int hosiposx14;
	int hosiposy14;
	////////////////////////
	int hosiposx15;
	int hosiposy15;
	////////////////////////
	int hosiposx16;
	int hosiposy16;
	////////////////////////
	int hosiposx17;
	int hosiposy17;
	////////////////////////
	int hosiposx18;
	int hosiposy18;
	////////////////////////
	int hosiposx19;
	int hosiposy19;
	////////////////////////
	int hosiposx20;
	int hosiposy20;
	////////////////////////
	int hosiposx21;
	int hosiposy21;
	////////////////////////
	int hosiposx22;
	int hosiposy22;
	////////////////////////
	int hosiposx23;
	int hosiposy23;
	////////////////////////
	int hosiposx24;
	int hosiposy24;
	////////////////////////
	int hosiposx25;
	int hosiposy25;
	////////////////////////
	int hosiposx26;
	int hosiposy26;
	////////////////////////
	int hosiposx27;
	int hosiposy27;
	////////////////////////
	int hosiposx28;
	int hosiposy28;
	////////////////////////
	int hosiposx29;
	int hosiposy29;
	////////////////////////
	int hosiposx30;
	int hosiposy30;
	////////////////////////
	int hosiposx31;
	int hosiposy31;
	////////////////////////
	int hosiposx32;
	int hosiposy32;
	////////////////////////
	int hosiposx33;
	int hosiposy33;
	////////////////////////
	int hosiposx34;
	int hosiposy34;
	////////////////////////
	int hosiposx35;
	int hosiposy35;
	////////////////////////
	int hosiposx36;
	int hosiposy36;
	////////////////////////
	int hosiposx37;
	int hosiposy37;
	////////////////////////
	int hosiposx38;
	int hosiposy38;
	////////////////////////
	int hosiposx39;
	int hosiposy39;
	////////////////////////
	int hosiposx40;
	int hosiposy40;
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
		skyy2 = (skyy2 + 2) % 640;
		skyy3 = (skyy3 + 1) % 1040;
		
		
		
		
		
		
		
	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		//skyy32 = (skyy32 + 5) % 640;
		//////////////////////////////////////////////////
		px3 = 400;
		py3 = px3;
		skyy3 = (skyy3 + 1) % (640+px3+40000);
		hosiposy3 = -900;
		hosiposx3 = -40300;
		////////////////////////
		px4 = 250;
		py4 = px4;
		skyy5 = (skyy5 + 3) % (640 + px4*2+10000);
		hosiposx4=-200;
		hosiposy4=-10900;
		////////////////////////
		px5 = 50;
		py5 = px5;
		skyy6 = (skyy6 + 15) % (640 + px5+10000);
		hosiposx5=20;
		hosiposy5=-10000;
		////////////////////////
		px6 = 50;
		py6 = px6;
		skyy7 = (skyy7 + 10) % (640 + px6+500);
		hosiposx6=130;
		hosiposy6=-500;
		////////////////////////
		px7 = 10;
		py7 = px7;
		skyy8 = (skyy8 + 1) % (640 + px7+40);
		hosiposx7=30;
		hosiposy7=-40;
		////////////////////////
		px8 = 10;
		py8 = px8;
		skyy9 = (skyy9 + 1) % (640 + px8+60);
		hosiposx8=40;
		hosiposy8=-60;
		////////////////////////
		px9 = 350;
		py9 = px9;
		skyy10 = (skyy10 + 2) % (640 + px9+3900);
		hosiposx9=(px*2)*-1;
		hosiposy9=-3900;
		////////////////////////
		px10 = 30;
		py10 = px10;
		skyy11 = (skyy11 + 7) % (640 + px10+3000);
		hosiposx10=60;
		hosiposy10=-3000;
		////////////////////////
		px11 = 30;
		py11 = px11;
		skyy12 = (skyy12 + 7) % (640 + px11+3060);
		hosiposx11=120;
		hosiposy11=-3060;
		////////////////////////
		px12 = 30;
		py12 = px12;
		skyy13 = (skyy13 + 7) % (640 + px12+3000);
		hosiposx12=180;
		hosiposy12=-3000;
		////////////////////////
		px13 = 15;
		py13 = px13;
		skyy14 = (skyy14 + 1) % (640 + px13+20);
		hosiposx13=90;
		hosiposy13=-20;
		////////////////////////
		px14 = 50;
		py14 = px14;
		skyy15 = (skyy15 + 15) % (640 + px14+100000);
		hosiposx14=390;
		hosiposy14=-100000;
		////////////////////////
		px15 = 20;
		py15 = px15;
		skyy16 = (skyy16 + 3) % (640 + px15+1000);
		hosiposx15=100;
		hosiposy15=-1000;
		////////////////////////
		px16 = 50;
		py16 = px16;
		skyy17 = (skyy17 + 5) % (640 + px16+2000);
		hosiposx16=120;
		hosiposy16=-2000;
		////////////////////////
		px17 = 50;
		py17 = px17;
		skyy18 = (skyy18 + 5) % (640 + px17+500);
		hosiposx17=200;
		hosiposy17=-500;
		////////////////////////
		px18 = 20;
		py18 = px18;
		skyy19 = (skyy19 + 5) % (640 + px18+300);
		hosiposx18=140;
		hosiposy18=-300;
		////////////////////////
		px19 = 70;
		py19 = px19;
		skyy20 = (skyy20 + 8) % (640 + px19+6000);
		hosiposx19=150;
		hosiposy19=-6000;
		////////////////////////
		px20 = 20;
		py20 = px20;
		skyy21 = (skyy21 + 2) % (640 + px20+50);
		hosiposx20=160;
		hosiposy20=-50;
		////////////////////////
		px21 = 50;
		py21 = px21;
		skyy22 = (skyy22 +3) % (640 + px21+100);
		hosiposx21=200;
		hosiposy21=-100;
		////////////////////////
		px22 = 150;
		py22 = px22;
		skyy23 = (skyy23 + 5) % (640 + px22+30000);
		hosiposx22=180;
		hosiposy22=-3000;
		////////////////////////
		px23 = 50;
		py23 = px23;
		skyy24 = (skyy24 + 7) % (640 + px23+300);
		hosiposx23=300;
		hosiposy23=-300;
		////////////////////////
		px24 = 250;
		py24 = px24;
		skyy25 = (skyy25 + 2) % (640 + px24+5000);
		hosiposx24=200;
		hosiposy24=-5000;
		////////////////////////
		px25 = 50;
		py25 = px25;
		skyy26 = (skyy26 + 6) % (640 + px25+400);
		hosiposx25=230;
		hosiposy25=-400;
		////////////////////////
		px26 = 20;
		py26 = px26;
		skyy27 = (skyy27 + 3) % (640 + px26+1000);
		hosiposx26=290;
		hosiposy26=-1000;
		////////////////////////
		px27 = 35;
		py27 = px27;
		skyy28 = (skyy28 + 5) % (640 + px27+250);
		hosiposx27=450;
		hosiposy27=-250;
		////////////////////////
		px28 = 30;
		py28 = px28;
		skyy29 = (skyy29 + 2) % (640 + px28+300);
		hosiposx28=260;
		hosiposy28=-300;
		////////////////////////
		px29 = 15;
		py29 = px29;
		skyy30 = (skyy30 + 5) % (640 + px29+70);
		hosiposx29=370;
		hosiposy29=-70;
		////////////////////////
		px30 = 15;
		py30 = px30;
		skyy31 = (skyy31 + 1) % (640 + px30+50);
		hosiposx30=500;
		hosiposy30=-50;
		////////////////////////
		px31 = 15;
		py31 = px31;
		skyy32 = (skyy32 + 1) % (640 + px31 + 50);
		hosiposx31 = 450;
		hosiposy31 = -50;
		////////////////////////
		px32 = 15;
		py32 = px32;
		skyy33 = (skyy33 + 1) % (640 + px32 + 150);
		hosiposx32 = 600;
		hosiposy32 = -150;
		////////////////////////
		px33 = 15;
		py33 = px33;
		skyy34 = (skyy34 + 1) % (640 + px33 + 200);
		hosiposx33 = 480;
		hosiposy33 = -200;
		////////////////////////
		px34 = 20;
		py34 = px34;
		skyy35 = (skyy35 + 3) % (640 + px34 + 1200);
		hosiposx34 = 465;
		hosiposy34 = -1200;
		////////////////////////
		px35 = 20;
		py35 = px35;
		skyy36 = (skyy36 + 3) % (640 + px35 + 600);
		hosiposx35 = 470;
		hosiposy35= -600;
		////////////////////////
		px36 = 60;
		py36 = px36;
		skyy37 = (skyy37 + 6) % (640 + px36 + 800);
		hosiposx36 = 550;
		hosiposy36 = -800;
		////////////////////////
		px37 = 20;
		py37 = px37;
		skyy37 = (skyy38 + 2) % (640 + px37+ 100);
		hosiposx37 = 150;
		hosiposy37 = -100;
		////////////////////////
		px38 = 20;
		py38 = px38;
		skyy39 = (skyy39 + 1) % (640 + px37 + 100);
		hosiposx38 = 250;
		hosiposy38 = -100;
		////////////////////////
		px39 = 15;
		py39 = px39;
		skyy40 = (skyy40 + 1) % (640 + px39 + 200);
		hosiposx39 = 50;
		hosiposy39 = -200;
		////////////////////////
		px40 = 15;
		py40 = px39;
		skyy41 = (skyy41 + 1) % (640 + px40 + 100);
		hosiposx40 = 350;
		hosiposy40 = -100;
		/////////////////////////////////////////////////////////////////////////
		//îwåi
		DrawGraph(0, 0, haikei, true);
		
		
		DrawExtendGraph(hosiposx3 + px3, hosiposy3 + py3 + skyy3, hosiposx3 + (px3 * 2), hosiposy3 + (py3 * 2) + skyy3, hosi4, true);


		px2 = 100;
		py2=px2;
		hosiposy2 = -200;
		hosiposx2 = 300;


		DrawExtendGraph(hosiposx2 + px2, hosiposy2 + py2 + skyy2, hosiposx2 + (px2 * 2), hosiposy2 + (py2 * 2) + skyy2, hosi3, true);
		//pos=pos+GetRand(100);
		px = 30;
		py = px;
		hosiposy = -100;
		hosiposx = 500;
		


		
		
		DrawExtendGraph(hosiposx + px, hosiposy + py + skyy, hosiposx + (px * 2), hosiposy + (py * 2) + skyy, hosi1, true);
		
		





		DrawExtendGraph(hosiposx4 + px4, hosiposy4 + py4 + skyy5, hosiposx4 + (px4 * 2), hosiposy4 + (py4 * 2) + skyy5, hosi5, true);

			
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
		

			DrawExtendGraph(hosiposx5 + px5, hosiposy5 + py5 + skyy6, hosiposx5 + (px5 * 2), hosiposy5 + (py5 * 2) + skyy6, hosi6, true);
			DrawExtendGraph(hosiposx6 + px6, hosiposy6 + py6 + skyy7, hosiposx6 + (px6 * 2), hosiposy6 + (py6 * 2) + skyy7, hosi7, true);
			DrawExtendGraph(hosiposx7 + px7, hosiposy7 + py7 + skyy8, hosiposx7 + (px7 * 2), hosiposy7 + (py7 * 2) + skyy8, hosi8, true);
			DrawExtendGraph(hosiposx8 + px8, hosiposy8 + py8 + skyy9, hosiposx8 + (px8 * 2), hosiposy8 + (py8 * 2) + skyy9, hosi9, true);
			DrawExtendGraph(hosiposx9 + px9, hosiposy9 + py9 + skyy10, hosiposx9 + (px9 * 2), hosiposy9 + (py9 * 2) + skyy10, hosi10, true);
			DrawExtendGraph(hosiposx10 + px10, hosiposy10 + py10 + skyy11, hosiposx10 + (px10 * 2), hosiposy10 + (py10 * 2) + skyy11, hosi11, true);
			DrawExtendGraph(hosiposx11 + px11, hosiposy11 + py11 + skyy12, hosiposx11 + (px11 * 2), hosiposy11 + (py11 * 2) + skyy12, hosi12, true);
			DrawExtendGraph(hosiposx12 + px12, hosiposy12 + py12 + skyy13, hosiposx12 + (px12 * 2), hosiposy12 + (py12 * 2) + skyy13, hosi13, true);
			DrawExtendGraph(hosiposx13 + px13, hosiposy13 + py13 + skyy14, hosiposx13 + (px13 * 2), hosiposy13 + (py13 * 2) + skyy14, hosi14, true);
			DrawExtendGraph(hosiposx14 + px14, hosiposy14 + py14 + skyy15, hosiposx14 + (px14 * 2), hosiposy14 + (py14 * 2) + skyy15, hosi15, true);
			DrawExtendGraph(hosiposx15 + px15, hosiposy15 + py15 + skyy16, hosiposx15 + (px15 * 2), hosiposy15 + (py15 * 2) + skyy16, hosi16, true);
			DrawExtendGraph(hosiposx16 + px16, hosiposy16 + py16 + skyy17, hosiposx16 + (px16 * 2), hosiposy16 + (py16 * 2) + skyy17, hosi17, true);
			DrawExtendGraph(hosiposx17 + px17, hosiposy17 + py17 + skyy18, hosiposx17 + (px17 * 2), hosiposy17 + (py17 * 2) + skyy18, hosi18, true); 
			DrawExtendGraph(hosiposx18 + px18, hosiposy18 + py18 + skyy19, hosiposx18 + (px18 * 2), hosiposy18 + (py18 * 2) + skyy19, hosi19, true);
			DrawExtendGraph(hosiposx19 + px19, hosiposy19 + py19 + skyy20, hosiposx19 + (px19 * 2), hosiposy19 + (py19 * 2) + skyy20, hosi20, true);
			DrawExtendGraph(hosiposx20 + px20, hosiposy20 + py20 + skyy21, hosiposx20 + (px20 * 2), hosiposy20 + (py20 * 2) + skyy21, hosi21, true);
			DrawExtendGraph(hosiposx21 + px21, hosiposy21 + py21 + skyy22, hosiposx21 + (px21 * 2), hosiposy21 + (py21 * 2) + skyy22, hosi22, true);
			DrawExtendGraph(hosiposx22 + px22, hosiposy22 + py22 + skyy23, hosiposx22 + (px22 * 2), hosiposy22 + (py22 * 2) + skyy23, hosi23, true);
			DrawExtendGraph(hosiposx23 + px23, hosiposy23 + py23 + skyy24, hosiposx23 + (px23 * 2), hosiposy23 + (py23 * 2) + skyy24, hosi24, true);
			DrawExtendGraph(hosiposx24 + px24, hosiposy24 + py24 + skyy25, hosiposx24 + (px24 * 2), hosiposy24 + (py24 * 2) + skyy25, hosi25, true);
			DrawExtendGraph(hosiposx25 + px25, hosiposy25 + py25 + skyy26, hosiposx25 + (px25 * 2), hosiposy25 + (py25 * 2) + skyy26, hosi26, true);
			DrawExtendGraph(hosiposx26 + px26, hosiposy26 + py26 + skyy27, hosiposx26 + (px26 * 2), hosiposy26 + (py26 * 2) + skyy27, hosi27, true);
			DrawExtendGraph(hosiposx27 + px27, hosiposy27 + py27 + skyy28, hosiposx27 + (px27 * 2), hosiposy27 + (py27 * 2) + skyy28, hosi28, true);
			DrawExtendGraph(hosiposx28 + px28, hosiposy28 + py28 + skyy29, hosiposx28 + (px28 * 2), hosiposy28 + (py28 * 2) + skyy29, hosi29, true);
			DrawExtendGraph(hosiposx29 + px29, hosiposy29 + py29 + skyy30, hosiposx29 + (px29 * 2), hosiposy29 + (py29 * 2) + skyy30, hosi30, true);
			DrawExtendGraph(hosiposx30 + px30, hosiposy30 + py30 + skyy31, hosiposx30 + (px30 * 2), hosiposy30 + (py30 * 2) + skyy31, hosi31, true);
			DrawExtendGraph(hosiposx31 + px31, hosiposy31 + py31 + skyy32, hosiposx31 + (px31 * 2), hosiposy31 + (py31 * 2) + skyy32, hosi10, true);
			DrawExtendGraph(hosiposx32 + px32, hosiposy32 + py32 + skyy33, hosiposx32 + (px32 * 2), hosiposy32 + (py32 * 2) + skyy33, hosi21, true);
			DrawExtendGraph(hosiposx33 + px33, hosiposy33 + py33 + skyy34, hosiposx33 + (px33 * 2), hosiposy33 + (py33 * 2) + skyy34, hosi19, true);
			DrawExtendGraph(hosiposx34 + px34, hosiposy34 + py34 + skyy35, hosiposx34 + (px34 * 2), hosiposy34 + (py34 * 2) + skyy35, hosi3, true);
			DrawExtendGraph(hosiposx35 + px35, hosiposy35 + py35 + skyy36, hosiposx35 + (px35 * 2), hosiposy35 + (py35 * 2) + skyy36, hosi23, true);
			DrawExtendGraph(hosiposx36 + px36, hosiposy36 + py36 + skyy37, hosiposx36 + (px36 * 2), hosiposy36 + (py36 * 2) + skyy37, hosi27, true);
			DrawExtendGraph(hosiposx37 + px37, hosiposy37 + py37 + skyy38, hosiposx37 + (px37 * 2), hosiposy37 + (py37 * 2) + skyy38, hosi11, true);
			DrawExtendGraph(hosiposx38 + px38, hosiposy38 + py38 + skyy39, hosiposx38 + (px38 * 2), hosiposy38 + (py38 * 2) + skyy39, hosi22, true);
			DrawExtendGraph(hosiposx39 + px39, hosiposy39 + py39 + skyy40, hosiposx39 + (px39 * 2), hosiposy39 + (py39 * 2) + skyy40, hosi7, true);
			DrawExtendGraph(hosiposx40 + px40, hosiposy40 + py40 + skyy41, hosiposx40 + (px40 * 2), hosiposy40 + (py40 * 2) + skyy41, hosi28, true);

	//	DrawGraph(pos, pos, hosi2, true);

////////////////////////////////////////////////////////////////////////////////
		//ÉvÉåÉCÉÑÅ[
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
			//é©ã@ÇÃñ{ëÃ(ìñÇΩÇËîªíË)
			DrawCircle(playerpos.x, playerpos.y, playerRadius, 0xffaaaa, false, 3);
		}
		float angle = atan2(playerpos.y - enemypos.y, playerpos.x - enemypos.x);


		float pangle = atan2(enemypos.y - playerpos.y, enemypos.x - playerpos.x);
		//íeî≠éÀ

		//timecont++;
		//mekakusiposx += (GetRand(30));
		//mekakusiposy += (GetRand(30));

		//for (int i = 0; -1 < i < 3; i++) {}

		//íeÇÃçXêVÇ®ÇÊÇ—ï\é¶
		switch (tekiMode)//ìGèàóù
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
			//ìñÇΩÇ¡ÇΩîΩâûÇèëÇ¢ÇƒÇ≠ÇæÇ≥Ç¢ÅB
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
		//		//ìñÇΩÇ¡ÇΩîΩâûÇèëÇ¢ÇƒÇ≠ÇæÇ≥Ç¢ÅB
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
		//						//ìñÇΩÇ¡ÇΩîΩâûÇèëÇ¢ÇƒÇ≠ÇæÇ≥Ç¢ÅB
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
			//íeÇÃåªç›ç¿ïWÇ…íeÇÃåªç›ë¨ìxÇâ¡éZÇµÇƒÇ≠ÇæÇ≥Ç¢player
			pb.pos = pb.pos + pb.vel;
			//íeÇÃäpìxÇatan2Ç≈åvéZÇµÇƒÇ≠ÇæÇ≥Ç¢ÅBangleÇ…ílÇì¸ÇÍÇÈÇÒÇæÇÊÉIÉD
			float pangle2 = atan2(pb.vel.y, pb.vel.x);
			//player
			DrawRotaGraph(pb.pos.x, pb.pos.y, 1.0f, pangle2, tamaP, true);
			//íeÇéEÇ∑ player
			if (pb.pos.x + 16 < 0 || pb.pos.x - 16 > 640 ||
				pb.pos.y + 24 < 0 || pb.pos.y - 24 > 480) {
				pb.isActive = false;
			}
			//player
			if (isDebugMode) {
				//íeÇÃñ{ëÃ(ìñÇΩÇËîªíË)
				DrawCircle(pb.pos.x, pb.pos.y, pbulletRadius, 0x0000ff, false, 3);
			}
		}
		//DrawGraph(mekakusiposx, mekakusiposy,mekakushi, true);

		//Ç†ÇΩÇËÅI
		//Å´ÇÃIsHitÇÕé¿ëïÇèëÇ¢ÇƒÇ‹ÇπÇÒÅBé©ï™Ç≈èëÇ¢ÇƒÇ≠ÇæÇ≥Ç¢ÅB
		//if (IsHit(pb.pos, pbulletRadius,enemypos, playerRadius)) {
		//	//ìñÇΩÇ¡ÇΩîΩâûÇèëÇ¢ÇƒÇ≠ÇæÇ≥Ç¢ÅB
		//	pb.isActive = false;
		//}





		//ìG
		for (auto& b : bullets)
		{
			if (!b.isActive) {
				continue;
			}



			//íeÇÃåªç›ç¿ïWÇ…íeÇÃåªç›ë¨ìxÇâ¡éZÇµÇƒÇ≠ÇæÇ≥Ç¢
			b.pos = b.pos + b.vel;


			//íeÇÃäpìxÇatan2Ç≈åvéZÇµÇƒÇ≠ÇæÇ≥Ç¢ÅBangleÇ…ílÇì¸ÇÍÇÈÇÒÇæÇÊÉIÉD
			float angle2 = atan2(b.vel.y, b.vel.x);
			//íeÇÃåªç›ç¿ïWÇ…íeÇÃåªç›ë¨ìxÇâ¡éZÇµÇƒÇ≠ÇæÇ≥Ç¢player
			//	pb.pos = pb.pos + pb.vel;




			DrawRotaGraph(b.pos.x, b.pos.y, 1.0f, angle2, tama, true);









			//DrawGraph(mekakusiposx, mekakusiposy,mekakushi, true);
			if (isDebugMode) {
				//íeÇÃñ{ëÃ(ìñÇΩÇËîªíË)
				DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
			}



			//íeÇéEÇ∑
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
					//ìñÇΩÇ¡ÇΩîΩâûÇèëÇ¢ÇƒÇ≠ÇæÇ≥Ç¢ÅB
					b.isActive = false;
					pb.isActive = false;
				}

			}

			/*if (mekakusiposx + 16 < 0 || mekakusiposx - 16 > 640 ||
			mekakusiposy - 100 < 0 || mekakusiposy - 24 > 480) {
			mekakusiposx = 0;
			mekakusiposy = -100;
			}*/
			//Ç†ÇΩÇËÅI
			//Å´ÇÃIsHitÇÕé¿ëïÇèëÇ¢ÇƒÇ‹ÇπÇÒÅBé©ï™Ç≈èëÇ¢ÇƒÇ≠ÇæÇ≥Ç¢ÅB
			if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {
				//ìñÇΩÇ¡ÇΩîΩâûÇèëÇ¢ÇƒÇ≠ÇæÇ≥Ç¢ÅB
				b.isActive = false;
			}

			//if (IsHit(b.pos, bulletRadius, pb.pos, pbulletRadius)) {
			//	//ìñÇΩÇ¡ÇΩîΩâûÇèëÇ¢ÇƒÇ≠ÇæÇ≥Ç¢ÅB
			//	b.isActive = false;
			//	pb.isActive = false;
			//}

			/////////////////////////////////////////////////////////////////////////////
			if (IsHit(enemypos, enemyRadius, playerpos, playerRadius)) {
				//ìñÇΩÇ¡ÇΩîΩâûÇèëÇ¢ÇƒÇ≠ÇæÇ≥Ç¢ÅB
				enemypos.y = 1000;
				//playerMode = PLYER_INIT;
				//plyertama = teki;
			}


		}
		//ìGÇÃï\é¶

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
			//ìGÇÃñ{ëÃ(ìñÇΩÇËîªíË)
			DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
		}
		++frame;
		ScreenFlip();

	}

	DxLib_End();

	return 0;
}
#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<stdio.h>


#pragma comment(lib,"Winmm.lib")            
//����Windows Multimedia API
//��ý�����Ӧ�ó���ӿ�,���ڵ͵�����Ƶ����Ϸ�ֱ�


#define High 600	//����ߴ�
#define Width 800
#define enemyNum 8	//��ʼ�л�����


int gameStatus = 0;	//��Ϸ״̬��0Ϊ��ʼ�˵����棬1Ϊ������Ϸ��2Ϊ������Ϸ��3Ϊ��Ϸ��ͣ
int isExpolde = 0;  //�жϷɻ��Ƿ�ը
int score = 0;      //��Ϸ�÷�    
int plane_hp = 10, plane_mp=100;			//�ɻ���Ѫ��������
int boss_hp = 5;							//bossѪ��
float position_x, position_y;				//�ɻ�λ��
float bullet_x, bullet_y;					//�ӵ�λ��
float boss_x, boss_y;                       //bossλ��
float ebullet_x, ebullet_y;					//boss�ӵ�λ��
float laser_x, laser_y;						//�����λ��
float enemy_x[enemyNum], enemy_y[enemyNum];	//�л�λ��
IMAGE img_bk;								//����ͼƬ
IMAGE img_planeNormal1, img_planeNormal2;	//�ɻ�ͼƬ
IMAGE img_bullet1, img_bullet2;				//�ӵ�ͼƬ
IMAGE img_boss1, img_boss2;					//bossͼƬ
IMAGE img_ebullet1, img_ebullet2;			//boss�ӵ�ͼƬ
IMAGE img_laser1, img_laser2;				//����ͼƬ
IMAGE img_enemyPlane1, img_enemyPlane2;		//�л�ͼƬ
IMAGE img_planeExplode1, img_planeExplode2;	//��ը��ķɻ�ͼƬ


void startMenu();                          //��ʼ���˵�����
void pauseMenu();                          //��ͣʱ�˵�����
void readRecordFile();                     //��ȡ��Ϸ�浵
void writeRecordFile();                    //������Ϸ�浵
void startup();                            //������Ϸ���ݳ�ʼ��
void show();                               //��ʾ����
void updateWithoutInput();                 //������޹صĸ���
void updateWithInput();                    //������йصĸ���
void gameover();                           //��Ϸ������������


void startMenu() {	//��ʼ���˵�����
	putimage(0, 0, &img_bk);
	setbkmode(TRANSPARENT);  //������͸����
	settextcolor(RED);       //������ɫ
	settextstyle(50, 0, _T("����"));  //������ʽ�ʹ�С
	outtextxy(int(Width * 0.34), int(High * 0.05), "�� �� ս ��");
	
    settextcolor(RED);
	settextstyle(40, 0, _T("����"));
	outtextxy(int(Width * 0.38), int(High * 0.2), "1 ��ʼ��Ϸ");
	outtextxy(int(Width * 0.38), int(High * 0.3), "2 ��ȡ�浵");
	outtextxy(int(Width * 0.38), int(High * 0.4), "3 �˳���Ϸ");
	
	settextcolor(GREEN);
	settextstyle(30, 0, _T("����"));
    outtextxy(int(Width * 0.4), int(High * 0.55), "|��Ϸ˵��|");
	settextcolor(BLUE);
	settextstyle(30, 0, _T("����"));
	outtextxy(int(Width * 0.35), int(High * 0.6), "�����Ʒɻ��ƶ�");
	outtextxy(int(Width * 0.35), int(High * 0.65), "�����������ӵ�");
	outtextxy(int(Width * 0.35), int(High * 0.7), "����Ҽ����伤����������");
	outtextxy(int(Width * 0.35), int(High * 0.75), "Esc��ͣ��Ϸ");
	outtextxy(int(Width * 0.35), int(High * 0.8), "ʧ�ܺ�����ͣҳ��ص��˵������¿�ʼ");

	FlushBatchDraw();  //�����������ִ��δ��ɵĻ�������
	Sleep(2);

	char input;
	if (kbhit()) {	//��������
		input = getch();
		if (input == '1')
			gameStatus = 1;  //��ʼ����Ϸ
		else if (input == '2') {
			readRecordFile();
			gameStatus = 1;
		}                   //��ȡ��Ϸ�浵
		else if (input == '3') {
			gameStatus = 2;
			exit(0);
		}
	}
}

void pauseMenu() {	//��Ϸ��ͣ��Ĳ˵�ҳ�棨��Esc������
	putimage(0, 0, &img_bk);
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(50, 0, _T("����"));
	outtextxy(int(Width * 0.35), int(High * 0.2), "1 ������Ϸ");
	outtextxy(int(Width * 0.35), int(High * 0.3), "2 �������");
	outtextxy(int(Width * 0.35), int(High * 0.4), "3 �ص��˵�");
    outtextxy(int(Width * 0.35), int(High * 0.5), "4 �˳���Ϸ");
	settextcolor(GREEN);
	settextstyle(30, 0, _T("����"));
    outtextxy(int(Width * 0.35), int(High * 0.6), "|��Ϸ˵��|");
    settextcolor(BLUE);
	settextstyle(30, 0, _T("����"));
	outtextxy(int(Width * 0.35), int(High * 0.65), "�����Ʒɻ��ƶ�");
	outtextxy(int(Width * 0.35), int(High * 0.7), "�����������ӵ�");
	outtextxy(int(Width * 0.35), int(High * 0.75), "Esc����ͣ��Ϸ");
	outtextxy(int(Width * 0.35), int(High * 0.8), "ʧ�ܺ�����ͣҳ��ص��˵������¿�ʼ");

	FlushBatchDraw();
	Sleep(2);

	char input;
	if (kbhit()) {	//��������
		input = getch();
		if (input == '1')
			gameStatus = 1;  //������Ϸ
		else if (input == '2') {
			writeRecordFile();
			gameStatus = 1;
		}                   //�������
		
		else if (input == '3') {
			gameStatus = 0;
		       //�ص��˵�
		}
		else if (input == '4') {
			gameStatus = 2;
			exit(0);       //�˳���Ϸ
		}
       
	}
}

void readRecordFile() {	//����
	FILE* fp;
	fp = fopen(".\\gameRecord\\gameRecord.dat", "r");
	fscanf(fp, "%f %f %f %f %f %f %f %f %d %d %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &position_x, &position_y, &bullet_x, &bullet_y, &ebullet_x, &ebullet_y,&boss_x, &boss_y,&isExpolde,&score,&plane_hp ,&plane_mp,&boss_hp,&enemy_x[0],&enemy_x[1],&enemy_x[2],&enemy_x[3],&enemy_x[4],&enemy_x[5],&enemy_x[6],&enemy_x[7],&enemy_y[0],&enemy_y[1],&enemy_y[2],&enemy_y[3],&enemy_y[4],&enemy_y[5],&enemy_y[6],&enemy_y[7]);
	fclose(fp);
}

void writeRecordFile() { //�浵
	FILE* fp;
	fp = fopen(".\\gameRecord\\gameRecord.dat", "w");
	fprintf(fp, "%f %f %f %f %f %f %f %f %d %d %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", position_x, position_y,  bullet_x, bullet_y, ebullet_x, ebullet_y,boss_x, boss_y,isExpolde, score,plane_hp , plane_mp,boss_hp,enemy_x[0],enemy_x[1],enemy_x[2],enemy_x[3],enemy_x[4],enemy_x[5],enemy_x[6],enemy_x[7],enemy_y[0],enemy_y[1],enemy_y[2],enemy_y[3],enemy_y[4],enemy_y[5],enemy_y[6],enemy_y[7]);
	fclose(fp);
}

void startup() {                                                                //������Ϸ�ĳ�ʼ��
	mciSendString("open .\\bgm\\game_music.mp3 alias bkmusic", NULL, 0, NULL);	//�򿪱�������
	mciSendString("play bkmusic repeat", NULL, 0, NULL);	//ѭ������

	initgraph(Width, High);	//��ȡ���ھ��,��ʼ����ͼ����
	HWND hwnd = GetHWnd();	//���ô��ڱ�������
	SetWindowText(hwnd, "����ս�� By �����Ϧ��");

	loadimage(&img_bk, ".\\image\\background.jpg");                       //����ͼƬ
	loadimage(&img_planeNormal1, ".\\image\\planeNormal_1.jpg");
	loadimage(&img_planeNormal2, ".\\image\\planeNormal_2.jpg");
	loadimage(&img_bullet1, ".\\image\\bullet1.jpg");
	loadimage(&img_bullet2, ".\\image\\bullet2.jpg");
	loadimage(&img_laser1, ".\\image\\laser1.jpg");
	loadimage(&img_laser2, ".\\image\\laser2.jpg");
	loadimage(&img_ebullet1, ".\\image\\bullet1.jpg");
	loadimage(&img_ebullet2, ".\\image\\bullet2.jpg");
	loadimage(&img_enemyPlane1, ".\\image\\enemyPlane3.jpg");
	loadimage(&img_enemyPlane2, ".\\image\\enemyPlane4.jpg");
	loadimage(&img_boss1, ".\\image\\boss1.jpg");
	loadimage(&img_boss2, ".\\image\\boss2.jpg");
	loadimage(&img_planeExplode1, ".\\image\\planeExplode_1.jpg");
	loadimage(&img_planeExplode2, ".\\image\\planeExplode_2.jpg");


	position_x = int(Width * 0.5);                                //��Ϸ���ݳ�ʼ��
	position_y = int(High * 0.7);
	bullet_x = position_x;
	bullet_y = -85;
	laser_x = 1001;
	laser_y = 1001;
	ebullet_x = 1000;
	ebullet_y = 1000;
	int i;
	for (i = 0; i < enemyNum; i++) {		//���ض�ܵл�
		enemy_x[i] = rand() % Width;        //������ɵл�
		enemy_y[i] = 10;
	}
	boss_x = -1000, boss_y = -1000;//����boss
	BeginBatchDraw();              //���ڿ�ʼ������ͼ��ִ�к��κλ�ͼ����������ʱ���������Ļ�ϣ�
	                               //ֱ��ִ�� FlushBatchDraw �� EndBatchDraw �Ž�֮ǰ�Ļ�ͼ���

	while (gameStatus == 0)
		startMenu();	//��ʼ���˵�ҳ��
}

void show() {
    while (gameStatus == 0)         //�ص����˵��Ĺ���
	{ 
	plane_hp = 10;
   	plane_mp = 100;			
    boss_hp = 5;
    score= 0;
    isExpolde = 0;
	position_x = int(Width * 0.5);                                
	position_y = int(High * 0.7);
	bullet_x = position_x;
	bullet_y = -85;
	laser_x = 1001;
	laser_y = 1001;
	ebullet_x = 1000;
	ebullet_y = 1000;
	int i;
	for (i = 0; i < enemyNum; i++) {	
	enemy_x[i] = rand() % Width;       
	enemy_y[i] = 10;
	}
	boss_x = -1000, boss_y = -1000;
	BeginBatchDraw();
	while (gameStatus == 0)
		startMenu();	
}	
	
	while (gameStatus == 3)	//��ͣҳ����ʾ
		pauseMenu();

	putimage(0, 0, &img_bk);	//��ʾ����
	if (isExpolde == 0) {
		//��ʾ�ɻ�
		putimage(int(position_x - 50), int(position_y - 60), &img_planeNormal1, NOTSRCERASE);     //ʹ������ͼƬ��ɫ��� ,��ɫ�����͸��
		putimage(int(position_x - 50), int(position_y - 60), &img_planeNormal2, SRCINVERT);       //������ǰ,��Ϊ����, ԭͼ�ں�
		//��ʾ�ӵ�
		putimage(int(bullet_x - 7), int(bullet_y), &img_bullet1, NOTSRCERASE);
		putimage(int(bullet_x - 7), int(bullet_y), &img_bullet2, SRCINVERT);
		//��ʾ�л��ӵ�
		putimage(int(ebullet_x - 7), int(ebullet_y), &img_ebullet1, NOTSRCERASE);
		putimage(int(ebullet_x - 7), int(ebullet_y), &img_ebullet2, SRCINVERT);
		//��ʾ����
		putimage(int(laser_x), int(laser_y), &img_laser2, NOTSRCERASE);
		putimage(int(laser_x), int(laser_y), &img_laser1, SRCINVERT);
		//��ʾ�л�
		int i;
		for (i = 0; i < enemyNum; i++) {
			putimage(int(enemy_x[i]), int(enemy_y[i]), &img_enemyPlane1, NOTSRCERASE);
			putimage(int(enemy_x[i]), int(enemy_y[i]), &img_enemyPlane2, SRCINVERT);
		}
		//��ʾboss
		putimage(int(boss_x), int(boss_y), &img_boss2, NOTSRCERASE);
		putimage(int(boss_x), int(boss_y), &img_boss1, SRCINVERT);
	}
	else {
		//��ʾ��ը�˵ķɻ�
		putimage(int(position_x - 50), int(position_y - 60), &img_planeExplode1, NOTSRCERASE);
		putimage(int(position_x - 50), int(position_y - 60), &img_planeExplode2, SRCINVERT);
	    settextcolor(BLUE);
	settextstyle(60, 0, _T("����"));
	outtextxy(Width * 0.15, High * 0.35, "�����ն�");
    outtextxy(Width * 0.15, High * 0.45, "�����밴ESC������������"); 
	}

	settextcolor(YELLOW);
	settextstyle(20, 0, _T("����"));
	outtextxy(Width * 0.75, High * 0.85, "��ǰ�÷֣�");	//�������
	outtextxy(Width * 0.75, High * 0.90, "��ǰѪ����");
	outtextxy(Width * 0.75, High * 0.95, "��ǰ������");
	char s[5], h[5], m[5];
	sprintf(s, "%d", score);                            //��һ����ʽ�����ַ��������һ��Ŀ���ַ����в��������
	sprintf(h, "%d", plane_hp);
	sprintf(m, "%d", plane_mp);
    settextcolor(RED);
	settextstyle(20, 0, _T("����"));
	outtextxy(Width * 0.90, High * 0.85, s);
	outtextxy(Width * 0.90, High * 0.90, h);
	outtextxy(Width * 0.90, High * 0.95, m);

	FlushBatchDraw();
	Sleep(2);
}

void updateWithoutInput() {
	if (isExpolde == 0) {
		if (bullet_y > -25)			//�ӵ��ٶ�
			bullet_y = bullet_y - 2;
		if (ebullet_y < 1000)			//�л��ӵ��ٶ�
			ebullet_y = ebullet_y + 2;
		if ((score == 25 || score % 15== 0) && (score != 0)) {	//ÿ�ﵽ15�ֻ�ˢ��boss
			int k = 50;
			boss_x = k + score;
			boss_y = 10;
			ebullet_x = boss_x + 100;
			ebullet_y = boss_y;
		}
		int i;
	    float va=0.5;
		for (i = 0; i < enemyNum; i++) {	//�л��ٶ�
			if (enemy_y[i] < High - 25)
			{	enemy_y[i] = enemy_y[i] + va;}
			else
			{    enemy_y[i] = 10;
			enemy_x[i] = rand() % Width;}
        if ((score % 30== 0) && (score != 0)) //ÿ�ﵽ30�֣��л��ٶ�ͻȻ�ӿ죬��Ҫ����һ���л��ָ�����
		{va=va+0.3;}
        if (abs(bullet_x - enemy_x[i]) + abs(bullet_y - enemy_y[i]) < 50) {	//���ӵ����ел�+1���һָ�1������
				enemy_x[i] = rand() % Width;
				enemy_y[i] = 10;
				bullet_y = -85;
				mciSendString("close gemusic", NULL, 0, NULL);	//�ر�ǰ��һ�ε�����
				mciSendString("open .\\bgm\\gotEnemy.mp3 alias gemusic", NULL, 0, NULL);
				mciSendString("play gemusic", NULL, 0, NULL);	//������һ��
				score++;
                plane_mp++;
				if (boss_x < 590 && score>0 && score % 2 == 0) {	//ÿ��2��boss����һ���ӵ����ƶ�һ��
					boss_x = boss_x + 100;
					ebullet_x = boss_x + 100;
					ebullet_y = boss_y;
					if (boss_x > 590)
						boss_x = 0;
				}
			}
			if ((laser_x >= enemy_x[i] - 50) && (laser_x <= enemy_x[i] + 50)) {	//��������ел��ָ�1��Ѫ����Ѫ������Ϊ10��
				enemy_x[i] = rand() % Width;
				enemy_y[i] = 10;
                if(plane_hp<10)
				{	plane_hp++;}


				mciSendString("close gemusic", NULL, 0, NULL);	//�ر�ǰ��һ�ε�����
				mciSendString("open .\\bgm\\gotEnemy.mp3 alias gemusic", NULL, 0, NULL);
				mciSendString("play gemusic", NULL, 0, NULL);	//������һ��
				score++;
				if (boss_x < 590 && score>0 && score % 2 == 0) {	//ÿ��2��boss����һ���ӵ���boss�ƶ�һ��
					boss_x = boss_x + 100;
					ebullet_x = boss_x + 100;
					ebullet_y = boss_y;
					if (boss_x > 590)
						boss_x = 0;
				}
			}
			if ((abs(bullet_x - boss_x-70)+ abs(bullet_y - boss_y-70) < 100) || ((laser_x >= boss_x - 120) && (laser_x <= boss_x + 120))) {	//������boss+10��
				boss_hp--;
				bullet_y = -85;
				mciSendString("close gemusic", NULL, 0, NULL);	//�ر�ǰ��һ�ε�����
				mciSendString("open .\\bgm\\gotEnemy.mp3 alias gemusic", NULL, 0, NULL);
				mciSendString("play gemusic", NULL, 0, NULL);	//������һ��
				if (boss_hp == 0) {
					score += 10;
					boss_x = -1000;
					boss_y = -1000;
					boss_hp = 5;
				}
				else {	//����boss��boss�ƶ��������ӵ�
					boss_x = boss_x + 100;
					ebullet_x = boss_x + 100;
					ebullet_y = boss_y;
					if (boss_x > 590)
						boss_x = 0;
				}
			}

			if ((abs(position_x - enemy_x[i]) + abs(position_y - enemy_y[i]) < 80) || (abs(position_x - ebullet_x) + abs(position_y - ebullet_y) < 80)) {	//���һ�ײ�ϵл���boss���ӵ�
				plane_hp--;
				if (plane_hp == 0) {
					isExpolde = 1;
					mciSendString("close exmusic", NULL, 0, NULL);	//�ر�ǰ��һ�ε�����
					mciSendString("open .\\bgm\\explode.mp3 alias exmusic", NULL, 0, NULL);
					mciSendString("play exmusic", NULL, 0, NULL);	//������һ��
				}
				else if (abs(position_x - enemy_x[i]) + abs(position_y - enemy_y[i]) < 80) {
					enemy_x[i] = rand() % Width;
					enemy_y[i] = -40;
					mciSendString("close gemusic", NULL, 0, NULL);	//�ر�ǰ��һ�ε�����
					mciSendString("open .\\bgm\\peng.mp3 alias gemusic", NULL, 0, NULL);
					mciSendString("play gemusic", NULL, 0, NULL);	//������һ��
				}
				else if (abs(position_x - ebullet_x) + abs(position_y - ebullet_y) < 80) {
					ebullet_y = 1000;
					mciSendString("close gemusic", NULL, 0, NULL);	//�ر�ǰ��һ�ε�����
					mciSendString("open .\\bgm\\peng.mp3 alias gemusic", NULL, 0, NULL);
					mciSendString("play gemusic", NULL, 0, NULL);	//������һ��
				}
			}
		}
		laser_x = 1001;
	}
}

void updateWithInput() {
	if (isExpolde == 0) {
		MOUSEMSG m;	//���������Ϣ
		while (MouseHit()) {	//����Ƿ��û����
			m = GetMouseMsg();
			if (m.uMsg == WM_MOUSEMOVE) {
				//���ɻ��Ƶ����λ��
				position_x = m.x;
				position_y = m.y;
			}
			else if (m.uMsg == WM_LBUTTONDOWN) {
				//������������ӵ�
				bullet_x = position_x;
				bullet_y = position_y - 85;
				mciSendString("close fgmusic", NULL, 0, NULL);	//�ر�ǰ��һ�ε�����
				mciSendString("open .\\bgm\\f_gun.mp3 alias fgmusic", NULL, 0, NULL);
				mciSendString("play fgmusic", NULL, 0, NULL);	//������һ��
			}
			else if (m.uMsg == WM_RBUTTONDOWN && plane_mp > 9) {
				//�����Ҽ����伤��
				laser_x = position_x - 40;
				laser_y = -30;
				plane_mp -= 10;	//������10��
				mciSendString("close fgmusic", NULL, 0, NULL);	//�ر�ǰ��һ�ε�����
				mciSendString("open .\\bgm\\f_gun.mp3 alias fgmusic", NULL, 0, NULL);
				mciSendString("play fgmusic", NULL, 0, NULL);	//������һ��
			}
		}
	}

	char input;
	if (kbhit()) {	//�ж��Ƿ�������
		input = getch();
		if (input == 27)	//�ж��Ƿ���Esc����ASCII��ֵΪ27����ͣ
			gameStatus = 3;
	}
}

void gameover() {
	EndBatchDraw();
	getch();
	closegraph();
}

int main() {
	startup();					//��ʼ��
while (1)
{   show();					//��ʾ����						
	updateWithoutInput();	//������޹صĸ���
	updateWithInput();		//������йصĸ���
	}
	gameover();					//��Ϸ��������к�������
	return 0;
}

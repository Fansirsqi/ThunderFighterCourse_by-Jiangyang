<center><img src="https://cdn.jsdelivr.net/gh/Fansirsqi/blog-Images@main/images/202208301033753.png"/></center>



<center><h1>河北大学</h1></center>

<center><h2>C课程设计报告</h2></center>

### 题目：雷霆战机

<center><p>学院：电子信息工程学院<br>
专  业：  通信工程<br>
组长学号：  20211804091<br>
组长姓名：  江阳<br>
组员学号：  20211804039<br>
组员姓名：  蔺卫坤<br>
指导教师：  郄建敏<br>
2022年   6 月   16 日</p></center>

## 一.问题描述以及系统分析

### 1.1 问题描述

设计一个飞机类的游戏，玩家操控飞机对敌机发射子弹，子弹击中敌机后敌机消失，玩家获得1分，敌机碰到飞机后玩家血量减少1点，并加入boss的设定，玩家获得一定数量的积分后boss出现并且能对飞机发射子弹，boss子弹击中飞机后玩家血量减少一点，boss的血量设定为5点，玩家需要子弹命中5次boss消失同时玩家获得10分。然后在这个基础上加上蓝量的设定，飞机能发射激光消耗10点蓝量。同时蓝量和血量都能通过击败敌机获得。血量为0点时，飞机炸毁游戏结束。其他有关游戏的设定因为篇幅有限这里省略。玩家可以通过鼠标和键盘对游戏进行控制和操作，并且实现三种界面的切换，并且能够完成游戏的读档和存档操作，应用图片和音乐对游戏进行包装美化，增加玩家对游戏的体验和感受。

### 1.2. 系统分析

由于该飞机游戏功能过于复杂，本着减少开发难度的目的，我们先利用函数封装的思想设计一个合理的游戏框架对游戏进行模块化处理。然后丰富游戏各个模块内容即可，各种功能都放在封装函数之中，让程序的代码更加合理清晰。
#### 游戏框架

![](https://cdn.jsdelivr.net/gh/Fansirsqi/blog-Images@main/images/202208301044735.png)

#### 相关函数与全局变量

![](https://cdn.jsdelivr.net/gh/Fansirsqi/blog-Images@main/images/202208301044496.png)

![](https://cdn.jsdelivr.net/gh/Fansirsqi/blog-Images@main/images/202208301045132.png)

主要原理是通过飞机，敌机，子弹，boss，boss子弹，激光等的坐标的位置关系完成
相关的游戏效果，举个例子，如果敌机的位置与子弹的位置接近，就把敌机的位置重置，子弹位置则重置在我们看不到的位置，达到子弹命中敌机的效果

## 二.系统设计

### 1.11界面和切换
界面的设计是通过EasyX库进行设计的。游戏中主要分为三种游戏界面：初始菜单界面，正常游戏界面，游戏暂停界面。

#### 界面设计：

先在`startup()`初始化函数中通过`initgraph(Width, High)`获取窗口句柄,初始化绘图环境。`putimage(0, 0, &img_bk)`将图片`img_bk`作为界面背景，`settextcolor(RED)`将字体颜色设置为红色，`settextstyle(50, 0, _T("宋体"))`设计字体样式大小`outtextxy(int(Width * 0.34)`, `int(High * 0.05)`, "雷 霆 战 机")在图片特定的位置上输出这四个字。

#### 界面切换:

通过定义一个全局变量`int gameStatus = 0`;了解游戏状态：
`0`为菜单界面，
`1`为正常游戏，
`2`为结束游戏，
`3`为游戏暂停。
当进行相关按键操作后，`gameStatus`的值会发生改变从而完成界面的切换。

#### 1.12功能和设定

这里主要讲的是玩游戏过程中的功能和设定。

#### 移动与命中

包括敌机，`boss`，子弹，激光，飞机的移动。下面以子弹和敌机的移动与命中为例。

`if (bullet_y > -25)`         //子弹速度

`bullet_y = bullet_y - 2`

当子弹与敌机的距离小到一定程度时，子弹移动到我们看不到的位置，敌机利用染得rand()函数进行随机刷新。
```cpp
if (abs(bullet_x - enemy_x[i]) + abs(bullet_y - enemy_y[i]) < 50) {
enemy_x[i] = rand() % Width;
enemy_y[i] = 10;
bullet_y = -85;
```
敌机被击中后也会重新随机刷新在地图中。
```cpp
float va=0.5;
for (i = 0; i < enemyNum; i++) { 
if (enemy_y[i] < High - 25){enemy_y[i] = enemy_y[i] + va;}
else{enemy_y[i] = 10;enemy_x[i] = rand() % Width;}
```

由于敌机是宏定义的8架飞机。

`\#define enemyNum 8`

游戏其他的移动与命中也类似。其中boss的移动是通过子弹或激光命中自己或敌机进行横向移动的，飞机的移动是玩家操控鼠标控制的，不进行过多介绍。敌机和boss都能无限刷新，boss还会发射子弹对玩家进行射击。

#### 血量，蓝量，输赢与得分
```cpp
int isExpolde = 0; //判断飞机是否爆炸

int score = 0;   //游戏得分  

int plane_hp = 10, plane_mp=100;   //飞机的血量与蓝量

int boss_hp = 5;                 //boss血量
```
当飞机的血量为0时，`isExpolde`为0，飞机坠毁游戏结束。摧毁敌机得1分，摧毁boss得10分。发动激光减少10点蓝量。子弹命中敌机恢复1点蓝量，激光命中敌机恢复1点血量，血量上限为10，蓝量没有设置上限。在完成相应操作后，将对应结果的语句加入代码中即可。

#### 游戏难度增加的额外设定

`if ((score % 30== 0) && (score != 0)) {va=va+0.3;}`其中`va=0.5`

每达到30分，敌机速度突然加快，需要击败一个敌机后游戏恢复正常

#### 1.13 控制和操作

游戏的操作分为键盘操作和鼠标操作，分别为界面切换时的操作和游戏过程中的操作。两者都在updateWithInput()函数中，即与玩家有关的更新中。其中键盘操作还存在在startMenu()，pauseMenu();函数中负责界面的切换。      

#### 键盘操作:

`char input;if (kbhit()) {input = getch();}`

即定义一个字符变量input如果检测有键盘操作利用getch()将其赋值给input，再将input的值用if进行判断，根据判断的结果改变gameStatus的值完成界面的切换。

#### 鼠标操作：

1.用鼠标控制飞机的移动 
```cpp
MOUSEMSG m;    //定义鼠标信息
while (MouseHit())  //检测是否敲击鼠标
m = GetMouseMsg(); //获得鼠标信息
if (m.uMsg == WM_MOUSEMOVE) 
{ position_x = m.x;position_y = m.y;}  
```

2.鼠标左键发射子弹
```cpp
if (m.uMsg == WM_LBUTTONDOWN)   
bullet_x = position_x;
bullet_y = position_y - 85;
```
\3. 右键发射激光
```cpp
if (m.uMsg == WM_RBUTTONDOWN && plane_mp > 9) 
laser_x = position_x - 40;
laser_y = -30; 
```
#### 1.14 图片和音效

##### 图片

所有的图片首先得在startup()函数中完成加载操作

`loadimage(&img_bk,".\\image\\background.jpg")`;其中`.\\image\\background.jpg`是图片

的相对路径，就是和源程序在同一个文件夹的image文件夹中的一个文件名叫做

background.jpg的图片。将其加载在图片变量img_bk。

用函数putimage(x, y, &img_bk);进行显示，其中x,y是坐标，代表图片的左上角。图片要移动的话则要关联相关的变量。

除背景图片外其他图片要**原图**和其遮罩图重叠进行不同要求的显示，使得更真实。

`putimage(int(enemy_x[i]), int(enemy_y[i]), &img_enemyPlane1, NOTSRCERASE);`

`putimage(int(enemy_x[i]), int(enemy_y[i]), &img_enemyPlane2, SRCINVERT);`
![](https://cdn.jsdelivr.net/gh/Fansirsqi/blog-Images@main/images/202208301053080.png)
![](https://cdn.jsdelivr.net/gh/Fansirsqi/blog-Images@main/images/202208301054434.png)

##### 音乐
```cpp
#pragma comment(lib,"Winmm.lib")            
//引用Windows Multimedia API
//背景音乐在游戏开始startup()函数时进行循环播放。
mciSendString("open .\\bgm\\game_music.mp3 alias bkmusic", NULL, 0, NULL);	
mciSendString("play bkmusic repeat", NULL, 0, NULL); 
//其他音乐在完成对应操作后进行一次播放。
mciSendString("close gemusic", NULL, 0, NULL);	//关闭前面一次的音乐
mciSendString("open .\\bgm\\gotEnemy.mp3 alias gemusic", NULL, 0, NULL);
mciSendString("play gemusic", NULL, 0, NULL);	//仅播放一次
//音乐的读取也是采用相对路径。
```
#### 1.15存档和读档
利用文件夹进行保存和读取，文件夹的位置同样采用相对路径。
##### 存档
```cpp
void writeRecordFile() { //存档
FILE* fp;
fp = fopen(".\\gameRecord\\gameRecord.dat", "w");
fprintf(fp,"%f %f %f %f %f %f %f %f %d %d %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", position_x, position_y,  bullet_x, bullet_y, ebullet_x, ebullet_y,boss_x,boss_y,isExpolde,score,plane_hp ,plane_mp,boss_hp,enemy_x[0],enemy_x[1],enemy_x[2],enemy_x[3],enemy_x[4],enemy_x[5],enemy_x[6],enemy_x[7],enemy_y[0],enemy_y[1],enemy_y[2],enemy_y[3],enemy_y[4],enemy_y[5],enemy_y[6],enemy_y[7]);fclose(fp);}
```
将游戏过程中的所有数据保存在`gameRecord.dat`文件中。

##### 读档
```cpp
void readRecordFile() {	//读档
FILE* fp;
fp = fopen(".\\gameRecord\\gameRecord.dat", "r");
fscanf(fp,"%f %f %f %f %f %f %f %f %d %d %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &position_x, &position_y, &bullet_x, &bullet_y, &ebullet_x, &ebullet_y,&boss_x,&boss_y,&isExpolde,&score,&plane_hp ,&plane_mp,&boss_hp,&enemy_x[0],&enemy_x[1],&enemy_x[2],&enemy_x[3],&enemy_x[4],&enemy_x[5],&enemy_x[6],&enemy_x[7],&enemy_y[0],&enemy_y[1],&enemy_y[2],&enemy_y[3],&enemy_y[4],&enemy_y[5],&enemy_y[6],&enemy_y[7]);fclose(fp);}
```
从`gameRecord.dat`读取相关数据，后续再将`gameStatus`的值设置为1后进入游戏界面即可。
#### 1.2部分模块流程图
![](https://cdn.jsdelivr.net/gh/Fansirsqi/blog-Images@main/images/202208301057919.png)
通过`int gameStatus = 0`控制游戏状态：
0为初始菜单界面
1为正常游戏
2为结束游戏
3为游戏暂停
![](https://cdn.jsdelivr.net/gh/Fansirsqi/blog-Images@main/images/202208301057737.png)

## 三.程序源代码及分析

```cpp
#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<stdio.h>
#pragma comment(lib,"Winmm.lib")            
//引用Windows Multimedia API
//多媒体相关应用程序接口,用于低档的音频和游戏手柄
#define High 600	//画面尺寸
#define Width 800
#define enemyNum 8	//初始敌机数量
int gameStatus = 0;
//游戏状态：0位初始菜单界面，1为正常游戏，2为结束游戏，3为游戏暂停
int isExpolde = 0;
//判断飞机是否爆炸
int score = 0;
//游戏得分    
int plane_hp = 10, plane_mp=100;
//飞机的血量与蓝量
int boss_hp = 5;
//boss血量
float position_x, position_y;
//飞机位置
float bullet_x, bullet_y;
//子弹位置
float boss_x, boss_y;
//boss位置
float ebullet_x, ebullet_y;
//boss子弹位置
float laser_x, laser_y;
//激光的位置
float enemy_x[enemyNum], enemy_y[enemyNum];
//敌机位置
IMAGE img_bk;
//背景图片
IMAGE img_planeNormal1, img_planeNormal2;
//飞机图片
IMAGE img_bullet1, img_bullet2;
//子弹图片
IMAGE img_boss1, img_boss2;
//boss图片
IMAGE img_ebullet1, img_ebullet2;
//boss子弹图片
IMAGE img_laser1, img_laser2;
//激光图片
IMAGE img_enemyPlane1, img_enemyPlane2;
//敌机图片
IMAGE img_planeExplode1, img_planeExplode2;
//爆炸后的飞机图片
void startMenu();
//初始化菜单界面
void pauseMenu();
//暂停时菜单界面
void readRecordFile();
//读取游戏存档
void writeRecordFile();
//保存游戏存档
void startup();
//进行游戏数据初始化
void show();
//显示画面
void updateWithoutInput();
//与玩家无关的更新
void updateWithInput();
//与玩家有关的更新
void gameover();
//游戏结束后续处理
void startMenu() {
	//初始化菜单界面
	putimage(0, 0, &img_bk);
	setbkmode(TRANSPARENT);
	//背景是透明的
	settextcolor(RED);
	//字体颜色
	settextstyle(50, 0, _T("宋体"));
	//字体样式和大小
	outtextxy(int(Width * 0.34), int(High * 0.05), "雷 霆 战 机");
	settextcolor(RED);
	settextstyle(40, 0, _T("黑体"));
	outtextxy(int(Width * 0.38), int(High * 0.2), "1 开始游戏");
	outtextxy(int(Width * 0.38), int(High * 0.3), "2 读取存档");
	outtextxy(int(Width * 0.38), int(High * 0.4), "3 退出游戏");
	settextcolor(GREEN);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(int(Width * 0.4), int(High * 0.55), "|游戏说明|");
	settextcolor(BLUE);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(int(Width * 0.35), int(High * 0.6), "鼠标控制飞机移动");
	outtextxy(int(Width * 0.35), int(High * 0.65), "鼠标左键发射子弹");
	outtextxy(int(Width * 0.35), int(High * 0.7), "鼠标右键发射激光消耗蓝量");
	outtextxy(int(Width * 0.35), int(High * 0.75), "Esc暂停游戏");
	outtextxy(int(Width * 0.35), int(High * 0.8), "失败后按任意键重新开始");
	FlushBatchDraw();
	//这个函数用于执行未完成的绘制任务
	Sleep(2);
	char input;
	if (kbhit()) {
		//键盘输入
		input = getch();
		if (input == '1')
					gameStatus = 1;
		//开始新游戏 else if (input == '2') {
			readRecordFile();
			gameStatus = 1;
		}
		//读取游戏存档 else if (input == '3') {
			gameStatus = 2;
			exit(0);
		}
	}
}
void pauseMenu() {
	//游戏暂停后的菜单页面（按Esc启动）
	putimage(0, 0, &img_bk);
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(int(Width * 0.35), int(High * 0.2), "1 继续游戏");
	outtextxy(int(Width * 0.35), int(High * 0.3), "2 保存进度");
	outtextxy(int(Width * 0.35), int(High * 0.4), "3 回到菜单");
	outtextxy(int(Width * 0.35), int(High * 0.5), "4 退出游戏");
	settextcolor(GREEN);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(int(Width * 0.35), int(High * 0.6), "|游戏说明|");
	settextcolor(BLUE);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(int(Width * 0.35), int(High * 0.65), "鼠标控制飞机移动");
	outtextxy(int(Width * 0.35), int(High * 0.7), "鼠标左键发射子弹");
	outtextxy(int(Width * 0.35), int(High * 0.75), "Esc键暂停游戏");
	outtextxy(int(Width * 0.35), int(High * 0.8), "失败后按任意键重新开始");
	FlushBatchDraw();
	Sleep(2);
	char input;
	if (kbhit()) {
		//键盘输入
		input = getch();
		if (input == '1')
					gameStatus = 1;
		//继续游戏 else if (input == '2') {
			writeRecordFile();
			gameStatus = 1;
		}
		//保存进度 else if (input == '3') {
			gameStatus = 0;
			//回到菜单
		} else if (input == '4') {
			gameStatus = 2;
			exit(0);
			//退出游戏
		}
	}
}
void readRecordFile() {
	//读档
	FILE* fp;
	fp = fopen(".\\gameRecord\\gameRecord.dat", "r");
	fscanf(fp, "%f %f %f %f %f %f %f %f %d %d %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &position_x, &position_y, &bullet_x, &bullet_y, &ebullet_x, &ebullet_y,&boss_x, &boss_y,&isExpolde,&score,&plane_hp ,&plane_mp,&boss_hp,&enemy_x[0],&enemy_x[1],&enemy_x[2],&enemy_x[3],&enemy_x[4],&enemy_x[5],&enemy_x[6],&enemy_x[7],&enemy_y[0],&enemy_y[1],&enemy_y[2],&enemy_y[3],&enemy_y[4],&enemy_y[5],&enemy_y[6],&enemy_y[7]);
	fclose(fp);
}
void writeRecordFile() {
	//存档
	FILE* fp;
	fp = fopen(".\\gameRecord\\gameRecord.dat", "w");
	fprintf(fp, "%f %f %f %f %f %f %f %f %d %d %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", position_x, position_y,  bullet_x, bullet_y, ebullet_x, ebullet_y,boss_x, boss_y,isExpolde, score,plane_hp , plane_mp,boss_hp,enemy_x[0],enemy_x[1],enemy_x[2],enemy_x[3],enemy_x[4],enemy_x[5],enemy_x[6],enemy_x[7],enemy_y[0],enemy_y[1],enemy_y[2],enemy_y[3],enemy_y[4],enemy_y[5],enemy_y[6],enemy_y[7]);
	fclose(fp);
}
void startup() {
	//进行游戏的初始化
	mciSendString("open .\\bgm\\game_music.mp3 alias bkmusic", NULL, 0, NULL);
	//打开背景音乐
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
	//循环播放
	initgraph(Width, High);
	//获取窗口句柄,初始化绘图环境
	HWND hwnd = GetHWnd();
	//设置窗口标题文字
	SetWindowText(hwnd, "雷霆战机 By 烽火醉夕阳");
	loadimage(&img_bk, ".\\image\\background.jpg");
	//加载图片
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
	position_x = int(Width * 0.5);
	//游戏数据初始化
	position_y = int(High * 0.7);
	bullet_x = position_x;
	bullet_y = -85;
	laser_x = 1001;
	laser_y = 1001;
	ebullet_x = 1000;
	ebullet_y = 1000;
	int i;
	for (i = 0; i < enemyNum; i++) {
		//加载多架敌机
		enemy_x[i] = rand() % Width;
		//随机生成敌机
		enemy_y[i] = 10;
	}
	boss_x = -1000, boss_y = -1000;
	//隐藏boss
	BeginBatchDraw();
	//用于开始批量绘图。执行后，任何绘图操作都将暂时不输出到屏幕上，
	//直到执行 FlushBatchDraw 或 EndBatchDraw 才将之前的绘图输出
	while (gameStatus == 0)
			startMenu();
	//初始化菜单页面
}
void show() {
	while (gameStatus == 0)         //回到主菜单的功能 {
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
	while (gameStatus == 3)	//暂停页面显示
	pauseMenu();
	putimage(0, 0, &img_bk);
	//显示背景
	if (isExpolde == 0) {
		//显示飞机
		putimage(int(position_x - 50), int(position_y - 60), &img_planeNormal1, NOTSRCERASE);
		//使得遮罩图片白色变黑 ,黑色区域变透明
		putimage(int(position_x - 50), int(position_y - 60), &img_planeNormal2, SRCINVERT);
		//遮罩在前,作为背景, 原图在后
		//显示子弹
		putimage(int(bullet_x - 7), int(bullet_y), &img_bullet1, NOTSRCERASE);
		putimage(int(bullet_x - 7), int(bullet_y), &img_bullet2, SRCINVERT);
		//显示敌机子弹
		putimage(int(ebullet_x - 7), int(ebullet_y), &img_ebullet1, NOTSRCERASE);
		putimage(int(ebullet_x - 7), int(ebullet_y), &img_ebullet2, SRCINVERT);
		//显示激光
		putimage(int(laser_x), int(laser_y), &img_laser2, NOTSRCERASE);
		putimage(int(laser_x), int(laser_y), &img_laser1, SRCINVERT);
		//显示敌机
		int i;
		for (i = 0; i < enemyNum; i++) {
			putimage(int(enemy_x[i]), int(enemy_y[i]), &img_enemyPlane1, NOTSRCERASE);
			putimage(int(enemy_x[i]), int(enemy_y[i]), &img_enemyPlane2, SRCINVERT);
		}
		//显示boss
		putimage(int(boss_x), int(boss_y), &img_boss2, NOTSRCERASE);
		putimage(int(boss_x), int(boss_y), &img_boss1, SRCINVERT);
	} else {
		//显示爆炸了的飞机
		putimage(int(position_x - 50), int(position_y - 60), &img_planeExplode1, NOTSRCERASE);
		putimage(int(position_x - 50), int(position_y - 60), &img_planeExplode2, SRCINVERT);
		settextcolor(BLUE);
		settextstyle(60, 0, _T("黑体"));
		outtextxy(Width * 0.15, High * 0.35, "江湖险恶！");
		outtextxy(Width * 0.15, High * 0.45, "大侠请按ESC键重新来过！");
	}
	settextcolor(YELLOW);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(Width * 0.75, High * 0.85, "当前得分：");
	//输出文字
	outtextxy(Width * 0.75, High * 0.90, "当前血量：");
	outtextxy(Width * 0.75, High * 0.95, "当前蓝量：");
	char s[5], h[5], m[5];
	sprintf(s, "%d", score);
	//将一个格式化的字符串输出到一个目的字符串中并进行输出
	sprintf(h, "%d", plane_hp);
	sprintf(m, "%d", plane_mp);
	settextcolor(RED);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(Width * 0.90, High * 0.85, s);
	outtextxy(Width * 0.90, High * 0.90, h);
	outtextxy(Width * 0.90, High * 0.95, m);
	FlushBatchDraw();
	Sleep(2);
}
void updateWithoutInput() {
	if (isExpolde == 0) {
		if (bullet_y > -25)			//子弹速度
		bullet_y = bullet_y - 2;
		if (ebullet_y < 1000)			//敌机子弹速度
		ebullet_y = ebullet_y + 2;
		if ((score == 25 || score % 15== 0) && (score != 0)) {
			//每达到15分会刷新boss
			int k = 50;
			boss_x = k + score;
			boss_y = 10;
			ebullet_x = boss_x + 100;
			ebullet_y = boss_y;
		}
		int i;
		float va=0.5;
		for (i = 0; i < enemyNum; i++) {
			//敌机速度
			if (enemy_y[i] < High - 25) {
				enemy_y[i] = enemy_y[i] + va;
			} else {
				enemy_y[i] = 10;
				enemy_x[i] = rand() % Width;
			}
			if ((score % 30== 0) && (score != 0)) //每达到30分，敌机速度突然加快，需要击败一个敌机恢复正常 {
				va=va+0.3;
			}
			if (abs(bullet_x - enemy_x[i]) + abs(bullet_y - enemy_y[i]) < 50) {
				//若子弹击中敌机+1分且恢复1点蓝量
				enemy_x[i] = rand() % Width;
				enemy_y[i] = 10;
				bullet_y = -85;
				mciSendString("close gemusic", NULL, 0, NULL);
				//关闭前面一次的音乐
				mciSendString("open .\\bgm\\gotEnemy.mp3 alias gemusic", NULL, 0, NULL);
				mciSendString("play gemusic", NULL, 0, NULL);
				//仅播放一次
				score++;
				plane_mp++;
				if (boss_x < 590 && score>0 && score % 2 == 0) {
					//每得2分boss发射一颗子弹并移动一步
					boss_x = boss_x + 100;
					ebullet_x = boss_x + 100;
					ebullet_y = boss_y;
					if (boss_x > 590)
											boss_x = 0;
				}
			}
			if ((laser_x >= enemy_x[i] - 50) && (laser_x <= enemy_x[i] + 50)) {
				//若激光击中敌机恢复1点血量，血量上限为10点
				enemy_x[i] = rand() % Width;
				enemy_y[i] = 10;
				if(plane_hp<10) {
					plane_hp++;
				}
				mciSendString("close gemusic", NULL, 0, NULL);
				//关闭前面一次的音乐
				mciSendString("open .\\bgm\\gotEnemy.mp3 alias gemusic", NULL, 0, NULL);
				mciSendString("play gemusic", NULL, 0, NULL);
				//仅播放一次
				score++;
				if (boss_x < 590 && score>0 && score % 2 == 0) {
					//每得2分boss发射一颗子弹，boss移动一步
					boss_x = boss_x + 100;
					ebullet_x = boss_x + 100;
					ebullet_y = boss_y;
					if (boss_x > 590)
											boss_x = 0;
				}
			}
			if ((abs(bullet_x - boss_x-70)+ abs(bullet_y - boss_y-70) < 100) || ((laser_x >= boss_x - 120) && (laser_x <= boss_x + 120))) {
				//若击败boss+10分
				boss_hp--;
				bullet_y = -85;
				mciSendString("close gemusic", NULL, 0, NULL);
				//关闭前面一次的音乐
				mciSendString("open .\\bgm\\gotEnemy.mp3 alias gemusic", NULL, 0, NULL);
				mciSendString("play gemusic", NULL, 0, NULL);
				//仅播放一次
				if (boss_hp == 0) {
					score += 10;
					boss_x = -1000;
					boss_y = -1000;
					boss_hp = 5;
				} else {
					//击中boss后boss移动并发射子弹
					boss_x = boss_x + 100;
					ebullet_x = boss_x + 100;
					ebullet_y = boss_y;
					if (boss_x > 590)
											boss_x = 0;
				}
			}
			if ((abs(position_x - enemy_x[i]) + abs(position_y - enemy_y[i]) < 80) || (abs(position_x - ebullet_x) + abs(position_y - ebullet_y) < 80)) {
				//若我机撞上敌机或boss的子弹
				plane_hp--;
				if (plane_hp == 0) {
					isExpolde = 1;
					mciSendString("close exmusic", NULL, 0, NULL);
					//关闭前面一次的音乐
					mciSendString("open .\\bgm\\explode.mp3 alias exmusic", NULL, 0, NULL);
					mciSendString("play exmusic", NULL, 0, NULL);
					//仅播放一次
				} else if (abs(position_x - enemy_x[i]) + abs(position_y - enemy_y[i]) < 80) {
					enemy_x[i] = rand() % Width;
					enemy_y[i] = -40;
					mciSendString("close gemusic", NULL, 0, NULL);
					//关闭前面一次的音乐
					mciSendString("open .\\bgm\\peng.mp3 alias gemusic", NULL, 0, NULL);
					mciSendString("play gemusic", NULL, 0, NULL);
					//仅播放一次
				} else if (abs(position_x - ebullet_x) + abs(position_y - ebullet_y) < 80) {
					ebullet_y = 1000;
					mciSendString("close gemusic", NULL, 0, NULL);
					//关闭前面一次的音乐
					mciSendString("open .\\bgm\\peng.mp3 alias gemusic", NULL, 0, NULL);
					mciSendString("play gemusic", NULL, 0, NULL);
					//仅播放一次
				}
			}
		}
		laser_x = 1001;
	}
}
void updateWithInput() {
	if (isExpolde == 0) {
		MOUSEMSG m;
		//定义鼠标信息
		while (MouseHit()) {
			//检测是否敲击鼠标
			m = GetMouseMsg();
			if (m.uMsg == WM_MOUSEMOVE) {
				//将飞机移到鼠标位置
				position_x = m.x;
				position_y = m.y;
			} else if (m.uMsg == WM_LBUTTONDOWN) {
				//按下左键发射子弹
				bullet_x = position_x;
				bullet_y = position_y - 85;
				mciSendString("close fgmusic", NULL, 0, NULL);
				//关闭前面一次的音乐
				mciSendString("open .\\bgm\\f_gun.mp3 alias fgmusic", NULL, 0, NULL);
				mciSendString("play fgmusic", NULL, 0, NULL);
				//仅播放一次
			} else if (m.uMsg == WM_RBUTTONDOWN && plane_mp > 9) {
				//按下右键发射激光
				laser_x = position_x - 40;
				laser_y = -30;
				plane_mp -= 10;
				//耗蓝量10点
				mciSendString("close fgmusic", NULL, 0, NULL);
				//关闭前面一次的音乐
				mciSendString("open .\\bgm\\f_gun.mp3 alias fgmusic", NULL, 0, NULL);
				mciSendString("play fgmusic", NULL, 0, NULL);
				//仅播放一次
			}
		}
	}
	char input;
	if (kbhit()) {
		//判断是否有输入
		input = getch();
		if (input == 27)	//判断是否按下Esc键（ASCII码值为27）暂停
		gameStatus = 3;
	}
}
void gameover() {
	EndBatchDraw();
	getch();
	closegraph();
}
int main() {
	startup();
	//初始化
	while (1) {
		show();
		//显示画面						
		updateWithoutInput();
		//与玩家无关的更新
		updateWithInput();
		//与玩家有关的更新
	}
	gameover();
	//游戏结束后进行后续处理
	return 0;
}
```
## 四.课程设计总结
通过这次课程设计的学习，我们从开始的构思想法到后面的查阅资料，从前期的编写代码到后期的调试查漏，再到最后的优化和现在的写课程设计报告，我们经历了很多困难，明白了很多事情不是马到成功的，需要我们脚踏实地一步一步地来，也认识了团队合作的重要意义。很多的东西看上去很难，但其实只要坚持下去就会看到意义。
编写的过程中也可能遇到有趣的事情，我想增加游戏的难度，想要随着得分的增加，敌机的速度加快，最终没有实现，误打误撞地得出了得分增加到XX的倍数，敌机就会加快速度，这时我们要用子弹击败一架敌机才会恢复正常，我觉得这个设定挺有趣的就保留了下来。游戏还存在一些优化的方向，比如可以连续射击子弹，暂停界面加入“重新开始”的按钮，增加排行榜和最高记录等等，由于时间原因没有进行优化。我觉得这次课程设计主要是给了我们一些框架类的一些东西和系统上的一些学习。
最后，对给予我们帮助的所有同学和老师以及博主表达由衷的感谢！

## 五.参考文献
> 《 C语言课程设计与游戏开发实践教程》2017年8月 童晶 丁海军 清华大学出版社
> 《C和C++游戏趣味编程》            2021年2月 童晶        人民邮电出版社
> 《C语言设计思想与实践》           2016年5月 周百顺      清华大学出版社
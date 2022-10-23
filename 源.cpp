#include<iostream>
#include<graphics.h>
#include<mmsystem.h>//多媒体设备接口头文件
#include<cstring>
#include<time.h>
#include<stdlib.h>
#pragma comment(lib, "winmm.lib")//加载静态库

using namespace std;
int mainmenu();//主菜单
void menurj_level();//人机对战菜单,选择对战难度
void menurj_sh();//人机对战菜单，选择先后手
int game_sr();//双人对战
int game_rj_easy_1st();//人机对战，简单，先手
int game_rj_difficulty_1st();//人机对战，难，先手
int game_rj_easy_2nd();//人机对战，简单，后手
int game_rj_difficulty_2nd();//人机对战，难，后手
void menusy();//声音菜单
void menusy_bjyy();//背景音乐菜单
void menusy_yx();//音效菜单
void open_sy_bjyy();//开背景音乐
void open_sy_yx();//开音效
void close_sy_yx();//关音效
void close_sy_bjyy();//关背景音乐(其实是暂停音乐)
int evalute();//求评估值
int minmax(int depth, int alpha, int beta);//minmax算法
char get_winplayer();//找到赢家
int event_player();//玩家事件，游戏显示
int player_move();//玩家下子
int player_huiqi();//玩家悔棋
void move_easy_cp();//电脑下子,简单
void move_difficulty_cp();//电脑下子，难
void gameover();//游戏结束
void gameover_yx();//游戏结束时的音效
void show_tb();//显示棋盘
IMAGE img_jzqbackground1; IMAGE img_jzqbackground2; IMAGE img_jzqTboard; IMAGE img_jzqx; IMAGE img_jzqo;
//      主菜单背景               游戏背景                       棋盘             x                 o    
IMAGE img_jzqbjyy; IMAGE img_jzqyx; IMAGE img_jzqbjyyx; IMAGE img_jzqyxx; IMAGE img_jzqmenubackground;
//       背景音乐           音效            背景音乐x            音效x              菜单栏背景
MOUSEMSG m;//鼠标
struct {
	int rj;//检查人机游戏，0是不是，1是是
	int sr;//检查双人游戏，0是不是，1是是
	int level;//难度系数判断参数，1是简单，2是难
	int bjyy;//1是背景音乐开，2是关
	int yx;//1是音效开，2是关
	int game;//判断游戏是否进行，0是进行，1是结束(不能下棋)
	int jx;//判断退出游戏和下子
	int gameover;//判断游戏结束后的显示
	int over;//1是退出游戏
}check;
struct {
	int x;//x的胜利场数
	int o;//o的胜利场数
	int p;//平局场数
	int move;//移动次数
}cnt;
struct {
	int x;//列
	int y;//行
}save[10];
pair <int, int> best_point;//最优解 
char tb[3][3] = { 0 };//棋盘
char cur_player = ' ';//记录当前的下棋的玩家,o是先手，x是后手
int cur_depth = 9;//一共有9步下棋
int wq = 10000000;//很大的值
char player = ' ';//玩家拿的什么棋子
char cp = ' ';//电脑拿的什么棋子

int main() {
	mciSendString("play F:\\resource\\jzqbgm.mp3 repeat", 0, 0, 0);
	initgraph(510, 390);
	memset(tb, ' ', sizeof(tb));
	srand((unsigned int)time(NULL));
	check.bjyy = 1;
	check.yx = 1;
	cur_depth = 9;
	loadimage(&img_jzqbackground1, "F:\\resource\\jzqbackground1.jpeg", 510, 390);
	loadimage(&img_jzqbackground2, "F:\\resource\\jzqbackground2.jpeg", 390, 390);
	loadimage(&img_jzqx, "F:\\resource\\jzqx.png", 90, 90);
	loadimage(&img_jzqo, "F:\\resource\\jzqo.png", 90, 90);
	loadimage(&img_jzqTboard, "F:\\resource\\jzqTboard.png", 270, 270);
	loadimage(&img_jzqbjyy, "F:\\resource\\jzqbjyy.jpeg", 60, 60);
	loadimage(&img_jzqyx, "F:\\resource\\jzqyx.jpeg", 60, 60);
	loadimage(&img_jzqbjyyx, "F:\\resource\\jzqbjyyx.png", 60, 60);
	loadimage(&img_jzqyxx, "F:\\resource\\jzqyxx.png", 60, 60);
	loadimage(&img_jzqmenubackground, "F:\\resource\\jzqmenubackground.jpeg", 120, 390);
	mainmenu();//主菜单
	return 0;
}

// 主菜单
int mainmenu() {
	char str1[20] = "井字棋游戏";
	char str2[20] = "< 人机对战 >";
	char str3[20] = "< 双人对战 >";
	char str4[20] = "< 声音设置 >";
	char str5[20] = "< 退出游戏 >";
	char str6[20] = "主菜单";
	settextcolor(BLUE);
	setbkmode(TRANSPARENT);
	settextstyle(0, 0, "隶书");
	int str1h = textheight(str1);  int str1w = textwidth(str1);
	int str2h = textheight(str2);  int str2w = textwidth(str2);
	int str3h = textheight(str3);  int str3w = textwidth(str3);
	int str4h = textheight(str4);  int str4w = textwidth(str4);
	int str5h = textheight(str5);  int str5w = textwidth(str5);
	int str6h = textheight(str6);  int str6w = textwidth(str6);
	BeginBatchDraw();
	putimage(0, 0, &img_jzqbackground1);
	outtextxy(0 + 255 - (str1w / 2), 0 + 56 - (str1h / 2), str1);//井字棋游戏
	outtextxy(0 + 255 - (str2w / 2), 112 + 28 - (str2h / 2), str2);//人机对战
	outtextxy(0 + 255 - (str3w / 2), 168 + 28 - (str3h / 2), str3);//双人对战
	outtextxy(0 + 255 - (str4w / 2), 224 + 28 - (str4h / 2), str4);//声音设置
	outtextxy(0 + 255 - (str5w / 2), 280 + 28 - (str5h / 2), str5);//退出游戏
	outtextxy(0 + 255 - (str6w / 2), 0 + 56 - (str1h / 2) + 40, str6);//菜单
	EndBatchDraw();
	m = GetMouseMsg();
	while (1) {
		if (MouseHit()) {//鼠标移动
			m = GetMouseMsg();//更新鼠标信息
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 255 - (str2w / 2) && m.x < 255 + (str2w / 2) &&
					m.y >140 - (str2h / 2) && m.y < 140 + (str2h / 2)) {//点击人机对战
					check.rj = 1;
					menurj_level();
					return 1;
				}
				if (m.x > 255 - (str3w / 2) && m.x < 255 + (str3w / 2) &&
					m.y >196 - (str3h / 2) && m.y < 196 + (str3h / 2)) {//点击双人对战
					check.sr = 1;
					cnt.move += 1;
					game_sr();
					return 1;
				}
				if (m.x > 255 - (str4w / 2) && m.x < 255 + (str4w / 2) &&
					m.y >252 - (str4h / 2) && m.y < 252 + (str4h / 2)) {//点击声音设置
					menusy();
					return 1;
				}
				if (m.x > 255 - (str5w / 2) && m.x < 255 + (str5w / 2) &&
					m.y >308 - (str5h / 2) && m.y < 308 + (str5h / 2)) {//点击退出游戏
					return 1;
				}
			}
		}
	}
	return 1;
}

//人机对战菜单,选择对战难度
void menurj_level() {
	cleardevice();
	char str1[20] = "井字棋游戏";
	char str2[20] = "难度选择";
	char str3[20] = "< 简单 >";
	char str4[20] = "< 难 >";
	char str6[20] = "菜单";
	char str7[20] = "[返回上一步]";
	int str1h = textheight(str1);  int str1w = textwidth(str1);
	int str2h = textheight(str2);  int str2w = textwidth(str2);
	int str3h = textheight(str3);  int str3w = textwidth(str3);
	int str4h = textheight(str4);  int str4w = textwidth(str4);
	int str6h = textheight(str6);  int str6w = textwidth(str6);
	int str7h = textheight(str7);  int str7w = textwidth(str7);
	BeginBatchDraw();
	putimage(0, 0, &img_jzqbackground1);
	outtextxy(0 + 255 - (str1w / 2), 0 + 56 - (str1h / 2), str1);//井字棋游戏
	outtextxy(0 + 255 - (str2w / 2), 112 + 28 - (str2h / 2), str2);//难度选择
	outtextxy(0 + 255 - (str3w / 2), 168 + 28 - (str3h / 2), str3);//简单
	outtextxy(0 + 255 - (str4w / 2), 224 + 28 - (str4h / 2), str4);//难
	outtextxy(0 + 255 - (str6w / 2), 0 + 56 - (str1h / 2) + 40, str6);//菜单
	outtextxy(510 - str7w, 0, str7);//返回上一步
	EndBatchDraw();
	m = GetMouseMsg();
	while (1) {
		if (MouseHit()) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 255 - (str3w / 2) && m.x < 255 + (str3w / 2) &&
					m.y > 196 - (str3h / 2) && m.y < 196 + (str3h / 2)) {//点击简单
					check.level = 1;
					menurj_sh();
					return;
				}
				if (m.x > 255 - (str4w / 2) && m.x < 255 + (str4w / 2) &&
					m.y > 252 - (str4h / 2) && m.y < 252 + (str4h / 2)) {//点击难
					check.level = 2;
					menurj_sh();
					return;
				}
				if (m.x > 390 && m.x < 390 + str7w &&
					m.y > 0 && m.y < str7h) {
					mainmenu();
					return;
				}
			}
		}
	}
	return;
}

//声音菜单
void menusy() {
	cleardevice();
	char str1[20] = "井字棋游戏";
	char str2[20] = "声音设置";
	char str3[20] = "< 背景音乐 >";
	char str4[20] = "< 音效 >";
	char str6[20] = "菜单";
	char str7[20] = "[返回上一步] ";
	int str1h = textheight(str1);  int str1w = textwidth(str1);
	int str2h = textheight(str2);  int str2w = textwidth(str2);
	int str3h = textheight(str3);  int str3w = textwidth(str3);
	int str4h = textheight(str4);  int str4w = textwidth(str4);
	int str6h = textheight(str6);  int str6w = textwidth(str6);
	int str7h = textheight(str7);  int str7w = textwidth(str7);
	BeginBatchDraw();
	putimage(0, 0, &img_jzqbackground1);
	outtextxy(0 + 255 - (str1w / 2), 0 + 56 - (str1h / 2), str1);//井字棋游戏
	outtextxy(0 + 255 - (str2w / 2), 112 + 28 - (str2h / 2), str2);//声音设置
	outtextxy(0 + 255 - (str3w / 2), 168 + 28 - (str3h / 2), str3);//背景音乐
	outtextxy(0 + 255 - (str4w / 2), 224 + 28 - (str4h / 2), str4);//音效
	outtextxy(0 + 255 - (str6w / 2), 0 + 56 - (str1h / 2) + 40, str6);//菜单
	outtextxy(510 - str7w, 0, str7);//返回上一步
	EndBatchDraw();
	m = GetMouseMsg();
	while (1) {
		if (MouseHit()) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 255 - (str3w / 2) && m.x < 255 + (str3w / 2) &&
					m.y > 196 - (str3h / 2) && m.y < 196 + (str3h / 2)) {//点击背景音乐
					menusy_bjyy();
					return;
				}
				if (m.x > 255 - (str4w / 2) && m.x < 255 + (str4w / 2) &&
					m.y > 252 - (str4h / 2) && m.y < 252 + (str4h / 2)) {//点击音效
					menusy_yx();
					return;
				}
				if (m.x > 390 && m.x < 390 + str7w &&
					m.y > 0 && m.y < str7h) {//返回上一步
					mainmenu();
					return;
				}
			}
		}
	}
	return;
}

//人机对战菜单，选择先后手
void menurj_sh() {
	cleardevice();
	char str1[20] = "井字棋游戏";
	char str2[20] = "先后手选择";
	char str3[20] = "< 先手 >";
	char str4[20] = "< 后手 >";
	char str6[20] = "菜单";
	char str7[20] = "[返回上一步]";
	int str1h = textheight(str1);  int str1w = textwidth(str1);
	int str2h = textheight(str2);  int str2w = textwidth(str2);
	int str3h = textheight(str3);  int str3w = textwidth(str3);
	int str4h = textheight(str4);  int str4w = textwidth(str4);
	int str6h = textheight(str6);  int str6w = textwidth(str6);
	int str7h = textheight(str7);  int str7w = textwidth(str7);
	BeginBatchDraw();
	putimage(0, 0, &img_jzqbackground1);
	outtextxy(0 + 255 - (str1w / 2), 0 + 56 - (str1h / 2), str1);//井字棋游戏
	outtextxy(0 + 255 - (str2w / 2), 112 + 28 - (str2h / 2), str2);//先后手选择
	outtextxy(0 + 255 - (str3w / 2), 168 + 28 - (str3h / 2), str3);//先手
	outtextxy(0 + 255 - (str4w / 2), 224 + 28 - (str4h / 2), str4);//后手
	outtextxy(0 + 255 - (str6w / 2), 0 + 56 - (str1h / 2) + 40, str6);//菜单
	outtextxy(510 - str7w, 0, str7);//返回上一步
	EndBatchDraw();
	m = GetMouseMsg();
	while (1) {
		if (MouseHit()) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 255 - (str3w / 2) && m.x < 255 + (str3w / 2) &&
					m.y > 196 - (str3h / 2) && m.y < 196 + (str3h / 2)) {//点击先手,o
					player = 'o';
					cp = 'x';
					check.rj = 1;
					if (check.level == 1) {//人机对战，简单，先手
						game_rj_easy_1st();
						return;
					}
					if (check.level == 2) {//人机对战，难，先手
						game_rj_difficulty_1st();
						return;
					}
				}
				if (m.x > 255 - (str4w / 2) && m.x < 255 + (str4w / 2) &&
					m.y > 252 - (str4h / 2) && m.y < 252 + (str4h / 2)) {//点击后手,x
					player = 'x';
					cp = 'o';
					check.rj = 1;
					if (check.level == 1) {//人机对战，简单，后手
						game_rj_easy_2nd();
						return;
					}
					if (check.level == 2) {//人机对战，难，后手
						game_rj_difficulty_2nd();
						return;
					}
				}
				if (m.x > 390 && m.x < 390 + str7w &&
					m.y > 0 && m.y < str7h) {
					menurj_level();
					return;
				}
			}
		}
	}
	return;
}

//背景音乐菜单
void menusy_bjyy() {
	cleardevice();
	char str1[20] = "井字棋游戏";
	char str2[20] = "背景音乐";
	char str3[20] = "< 背景音乐  开 >";
	char str4[20] = "< 背景音乐  关 >";
	char str5[20] = "[返回上一步]";
	char str6[20] = "菜单";
	settextcolor(BLUE);
	cleardevice();
	setbkmode(TRANSPARENT);
	settextstyle(0, 0, "隶书");
	int str1h = textheight(str1);  int str1w = textwidth(str1);
	int str2h = textheight(str2);  int str2w = textwidth(str2);
	int str3h = textheight(str3);  int str3w = textwidth(str3);
	int str4h = textheight(str4);  int str4w = textwidth(str4);
	int str5h = textheight(str5);  int str5w = textwidth(str5);
	int str6h = textheight(str6);  int str6w = textwidth(str6);
	BeginBatchDraw();
	putimage(0, 0, &img_jzqbackground1);
	outtextxy(0 + 255 - (str1w / 2), 0 + 56 - (str1h / 2), str1);//井字棋游戏
	outtextxy(0 + 255 - (str2w / 2), 112 + 28 - (str2h / 2), str2);//背景声音设置
	outtextxy(0 + 255 - (str3w / 2), 168 + 28 - (str3h / 2), str3);//背景音乐开
	outtextxy(0 + 255 - (str4w / 2), 224 + 28 - (str4h / 2), str4);//背景音乐关
	outtextxy(510 - str5w, 0, str5);//返回上一步
	outtextxy(0 + 255 - (str6w / 2), 0 + 56 - (str1h / 2) + 40, str6);//菜单
	EndBatchDraw();
	m = GetMouseMsg();
	while (1) {
		if (MouseHit()) {//鼠标移动
			m = GetMouseMsg();//更新鼠标信息
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 255 - (str3w / 2) && m.x < 255 + (str3w / 2) &&
					m.y >196 - (str3h / 2) && m.y < 196 + (str3h / 2)) {//背景音乐开
					check.bjyy = 1;
					open_sy_bjyy();
				}
				if (m.x > 255 - (str4w / 2) && m.x < 255 + (str4w / 2) &&
					m.y >252 - (str4h / 2) && m.y < 252 + (str4h / 2)) {//背景音乐关
					check.bjyy = 2;
					close_sy_bjyy();
				}
				if (m.x > 390 && m.x < 390 + str5w &&
					m.y > 0 && m.y < str5h) {
					menusy();
					return;
				}
			}
		}
	}
	return;
}

//音效菜单
void menusy_yx() {
	cleardevice();
	char str1[20] = "井字棋游戏";
	char str2[20] = "音效";
	char str3[20] = "< 音效  开 >";
	char str4[20] = "< 音效  关 >";
	char str5[20] = "[返回上一步]";
	char str6[20] = "菜单";
	settextcolor(BLUE);
	cleardevice();
	setbkmode(TRANSPARENT);
	settextstyle(0, 0, "隶书");
	int str1h = textheight(str1);  int str1w = textwidth(str1);
	int str2h = textheight(str2);  int str2w = textwidth(str2);
	int str3h = textheight(str3);  int str3w = textwidth(str3);
	int str4h = textheight(str4);  int str4w = textwidth(str4);
	int str5h = textheight(str5);  int str5w = textwidth(str5);
	int str6h = textheight(str6);  int str6w = textwidth(str6);
	BeginBatchDraw();
	putimage(0, 0, &img_jzqbackground1);
	outtextxy(0 + 255 - (str1w / 2), 0 + 56 - (str1h / 2), str1);//井字棋游戏
	outtextxy(0 + 255 - (str2w / 2), 112 + 28 - (str2h / 2), str2);//背景声音设置
	outtextxy(0 + 255 - (str3w / 2), 168 + 28 - (str3h / 2), str3);//背景音乐开
	outtextxy(0 + 255 - (str4w / 2), 224 + 28 - (str4h / 2), str4);//背景音乐关
	outtextxy(510 - str5w, 0, str5);//返回上一步
	outtextxy(0 + 255 - (str6w / 2), 0 + 56 - (str1h / 2) + 40, str6);//菜单
	EndBatchDraw();
	m = GetMouseMsg();
	while (1) {
		if (MouseHit()) {//鼠标移动
			m = GetMouseMsg();//更新鼠标信息
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 255 - (str3w / 2) && m.x < 255 + (str3w / 2) &&
					m.y >196 - (str3h / 2) && m.y < 196 + (str3h / 2)) {//音效开
					check.yx = 1;
				}
				if (m.x > 255 - (str4w / 2) && m.x < 255 + (str4w / 2) &&
					m.y >252 - (str4h / 2) && m.y < 252 + (str4h / 2)) {//音效关
					check.yx = 2;
				}
				if (m.x > 390 && m.x < 390 + str5w &&
					m.y > 0 && m.y < str5h) {
					menusy();
					return;
				}
			}
		}
	}
	return;
}

//打开背景音乐
void open_sy_bjyy() {
	mciSendString("play F:\\resource\\jzqbgm.mp3 repeat", 0, 0, 0);//播放
}

//关背景音乐
void close_sy_bjyy() {
	mciSendString("pause F:\\resource\\jzqbgm.mp3", 0, 0, 0);
}

//打开音效
void open_sy_yx() {
	mciSendString("play F:\\resource\\jzqyxo.mp3", 0, 0, 0);
	Sleep(200);
}

//关音效
void close_sy_yx() {
	mciSendString("pause F:\\resource\\jzqyxo.mp3", 0, 0, 0);
	mciSendString("pause F:\\resource\\victory.mp3", 0, 0, 0);
	mciSendString("pause F:\\resource\\defeat.mp3", 0, 0, 0);
}

//check.jx方便悔棋和结束游戏
//== 1 是退出游戏
//== 0 是继续游戏
//== 2 是悔棋的时候转到玩家事件

//双人对战
int game_sr() {
	while (1) {
		player = 'o';
		cp = 'x';
		check.jx = event_player();
		if (check.jx == 1) {
			return 1;
		}
		player = 'x';
		cp = 'o';
		check.jx = event_player();
		if (check.jx == 1) {
			return 1;
		}
	}
	return 1;
}

//人机对战，简单，先手
int game_rj_easy_1st() {
	while (1) {
		int x = rand() % 3;
		cur_player = player;
		check.jx = event_player();
		if (check.jx == 1) {
			return 1;
		}
		else if (check.jx == 0) {
			cur_player = cp;
			if (x == 0) {
				move_easy_cp();
			}
			else {
				move_difficulty_cp();
			}
		}
	}
	return 1;
}

//人机对战，简单，后手
int game_rj_easy_2nd() {
	while (1) {
		int x = rand() % 3;
		if (check.jx == 0) {
			cur_player = cp;
			if (x == 0) {
				move_easy_cp();
			}
			else {
				move_difficulty_cp();
			}
		}
		cur_player = player;
		check.jx = event_player();
		if (check.jx == 1) {
			return 1;
		}
	}
	return 1;
}

//人机对战，难，先手
int game_rj_difficulty_1st() {
	while (1) {
		cur_player = player;
		check.jx = event_player();
		if (check.jx == 1) {
			return 1;
		}
		if (check.jx == 0) {
			cur_player = cp;
			move_difficulty_cp();
		}
	}
	return 1;
}

//人机对战，难，后手
int game_rj_difficulty_2nd() {
	while (1) {
		if (check.jx == 0) {
			cur_player = cp;
			move_difficulty_cp();
		}
		cur_player = player;
		check.jx = event_player();
		if (check.jx == 1) {
			return 1;
		}
	}
	return 1;
}

//显示棋盘
void show_tb() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tb[i][j] == 'x') {
				putimage(180 + j * 90, 60 + i * 90, &img_jzqx);
			}
			if (tb[i][j] == 'o') {
				putimage(180 + j * 90, 60 + i * 90, &img_jzqo);
			}
		}
	}
}

//玩家事件,游戏界面
int event_player() {
	check.gameover = 0;
	check.over = 0;
	m = GetMouseMsg();
	while (1) {
		if (MouseHit()) {
			cleardevice();
			char str1[20] = "井字棋游戏";
			char str2[20] = "菜单栏";
			char str3[20] = "悔棋";
			char str4[20] = "再来一局";
			char str5[20] = "返回主菜单";
			char str6[20] = "退出游戏";
			char str7[20] = "背景音乐";
			char str8[20] = "音效";
			settextcolor(BLUE);
			cleardevice();
			setbkmode(TRANSPARENT);
			int str1h = textheight(str1);  int str1w = textwidth(str1);
			int str2h = textheight(str2);  int str2w = textwidth(str2);
			int str3h = textheight(str3);  int str3w = textwidth(str3);//悔棋
			int str4h = textheight(str4);  int str4w = textwidth(str4);//再来一局
			int str5h = textheight(str5);  int str5w = textwidth(str5);//返回主菜单
			int str6h = textheight(str6);  int str6w = textwidth(str6);//退出游戏
			int str7h = textheight(str7);  int str7w = textwidth(str7);//背景音乐
			int str8h = textheight(str8);  int str8w = textwidth(str8);//音效
			BeginBatchDraw();
			putimage(120, 0, &img_jzqbackground2);
			putimage(0, 0, &img_jzqmenubackground);
			putimage(180, 60, &img_jzqTboard);
			if (check.bjyy == 1) {
				putimage(160 + str7w, 0, &img_jzqbjyy);
			}
			if (check.bjyy == 2) {
				putimage(160 + str7w, 0, &img_jzqbjyyx);
			}
			if (check.yx == 1) {
				putimage(355 + str8w, 0, &img_jzqyx);
			}
			if (check.yx == 2) {
				putimage(355 + str8w, 0, &img_jzqyxx);
			}
			show_tb();
			settextstyle(20, 10, "隶书");
			outtextxy(55 - (str1w / 2), 0 + 56 - (str1h / 2), str1);//井字棋游戏
			outtextxy(55 - (str2w / 2), 92 + 28 - (str2h / 2), str2);//菜单
			outtextxy(55 - (str3w / 2), 148 + 28 - (str3h / 2), str3);//悔棋
			outtextxy(55 - (str4w / 2), 204 + 28 - (str4h / 2), str4);//重新开始
			outtextxy(55 - (str5w / 2), 260 + 28 - (str5h / 2), str5);//返回主菜单
			outtextxy(55 - (str6w / 2), 316 + 28 - (str6h / 2), str6);//退出游戏
			settextstyle(0, 0, "隶书");
			outtextxy(160, 0 + 30 - (str7h / 2), str7);//背景音乐
			outtextxy(355, 0 + 30 - (str8h / 2), str8);//音效
			gameover();
			EndBatchDraw();
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 60 - (str3w / 2) && m.x < 60 + (str3w / 2) &&
					m.y >176 - (str3h / 2) && m.y < 176 + (str3h / 2)) {//悔棋
					if (cnt.move > 1) {
						int huiqi = player_huiqi();
						return huiqi;
					}
				}
				if (m.x > 60 - (str4w / 2) && m.x < 60 + (str4w / 2) &&
					m.y >232 - (str4h / 2) && m.y < 232 + (str4h / 2)) {//再来一局
					if (get_winplayer() == 'x' || get_winplayer() == 'o' || get_winplayer() == 'p') {
						int check_zlyj = MessageBox(NULL, "确定再来一局吗？", "选择", MB_OKCANCEL);
						if (check_zlyj == IDOK) {
							memset(tb, ' ', sizeof(tb));
							cur_depth = 9;
							check.game = 0;
							cnt.move = 0;
							check.jx = 0;
							if (check.sr == 1) {//当前是双人游戏
								check.over = game_sr();
								if (check.over == 1) {
									return 1;
								}
							}
							if (check.rj == 1) {//当前是人机
								if (check.level == 1 && player == 'o') {//人机对战，简单，先手
									check.over = game_rj_easy_1st();
									if (check.over == 1) {
										return 1;
									}
								}
								if (check.level == 2 && player == 'o') {//人机对战，难，先手
									check.over = game_rj_difficulty_1st();
									if (check.over == 1) {
										return 1;
									}
								}
								if (check.level == 1 && player == 'x') {//人机对战，简单，后手
									check.over = game_rj_easy_2nd();
									if (check.over == 1) {
										return 1;
									}
								}
								if (check.level == 2 && player == 'x') {//人机对战，难，后手
									check.over = game_rj_difficulty_2nd();
									if (check.over == 1) {
										return 1;
									}
								}
							}
						}
					}
				}
				if (m.x > 60 - (str5w / 2) && m.x < 60 + (str5w / 2) &&
					m.y >288 - (str5h / 2) && m.y < 288 + (str5h / 2)) {// 返回主菜单
					int check_zcd = MessageBox(NULL, "确认返回主菜单吗？", "选择", MB_OKCANCEL);
					if (check_zcd == IDOK) {
						memset(tb, ' ', sizeof(tb));
						player = ' ';
						cp = ' ';
						cur_depth = 9;
						check.game = 0;
						check.level = 0;
						check.jx = 0;
						check.rj = 0;
						check.sr = 0;
						cnt.o = 0;
						cnt.x = 0;
						cnt.p = 0;
						cnt.move = 0;
						check.over = mainmenu();
						if (check.over == 1) {
							return 1;
						}
					}
				}
				if (m.x > 60 - (str6w / 2) && m.x < 60 + (str6w / 2) &&
					m.y >344 - (str6h / 2) && m.y < 344 + (str6h / 2)) {//退出游戏
					int check_end = MessageBox(NULL, "确认退出游戏吗？", "选择", MB_OKCANCEL);
					if (check_end == IDOK) {
						check.over = 1;
						return 1;
					}
				}
				if (m.x > 160 + str7w && m.x < 160 + str7w + 60 &&
					m.y > 0 && m.y < 60) {//背景音乐
					if (check.bjyy == 1) {
						check.bjyy = 2;//关背景音乐
						close_sy_bjyy();
						putimage(160 + str7w, 0, &img_jzqbjyyx);
					}
					else if (check.bjyy == 2) {
						check.bjyy = 1;//开背景音乐
						open_sy_bjyy();
						putimage(160 + str7w, 0, &img_jzqbjyy);
					}
				}
				if (m.x > 355 + str8w && m.x < 355 + str8w + 60 &&
					m.y > 0 && m.y < 60) {//音效
					if (check.yx == 1) {
						check.yx = 2;//关音效
						close_sy_yx();
						putimage(355 + str8w, 0, &img_jzqyxx);
					}
					else if (check.yx == 2) {
						check.yx = 1;//开音效
						putimage(355 + str8w, 0, &img_jzqyx);
					}
				}
				if (check.game == 0) {
					int pm = player_move();
					if (pm == 1) {
						return 0;
					}
				}
			}
		}
	}
	return 0;
}

//玩家悔棋
int player_huiqi() {
	int check_huiqi = MessageBox(NULL, "确认悔棋吗？", "选择", MB_OKCANCEL);
	if (check_huiqi == IDOK) {
		check.game = 0;//可以下子
		char win = get_winplayer();
		if (win == 'x') {
			cnt.x--;
		}
		if (win == 'o') {
			cnt.o--;
		}
		if (win == 'p') {
			cnt.p--;
		}
		if (check.sr == 1) {//双人时
			tb[save[cnt.move].y][save[cnt.move].x] = ' ';
			cnt.move--;
			return 0;
		}
		if (check.rj == 1) {
			if (player == 'o') {//玩家先手
				if (win == 'p' || win == 'o') {
					tb[save[cnt.move].y][save[cnt.move].x] = ' ';
					cnt.move--;
					cur_depth++;
					return 2;
				}
				else {
					tb[save[cnt.move].y][save[cnt.move].x] = ' ';
					tb[save[cnt.move - 1].y][save[cnt.move - 1].x] = ' ';
					cnt.move -= 2;
					cur_depth += 2;
					return 2;
				}
			}
			if (player == 'x') {//玩家后手
				if (win == 'x') {
					tb[save[cnt.move].y][save[cnt.move].x] = ' ';
					cnt.move--;
					cur_depth++;
					return 2;
				}
				else {
					tb[save[cnt.move].y][save[cnt.move].x] = ' ';
					tb[save[cnt.move - 1].y][save[cnt.move - 1].x] = ' ';
					cnt.move -= 2;
					cur_depth += 2;
					return 2;
				}
			}
		}
	}
	return 2;
}

//玩家下子
int player_move() {
	if (m.x > 180 && m.x < 270 &&
		m.y > 60 && m.y < 150) {//下子在0,0
		if (tb[0][0] == ' ') {
			tb[0][0] = player;
			save[++cnt.move].x = 0;
			save[cnt.move].y = 0;
			cur_depth--;
			check.jx = 0;
			if (check.yx == 1) {
				open_sy_yx();
			}
			return 1;
		}
	}
	if (m.x > 270 && m.x < 360 &&
		m.y > 60 && m.y < 150) {//下子在0,1
		if (tb[0][1] == ' ') {
			tb[0][1] = player;
			save[++cnt.move].x = 1;
			save[cnt.move].y = 0;
			cur_depth--;
			check.jx = 0;
			if (check.yx == 1) {
				open_sy_yx();
			}
			return 1;
		}
	}
	if (m.x > 360 && m.x < 450 &&
		m.y > 60 && m.y < 150) {//下子在0,2
		if (tb[0][2] == ' ') {
			tb[0][2] = player;
			save[++cnt.move].x = 2;
			save[cnt.move].y = 0;
			cur_depth--;
			check.jx = 0;
			if (check.yx == 1) {
				open_sy_yx();
			}
			return 1;
		}
	}
	if (m.x > 180 && m.x < 270 &&
		m.y > 150 && m.y < 240) {//下子在1,0
		if (tb[1][0] == ' ') {
			tb[1][0] = player;
			save[++cnt.move].x = 0;
			save[cnt.move].y = 1;
			cur_depth--;
			check.jx = 0;
			if (check.yx == 1) {
				open_sy_yx();
			}
			return 1;
		}
	}
	if (m.x > 270 && m.x < 360 &&
		m.y > 150 && m.y < 240) {//下子在1,1
		if (tb[1][1] == ' ') {
			tb[1][1] = player;
			save[++cnt.move].x = 1;
			save[cnt.move].y = 1;
			cur_depth--;
			check.jx = 0;
			if (check.yx == 1) {
				open_sy_yx();
			}
			return 1;
		}
	}
	if (m.x > 360 && m.x < 450 &&
		m.y > 150 && m.y < 240) {//下子在1,2
		if (tb[1][2] == ' ') {
			tb[1][2] = player;
			save[++cnt.move].x = 2;
			save[cnt.move].y = 1;
			cur_depth--;
			check.jx = 0;
			if (check.yx == 1) {
				open_sy_yx();
			}
			return 1;
		}
	}
	if (m.x > 180 && m.x < 270 &&
		m.y > 240 && m.y < 330) {//下子在2,0
		if (tb[2][0] == ' ') {
			tb[2][0] = player;
			save[++cnt.move].x = 0;
			save[cnt.move].y = 2;
			cur_depth--;
			check.jx = 0;
			if (check.yx == 1) {
				open_sy_yx();
			}
			return 1;
		}
	}
	if (m.x > 270 && m.x < 360 &&
		m.y > 240 && m.y < 330) {//下子在2,1
		if (tb[2][1] == ' ') {
			tb[2][1] = player;
			save[++cnt.move].x = 1;
			save[cnt.move].y = 2;
			cur_depth--;
			check.jx = 0;
			if (check.yx == 1) {
				open_sy_yx();
			}
			return 1;
		}
	}
	if (m.x > 360 && m.x < 450 &&
		m.y > 240 && m.y < 330) {//下子在2,2
		if (tb[2][2] == ' ') {
			tb[2][2] = player;
			save[++cnt.move].x = 2;
			save[cnt.move].y = 2;
			cur_depth--;
			check.jx = 0;
			if (check.yx == 1) {
				open_sy_yx();
			}
			return 1;
		}
	}
	return 0;
}

//minmax算法
int minmax(int depth, int alpha, int beta) {
	int cur_value = 0;
	int	best_value = 0;
	int	cnt = 0;
	pair <int, int> p[10];
	if (get_winplayer() == player || get_winplayer() == cp || depth == 0) {
		return evalute();
	}
	if (cur_player == cp) {//还没下完
		best_value = -wq;
	}
	else if (cur_player == player) {//还没下完
		best_value = wq;
	}
	for (int i = 0; i < 3; i++) {//剩余点
		for (int j = 0; j < 3; j++) {
			if (tb[i][j] == ' ') {
				p[cnt].first = i;
				p[cnt].second = j;
				cnt++;
			}
		}
	}
	for (int i = 0; i < cnt; i++) {
		pair<int, int> cur_point = p[i];//当前点
		int x = cur_point.first;
		int y = cur_point.second;
		tb[x][y] = cur_player;//假设在这下子（搜索，已访问）
		cur_player = (cur_player == player) ? cp : player;
		cur_value = minmax(depth - 1, alpha, beta);//往下搜索
		tb[x][y] = ' ';//取消下棋（回溯）
		cur_player = (cur_player == player) ? cp : player;
		if (cur_player == cp) {//max节点
			if (cur_value > best_value) {
				best_value = cur_value;
				if (depth == cur_depth) {
					best_point = cur_point;
				}
				alpha = best_value;
			}
			if (beta <= alpha) {
				return beta;
			}
		}
		else if (cur_player == player) {//min节点
			if (cur_value < best_value) {
				best_value = cur_value;
				if (depth == cur_depth) {
					best_point = cur_point;
				}
				beta = best_value;
			}
			if (beta <= alpha) {
				return alpha;
			}
		}
	}
	return best_value;
}

//找到赢家
char get_winplayer() {
	int i = 0;
	int j = 0;
	int cnt = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (tb[i][j] == 'x' || tb[i][j] == 'o') {
				cnt++;
			}
		}
	}
	for (i = 0; i < 3; i++) {//3行 
		if (tb[i][0] == tb[i][1] && tb[i][1] == tb[i][2] && tb[i][0] != ' ') {
			return tb[i][0];
		}
	}
	for (j = 0; j < 3; j++) {//3列
		if (tb[0][j] == tb[1][j] && tb[1][j] == tb[2][j] && tb[0][j] != ' ') {
			return tb[0][j];
		}
	}
	if (tb[0][0] == tb[1][1] && tb[1][1] == tb[2][2] && tb[0][0] != ' ') {//向下斜 
		return tb[0][0];
	}
	if (tb[2][0] == tb[1][1] && tb[1][1] == tb[0][2] && tb[2][0] != ' ') {//向上斜 
		return tb[2][0];
	}
	if (cnt == 9) {
		return 'p';
	}
	return '0';
}

//求评估值
int evalute() {
	int i = 0;
	int j = 0;//有结果
	if (get_winplayer() == cp) {
		return wq;
	}
	if (get_winplayer() == player) {
		return -wq;
	}
	int value = 0;//如果输赢还么出来，开始计算价值
	char temp_tb[3][3] = { 0 };//临时棋盘
	memset(temp_tb, ' ', sizeof(temp_tb));
	for (i = 0; i < 3; i++) {//假设电脑下棋
		for (j = 0; j < 3; j++) {
			if (tb[i][j] == ' ') {
				temp_tb[i][j] = cp;
			}
			else {
				temp_tb[i][j] = tb[i][j];
			}
		}
	}
	for (i = 0; i < 3; i++) {//3行 
		if (temp_tb[i][0] == temp_tb[i][1] && temp_tb[i][1] == temp_tb[i][2] && temp_tb[i][0] == cp && temp_tb[i][0] != ' ')
			value += 10;
	}
	for (j = 0; j < 3; j++) {//3行列
		if (temp_tb[0][j] == temp_tb[1][j] && temp_tb[1][j] == temp_tb[2][j] && temp_tb[0][j] == cp && temp_tb[0][j] != ' ')
			value += 10;
	}
	if (temp_tb[0][0] == temp_tb[1][1] && temp_tb[1][1] == temp_tb[2][2] && temp_tb[0][0] == cp && temp_tb[0][0] != ' ') {//向下斜 
		value += 10;
	}
	if (temp_tb[2][0] == temp_tb[1][1] && temp_tb[0][2] == temp_tb[1][1] && temp_tb[2][0] == cp && temp_tb[2][0] != ' ') {//向上斜 
		value += 10;
	}
	for (i = 0; i < 3; i++) {//假设玩家下棋
		for (j = 0; j < 3; j++) {
			if (tb[i][j] == ' ') {
				temp_tb[i][j] = player;
			}
			else {
				temp_tb[i][j] = tb[i][j];
			}
		}
	}
	for (i = 0; i < 3; i++) {//3行 
		if (temp_tb[i][0] == temp_tb[i][1] && temp_tb[i][1] == temp_tb[i][2] && temp_tb[i][0] == player && temp_tb[i][0] != ' ')
			value -= 10;
	}
	for (j = 0; j < 3; j++) {//3列 
		if (temp_tb[0][j] == temp_tb[1][j] && temp_tb[1][j] == temp_tb[2][j] && temp_tb[0][j] == player && temp_tb[0][j] != ' ')
			value -= 10;
	}
	if (temp_tb[0][0] == temp_tb[1][1] && temp_tb[1][1] == temp_tb[2][2] && temp_tb[0][0] == player && temp_tb[0][0] != ' ') {//向下斜 
		value -= 10;
	}
	if (temp_tb[2][0] == temp_tb[1][1] && temp_tb[0][2] == temp_tb[1][1] && temp_tb[2][0] == player && temp_tb[2][0] != ' ') {//向上斜 
		value -= 10;
	}
	return value;
}

//电脑下子,难
void move_difficulty_cp() {
	char win = get_winplayer();
	if (win != 'o' && win != 'x' && win != 'p') {
		minmax(cur_depth, -wq, wq);
		tb[best_point.first][best_point.second] = cp;
		save[++cnt.move].x = best_point.second;
		save[cnt.move].y = best_point.first;
		cur_depth--;
		if (check.yx == 1) {
			open_sy_yx();
		}
	}
}

//电脑下子，简单
void move_easy_cp() {
	int x = 0;
	int y = 0;
	char win = get_winplayer();
	while (1)
	{
		if (win != 'o' && win != 'x' && win != 'p') {
			x = rand() % 3;
			y = rand() % 3;
			if (tb[x][y] == ' ')
			{
				tb[x][y] = cp;
				save[++cnt.move].x = y;//行
				save[cnt.move].y = x;//列
				cur_depth--;
				if (check.yx == 1) {
					open_sy_yx();
				}
				break;
			}
		}
		else {
			break;
		}
	}
}

//游戏结果
void gameover() {
	char str9[20] = "红方得分:";
	char str10[20] = "黑方得分:";
	char str11[20] = "平局数:";
	char str12[20] = "黑方胜利";
	char str13[20] = "红方胜利";
	char str14[20] = "平局";
	int str9h = textheight(str9);  int str9w = textwidth(str9);//红方得分
	int str10h = textheight(str10);  int str10w = textwidth(str10);//黑方得分
	int str11h = textheight(str11);  int str11w = textwidth(str11);//平局数
	int str12h = textheight(str12);  int str12w = textwidth(str12);//黑方胜利
	int str13h = textheight(str13);  int str13w = textwidth(str13);//红方胜利
	int str14h = textheight(str14);  int str14w = textwidth(str14);//平局
	char win = get_winplayer();
	if (win == 'x' || win == 'o' || win == 'p') {
		if (check.gameover == 0) {
			gameover_yx();
			check.gameover++;
		}
	}
	if (win == 'o') {
		settextcolor(BLACK);
		outtextxy(120 + 195 - (str12w / 2), 0 + 195 - (str12h / 2), str12);
		settextcolor(BLUE);
	}
	if (win == 'x') {
		settextcolor(RED);
		outtextxy(120 + 195 - (str13w / 2), 0 + 195 - (str13h / 2), str13);
		settextcolor(BLUE);
	}
	if (win == 'p') {
		settextcolor(GREEN);
		outtextxy(120 + 195 - (str14w / 2), 0 + 195 - (str14h / 2), str14);
		settextcolor(BLUE);
	}
	char strx[20] = { 0 };
	char stro[20] = { 0 };
	char strp[20] = { 0 };
	sprintf_s(strx, "%d", cnt.x);
	sprintf_s(stro, "%d", cnt.o);
	sprintf_s(strp, "%d", cnt.p);
	outtextxy(155, 390 - str9h - 20, str9);//红方
	outtextxy(510 - (cnt.o + '0') - str10w + 20, 390 - str10h - 20, str10);//黑方
	outtextxy(160 + str9w + (cnt.x + '0') - 20, 390 - str11h - 20, str11);//平局
	outtextxy(155 + str9w, 390 - str9h - 20, strx);//红方得分
	outtextxy(510 - (cnt.p + '0') + 20, 390 - str10h - 20, stro);//黑方得分
	outtextxy(160 + str9w + (cnt.x + '0') - 20 + str11w, 390 - str11h - 20, strp);//平局数
}

//游戏结束的音效
void gameover_yx() {
	char win = get_winplayer();
	if (win == 'o') {
		check.game = 1;
		cnt.o++;
		if (check.yx == 1) {
			if (check.sr == 1) {//双人时
				mciSendString("play F:\\resource\\victory.mp3", 0, 0, 0);
			}
			else if (check.rj == 1) {
				if (win == player) {
					mciSendString("play F:\\resource\\victory.mp3", 0, 0, 0);
				}
				else if (win == cp) {
					mciSendString("play F:\\resource\\defeat.mp3", 0, 0, 0);
				}
			}
		}
	}
	else if (win == 'x') {
		check.game = 1;
		cnt.x++;
		if (check.yx == 1) {
			if (check.sr == 1) {//双人时
				mciSendString("play F:\\resource\\victory.mp3", 0, 0, 0);
			}
			else if (check.rj == 1) {
				if (win == player) {
					mciSendString("play F:\\resource\\victory.mp3", 0, 0, 0);
				}
				else if (win == cp) {
					mciSendString("play F:\\resource\\defeat.mp3", 0, 0, 0);
				}
			}
		}
	}
	else if (win == 'p') {
		check.game = 1;
		cnt.p++;
	}
	return;
}
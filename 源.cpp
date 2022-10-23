#include<iostream>
#include<graphics.h>
#include<mmsystem.h>//��ý���豸�ӿ�ͷ�ļ�
#include<cstring>
#include<time.h>
#include<stdlib.h>
#pragma comment(lib, "winmm.lib")//���ؾ�̬��

using namespace std;
int mainmenu();//���˵�
void menurj_level();//�˻���ս�˵�,ѡ���ս�Ѷ�
void menurj_sh();//�˻���ս�˵���ѡ���Ⱥ���
int game_sr();//˫�˶�ս
int game_rj_easy_1st();//�˻���ս���򵥣�����
int game_rj_difficulty_1st();//�˻���ս���ѣ�����
int game_rj_easy_2nd();//�˻���ս���򵥣�����
int game_rj_difficulty_2nd();//�˻���ս���ѣ�����
void menusy();//�����˵�
void menusy_bjyy();//�������ֲ˵�
void menusy_yx();//��Ч�˵�
void open_sy_bjyy();//����������
void open_sy_yx();//����Ч
void close_sy_yx();//����Ч
void close_sy_bjyy();//�ر�������(��ʵ����ͣ����)
int evalute();//������ֵ
int minmax(int depth, int alpha, int beta);//minmax�㷨
char get_winplayer();//�ҵ�Ӯ��
int event_player();//����¼�����Ϸ��ʾ
int player_move();//�������
int player_huiqi();//��һ���
void move_easy_cp();//��������,��
void move_difficulty_cp();//�������ӣ���
void gameover();//��Ϸ����
void gameover_yx();//��Ϸ����ʱ����Ч
void show_tb();//��ʾ����
IMAGE img_jzqbackground1; IMAGE img_jzqbackground2; IMAGE img_jzqTboard; IMAGE img_jzqx; IMAGE img_jzqo;
//      ���˵�����               ��Ϸ����                       ����             x                 o    
IMAGE img_jzqbjyy; IMAGE img_jzqyx; IMAGE img_jzqbjyyx; IMAGE img_jzqyxx; IMAGE img_jzqmenubackground;
//       ��������           ��Ч            ��������x            ��Чx              �˵�������
MOUSEMSG m;//���
struct {
	int rj;//����˻���Ϸ��0�ǲ��ǣ�1����
	int sr;//���˫����Ϸ��0�ǲ��ǣ�1����
	int level;//�Ѷ�ϵ���жϲ�����1�Ǽ򵥣�2����
	int bjyy;//1�Ǳ������ֿ���2�ǹ�
	int yx;//1����Ч����2�ǹ�
	int game;//�ж���Ϸ�Ƿ���У�0�ǽ��У�1�ǽ���(��������)
	int jx;//�ж��˳���Ϸ������
	int gameover;//�ж���Ϸ���������ʾ
	int over;//1���˳���Ϸ
}check;
struct {
	int x;//x��ʤ������
	int o;//o��ʤ������
	int p;//ƽ�ֳ���
	int move;//�ƶ�����
}cnt;
struct {
	int x;//��
	int y;//��
}save[10];
pair <int, int> best_point;//���Ž� 
char tb[3][3] = { 0 };//����
char cur_player = ' ';//��¼��ǰ����������,o�����֣�x�Ǻ���
int cur_depth = 9;//һ����9������
int wq = 10000000;//�ܴ��ֵ
char player = ' ';//����õ�ʲô����
char cp = ' ';//�����õ�ʲô����

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
	mainmenu();//���˵�
	return 0;
}

// ���˵�
int mainmenu() {
	char str1[20] = "��������Ϸ";
	char str2[20] = "< �˻���ս >";
	char str3[20] = "< ˫�˶�ս >";
	char str4[20] = "< �������� >";
	char str5[20] = "< �˳���Ϸ >";
	char str6[20] = "���˵�";
	settextcolor(BLUE);
	setbkmode(TRANSPARENT);
	settextstyle(0, 0, "����");
	int str1h = textheight(str1);  int str1w = textwidth(str1);
	int str2h = textheight(str2);  int str2w = textwidth(str2);
	int str3h = textheight(str3);  int str3w = textwidth(str3);
	int str4h = textheight(str4);  int str4w = textwidth(str4);
	int str5h = textheight(str5);  int str5w = textwidth(str5);
	int str6h = textheight(str6);  int str6w = textwidth(str6);
	BeginBatchDraw();
	putimage(0, 0, &img_jzqbackground1);
	outtextxy(0 + 255 - (str1w / 2), 0 + 56 - (str1h / 2), str1);//��������Ϸ
	outtextxy(0 + 255 - (str2w / 2), 112 + 28 - (str2h / 2), str2);//�˻���ս
	outtextxy(0 + 255 - (str3w / 2), 168 + 28 - (str3h / 2), str3);//˫�˶�ս
	outtextxy(0 + 255 - (str4w / 2), 224 + 28 - (str4h / 2), str4);//��������
	outtextxy(0 + 255 - (str5w / 2), 280 + 28 - (str5h / 2), str5);//�˳���Ϸ
	outtextxy(0 + 255 - (str6w / 2), 0 + 56 - (str1h / 2) + 40, str6);//�˵�
	EndBatchDraw();
	m = GetMouseMsg();
	while (1) {
		if (MouseHit()) {//����ƶ�
			m = GetMouseMsg();//���������Ϣ
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 255 - (str2w / 2) && m.x < 255 + (str2w / 2) &&
					m.y >140 - (str2h / 2) && m.y < 140 + (str2h / 2)) {//����˻���ս
					check.rj = 1;
					menurj_level();
					return 1;
				}
				if (m.x > 255 - (str3w / 2) && m.x < 255 + (str3w / 2) &&
					m.y >196 - (str3h / 2) && m.y < 196 + (str3h / 2)) {//���˫�˶�ս
					check.sr = 1;
					cnt.move += 1;
					game_sr();
					return 1;
				}
				if (m.x > 255 - (str4w / 2) && m.x < 255 + (str4w / 2) &&
					m.y >252 - (str4h / 2) && m.y < 252 + (str4h / 2)) {//�����������
					menusy();
					return 1;
				}
				if (m.x > 255 - (str5w / 2) && m.x < 255 + (str5w / 2) &&
					m.y >308 - (str5h / 2) && m.y < 308 + (str5h / 2)) {//����˳���Ϸ
					return 1;
				}
			}
		}
	}
	return 1;
}

//�˻���ս�˵�,ѡ���ս�Ѷ�
void menurj_level() {
	cleardevice();
	char str1[20] = "��������Ϸ";
	char str2[20] = "�Ѷ�ѡ��";
	char str3[20] = "< �� >";
	char str4[20] = "< �� >";
	char str6[20] = "�˵�";
	char str7[20] = "[������һ��]";
	int str1h = textheight(str1);  int str1w = textwidth(str1);
	int str2h = textheight(str2);  int str2w = textwidth(str2);
	int str3h = textheight(str3);  int str3w = textwidth(str3);
	int str4h = textheight(str4);  int str4w = textwidth(str4);
	int str6h = textheight(str6);  int str6w = textwidth(str6);
	int str7h = textheight(str7);  int str7w = textwidth(str7);
	BeginBatchDraw();
	putimage(0, 0, &img_jzqbackground1);
	outtextxy(0 + 255 - (str1w / 2), 0 + 56 - (str1h / 2), str1);//��������Ϸ
	outtextxy(0 + 255 - (str2w / 2), 112 + 28 - (str2h / 2), str2);//�Ѷ�ѡ��
	outtextxy(0 + 255 - (str3w / 2), 168 + 28 - (str3h / 2), str3);//��
	outtextxy(0 + 255 - (str4w / 2), 224 + 28 - (str4h / 2), str4);//��
	outtextxy(0 + 255 - (str6w / 2), 0 + 56 - (str1h / 2) + 40, str6);//�˵�
	outtextxy(510 - str7w, 0, str7);//������һ��
	EndBatchDraw();
	m = GetMouseMsg();
	while (1) {
		if (MouseHit()) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 255 - (str3w / 2) && m.x < 255 + (str3w / 2) &&
					m.y > 196 - (str3h / 2) && m.y < 196 + (str3h / 2)) {//�����
					check.level = 1;
					menurj_sh();
					return;
				}
				if (m.x > 255 - (str4w / 2) && m.x < 255 + (str4w / 2) &&
					m.y > 252 - (str4h / 2) && m.y < 252 + (str4h / 2)) {//�����
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

//�����˵�
void menusy() {
	cleardevice();
	char str1[20] = "��������Ϸ";
	char str2[20] = "��������";
	char str3[20] = "< �������� >";
	char str4[20] = "< ��Ч >";
	char str6[20] = "�˵�";
	char str7[20] = "[������һ��] ";
	int str1h = textheight(str1);  int str1w = textwidth(str1);
	int str2h = textheight(str2);  int str2w = textwidth(str2);
	int str3h = textheight(str3);  int str3w = textwidth(str3);
	int str4h = textheight(str4);  int str4w = textwidth(str4);
	int str6h = textheight(str6);  int str6w = textwidth(str6);
	int str7h = textheight(str7);  int str7w = textwidth(str7);
	BeginBatchDraw();
	putimage(0, 0, &img_jzqbackground1);
	outtextxy(0 + 255 - (str1w / 2), 0 + 56 - (str1h / 2), str1);//��������Ϸ
	outtextxy(0 + 255 - (str2w / 2), 112 + 28 - (str2h / 2), str2);//��������
	outtextxy(0 + 255 - (str3w / 2), 168 + 28 - (str3h / 2), str3);//��������
	outtextxy(0 + 255 - (str4w / 2), 224 + 28 - (str4h / 2), str4);//��Ч
	outtextxy(0 + 255 - (str6w / 2), 0 + 56 - (str1h / 2) + 40, str6);//�˵�
	outtextxy(510 - str7w, 0, str7);//������һ��
	EndBatchDraw();
	m = GetMouseMsg();
	while (1) {
		if (MouseHit()) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 255 - (str3w / 2) && m.x < 255 + (str3w / 2) &&
					m.y > 196 - (str3h / 2) && m.y < 196 + (str3h / 2)) {//�����������
					menusy_bjyy();
					return;
				}
				if (m.x > 255 - (str4w / 2) && m.x < 255 + (str4w / 2) &&
					m.y > 252 - (str4h / 2) && m.y < 252 + (str4h / 2)) {//�����Ч
					menusy_yx();
					return;
				}
				if (m.x > 390 && m.x < 390 + str7w &&
					m.y > 0 && m.y < str7h) {//������һ��
					mainmenu();
					return;
				}
			}
		}
	}
	return;
}

//�˻���ս�˵���ѡ���Ⱥ���
void menurj_sh() {
	cleardevice();
	char str1[20] = "��������Ϸ";
	char str2[20] = "�Ⱥ���ѡ��";
	char str3[20] = "< ���� >";
	char str4[20] = "< ���� >";
	char str6[20] = "�˵�";
	char str7[20] = "[������һ��]";
	int str1h = textheight(str1);  int str1w = textwidth(str1);
	int str2h = textheight(str2);  int str2w = textwidth(str2);
	int str3h = textheight(str3);  int str3w = textwidth(str3);
	int str4h = textheight(str4);  int str4w = textwidth(str4);
	int str6h = textheight(str6);  int str6w = textwidth(str6);
	int str7h = textheight(str7);  int str7w = textwidth(str7);
	BeginBatchDraw();
	putimage(0, 0, &img_jzqbackground1);
	outtextxy(0 + 255 - (str1w / 2), 0 + 56 - (str1h / 2), str1);//��������Ϸ
	outtextxy(0 + 255 - (str2w / 2), 112 + 28 - (str2h / 2), str2);//�Ⱥ���ѡ��
	outtextxy(0 + 255 - (str3w / 2), 168 + 28 - (str3h / 2), str3);//����
	outtextxy(0 + 255 - (str4w / 2), 224 + 28 - (str4h / 2), str4);//����
	outtextxy(0 + 255 - (str6w / 2), 0 + 56 - (str1h / 2) + 40, str6);//�˵�
	outtextxy(510 - str7w, 0, str7);//������һ��
	EndBatchDraw();
	m = GetMouseMsg();
	while (1) {
		if (MouseHit()) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 255 - (str3w / 2) && m.x < 255 + (str3w / 2) &&
					m.y > 196 - (str3h / 2) && m.y < 196 + (str3h / 2)) {//�������,o
					player = 'o';
					cp = 'x';
					check.rj = 1;
					if (check.level == 1) {//�˻���ս���򵥣�����
						game_rj_easy_1st();
						return;
					}
					if (check.level == 2) {//�˻���ս���ѣ�����
						game_rj_difficulty_1st();
						return;
					}
				}
				if (m.x > 255 - (str4w / 2) && m.x < 255 + (str4w / 2) &&
					m.y > 252 - (str4h / 2) && m.y < 252 + (str4h / 2)) {//�������,x
					player = 'x';
					cp = 'o';
					check.rj = 1;
					if (check.level == 1) {//�˻���ս���򵥣�����
						game_rj_easy_2nd();
						return;
					}
					if (check.level == 2) {//�˻���ս���ѣ�����
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

//�������ֲ˵�
void menusy_bjyy() {
	cleardevice();
	char str1[20] = "��������Ϸ";
	char str2[20] = "��������";
	char str3[20] = "< ��������  �� >";
	char str4[20] = "< ��������  �� >";
	char str5[20] = "[������һ��]";
	char str6[20] = "�˵�";
	settextcolor(BLUE);
	cleardevice();
	setbkmode(TRANSPARENT);
	settextstyle(0, 0, "����");
	int str1h = textheight(str1);  int str1w = textwidth(str1);
	int str2h = textheight(str2);  int str2w = textwidth(str2);
	int str3h = textheight(str3);  int str3w = textwidth(str3);
	int str4h = textheight(str4);  int str4w = textwidth(str4);
	int str5h = textheight(str5);  int str5w = textwidth(str5);
	int str6h = textheight(str6);  int str6w = textwidth(str6);
	BeginBatchDraw();
	putimage(0, 0, &img_jzqbackground1);
	outtextxy(0 + 255 - (str1w / 2), 0 + 56 - (str1h / 2), str1);//��������Ϸ
	outtextxy(0 + 255 - (str2w / 2), 112 + 28 - (str2h / 2), str2);//������������
	outtextxy(0 + 255 - (str3w / 2), 168 + 28 - (str3h / 2), str3);//�������ֿ�
	outtextxy(0 + 255 - (str4w / 2), 224 + 28 - (str4h / 2), str4);//�������ֹ�
	outtextxy(510 - str5w, 0, str5);//������һ��
	outtextxy(0 + 255 - (str6w / 2), 0 + 56 - (str1h / 2) + 40, str6);//�˵�
	EndBatchDraw();
	m = GetMouseMsg();
	while (1) {
		if (MouseHit()) {//����ƶ�
			m = GetMouseMsg();//���������Ϣ
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 255 - (str3w / 2) && m.x < 255 + (str3w / 2) &&
					m.y >196 - (str3h / 2) && m.y < 196 + (str3h / 2)) {//�������ֿ�
					check.bjyy = 1;
					open_sy_bjyy();
				}
				if (m.x > 255 - (str4w / 2) && m.x < 255 + (str4w / 2) &&
					m.y >252 - (str4h / 2) && m.y < 252 + (str4h / 2)) {//�������ֹ�
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

//��Ч�˵�
void menusy_yx() {
	cleardevice();
	char str1[20] = "��������Ϸ";
	char str2[20] = "��Ч";
	char str3[20] = "< ��Ч  �� >";
	char str4[20] = "< ��Ч  �� >";
	char str5[20] = "[������һ��]";
	char str6[20] = "�˵�";
	settextcolor(BLUE);
	cleardevice();
	setbkmode(TRANSPARENT);
	settextstyle(0, 0, "����");
	int str1h = textheight(str1);  int str1w = textwidth(str1);
	int str2h = textheight(str2);  int str2w = textwidth(str2);
	int str3h = textheight(str3);  int str3w = textwidth(str3);
	int str4h = textheight(str4);  int str4w = textwidth(str4);
	int str5h = textheight(str5);  int str5w = textwidth(str5);
	int str6h = textheight(str6);  int str6w = textwidth(str6);
	BeginBatchDraw();
	putimage(0, 0, &img_jzqbackground1);
	outtextxy(0 + 255 - (str1w / 2), 0 + 56 - (str1h / 2), str1);//��������Ϸ
	outtextxy(0 + 255 - (str2w / 2), 112 + 28 - (str2h / 2), str2);//������������
	outtextxy(0 + 255 - (str3w / 2), 168 + 28 - (str3h / 2), str3);//�������ֿ�
	outtextxy(0 + 255 - (str4w / 2), 224 + 28 - (str4h / 2), str4);//�������ֹ�
	outtextxy(510 - str5w, 0, str5);//������һ��
	outtextxy(0 + 255 - (str6w / 2), 0 + 56 - (str1h / 2) + 40, str6);//�˵�
	EndBatchDraw();
	m = GetMouseMsg();
	while (1) {
		if (MouseHit()) {//����ƶ�
			m = GetMouseMsg();//���������Ϣ
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 255 - (str3w / 2) && m.x < 255 + (str3w / 2) &&
					m.y >196 - (str3h / 2) && m.y < 196 + (str3h / 2)) {//��Ч��
					check.yx = 1;
				}
				if (m.x > 255 - (str4w / 2) && m.x < 255 + (str4w / 2) &&
					m.y >252 - (str4h / 2) && m.y < 252 + (str4h / 2)) {//��Ч��
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

//�򿪱�������
void open_sy_bjyy() {
	mciSendString("play F:\\resource\\jzqbgm.mp3 repeat", 0, 0, 0);//����
}

//�ر�������
void close_sy_bjyy() {
	mciSendString("pause F:\\resource\\jzqbgm.mp3", 0, 0, 0);
}

//����Ч
void open_sy_yx() {
	mciSendString("play F:\\resource\\jzqyxo.mp3", 0, 0, 0);
	Sleep(200);
}

//����Ч
void close_sy_yx() {
	mciSendString("pause F:\\resource\\jzqyxo.mp3", 0, 0, 0);
	mciSendString("pause F:\\resource\\victory.mp3", 0, 0, 0);
	mciSendString("pause F:\\resource\\defeat.mp3", 0, 0, 0);
}

//check.jx�������ͽ�����Ϸ
//== 1 ���˳���Ϸ
//== 0 �Ǽ�����Ϸ
//== 2 �ǻ����ʱ��ת������¼�

//˫�˶�ս
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

//�˻���ս���򵥣�����
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

//�˻���ս���򵥣�����
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

//�˻���ս���ѣ�����
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

//�˻���ս���ѣ�����
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

//��ʾ����
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

//����¼�,��Ϸ����
int event_player() {
	check.gameover = 0;
	check.over = 0;
	m = GetMouseMsg();
	while (1) {
		if (MouseHit()) {
			cleardevice();
			char str1[20] = "��������Ϸ";
			char str2[20] = "�˵���";
			char str3[20] = "����";
			char str4[20] = "����һ��";
			char str5[20] = "�������˵�";
			char str6[20] = "�˳���Ϸ";
			char str7[20] = "��������";
			char str8[20] = "��Ч";
			settextcolor(BLUE);
			cleardevice();
			setbkmode(TRANSPARENT);
			int str1h = textheight(str1);  int str1w = textwidth(str1);
			int str2h = textheight(str2);  int str2w = textwidth(str2);
			int str3h = textheight(str3);  int str3w = textwidth(str3);//����
			int str4h = textheight(str4);  int str4w = textwidth(str4);//����һ��
			int str5h = textheight(str5);  int str5w = textwidth(str5);//�������˵�
			int str6h = textheight(str6);  int str6w = textwidth(str6);//�˳���Ϸ
			int str7h = textheight(str7);  int str7w = textwidth(str7);//��������
			int str8h = textheight(str8);  int str8w = textwidth(str8);//��Ч
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
			settextstyle(20, 10, "����");
			outtextxy(55 - (str1w / 2), 0 + 56 - (str1h / 2), str1);//��������Ϸ
			outtextxy(55 - (str2w / 2), 92 + 28 - (str2h / 2), str2);//�˵�
			outtextxy(55 - (str3w / 2), 148 + 28 - (str3h / 2), str3);//����
			outtextxy(55 - (str4w / 2), 204 + 28 - (str4h / 2), str4);//���¿�ʼ
			outtextxy(55 - (str5w / 2), 260 + 28 - (str5h / 2), str5);//�������˵�
			outtextxy(55 - (str6w / 2), 316 + 28 - (str6h / 2), str6);//�˳���Ϸ
			settextstyle(0, 0, "����");
			outtextxy(160, 0 + 30 - (str7h / 2), str7);//��������
			outtextxy(355, 0 + 30 - (str8h / 2), str8);//��Ч
			gameover();
			EndBatchDraw();
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 60 - (str3w / 2) && m.x < 60 + (str3w / 2) &&
					m.y >176 - (str3h / 2) && m.y < 176 + (str3h / 2)) {//����
					if (cnt.move > 1) {
						int huiqi = player_huiqi();
						return huiqi;
					}
				}
				if (m.x > 60 - (str4w / 2) && m.x < 60 + (str4w / 2) &&
					m.y >232 - (str4h / 2) && m.y < 232 + (str4h / 2)) {//����һ��
					if (get_winplayer() == 'x' || get_winplayer() == 'o' || get_winplayer() == 'p') {
						int check_zlyj = MessageBox(NULL, "ȷ������һ����", "ѡ��", MB_OKCANCEL);
						if (check_zlyj == IDOK) {
							memset(tb, ' ', sizeof(tb));
							cur_depth = 9;
							check.game = 0;
							cnt.move = 0;
							check.jx = 0;
							if (check.sr == 1) {//��ǰ��˫����Ϸ
								check.over = game_sr();
								if (check.over == 1) {
									return 1;
								}
							}
							if (check.rj == 1) {//��ǰ���˻�
								if (check.level == 1 && player == 'o') {//�˻���ս���򵥣�����
									check.over = game_rj_easy_1st();
									if (check.over == 1) {
										return 1;
									}
								}
								if (check.level == 2 && player == 'o') {//�˻���ս���ѣ�����
									check.over = game_rj_difficulty_1st();
									if (check.over == 1) {
										return 1;
									}
								}
								if (check.level == 1 && player == 'x') {//�˻���ս���򵥣�����
									check.over = game_rj_easy_2nd();
									if (check.over == 1) {
										return 1;
									}
								}
								if (check.level == 2 && player == 'x') {//�˻���ս���ѣ�����
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
					m.y >288 - (str5h / 2) && m.y < 288 + (str5h / 2)) {// �������˵�
					int check_zcd = MessageBox(NULL, "ȷ�Ϸ������˵���", "ѡ��", MB_OKCANCEL);
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
					m.y >344 - (str6h / 2) && m.y < 344 + (str6h / 2)) {//�˳���Ϸ
					int check_end = MessageBox(NULL, "ȷ���˳���Ϸ��", "ѡ��", MB_OKCANCEL);
					if (check_end == IDOK) {
						check.over = 1;
						return 1;
					}
				}
				if (m.x > 160 + str7w && m.x < 160 + str7w + 60 &&
					m.y > 0 && m.y < 60) {//��������
					if (check.bjyy == 1) {
						check.bjyy = 2;//�ر�������
						close_sy_bjyy();
						putimage(160 + str7w, 0, &img_jzqbjyyx);
					}
					else if (check.bjyy == 2) {
						check.bjyy = 1;//����������
						open_sy_bjyy();
						putimage(160 + str7w, 0, &img_jzqbjyy);
					}
				}
				if (m.x > 355 + str8w && m.x < 355 + str8w + 60 &&
					m.y > 0 && m.y < 60) {//��Ч
					if (check.yx == 1) {
						check.yx = 2;//����Ч
						close_sy_yx();
						putimage(355 + str8w, 0, &img_jzqyxx);
					}
					else if (check.yx == 2) {
						check.yx = 1;//����Ч
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

//��һ���
int player_huiqi() {
	int check_huiqi = MessageBox(NULL, "ȷ�ϻ�����", "ѡ��", MB_OKCANCEL);
	if (check_huiqi == IDOK) {
		check.game = 0;//��������
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
		if (check.sr == 1) {//˫��ʱ
			tb[save[cnt.move].y][save[cnt.move].x] = ' ';
			cnt.move--;
			return 0;
		}
		if (check.rj == 1) {
			if (player == 'o') {//�������
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
			if (player == 'x') {//��Һ���
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

//�������
int player_move() {
	if (m.x > 180 && m.x < 270 &&
		m.y > 60 && m.y < 150) {//������0,0
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
		m.y > 60 && m.y < 150) {//������0,1
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
		m.y > 60 && m.y < 150) {//������0,2
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
		m.y > 150 && m.y < 240) {//������1,0
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
		m.y > 150 && m.y < 240) {//������1,1
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
		m.y > 150 && m.y < 240) {//������1,2
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
		m.y > 240 && m.y < 330) {//������2,0
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
		m.y > 240 && m.y < 330) {//������2,1
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
		m.y > 240 && m.y < 330) {//������2,2
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

//minmax�㷨
int minmax(int depth, int alpha, int beta) {
	int cur_value = 0;
	int	best_value = 0;
	int	cnt = 0;
	pair <int, int> p[10];
	if (get_winplayer() == player || get_winplayer() == cp || depth == 0) {
		return evalute();
	}
	if (cur_player == cp) {//��û����
		best_value = -wq;
	}
	else if (cur_player == player) {//��û����
		best_value = wq;
	}
	for (int i = 0; i < 3; i++) {//ʣ���
		for (int j = 0; j < 3; j++) {
			if (tb[i][j] == ' ') {
				p[cnt].first = i;
				p[cnt].second = j;
				cnt++;
			}
		}
	}
	for (int i = 0; i < cnt; i++) {
		pair<int, int> cur_point = p[i];//��ǰ��
		int x = cur_point.first;
		int y = cur_point.second;
		tb[x][y] = cur_player;//�����������ӣ��������ѷ��ʣ�
		cur_player = (cur_player == player) ? cp : player;
		cur_value = minmax(depth - 1, alpha, beta);//��������
		tb[x][y] = ' ';//ȡ�����壨���ݣ�
		cur_player = (cur_player == player) ? cp : player;
		if (cur_player == cp) {//max�ڵ�
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
		else if (cur_player == player) {//min�ڵ�
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

//�ҵ�Ӯ��
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
	for (i = 0; i < 3; i++) {//3�� 
		if (tb[i][0] == tb[i][1] && tb[i][1] == tb[i][2] && tb[i][0] != ' ') {
			return tb[i][0];
		}
	}
	for (j = 0; j < 3; j++) {//3��
		if (tb[0][j] == tb[1][j] && tb[1][j] == tb[2][j] && tb[0][j] != ' ') {
			return tb[0][j];
		}
	}
	if (tb[0][0] == tb[1][1] && tb[1][1] == tb[2][2] && tb[0][0] != ' ') {//����б 
		return tb[0][0];
	}
	if (tb[2][0] == tb[1][1] && tb[1][1] == tb[0][2] && tb[2][0] != ' ') {//����б 
		return tb[2][0];
	}
	if (cnt == 9) {
		return 'p';
	}
	return '0';
}

//������ֵ
int evalute() {
	int i = 0;
	int j = 0;//�н��
	if (get_winplayer() == cp) {
		return wq;
	}
	if (get_winplayer() == player) {
		return -wq;
	}
	int value = 0;//�����Ӯ��ô��������ʼ�����ֵ
	char temp_tb[3][3] = { 0 };//��ʱ����
	memset(temp_tb, ' ', sizeof(temp_tb));
	for (i = 0; i < 3; i++) {//�����������
		for (j = 0; j < 3; j++) {
			if (tb[i][j] == ' ') {
				temp_tb[i][j] = cp;
			}
			else {
				temp_tb[i][j] = tb[i][j];
			}
		}
	}
	for (i = 0; i < 3; i++) {//3�� 
		if (temp_tb[i][0] == temp_tb[i][1] && temp_tb[i][1] == temp_tb[i][2] && temp_tb[i][0] == cp && temp_tb[i][0] != ' ')
			value += 10;
	}
	for (j = 0; j < 3; j++) {//3����
		if (temp_tb[0][j] == temp_tb[1][j] && temp_tb[1][j] == temp_tb[2][j] && temp_tb[0][j] == cp && temp_tb[0][j] != ' ')
			value += 10;
	}
	if (temp_tb[0][0] == temp_tb[1][1] && temp_tb[1][1] == temp_tb[2][2] && temp_tb[0][0] == cp && temp_tb[0][0] != ' ') {//����б 
		value += 10;
	}
	if (temp_tb[2][0] == temp_tb[1][1] && temp_tb[0][2] == temp_tb[1][1] && temp_tb[2][0] == cp && temp_tb[2][0] != ' ') {//����б 
		value += 10;
	}
	for (i = 0; i < 3; i++) {//�����������
		for (j = 0; j < 3; j++) {
			if (tb[i][j] == ' ') {
				temp_tb[i][j] = player;
			}
			else {
				temp_tb[i][j] = tb[i][j];
			}
		}
	}
	for (i = 0; i < 3; i++) {//3�� 
		if (temp_tb[i][0] == temp_tb[i][1] && temp_tb[i][1] == temp_tb[i][2] && temp_tb[i][0] == player && temp_tb[i][0] != ' ')
			value -= 10;
	}
	for (j = 0; j < 3; j++) {//3�� 
		if (temp_tb[0][j] == temp_tb[1][j] && temp_tb[1][j] == temp_tb[2][j] && temp_tb[0][j] == player && temp_tb[0][j] != ' ')
			value -= 10;
	}
	if (temp_tb[0][0] == temp_tb[1][1] && temp_tb[1][1] == temp_tb[2][2] && temp_tb[0][0] == player && temp_tb[0][0] != ' ') {//����б 
		value -= 10;
	}
	if (temp_tb[2][0] == temp_tb[1][1] && temp_tb[0][2] == temp_tb[1][1] && temp_tb[2][0] == player && temp_tb[2][0] != ' ') {//����б 
		value -= 10;
	}
	return value;
}

//��������,��
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

//�������ӣ���
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
				save[++cnt.move].x = y;//��
				save[cnt.move].y = x;//��
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

//��Ϸ���
void gameover() {
	char str9[20] = "�췽�÷�:";
	char str10[20] = "�ڷ��÷�:";
	char str11[20] = "ƽ����:";
	char str12[20] = "�ڷ�ʤ��";
	char str13[20] = "�췽ʤ��";
	char str14[20] = "ƽ��";
	int str9h = textheight(str9);  int str9w = textwidth(str9);//�췽�÷�
	int str10h = textheight(str10);  int str10w = textwidth(str10);//�ڷ��÷�
	int str11h = textheight(str11);  int str11w = textwidth(str11);//ƽ����
	int str12h = textheight(str12);  int str12w = textwidth(str12);//�ڷ�ʤ��
	int str13h = textheight(str13);  int str13w = textwidth(str13);//�췽ʤ��
	int str14h = textheight(str14);  int str14w = textwidth(str14);//ƽ��
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
	outtextxy(155, 390 - str9h - 20, str9);//�췽
	outtextxy(510 - (cnt.o + '0') - str10w + 20, 390 - str10h - 20, str10);//�ڷ�
	outtextxy(160 + str9w + (cnt.x + '0') - 20, 390 - str11h - 20, str11);//ƽ��
	outtextxy(155 + str9w, 390 - str9h - 20, strx);//�췽�÷�
	outtextxy(510 - (cnt.p + '0') + 20, 390 - str10h - 20, stro);//�ڷ��÷�
	outtextxy(160 + str9w + (cnt.x + '0') - 20 + str11w, 390 - str11h - 20, strp);//ƽ����
}

//��Ϸ��������Ч
void gameover_yx() {
	char win = get_winplayer();
	if (win == 'o') {
		check.game = 1;
		cnt.o++;
		if (check.yx == 1) {
			if (check.sr == 1) {//˫��ʱ
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
			if (check.sr == 1) {//˫��ʱ
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
#include<easyx.h>
#include<stdio.h>
#include <windows.h>
#pragma  comment (lib,"winmm.lib")
const int WIDTH = 400;   // ���
const int HEIGHT = 760;  // �߶�
const int INTERVAL = 48; // ���   ͼ��ü��
//  ����ͼƬ
IMAGE img_bk;
IMAGE img_item[3];    // ����һ���򵥵���ά����  ͷ������
void loadImg()
{
	loadimage(&img_bk, "images/bk.jpg", WIDTH, HEIGHT);
	loadimage(img_item + 0, "images/cao.png", 48, 48);
	loadimage(img_item + 1, "images/lingdang.png", 48, 48);
	loadimage(img_item + 2, "images/shu.png", 48, 48);
}
int main()
{
	initgraph(WIDTH, HEIGHT);
	loadImg();
	// ��������
	mciSendString(_T("open micc/yang.mp3"), 0, 0, 0);
	mciSendString(_T("play micc/yang.mp3"), 0, 0, 0);

	// ����һ��ͷ����
	// ��ʼ�� 
	int map[3][3] = { 0 };
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			map[r][c] = r + 1;  //1 2  3 
		}

	}
	// �����������
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
		  // ���鵱�е��к����������  1 2 3 
			int r1 = rand() % 3;  
			int c1 = rand() % 3;
			// �����к���  ��������
			int temp = map[r1][c1]; 2,3,
			map[r1][c1] = map[r][c];
			// ����
			map[r][c] = temp;
		}
	}
	// ��һ��  �����λ��������
	// �ҵ�ͼƬ x
	int  offsetX = (WIDTH - (2 * INTERVAL + 3 * 48)) / 2;
	// �ҵ�y��λ��
	int offsetY = (HEIGHT - (2 * INTERVAL + 3 * 48)) / 2;
	// 7����λ
	int store[7] = { 0 };

	// ���Ƶ�ͼ   1 ����  2 ����  3  ����
	while (true)
	{
		BeginBatchDraw();
		// ���Ƶ�ͼ  ������ͼ
		putimage(0, 0, &img_bk);
		// ����  ��Ⱦ
		for (int  r = 0; r < 3; r++)
		{
			for (int  c = 0; c < 3; c++)
			{
				if (map[r][c])
					// ��ʼ��Ⱦ             x  , y   ͼƬ
					putimage(offsetX + c * (48 + INTERVAL), offsetY + r * (48 + INTERVAL), 
						img_item + (map[r][c] - 1));
			}
		}
		for (int  i = 0; i < 7; i++)
		{
			if (store[i])
			{
				putimage((i * 50) + 26, 620, img_item + (store[i] - 1));
			}

		}
		EndBatchDraw();
		// ����  ��Ҫ �����  ����  ���������       
		ExMessage  msg = { 0 };
		// �������Ժ�  �Ƿ�����Ϣ  ��Ϣ��     VM_LBUTTONDOWN ���
		if (peekmessage(&msg) && msg.message ==WM_LBUTTONDOWN)
		{
			for (int r = 0; r < 3; r++) {
			
				for (int  c = 0; c < 3; c++)
				{
					// ��������x
					int  x = offsetX + c*(48 + INTERVAL);
					// �������y
					int y = offsetY + r * (48 + INTERVAL);
					// �ж�һ������Ƿ�����ͼƬ
					if (msg.x > x && msg.x < x + 48 && msg.y>y && msg.y < y + 48)
					{
						// ��� ͼƬ��Ӧ�����λ�� 
						int col = (msg.x - offsetX) / (48 + INTERVAL);
						int row = (msg.y - offsetY) / (48 + INTERVAL);

						// �������ͼƬ��Ⱦ�����������

						for (int i = 0; i < 7; i++)
						{
							// ���������û��
							if (store[i] == 0) {
							 //  �������������������ͼƬ
								store[i] = map[row][col];
								break;
							}
						}
						// ��¼һ�¸��ô���
						int cnt = 0;
						for (int  i = 0; i < 7; i++)
						{
							if (store[i] == map[row][col]) {
								cnt++;
							}
						}
						// ����ﵽ��3 
						if (cnt == 3)
						{
							for (int i = 0; i < 7; i++)
							{
								if (store[i] == map[row][col])
								{
									store[i] = 0;
								}
							}
						}
						map[row][col] = 0;
					}

				}
			
			}
		}

	}

	while (1);  // ��ֹ����
	return 0;
}
#include<easyx.h>
#include<stdio.h>
#include <windows.h>
#pragma  comment (lib,"winmm.lib")
const int WIDTH = 400;   // 宽度
const int HEIGHT = 760;  // 高度
const int INTERVAL = 48; // 间隔   图标得间隔
//  定义图片
IMAGE img_bk;
IMAGE img_item[3];    // 定义一个简单得三维数组  头得数组
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
	// 播放音乐
	mciSendString(_T("open micc/yang.mp3"), 0, 0, 0);
	mciSendString(_T("play micc/yang.mp3"), 0, 0, 0);

	// 创建一个头数组
	// 初始换 
	int map[3][3] = { 0 };
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			map[r][c] = r + 1;  //1 2  3 
		}

	}
	// 打乱这个数组
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
		  // 数组当中得行和列随机打乱  1 2 3 
			int r1 = rand() % 3;  
			int c1 = rand() % 3;
			// 打乱行和列  交换打乱
			int temp = map[r1][c1]; 2,3,
			map[r1][c1] = map[r][c];
			// 交换
			map[r][c] = temp;
		}
	}
	// 算一下  数组得位置再哪里
	// 找到图片 x
	int  offsetX = (WIDTH - (2 * INTERVAL + 3 * 48)) / 2;
	// 找到y得位置
	int offsetY = (HEIGHT - (2 * INTERVAL + 3 * 48)) / 2;
	// 7个卡位
	int store[7] = { 0 };

	// 绘制地图   1 定义  2 加载  3  绘制
	while (true)
	{
		BeginBatchDraw();
		// 绘制地图  背景地图
		putimage(0, 0, &img_bk);
		// 绘制  渲染
		for (int  r = 0; r < 3; r++)
		{
			for (int  c = 0; c < 3; c++)
			{
				if (map[r][c])
					// 开始渲染             x  , y   图片
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
		// 就是  需要 点击了  创建  下面得数组       
		ExMessage  msg = { 0 };
		// 点击鼠标以后  是否有消息  消息是     VM_LBUTTONDOWN 左键
		if (peekmessage(&msg) && msg.message ==WM_LBUTTONDOWN)
		{
			for (int r = 0; r < 3; r++) {
			
				for (int  c = 0; c < 3; c++)
				{
					// 鼠标坐标得x
					int  x = offsetX + c*(48 + INTERVAL);
					// 鼠标坐标y
					int y = offsetY + r * (48 + INTERVAL);
					// 判断一下鼠标是否点击了图片
					if (msg.x > x && msg.x < x + 48 && msg.y>y && msg.y < y + 48)
					{
						// 求出 图片对应数组得位置 
						int col = (msg.x - offsetX) / (48 + INTERVAL);
						int row = (msg.y - offsetY) / (48 + INTERVAL);

						// 点击到得图片渲染到下面得数组

						for (int i = 0; i < 7; i++)
						{
							// 下面得数组没有
							if (store[i] == 0) {
							 //  上面得数组给下面得数组图片
								store[i] = map[row][col];
								break;
							}
						}
						// 记录一下给得次数
						int cnt = 0;
						for (int  i = 0; i < 7; i++)
						{
							if (store[i] == map[row][col]) {
								cnt++;
							}
						}
						// 如果达到了3 
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

	while (1);  // 防止闪退
	return 0;
}
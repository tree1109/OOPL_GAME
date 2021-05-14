#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"

namespace game_framework {

	//
	// 未完成
	// size
	// madeline 48 x 48
	//
	//	block 24 x 24

	GameMap::GameMap()
		:X(20), Y(0), MW(24), MH(24), MAP_SIZE_H(20), MAP_SIZE_W(25)					// 給予地圖上左上角座標及每張小圖寬高
	{

		/*簡易地圖
		for (int y = 0; y < 19; y++) {
			for (int x = 0; x < 26; x++) {
				map[y][x] = 0;

			}
		}
		for (int x = 0; x < 26; x++) {
			map[19][x] = 1;
		}
		//*/

		//*三角
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 26; x++) {
				map[y][x] = 1 ? x + y >= 19 && (y > 11 || y < 9) : 0;
			}
		}
		//*/
		int init_map[20][25] = {
		{-1, 16, 5, 21, 16, 16, 16, 21, 21, 21, 21, 14, -1, -1, 31, 31, 36, 36, 36, 36, 5, 36, 36, 51, 51},
		{ 13, 21, 6, -1, 20, 21, 22, -1, -1, -1, -1, 15, 16, 28, 36, 37, -1, -1, -1, -1, 6, -1, -1, -1, -1 },
		{ 32, -1, 6, -1, -1, -1, 6, -1, -1, -1, -1, 30, 31, 32, -1, -1, -1, -1, -1, -1, 6, -1, -1, -1, -1 },
		{ 32, -1, 6, 1, 7, -1, 6, -1, -1, -1, -1, 30, 31, 32, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1 },
		{ 32, -1, 6, -1, -1, -1, 6, -1, -1, -1, -1, 35, 36, 37, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ 32, -1, 6, -1, -1, -1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ 32, -1, 5, 1, 1, 1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, 1, 1, 7, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 6, -1, -1, 6, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 6, -1, -1, 6, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 6, 1, 1, 6, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 6, -1, 15, 17, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, 11, 19, 17, 8, 8, 8, 8 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, 26, 27, -1, -1, -1, -1, -1, 15, 16, -1, 18, 11, 11, 11, 12 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, 30, 31, 32, -1, -1, -1, -1, -1, 15, 16, -1, -1, 16, 16, 16, 17 },
		{ 11, 11, 26, 27, -1, -1, -1, -1, -1, 30, 31, 32, 8, 8, 8, 8, 8, 15, 16, -1, -1, -1, -1, 31, 17 },
		{ -1, -1, 31, 32, 8, 8, 8, 8, 8, 30, 31, 33, 26, 26, 11, 11, 11, 19, -1, -1, -1, -1, -1, 31, 32 },
		{ -1, -1, 31, 33, 26, 26, 26, 26, 26, 34, 31, 31, 31, 31, 31, 16, 16, -1, -1, -1, -1, -1, -1, -1, 33 },
		{ -1, -1, 31, 31, 31, 31, 31, 31, 31, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
		};


	}

	void GameMap::LoadBitmap()
	{
		block_1.LoadBitmap("Bitmaps\\tile\\032.bmp", RGB(255, 0, 255));
		//tiled.push_back(new CMovingBitmap().LoadBitmap("Bitmaps\\tile\\032.bmp", RGB(255, 0, 255)));
		//block_1.LoadBitmap("Bitmaps\\sad.bmp", RGB(0, 0, 0));
		
		/*
		stringstream path;
		char* path_s;
		for (int i = 0; i < 55; i++) {
			path << "Bitmaps\\tile\\" << (i % 1000) / 100 << (i % 100) / 10 << i % 10 << ".bmp";
			strcpy(path_s, path.str().c_str());
			tiled[i].LoadBitmap(path_s, RGB(255, 0, 255));
			//_snprintf(path, sizeof(path), "Bitmaps\\tile\\%d%d%d.bmp", (i % 1000)/100, (i % 100)/10, i % 10);
			//tiled[i].LoadBitmap(path, RGB(255, 0, 255));
		}
		//*/
	}

	void GameMap::OnShow()
	{
		for (int y = 0; y < MAP_SIZE_H; y++)
			for (int x = 0; x < MAP_SIZE_W; x++)
			{
				int tmp(map[y][x]);
				switch (tmp) {
				case 0:
					break;
				case 1:
					//tiled.at(1).SetTopLeft(X + (MW * x), Y + (MH * y));
					//tiled.at(1).ShowBitmap();
					block_1.SetTopLeft(X + (MW * x), Y + (MH * y));
					block_1.ShowBitmap();
					break;
				default:
					ASSERT(0);										//map陣列不該出現0, 1, 2以外的值
				}
			}
	}

	void GameMap::OnMove()
	{

	}

	bool GameMap::isCollided(int x_pos, int y_pos, int width, int height)
	{
		for (int y = 0; y < MAP_SIZE_H; y++)
			for (int x = 0; x < MAP_SIZE_W; x++)
			{
				// 取得方塊實際位置
				const int block_x_pos = x * 24 + X;
				const int block_y_pos = y * 24 + Y;

				// AABB
				if (map[y][x] != 0 &&
					x_pos + width - 1 > block_x_pos &&
					x_pos < block_x_pos + 23 &&
					y_pos + height - 1 > block_y_pos &&
					y_pos < block_y_pos + 23
					)
				{
					return true;
				}
			}
		return false;
	}

	GameMap::~GameMap()
	{

	}
}
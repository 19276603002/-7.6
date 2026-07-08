#ifndef SCENIC_SPOT_H
#define SCENIC_SPOT_H

#include "global.h"

// 初始化景点列表（内置默认数据）
void initSpotList(ScenicSpot spots[], int *count);

// 添加新景点，成功返回1，失败返回0
int addSpot(ScenicSpot spots[], int *count, ScenicSpot newSpot);

// 根据景点编号查找下标，未找到返回-1
int findSpotById(ScenicSpot spots[], int count, int id);

// 打印所有景点列表
void printAllSpots(ScenicSpot spots[], int count);

// 打印单个景点详情
void printSpotDetail(ScenicSpot spots[], int count, int id);

#endif // SCENIC_SPOT_H
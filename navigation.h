#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "global.h"
#include "scenic_spot.h"

// 初始化路径列表（内置默认数据）
void initRouteList(Route routes[], int *count);

// 添加新路径，成功返回1，失败返回0
int addRoute(Route routes[], int *count, Route newRoute);

// 查询起点到终点的路径并打印结果
void queryRoute(Route routes[], int routeCount, ScenicSpot spots[], int spotCount, int startId, int endId);

// 打印所有路径列表
void printAllRoutes(Route routes[], int routeCount, ScenicSpot spots[], int spotCount);

// 创建邻接表图（内置默认景点和路径，无向图）
void createGraph(ALGraph *graph);

// 打印邻接表图的完整结构
void printGraph(ALGraph *graph);

#endif // NAVIGATION_H
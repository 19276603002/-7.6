#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 全局常量定义
#define MAX_SPOT_NUM 100   // 系统最大景点数量
#define MAX_ROUTE_NUM 200  // 系统最大路径数量
#define NAME_LEN 50        // 名称字段最大长度
#define ADDR_LEN 100       // 地址字段最大长度
#define DESC_LEN 200       // 描述/简介字段最大长度

// 景点信息结构体
typedef struct {
    int id;                 // 景点唯一编号
    char name[NAME_LEN];    // 景点名称
    char address[ADDR_LEN]; // 景点地址
    char intro[DESC_LEN];   // 景点简介
} ScenicSpot;

// 路径信息结构体
typedef struct {
    int startId;        // 起点景点编号
    int endId;          // 终点景点编号
    float distance;     // 路径距离（单位：公里）
    int duration;       // 预计通行时间（单位：分钟）
    char description[DESC_LEN]; // 路径详情描述
} Route;

// ========== 新增：邻接表图结构 ==========
// 边结点结构体：存储一条路径的邻接信息
typedef struct ArcNode {
    int adjvex;             // 邻接点在顶点数组中的下标
    float distance;         // 路径距离（公里）
    int duration;           // 预计通行时间（分钟）
    struct ArcNode *nextArc; // 指向下一条边结点
} ArcNode;

// 顶点结点结构体：存储一个景点 + 它的所有出边
typedef struct VNode {
    ScenicSpot data;        // 顶点存储的景点数据
    ArcNode *firstArc;      // 边表头指针，指向第一条依附该顶点的边
} VNode;

// 邻接表存储的图结构体
typedef struct {
    VNode vertices[MAX_SPOT_NUM]; // 顶点数组（存放所有景点）
    int vexNum;                   // 顶点总数（景点数）
    int arcNum;                   // 边总数（路径数）
} ALGraph;

#endif // GLOBAL_H
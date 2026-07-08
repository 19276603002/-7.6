#include "navigation.h"

void initRouteList(Route routes[], int *count) {
    int i;
    *count = 0;
    Route defaultRoutes[] = {
        {1, 2, 5.2f, 20, "沿滨海大道直行，全程主干道，红绿灯少"},
        {2, 3, 3.8f, 15, "经文化路过江隧道直达，无红绿灯"},
        {1, 3, 4.5f, 18, "穿市中心步行街，途经核心商业圈"}
    };
    for(i = 0; i < 3; i++) {
        routes[i] = defaultRoutes[i];
        (*count)++;
    }
}

int addRoute(Route routes[], int *count, Route newRoute) {
    if (*count >= MAX_ROUTE_NUM) {
        printf("路径数量已达上限，添加失败！\n");
        return 0;
    }
    routes[*count] = newRoute;
    (*count)++;
    printf("路径添加成功！\n");
    return 1;
}

void queryRoute(Route routes[], int routeCount, ScenicSpot spots[], int spotCount, int startId, int endId) {
    int i, found = 0;
    int startIdx = findSpotById(spots, spotCount, startId);
    int endIdx = findSpotById(spots, spotCount, endId);
    
    if (startIdx == -1 || endIdx == -1) {
        printf("起点或终点景点编号不存在！\n");
        return;
    }
    
    printf("===== 导航查询结果 =====\n");
    printf("起点：%s → 终点：%s\n", spots[startIdx].name, spots[endIdx].name);
    
    for (i = 0; i < routeCount; i++) {
        if (routes[i].startId == startId && routes[i].endId == endId) {
            printf("距离：%.1f公里\n", routes[i].distance);
            printf("预计耗时：%d分钟\n", routes[i].duration);
            printf("路径描述：%s\n", routes[i].description);
            found = 1;
            break;
        }
    }
    if (!found) printf("未查询到直达路径\n");
}

void printAllRoutes(Route routes[], int routeCount, ScenicSpot spots[], int spotCount) {
    int i;
    if (routeCount == 0) {
        printf("暂无路径信息\n");
        return;
    }
    printf("===== 全部路径列表 =====\n");
    printf("起点\t\t→\t终点\t\t距离\t耗时\n");
    for (i = 0; i < routeCount; i++) {
        int sIdx = findSpotById(spots, spotCount, routes[i].startId);
        int eIdx = findSpotById(spots, spotCount, routes[i].endId);
        char sName[NAME_LEN] = "未知景点";
        char eName[NAME_LEN] = "未知景点";
        if (sIdx != -1) strcpy(sName, spots[sIdx].name);
        if (eIdx != -1) strcpy(eName, spots[eIdx].name);
        printf("%s\t→\t%s\t%.1fkm\t%dmin\n", sName, eName, routes[i].distance, routes[i].duration);
    }
}

// 创建邻接表图
void createGraph(ALGraph *graph) {
    int i;
    ScenicSpot defaultSpots[] = {
        {1, "中山公园", "市中心中山路1号", "城市核心休闲公园，含湖景与古建筑"},
        {2, "海滨浴场", "滨海大道88号", "天然沙滩，支持游泳、露营等休闲活动"},
        {3, "市博物馆", "文化街10号", "本地历史文化展馆，常设免费开放"}
    };
    int routeInfo[][4] = {
        {0, 1, 5, 20},
        {1, 2, 4, 15},
        {0, 2, 4, 18}
    };
    
    graph->vexNum = 3;
    graph->arcNum = 3;
    for (i = 0; i < graph->vexNum; i++) {
        graph->vertices[i].data = defaultSpots[i];
        graph->vertices[i].firstArc = NULL;
    }
    
    for (i = 0; i < graph->arcNum; i++) {
        int startIdx = routeInfo[i][0];
        int endIdx = routeInfo[i][1];
        float dist = (float)routeInfo[i][2];
        int dur = routeInfo[i][3];
        
        ArcNode *arc1 = (ArcNode *)malloc(sizeof(ArcNode));
        arc1->adjvex = endIdx;
        arc1->distance = dist;
        arc1->duration = dur;
        arc1->nextArc = graph->vertices[startIdx].firstArc;
        graph->vertices[startIdx].firstArc = arc1;
        
        ArcNode *arc2 = (ArcNode *)malloc(sizeof(ArcNode));
        arc2->adjvex = startIdx;
        arc2->distance = dist;
        arc2->duration = dur;
        arc2->nextArc = graph->vertices[endIdx].firstArc;
        graph->vertices[endIdx].firstArc = arc2;
    }
    
    printf("邻接表图创建成功！共%d个景点，%d条路径\n", graph->vexNum, graph->arcNum);
}

// 打印邻接表图
void printGraph(ALGraph *graph) {
    int i;
    if (graph->vexNum == 0) {
        printf("图为空，请先创建图！\n");
        return;
    }
    
    printf("\n========== 邻接表图结构 ==========\n");
    for (i = 0; i < graph->vexNum; i++) {
        ArcNode *p = graph->vertices[i].firstArc;
        printf("[%d] %s：", graph->vertices[i].data.id, graph->vertices[i].data.name);
        
        while (p != NULL) {
            printf("→ %s(%.1fkm/%dmin) ", 
                   graph->vertices[p->adjvex].data.name, 
                   p->distance, 
                   p->duration);
            p = p->nextArc;
        }
        printf("\n");
    }
    printf("==================================\n");
}
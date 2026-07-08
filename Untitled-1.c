#include "global.h"
#include "scenic_spot.h"
#include "navigation.h"

// 菜单展示函数
void showMenu() {
    printf("\n=====================\n");
    printf("  旅游导航系统 V1.0  \n");
    printf("=====================\n");
    printf("1. 查看所有景点\n");
    printf("2. 查询景点详情\n");
    printf("3. 添加新景点\n");
    printf("4. 查看所有路径\n");
    printf("5. 路径导航查询\n");
    printf("6. 添加新路径\n");
    printf("7. 创建邻接表图\n");
    printf("8. 打印邻接表图\n");
    printf("0. 退出系统\n");
    printf("=====================\n");
    printf("请输入您的选择：");
}

int main() {
    ScenicSpot spots[MAX_SPOT_NUM];
    Route routes[MAX_ROUTE_NUM];
    ALGraph graph;
    int spotCount = 0;
    int routeCount = 0;
    int choice;
    
    // 初始化系统基础数据
    initSpotList(spots, &spotCount);
    initRouteList(routes, &routeCount);
    printf("旅游导航系统启动成功！\n");
    
    // 菜单主循环
    while (1) {
        showMenu();
        scanf("%d", &choice);
        getchar(); // 吸收输入后的换行符
        
        switch (choice) {
            case 1:
                printAllSpots(spots, spotCount);
                break;
            case 2: {
                int id;
                printf("请输入要查询的景点编号：");
                scanf("%d", &id);
                printSpotDetail(spots, spotCount, id);
                break;
            }
            case 3: {
                ScenicSpot newSpot;
                printf("请输入景点编号：");
                scanf("%d", &newSpot.id);
                getchar();
                printf("请输入景点名称：");
                fgets(newSpot.name, NAME_LEN, stdin);
                newSpot.name[strcspn(newSpot.name, "\n")] = '\0';
                printf("请输入景点地址：");
                fgets(newSpot.address, ADDR_LEN, stdin);
                newSpot.address[strcspn(newSpot.address, "\n")] = '\0';
                printf("请输入景点简介：");
                fgets(newSpot.intro, DESC_LEN, stdin);
                newSpot.intro[strcspn(newSpot.intro, "\n")] = '\0';
                addSpot(spots, &spotCount, newSpot);
                break;
            }
            case 4:
                printAllRoutes(routes, routeCount, spots, spotCount);
                break;
            case 5: {
                int start, end;
                printf("请输入起点景点编号：");
                scanf("%d", &start);
                printf("请输入终点景点编号：");
                scanf("%d", &end);
                queryRoute(routes, routeCount, spots, spotCount, start, end);
                break;
            }
            case 6: {
                Route newRoute;
                printf("请输入起点景点编号：");
                scanf("%d", &newRoute.startId);
                printf("请输入终点景点编号：");
                scanf("%d", &newRoute.endId);
                printf("请输入路径距离(公里)：");
                scanf("%f", &newRoute.distance);
                printf("请输入预计耗时(分钟)：");
                scanf("%d", &newRoute.duration);
                getchar();
                printf("请输入路径描述：");
                fgets(newRoute.description, DESC_LEN, stdin);
                newRoute.description[strcspn(newRoute.description, "\n")] = '\0';
                addRoute(routes, &routeCount, newRoute);
                break;
            }
            case 7:
                createGraph(&graph);
                break;
            case 8:
                printGraph(&graph);
                break;
            case 0:
                printf("感谢使用，系统已退出！\n");
                return 0;
            default:
                printf("输入无效，请重新选择！\n");
        }
    }
    return 0;
}
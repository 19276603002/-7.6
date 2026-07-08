#include "scenic_spot.h"

void initSpotList(ScenicSpot spots[], int *count) {
    int i;
    *count = 0;
    // 内置3个默认景点
    ScenicSpot defaultSpots[] = {
        {1, "中山公园", "市中心中山路1号", "城市核心休闲公园，含湖景与古建筑"},
        {2, "海滨浴场", "滨海大道88号", "天然沙滩，支持游泳、露营等休闲活动"},
        {3, "市博物馆", "文化街10号", "本地历史文化展馆，常设免费开放"}
    };
    for(i = 0; i < 3; i++) {
        spots[i] = defaultSpots[i];
        (*count)++;
    }
}

int addSpot(ScenicSpot spots[], int *count, ScenicSpot newSpot) {
    if (*count >= MAX_SPOT_NUM) {
        printf("景点数量已达上限，添加失败！\n");
        return 0;
    }
    if (findSpotById(spots, *count, newSpot.id) != -1) {
        printf("景点编号已存在，添加失败！\n");
        return 0;
    }
    spots[*count] = newSpot;
    (*count)++;
    printf("景点添加成功！\n");
    return 1;
}

int findSpotById(ScenicSpot spots[], int count, int id) {
    int i;
    for (i = 0; i < count; i++) {
        if (spots[i].id == id) return i;
    }
    return -1;
}

void printAllSpots(ScenicSpot spots[], int count) {
    int i;
    if (count == 0) {
        printf("暂无景点信息\n");
        return;
    }
    printf("===== 景点列表 =====\n");
    printf("编号\t景点名称\t\t地址\n");
    for (i = 0; i < count; i++) {
        printf("%d\t%s\t\t%s\n", spots[i].id, spots[i].name, spots[i].address);
    }
}

void printSpotDetail(ScenicSpot spots[], int count, int id) {
    int index = findSpotById(spots, count, id);
    if (index == -1) {
        printf("未找到编号为%d的景点\n", id);
        return;
    }
    ScenicSpot s = spots[index];
    printf("===== 景点详情 =====\n");
    printf("编号：%d\n名称：%s\n地址：%s\n简介：%s\n", s.id, s.name, s.address, s.intro);
}
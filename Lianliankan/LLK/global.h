#pragma once

//定义顶点结构体
typedef struct tagVertex
{
	int row;	//行
	int col;	//列
	int info;	//信息类
}Vertex;

#define		BLANK				-1		//游戏图片消除
#define		MAX_ROW				10		//游戏地图行数
#define		MAX_COL				16		//游戏地图列数
#define		MAX_VERTEX_NUM		160		//顶点数
#define		MAX_PIC_NUM			10		//图片花色
#define		REPEAT_NUM			16		//每种花色图片个数
#define		MAP_TOP				50		//游戏地图左上角Y坐标
#define		MAP_LEFT			50		//游戏地图左上角X坐标
#define		PIC_WIDTH			40		//游戏图片宽度X
#define		PIC_HEIGHT			40		//游戏图片高度Y
#define     AVPATHNUM			100		//路径数目
#define     PLAY_TIME_ID		1
#define		GAME_LOSE			-1		//失败
#define		GAME_SUCCESS		0		//获胜
#define		GAME_PLAY			1		//游戏正在进行
#define		MAX_TIME			300		//游戏倒计时
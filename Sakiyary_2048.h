#ifndef SAKIYARY_2048_C_SAKIYARY_2048_H
#define SAKIYARY_2048_C_SAKIYARY_2048_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#undef main

void StartAndLoad();//启动并加载图片和字体
int PlayUI();//游戏界面
void Move(int Dir1, int Dir2, int IfAuto);//移动面板_核心算法
void RandomCreate();//随机生成2或4
void Revoke();//撤回一步
void Restart();//重开游戏
void IfOver();//判断是否游戏结束
void MsgBox(int kind);//游戏结束/暂停/胜利的选项框
void PrintAllElements();//清空渲染器并重新打印全部
void PrintTime();//打印计时器的时间
void PrintScores();//打印分数与最高分
void PrintNotes();//打印数字方块
void FreeAndQuit();//清除所有加载项并退出 Free是个好习惯

static int IfBegin = 0, IfWin = 0, IfMsgBox = 0;//判断是否开始/胜利/有对话框存在

static int Score = 0, OldScore = 0, BestScore = 0, OldBestScore = 0;//游戏分数与最高分
static char ScoreChar[10], BestScoreChar[10];//打印分数需要的字符串

static int DownButtonX, DownButtonY, UpButtonX, UpButtonY;//鼠标按下与松开时的坐标

static time_t PlayStartTime, PlayEndTime, PauseTime, MainTime;//记录游戏时间与暂停时间
static char TimeChar[10];//打印时间需要的字符串

static int Map[4][4] = {
        {0, 7, 8,  15},
        {0, 6, 9,  14},
        {3, 5, 10, 13},
        {3, 4, 11, 12}
};//测试用起始数据

// static int Map[4][4] = {
//         {0, 0, 0, 0},
//         {0, 0, 0, 0},
//         {0, 0, 0, 0},
//         {0, 0, 0, 0}
// };//纯0初始数据

static int OldMap[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
};//供撤回用的旧面板

static SDL_Window *Window = NULL;//窗口
static SDL_Renderer *Renderer = NULL;//渲染器
static SDL_Surface *MainBackGroundSurface = NULL;//开始界面背景
static SDL_Surface *PlayBackGroundSurface = NULL;//游戏界面背景
static SDL_Surface *MsgBoxSurface[3] = {NULL};//三种对话框
static SDL_Surface *NoteSurface[17] = {NULL};//十七种数字图标
static SDL_Rect NoteRect;//数字图标的坐标与大小信息
static TTF_Font *Font = NULL;//字体
static SDL_Color FontColor = {255, 255, 255, 255};//字体颜色为白色
static SDL_Event MainEvent;//开始事件
static SDL_Event PlayEvent;//游戏事件

#endif //SAKIYARY_2048_C_SAKIYARY_2048_H
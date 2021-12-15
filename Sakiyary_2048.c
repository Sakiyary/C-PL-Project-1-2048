#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

void StartAndLoad();//启动并加载图片和字体

void PlayUI();//游戏界面

void Move(int Dir1, int Dir2);//移动面板_核心算法

void RandomCreate();//随机生成2或4

void Revoke();//撤回一步

void Restart();//重开游戏

void IfOver();//判断是否游戏结束

void MsgBox(int kind);//游戏结束/暂停/胜利的选项框

void PrintAll();//清空渲染器并重新打印全部

void PrintTime();//打印计时器的时间

void PrintScores();//打印分数与最高分

void PrintNotes();//打印数字方块

void FreeAndQuit();//清除所有加载项并退出,Free是个好习惯

int IfBegin = 0, IfWin = 0, IfMsgBox = 0;

int Score = 0, OldScore = 0, BestScore = 0, OldBestScore = 0;
char ScoreChar[10], BestScoreChar[10];//打印分数需要的字符串

int DownButtonX, DownButtonY, UpButtonX, UpButtonY;

time_t PlayStartTime, PlayEndTime, PauseTime, MainTime;
char TimeChar[10];//打印时间需要的字符串

int Map[4][4] = {
        {1,  5, 6, 13},
        {16, 4, 7, 12},
        {16, 3, 8, 11},
        {0,  2, 9, 10}
};//测试用起始数据

// int Map[4][4] = {
//         {0, 0, 0, 0},
//         {0, 0, 0, 0},
//         {0, 0, 0, 0},
//         {0, 0, 0, 0}
// };//纯0初始数据

int OldMap[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
};

SDL_Window *Window = NULL;
SDL_Renderer *Renderer = NULL;

SDL_Surface *MainBackGroundSurface = NULL;
SDL_Texture *MainBackGroundTexture = NULL;
SDL_Surface *PlayBackGroundSurface = NULL;
SDL_Texture *PlayBackGroundTexture = NULL;
SDL_Surface *MsgBoxSurface[3] = {NULL};
SDL_Texture *MsgBoxTexture[3] = {NULL};
SDL_Surface *NoteSurface[14] = {NULL};
SDL_Texture *NoteTexture = NULL;
SDL_Rect NoteRect;
SDL_Surface *WordsSurface = NULL;
SDL_Texture *WordsTexture = NULL;
TTF_Font *ScoreFont = NULL;
TTF_Font *TimeFont = NULL;
SDL_Color FontColor = {255, 255, 255, 255};

SDL_Event MainEvent;
SDL_Event PlayEvent;

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    Window = SDL_CreateWindow("Sakiyary's Infinite 2048 ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 1000, SDL_WINDOW_SHOWN);
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    StartAndLoad();
    srand((unsigned) time(NULL));
    printf("MainEvent\n");
    while (SDL_WaitEvent(&MainEvent)) {
        SDL_RenderClear(Renderer);
        SDL_RenderCopy(Renderer, MainBackGroundTexture, NULL, NULL);
        SDL_RenderPresent(Renderer);
        switch (MainEvent.type) {
            case SDL_QUIT:
                FreeAndQuit();
            case SDL_KEYDOWN:
                switch (MainEvent.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_BACKSPACE:
                        FreeAndQuit();
                    case SDLK_RETURN:
                        if (!IfBegin)
                            RandomCreate();
                        PlayUI();
                        IfMsgBox = 0;
                        MainTime = PauseTime ? PauseTime : time(NULL);
                        printf("MainEvent\n");
                        break;
                    default:
                        break;
                }
            case SDL_MOUSEBUTTONUP:
                printf("(%d,%d) in Main UI\n", MainEvent.button.x, MainEvent.button.y);
                if (MainEvent.button.x > 205 && MainEvent.button.x < 604 && MainEvent.button.y > 650 && MainEvent.button.y < 777) {
                    if (!IfBegin)
                        RandomCreate();
                    PlayUI();
                }
                IfMsgBox = 0;
                MainTime = PauseTime ? PauseTime : time(NULL);
                printf("MainEvent\n");
                break;
            default:
                break;
        }
        SDL_Delay(10);
    }
    FreeAndQuit();
}

void PlayUI() {
    if (!IfBegin)PlayStartTime = time(NULL);
    else PlayStartTime += (time(NULL) - MainTime);
    IfBegin = 1;
    printf("PlayEvent\n");
    while (1) {
        if (!IfMsgBox) {
            PrintAll();
            PauseTime = 0;
        }
        while (SDL_WaitEventTimeout(&PlayEvent, 100) || IfMsgBox) {
            switch (PlayEvent.type) {
                case SDL_QUIT:
                    FreeAndQuit();
                case SDL_KEYDOWN:
                    switch (PlayEvent.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_BACKSPACE:
                            if (IfMsgBox == 2)Restart();
                            return;
                        case SDLK_z:
                            if (IfMsgBox != 1)
                                Revoke();
                            break;
                        case SDLK_r:
                            Restart();
                            break;
                        case SDLK_RETURN:
                        case SDLK_c:
                            IfMsgBox = 0;
                            PlayStartTime += time(NULL) - PauseTime;
                            break;
                        case SDLK_p:
                            MsgBox(2);
                        case SDLK_w:
                        case SDLK_UP:
                            if (!IfMsgBox)
                                Move(1, 1);
                            break;
                        case SDLK_s:
                        case SDLK_DOWN:
                            if (!IfMsgBox)
                                Move(1, 0);
                            break;
                        case SDLK_a:
                        case SDLK_LEFT:
                            if (!IfMsgBox)
                                Move(0, 1);
                            break;
                        case SDLK_d:
                        case SDLK_RIGHT:
                            if (!IfMsgBox)
                                Move(0, 0);
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    DownButtonX = PlayEvent.button.x;
                    DownButtonY = PlayEvent.button.y;
                    break;
                case SDL_MOUSEBUTTONUP:
                    UpButtonX = PlayEvent.button.x;
                    UpButtonY = PlayEvent.button.y;
                    int dx = DownButtonX - UpButtonX > 0 ? DownButtonX - UpButtonX : UpButtonX - DownButtonX;
                    int dy = DownButtonY - UpButtonY > 0 ? DownButtonY - UpButtonY : UpButtonY - DownButtonY;
                    if (!IfMsgBox) {
                        if (dx < 20 && dy < 20 && UpButtonY > 210 && UpButtonY < 258) {
                            if (UpButtonX > 465 && UpButtonX < 533)
                                return;
                            else if (UpButtonX > 546 && UpButtonX < 608)
                                Revoke();
                            else if (UpButtonX > 625 && UpButtonX < 690)
                                Restart();
                            else if (UpButtonX > 711 && UpButtonX < 772)
                                MsgBox(2);
                        } else if (dx < 100 && DownButtonY - UpButtonY > 100)
                            Move(1, 1);
                        else if (dx < 100 && UpButtonY - DownButtonY > 100)
                            Move(1, 0);
                        else if (dy < 100 && DownButtonX - UpButtonX > 100)
                            Move(0, 1);
                        else if (dy < 100 && UpButtonX - DownButtonX > 100)
                            Move(0, 0);
                    }
                    if (IfMsgBox) {
                        if (dx < 20 && dy < 20 && UpButtonY > 570 && UpButtonY < 638) {
                            if (UpButtonX > 261 && UpButtonX < 323) {
                                if (IfMsgBox == 2)Restart();
                                return;
                            } else if (UpButtonX > 467 && UpButtonX < 548)
                                Restart();
                            else if (UpButtonX > 370 && UpButtonX < 427) {
                                if (IfMsgBox == 1) {
                                    IfMsgBox = 0;
                                    PlayStartTime += time(NULL) - PauseTime;
                                } else Revoke();
                            }
                        }
                    }
                    if (!IfMsgBox)printf("(%d,%d) in Play UI\n", PlayEvent.button.x, PlayEvent.button.y);
                    else printf("(%d,%d) in MsgBox UI\n", PlayEvent.button.x, PlayEvent.button.y);
                    break;
                default:
                    break;
            }
            SDL_Delay(10);
            break;
        }
    }
}

void Move(int Dir1, int Dir2) {
    int IfMove = 0;
    int RecMap[4][4];
    int RecScore = Score, RecBestScore = BestScore;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            RecMap[i][j] = Map[i][j];
    for (int i = 0; i < 4; ++i) {
        if (!Map[Dir1 ? 0 : i][Dir1 ? i : 0] && !Map[Dir1 ? 1 : i][Dir1 ? i : 1] && !Map[Dir1 ? 2 : i][Dir1 ? i : 2] && !Map[Dir1 ? 3 : i][Dir1 ? i : 3])continue;
        for (int j = Dir2 ? 0 : 3; (Dir2 && j < 3) || (!Dir2 && j > 0); j += Dir2 ? 1 : -1)
            for (int k = 0; (Dir2 && k < 3 - j) || (!Dir2 && k < j); ++k)
                if (!Map[Dir1 ? j : i][Dir1 ? i : j]) {
                    for (int l = j; (Dir2 && l < 3) || (!Dir2 && l > 0); l += Dir2 ? 1 : -1)
                        Map[Dir1 ? l : i][Dir1 ? i : l] = Map[Dir1 ? (Dir2 ? l + 1 : l - 1) : i][Dir1 ? i : (Dir2 ? l + 1 : l - 1)];
                    Map[Dir1 ? (Dir2 ? 3 : 0) : i][Dir1 ? i : (Dir2 ? 3 : 0)] = 0;
                }
        for (int j = Dir2 ? 0 : 3; (Dir2 && j < 3) || (!Dir2 && j > 0); j += Dir2 ? 1 : -1) {
            if (Map[Dir1 ? j : i][Dir1 ? i : j] == Map[Dir1 ? (Dir2 ? j + 1 : j - 1) : i][Dir1 ? i : (Dir2 ? j + 1 : j - 1)] && Map[Dir1 ? j : i][Dir1 ? i : j] != 0) {
                Map[Dir1 ? j : i][Dir1 ? i : j]++;
                Score += 1 << Map[Dir1 ? j : i][Dir1 ? i : j];
                BestScore = BestScore < Score ? Score : BestScore;
                if (Map[Dir1 ? j : i][Dir1 ? i : j] == 11 && !IfWin)IfWin = 1;
                for (int k = Dir2 ? j + 1 : j - 1; (Dir2 && k < 3) || (!Dir2 && k > 0); k += Dir2 ? 1 : -1)
                    Map[Dir1 ? k : i][Dir1 ? i : k] = Map[Dir1 ? (Dir2 ? k + 1 : k - 1) : i][Dir1 ? i : (Dir2 ? k + 1 : k - 1)];
                Map[Dir1 ? (Dir2 ? 3 : 0) : i][Dir1 ? i : (Dir2 ? 3 : 0)] = 0;
                IfMove = 1;
            }
        }
        if (!IfMove)//判断整个面板到底动没动
            for (int j = 0; j < 4; ++j)
                if (RecMap[Dir1 ? j : i][Dir1 ? i : j] != Map[Dir1 ? j : i][Dir1 ? i : j])
                    IfMove = 1;
    }
    PrintAll();
    if (IfMove) {//如果面板发生变动，保存该面板与分数
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                OldMap[i][j] = RecMap[i][j];
        OldScore = RecScore;
        OldBestScore = RecBestScore;
        if (IfWin == 1) {
            MsgBox(1);
            IfWin = 2;//0表示未胜利，1表示需要在一步操作结束后跳出胜利界面，2表示已经宣告过胜利故不用再次宣告。
        }
        RandomCreate();
    }
    IfOver();//判断死局
}

void RandomCreate() {
    int cnt = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (!Map[i][j])cnt++;
    if (!cnt)return;
    SDL_Delay(100);
    int pivot = rand() % cnt + 1;
    for (int i = 0; i < 4; ++i)
        if (pivot)
            for (int j = 0; j < 4; ++j)
                if (!Map[i][j]) {
                    pivot--;
                    if (!pivot) {
                        Map[i][j] = rand() > (RAND_MAX / 5) ? 1 : 2;//80%概率出现"2"; 20%概率出现"4".
                        break;
                    }
                }
    if (!IfMsgBox)PrintAll();
}

void IfOver() {
    int cnt = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (!Map[i][j])cnt++;
    if (cnt)return;
    int flag = 0;
    for (int i = 0; i < 4; ++i)
        if (!flag)
            for (int j = 0; j < 3; ++j)
                if (Map[i][j] == Map[i][j + 1] || Map[j][i] == Map[j + 1][i]) {
                    flag = 1;
                    break;
                }
    if (!flag)MsgBox(0);
}

void Revoke() {
    IfMsgBox = 0;
    int IfRevoke = 1, cnt = 0;
    for (int i = 0; i < 4; ++i) {
        if (!IfRevoke)
            break;
        for (int j = 0; j < 4; ++j)
            if (Map[i][j] != OldMap[i][j]) {
                IfRevoke = 0;
                break;
            }
    }
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (!OldMap[i][j])
                cnt++;
    if (cnt == 16)
        printf("This is your first step !\n");
    else if (IfRevoke)
        printf("You can revoke for only one time !\n");
    else {
        printf("Revoke\n");
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                Map[i][j] = OldMap[i][j];
        Score = OldScore;
        BestScore = OldBestScore;
    }
}


void Restart() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            Map[i][j] = 0;
            OldMap[i][j] = 0;
        }
    PauseTime = 0;
    Score = 0;
    IfBegin = 1;
    IfMsgBox = 0;
    IfWin = 0;
    printf("Restart\n");
    RandomCreate();
    PlayStartTime = time(NULL);
}

void MsgBox(int kind) {//kind: 0代表游戏结束，1代表游戏胜利，2代表游戏暂停.
    PauseTime = time(NULL);
    IfMsgBox = 1;
    if (!kind)IfMsgBox = 2;
    SDL_RenderCopy(Renderer, MsgBoxTexture[kind], NULL, NULL);
    SDL_RenderPresent(Renderer);
}

void PrintAll() {
    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer, PlayBackGroundTexture, NULL, NULL);
    PrintTime();
    PrintScores();
    PrintNotes();
    SDL_RenderPresent(Renderer);
}

void PrintTime() {
    PlayEndTime = time(NULL);
    int DurSecond = (int) difftime(PlayEndTime, PlayStartTime);
    sprintf(TimeChar, "%.2d:%.2d:%.2d", DurSecond / 3600, DurSecond / 60 % 60, DurSecond % 60);
    WordsSurface = TTF_RenderUTF8_Blended(TimeFont, TimeChar, FontColor);
    WordsTexture = SDL_CreateTextureFromSurface(Renderer, WordsSurface);
    SDL_Rect TimeRect = {188, 212, WordsSurface->w, WordsSurface->h};
    SDL_RenderCopy(Renderer, WordsTexture, NULL, &TimeRect);
}

void PrintScores() {
    sprintf(ScoreChar, "%d", Score);
    WordsSurface = TTF_RenderUTF8_Blended(ScoreFont, ScoreChar, FontColor);
    WordsTexture = SDL_CreateTextureFromSurface(Renderer, WordsSurface);
    SDL_Rect ScoreRect = {580, 38, WordsSurface->w, WordsSurface->h};
    SDL_RenderCopy(Renderer, WordsTexture, NULL, &ScoreRect);
    sprintf(BestScoreChar, "%d", BestScore);
    WordsSurface = TTF_RenderUTF8_Blended(ScoreFont, BestScoreChar, FontColor);
    WordsTexture = SDL_CreateTextureFromSurface(Renderer, WordsSurface);
    SDL_Rect BestRect = {580, 94, WordsSurface->w, WordsSurface->h};
    SDL_RenderCopy(Renderer, WordsTexture, NULL, &BestRect);
}

void PrintNotes() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            NoteRect.x = 88 + 162 * j;
            NoteRect.y = 316 + 157 * i;
            if (Map[i][j]) {
                NoteTexture = SDL_CreateTextureFromSurface(Renderer, NoteSurface[Map[i][j] - 1 < 13 ? Map[i][j] - 1 : 13]);
                SDL_RenderCopy(Renderer, NoteTexture, NULL, &NoteRect);
            }
        }
}

void StartAndLoad() {
    MainBackGroundSurface = IMG_Load("IMAGE/MainBackGround.png");
    PlayBackGroundSurface = IMG_Load("IMAGE/PlayBackGround.png");

    for (int i = 0; i < 3; ++i) {
        char BoxName[20];
        sprintf(BoxName, "IMAGE/MsgBox%d.png", i);
        MsgBoxSurface[i] = IMG_Load(BoxName);
        MsgBoxTexture[i] = SDL_CreateTextureFromSurface(Renderer, MsgBoxSurface[i]);
    }

    MainBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, MainBackGroundSurface);
    PlayBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, PlayBackGroundSurface);

    ScoreFont = TTF_OpenFont("IMAGE/COPRGTB.TTF", 50);
    TimeFont = TTF_OpenFont("IMAGE/COPRGTL.TTF", 50);
    for (int i = 0; i < 14; ++i) {
        char PicName[20];
        sprintf(PicName, "IMAGE/Note%d.png", i + 1);
        NoteSurface[i] = IMG_Load(PicName);
    }
    NoteRect.w = NoteSurface[0]->w;
    NoteRect.h = NoteSurface[0]->h;
}

void FreeAndQuit() {
    SDL_FreeSurface(MainBackGroundSurface);
    SDL_FreeSurface(PlayBackGroundSurface);
    SDL_FreeSurface(WordsSurface);
    for (int i = 0; i < 14; ++i)
        SDL_FreeSurface(NoteSurface[i]);
    for (int i = 0; i < 3; ++i) {
        SDL_FreeSurface(MsgBoxSurface[i]);
        SDL_DestroyTexture(MsgBoxTexture[i]);
    }
    SDL_DestroyTexture(MainBackGroundTexture);
    SDL_DestroyTexture(PlayBackGroundTexture);
    SDL_DestroyTexture(NoteTexture);
    SDL_DestroyTexture(WordsTexture);
    TTF_CloseFont(ScoreFont);
    TTF_CloseFont(TimeFont);

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}
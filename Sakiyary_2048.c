#include "Sakiyary_2048.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);//SDL初始化
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);//忽视鼠标移动带来的事件处理与内存占用!!!
    TTF_Init();//字体加载初始化
    Window = SDL_CreateWindow("Sakiyary$ Infinite 2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 1000, SDL_WINDOW_SHOWN);//创建窗口
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    StartAndLoad();//加载图片文件
    srand((unsigned) time(NULL));//创建随机数种子
    printf("MainEvent\n");//供测试用 可注释掉
    SDL_COMPILE_TIME_ASSERT(MainEvent, sizeof(SDL_Event) == sizeof(((SDL_Event *) NULL)->padding));
    while (SDL_WaitEvent(&MainEvent)) {
        SDL_Texture *MainBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, MainBackGroundSurface);
        SDL_RenderCopy(Renderer, MainBackGroundTexture, NULL, NULL);
        SDL_RenderPresent(Renderer);
        SDL_DestroyTexture(MainBackGroundTexture);
        switch (MainEvent.type) {
            case SDL_QUIT:
                FreeAndQuit();
                return 0;
            case SDL_KEYDOWN:
                switch (MainEvent.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_BACKSPACE:
                        FreeAndQuit();
                        return 0;
                    case SDLK_SPACE:
                    case SDLK_RETURN:
                        if (!IfBegin)
                            for (int i = 0; i < 2; ++i)
                                RandomCreate();
                        SDL_COMPILE_TIME_ASSERT(MainEvent, sizeof(SDL_Event) == sizeof(((SDL_Event *) NULL)->padding));
                        if (PlayUI())
                            return 0;
                        SDL_COMPILE_TIME_ASSERT(PlayEvent, sizeof(SDL_Event) == sizeof(((SDL_Event *) NULL)->padding));
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
                        for (int i = 0; i < 2; ++i)
                            RandomCreate();
                    SDL_COMPILE_TIME_ASSERT(MainEvent, sizeof(SDL_Event) == sizeof(((SDL_Event *) NULL)->padding));
                    if (PlayUI())
                        return 0;
                    SDL_COMPILE_TIME_ASSERT(PlayEvent, sizeof(SDL_Event) == sizeof(((SDL_Event *) NULL)->padding));
                    IfMsgBox = 0;
                    MainTime = PauseTime ? PauseTime : time(NULL);
                    printf("MainEvent\n");
                }
                break;
            default:
                break;
        }
        SDL_COMPILE_TIME_ASSERT(MainEvent, sizeof(SDL_Event) == sizeof(((SDL_Event *) NULL)->padding));
    }
    FreeAndQuit();
    return 0;
}

int PlayUI() {
    if (!IfBegin)PlayStartTime = time(NULL);
    else PlayStartTime += (time(NULL) - MainTime);
    IfBegin = 1;
    printf("PlayEvent\n");
    SDL_COMPILE_TIME_ASSERT(PlayEvent, sizeof(SDL_Event) == sizeof(((SDL_Event *) NULL)->padding));
    while (1) {
        if (!IfMsgBox) {
            PrintAllElements();
            PauseTime = 0;
        }
        while (SDL_PollEvent(&PlayEvent) || IfMsgBox) {
            switch (PlayEvent.type) {
                case SDL_QUIT:
                    FreeAndQuit();
                    return 1;
                case SDL_KEYDOWN:
                    switch (PlayEvent.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_BACKSPACE:
                            if (IfMsgBox == 2)
                                Restart();
                            return 0;
                        case SDLK_z:
                            if (IfMsgBox != 1)
                                Revoke();
                            break;
                        case SDLK_r:
                            Restart();
                            break;
                        case SDLK_RETURN:
                            if (!IfMsgBox)
                                Move(rand() > RAND_MAX / 2, rand() > RAND_MAX / 2, 1);
                            else if (IfMsgBox == 2)
                                Restart();
                            else if (IfMsgBox == 1) {
                                IfMsgBox = 0;
                                PlayStartTime += time(NULL) - PauseTime;
                            }
                            break;
                        case SDLK_w:
                        case SDLK_UP:
                            if (!IfMsgBox)
                                Move(1, 1, 0);
                            break;
                        case SDLK_s:
                        case SDLK_DOWN:
                            if (!IfMsgBox)
                                Move(1, 0, 0);
                            break;
                        case SDLK_a:
                        case SDLK_LEFT:
                            if (!IfMsgBox)
                                Move(0, 1, 0);
                            break;
                        case SDLK_d:
                        case SDLK_RIGHT:
                            if (!IfMsgBox)
                                Move(0, 0, 0);
                            break;
                        case SDLK_SPACE:
                            if (!IfMsgBox)
                                MsgBox(2);
                            else if (IfMsgBox == 1) {
                                IfMsgBox = 0;
                                PlayStartTime += time(NULL) - PauseTime;
                            }
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
                                return 0;
                            else if (UpButtonX > 546 && UpButtonX < 608)
                                Revoke();
                            else if (UpButtonX > 625 && UpButtonX < 690)
                                Restart();
                            else if (UpButtonX > 711 && UpButtonX < 772)
                                MsgBox(2);
                        } else if (dx < 100 && DownButtonY - UpButtonY > 100)
                            Move(1, 1, 0);
                        else if (dx < 100 && UpButtonY - DownButtonY > 100)
                            Move(1, 0, 0);
                        else if (dy < 100 && DownButtonX - UpButtonX > 100)
                            Move(0, 1, 0);
                        else if (dy < 100 && UpButtonX - DownButtonX > 100)
                            Move(0, 0, 0);
                    } else {
                        if (dx < 20 && dy < 20 && UpButtonY > 570 && UpButtonY < 638) {
                            if (UpButtonX > 261 && UpButtonX < 323) {
                                if (IfMsgBox == 2)
                                    Restart();
                                return 0;
                            } else if (UpButtonX > 467 && UpButtonX < 548)
                                Restart();
                            else if (UpButtonX > 370 && UpButtonX < 427) {
                                if (IfMsgBox == 1) {
                                    IfMsgBox = 0;
                                    PlayStartTime += time(NULL) - PauseTime;
                                } else
                                    Revoke();
                            }
                        }
                    }
                    if (!IfMsgBox)
                        printf("(%d,%d) in Play UI\n", PlayEvent.button.x, PlayEvent.button.y);
                    else
                        printf("(%d,%d) in MsgBox UI\n", PlayEvent.button.x, PlayEvent.button.y);
                    break;
                default:
                    break;
            }
            SDL_COMPILE_TIME_ASSERT(PlayEvent, sizeof(SDL_Event) == sizeof(((SDL_Event *) NULL)->padding));
            break;
        }
    }
}

void Move(int Dir1, int Dir2, int IfAuto) {//统一命名 列数为i 行数为j
    int IfMove = 0;
    int RecMap[4][4], TmpMap[4][4];
    int RecScore = Score, RecBestScore = BestScore;

    for (int i = 0; i < 4; ++i)//将面板储存至暂时记录面板
        for (int j = 0; j < 4; ++j)
            RecMap[j][i] = Map[j][i];

    if (!Dir1 || !Dir2)//旋转面板使得移动方向总为向上移动
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) {
                if (Dir1 && !Dir2)
                    Map[j][i] = RecMap[3 - j][i];
                if (!Dir1 && Dir2)
                    Map[j][i] = RecMap[3 - i][j];
                if (!Dir1 && !Dir2)
                    Map[j][i] = RecMap[i][3 - j];
            }

    for (int i = 0; i < 4; ++i) {//向上移动时每一列都可以分别处理
        if (!Map[0][i] && !Map[1][i] && !Map[2][i] && !Map[3][i])
            continue;//若都为零则不处理

        for (int j = 0; j < 3; ++j)//消除所有可以缩去的0
            for (int k = 0; k < 3 - j; ++k)
                if (!Map[j][i]) {
                    for (int l = j; l < 3; ++l)
                        Map[l][i] = Map[l + 1][i];
                    Map[3][i] = 0;
                }

        for (int j = 0; j < 3; ++j) {//相同数字按照规则合并且计算分数判断胜局
            if (Map[j][i] == Map[j + 1][i] && Map[j][i]) {
                Map[j][i]++;
                Score += 1 << Map[j][i];
                BestScore = BestScore < Score ? Score : BestScore;
                if (Map[j][i] == 11 && !IfWin)
                    IfWin = 1;
                for (int k = j + 1; k < 3; ++k)
                    Map[k][i] = Map[k + 1][i];
                Map[3][i] = 0;
            }
        }
    }

    if (!Dir1 || !Dir2) {//将面板再转回来
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                TmpMap[j][i] = Map[j][i];
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) {
                if (Dir1 && !Dir2)
                    Map[j][i] = TmpMap[3 - j][i];
                if (!Dir1 && Dir2)
                    Map[j][i] = TmpMap[i][3 - j];
                if (!Dir1 && !Dir2)
                    Map[j][i] = TmpMap[3 - i][j];
            }
    }
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (RecMap[j][i] != Map[j][i])
                IfMove = 1;//通过比较暂时储存面板与移动后面板 判断整个面板到底动没动

    if (IfAuto && !IfMove) {//如果是自动操作，面板却没有动，那再来一次
        Move(rand() > RAND_MAX / 2, rand() > RAND_MAX / 2, 1);
        return;
    }

    if (IfMove) {//如果面板发生变动 保存该面板与分数
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                OldMap[j][i] = RecMap[j][i];
        OldScore = RecScore;
        OldBestScore = RecBestScore;
        if (IfWin == 1) {
            MsgBox(1);
            IfWin = 2;//0表示未胜利 1表示需要在一步操作结束后跳出胜利界面 2表示已经宣告过胜利故不用再次宣告。
        }
        RandomCreate();
    }
    IfOver();//判断死局
}

void RandomCreate() {
//    if (!IfMsgBox && IfBegin)//此行代码会使游戏非常卡顿
//        PrintAllElements();//如果游戏已经开始且非对话框界面 就重新打印界面
    int cnt = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (!Map[i][j])
                cnt++;//统计空位的个数
    if (!cnt)
        return;//如果没有空位就返回
    int pivot = rand() % cnt + 1;
    for (int i = 0; i < 4; ++i)
        if (pivot)
            for (int j = 0; j < 4; ++j)
                if (!Map[i][j]) {
                    pivot--;
                    if (!pivot) {
                        Map[i][j] = rand() > (RAND_MAX / 10) ? 1 : 2;//90%概率出现"2" 10%概率出现"4" 此为最初版2048的源码数据参数
                        break;
                    }
                }
}

void IfOver() {
    int cnt = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (!Map[i][j])
                cnt++;//统计空位的个数
    if (cnt)
        return;//有空位就返回
    int flag = 0;
    for (int i = 0; i < 4; ++i)
        if (!flag)
            for (int j = 0; j < 3; ++j)
                if (Map[i][j] == Map[i][j + 1] || Map[j][i] == Map[j + 1][i]) {
                    flag = 1;
                    break;
                }
    if (!flag) {
        PrintAllElements();
        MsgBox(0);//弹出游戏失败对话框
    }
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
        printf("This is your first step !\n");//这三句提示并没有做进图形界面中 可以注释掉
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


void Restart() {//全部/remake!!!除了最高分
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
    for (int i = 0; i < 2; ++i)
        RandomCreate();
    PlayStartTime = time(NULL);
}

void MsgBox(int kind) {//kind: 0代表游戏结束，1代表游戏胜利，2代表游戏暂停.
    PauseTime = time(NULL);
    IfMsgBox = 1;
    if (!kind)
        IfMsgBox = 2;
    SDL_Texture *MsgBoxTexture = SDL_CreateTextureFromSurface(Renderer, MsgBoxSurface[kind]);
    SDL_RenderCopy(Renderer, MsgBoxTexture, NULL, NULL);
    SDL_RenderPresent(Renderer);
    SDL_DestroyTexture(MsgBoxTexture);
}

void PrintAllElements() {
    SDL_Texture *PlayBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, PlayBackGroundSurface);
    SDL_RenderCopy(Renderer, PlayBackGroundTexture, NULL, NULL);
    SDL_DestroyTexture(PlayBackGroundTexture);
    PrintTime();
    PrintScores();
    PrintNotes();
    SDL_RenderPresent(Renderer);
}

void PrintTime() {
    PlayEndTime = time(NULL);
    int DurSecond = (int) difftime(PlayEndTime, PlayStartTime);
    sprintf(TimeChar, "%.2d:%.2d:%.2d", DurSecond / 3600, DurSecond / 60 % 60, DurSecond % 60);
    SDL_Surface *WordsSurface = TTF_RenderUTF8_Blended(Font, TimeChar, FontColor);
    SDL_Texture *WordsTexture = SDL_CreateTextureFromSurface(Renderer, WordsSurface);
    SDL_Rect TimeRect = {200, 212, WordsSurface->w, WordsSurface->h};
    SDL_RenderCopy(Renderer, WordsTexture, NULL, &TimeRect);
    SDL_FreeSurface(WordsSurface);
    SDL_DestroyTexture(WordsTexture);
}

void PrintScores() {
    sprintf(ScoreChar, "%d", Score);
    SDL_Surface *ScoreSurface = TTF_RenderUTF8_Blended(Font, ScoreChar, FontColor);
    SDL_Texture *ScoreTexture = SDL_CreateTextureFromSurface(Renderer, ScoreSurface);
    SDL_Rect ScoreRect = {690 - ScoreSurface->w / 2, 38, ScoreSurface->w, ScoreSurface->h};
    SDL_RenderCopy(Renderer, ScoreTexture, NULL, &ScoreRect);
    SDL_FreeSurface(ScoreSurface);
    SDL_DestroyTexture(ScoreTexture);
    sprintf(BestScoreChar, "%d", BestScore);
    SDL_Surface *BestScoreSurface = TTF_RenderUTF8_Blended(Font, BestScoreChar, FontColor);
    SDL_Texture *BestScoreTexture = SDL_CreateTextureFromSurface(Renderer, BestScoreSurface);
    SDL_Rect BestRect = {690 - BestScoreSurface->w / 2, 100, BestScoreSurface->w, BestScoreSurface->h};
    SDL_RenderCopy(Renderer, BestScoreTexture, NULL, &BestRect);
    SDL_FreeSurface(BestScoreSurface);
    SDL_DestroyTexture(BestScoreTexture);
}

void PrintNotes() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (Map[i][j]) {
                NoteRect.x = 88 + 162 * j;
                NoteRect.y = 316 + 157 * i;
                SDL_Texture *NoteTexture = NULL;
                NoteTexture = SDL_CreateTextureFromSurface(Renderer, NoteSurface[Map[i][j] < 17 ? Map[i][j] - 1 : 16]);
                SDL_RenderCopy(Renderer, NoteTexture, NULL, &NoteRect);
                SDL_DestroyTexture(NoteTexture);
            }
}

void StartAndLoad() {
    MainBackGroundSurface = IMG_Load("IMAGE/MainBackGround.png");
    PlayBackGroundSurface = IMG_Load("IMAGE/PlayBackGround.png");
    for (int i = 0; i < 3; ++i) {
        char BoxName[20];
        sprintf(BoxName, "IMAGE/MsgBox%d.png", i);
        MsgBoxSurface[i] = IMG_Load(BoxName);
    }
    Font = TTF_OpenFont("IMAGE/GenshinDefault.ttf", 48);//由于Linux对于文件名大小写的高敏感性 注意后缀的大小写
    for (int i = 0; i < 17; ++i) {
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
    for (int i = 0; i < 14; ++i)
        SDL_FreeSurface(NoteSurface[i]);
    for (int i = 0; i < 3; ++i)
        SDL_FreeSurface(MsgBoxSurface[i]);
    TTF_CloseFont(Font);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}
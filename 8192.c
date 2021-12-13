#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void PlayUI(SDL_Event PlayEvent);//游戏界面

void Move(int Dir1, int Dir2);//移动面板_核心算法

void RandomCreate();//随机生成2或4

void SaveMap(int RecMap[][4]);//储存面板

void Revoke();//撤回一步

void Restart();//重开游戏

void IfOver();//判断是否游戏结束

void MsgBox(int kind);

void PrintAll();//清空渲染器，重新打印全部

void PrintTime();//打印计时器的时间

void PrintScores();//打印分数与最高分

void PrintNotes();//打印数字方块

void StartAndLoad();//启动并加载图片和字体

void FreeAndQuit();//清除所有加载项并退出

int IfBegin = 0, IfWin = 0, IfMsgBox = 0;

int Score = 0, OldScore = 0, BestScore = 0, OldBestScore = 0;
char ScoreChar[10], BestScoreChar[10];

int DownButtonX, DownButtonY, UpButtonX, UpButtonY;

time_t PlayStartTime, PlayEndTime, PauseTime, MainTime;
char TimeChar[10];

int Map[4][4] = {
        {2, 32, 64,  8192},
        {0, 16, 128, 4096},
        {0, 8,  256, 2048},
        {0, 4,  512, 1024}
};

// int Map[4][4] = {
//         {0, 0, 0, 0},
//         {0, 0, 0, 0},
//         {0, 0, 0, 0},
//         {0, 0, 0, 0}
// };

// int Map[4][4] = {
//         {0, 0, 0, 0},
//         {0, 0, 0, 0},
//         {0, 0, 0, 0},
//         {0, 0, 0, 0}
// };

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

SDL_Rect MsgBoxRect;

SDL_Surface *GameOverMsgBoxSurface = NULL;
SDL_Texture *GameOverMsgBoxTexture = NULL;

SDL_Surface *GamePauseMsgBoxSurface = NULL;
SDL_Texture *GamePauseMsgBoxTexture = NULL;

SDL_Surface *GameWinMsgBoxSurface = NULL;
SDL_Texture *GameWinMsgBoxTexture = NULL;

TTF_Font *ScoreFont = NULL;
SDL_Surface *ScoreSurface = NULL;
SDL_Texture *ScoreTexture = NULL;
SDL_Rect ScoreRect;

TTF_Font *TimeFont = NULL;
SDL_Surface *TimeSurface = NULL;
SDL_Texture *TimeTexture = NULL;
SDL_Rect TimeRect;

SDL_Color FontColor = {255, 255, 255, 255};

SDL_Surface *Note2Surface = NULL;
SDL_Texture *Note2Texture = NULL;
SDL_Rect Note2Rect;

SDL_Surface *Note4Surface = NULL;
SDL_Texture *Note4Texture = NULL;
SDL_Rect Note4Rect;

SDL_Surface *Note8Surface = NULL;
SDL_Texture *Note8Texture = NULL;
SDL_Rect Note8Rect;

SDL_Surface *Note16Surface = NULL;
SDL_Texture *Note16Texture = NULL;
SDL_Rect Note16Rect;

SDL_Surface *Note32Surface = NULL;
SDL_Texture *Note32Texture = NULL;
SDL_Rect Note32Rect;

SDL_Surface *Note64Surface = NULL;
SDL_Texture *Note64Texture = NULL;
SDL_Rect Note64Rect;

SDL_Surface *Note128Surface = NULL;
SDL_Texture *Note128Texture = NULL;
SDL_Rect Note128Rect;

SDL_Surface *Note256Surface = NULL;
SDL_Texture *Note256Texture = NULL;
SDL_Rect Note256Rect;

SDL_Surface *Note512Surface = NULL;
SDL_Texture *Note512Texture = NULL;
SDL_Rect Note512Rect;

SDL_Surface *Note1024Surface = NULL;
SDL_Texture *Note1024Texture = NULL;
SDL_Rect Note1024Rect;

SDL_Surface *Note2048Surface = NULL;
SDL_Texture *Note2048Texture = NULL;
SDL_Rect Note2048Rect;

SDL_Surface *Note4096Surface = NULL;
SDL_Texture *Note4096Texture = NULL;
SDL_Rect Note4096Rect;

SDL_Surface *Note8192Surface = NULL;
SDL_Texture *Note8192Texture = NULL;
SDL_Rect Note8192Rect;

SDL_Surface *Note16384Surface = NULL;
SDL_Texture *Note16384Texture = NULL;
SDL_Rect Note16384Rect;

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    Window = SDL_CreateWindow("Sakiyary's Infinite 2048 ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 1000, SDL_WINDOW_SHOWN);
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event MainEvent;
    SDL_Event PlayEvent;
    StartAndLoad();
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
                        PlayUI(PlayEvent);
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
                    PlayUI(PlayEvent);
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


void PlayUI(SDL_Event PlayEvent) {
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
                    printf("(%d,%d)\n", PlayEvent.button.x, PlayEvent.button.y);
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
                    printf("(%d,%d)\n", PlayEvent.button.x, PlayEvent.button.y);
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
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            RecMap[i][j] = Map[i][j];
        }
    }
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
                Map[Dir1 ? j : i][Dir1 ? i : j] *= 2;
                Score += Map[Dir1 ? j : i][Dir1 ? i : j];
                BestScore = BestScore < Score ? Score : BestScore;
                if (Map[Dir1 ? j : i][Dir1 ? i : j] == 2048 && !IfWin)IfWin = 1;
                for (int k = Dir2 ? j + 1 : j - 1; (Dir2 && k < 3) || (!Dir2 && k > 0); k += Dir2 ? 1 : -1)
                    Map[Dir1 ? k : i][Dir1 ? i : k] = Map[Dir1 ? (Dir2 ? k + 1 : k - 1) : i][Dir1 ? i : (Dir2 ? k + 1 : k - 1)];
                Map[Dir1 ? (Dir2 ? 3 : 0) : i][Dir1 ? i : (Dir2 ? 3 : 0)] = 0;
                IfMove = 1;
            }
        }
        if (!IfMove)
            for (int j = 0; j < 4; ++j)
                if (RecMap[Dir1 ? j : i][Dir1 ? i : j] != Map[Dir1 ? j : i][Dir1 ? i : j])
                    IfMove = 1;
    }
    PrintAll();
    if (IfMove) {
        SaveMap(RecMap);
        if (IfWin == 1) {
            MsgBox(1);
            IfWin = 2;
        }
        RandomCreate();
    }
    IfOver();
}

void RandomCreate() {
    int cnt = 0;
    srand((unsigned) time(NULL));
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (!Map[i][j])cnt++;
    if (!cnt)return;
    SDL_Delay(200);
    int pivot = rand() % cnt + 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (!Map[i][j]) {
                pivot--;
                if (!pivot) {
                    Map[i][j] = rand() % 4 ? 2 : 4;
                    break;
                }
            }
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
    for (int i = 0; i < 4; ++i) {
        if (!flag)
            for (int j = 0; j < 3; ++j)
                if (Map[i][j] == Map[i][j + 1] || Map[j][i] == Map[j + 1][i]) {
                    flag = 1;
                    break;
                }
    }
    if (!flag)MsgBox(0);

}

void SaveMap(int RecMap[][4]) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            OldMap[i][j] = RecMap[i][j];
    OldScore = Score;
    OldBestScore = BestScore;
}

void Revoke() {
    IfMsgBox = 0;
    int IfRevoke = 1, cnt = 0;
    for (int i = 0; i < 4; ++i) {
        if (!IfRevoke)break;
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
    if (cnt == 16)printf("This is your first step !\n");
    else if (IfRevoke)printf("You can only revoke one time !\n");
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
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Map[i][j] = 0;
            OldMap[i][j] = 0;
        }
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

void MsgBox(int kind) {
    //kind=0:Game Over; 1:Game Win; 2:Game Pause.
    PauseTime = time(NULL);
    SDL_Event MsgEvent;
    IfMsgBox = 1;
    switch (kind) {
        case 0:
            IfMsgBox = 2;
            SDL_RenderCopy(Renderer, GameOverMsgBoxTexture, NULL, &MsgBoxRect);
            SDL_RenderPresent(Renderer);
            printf("Game Over\n");
            break;
        case 1:
            SDL_RenderCopy(Renderer, GameWinMsgBoxTexture, NULL, &MsgBoxRect);;
            SDL_RenderPresent(Renderer);
            printf("Game Win\n");
            break;
        case 2:
            SDL_RenderCopy(Renderer, GamePauseMsgBoxTexture, NULL, &MsgBoxRect);;
            SDL_RenderPresent(Renderer);
            printf("Pause\n");
            break;
        default:
            break;
    }
}

void GameOverMsgBox() {
    Restart();
}

void GameWinMsgBox() {

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
    TimeSurface = TTF_RenderUTF8_Blended(TimeFont, TimeChar, FontColor);
    TimeTexture = SDL_CreateTextureFromSurface(Renderer, TimeSurface);
    TimeRect.x = 188;
    TimeRect.y = 212;
    TimeRect.w = TimeSurface->w;
    TimeRect.h = TimeSurface->h;
    SDL_RenderCopy(Renderer, TimeTexture, NULL, &TimeRect);
}

void PrintScores() {
    sprintf(ScoreChar, "%d", Score);
    ScoreSurface = TTF_RenderUTF8_Blended(ScoreFont, ScoreChar, FontColor);
    ScoreTexture = SDL_CreateTextureFromSurface(Renderer, ScoreSurface);
    ScoreRect.x = 580;
    ScoreRect.y = 38;
    ScoreRect.w = ScoreSurface->w;
    ScoreRect.h = ScoreSurface->h;
    SDL_RenderCopy(Renderer, ScoreTexture, NULL, &ScoreRect);
    sprintf(BestScoreChar, "%d", BestScore);
    ScoreSurface = TTF_RenderUTF8_Blended(ScoreFont, BestScoreChar, FontColor);
    ScoreTexture = SDL_CreateTextureFromSurface(Renderer, ScoreSurface);
    ScoreRect.x = 580;
    ScoreRect.y = 94;
    ScoreRect.w = ScoreSurface->w;
    ScoreRect.h = ScoreSurface->h;
    SDL_RenderCopy(Renderer, ScoreTexture, NULL, &ScoreRect);
}

void PrintNotes() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            switch (Map[i][j]) {
                case 0:
                    continue;
                case 2:
                    Note2Rect.x = 88 + 162 * j;
                    Note2Rect.y = 316 + 157 * i;
                    SDL_RenderCopy(Renderer, Note2Texture, NULL, &Note2Rect);
                    break;
                case 4:
                    Note4Rect.x = 88 + 162 * j;
                    Note4Rect.y = 316 + 157 * i;
                    SDL_RenderCopy(Renderer, Note4Texture, NULL, &Note4Rect);
                    break;
                case 8:
                    Note8Rect.x = 88 + 162 * j;
                    Note8Rect.y = 316 + 157 * i;
                    SDL_RenderCopy(Renderer, Note8Texture, NULL, &Note8Rect);
                    break;
                case 16:
                    Note16Rect.x = 88 + 162 * j;
                    Note16Rect.y = 316 + 157 * i;
                    SDL_RenderCopy(Renderer, Note16Texture, NULL, &Note16Rect);
                    break;
                case 32:
                    Note32Rect.x = 88 + 162 * j;
                    Note32Rect.y = 316 + 157 * i;
                    SDL_RenderCopy(Renderer, Note32Texture, NULL, &Note32Rect);
                    break;
                case 64:
                    Note64Rect.x = 88 + 162 * j;
                    Note64Rect.y = 316 + 157 * i;
                    SDL_RenderCopy(Renderer, Note64Texture, NULL, &Note64Rect);
                    break;
                case 128:
                    Note128Rect.x = 88 + 162 * j;
                    Note128Rect.y = 316 + 157 * i;
                    SDL_RenderCopy(Renderer, Note128Texture, NULL, &Note128Rect);
                    break;
                case 256:
                    Note256Rect.x = 88 + 162 * j;
                    Note256Rect.y = 316 + 157 * i;
                    SDL_RenderCopy(Renderer, Note256Texture, NULL, &Note256Rect);
                    break;
                case 512:
                    Note512Rect.x = 88 + 162 * j;
                    Note512Rect.y = 316 + 157 * i;
                    SDL_RenderCopy(Renderer, Note512Texture, NULL, &Note512Rect);
                    break;
                case 1024:
                    Note1024Rect.x = 88 + 162 * j;
                    Note1024Rect.y = 316 + 157 * i;
                    SDL_RenderCopy(Renderer, Note1024Texture, NULL, &Note1024Rect);
                    break;
                case 2048:
                    Note2048Rect.x = 88 + 162 * j;
                    Note2048Rect.y = 316 + 157 * i;
                    SDL_RenderCopy(Renderer, Note2048Texture, NULL, &Note2048Rect);
                    break;
                case 4096:
                    Note4096Rect.x = 88 + 162 * j;
                    Note4096Rect.y = 316 + 157 * i;
                    SDL_RenderCopy(Renderer, Note4096Texture, NULL, &Note4096Rect);
                    break;
                case 8192:
                    Note8192Rect.x = 88 + 162 * j;
                    Note8192Rect.y = 316 + 157 * i;
                    SDL_RenderCopy(Renderer, Note8192Texture, NULL, &Note8192Rect);
                    break;
                case 16384:
                case 32768:
                case 65536:
                case 131072:
                    Note16384Rect.x = 88 + 162 * j;
                    Note16384Rect.y = 316 + 157 * i;
                    SDL_RenderCopy(Renderer, Note16384Texture, NULL, &Note16384Rect);
                default:
                    break;
            }
        }
    }
}

void StartAndLoad() {
    MainBackGroundSurface = IMG_Load("IMAGE/MainBackGround.png");
    PlayBackGroundSurface = IMG_Load("IMAGE/PlayBackGround.png");
    GameOverMsgBoxSurface = IMG_Load("IMAGE/GameOverMsgBox.png");
    GamePauseMsgBoxSurface = IMG_Load("IMAGE/GamePauseMsgBox.png");
    GameWinMsgBoxSurface = IMG_Load("IMAGE/GameWinMsgBox.png");

    MainBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, MainBackGroundSurface);
    PlayBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, PlayBackGroundSurface);
    GameOverMsgBoxTexture = SDL_CreateTextureFromSurface(Renderer, GameOverMsgBoxSurface);
    GamePauseMsgBoxTexture = SDL_CreateTextureFromSurface(Renderer, GamePauseMsgBoxSurface);
    GameWinMsgBoxTexture = SDL_CreateTextureFromSurface(Renderer, GameWinMsgBoxSurface);

    MsgBoxRect.w = GameOverMsgBoxSurface->w;
    MsgBoxRect.h = GameOverMsgBoxSurface->h;
    MsgBoxRect.x = 100;
    MsgBoxRect.y = 300;

    ScoreFont = TTF_OpenFont("IMAGE/COPRGTB.TTF", 50);
    TimeFont = TTF_OpenFont("IMAGE/COPRGTL.TTF", 50);

    Note2Surface = IMG_Load("IMAGE/Note2.png");
    Note4Surface = IMG_Load("IMAGE/Note4.png");
    Note8Surface = IMG_Load("IMAGE/Note8.png");
    Note16Surface = IMG_Load("IMAGE/Note16.png");
    Note32Surface = IMG_Load("IMAGE/Note32.png");
    Note64Surface = IMG_Load("IMAGE/Note64.png");
    Note128Surface = IMG_Load("IMAGE/Note128.png");
    Note256Surface = IMG_Load("IMAGE/Note256.png");
    Note512Surface = IMG_Load("IMAGE/Note512.png");
    Note1024Surface = IMG_Load("IMAGE/Note1024.png");
    Note2048Surface = IMG_Load("IMAGE/Note2048.png");
    Note4096Surface = IMG_Load("IMAGE/Note4096.png");
    Note8192Surface = IMG_Load("IMAGE/Note8192.png");
    Note16384Surface = IMG_Load("IMAGE/Note16384.png");

    Note2Texture = SDL_CreateTextureFromSurface(Renderer, Note2Surface);
    Note4Texture = SDL_CreateTextureFromSurface(Renderer, Note4Surface);
    Note8Texture = SDL_CreateTextureFromSurface(Renderer, Note8Surface);
    Note16Texture = SDL_CreateTextureFromSurface(Renderer, Note16Surface);
    Note32Texture = SDL_CreateTextureFromSurface(Renderer, Note32Surface);
    Note64Texture = SDL_CreateTextureFromSurface(Renderer, Note64Surface);
    Note128Texture = SDL_CreateTextureFromSurface(Renderer, Note128Surface);
    Note256Texture = SDL_CreateTextureFromSurface(Renderer, Note256Surface);
    Note512Texture = SDL_CreateTextureFromSurface(Renderer, Note512Surface);
    Note1024Texture = SDL_CreateTextureFromSurface(Renderer, Note1024Surface);
    Note2048Texture = SDL_CreateTextureFromSurface(Renderer, Note2048Surface);
    Note4096Texture = SDL_CreateTextureFromSurface(Renderer, Note4096Surface);
    Note8192Texture = SDL_CreateTextureFromSurface(Renderer, Note8192Surface);
    Note16384Texture = SDL_CreateTextureFromSurface(Renderer, Note16384Surface);

    Note2Rect.w = Note2Surface->w;
    Note2Rect.h = Note2Surface->h;
    Note4Rect.w = Note4Surface->w;
    Note4Rect.h = Note4Surface->h;
    Note8Rect.w = Note8Surface->w;
    Note8Rect.h = Note8Surface->h;
    Note16Rect.w = Note16Surface->w;
    Note16Rect.h = Note16Surface->h;
    Note32Rect.w = Note32Surface->w;
    Note32Rect.h = Note32Surface->h;
    Note64Rect.w = Note64Surface->w;
    Note64Rect.h = Note64Surface->h;
    Note128Rect.w = Note128Surface->w;
    Note128Rect.h = Note128Surface->h;
    Note256Rect.w = Note256Surface->w;
    Note256Rect.h = Note256Surface->h;
    Note512Rect.w = Note512Surface->w;
    Note512Rect.h = Note512Surface->h;
    Note1024Rect.w = Note1024Surface->w;
    Note1024Rect.h = Note1024Surface->h;
    Note2048Rect.w = Note2048Surface->w;
    Note2048Rect.h = Note2048Surface->h;
    Note4096Rect.w = Note4096Surface->w;
    Note4096Rect.h = Note4096Surface->h;
    Note8192Rect.w = Note8192Surface->w;
    Note8192Rect.h = Note8192Surface->h;
    Note16384Rect.w = Note16384Surface->w;
    Note16384Rect.h = Note16384Surface->h;
}

void FreeAndQuit() {
    SDL_FreeSurface(MainBackGroundSurface);
    SDL_FreeSurface(PlayBackGroundSurface);
    SDL_FreeSurface(GameOverMsgBoxSurface);
    SDL_FreeSurface(GamePauseMsgBoxSurface);
    SDL_FreeSurface(GameWinMsgBoxSurface);
    SDL_FreeSurface(Note2Surface);
    SDL_FreeSurface(Note4Surface);
    SDL_FreeSurface(Note8Surface);
    SDL_FreeSurface(Note16Surface);
    SDL_FreeSurface(Note32Surface);
    SDL_FreeSurface(Note64Surface);
    SDL_FreeSurface(Note128Surface);
    SDL_FreeSurface(Note256Surface);
    SDL_FreeSurface(Note512Surface);
    SDL_FreeSurface(Note1024Surface);
    SDL_FreeSurface(Note2048Surface);
    SDL_FreeSurface(Note4096Surface);
    SDL_FreeSurface(Note8192Surface);
    SDL_FreeSurface(Note16384Surface);

    SDL_DestroyTexture(MainBackGroundTexture);
    SDL_DestroyTexture(PlayBackGroundTexture);
    SDL_DestroyTexture(GameOverMsgBoxTexture);
    SDL_DestroyTexture(GamePauseMsgBoxTexture);
    SDL_DestroyTexture(GameWinMsgBoxTexture);
    SDL_DestroyTexture(Note2Texture);
    SDL_DestroyTexture(Note4Texture);
    SDL_DestroyTexture(Note8Texture);
    SDL_DestroyTexture(Note16Texture);
    SDL_DestroyTexture(Note32Texture);
    SDL_DestroyTexture(Note64Texture);
    SDL_DestroyTexture(Note128Texture);
    SDL_DestroyTexture(Note256Texture);
    SDL_DestroyTexture(Note512Texture);
    SDL_DestroyTexture(Note1024Texture);
    SDL_DestroyTexture(Note2048Texture);
    SDL_DestroyTexture(Note4096Texture);
    SDL_DestroyTexture(Note8192Texture);
    SDL_DestroyTexture(Note16384Texture);

    TTF_CloseFont(ScoreFont);
    TTF_CloseFont(TimeFont);

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void PlayUI(SDL_Event PlayEvent);//游戏界面

void Move(int Dir1, int Dir2);//移动面板_核心算法

void RandomCreate();//随机生成2或4

void SaveMap();//储存面板

void Revoke();//撤回一步

void Pause();//暂停游戏

void Restart();//重开游戏

void IfOver();//判断是否游戏结束

void GameOverMsgbox();//游戏结束弹窗

void GameWinMsgbox();//游戏胜利弹窗

void GamePauseMsgbox();//游戏暂停弹窗

void GameRestartMsgbox();//游戏重开弹窗

void PrintAll();//清空渲染器，重新打印全部

void PrintTime();//打印计时器的时间

void PrintScores();//打印分数与最高分

void PrintNotes();//打印数字方块

void StartAndLoad();//启动并加载图片和字体

void FreeAndQuit();//清除所有加载项并退出

int IfBegin = 0, IfWin = 0;

int Score = 0, OldScore = 0, BestScore = 0, OldBestScore = 0;
char ScoreChar[10], BestScoreChar[10];

int DownButtonX, DownButtonY, UpButtonX, UpButtonY;

time_t PlayStartTime, PlayEndTime, PauseTime;
char TimeChar[10];

int Map[4][4] = {
        {0, 16, 32,  4096},
        {0, 8,  64,  2048},
        {0, 4,  128, 1024},
        {0, 2,  256, 512}
};

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
            case SDL_MOUSEBUTTONDOWN:
                printf("(%d,%d)\n", MainEvent.button.x, MainEvent.button.y);
                if (MainEvent.button.x > 205 && MainEvent.button.x < 604 && MainEvent.button.y > 650 && MainEvent.button.y < 777) {
                    if (!IfBegin)
                        RandomCreate();
                    PlayUI(PlayEvent);
                }
                break;
            case SDL_KEYDOWN:
                switch (MainEvent.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_BACKSPACE:
                        FreeAndQuit();
                    case SDLK_RETURN:
                        if (!IfBegin)RandomCreate();
                        for (int i = 0; i < 4; ++i) {
                            for (int j = 0; j < 4; ++j) {
                                printf("%d ", Map[i][j]);
                            }
                            printf("\n");
                        }
                        PlayUI(PlayEvent);
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
        SDL_Delay(10);
    }
    FreeAndQuit();
}


void PlayUI(SDL_Event PlayEvent) {
    PlayStartTime = time(NULL);
    IfBegin = 1;
    printf("PlayEvent\n");
    while (1) {
        PrintAll();
        while (SDL_WaitEventTimeout(&PlayEvent, 100)) {
            switch (PlayEvent.type) {
                case SDL_QUIT:
                    FreeAndQuit();
                case SDL_KEYDOWN:
                    switch (PlayEvent.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_BACKSPACE:
                            printf("MainEvent\n");
                            return;
                        case SDLK_z:
                            Revoke();
                            printf("REVOKE\n");
                            break;
                        case SDLK_r:
                            Restart();
                            printf("RESTART\n");
                            break;
                        case SDLK_w:
                        case SDLK_UP:
                            Move(1, 1);
                            break;
                        case SDLK_s:
                        case SDLK_DOWN:
                            Move(1, 0);
                            break;
                        case SDLK_a:
                        case SDLK_LEFT:
                            Move(0, 1);
                            break;
                        case SDLK_d:
                        case SDLK_RIGHT:
                            Move(0, 0);
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    DownButtonX = PlayEvent.button.x;
                    DownButtonY = PlayEvent.button.y;
                    printf("(%d,%d)\n", PlayEvent.button.x, PlayEvent.button.y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    UpButtonX = PlayEvent.button.x;
                    UpButtonY = PlayEvent.button.y;
                    if (DownButtonX - UpButtonX < 100 && UpButtonX - DownButtonX < 100 && DownButtonY - UpButtonY > 100)
                        Move(1, 1);
                    else if (DownButtonX - UpButtonX < 100 && UpButtonX - DownButtonX < 100 && UpButtonY - DownButtonY > 100)
                        Move(1, 0);
                    else if (DownButtonY - UpButtonY < 100 && UpButtonY - DownButtonY < 100 && DownButtonX - UpButtonX > 100)
                        Move(0, 1);
                    else if (DownButtonY - UpButtonY < 100 && UpButtonY - DownButtonY < 100 && UpButtonX - DownButtonX > 100)
                        Move(0, 0);
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
    SaveMap();
    int IfMove = 0;
    for (int i = 0; i < 4; ++i) {
        if (!Map[Dir1 ? 0 : i][Dir1 ? i : 0] && !Map[Dir1 ? 1 : i][Dir1 ? i : 1] && !Map[Dir1 ? 2 : i][Dir1 ? i : 2] && !Map[Dir1 ? 3 : i][Dir1 ? i : 3])continue;
        int Rec[4];
        for (int j = 0; j < 4; ++j)Rec[j] = Map[Dir1 ? j : i][Dir1 ? i : j];
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
                if (Map[Dir1 ? j : i][Dir1 ? i : j] == 2048)GameWinMsgbox();
                for (int k = Dir2 ? j + 1 : j - 1; (Dir2 && k < 3) || (!Dir2 && k > 0); k += Dir2 ? 1 : -1)
                    Map[Dir1 ? k : i][Dir1 ? i : k] = Map[Dir1 ? (Dir2 ? k + 1 : k - 1) : i][Dir1 ? i : (Dir2 ? k + 1 : k - 1)];
                Map[Dir1 ? (Dir2 ? 3 : 0) : i][Dir1 ? i : (Dir2 ? 3 : 0)] = 0;
                IfMove = 1;
            }
        }
        if (!IfMove)
            for (int j = 0; j < 4; ++j)
                if (Rec[j] != Map[Dir1 ? j : i][Dir1 ? i : j])
                    IfMove = 1;
    }
    PrintAll();
    if (IfMove)RandomCreate();
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
    PrintAll();
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
    if (!flag)GameOverMsgbox();
}

void SaveMap() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            OldMap[i][j] = Map[i][j];
    OldScore = Score;
    OldBestScore = BestScore;
}

void Revoke() {
    int IfRevoke = 1;
    for (int i = 0; i < 4; ++i) {
        if (!IfRevoke)break;
        for (int j = 0; j < 4; ++j)
            if (Map[i][j] != OldMap[i][j]) {
                IfRevoke = 0;
                break;
            }
    }
    if (IfRevoke)printf("You can only revoke one time !\n");
    else {
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
    Score = 0;
    RandomCreate();
}

void GameOverMsgbox() {
    Restart();
}

void GameWinMsgbox() {
    if (!IfWin) {
        return;
    }
    IfWin = 1;
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
                default:
                    break;
            }
        }
    }
}

void StartAndLoad() {
    MainBackGroundSurface = IMG_Load("IMAGE/MainBackGround.png");
    MainBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, MainBackGroundSurface);
    PlayBackGroundSurface = IMG_Load("IMAGE/PlayBackGround.png");
    PlayBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, PlayBackGroundSurface);

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
}

void FreeAndQuit() {
    SDL_FreeSurface(MainBackGroundSurface);
    SDL_FreeSurface(PlayBackGroundSurface);
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

    SDL_DestroyTexture(MainBackGroundTexture);
    SDL_DestroyTexture(PlayBackGroundTexture);
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

    TTF_CloseFont(ScoreFont);
    TTF_CloseFont(TimeFont);

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}
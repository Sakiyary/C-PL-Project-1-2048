#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void MoveUP();

void MoveDOWN();

void MoveRIGHT();

void MoveLEFT();

void PrintNotes();

void RandomCreate();

void SaveMap();

void Revoke();

void Restart();

void StartAndLoad();

void FreeAndQuit();

void PlayUI(SDL_Event PlayEvent);

int IfBegin = 0;

int Score = 0;

//int Map[4][4] = {
//        {4, 2, 4, 0},
//        {2, 4, 2, 8},
//        {4, 2, 4, 2},
//        {2, 4, 2, 0}
//};
int Map[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
};

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
    Window = SDL_CreateWindow("Sakiyary's Infinite 2048 ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 1000, SDL_WINDOW_SHOWN);
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event MainEvent;
    SDL_Event PlayEvent;
    StartAndLoad();
    printf("MainEvent\n");
    while (SDL_WaitEvent(&MainEvent) || SDL_PollEvent(&MainEvent)) {
        SDL_RenderClear(Renderer);
        SDL_RenderCopy(Renderer, MainBackGroundTexture, NULL, NULL);
        SDL_RenderPresent(Renderer);
        switch (MainEvent.type) {
            case SDL_QUIT:
                FreeAndQuit();
            case SDL_MOUSEBUTTONDOWN:
                printf("(%d,%d)\n", MainEvent.button.x, MainEvent.button.y);
                if (MainEvent.button.x > 212 && MainEvent.button.x < 604 && MainEvent.button.y > 656 && MainEvent.button.y < 772) {
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
    IfBegin = 1;
    printf("PlayEvent\n");
    while (SDL_WaitEvent(&PlayEvent) || SDL_PollEvent(&PlayEvent)) {
        SDL_RenderClear(Renderer);
        SDL_RenderCopy(Renderer, PlayBackGroundTexture, NULL, NULL);
        SDL_RenderPresent(Renderer);
        PrintNotes();
//        while (SDL_PollEvent(&PlayEvent)) {
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
                    case SDLK_UP:
                        MoveUP();
                        printf("UP\n");
                        for (int i = 0; i < 4; ++i) {
                            for (int j = 0; j < 4; ++j) {
                                printf("%d ", Map[i][j]);
                            }
                            printf("\n");
                        }
                        break;
                    case SDLK_DOWN:
                        MoveDOWN();
                        printf("DOWN\n");
                        for (int i = 0; i < 4; ++i) {
                            for (int j = 0; j < 4; ++j) {
                                printf("%d ", Map[i][j]);
                            }
                            printf("\n");
                        }
                        break;
                    case SDLK_RIGHT:
                        MoveRIGHT();
                        printf("RIGHT\n");
                        for (int i = 0; i < 4; ++i) {
                            for (int j = 0; j < 4; ++j) {
                                printf("%d ", Map[i][j]);
                            }
                            printf("\n");
                        }
                        break;
                    case SDLK_LEFT:
                        MoveLEFT();
                        printf("LEFT\n");
                        for (int i = 0; i < 4; ++i) {
                            for (int j = 0; j < 4; ++j) {
                                printf("%d ", Map[i][j]);
                            }
                            printf("\n");
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("(%d,%d)\n", PlayEvent.button.x, PlayEvent.button.y);
                break;
            default:
                break;
        }
        SDL_Delay(10);
//        }
    }
}

void PrintNotes() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            switch (Map[i][j]) {
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
    SDL_RenderPresent(Renderer);
}

void RandomCreate() {
    int cnt = 0;
    srand((unsigned) time(NULL));
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (!Map[i][j])cnt++;
        }
    }
    if (!cnt) {
        PrintNotes();
        return;
    }
    int pivot = rand() % cnt + 1;
    printf("cnt=%d pivot=%d\n", cnt, pivot);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (!Map[i][j])pivot--;
            if (!Map[i][j] && !pivot) {
                Map[i][j] = rand() % 4 ? 2 : 4;
                printf("i=%d j=%d num=%d\n", i, j, Map[i][j]);
                break;
            }
        }
    }
    PrintNotes();
}

void SaveMap() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            OldMap[i][j] = Map[i][j];
        }
    }
}

void Revoke() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Map[i][j] = OldMap[i][j];
        }
    }
}

void Restart() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Map[i][j] = 0;
            OldMap[i][j] = 0;
        }
    }
    RandomCreate();
}

void MoveUP() {
    SaveMap();
    int IfMove = 0;
    for (int i = 0; i < 4; ++i) {
        if (!Map[0][i] && !Map[1][i] && !Map[2][i] && !Map[3][i])continue;
        int Rec[4];
        for (int j = 0; j < 4; ++j)Rec[j] = Map[j][i];
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 3 - j; ++k)
                if (!Map[j][i]) {
                    for (int l = j; l < 3; ++l) Map[l][i] = Map[l + 1][i];
                    Map[3][i] = 0;
                }
        for (int j = 0; j < 3; ++j) {
            if (Map[j][i] == Map[j + 1][i] && Map[j][i] != 0) {
                Map[j][i] *= 2;
                Score += Map[j][i];
                for (int k = j + 1; k < 3; ++k)Map[k][i] = Map[k + 1][i];
                Map[3][i] = 0;
                IfMove = 1;
            }
        }
        if (!IfMove)for (int j = 0; j < 4; ++j)if (Rec[j] != Map[j][i])IfMove = 1;
    }
    PrintNotes();
    if (IfMove) {
//        SDL_Delay(500);
        RandomCreate();
    }
}

void MoveDOWN() {
    SaveMap();
    int IfMove = 0;
    for (int i = 0; i < 4; ++i) {
        if (!Map[0][i] && !Map[1][i] && !Map[2][i] && !Map[3][i])continue;
        int Rec[4];
        for (int j = 0; j < 4; ++j)Rec[j] = Map[j][i];
        for (int j = 3; j > 0; --j)
            for (int k = 0; k < j; ++k)
                if (!Map[j][i]) {
                    for (int l = j; l > 0; --l) Map[l][i] = Map[l - 1][i];
                    Map[0][i] = 0;
                }
        for (int j = 3; j > 0; --j) {
            if (Map[j][i] == Map[j - 1][i] && Map[j][i] != 0) {
                Map[j][i] *= 2;
                Score += Map[j][i];
                for (int k = j - 1; k > 0; --k)Map[k][i] = Map[k - 1][i];
                Map[0][i] = 0;
            }
        }
        if (!IfMove)for (int j = 0; j < 4; ++j)if (Rec[j] != Map[j][i])IfMove = 1;
    }
    PrintNotes();
    if (IfMove) {
//        SDL_Delay(500);
        RandomCreate();
    }
}

void MoveLEFT() {
    SaveMap();
    int IfMove = 0;
    for (int i = 0; i < 4; ++i) {
        if (!Map[i][0] && !Map[i][1] && !Map[i][2] && !Map[i][3])continue;
        int Rec[4];
        for (int j = 0; j < 4; ++j)Rec[j] = Map[i][j];
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 3 - j; ++k)
                if (!Map[i][j]) {
                    for (int l = j; l < 3; ++l) Map[i][l] = Map[i][l + 1];
                    Map[i][3] = 0;
                }
        for (int j = 0; j < 3; ++j) {
            if (Map[i][j] == Map[i][j + 1] && Map[i][j] != 0) {
                Map[i][j] *= 2;
                Score += Map[i][j];
                for (int k = j + 1; k < 3; ++k)Map[i][k] = Map[i][k + 1];
                Map[i][3] = 0;
                IfMove = 1;
            }
        }
        if (!IfMove)for (int j = 0; j < 4; ++j)if (Rec[j] != Map[i][j])IfMove = 1;
    }
    PrintNotes();
    if (IfMove) {
//        SDL_Delay(500);
        RandomCreate();
    }
}

void MoveRIGHT() {
    SaveMap();
    int IfMove = 0;
    for (int i = 0; i < 4; ++i) {
        if (!Map[i][0] && !Map[i][1] && !Map[i][2] && !Map[i][3])continue;
        int Rec[4];
        for (int j = 0; j < 4; ++j)Rec[j] = Map[i][j];
        for (int j = 3; j > 0; --j)
            for (int k = 0; k < j; ++k)
                if (!Map[i][j]) {
                    for (int l = j; l > 0; --l) Map[i][l] = Map[i][l - 1];
                    Map[i][0] = 0;
                }
        for (int j = 3; j > 0; --j) {
            if (Map[i][j] == Map[i][j - 1] && Map[i][j] != 0) {
                Map[i][j] *= 2;
                Score += Map[i][j];
                for (int k = j - 1; k > 0; --k)Map[i][k] = Map[i][k - 1];
                Map[i][0] = 0;
                IfMove = 1;
            }
        }
        if (!IfMove)for (int j = 0; j < 4; ++j)if (Rec[j] != Map[i][j])IfMove = 1;
    }
    PrintNotes();
    if (IfMove) {
//        SDL_Delay(500);
        RandomCreate();
    }
}

void StartAndLoad() {
    MainBackGroundSurface = IMG_Load("IMAGE/MainBackGround.png");
    MainBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, MainBackGroundSurface);
    PlayBackGroundSurface = IMG_Load("IMAGE/PlayBackGround.png");
    PlayBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, PlayBackGroundSurface);
    Note2Surface = IMG_Load("IMAGE/Note2.png");
    Note2Texture = SDL_CreateTextureFromSurface(Renderer, Note2Surface);
    Note4Surface = IMG_Load("IMAGE/Note4.png");
    Note4Texture = SDL_CreateTextureFromSurface(Renderer, Note4Surface);
    Note8Surface = IMG_Load("IMAGE/Note8.png");
    Note8Texture = SDL_CreateTextureFromSurface(Renderer, Note8Surface);
    Note16Surface = IMG_Load("IMAGE/Note16.png");
    Note16Texture = SDL_CreateTextureFromSurface(Renderer, Note16Surface);
    Note32Surface = IMG_Load("IMAGE/Note32.png");
    Note32Texture = SDL_CreateTextureFromSurface(Renderer, Note32Surface);
    Note64Surface = IMG_Load("IMAGE/Note64.png");
    Note64Texture = SDL_CreateTextureFromSurface(Renderer, Note64Surface);
    Note128Surface = IMG_Load("IMAGE/Note128.png");
    Note128Texture = SDL_CreateTextureFromSurface(Renderer, Note128Surface);
    Note256Surface = IMG_Load("IMAGE/Note256.png");
    Note256Texture = SDL_CreateTextureFromSurface(Renderer, Note256Surface);
    Note512Surface = IMG_Load("IMAGE/Note512.png");
    Note512Texture = SDL_CreateTextureFromSurface(Renderer, Note512Surface);
    Note1024Surface = IMG_Load("IMAGE/Note1024.png");
    Note1024Texture = SDL_CreateTextureFromSurface(Renderer, Note1024Surface);
    Note2048Surface = IMG_Load("IMAGE/Note2048.png");
    Note2048Texture = SDL_CreateTextureFromSurface(Renderer, Note2048Surface);
    Note4096Surface = IMG_Load("IMAGE/Note4096.png");
    Note4096Texture = SDL_CreateTextureFromSurface(Renderer, Note4096Surface);
    Note8192Surface = IMG_Load("IMAGE/Note8192.png");
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

    SDL_DestroyTexture(MainBackGroundTexture);
    SDL_DestroyTexture(PlayBackGroundTexture);
    SDL_DestroyTexture(Note2Texture);
    SDL_DestroyTexture(Note4Texture);

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}
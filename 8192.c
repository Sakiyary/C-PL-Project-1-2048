#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//void MoveUP();
//
//void MoveDOWN();
//
//void MoveRIGHT();
//
//void MoveLEFT();
void LoadStart();

int Map[4][4] = {
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

int main(int argc, char *argv[]) {
    Window = SDL_CreateWindow("Sakiyary's Infinite 2048 ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 1000, SDL_WINDOW_SHOWN);
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event PlayEvent;
    SDL_Event MainEvent;
    LoadStart();
    MAIN:
    printf("MainEvent\n");
    while (SDL_WaitEvent(&MainEvent)||SDL_PollEvent(&MainEvent)) {
        SDL_RenderClear(Renderer);
        SDL_RenderCopy(Renderer, MainBackGroundTexture, NULL, NULL);
        SDL_RenderPresent(Renderer);
        switch (MainEvent.type) {
            case SDL_QUIT:
                goto END;
            case SDL_MOUSEBUTTONDOWN:
                printf("(%d,%d)\n", MainEvent.button.x, MainEvent.button.y);
                if (MainEvent.button.x > 212 && MainEvent.button.x < 604 && MainEvent.button.y > 656 && MainEvent.button.y < 772)
                    goto PLAY;
                break;
            case SDL_KEYDOWN:
                switch (MainEvent.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        goto END;
                    case SDLK_BACKSPACE:
                        goto END;
                    case SDLK_RETURN:
                        goto PLAY;
                    default:
                        break;
                }
            default:
                break;
        }
        SDL_Delay(10);
    }
    PLAY:
    printf("PlayEvent\n");
    while (SDL_WaitEvent(&PlayEvent)||SDL_PollEvent(&PlayEvent)) {
        SDL_RenderClear(Renderer);
        SDL_RenderCopy(Renderer, PlayBackGroundTexture, NULL, NULL);
        SDL_RenderPresent(Renderer);
        switch (PlayEvent.type) {
            case SDL_QUIT:
                goto END;
            case SDL_KEYDOWN:
                switch (PlayEvent.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        goto MAIN;
                    case SDLK_BACKSPACE:
                        goto MAIN;
                    case SDLK_z:
                        printf("REVOKE\n");
                        break;
                    case SDLK_r:
                        printf("RESTART\n");
                        break;
                    case SDLK_UP:
//                        MoveUP();
                        printf("UP\n");
                        break;
                    case SDLK_DOWN:
//                        MoveDOWN();
                        printf("DOWN\n");
                        break;
                    case SDLK_RIGHT:
//                        MoveRIGHT();
                        printf("RIGHT\n");
                        break;
                    case SDLK_LEFT:
//                        MoveLEFT();
                        printf("LEFT\n");
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
    }

    END:

    SDL_FreeSurface(MainBackGroundSurface);
    SDL_FreeSurface(PlayBackGroundSurface);

    SDL_DestroyTexture(MainBackGroundTexture);
    SDL_DestroyTexture(PlayBackGroundTexture);

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);

    SDL_Quit();
}

void LoadStart() {
    MainBackGroundSurface = IMG_Load("IMAGE/MainBackGround.png");
    MainBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, MainBackGroundSurface);
    PlayBackGroundSurface = IMG_Load("IMAGE/PlayBackGround.png");
    PlayBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, PlayBackGroundSurface);
}
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

int Map[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
};

SDL_Window *Window = NULL;
SDL_Renderer *Renderer = NULL;


int main(int argc, char *argv[]) {
    Window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED_DISPLAY(1), SDL_WINDOWPOS_UNDEFINED_DISPLAY(1), 800, 1000, SDL_WINDOW_SHOWN);
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event PlayEvent;
    SDL_Event MainEvent;
    MAIN:
    printf("MainEvent\n");
    while (SDL_WaitEvent(&MainEvent)) {
        switch (MainEvent.type) {
            case SDL_QUIT:
                goto END;
            case SDL_MOUSEBUTTONDOWN:
                printf("(%d,%d)\n", MainEvent.button.x, MainEvent.button.y);
                if (MainEvent.button.x > 600 && MainEvent.button.x < 700)
                    goto PLAY;
                break;
            case SDL_KEYDOWN:
                switch (MainEvent.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        goto END;
                    default:
                        break;
                }
            default:
                break;
        }
    }
    PLAY:
    printf("PlayEvent\n");
    while (SDL_WaitEvent(&PlayEvent)) {
        switch (PlayEvent.type) {
            case SDL_QUIT:
                goto END;
            case SDL_KEYDOWN:
                switch (PlayEvent.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        goto MAIN;
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
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}


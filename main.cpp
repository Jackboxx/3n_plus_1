#include <iostream>
#include "SDL2/SDL.h"

SDL_Window* window;
SDL_Renderer* renderer;
int step = 10;

int init(){
    if(SDL_Init(SDL_INIT_VIDEO) != 0) return -1;
    window = SDL_CreateWindow("3n + 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1400, 700, 0);

    if(!window){
        std::cout << "Window failled to initialize" << std::endl;
        SDL_Quit();
        return -1;
    }

    Uint32 flags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED;
    renderer = SDL_CreateRenderer(window, -1, flags);

    if(!renderer){
        std::cout << "Renderer failled to initialize" << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    return 0;
}

int drawNum(int *num){
    if (*num != 4){
            int previous = *num;
            if(*num % 2 == 0) *num /= 2;
            else *num = 3 * *num + 1;

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderDrawLine(renderer, step, 700 - previous, step + 10, 700 - *num);
            
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            SDL_Rect r = {step - 2, 700 - (previous + 2), 4, 4};
            SDL_RenderDrawRect(renderer, &r);
    }else{
        step = 10;
        return 1;
    }
    
    step += 10;
    return 0;
}

void loop(){
    bool running = true;
    SDL_Event event;

    int count = 3;
    int value = 3;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) running = false;
        }


        if(count <= 100 && drawNum(&value) == 1){
            count++;
            value = count;
        }

        if(count == 100) std::cout << "DONE" <<std::endl;

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
}  

int main(int args, char* argv[]){
    if(init()) return -1;

    loop();
    return 0;
}
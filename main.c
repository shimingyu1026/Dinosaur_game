#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include <conio.h>
#include <Windows.h>
#define zero "Resource/zero.png"
#define one "Resource/one.png"
#define two "Resource/two.png"
#define three "Resource/three.png"
#define four "Resource/four.png"
#define five "Resource/five.png"
#define six "Resource/six.png"
#define seven "Resource/seven.png"
#define eight "Resource/eight.png"
#define nine "Resource/nine.png"

uint32_t begin;
uint32_t current;
long cost;
long frame = 650 / 60;
long delay;

int speed;
int dinosaur_flag = 0;
int flag = 0;
int tag = 0;
int dinosaur_tag = 0;
int obstacle_flag = 0;
int obstacle_tag = 1;
int FLAG = 0;
int score = 0;
int times = 0;

typedef struct
{
    SDL_Surface *surface;
    SDL_Rect rect;
    int count;
} picture;

SDL_Surface *screen;

picture dinosaur;
picture background1;
picture background2;
picture obstacle;
picture score_d;
picture game_over[2];

SDL_Window *window;

void draw_dino(char *file);

void move();

void quit();

void draw_obs(char *file);

void judge_different_obstacles();

void dinosaur_draw_dino(PVOID p);

void random(PVOID p);

void no_name(PVOID p);

void draw_score();

void draw_background();

void game_over_draw();

void A()
{
    _beginthread(dinosaur_draw_dino, 0, 0); // 启动dinosaur_draw_dino
    _beginthread(random, 0, 0);             // 启动random
    _beginthread(no_name, 0, 0);
}

#undef main
int main(int argc, char *argv[])
{

    background2.rect.x = 730;
    background2.rect.y = 0;
    background1.rect.x = 0;
    background1.rect.y = 0;
    background1.surface = IMG_Load("Resource/background1.png");
    background2.surface = IMG_Load("Resource/background2.png");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_StopTextInput();
    window = SDL_CreateWindow("dinosaur", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 730, 400, SDL_WINDOW_SHOWN); // 创建屏幕
    screen = SDL_GetWindowSurface(window);
    A();
    SDL_Event mainevent;
    while (1)
    {
        while (SDL_WaitEvent(&mainevent))
        {
            switch (mainevent.type)
            {
                case SDL_MOUSEBUTTONUP:
                    if (mainevent.button.x > 350 && mainevent.button.x < 384 && mainevent.button.y > 200 && mainevent.button.y < 230 && FLAG == 1)
                    {
                        // printf("(%d,%d) in Main UI\n", mainevent.button.x, mainevent.button.y);
                        FLAG = 0;
                        speed = 2;
                        dinosaur_flag = 0;
                        dinosaur_tag = 0;
                        obstacle_flag = 0;
                        obstacle_tag = 1;
                        score = 0;
                        times = 0;
                        dinosaur.rect.x = 55;
                        dinosaur.rect.y = 270;
                        obstacle.rect.x = 700;
                        obstacle.rect.y = 200;
                    }
                    break;
                case SDL_QUIT:
                    quit();
                    return 0;

                case SDL_KEYDOWN:
                    switch (mainevent.key.keysym.sym)
                    {
                        case SDLK_SPACE:
                            dinosaur_flag = 1;
                            break;

                        case SDLK_UP:
                            dinosaur_flag = 1;
                            break;
                        case SDLK_DOWN:
                            dinosaur_tag = 1;

                            break;
                        default:
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (mainevent.key.keysym.sym)
                    {
                        case SDLK_DOWN:
                            dinosaur_tag = 0;
                            dinosaur_flag = 0;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

void quit()
{
    SDL_DestroyWindow(window);
    SDL_FreeSurface(dinosaur.surface);
    SDL_FreeSurface(background1.surface);
    SDL_FreeSurface(obstacle.surface);
    SDL_FreeSurface(game_over[0].surface);
    SDL_FreeSurface(game_over[1].surface);
}

void move()
{
    if (dinosaur_tag == 1)
    {

        dinosaur.rect.y = 287;
        while (1)
        {
            if (dinosaur_tag == 0)
                break;
            for (int i = 0; i < 15; i++)
            {
                begin = SDL_GetTicks();
                if (dinosaur_tag == 0)
                {
                    dinosaur.rect.y = 270;
                    break;
                }
                if (FLAG == 1)
                {
                    game_over_draw();
                    while (1)
                    {
                        if (FLAG == 0)
                            return;
                    }
                }

                draw_background();
                draw_dino("Resource/dinosaur4.png");
                judge_different_obstacles();
                draw_score();
                SDL_UpdateWindowSurface(window);
                current = SDL_GetTicks();
                cost = current - begin;
                delay = frame - cost;
                if (delay > 0)
                {
                    SDL_Delay(delay);
                }
            }
            for (int i = 0; i < 15; i++)
            {
                begin = SDL_GetTicks();
                if (dinosaur_tag == 0)
                    break;
                if (FLAG == 1)
                {
                    game_over_draw();
                    while (1)
                    {
                        if (FLAG == 0)
                            return;
                    }
                }
                draw_background();
                draw_dino("Resource/dinosaur5.png");
                judge_different_obstacles();
                draw_score();
                SDL_UpdateWindowSurface(window);
                current = SDL_GetTicks();
                cost = current - begin;
                delay = frame - cost;
                if (delay > 0)
                {
                    SDL_Delay(delay);
                }
            }
        }
    }
    int judge = 0;
    if (dinosaur_flag == 1)
    {
        for (int i = 0; i <= 40; i++)
        {
            begin = SDL_GetTicks();
            if (FLAG == 1)
            {
                game_over_draw();
                while (1)
                {
                    if (FLAG == 0)
                        return;
                }
            }
            draw_background();
            dinosaur.rect.y = 270 - 3 * i;
            judge_different_obstacles();
            draw_dino("Resource/dinosaur3.png");
            draw_score();
            SDL_UpdateWindowSurface(window);
            if (dinosaur_tag == 1)
            {
                judge = 1;
                int k = i;
                for (int j = 1; j <= k; j++)
                {
                    begin = SDL_GetTicks();
                    if (FLAG == 1)
                    {
                        game_over_draw();
                        while (1)
                        {
                            if (FLAG == 0)
                                return;
                        }
                    }
                    draw_background();
                    dinosaur.rect.y = 270 - 3 * k + 3 * j;
                    judge_different_obstacles();
                    draw_dino("Resource/dinosaur3.png");
                    draw_score();
                    SDL_UpdateWindowSurface(window);
                    current = SDL_GetTicks();
                    cost = current - begin;
                    delay = frame - cost;
                    if (delay > 0)
                    {
                        SDL_Delay(delay);
                    }
                }
                dinosaur_flag = 0;
                dinosaur.rect.y = 270;
                break;
            }
            current = SDL_GetTicks();
            cost = current - begin;
            delay = frame - cost;
            if (delay > 0)
            {
                SDL_Delay(delay);
            }
        }
        if (judge == 0)
        {
            for (int i = 0; i <= 40; i++)
            {
                begin = SDL_GetTicks();
                if (FLAG == 1)
                {
                    game_over_draw();
                    while (1)
                    {
                        if (FLAG == 0)
                            return;
                    }
                }
                draw_background();
                dinosaur.rect.y = 150 + 3 * i;
                judge_different_obstacles();
                draw_dino("Resource/dinosaur3.png");
                draw_score();
                SDL_UpdateWindowSurface(window);
                current = SDL_GetTicks();
                cost = current - begin;
                delay = frame - cost;
                if (delay > 0)
                {
                    SDL_Delay(delay);
                }
            }
        }
        dinosaur_flag = 0;
    }
}

void dinosaur_draw_dino(PVOID p) // 线程B
{
    while (1)
    {

        for (int i = 0; i < 15; i++)
        {
            begin = SDL_GetTicks();
            dinosaur.rect.x = 55;
            dinosaur.rect.y = 270;
            int judge1 = 0;
            draw_background();
            judge_different_obstacles();
            draw_dino("Resource/dinosaur1.png");
            draw_score();
            SDL_UpdateWindowSurface(window);
            while (FLAG == 1)
            {
                for (; judge1 < 1; judge1++)

                    game_over_draw();
                SDL_Delay(delay);
            }

            move();
            current = SDL_GetTicks();
            cost = current - begin;

            delay = frame - cost;

            if (delay > 0)
            {
                SDL_Delay(delay);
            }
        }

        for (int i = 0; i < 15; i++)
        {
            begin = SDL_GetTicks();
            dinosaur.rect.x = 55;
            dinosaur.rect.y = 270;
            int judge2 = 0;
            draw_background();
            draw_dino("Resource/dinosaur2.png");
            draw_score();
            judge_different_obstacles();

            SDL_UpdateWindowSurface(window);
            while (FLAG == 1)
            {
                for (; judge2 < 1; judge2++)
                    game_over_draw();
                SDL_Delay(delay);
            }

            move();
            current = SDL_GetTicks();
            cost = current - begin;

            delay = frame - cost;

            if (delay > 0)
            {
                SDL_Delay(delay);
            }
        }
    }
}

void draw_dino(char *file)
{
    dinosaur.surface = IMG_Load(file);
    dinosaur.rect.w = dinosaur.surface->w;
    dinosaur.rect.h = dinosaur.surface->h;
    SDL_BlitSurface(dinosaur.surface, NULL, screen, &dinosaur.rect);
    SDL_FreeSurface(dinosaur.surface);
}

void draw_obs(char *file)
{
    obstacle.surface = IMG_Load(file);
    obstacle.rect.h = obstacle.surface->h;
    obstacle.rect.w = obstacle.surface->h;
    SDL_BlitSurface(obstacle.surface, NULL, screen, &obstacle.rect);
    SDL_FreeSurface(obstacle.surface);
}

void random(PVOID p)
{
    int pe = -1;
    while (1)
    {
        while (obstacle_flag == 0)
        {
            srand((unsigned int)time(NULL));
            obstacle_flag = rand() % 6 + 1;
            times++;
            if (obstacle_flag == 1)
            {
                obstacle.rect.x = 700;
                obstacle.rect.y = 200;
            }
            if (obstacle_flag == 2)
            {
                obstacle.rect.x = 700;
                obstacle.rect.y = 245;
            }
            if (obstacle_flag == 3)
            {
                obstacle.rect.x = 700;
                obstacle.rect.y = 270;
            }
            if (obstacle_flag == 4)
            {
                obstacle.rect.x = 700;
                obstacle.rect.y = 283;
            }
            if (obstacle_flag == 5)
            {
                obstacle.rect.x = 700;
                obstacle.rect.y = 269;
            }
            if (obstacle_flag == 6)
            {
                obstacle.rect.x = 700;
                obstacle.rect.y = 283;
            }
        }
    }
}

void judge_different_obstacles()
{
    if (obstacle_flag == 1)
    {
        if (obstacle_tag <= 10)
        {
            obstacle_tag++;
            obstacle.rect.y = 200;
            draw_obs("Resource/pterosaur1.png");
            obstacle.rect.x = obstacle.rect.x - speed;
            if (obstacle.rect.x <= 0)
                obstacle.rect.x = -10;
            if (obstacle.rect.x <= -10)
                obstacle.rect.x = -25;
            if (obstacle.rect.x <= -25)
                obstacle.rect.x = -40;
            return;
        }
        if (obstacle_tag > 10 || obstacle_tag <= 20)
        {
            obstacle.rect.y = 206;
            draw_obs("Resource/pterosaur2.png");
            obstacle.rect.x = obstacle.rect.x - speed;
            if (obstacle.rect.x <= 0)
                obstacle.rect.x = -10;
            if (obstacle.rect.x <= -10)
                obstacle.rect.x = -25;
            if (obstacle.rect.x <= -25)
                obstacle.rect.x = -40;
            if (obstacle_tag == 20)
            {
                obstacle_tag = 0;
            }
            obstacle_tag++;
            return;
        }
    }
    if (obstacle_flag == 2)
    {
        if (obstacle_tag <= 10)
        {
            obstacle_tag++;
            obstacle.rect.y = 245;
            draw_obs("Resource/pterosaur1.png");
            obstacle.rect.x = obstacle.rect.x - speed;
            if (obstacle.rect.x <= 0)
                obstacle.rect.x = -10;
            if (obstacle.rect.x <= -10)
                obstacle.rect.x = -25;
            if (obstacle.rect.x <= -25)
                obstacle.rect.x = -40;
            return;
        }
        if (obstacle_tag > 10 || obstacle_tag <= 20)
        {
            obstacle.rect.y = 251;
            draw_obs("Resource/pterosaur2.png");
            obstacle.rect.x = obstacle.rect.x - speed;
            if (obstacle.rect.x <= 0)
                obstacle.rect.x = -10;
            if (obstacle.rect.x <= -10)
                obstacle.rect.x = -25;
            if (obstacle.rect.x <= -25)
                obstacle.rect.x = -40;
            if (obstacle_tag == 20)
            {
                obstacle_tag = 0;
            }
            obstacle_tag++;
            return;
        }
    }

    if (obstacle_flag == 3)
    {
        draw_obs("Resource/cactus3.png");
        obstacle.rect.x = obstacle.rect.x - speed;
        if (obstacle.rect.x <= 0)
            obstacle.rect.x = -10;
        if (obstacle.rect.x <= -10)
            obstacle.rect.x = -25;
        if (obstacle.rect.x <= -25)
            obstacle.rect.x = -40;
        return;
    }

    if (obstacle_flag == 4)
    {
        draw_obs("Resource/cactus1.png");
        obstacle.rect.x = obstacle.rect.x - speed;
        if (obstacle.rect.x <= 0)
            obstacle.rect.x = -10;
        if (obstacle.rect.x <= -10)
            obstacle.rect.x = -25;
        if (obstacle.rect.x <= -25)
            obstacle.rect.x = -40;
        return;
    }
    if (obstacle_flag == 5)
    {
        draw_obs("Resource/cactus2.png");
        obstacle.rect.x = obstacle.rect.x - speed;
        if (obstacle.rect.x <= 0)
            obstacle.rect.x = -10;
        if (obstacle.rect.x <= -10)
            obstacle.rect.x = -25;
        if (obstacle.rect.x <= -25)
            obstacle.rect.x = -40;
        return;
    }
    if (obstacle_flag == 6)
    {
        draw_obs("Resource/cactus4.png");
        obstacle.rect.x = obstacle.rect.x - speed;
        if (obstacle.rect.x <= 0)
            obstacle.rect.x = -10;
        if (obstacle.rect.x <= -10)
            obstacle.rect.x = -25;
        if (obstacle.rect.x <= -25)
            obstacle.rect.x = -40;
        return;
    }
}
void no_name(PVOID p)
{
    uint32_t begin_time;
    uint32_t current_time;
    SDL_Point p1, p2, p3, p4;
    begin_time = SDL_GetTicks();
    speed = 2;
    while (1)
    {
        if (FLAG == 0)
        {
            p1.x = dinosaur.rect.x + 25;
            p1.y = dinosaur.rect.y + 25;
            p2.x = dinosaur.rect.x + dinosaur.rect.w - 14;
            p2.y = dinosaur.rect.y + 10;
            p3.x = dinosaur.rect.x + 20;
            p3.y = dinosaur.rect.y + dinosaur.rect.h - 20;
            p4.x = dinosaur.rect.x + dinosaur.rect.w - 10;
            p4.y = dinosaur.rect.y + dinosaur.rect.h - 10;
            if (SDL_PointInRect(&p1, &obstacle.rect) || SDL_PointInRect(&p2, &obstacle.rect) || SDL_PointInRect(&p3, &obstacle.rect) || SDL_PointInRect(&p3, &obstacle.rect))
            {
                FLAG = 1;
                tag = dinosaur_tag;
                flag = dinosaur_flag;
                // printf("%d %d\n", flag, tag);
            }
            if (obstacle.rect.x == -40)
            {

                obstacle_flag = 0;
                current_time = SDL_GetTicks();
                if (((current_time - begin_time) / 10000) > 0 && speed <= 8)
                {
                    speed++;
                    begin_time = SDL_GetTicks();
                }
            }
        }
    }
}

void draw_score()
{
    int score_p;
    score_p = score / 15 + 8 * times;
    score_d.rect.x = 680;
    score_d.rect.y = 20;
    for (; score_p != 0;)
    {
        int nu = score_p % 10;
        score_p /= 10;
        switch (nu)
        {
            case 0:
                score_d.surface = IMG_Load(zero);
                SDL_BlitSurface(score_d.surface, NULL, screen, &score_d.rect);
                SDL_FreeSurface(score_d.surface);
                break;
            case 1:
                score_d.surface = IMG_Load(one);
                SDL_BlitSurface(score_d.surface, NULL, screen, &score_d.rect);
                SDL_FreeSurface(score_d.surface);
                break;
            case 2:
                score_d.surface = IMG_Load(two);
                SDL_BlitSurface(score_d.surface, NULL, screen, &score_d.rect);
                SDL_FreeSurface(score_d.surface);
                break;
            case 3:
                score_d.surface = IMG_Load(three);
                SDL_BlitSurface(score_d.surface, NULL, screen, &score_d.rect);
                SDL_FreeSurface(score_d.surface);
                break;
            case 4:
                score_d.surface = IMG_Load(four);
                SDL_BlitSurface(score_d.surface, NULL, screen, &score_d.rect);
                SDL_FreeSurface(score_d.surface);
                break;
            case 5:
                score_d.surface = IMG_Load(five);
                SDL_BlitSurface(score_d.surface, NULL, screen, &score_d.rect);
                SDL_FreeSurface(score_d.surface);
                break;
            case 6:
                score_d.surface = IMG_Load(six);
                SDL_BlitSurface(score_d.surface, NULL, screen, &score_d.rect);
                SDL_FreeSurface(score_d.surface);
                break;
            case 7:
                score_d.surface = IMG_Load(seven);
                SDL_BlitSurface(score_d.surface, NULL, screen, &score_d.rect);
                SDL_FreeSurface(score_d.surface);
                break;
            case 8:
                score_d.surface = IMG_Load(eight);
                SDL_BlitSurface(score_d.surface, NULL, screen, &score_d.rect);
                SDL_FreeSurface(score_d.surface);
                break;
            case 9:
                score_d.surface = IMG_Load(nine);
                SDL_BlitSurface(score_d.surface, NULL, screen, &score_d.rect);
                SDL_FreeSurface(score_d.surface);
                break;
        }

        score_d.rect.x -= 10;
    }
    score++;
}

void draw_background()
{

    SDL_BlitSurface(background1.surface, NULL, screen, &background1.rect);
    SDL_BlitSurface(background2.surface, NULL, screen, &background2.rect);
    int a;
    int b;
    if (background1.rect.x <= background2.rect.x)
    {
        a = background2.rect.x - speed;
        background2.rect.x = a;
        b = background2.rect.x - 730;
        background1.rect.x = b;
    }
    if (background2.rect.x <= background1.rect.x)
    {
        a = background1.rect.x - speed;
        background1.rect.x = a;
        b = background1.rect.x - 730;
        background2.rect.x = b;
    }
    if (background1.rect.x <= background2.rect.x)
    {
        if (background2.rect.x <= 0)
        {
            a = background2.rect.x + 730;
            background1.rect.x = a;
        }
    }
    if (background2.rect.x <= background1.rect.x)
    {
        if (background1.rect.x <= 0)
        {
            a = background1.rect.x + 730;
            background2.rect.x = a;
        }
    }
}
void game_over_draw()
{
    // printf("%d %d\n", flag, tag);
    if ((tag == 1 && flag == 1) || (tag == 0 && flag == 0) || (flag == 1 && tag == 0))
    {
        draw_dino("Resource/dinosaur6.png");
        game_over[0].surface = IMG_Load("Resource/gameover.png");
        game_over[0].rect.x = 270;
        game_over[0].rect.y = 170;
        SDL_BlitSurface(game_over[0].surface, NULL, screen, &game_over[0].rect);
        SDL_FreeSurface(game_over[0].surface);
        game_over[1].surface = IMG_Load("Resource/restart.png");
        game_over[1].rect.x = 350;
        game_over[1].rect.y = 200;
        SDL_BlitSurface(game_over[1].surface, NULL, screen, &game_over[1].rect);
        SDL_FreeSurface(game_over[1].surface);
        SDL_UpdateWindowSurface(window);
    }
    else
    {
        game_over[0].surface = IMG_Load("Resource/gameover.png");
        game_over[0].rect.x = 270;
        game_over[0].rect.y = 170;
        SDL_BlitSurface(game_over[0].surface, NULL, screen, &game_over[0].rect);
        SDL_FreeSurface(game_over[0].surface);
        game_over[1].surface = IMG_Load("Resource/restart.png");
        game_over[1].rect.x = 350;
        game_over[1].rect.y = 200;
        SDL_BlitSurface(game_over[1].surface, NULL, screen, &game_over[1].rect);
        SDL_FreeSurface(game_over[1].surface);
        SDL_UpdateWindowSurface(window);
    }
}
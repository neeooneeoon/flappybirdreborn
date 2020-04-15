#include "sdl_engine.h"

using namespace std;

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT, const string &WINDOW_TITLE)
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    //Window Mode
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //Full-screen Mode
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == nullptr)
        logSDLError(std::cout, "CreateWindow", true);

    //Chay binh thuong
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //Chay may ao
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr)
        logSDLError(std::cout, "CreateRenderer", true);

    setDefaultBGColor(renderer);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderClear(renderer);
}

void setDefaultBGColor(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 113, 197, 207, 255);
}

void loadSprites(SDL_Surface* &surface, SDL_Texture* &texture, SDL_Renderer* &renderer, char* path)
{
    surface = IMG_Load(path);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
}

void quitSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

void destroyObject(SDL_Surface *surface, SDL_Texture *texture)
{
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

bool collisionCheck(SDL_Rect &rect1, SDL_Rect &rect2)
{
    return SDL_HasIntersection(&rect1, &rect2);
}


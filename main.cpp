/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include "LTexture.h"
#include <stdio.h>
#include <ctime>

//Screen dimension constants
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 120;

bool init();
bool loadMedia();
void close();
std::string getTime();

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;
LTexture gTextTexture;
LTexture gDateTexture;
SDL_Color gTextColor = { 255, 255, 255 };
Uint8 gCounter = 0;

std::string getTime()
{
  std::time_t t = std::time( NULL );
  std::tm* time_struct = localtime( &t );
  std::string seconds = std::to_string( time_struct->tm_sec );
  std::string minutes = std::to_string( time_struct->tm_min );
  std::string hours = std::to_string( time_struct->tm_hour );
  char buff[255] = "";
  std::strftime(buff, sizeof( char* ) * 255, "%a %I:%M:%S", time_struct);
  std::string result(buff);
  return result;
}
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("c-clock", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
      //Initialize PNG loading
      int imgFlags = IMG_INIT_PNG;
      if (!(IMG_Init(imgFlags) & imgFlags))
      {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        success = false;
      }
      if( TTF_Init() == -1 )
      {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
      }
      if( SDL_RenderSetLogicalSize( gRenderer, 400, 120 ) != 0 )
      {
        printf( "Failed to set Logical Size! SDL Error: %s\n", SDL_GetError() );
        success = false;
      }
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

  gFont = TTF_OpenFont( "awesome.ttf", 28 );
  if( gFont == NULL )
  {
    printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
    success = false;
  }
  else
  {
    if( !gTextTexture.loadFromRenderedText( gRenderer, gFont, "Hello World!", gTextColor ) )
    {
      printf( "Failed to render text texture!\n" );
      success = false;
    }
    if( !gDateTexture.loadFromRenderedText( gRenderer, gFont, getTime(), gTextColor ) )
    {
      printf( "Failed to render date texture!\n" );
      success = false;
    }
  }

	return success;
}

void close()
{
	//Free loaded image
  gTextTexture.free();
  gDateTexture.free();
  TTF_CloseFont( gFont );
  gFont = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
  TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char *args[])
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;

			SDL_Event e;
      Uint8 frame = 0;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
          else if( e.type == SDL_KEYDOWN )
          {
            switch( e.key.keysym.sym )
            {
              /* SDLK_a */
            }
          }
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 20, 180, 200, 100 );
				SDL_RenderClear( gRenderer );

        gTextTexture.render( gRenderer, ( SCREEN_WIDTH - gTextTexture.getWidth() ), ( SCREEN_HEIGHT - gTextTexture.getHeight() - gDateTexture.getHeight() ) );
        gDateTexture.loadFromRenderedText( gRenderer, gFont, getTime(), gTextColor );
        gDateTexture.render( gRenderer, ( SCREEN_WIDTH - gDateTexture.getWidth() ), ( SCREEN_HEIGHT - gDateTexture.getHeight() ) );

				//Update screen
				SDL_RenderPresent( gRenderer );
        frame++;
        if (frame % 60 == 0)
        {
          gCounter++;
          frame = 0;
        }
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}


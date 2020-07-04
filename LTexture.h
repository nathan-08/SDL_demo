#ifndef L_TEXTURE_H
#define L_TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include <cmath>

class LTexture
{
  public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile( SDL_Renderer* renderer, std::string path );

    //Creates image from font string
    bool loadFromRenderedText( SDL_Renderer* renderer, TTF_Font* font, std::string textureText, SDL_Color textColor );

    //Deallocates texture
    void free();

    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setAlpha( Uint8 alpha );
    void setBlendMode( SDL_BlendMode blending );

    //Renders texture at given point
    void render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image dimensions
    int getWidth();
    int getHeight();

  private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif

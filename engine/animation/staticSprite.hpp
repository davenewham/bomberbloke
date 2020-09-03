#ifndef STATICSPRITE_HPP
#define STATICSPRITE_HPP
#include "AbstractSpriteHandler.hpp"
#include "SDL2/SDL_image.h"
#include "engine.hpp"

extern SDL_Renderer *_renderer;
SDL_Texture* get_sprite(std::string);

class staticSprite : public AbstractSpriteHandler{
public:
  staticSprite(double xpos, double ypos, double xdim, double ydim, std::string asset_name)
    : AbstractSpriteHandler(xpos, ypos, xdim, ydim){
      mpSprite = get_sprite(asset_name);
      return;
    }

    void draw(Camera *cam){
      SDL_Rect dstrect = cam->getScreenRect(mPosition[0], mPosition[1], mDimmension[0], mDimmension[1]);
      cam->displayTexture(mpSprite, nullptr, &dstrect);

      return;
    }

    ~staticSprite(){return;}

    SDL_Texture *mpSprite;
  };
#endif

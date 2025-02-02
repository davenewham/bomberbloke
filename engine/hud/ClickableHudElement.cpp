#include "ClickableHudElement.hpp"

#include <SDL2/SDL.h>

ClickableHudElement::ClickableHudElement(int xPos,
                                         int yPos,
                                         int xDim,
                                         int yDim,
                                         std::function<void()> onClickFn,
                                         AlignFlag xAlignFlag,
                                         AlignFlag yAlignFlag)
  : AbstractHudElement(xPos, yPos, xDim, yDim, xAlignFlag, yAlignFlag)
{
  // Base class constructor must be called
  mOnClickFn = onClickFn;

  // Set to be interactive so that onInput is called by scene
  mIsInteractive = true;
}

bool
ClickableHudElement::isCoordOnElement(int x, int y)
{
  if (x >= mPosition[0] && x < mPosition[0] + mDimensions[0]) {
    if (y >= mPosition[1] && y < mPosition[1] + mDimensions[1])
      return true;
  }
  return false;
}

void
ClickableHudElement::onInput(SDL_Event* event)
{
  if (!mIsInteractive)
    return;

  // If its a mouse button up event, it cannot be clicked
  if (event->type == SDL_MOUSEBUTTONUP) {
    if (mIsClicked) {
      mIsClicked = false;
      mPropertiesUpdated = true;
      onClick(event->button.x, event->button.y);
    }
  } else if (event->type == SDL_MOUSEBUTTONDOWN) {
    // If it is a mouse button down event and the cursor is on the button
    // it must be clicked and the mouse must be over it
    if (isCoordOnElement(event->button.x, event->button.y)) {
      mIsMouseOver = true;
      mIsClicked = true;
      mPropertiesUpdated = true;
    }
  } else if (event->type == SDL_MOUSEMOTION) {
    // If it is a mouse motion event check if the cursor is on the button
    bool newIsMouseOver = isCoordOnElement(event->motion.x, event->motion.y);
    // Check if IsMouseOver has changed
    if (newIsMouseOver != mIsMouseOver) {
      mIsMouseOver = newIsMouseOver;
      mPropertiesUpdated = true;
    }
  }
}

void
ClickableHudElement::onClick(int, int)
{
  if (mOnClickFn != nullptr)
    mOnClickFn();
}

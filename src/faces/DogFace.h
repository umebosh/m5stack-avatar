// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include <M5Stack.h> // TODO: include only the Sprite function not a whole library
#include "../Drawable.h"
#include "../BoundingRect.h"
#include "../DrawContext.h"

namespace m5avatar
{
  class DogEye : public Drawable
  {
    void draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *ctx)
    {
      uint32_t cx = rect.getCenterX();
      uint32_t cy = rect.getCenterY();
      Gaze g = ctx->getGaze();
      ColorPalette cp = ctx->getColorPalette();
      uint32_t offsetX = g.getHorizontal() * 8;
      uint32_t offsetY = g.getVertical() * 5;
      float eor = ctx->getEyeOpenRatio();

      if (eor == 0)
      {
        // eye closed
        spi->fillRect(cx - 15, cy - 2, 30, 4, cp.get(COLOR_PRIMARY));
        return;
      }
      spi->fillEllipse(cx, cy, 30, 25, cp.get(COLOR_PRIMARY));
      spi->fillEllipse(cx, cy, 28, 23, cp.get(COLOR_BACKGROUND));

      spi->fillEllipse(cx + offsetX, cy + offsetY, 18, 18, cp.get(COLOR_PRIMARY));
      spi->fillEllipse(cx + offsetX - 3, cy + offsetY - 3, 3, 3, cp.get(COLOR_BACKGROUND));
    }
  };

  class DogMouth : public Drawable
  {
  private:
    uint16_t minWidth;
    uint16_t maxWidth;
    uint16_t minHeight;
    uint16_t maxHeight;

  public:
    DogMouth()
    : DogMouth(50, 90, 4, 60)
    {}
    DogMouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight, uint16_t maxHeight)
    : minWidth{minWidth}, maxWidth{maxWidth}, minHeight{minHeight}, maxHeight{maxHeight}
    {}
    void draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *ctx)
    {
      ColorPalette cp = ctx->getColorPalette();
      uint32_t primaryColor = ctx->getColorPalette().get(COLOR_PRIMARY);
      uint32_t backgroundColor = ctx->getColorPalette().get(COLOR_BACKGROUND);
      uint32_t cx = rect.getCenterX();
      uint32_t cy = rect.getCenterY();
      float breath = min(1.0f, ctx->getBreath());
      float openRatio = ctx->getMouthOpenRatio();
      uint32_t h = minHeight + (maxHeight - minHeight) * openRatio;
      uint32_t w = minWidth + (maxWidth - minWidth) * (1 - openRatio);
      if (h > minHeight)
      {
        spi->fillEllipse(cx, cy, w / 2, h / 2, primaryColor);
        spi->fillEllipse(cx, cy, w / 2 - 4, h / 2 - 4, TFT_RED);
        spi->fillRect(cx - w / 2, cy - h / 2, w, h / 2, backgroundColor);
      }
      spi->fillEllipse(cx, cy - 15, 10, 6, primaryColor);
      spi->fillEllipse(cx - 28, cy, 30, 15, primaryColor);
      spi->fillEllipse(cx + 28, cy, 30, 15, primaryColor);
      spi->fillEllipse(cx - 29, cy - 4, 27, 15, backgroundColor);
      spi->fillEllipse(cx + 29, cy - 4, 27, 15, backgroundColor);
    }
  };

  class DogFace : public Face
  {
  public:
    DogFace()
        : Face(new DogMouth(),
               new BoundingRect(168, 163),
               new DogEye(),
               new BoundingRect(103, 80),
               new DogEye(),
               new BoundingRect(106, 240),
               new Eyeblow(15, 2, false),
               new BoundingRect(67, 96),
               new Eyeblow(15, 2, true),
               new BoundingRect(72, 230))
    {
    }
  };

  } // namespace m5avatar
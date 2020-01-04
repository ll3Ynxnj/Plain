#ifndef PLARENDERER_HPP
#define PLARENDERER_HPP

#include "PLARenderingData.hpp"

class PLARenderer
{
public:
  PLARenderer();
  virtual ~PLARenderer();

  void Render();

  virtual void SetScreenSize(int w, int h) const = 0;

protected:
  virtual void DrawRect(const PLARDRect *aRect) const = 0;
};

#endif

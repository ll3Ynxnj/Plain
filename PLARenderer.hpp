#ifndef PLARENDERER_HPP
#define PLARENDERER_HPP

#include "PLARDRect.hpp"
#include "PLARDCircle.hpp"

class PLARenderer
{
public:
  PLARenderer();
  virtual ~PLARenderer();

  void Render();

  virtual void SetScreenSize(int w, int h) const = 0;

protected:
  virtual void Clear() const = 0;
  virtual void Flush() const = 0;
  virtual void DrawDemo() const = 0;
  virtual void DrawRect(const PLARDRect *aRect) const = 0;
  virtual void DrawCircle(const PLARDCircle *aCircle) const = 0;
};

#endif

#ifndef RENDERER_H
#define RENDERER_H

#include "plot.h"
#include "image.h"

class Renderer {
private:
  // it's convenient to have these as fields, to avoid the need
  // to pass them explicitly to helper functions
  const Plot &m_plot;
  Image *m_img;

  // value semantics prohibited
  Renderer(const Renderer &);
  Renderer &operator=(const Renderer &);

public:
  Renderer(const Plot &plot);
  ~Renderer();

  Image *render();

private:
  // TODO: add private helper functions
};

#endif // RENDERER_H

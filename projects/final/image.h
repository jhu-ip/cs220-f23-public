#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <iostream>
#include "color.h"

class Image {
private:
  int m_width, m_height;
  Color *m_pixels;

  // value semantics are prohibited
  Image(const Image &);
  Image &operator=(const Image &);

public:
  Image(int width, int height);
  ~Image();

  int get_width() const { return m_width; }
  int get_height() const { return m_height; }

  // TODO: add member function to access pixel Color data

  void write_png(std::ostream &out);
};

#endif // IMAGE_H

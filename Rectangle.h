#pragma once

#include <cairo/cairo.h>
#include "debug.h"
#ifdef CWDEBUG
#include "utils/has_print_on.h"
#endif

namespace cairowindow {
// This class defines a print_on method.
using utils::has_print_on::operator<<;

class Rectangle
{
 private:
  cairo_rectangle_t geometry_;

 public:
  Rectangle() : geometry_{} { }
  Rectangle(double offset_x, double offset_y, double width, double height) : geometry_{offset_x, offset_y, width, height} { }

  double offset_x() const { return geometry_.x; }
  double offset_y() const { return geometry_.y; }
  double width() const { return geometry_.width; }
  double height() const { return geometry_.height; }

  bool is_defined() const { return geometry_.width > 0.0 && geometry_.height > 0.0; }

  double area() const { ASSERT(is_defined()); return geometry_.width * geometry_.height; }

#ifdef CWDEBUG
  void print_on(std::ostream& os) const
  {
    os << '{' << geometry_.x << ", " << geometry_.y << ", " << geometry_.width << ", " << geometry_.height << '}';
  }
#endif
};

} // namespace cairowindow

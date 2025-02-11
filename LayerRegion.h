#pragma once

#include "Rectangle.h"
#include "StrokeExtents.h"
#include <cairo/cairo.h>
#include <functional>

namespace cairowindow {

class Layer;

class LayerRegion
{
 private:
  Layer* layer_;                                // The Layer that this is a region of. Drawing happens to the surface of this layer.
  StrokeExtents stroke_extents_;                // The region area (as returned by draw).
  std::function<StrokeExtents(cairo_t*)> draw_; // A copy the argument of draw; used to redraw the region when necessary.

 private:
  virtual StrokeExtents do_draw(cairo_t* cr) { Dout(dc::warning, "Calling unimplemented do_draw()"); return {}; }

 public:
  LayerRegion() : layer_(nullptr) { }
  ~LayerRegion();

  void draw(Layer* layer);
  void draw(Layer* layer, std::function<StrokeExtents(cairo_t*)> user_draw)
  {
    draw_ = user_draw;
    draw(layer);
  }

  StrokeExtents redraw(cairo_t* cr)
  {
    DoutEntering(dc::notice, "LayerRegion::redraw(cr) [" << this << "]");

    if (draw_)
      return draw_(cr);

    return do_draw(cr);
  }

  StrokeExtents const& stroke_extents() const { return stroke_extents_; }
};

} // namespace cairowindow

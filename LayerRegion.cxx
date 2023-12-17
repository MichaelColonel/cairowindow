#include "sys.h"
#include "LayerRegion.h"
#include "Layer.h"
#include "debug.h"

namespace cairowindow {

void LayerRegion::draw()
{
  cairo_t* cr = layer_->cr();
  cairo_save(cr);
  // Apply layer offset, if any.
  cairo_translate(cr, -layer_->offset_x(), -layer_->offset_y());

  // For now only a single user_draw() call per region is allowed.
  // The reason for this is that a region is supposed to a single rectangle, so doing
  // multiple draw calls could accidently cause large rectangles with a lot of empty space.
  ASSERT(!rectangle_.is_defined());
  // Call the drawing function of the user.
  rectangle_ = redraw(cr);

  cairo_restore(cr);
  layer_->add_area(rectangle_.area());
  layer_->window_update(rectangle_);
}

} // namespace cairowindow

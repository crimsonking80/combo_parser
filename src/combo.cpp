#include "combo.hpp"

#include "card.hpp"

Color Combo::color_identity() const
{
  Color color;

  for(cards_t::const_iterator it = cards_.begin(); it != cards_.end(); ++it)
    color += (*it)->color_identity();

  return color;
}

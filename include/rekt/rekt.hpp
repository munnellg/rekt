#ifndef REKT_REKT_HPP
#define REKT_REKT_HPP

#include <rekt/rectangle.hpp>
#include <rekt/io.hpp>

namespace rekt {
	std::vector<Rectangle> compute_overlapping_rectangles(std::vector<Rectangle> &rects);
}

#endif
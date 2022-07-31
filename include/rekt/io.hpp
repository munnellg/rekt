#ifndef REKT_IO_HPP
#define REKT_IO_HPP

#include <istream>
#include <ostream>
#include <rekt/rectangle.hpp>
#include <vector>

namespace rekt {
	namespace io {
		std::vector<Rectangle> deserialize_rects(std::string const &str);
		std::vector<Rectangle> deserialize_rects(std::istream &in);
		Rectangle deserialize_rect(std::string const &str);
		Rectangle deserialize_rect(std::istream &in);

		void serialize_rects(std::vector<Rectangle> const &rects, std::ostream &out);
		void serialize_rect(Rectangle const &rect, std::ostream &out);
	}
}


#endif
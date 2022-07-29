#ifndef REKT_RECTANGLE_HPP
#define REKT_RECTANGLE_HPP

#include <optional>

namespace rekt {

class Rectangle {

public:
	int x, y, w, h;

	Rectangle();
	Rectangle(int x, int y, int w, int h);

	bool intersects(Rectangle const &rect) const;
	std::optional<Rectangle> intersect(Rectangle const &rect) const;

	bool operator ==(Rectangle const &rect) const;
	bool operator !=(Rectangle const &rect) const;
};

}
#endif
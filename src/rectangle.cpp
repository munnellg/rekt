#include <rekt/rectangle.hpp>

namespace rekt {

Rectangle::Rectangle() : x(0), y(0), w(0), h(0) {
}

Rectangle::Rectangle(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {
}

bool Rectangle::intersects(Rectangle const &rect) const {
	return false;
}

std::optional<Rectangle> Rectangle::intersect(Rectangle const &rect) const {
	if (!this->intersects(rect)) {
		return {};
	}

	std::optional<Rectangle> r;
	return r;
}

bool Rectangle::operator ==(Rectangle const &rect) const {
	if (this->x != rect.x) { return false; }
	if (this->y != rect.y) { return false; }
	if (this->w != rect.w) { return false; }
	if (this->h != rect.h) { return false; }
	return true;
}

bool Rectangle::operator !=(Rectangle const &rect) const {
	return !(*this == rect);
}

}
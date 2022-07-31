#include <rekt/rectangle.hpp>

#include <vector>
#include <iostream>
#include <istream>
#include <limits>

namespace rekt {
	// ===========================================================
	// constructors
	// ===========================================================

	Rectangle::Rectangle(int x, int y, int w, int h) :
			m_pos_x(x),
			m_pos_y(y),
			m_width(w),
			m_height(h) {
		validate();
	}

	Rectangle::Rectangle(Rectangle const &rect) :
			m_pos_x(rect.m_pos_x),
			m_pos_y(rect.m_pos_y),
			m_width(rect.m_width),
			m_height(rect.m_height) {
		validate();
	}

	// ===========================================================
	// public methods
	// ===========================================================

	int Rectangle::x() const {
		return m_pos_x;
	}

	void Rectangle::x(int const x) {
		m_pos_x = x;
	}

	int Rectangle::y() const {
		return m_pos_y;
	}

	void Rectangle::y(int const y) {
		m_pos_y = y;
	}

	int Rectangle::w() const {
		return m_width;
	}

	void Rectangle::w(int const w) {
		validate_width(w);
		m_width = w;
	}

	int Rectangle::h() const {
		return m_height;
	}

	void Rectangle::h(int const h) {
		validate_height(h);
		m_height = h;
	}

	bool Rectangle::intersects(Rectangle const &rect) const {
		if ((std::numeric_limits<int>::max() - m_width < m_pos_x) ||
				(std::numeric_limits<int>::max() - rect.m_width < rect.m_pos_x) ||
				(std::numeric_limits<int>::max() - m_height < m_pos_y) ||
				(std::numeric_limits<int>::max() - m_height < rect.m_pos_y)) {

			throw "integer overflow detected when checking if rectangles intersect";
		}

		if (m_pos_x > (rect.m_pos_x + rect.m_width) || rect.m_pos_x > (m_pos_x + m_width)) {
			return false;
		}

		if (m_pos_y > (rect.m_pos_y + rect.m_height) || rect.m_pos_y > (m_pos_y + m_height)) {
			return false;
		}

		return true;
	}

	std::optional<Rectangle> Rectangle::intersect(Rectangle const &rect) const {
		// first check if the two rectangles actually intersect
		if (!this->intersects(rect)) {
			return {};
		}

		// now compute the overlap between the two
		std::optional<Rectangle> r;
		return r;
	}

	bool Rectangle::operator ==(Rectangle const &rect) const {
		if (this->x() != rect.x()) { return false; }
		if (this->y() != rect.y()) { return false; }
		if (this->w() != rect.w()) { return false; }
		if (this->h() != rect.h()) { return false; }
		return true;
	}

	bool Rectangle::operator !=(Rectangle const &rect) const {
		return !(*this == rect);
	}

	// ===========================================================
	// private methods
	// ===========================================================

	void Rectangle::validate() const {
		validate_width(m_width);
		validate_height(m_height);
	}

	void Rectangle::validate_height(int const height) const {
		if (height < 0) {
			throw "Rectangle cannot have negative height";
		}
	}

	void Rectangle::validate_width(int const width) const {
		if (width < 0) {
			throw "Rectangle cannot have negative width";
		}
	}
}


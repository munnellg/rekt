#ifndef REKT_RECTANGLE_HPP
#define REKT_RECTANGLE_HPP

#include <istream>
#include <optional>
#include <string>
#include <vector>

namespace rekt {
	class Rectangle {

	public:

		Rectangle() = default;
		Rectangle(int const x, int const y, int const w, int const h);
		Rectangle(Rectangle const &rect);

		int x() const;
		void x(int const x);

		int y() const;
		void y(int const y);

		int w() const;
		void w(int const w);

		int h() const;
		void h(int const h);

		bool intersects(Rectangle const &rect) const;
		std::optional<Rectangle> intersect(Rectangle const &rect) const;

		bool operator ==(Rectangle const &rect) const;
		bool operator !=(Rectangle const &rect) const;

	private:
		int m_pos_x;
		int m_pos_y;
		int m_width;
		int m_height;

		void validate() const;
		void validate_height(int const height) const;
		void validate_width(int const width) const;
	};
}
#endif
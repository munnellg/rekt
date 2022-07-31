#include <catch2/catch.hpp>
#include <limits>
#include <rekt/rekt.hpp>

TEST_CASE("Rectangle constructor throws on invalid width", "[rectangle]") {
	REQUIRE_THROWS_WITH(rekt::Rectangle(0, 0, -10, 10), "Rectangle cannot have negative width");
}

TEST_CASE("Rectangle constructor throws on invalid height", "[rectangle]") {
	REQUIRE_THROWS_WITH(rekt::Rectangle(0, 0, 10, -10), "Rectangle cannot have negative height");
}

TEST_CASE("Rectangle detect intersection", "[rectangle]") {
	rekt::Rectangle r1(10, 11, 2, 3);
	rekt::Rectangle r2(10, 11, 2, 3);

	REQUIRE(r1.intersects(r2));
	REQUIRE(r2.intersects(r1)); // check symmetry
}

TEST_CASE("Rectangle detect no intersection -- too far to one side", "[rectangle]") {
	rekt::Rectangle r1(10, 10, 1, 3);
	rekt::Rectangle r2(12, 10, 2, 1);

	REQUIRE_FALSE(r1.intersects(r2));
	REQUIRE_FALSE(r1.intersects(r2)); // check symmetry
}

TEST_CASE("Rectangle detect no intersection -- too far above/below", "[rectangle]") {
	rekt::Rectangle r1(10, 10, 1, 1);
	rekt::Rectangle r2(10, 12, 1, 1);

	REQUIRE_FALSE(r1.intersects(r2));
	REQUIRE_FALSE(r1.intersects(r2)); // check symmetry
}

TEST_CASE("Rectangle detect intersection touching sides", "[rectangle]") {
	rekt::Rectangle r1(10, 11, 1, 1);
	rekt::Rectangle r2(11, 10, 1, 1);

	REQUIRE(r1.intersects(r2));
	REQUIRE(r2.intersects(r1)); // check symmetry
}

TEST_CASE("Rectangle detect intersection touching top/bottom", "[rectangle]") {
	rekt::Rectangle r1(10, 10, 1, 1);
	rekt::Rectangle r2(10, 11, 1, 1);

	REQUIRE(r1.intersects(r2));
	REQUIRE(r2.intersects(r1)); // check symmetry
}

TEST_CASE("Rectangle detect intersection concentric rects", "[rectangle]") {
	rekt::Rectangle r1(10, 10, 10, 10);
	rekt::Rectangle r2(15, 15, 3, 3);

	REQUIRE(r1.intersects(r2));
	REQUIRE(r2.intersects(r1)); // check symmetry
}

TEST_CASE("Rectangle detect intersection zero area", "[rectangle]") {
	rekt::Rectangle r1(10, 11, 0, 0);
	rekt::Rectangle r2(10, 11, 0, 0);

	REQUIRE(r1.intersects(r2));
	REQUIRE(r2.intersects(r1)); // check symmetry
}

TEST_CASE("Rectangle detect intersection (negative coordinates)", "[rectangle]") {
	rekt::Rectangle r1(-10, -11, 2, 3);
	rekt::Rectangle r2(-10, -11, 2, 3);

	REQUIRE(r1.intersects(r2));
	REQUIRE(r2.intersects(r1)); // check symmetry
}

TEST_CASE("Rectangle detect no intersection -- too far to one side (negative coordinates)", "[rectangle]") {
	rekt::Rectangle r1(-10, -10, 5, 2);
	rekt::Rectangle r2(-12, -10, 1, 3);

	REQUIRE_FALSE(r1.intersects(r2));
	REQUIRE_FALSE(r1.intersects(r2)); // check symmetry
}

TEST_CASE("Rectangle detect no intersection -- too far above/below (negative coordinates)", "[rectangle]") {
	rekt::Rectangle r1(-10, -10, 1, 1);
	rekt::Rectangle r2(-10, -12, 1, 1);

	REQUIRE_FALSE(r1.intersects(r2));
	REQUIRE_FALSE(r1.intersects(r2)); // check symmetry
}

TEST_CASE("Rectangle detect intersection touching sides (negative coordinates)", "[rectangle]") {
	rekt::Rectangle r1(-10, -11, 1, 1);
	rekt::Rectangle r2(-11, -10, 1, 1);

	REQUIRE(r1.intersects(r2));
	REQUIRE(r2.intersects(r1)); // check symmetry
}

TEST_CASE("Rectangle detect intersection touching top/bottom (negative coordinates)", "[rectangle]") {
	rekt::Rectangle r1(-10, -10, 1, 1);
	rekt::Rectangle r2(-10, -11, 1, 1);

	REQUIRE(r1.intersects(r2));
	REQUIRE(r2.intersects(r1)); // check symmetry
}

TEST_CASE("Rectangle detect intersection concentric rects (negative coordinates)", "[rectangle]") {
	rekt::Rectangle r1(-10, -10, 10, 10);
	rekt::Rectangle r2(-5, -5, 3, 3);

	REQUIRE(r1.intersects(r2));
	REQUIRE(r2.intersects(r1)); // check symmetry
}

TEST_CASE("Rectangle detect intersection zero area (negative coordinates)", "[rectangle]") {
	rekt::Rectangle r1(-10, -11, 0, 0);
	rekt::Rectangle r2(-10, -11, 0, 0);

	REQUIRE(r1.intersects(r2));
	REQUIRE(r2.intersects(r1)); // check symmetry
}

TEST_CASE("Rectangle detect integer overflow on x-axis when computing intersection", "[rectangle]") {
	rekt::Rectangle r1(std::numeric_limits<int>::max() - 10, -11, 11, 20);
	rekt::Rectangle r2(-10, -11, 100, 50);

	REQUIRE_THROWS_WITH(r1.intersects(r2), "integer overflow detected when checking if rectangles intersect");
	REQUIRE_THROWS_WITH(r2.intersects(r1), "integer overflow detected when checking if rectangles intersect"); // check symmetry
}

TEST_CASE("Rectangle detect integer overflow on y-axis when computing intersection", "[rectangle]") {
	rekt::Rectangle r1(-10, std::numeric_limits<int>::max() - 11, 11, 30);
	rekt::Rectangle r2(-10, -11, 40, 50);

	REQUIRE_THROWS_WITH(r1.intersects(r2), "integer overflow detected when checking if rectangles intersect");
	REQUIRE_THROWS_WITH(r2.intersects(r1), "integer overflow detected when checking if rectangles intersect"); // check symmetry
}

TEST_CASE("Rectangle equality operator", "[rectangle]") {
	rekt::Rectangle r1(0, 1, 2, 3);
	rekt::Rectangle r2(0, 1, 2, 3);

	REQUIRE(r1 == r2);

	r1.x(1);
	REQUIRE_FALSE(r1 == r2);

	r1.x(0); r1.y(0);
	REQUIRE_FALSE(r1 == r2);

	r1.y(1); r1.w(0);
	REQUIRE_FALSE(r1 == r2);

	r1.w(2); r1.h(0);
	REQUIRE_FALSE(r1 == r2);
}

TEST_CASE("Rectangle inequality operator", "[rectangle]") {
	rekt::Rectangle r1(0, 1, 2, 3);
	rekt::Rectangle r2(0, 1, 2, 3);

	REQUIRE_FALSE(r1 != r2);

	r1.x(1);
	REQUIRE(r1 != r2);

	r1.x(0); r1.y(0);
	REQUIRE(r1 != r2);

	r1.y(1); r1.w(0);
	REQUIRE(r1 != r2);

	r1.w(2); r1.h(0);
	REQUIRE(r1 != r2);
}

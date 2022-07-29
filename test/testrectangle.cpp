#include <catch2/catch.hpp>
#include <rekt/rectangle.hpp>

TEST_CASE("Rectangle equality operator", "[rectangle]") {
	rekt::Rectangle r1(0, 1, 2, 3);
	rekt::Rectangle r2(0, 1, 2, 3);

	REQUIRE(r1 == r2);

	r1.x = 1;
	REQUIRE_FALSE(r1 == r2);

	r1.x = 0; r1.y = 0;
	REQUIRE_FALSE(r1 == r2);

	r1.y = 1; r1.w = 0;
	REQUIRE_FALSE(r1 == r2);

	r1.w = 2; r1.h = 0;
	REQUIRE_FALSE(r1 == r2);
}

TEST_CASE("Rectangle inequality operator", "[rectangle]") {
	rekt::Rectangle r1(0, 1, 2, 3);
	rekt::Rectangle r2(0, 1, 2, 3);

	REQUIRE_FALSE(r1 != r2);

	r1.x = 1;
	REQUIRE(r1 != r2);

	r1.x = 0; r1.y = 0;
	REQUIRE(r1 != r2);

	r1.y = 1; r1.w = 0;
	REQUIRE(r1 != r2);

	r1.w = 2; r1.h = 0;
	REQUIRE(r1 != r2);
}
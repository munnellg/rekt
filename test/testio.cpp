#include <catch2/catch.hpp>
#include <rekt/rekt.hpp>
#include <string>
#include <sstream>

TEST_CASE("Test deserialize JSON valid input", "[io][deserialize_rects]") {
	std::string json_str = "{ \"rects\": [ \
			{ \"x\": 100, \"y\": 100, \"w\": 250, \"h\": 80 },  \
			{ \"x\": 120, \"y\": 200, \"w\": 250, \"h\": 150 }, \
			{ \"x\": 140, \"y\": 160, \"w\": 250, \"h\": 100 }, \
			{ \"x\": 160, \"y\": 140, \"w\": 350, \"h\": 190 }  \
		] \
	}";

	std::vector<rekt::Rectangle> expected = {
		rekt::Rectangle(100, 100, 250, 80),
		rekt::Rectangle(120, 200, 250, 150),
		rekt::Rectangle(140, 160, 250, 100),
		rekt::Rectangle(160, 140, 350, 190)
	};

	REQUIRE(rekt::io::deserialize_rects(json_str) == expected);

	// repeat the test for istream input
	std::istringstream json_stream(json_str);
	REQUIRE(rekt::io::deserialize_rects(json_stream) == expected);
}

TEST_CASE("Test deserialize JSON empty object", "[io][deserialize_rects]") {
	std::string json_str = "{}";
	std::vector<rekt::Rectangle> expected = {};

	REQUIRE(rekt::io::deserialize_rects(json_str) == expected);

	// repeat the test for istream input
	std::istringstream json_stream(json_str);
	REQUIRE(rekt::io::deserialize_rects(json_stream) == expected);
}

TEST_CASE("Test deserialize JSON empty \"rects\" list", "[io][deserialize_rects]") {
	std::string json_str = "{ \"rects\" : [] }";
	std::vector<rekt::Rectangle> expected = {};
	
	REQUIRE(rekt::io::deserialize_rects(json_str) == expected);

	// repeat the test for istream input
	std::istringstream json_stream(json_str);
	REQUIRE(rekt::io::deserialize_rects(json_stream) == expected);
}

TEST_CASE("Test deserialize JSON \"rects\" is not an array", "[io][deserialize_rects]") {
	std::string json_str = "{ \"rects\" : {} }";
	REQUIRE_THROWS_WITH(rekt::io::deserialize_rects(json_str), Catch::Matchers::Contains("type must be array"));

	// repeat the test for istream input
	std::istringstream json_stream(json_str);
	REQUIRE_THROWS_WITH(rekt::io::deserialize_rects(json_stream), Catch::Matchers::Contains("type must be array"));
}

TEST_CASE("Test deserialize JSON negative width", "[io][deserialize_rects]") {
	std::string json_str = "{ \"rects\": [ { \"x\": 100, \"y\": 100, \"w\": -250, \"h\": 80 } ] }";
	REQUIRE_THROWS_WITH(rekt::io::deserialize_rects(json_str), "Rectangle cannot have negative width");

	// repeat the test for istream input
	std::istringstream json_stream(json_str);
	REQUIRE_THROWS_WITH(rekt::io::deserialize_rects(json_stream), "Rectangle cannot have negative width");
}

TEST_CASE("Test deserialize JSON negative height", "[io][deserialize_rects]") {
	std::string json_str = "{ \"rects\": [ { \"x\": 100, \"y\": 100, \"w\": 250, \"h\": -80 } ] }";
	REQUIRE_THROWS_WITH(rekt::io::deserialize_rects(json_str), "Rectangle cannot have negative height");

	// repeat the test for istream input
	std::istringstream json_stream(json_str);
	REQUIRE_THROWS_WITH(rekt::io::deserialize_rects(json_stream), "Rectangle cannot have negative height");
}

TEST_CASE("Test deserialize JSON missing x attribute", "[io][deserialize_rects]") {
	std::string json_str = "{ \"rects\": [ { \"y\": 100, \"w\": 250, \"h\": -80 } ] }";
	REQUIRE_THROWS_WITH(rekt::io::deserialize_rects(json_str), Catch::Matchers::Contains("key 'x' not found"));

	// repeat the test for istream input
	std::istringstream json_stream(json_str);
	REQUIRE_THROWS_WITH(rekt::io::deserialize_rects(json_stream), Catch::Matchers::Contains("key 'x' not found"));
}

TEST_CASE("Test deserialize JSON missing y attribute", "[io][deserialize_rects]") {
	std::string json_str = "{ \"rects\": [ { \"x\": 100, \"w\": 250, \"h\": -80 } ] }";
	REQUIRE_THROWS_WITH(rekt::io::deserialize_rects(json_str), Catch::Matchers::Contains("key 'y' not found"));

	// repeat the test for istream input
	std::istringstream json_stream(json_str);
	REQUIRE_THROWS_WITH(rekt::io::deserialize_rects(json_stream), Catch::Matchers::Contains("key 'y' not found"));
}

TEST_CASE("Test deserialize JSON missing w attribute", "[io][deserialize_rects]") {
	std::string json_str = "{ \"rects\": [ { \"x\": 100, \"y\": 100, \"h\": -80 } ] }";
	REQUIRE_THROWS_WITH(rekt::io::deserialize_rects(json_str), Catch::Matchers::Contains("key 'w' not found"));

	// repeat the test for istream input
	std::istringstream json_stream(json_str);
	REQUIRE_THROWS_WITH(rekt::io::deserialize_rects(json_stream), Catch::Matchers::Contains("key 'w' not found"));
}

TEST_CASE("Test deserialize JSON missing h attribute", "[io][deserialize_rects]") {
	std::string json_str = "{ \"rects\": [ { \"x\": 100, \"y\": 100, \"w\": 250 } ] }";
	REQUIRE_THROWS_WITH(rekt::io::deserialize_rects(json_str), Catch::Matchers::Contains("key 'h' not found"));

	// repeat the test for istream input
	std::istringstream json_stream(json_str);
	REQUIRE_THROWS_WITH(rekt::io::deserialize_rects(json_stream), Catch::Matchers::Contains("key 'h' not found"));
}
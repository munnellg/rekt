#include <nlohmann/json.hpp>
#include <rekt/io.hpp>

namespace rekt {
	
	// from_json and to_json required by nlohmann_json
	// must be defined in the same namespace as Rectangle 
	// see: https://github.com/nlohmann/json#arbitrary-types-conversions
	void to_json(nlohmann::json &json, Rectangle const &rect) {
		json = nlohmann::json{
			{ "x", rect.x() },
			{ "y", rect.y() },
			{ "w", rect.w() },
			{ "h", rect.h() }
		};
	}

	void from_json(nlohmann::json const &json, Rectangle &rect) {
		rect.x(json.at("x").get<int>());
		rect.y(json.at("y").get<int>());
		rect.w(json.at("w").get<int>());
		rect.h(json.at("h").get<int>());
	}

	namespace io {

		std::vector<Rectangle> deserialize_rects(std::istream &in) {
			nlohmann::json json = nlohmann::json::parse(in);

			if (!json.contains("rects")) {
				return {};
			}
			
			return  json["rects"].get<std::vector<Rectangle>>(); // implicitly calls `from_json`
		}

		std::vector<Rectangle> deserialize_rects(std::string const &str) {
			std::istringstream in(str);
			return deserialize_rects(in);
		}

		Rectangle deserialize_rect(std::istream &in) {
			nlohmann::json json = nlohmann::json::parse(in);	
			return  json.get<Rectangle>(); // implicitly calls `from_json`
		}

		Rectangle deserialize_rect(std::string const &str) {
			std::istringstream in(str);
			return deserialize_rect(in);
		}

		void serialize_rects(std::vector<Rectangle> const &rects, std::ostream &out) {
			nlohmann::json json;	
			json["rects"] = rects; // implicitly calls to_json
			out << json;
		}

		void serialize_rect(Rectangle const &rect, std::ostream &out) {	
			nlohmann::json json = rect; // implicitly calls `to_json`
			out << json;
		}
	}
}
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <rekt/rekt.hpp>
#include <string>
#include <vector>

std::string g_program_name;
std::vector<std::string> g_args;

unsigned int g_max_shapes = 1000;

template <typename... Args>
void quit_with_error(Args const &... args) {
	std::cerr << "ERROR: ";
	((std::cerr << args), ...);
	std::cerr << std::endl;
	
	exit(EXIT_FAILURE);
}

void usage() {
	std::cerr << "usage: " << g_program_name << " [options] FILE [FILE ...]" << std::endl;
	std::cerr << std::endl;
	std::cerr << "args:" << std::endl;
	std::cerr << "\tFILE\ta json file containing shape data" << std::endl;
	std::cerr << std::endl;
	std::cerr << "options:" << std::endl;
	std::cerr << "\t-h --help\tprint this help message and quit" << std::endl;
	std::cerr << "\t-M --max-shapes\tset the maximum number of shapes to be analyzed (default 1000)" << std::endl;
	
	exit(EXIT_SUCCESS);
}

template <typename T>
void parse_flag_with_arg(std::string const &flag, int const argc, char **argv, int &i, T &dst) {
	if (++i >= argc) {
		quit_with_error(flag, " expects argument");
	}

	std::istringstream ss(argv[i]);
	ss >> dst;
	
	if (ss.fail()) {
		quit_with_error(argv[i], " is not a valid argument for ", flag);
	}
}

void parse_args(int const argc, char **argv) {
	g_program_name = argv[0];

	for (int i = 1; i < argc; i++) {
		std::string arg_str(argv[i]);

		// check if arg is a flag
		if (arg_str.rfind("-", 0) == 0) {

			// if arg is a flag, decode it and configure application as appropriate
			if ("-h" == arg_str || "--help" == arg_str) {
				usage();
			} if ("-M" == arg_str || "--max-shapes") {
				parse_flag_with_arg(arg_str, argc, argv, i, g_max_shapes);
			} else {
				quit_with_error("Unknown option \"", arg_str, "\"");
			}
		} else {
			// if arg is not a flag, assume it is an input file
			g_args.push_back(arg_str);
		}
	}
}

void process_shape_file(std::string filename) {
	std::cerr << "Processing \"" << filename << "\"" << std::endl;

	std::ifstream in(filename);

	if (!in.is_open()) {
		std::cerr << "Unable to open \"" << filename << "\"" << std::endl;
		return;
	}

	std::vector<rekt::Rectangle> rects = rekt::io::deserialize_rects(in);
	
	if (rects.size() > g_max_shapes) {
		rects.resize(g_max_shapes);
	}

	std::cout << "Input:" << std::endl;

	for (size_t i = 0; i < rects.size(); i++) {
		std::cout << std::setw(4) << i + 1 << ": Rectangle at (" << rects[i].x() << ", " << rects[i].y() << "), w=" << rects[i].w() << ", h=" << rects[i].y() << "." << std::endl;
	}

	// compute intersections

	in.close();
}

int main(int argc, char **argv) {	
	parse_args(argc, argv);

	if (g_args.size() <= 0) {
		quit_with_error("Program expects shapefile as input. Rerun with -h flag for usage information");
	}

	std::for_each(g_args.begin(), g_args.end(), [](std::string const &filename) {
		process_shape_file(filename);
	});

	return 0;
}
#include "rektapp.hpp"

#include <iostream>

namespace rekt {

void RektApp::parse_args(int argc, char **argv) {

}

int RektApp::run(int argc, char **argv) {
	RektApp::parse_args(argc, argv);
	return 0;	
}

}

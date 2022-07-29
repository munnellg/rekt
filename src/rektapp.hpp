#ifndef REKT_REKTAPP_HPP
#define REKT_REKTAPP_HPP

namespace rekt {

class RektApp {
private:
	static void parse_args(int argc, char **argv);

public:
	static int run(int argc, char **argv);
};

}

#endif
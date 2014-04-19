#include "reader.h"
#include <iostream>

int main(int argc,char** argv) {
	ConfReader test;
	std::cout << "reading file" << std::endl;
	test.init("example.ini");
	section_map * tim_awesome(test.get_section("tim.awesome"));
	
	std::cout << "awesome level = " << tim_awesome->at("awesome_level") << std::endl;
	std::cout << "odd string = " << tim_awesome->at("odd_string") << std::endl;
	std::cout << "boobs = " << tim_awesome->at("boobs") << std::endl;
	std::cout << "winar loc = " << tim_awesome->at("winar_exe") << std::endl;
	std::cout << "folder loc = " << tim_awesome->at("folder_loc") << std::endl;
	std::cin.get();

	return 0;
}

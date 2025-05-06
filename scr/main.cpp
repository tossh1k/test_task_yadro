#include <iostream>
#include "decl.h"

int main(int argc, char* argv[])
{
	if (argc != 2) {
		std::cout << "Invalid argument." << '\n';
		return 1;
	}
	
	std::string file = argv[1];
	
    try { 
        validating(file); 
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << '\n';
        return 1;
    }
    Club club;
    club.Parse(file);
    return 0;
}

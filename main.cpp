//-----------------> by Web-Void(Sakair)
//                                      Void
//github: Sanctuc

#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <string>

#include "init_repository.hpp"
#include "profile.hpp"

#define red_color "\x1B[31m \033[0m"
#define green_color "\x1B[32m \033[0m"
#define yellow_color "\x1B[33m \033[0m"
#define blue_color "\x1B[34m \033[0m"
#define purple_color "\x1B[35m \033[0m"

std::string error_0x0 = "\x1B[31mRepository initialization error.\033[0m";

int out;


void help_menu(void)
{
    std::cout << "If you want to initialize the repository --> [\x1B[33mvoid init\033[0m]\n" <<
    "If you want to see the profile --> [\x1B[33mvoid profile\033[0m]\n" <<
    "If you want to create a profile --> [\x1B[33mvoid --create_profile\033[0m]"
    << std::endl;
}


int main(int argc, char const *argv[])
{
    if(argc < 2) {
        std::cout << "Usage: \x1B[33mvoid --help\033[0m\n";
        return 1;
    }
    
    std::string init_arg = argv[1];

    if (init_arg.compare("init") == 0) out = init_repository();
    else if (init_arg.compare("--help") == 0) help_menu();
    else if (init_arg.compare("profile") == 0) std::cout << "okey";
    else if (init_arg.compare("--create_profile") == 0) create_profile();
    if (out != 0){ std::cout << error_0x0 << std::endl; return 0;}
    
}
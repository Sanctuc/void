#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <fstream>


int create_profile()
{
    std::string name_user;
    std::string email;

    std::cout << "To create a profile, enter a name: ";
    std::cin >> name_user;
    std::cout << "Enter a email: ";
    std::cin >> email;


    std::string name_file = "config/user_" + name_user + ".txt";

    std::ofstream file;
    file.open(name_file);

    if (file.is_open())
    {
        file << "User: "<< name_user << " " << email << std::endl;
    }
    
    file.close();
    return 0;
}
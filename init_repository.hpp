#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <fstream>
#include <filesystem>

int init_repository(void)
{
    auto result = std::filesystem::create_directory(".void");
    if(result == false){
        std::cout << "\x1B[34mThe repository has already been initialized\033[0m" << std::endl;
        return 0;
    }
    
    //for windows
    system("attrib +h .void");

    std::filesystem::create_directory(".void/logs");
    std::filesystem::create_directory(".void/objects");
    std::filesystem::create_directory(".void/config");


    std::ifstream file;

    std::string line;

    file.open("config/user_Sania.txt");

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::cout << line << std::endl;
        }
    }
    else 
    {
        std::cout << "\x1B[31mFailed to open file\033[0m" << std::endl;
        return 0;
    }
    file.close();


    try {
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::cout << "Current working directory: " << currentPath << std::endl;
        
        std::ofstream f;
        f.open(".void/config/config.txt");

        if (f.is_open())
        {
            f << "Creater\n" << line << "\n" << "Name Project: " << currentPath;
        f.close();
        std::cout << "\x1B[32mThe repository is initialized\033[0m" << std::endl;
        }
    } 
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: "<< e.what() << std::endl;
    }

    return 0;
}
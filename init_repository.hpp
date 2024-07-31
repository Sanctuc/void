#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>


std::string name_user;
std::string email;

// Split function
std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    for (char ch : str) {
        if (ch == delimiter) {
            if (!token.empty()) {
                tokens.push_back(token);
            }
            token.clear();
        } else {
            token += ch;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}


void create_profile()
{				
				std::cout << "To create a profile, enter a name: ";
				std::cin >> name_user;
				std::cout << "Enter a email: ";
				std::cin >> email;
}


int init_repository(void)
{
  create_profile();
  auto result = std::filesystem::create_directory(".void");
if (!result) {
    std::cout << "\x1B[34mThe repository has already been initialized\033[0m" << std::endl;
    return 0;
}

// Создание директорий
std::filesystem::create_directory(".void/logs");
std::filesystem::create_directory(".void/objects");
std::filesystem::create_directory(".void/config");

// Запись в файл config.txt
try {
    std::filesystem::path currentPath = std::filesystem::current_path();
		std::ofstream file(".void/logs/path.txt");
		if(file.is_open()) {
				file << "Current working directory: " << currentPath << std::endl;
		}
    
		char delimiter = '/';
    std::vector<std::string> words = split(currentPath, delimiter);
		std::string name_project = words.back();
    

		std::ofstream f(".void/config/config.txt");
    if (f.is_open()) {
        f << "Creater: " << name_user << " Email: " << email << "\n" << "Name Project: " << name_project << "\nCommit: 0";
        f.close();
        std::cout << "\x1B[32mThe repository is initialized\033[0m" << std::endl;
    } else {
        std::cerr << "\x1B[31mFailed to create config.txt\033[0m" << std::endl;
    }
} catch (const std::filesystem::filesystem_error& e) {
    std::cerr << "Error: "<< e.what() << std::endl;
}

return 0;
 
}

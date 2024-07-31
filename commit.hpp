#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

// Функция для получения текущего количества коммитов
int getCommitCount(const std::string& configPath) {
    std::ifstream in(configPath);
    int commitCount = 0;
    std::string line;

    if (in.is_open()) {
        while (std::getline(in, line)) {
            if (line.find("Commit:") == 0) {
                commitCount++;
            }
        }
        in.close();
    }
    return commitCount;
}

// Функция для проверки изменений в файлах
bool filesChanged(const std::vector<std::string>& files, const std::string& folderPath) {
    namespace fs = std::filesystem;
    for (const auto& file : files) {
        std::ifstream inFile(file);
        if (inFile.is_open()) {
            std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
            inFile.close();

            fs::path outputPath = fs::path(folderPath) / "objects" / file;
            std::ifstream existingFile(outputPath);
            if (existingFile.is_open()) {
                std::string existingContent((std::istreambuf_iterator<char>(existingFile)), std::istreambuf_iterator<char>());
                existingFile.close();

                if (content != existingContent) {
                    return true;  // Файлы изменились
                }
            } else {
                return true;  // Новый файл
            }
        }
    }
    return false;  // Файлы не изменились
}

int commit() {
    namespace fs = std::filesystem;
    std::string folderPath = ".void";
    std::string configPath = folderPath + "/config/config.txt";

    // Проверяем, существует ли директория
    if (fs::exists(folderPath) && fs::is_directory(folderPath)) {
        std::cout << "Folder exists.\n";
    } else {
        std::cout << "Folder does not exist.\n";
        return 0;
    }

    // Получаем текущую директорию
    fs::path currentDir = fs::current_path();
    // Создаем вектор для хранения имен файлов
    std::vector<std::string> files;

    // Итерируемся по содержимому текущей директории
    for (const auto& entry : fs::directory_iterator(currentDir)) {
        if (entry.is_regular_file()) {
            // Если это обычный файл, добавляем его имя в вектор
            files.push_back(entry.path().filename().string());
        }
    }

    // Проверяем, изменились ли файлы
    if (!filesChanged(files, folderPath)) {
        std::cout << "No changes detected. Commit not needed.\n";
        return 0;
    }

    // Выводим и обрабатываем файлы
    std::cout << "Files in current directory:\n";
    for (const auto& file : files) {
        std::ifstream inFile(file);
        if (inFile.is_open()) {
            std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
            inFile.close();

            fs::path outputPath = fs::path(folderPath) / "objects" / file;
            std::ofstream outFile(outputPath);
            if (outFile.is_open()) {
                outFile << content;
                outFile.close();
            } else {
                std::cerr << "Failed to open file for writing: " << outputPath.string() << std::endl;
            }
        } else {
            std::cerr << "Failed to open input file: " << file << std::endl;
        }
    }

    // Получаем текущее количество коммитов
    int commitCount = getCommitCount(configPath);

    // Записываем новый коммит в config.txt
    std::ofstream out(configPath, std::ios::app);
    if (out.is_open()) {
        out << "Commit: " << (commitCount + 1) << std::endl;
        out.close();
    } else {
        std::cerr << "Failed to open config file for writing: " << configPath << std::endl;
    }	-

    return 0;
}


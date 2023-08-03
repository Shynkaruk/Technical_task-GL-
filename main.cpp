#include "file_search.h" // Підключаємо файл

int main() {
    std::string directory = "/path/to/your/directory"; 
    std::string filename = "file_to_find.txt"; 

    // Викликаємо функцію пошуку з статичної бібліотеки
    std::string foundFilePath = searchFileByName(directory, filename);

    if (!foundFilePath.empty()) {
        std::cout << "File found: " << foundFilePath << std::endl;
    }
    else {
        std::cout << "File not found." << std::endl;
    }

    return 0;
}
#include "utilities.h"
#include <iostream>
#include <map>

int main() {
    try {
        // Test file path
        std::string file_path = "test.txt";

        // Call occurrence_map function to get word occurrences
        std::map<std::string, int> word_occurrences = occurrence_map("test.txt");

        // Print the word occurrences
        std::cout << "Word occurrences:" << std::endl;
        for (const auto& pair : word_occurrences) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

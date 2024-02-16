#include "utilities.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

// Implementations of TypedArray functions...

TypedArray<TypedArray<double>> read_matrix_csv(const std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }

    TypedArray<TypedArray<double>> matrix;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        TypedArray<double> row;

        std::string value;
        while (std::getline(iss, value, ',')) {
            try {
                double val = std::stod(value);
                row.set(row.size(), val);
            } catch (...) {
                throw std::runtime_error("Invalid format in CSV file");
            }
        }

        matrix.set(matrix.size(), row);
    }

    return matrix;
}

void write_matrix_csv(TypedArray<TypedArray<double>> matrix, const std::string path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot create file");
    }

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.get(i).size(); ++j) {
            file << matrix.get(i).get(j);
            if (j < matrix.get(i).size() - 1) {
                file << ",";
            }
        }
        file << std::endl;
    }

    file.close();
}
std::map<std::string, int> occurrence_map(const std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }

    std::map<std::string, int> wordMap;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            // Remove punctuation
            word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
                return !std::isalnum(c) && c != '\'';
            }), word.end());

            // Convert to lowercase
            std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) {
                return std::tolower(c);
            });

            if (!word.empty()) {
                wordMap[word]++;
            }
        }
    }

    return wordMap;
}
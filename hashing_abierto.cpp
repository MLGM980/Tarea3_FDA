#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>

struct KeyValuePair {
    std::string key;
    std::string value;
};

class OpenAddressingHashTable {
private:
    std::vector<KeyValuePair> table;
    int size;

public:
    OpenAddressingHashTable(int tableSize) : size(tableSize) {
        table.resize(size);
    }

    void insert(const std::string& key, const std::string& value) {
        int index = hashFunction(key);

        while (!table[index].key.empty()) {
            index = (index + 1) % size;
        }

        table[index].key = key;
        table[index].value = value;
    }

    std::string search(const std::string& key) {
        int index = hashFunction(key);

        while (!table[index].key.empty()) {
            if (table[index].key == key) {
                return table[index].value;
            }
            index = (index + 1) % size;
        }

        return ""; // Elemento no encontrado
    }

    void loadCSV(const std::string& filename, int keyColumn, int valueColumn) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string line;
        std::getline(file, line); // Leer encabezados del CSV

        while (std::getline(file, line)) {
            std::string key, value;
            std::istringstream lineStream(line);
            std::string cell;
            int currentColumn = 0;

            while (std::getline(lineStream, cell, ';')) {
                if (currentColumn == keyColumn) {
                    key = cell;
                } else if (currentColumn == valueColumn) {
                    value = cell;
                }
                currentColumn++;
            }

            insert(key, value);
        }

        file.close();
    }

private:
    int hashFunction(const std::string& key) {
        // Implementación de una función hash básica
        int sum = 0;
        for (char ch : key) {
            sum += static_cast<int>(ch);
        }
        return sum % size;
    }
};
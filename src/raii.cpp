#include <iostream>
#include <fstream>
#include <memory>
#include <string>

// FileReader class to read a file
class FileReader {
public:
    FileReader(const std::string& filename) 
        : filePtr(std::make_unique<std::ifstream>(filename)) {
        if (!filePtr->is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }

    std::string read() {
        std::string content((std::istreambuf_iterator<char>(*filePtr)),
                             std::istreambuf_iterator<char>());
        return content;
    }

private:
    std::unique_ptr<std::ifstream> filePtr;
};

int main() {
    try {
        FileReader reader("example.utf8");
        std::string content = reader.read();
        std::cout << "File Content:\n" << content << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}

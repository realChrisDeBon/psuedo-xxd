#include <iostream>
#include <fstream>
#include <string>

int main() {

    std::string binaryFilePath, headerFilePath;
    std::cout << "Enter the binary file name: ";
    std::cin >> binaryFilePath;
    std::cout << "Enter the output header file name: ";
    std::cin >> headerFilePath;

    std::ifstream binaryFile(binaryFilePath, std::ios::binary);
    if (!binaryFile) {
        std::cerr << "Error opening binary file." << std::endl;
        return 1;
    }

    std::ofstream headerFile(headerFilePath + ".h");
    if (!headerFile) {
        std::cerr << "Error opening header file." << std::endl;
        return 1;
    }

    headerFile << "#pragma once\n\n";
    headerFile << "const unsigned char "<< headerFilePath << "[] = {\n";

    unsigned char byte;
    while (binaryFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        headerFile << "    0x" << std::hex << static_cast<int>(byte) << ",\n";
    }

    headerFile << "};\n";
    headerFile << "const unsigned int "<< headerFilePath << "_len = sizeof("<< headerFilePath << ");\n";

    std::cout << "Binary file converted to header: " << headerFilePath << std::endl;

    return 0;
}
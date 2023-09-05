#include <iostream>
#include <fstream>
#include <string>

std::string escapeChar(char c) {
    switch (c) {
        case '\\': return "\\\\";
        case '\'': return "\\\'";
        case '\"': return "\\\"";
        case '\t': return "\\t";
        case '\r': return "\\r";
        case '\n': return "\\n";
        default:
            if (c >= 32 && c <= 126) {
                return std::string(1, c);
            } else {
                return "\\" + std::to_string(static_cast<int>(c));
            }
    }
}
// psuedo XXD for converting text into C array headers
int main() {

    std::string inputFileName, outputFileName;
    std::cout << "Enter the existing text-based file name: ";
    std::cin >> inputFileName;
    std::cout << "Enter the output header file name: ";
    std::cin >> outputFileName;

    std::ifstream inputFile(inputFileName, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    std::ofstream outputFile(outputFileName + ".h"); // omit .h by preference
    if (!outputFile) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }
    
    outputFile << "#pragma once\n\n";
    outputFile << "const char " << outputFileName << "[] = {\n";

    for (char c : content) {
        outputFile << " '" << escapeChar(c) << "', ";
    }

    outputFile << "};\n";
    outputFile << "const unsigned int " << outputFileName << "_len = sizeof(" << outputFileName << ");\n";

    outputFile.close();

    std::cout << "Text-based file converted to header: " << outputFileName << std::endl;

    return 0;
}
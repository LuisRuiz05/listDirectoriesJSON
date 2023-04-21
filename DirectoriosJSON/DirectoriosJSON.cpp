#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <json/json.h>
#include <filesystem>

namespace fs = std::filesystem;

using namespace Json;

void generateJson(const std::string& directoryPath, const std::string& outputPath);
void generateJsonRecursively(const fs::path& dirPath, Value& jsonOutput);

int main(int argc, char* argv[]) {
    std::string directoryPath;
    std::string outputPath = "file.json";

    std::cout << "Type the directory's path: ";
    std::cin >> directoryPath;

    // Call function
    generateJson(directoryPath, outputPath);

    return 0;
}

void generateJson(const std::string& directoryPath, const std::string& outputPath) {
    // Convert the directory path to an fs::path object
    fs::path dirPath(directoryPath);

    if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
        std::cerr << "Error: " << directoryPath << " does not exist or is not a directory." << std::endl;
        return;
    }

    // Create a Json::Value object to store the JSON output
    Value jsonOutput;
    // Create a JSON array in the output object
    jsonOutput["files"] = Value(Json::arrayValue);

    // Call the recursive function to generate JSON for all files and subdirectories
    generateJsonRecursively(dirPath, jsonOutput);

    std::ofstream outputFile(outputPath);
    // Write the JSON to the output file
    if (outputFile.is_open()) {
        outputFile << jsonOutput;
        outputFile.close();
        std::cout << "JSON file generated successfully: " << outputPath << std::endl;
    }
    else {
        std::cerr << "Error: Failed to create JSON file." << std::endl;
    }
}

void generateJsonRecursively(const fs::path& dirPath, Value& jsonOutput) {
    for (const auto& entry : fs::directory_iterator(dirPath)) {
        if (fs::is_regular_file(entry.status())) {
            Value file;
            file["name"] = entry.path().filename().string();
            file["size"] = (Json::Int64)fs::file_size(entry.path());
            jsonOutput["files"].append(file);
        }
        else if (fs::is_directory(entry.status())) {
            // If the entry is a directory, recursively call this function to generate JSON for its contents
            Value subDirectory;
            subDirectory["name"] = entry.path().filename().string();
            subDirectory["files"] = Value(Json::arrayValue);
            generateJsonRecursively(entry.path(), subDirectory);
            jsonOutput["files"].append(subDirectory);
        }
    }
}
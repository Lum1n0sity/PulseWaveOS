#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <vector>

using stringT = std::string;
using fstream = std::fstream;

stringT trim(const stringT& str);

int main() {
    stringT projectFolderPath;

    std::cout << "Enter the file path to your project folder (Only /): ";
    std::getline(std::cin, projectFolderPath);

    projectFolderPath = trim(projectFolderPath);

    stringT buildFolderPath = projectFolderPath + "/build";
    stringT configJsonPath = projectFolderPath + "/config.json";

    if (!std::filesystem::exists(buildFolderPath)) 
    {
        if (!std::filesystem::create_directory(buildFolderPath)) 
        {
            std::cerr << "Error creating output directory: " << buildFolderPath << std::endl;
            return 1;
        }
    }

    std::cout << "configJsonPath: " << configJsonPath << '\n';

    fstream file(configJsonPath);
    nlohmann::json json_data;
    file >> json_data;
    
    if (!file.is_open()) 
    {
        std::cerr << "Error opening config.json" << std::endl;
        return 1;
    }

    // Store dependency timestamps in a map
    std::map<stringT, std::filesystem::file_time_type> dependencyTimestamps;

    for (const auto& component : json_data["components"]) 
    {
        stringT source_file = component["sources"][0];
        stringT output_file = buildFolderPath + "/" + component["output"].get<stringT>(); // Use '/' for path separation

        stringT compile_command = "g++ -o \"" + output_file + "\" \"" + source_file + "\"";

        std::cout << "Compiling " << source_file << std::endl;
        int result = system(compile_command.c_str());
        if (result == 0) 
        {
            dependencyTimestamps[source_file] = std::filesystem::last_write_time(source_file);
            std::cout << "Successfully compiled: " << output_file << std::endl;
        } 
        else 
        {
            std::cerr << "Error compiling: " << output_file << std::endl;
        }
    }

    return 0;
}

stringT trim(const stringT& str)
{
    size_t first = str.find_first_not_of(' ');
    if (stringT::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
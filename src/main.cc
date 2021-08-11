#include <iostream>
#include <fstream>
#include <vector>

#include "./undead.cc"

#define UNDEAD_FILEPATH "./src/tests/"

void perform(std::vector<std::string>& file_contents) {
    Undead executor;
    auto genetated = executor.GenerateEntities(file_contents);

    for (auto& entity: genetated)
    {
        std::cout << "ENTITY: " << entity.first << " " << entity.second->Scope.first << ":" << entity.second->Scope.second << " " << entity.second->Tasks.size() << "\n";
    }
    
}

//run: g++ -o undead src/main.cc && ./undead hello_world.undead
int main(int arg_count, char** args) {     
    if (arg_count == 2) {
        std::string filename;
        if (args[1] != "") {
            if (!ends_with(std::string(args[1]), ".undead"))
            {
                std::cout << "File should have \".undead\" extension.\n";
                return 1;
            }
            filename = args[1];
        } else {
            filename = "hello_world.undead";
        }


        std::ifstream file(UNDEAD_FILEPATH + filename);
        std::string line;
        std::vector<std::string> lines;

        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        //for (auto line: lines)
        //    std::cout << line << "\n";

        perform(lines);
    }
}
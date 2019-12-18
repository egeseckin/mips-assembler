#include <iostream>
#include "ErrorHandling.h"
#include <fstream>
#include <filesystem>
#include <vector>
#include <map>
class Main : ErrorHandling {
    public:
        Main() { ErrorHandling(); }
        ~Main() {}
        
        char menu() {
            std::string menuOption;

            std::cout << "(1) Interactive Mode" <<  std::endl;
            std::cout << "(2) Batch Mode" << std::endl;
            std::cout << "(3) Exit" << std::endl;

            std::cout << "Your Choice: ";
            std::cin >> menuOption;
            
            bool option = optionChecker(menuOption);
            if (option == false) {
                std::cout << "You have enter wrong input" << std::endl;
                std::cout << "Input should not be empty or multi value";
                return NULL;
            }
            return menuOption.at(0);
        }

        void readFile(std::string fileName) {
            bool isExist = std::filesystem::exists(fileName);
            if (isExist) {
                std::fstream file(fileName);
                if (file.is_open()) {
                    std::string line;
                    while (getline(file, line)) {
                        std::cout << line << std::endl;
                        // get the new codes from file and process it
                    }
                    file.close();
                }
            }
        }

        void writeFile(std::vector<std::string> instructionSet){
            std::ofstream outfile ("output.txt");
            std::vector<std::string>::iterator it = instructionSet.begin();

            while(it != instructionSet.end()){
                outfile << *it << std::endl;
            }

            outfile.close();

        }

        std::pair<std::map<std::string, int>, std::vector<int>> labelAndPcCounter(std::vector<std::string> instructionSet) {
            int pc = 80001000;

            std::vector<int> pcCounter;
            std::map<std::string, int> labels;
        
            std::vector<std::string>::iterator it = instructionSet.begin();

            while(it != instructionSet.end()) {
                pcCounter.push_back(pc);

                if (it->find(':') != std::string::npos) {
                    labels.insert(labels.begin(), {it->substr(0, it->find(':') + 1), pc});
                }
                pc += 4;
                it++;
            }
            
            return std::make_pair(labels, pcCounter);;
        }
};

int main(int argc, char **argv) {
    Main assembler;
    char menuOption;
    
    std::string fileName = "./test1.txt";
    assembler.readFile(fileName);
    std::cout << "Welcome to the MIPS ASSEMBLER" << std::endl;
    std::vector<std::string> x;
    x.push_back("add s1 s3 s1");
    x.push_back("label: s1 s2 s3");
    x.push_back("bne s1 s2 label");
    x.push_back("label1: s1 s2 s3");

    std::pair<std::map<std::string, int>, std::vector<int>> result = assembler.labelAndPcCounter(x);
    std::cout<< "";
    do {
        menuOption = assembler.menu();
        switch (menuOption) {
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            default:
                std::cout << "\nWrong Option!!!" << std::endl;
                break;
        }
    } while (menuOption != '3');
    
    return 0;
}

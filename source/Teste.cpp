#include <fstream>
#include <iostream>
#include <experimental/filesystem>
using namespace std;
using namespace experimental::filesystem;
 
int main()
{
    create_directories("sandbox/a/b");
    std::ofstream("sandbox/file1.txt");
    std::ofstream("sandbox/file2.txt");
    for(auto& p: directory_iterator("sandbox"))
        std::cout << p << '\n';
    remove_all("sandbox");
}
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    vector<vector<int> > mv(3,vector<int>(10));
    cout << std::boolalpha << mv.empty() << "\n";
}


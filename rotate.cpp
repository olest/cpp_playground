#include<vector>
#include<algorithm>
#include<iostream>

int main() {
    std::vector<int> v(10);
    std::iota(v.begin(),v.end(),0);

    for (const auto& e: v) {
        std::cout << e << " ";
    }
    std::cout << "\n";

    std::rotate(begin(v),begin(v)+3,end(v)-3);
    for (const auto& e: v) {
        std::cout << e << " ";
    }
    std::cout << "\n";

}

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>

using namespace std;

int main() {

    std::vector<int> v = {1,2,3,4};

    std::ostringstream oss;

    std::copy(v.begin(), 
              v.end(),
              std::ostream_iterator<int>(oss, ","));

    std::cout << oss.str() << std::endl;

}


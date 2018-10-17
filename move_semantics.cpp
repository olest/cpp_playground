#include<vector>
#include<iostream>

// https://stackoverflow.com/questions/21858187/why-does-vector-emplace-back-call-the-move-constructor

struct Object { 
    Object() { std::cout << "constructor\n"; }

    Object(const Object &) { std::cout << "copy constructor\n"; }

    Object(Object &&) { std::cout << "move constructor\n"; }
};

 

int main() {

    std::vector<Object> v;
    // ensure minimum capacity, so std::move is not called while resizing
    v.reserve(10);
    v.emplace_back(Object{});
    v.emplace_back();
}

// Output:
// constructor
// move constructor
// constructor
//

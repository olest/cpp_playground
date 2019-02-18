#include<vector>
#include<iostream>

// https://stackoverflow.com/questions/21858187/why-does-vector-emplace-back-call-the-move-constructor

struct Object { 
    public:
    Object() : _data(nullptr) { std::cout << "default constructor" << "\n"; }
    Object(int* d) : _data(d) {  std::cout << "constructor\n"; }

    Object(const Object& o) { _data = new int; *_data = *o._data; std::cout << "copy constructor\n"; }

    Object(Object && o) : _data(o._data) { o._data=nullptr;  std::cout << "move constructor\n"; }

    ~Object() { std::cout << "destructor"; if (_data!=nullptr) { delete _data; }}
    private:
    int* _data;
};

 

int main() {

    std::vector<Object> v;
    // ensure minimum capacity, so std::move is not called while resizing
    v.reserve(10);
    int d = 5;
    v.emplace_back(&d);
    v.emplace_back();
}

// Output:
// constructor
// move constructor
// constructor
//

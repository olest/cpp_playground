#include<vector>
#include<iostream>

using namespace std;

int main() {

    size_t nbins = 5;

    vector<int> vec(nbins);
    cout << "size: " << vec.size() << endl;
    cout << "capacity: " << vec.capacity() << endl;
    vec[1] = 10;
    for (auto item: vec) {
        cout << "item: " << item << "\n";
    }
    vec.clear();
    vec.resize(nbins);
    cout << "\nsize: " << vec.size() << endl;
    cout << "capacity: " << vec.capacity() << endl;
    vec[1] = 20;
    for (auto item: vec) {
        cout << "item: " << item << "\n";
    }
}

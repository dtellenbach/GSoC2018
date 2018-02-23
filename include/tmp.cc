#include <iostream>
#include <array>



template<int C>
class MyClass {
    public:
    // static constexpr int sze();
    static constexpr int arraySize();
    std::array<int, arraySize()> arr;
    
    
};

template<int C>
constexpr int MyClass<C>::arraySize() {
    return (C*C+C)/2;
}

int main() {

    MyClass<3> cls;
    std::cout << cls.arr.size() << std::endl;
}


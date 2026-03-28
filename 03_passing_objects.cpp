#include <iostream>
using namespace std;

// ========== BASE CLASS ==========
class Base {
public:
    Base() {
        cout << "Base::Base() constructor" << endl;
    }
    
    Base(const Base& other) {
        cout << "Base::Base(const Base&) COPY constructor" << endl;
    }
    
    virtual ~Base() {
        cout << "Base::~Base() destructor" << endl;
    }
    
    virtual void print() {
        cout << "Base::print()" << endl;
    }
};

// ========== DERIVED CLASS ==========
class Desc : public Base {
public:
    Desc() {
        cout << "Desc::Desc() constructor" << endl;
    }
    
    Desc(const Desc& other) : Base(other) {
        cout << "Desc::Desc(const Desc&) COPY constructor" << endl;
    }
    
    ~Desc() {
        cout << "Desc::~Desc() destructor" << endl;
    }
    
    void print() override {
        cout << "Desc::print()" << endl;
    }
};

// ========== FUNCTIONS FOR PASSING OBJECTS ==========

// 1. Pass by value (copy is created)
void func1(Base obj) {
    cout << "  func1: inside function" << endl;
    obj.print();
}

// 2. Pass by pointer (no copy)
void func2(Base* obj) {
    cout << "  func2: inside function" << endl;
    obj->print();
}

// 3. Pass by reference (no copy)
void func3(Base& obj) {
    cout << "  func3: inside function" << endl;
    obj.print();
}

int main() {
    cout << "========== PROGRAM 3: PASSING OBJECTS ==========\n\n";
    
    cout << "--- Create derived object ---\n";
    Desc d;
    
    cout << "\n--- Pass to func1 (by value) ---\n";
    func1(d);  // creates copy of Base! (slicing!)
    
    cout << "\n--- Pass to func2 (by pointer) ---\n";
    func2(&d);  // no copy, just address
    
    cout << "\n--- Pass to func3 (by reference) ---\n";
    func3(d);   // no copy, just reference
    
    cout << "\n--- Destroy object d ---\n";
    // d destroyed here
    
    cout << "\n========== END OF PROGRAM ==========\n";
    return 0;
}
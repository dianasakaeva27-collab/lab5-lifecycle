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

// ========== FUNCTIONS RETURNING LOCAL OBJECTS (DANGEROUS!) ==========
Base func1() {
    Base local;
    cout << "  func1: returning local object" << endl;
    return local;  // creates copy
}

Base* func2() {
    Base local;
    cout << "  func2: returning POINTER to local object" << endl;
    return &local;  // DANGEROUS! local dies after function exit
}

Base& func3() {
    Base local;
    cout << "  func3: returning REFERENCE to local object" << endl;
    return local;   // DANGEROUS! local dies after function exit
}

// ========== FUNCTIONS RETURNING DYNAMIC OBJECTS ==========
Base* func4() {
    Base* ptr = new Base();
    cout << "  func4: returning pointer to dynamic object" << endl;
    return ptr;  // OK, must delete later
}

Base* func5() {
    Desc* ptr = new Desc();
    cout << "  func5: returning pointer to dynamic derived object" << endl;
    return ptr;  // OK, virtual works
}

Base& func6() {
    Base* ptr = new Base();
    cout << "  func6: returning REFERENCE to dynamic object" << endl;
    return *ptr;  // OK, must delete later
}

int main() {
    cout << "========== PROGRAM 4: RETURNING OBJECTS ==========\n\n";
    
    cout << "--- func1: return local object by value ---\n";
    Base obj1 = func1();  // OK: creates copy
    obj1.print();
    
    cout << "\n--- func2: return pointer to local object (DANGEROUS!) ---\n";
    Base* ptr2 = func2();  // ptr2 points to dead object!
    cout << "  After func2, local object is already destroyed!" << endl;
    // ptr2->print();  // UNCOMMENT - program will crash!
    
    cout << "\n--- func4: return dynamic object (correct) ---\n";
    Base* ptr4 = func4();
    ptr4->print();
    delete ptr4;  // must delete!
    
    cout << "\n--- func5: return dynamic derived object ---\n";
    Base* ptr5 = func5();
    ptr5->print();  // calls Desc::print() thanks to virtual
    delete ptr5;    // calls ~Desc() and ~Base()
    
    cout << "\n--- func6: return reference to dynamic object ---\n";
    Base& ref6 = func6();
    ref6.print();
    delete &ref6;   // must delete!
    
    cout << "\n========== END OF PROGRAM ==========\n";
    return 0;
}
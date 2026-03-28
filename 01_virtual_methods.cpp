#include <iostream>
using namespace std;

// ========== BASE CLASS ==========
class Base {
public:
    // Non-virtual method
    void nonVirtual() {
        cout << "Base::nonVirtual()" << endl;
    }
    
    // Virtual method
    virtual void virtualMethod() {
        cout << "Base::virtualMethod()" << endl;
    }
    
    // Method that calls another method
    void callNonVirtual() {
        cout << "Base::callNonVirtual() -> ";
        nonVirtual();
    }
    
    void callVirtual() {
        cout << "Base::callVirtual() -> ";
        virtualMethod();
    }
    
    virtual ~Base() {
        cout << "Base::~Base()" << endl;
    }
};

// ========== DERIVED CLASS ==========
class Desc : public Base {
public:
    // Override non-virtual method (hiding)
    void nonVirtual() {
        cout << "Desc::nonVirtual()" << endl;
    }
    
    // Override virtual method
    void virtualMethod() override {
        cout << "Desc::virtualMethod()" << endl;
    }
    
    ~Desc() {
        cout << "Desc::~Desc()" << endl;
    }
};

int main() {
    cout << "========== PROGRAM 1: VIRTUAL METHODS ==========\n\n";
    
    // Create derived object
    Desc d;
    
    cout << "--- Call through derived object ---\n";
    d.nonVirtual();      // calls Desc::nonVirtual()
    d.virtualMethod();   // calls Desc::virtualMethod()
    
    cout << "\n--- Call through base class pointer ---\n";
    Base* ptr = &d;
    ptr->nonVirtual();    // calls Base::nonVirtual() (non-virtual!)
    ptr->virtualMethod(); // calls Desc::virtualMethod() (virtual!)
    
    cout << "\n--- Call methods that call other methods ---\n";
    d.callNonVirtual();   // Base::callNonVirtual() -> Base::nonVirtual()
    d.callVirtual();      // Base::callVirtual() -> Desc::virtualMethod()
    
    cout << "\n--- Delete through base class pointer ---\n";
    Base* ptr2 = new Desc();
    delete ptr2;  // calls ~Desc() and ~Base() (virtual destructor)
    
    cout << "\n========== END OF PROGRAM ==========\n";
    return 0;
}
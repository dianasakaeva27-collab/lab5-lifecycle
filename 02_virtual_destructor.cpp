#include <iostream>
using namespace std;

// ========== BASE CLASS ==========
class Base {
public:
    Base() {
        cout << "Base::Base() constructor" << endl;
    }
    
    // WITHOUT virtual - derived destructor will NOT be called!
    // WITH virtual - derived destructor WILL be called!
    virtual ~Base() {
        cout << "Base::~Base() destructor" << endl;
    }
};

// ========== DERIVED CLASS ==========
class Desc : public Base {
private:
    int* data;  // pointer to dynamic memory
public:
    Desc() {
        cout << "Desc::Desc() constructor" << endl;
        data = new int(42);  // allocate memory
    }
    
    ~Desc() {
        cout << "Desc::~Desc() destructor" << endl;
        delete data;  // free memory
    }
};

int main() {
    cout << "========== PROGRAM 2: VIRTUAL DESTRUCTOR ==========\n\n";
    
    cout << "--- Create derived object ---\n";
    Desc d;  // normal creation and destruction
    
    cout << "\n--- Create object through base class pointer ---\n";
    Base* ptr = new Desc();  // create derived
    delete ptr;  // delete through base pointer
    
    cout << "\n--- If destructor was NOT virtual ---\n";
    cout << "Then delete ptr would call only ~Base()\n";
    cout << "Memory 'data' would leak!\n";
    
    cout << "\n========== END OF PROGRAM ==========\n";
    return 0;
}
#include <iostream>
#include <memory>  // for unique_ptr, shared_ptr
using namespace std;

// ========== BASE CLASS ==========
class Base {
public:
    Base() {
        cout << "Base::Base() constructor" << endl;
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
    
    ~Desc() {
        cout << "Desc::~Desc() destructor" << endl;
    }
    
    void print() override {
        cout << "Desc::print()" << endl;
    }
};

// ========== FUNCTIONS WITH SMART POINTERS ==========

// Pass unique_ptr by reference (pass ownership)
void takeUniquePtr(unique_ptr<Base>& ptr) {
    cout << "  takeUniquePtr: received unique_ptr" << endl;
    ptr->print();
}

// Pass shared_ptr by value (increment counter)
void takeSharedPtr(shared_ptr<Base> ptr) {
    cout << "  takeSharedPtr: received shared_ptr, count = " 
         << ptr.use_count() << endl;
    ptr->print();
}

// Return unique_ptr (transfer ownership)
unique_ptr<Base> returnUniquePtr() {
    cout << "  returnUniquePtr: creating object" << endl;
    unique_ptr<Base> ptr = make_unique<Desc>();
    return ptr;
}

int main() {
    cout << "========== PROGRAM 6: SMART POINTERS ==========\n\n";
    
    cout << "--- unique_ptr (exclusive ownership) ---\n";
    unique_ptr<Base> uptr1 = make_unique<Desc>();  // create
    uptr1->print();
    
    // unique_ptr cannot be copied, only moved
    unique_ptr<Base> uptr2 = move(uptr1);  // transfer ownership
    cout << "uptr1 is now empty: " << (uptr1 ? "not empty" : "empty") << endl;
    uptr2->print();
    
    cout << "\n--- Pass unique_ptr to function ---\n";
    unique_ptr<Base> uptr3 = make_unique<Desc>();
    takeUniquePtr(uptr3);  // pass by reference
    uptr3->print();        // still exists
    
    cout << "\n--- Return unique_ptr from function ---\n";
    unique_ptr<Base> uptr4 = returnUniquePtr();
    uptr4->print();
    
    cout << "\n--- shared_ptr (shared ownership) ---\n";
    shared_ptr<Base> sptr1 = make_shared<Desc>();
    cout << "Count after creation: " << sptr1.use_count() << endl;
    
    shared_ptr<Base> sptr2 = sptr1;  // copy
    cout << "Count after copy: " << sptr1.use_count() << endl;
    
    cout << "\n--- Pass shared_ptr to function ---\n";
    takeSharedPtr(sptr1);
    cout << "Count after function: " << sptr1.use_count() << endl;
    
    cout << "\n--- Smart pointers delete objects automatically ---\n";
    cout << "Exiting main: objects will be destroyed automatically\n";
    
    cout << "\n========== END OF PROGRAM ==========\n";
    return 0;
}
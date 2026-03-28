#include <iostream>
#include <string>
using namespace std;

// ========== BASE CLASS ==========
class Base {
public:
    // Method returning class name
    virtual string classname() {
        return "Base";
    }
    
    // Method checking if object belongs to class
    virtual bool isA(string name) {
        return name == "Base";
    }
    
    virtual ~Base() {
        cout << "Base::~Base()" << endl;
    }
};

// ========== DERIVED CLASS ==========
class Desc : public Base {
public:
    string classname() override {
        return "Desc";
    }
    
    bool isA(string name) override {
        return (name == "Desc") || Base::isA(name);
    }
    
    ~Desc() {
        cout << "Desc::~Desc()" << endl;
    }
    
    void onlyDescMethod() {
        cout << "This method exists only in Desc" << endl;
    }
};

// ========== GRANDCHILD CLASS ==========
class GrandChild : public Desc {
public:
    string classname() override {
        return "GrandChild";
    }
    
    bool isA(string name) override {
        return (name == "GrandChild") || Desc::isA(name);
    }
    
    ~GrandChild() {
        cout << "GrandChild::~GrandChild()" << endl;
    }
};

int main() {
    cout << "========== PROGRAM 5: TYPE CHECKING ==========\n\n";
    
    Base* ptr1 = new Base();
    Base* ptr2 = new Desc();
    Base* ptr3 = new GrandChild();
    
    cout << "--- classname() method ---\n";
    cout << "ptr1: " << ptr1->classname() << endl;
    cout << "ptr2: " << ptr2->classname() << endl;
    cout << "ptr3: " << ptr3->classname() << endl;
    
    cout << "\n--- isA() method ---\n";
    cout << "ptr1 is Base? " << ptr1->isA("Base") << endl;
    cout << "ptr2 is Base? " << ptr2->isA("Base") << endl;
    cout << "ptr2 is Desc? " << ptr2->isA("Desc") << endl;
    cout << "ptr3 is Base? " << ptr3->isA("Base") << endl;
    cout << "ptr3 is Desc? " << ptr3->isA("Desc") << endl;
    cout << "ptr3 is GrandChild? " << ptr3->isA("GrandChild") << endl;
    
    cout << "\n--- dynamic_cast (safe casting) ---\n";
    
    // Try to cast Base* to Desc*
    Desc* d1 = dynamic_cast<Desc*>(ptr1);
    if (d1) {
        cout << "ptr1 can be cast to Desc" << endl;
        d1->onlyDescMethod();
    } else {
        cout << "ptr1 CANNOT be cast to Desc" << endl;
    }
    
    Desc* d2 = dynamic_cast<Desc*>(ptr2);
    if (d2) {
        cout << "ptr2 can be cast to Desc" << endl;
        d2->onlyDescMethod();
    } else {
        cout << "ptr2 CANNOT be cast to Desc" << endl;
    }
    
    Desc* d3 = dynamic_cast<Desc*>(ptr3);
    if (d3) {
        cout << "ptr3 can be cast to Desc" << endl;
        d3->onlyDescMethod();
    } else {
        cout << "ptr3 CANNOT be cast to Desc" << endl;
    }
    
    cout << "\n--- Cast with isA (safe) ---\n";
    if (ptr2->isA("Desc")) {
        Desc* safe = (Desc*)ptr2;  // unsafe cast, but we checked
        safe->onlyDescMethod();
    }
    
    cout << "\n--- Deleting objects ---\n";
    delete ptr1;
    delete ptr2;
    delete ptr3;
    
    cout << "\n========== END OF PROGRAM ==========\n";
    return 0;
}
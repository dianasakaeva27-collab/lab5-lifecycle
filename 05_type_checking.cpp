#include <iostream>
#include <string>
using namespace std;

// ========== БАЗОВЫЙ КЛАСС ==========
class Base {
public:
    // Метод, возвращающий имя класса
    virtual string classname() {
        return "Base";
    }
    
    // Метод, проверяющий принадлежность объекта к классу
    virtual bool isA(string name) {
        return name == "Base";
    }
    
    // Виртуальный деструктор
    virtual ~Base() {
        cout << "Base::~Base()" << endl;
    }
};

// ========== КЛАСС-ПОТОМОК ==========
class Desc : public Base {
public:
    // Переопределяем метод classname()
    string classname() override {
        return "Desc";
    }
    
    // Переопределяем метод isA() - учитываем иерархию
    bool isA(string name) override {
        // Проверяем, является ли объект Desc или любым предком
        return (name == "Desc") || Base::isA(name);
    }
    
    ~Desc() {
        cout << "Desc::~Desc()" << endl;
    }
    
    // Метод, который есть только у Desc (не в Base)
    void onlyDescMethod() {
        cout << "Этот метод существует только в Desc" << endl;
    }
};

// ========== КЛАСС-ВНУК ==========
class GrandChild : public Desc {
public:
    // Переопределяем classname() для внука
    string classname() override {
        return "GrandChild";
    }
    
    // Переопределяем isA() - проверяем все уровни иерархии
    bool isA(string name) override {
        return (name == "GrandChild") || Desc::isA(name);
    }
    
    ~GrandChild() {
        cout << "GrandChild::~GrandChild()" << endl;
    }
};

int main() {
    cout << "========== ПРОГРАММА 5: ПРОВЕРКА ТИПА ==========\n\n";
    
    // Создаём объекты разных типов
    Base* ptr1 = new Base();        // указатель на Base
    Base* ptr2 = new Desc();        // указатель на Base, но объект Desc
    Base* ptr3 = new GrandChild();  // указатель на Base, но объект GrandChild
    
    cout << "--- Метод classname() ---\n";
    cout << "ptr1: " << ptr1->classname() << endl;  // "Base"
    cout << "ptr2: " << ptr2->classname() << endl;  // "Desc"
    cout << "ptr3: " << ptr3->classname() << endl;  // "GrandChild"
    
    cout << "\n--- Метод isA() ---\n";
    cout << "ptr1 is Base? " << ptr1->isA("Base") << endl;           // true
    cout << "ptr2 is Base? " << ptr2->isA("Base") << endl;           // true
    cout << "ptr2 is Desc? " << ptr2->isA("Desc") << endl;           // true
    cout << "ptr3 is Base? " << ptr3->isA("Base") << endl;           // true
    cout << "ptr3 is Desc? " << ptr3->isA("Desc") << endl;           // true
    cout << "ptr3 is GrandChild? " << ptr3->isA("GrandChild") << endl; // true
    
    cout << "\n--- dynamic_cast (безопасное приведение типов) ---\n";
    
    // Пытаемся привести Base* к Desc*
    Desc* d1 = dynamic_cast<Desc*>(ptr1);
    if (d1) {
        cout << "ptr1 можно привести к Desc" << endl;
        d1->onlyDescMethod();
    } else {
        cout << "ptr1 НЕЛЬЗЯ привести к Desc" << endl;  // ← этот сработает
    }
    
    Desc* d2 = dynamic_cast<Desc*>(ptr2);
    if (d2) {
        cout << "ptr2 можно привести к Desc" << endl;    // ← этот сработает
        d2->onlyDescMethod();
    } else {
        cout << "ptr2 НЕЛЬЗЯ привести к Desc" << endl;
    }
    
    Desc* d3 = dynamic_cast<Desc*>(ptr3);
    if (d3) {
        cout << "ptr3 можно привести к Desc" << endl;    // ← этот сработает
        d3->onlyDescMethod();
    } else {
        cout << "ptr3 НЕЛЬЗЯ привести к Desc" << endl;
    }
    
    cout << "\n--- Приведение с помощью isA (безопасно) ---\n";
    // Сначала проверяем, потом приводим (опасное приведение, но мы уже проверили)
    if (ptr2->isA("Desc")) {
        Desc* safe = (Desc*)ptr2;  // опасное приведение, но безопасно, потому что проверили
        safe->onlyDescMethod();
    }
    
    cout << "\n--- Удаление объектов ---\n";
    delete ptr1;
    delete ptr2;
    delete ptr3;
    
    cout << "\n========== КОНЕЦ ПРОГРАММЫ ==========\n";
    return 0;
}

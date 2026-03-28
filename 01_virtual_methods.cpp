#include <iostream>
using namespace std;

// ========== БАЗОВЫЙ КЛАСС ==========
class Base {
public:
    // Невиртуальный метод
    void nonVirtual() {
        cout << "Base::nonVirtual()" << endl;
    }
    
    // Виртуальный метод
    virtual void virtualMethod() {
        cout << "Base::virtualMethod()" << endl;
    }
    
    // Метод, который вызывает другой метод
    void callNonVirtual() {
        cout << "Base::callNonVirtual() -> ";
        nonVirtual();  // вызов невиртуального метода
    }
    
    void callVirtual() {
        cout << "Base::callVirtual() -> ";
        virtualMethod();  // вызов виртуального метода
    }
    
    // Виртуальный деструктор (важен для корректного удаления потомка)
    virtual ~Base() {
        cout << "Base::~Base()" << endl;
    }
};

// ========== КЛАСС-ПОТОМОК ==========
class Desc : public Base {
public:
    // Переопределяем невиртуальный метод (скрываем метод базового класса)
    void nonVirtual() {
        cout << "Desc::nonVirtual()" << endl;
    }
    
    // Переопределяем виртуальный метод (override явно указывает, что это переопределение)
    void virtualMethod() override {
        cout << "Desc::virtualMethod()" << endl;
    }
    
    // Деструктор потомка
    ~Desc() {
        cout << "Desc::~Desc()" << endl;
    }
};

int main() {
    cout << "========== ПРОГРАММА 1: ВИРТУАЛЬНЫЕ МЕТОДЫ ==========\n\n";
    
    // Создаём объект потомка
    Desc d;
    
    cout << "--- Вызов через объект потомка ---\n";
    d.nonVirtual();      // вызывается Desc::nonVirtual()
    d.virtualMethod();   // вызывается Desc::virtualMethod()
    
    cout << "\n--- Вызов через указатель на базовый класс ---\n";
    Base* ptr = &d;
    ptr->nonVirtual();    // вызывается Base::nonVirtual() (невиртуальный!)
    ptr->virtualMethod(); // вызывается Desc::virtualMethod() (виртуальный!)
    
    cout << "\n--- Вызов методов, которые вызывают другие методы ---\n";
    d.callNonVirtual();   // Base::callNonVirtual() -> Base::nonVirtual()
    d.callVirtual();      // Base::callVirtual() -> Desc::virtualMethod()
    
    cout << "\n--- Удаление через указатель на базовый класс ---\n";
    Base* ptr2 = new Desc();
    delete ptr2;  // вызывается ~Desc() и ~Base() (благодаря виртуальному деструктору)
    
    cout << "\n========== КОНЕЦ ПРОГРАММЫ ==========\n";
    return 0;
}

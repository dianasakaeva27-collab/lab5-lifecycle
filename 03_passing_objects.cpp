#include <iostream>
using namespace std;

// ========== БАЗОВЫЙ КЛАСС ==========
class Base {
public:
    // Конструктор по умолчанию
    Base() {
        cout << "Base::Base() конструктор" << endl;
    }
    
    // Конструктор копирования
    Base(const Base& other) {
        cout << "Base::Base(const Base&) КОНСТРУКТОР КОПИРОВАНИЯ" << endl;
    }
    
    // Виртуальный деструктор
    virtual ~Base() {
        cout << "Base::~Base() деструктор" << endl;
    }
    
    // Виртуальный метод вывода
    virtual void print() {
        cout << "Base::print()" << endl;
    }
};

// ========== КЛАСС-ПОТОМОК ==========
class Desc : public Base {
public:
    // Конструктор потомка
    Desc() {
        cout << "Desc::Desc() конструктор" << endl;
    }
    
    // Конструктор копирования потомка (вызывает конструктор копирования Base)
    Desc(const Desc& other) : Base(other) {
        cout << "Desc::Desc(const Desc&) КОНСТРУКТОР КОПИРОВАНИЯ" << endl;
    }
    
    // Деструктор потомка
    ~Desc() {
        cout << "Desc::~Desc() деструктор" << endl;
    }
    
    // Переопределение виртуального метода
    void print() override {
        cout << "Desc::print()" << endl;
    }
};

// ========== ФУНКЦИИ ДЛЯ ПЕРЕДАЧИ ОБЪЕКТОВ ==========

// 1. Передача по значению (создаётся копия)
void func1(Base obj) {
    cout << "  func1: внутри функции" << endl;
    obj.print();  // вызывается Base::print() из-за срезки (slicing)
}

// 2. Передача по указателю (копия НЕ создаётся)
void func2(Base* obj) {
    cout << "  func2: внутри функции" << endl;
    obj->print();  // вызывается Desc::print() (полиморфизм работает)
}

// 3. Передача по ссылке (копия НЕ создаётся)
void func3(Base& obj) {
    cout << "  func3: внутри функции" << endl;
    obj.print();   // вызывается Desc::print() (полиморфизм работает)
}

int main() {
    cout << "========== ПРОГРАММА 3: ПЕРЕДАЧА ОБЪЕКТОВ ==========\n\n";
    
    cout << "--- Создаём объект потомка ---\n";
    Desc d;
    
    cout << "\n--- Передаём в func1 (по значению) ---\n";
    func1(d);  // создаётся копия Base! (происходит срезка - slicing!)
    
    cout << "\n--- Передаём в func2 (по указателю) ---\n";
    func2(&d);  // копия не создаётся, передаётся адрес
    
    cout << "\n--- Передаём в func3 (по ссылке) ---\n";
    func3(d);   // копия не создаётся, передаётся ссылка
    
    cout << "\n--- Уничтожение объекта d ---\n";
    // d уничтожится здесь
    
    cout << "\n========== КОНЕЦ ПРОГРАММЫ ==========\n";
    return 0;
}

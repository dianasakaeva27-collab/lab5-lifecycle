#include <iostream>
#include <string>
using namespace std;

// ========== БАЗОВЫЙ КЛАСС (РОДИТЕЛЬ) ==========
class Base {
public:
    // Метод, возвращающий имя класса
    virtual string classname() {
        return "Base";
    }
    
  
    // виртуальный метод, который проверяет, принадлежит ли объект к определённому классу или его потомкам
    virtual bool isA(string name) {
        return name == "Base";
    }
    
    // Виртуальный деструктор (обязателен для полиморфизма)
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
    
    // Переопределяем метод isA() - проверяем себя и всех предков
    bool isA(string name) override {
        // Объект является Desc или любым предком (Base)
        return (name == "Desc") || Base::isA(name);
    }
    
    ~Desc() {
        cout << "Desc::~Desc()" << endl;
    }
    
    // Метод, который есть только у Desc (нет в Base)
    void onlyDescMethod() {
        cout << "Этот метод существует только в Desc" << endl;
    }
};

// ========== КЛАСС-ВНУК ==========
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
    cout << "========== ПРОГРАММА 5: ПРОВЕРКА ТИПА ==========\n\n";
    
    // Создаём три объекта разных типов
    Base* ptr1 = new Base();        // реальный объект Base
    Base* ptr2 = new Desc();        // реальный объект Desc (хранится в указателе на Base)
    Base* ptr3 = new GrandChild();  // реальный объект GrandChild
    
    // ===== 1. ДЕМОНСТРАЦИЯ classname() =====
    cout << "--- Метод classname() ---\n";
    cout << "ptr1 (объект Base): " << ptr1->classname() << endl;
    cout << "ptr2 (объект Desc): " << ptr2->classname() << endl;
    cout << "ptr3 (объект GrandChild): " << ptr3->classname() << endl;
    
    // ===== 2. ДЕМОНСТРАЦИЯ isA() =====
    cout << "\n--- Метод isA() ---\n";
    cout << "ptr1 is Base? " << ptr1->isA("Base") << endl;
    cout << "ptr2 is Base? " << ptr2->isA("Base") << endl;
    cout << "ptr2 is Desc? " << ptr2->isA("Desc") << endl;
    cout << "ptr3 is Base? " << ptr3->isA("Base") << endl;
    cout << "ptr3 is Desc? " << ptr3->isA("Desc") << endl;
    cout << "ptr3 is GrandChild? " << ptr3->isA("GrandChild") << endl;
    
    // ===== 3. БЕЗОПАСНОЕ ПРИВЕДЕНИЕ ТИПОВ (dynamic_cast) =====
    cout << "\n--- dynamic_cast (безопасное приведение типов) ---\n";
    
    // Попытка привести Base* к Desc*
    Desc* d1 = dynamic_cast<Desc*>(ptr1);
    if (d1) {
        // Приведение успешно (ptr1 на самом деле указывает на Desc или потомка)
        cout << "ptr1 можно привести к Desc" << endl;
        d1->onlyDescMethod();
    } else {
        // Приведение НЕ удалось (ptr1 указывает на Base, а не на Desc)
        cout << "ptr1 НЕЛЬЗЯ привести к Desc" << endl;
    }
    
    Desc* d2 = dynamic_cast<Desc*>(ptr2);
    if (d2) {
        cout << "ptr2 можно привести к Desc" << endl;
        d2->onlyDescMethod();  // безопасно, т.к. мы проверили
    } else {
        cout << "ptr2 НЕЛЬЗЯ привести к Desc" << endl;
    }
    
    Desc* d3 = dynamic_cast<Desc*>(ptr3);
    if (d3) {
        cout << "ptr3 можно привести к Desc" << endl;
        d3->onlyDescMethod();
    } else {
        cout << "ptr3 НЕЛЬЗЯ привести к Desc" << endl;
    }
    
    // ===== 4. РУЧНОЕ БЕЗОПАСНОЕ ПРИВЕДЕНИЕ (через isA) =====
    cout << "\n--- Ручное приведение с проверкой isA ---\n";
    
    // Сначала проверяем тип с помощью isA, потом приводим
    if (ptr2->isA("Desc")) {
        // Мы УВЕРЕНЫ, что ptr2 указывает на Desc или потомка
        // Ручное приведение - безопасно
        Desc* safe = (Desc*)ptr2;
        safe->onlyDescMethod();
    }
    
    // ===== 5. ОПАСНОЕ ПРИВЕДЕНИЕ (без проверки) =====
    cout << "\n--- Опасное приведение (C-style cast) ---\n";
    cout << "Без проверки: (Desc*)ptr1 - приведёт к ошибке при вызове метода\n";
    // Desc* dangerous = (Desc*)ptr1;  // 
    // dangerous->onlyDescMethod();    // ОШИБКА! объект Base не имеет этого метода
    
    // ===== 6. УДАЛЕНИЕ ОБЪЕКТОВ =====
    cout << "\n--- Удаление объектов ---\n";
    delete ptr1;
    delete ptr2;
    delete ptr3;
    
    cout << "\n========== КОНЕЦ ПРОГРАММЫ ==========\n";
    return 0;
}

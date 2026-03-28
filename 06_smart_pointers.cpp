#include <iostream>
#include <memory>  // для unique_ptr, shared_ptr
using namespace std;

// ========== БАЗОВЫЙ КЛАСС ==========
class Base {
public:
    // Конструктор базового класса
    Base() {
        cout << "Base::Base() конструктор" << endl;
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
    
    // Деструктор потомка
    ~Desc() {
        cout << "Desc::~Desc() деструктор" << endl;
    }
    
    // Переопределение виртуального метода
    void print() override {
        cout << "Desc::print()" << endl;
    }
};

// ========== ФУНКЦИИ С УМНЫМИ УКАЗАТЕЛЯМИ ==========

// Передача unique_ptr по ссылке (не передаём владение)
void takeUniquePtr(unique_ptr<Base>& ptr) {
    cout << "  takeUniquePtr: получили unique_ptr" << endl;
    ptr->print();
}

// Передача shared_ptr по значению (увеличиваем счётчик ссылок)
void takeSharedPtr(shared_ptr<Base> ptr) {
    cout << "  takeSharedPtr: получили shared_ptr, счётчик = " 
         << ptr.use_count() << endl;
    ptr->print();
}

// Возврат unique_ptr (передача владения)
unique_ptr<Base> returnUniquePtr() {
    cout << "  returnUniquePtr: создаём объект" << endl;
    unique_ptr<Base> ptr = make_unique<Desc>();  // создаём Desc через make_unique
    return ptr;  // владение передаётся вызывающему коду
}

int main() {
    cout << "========== ПРОГРАММА 6: УМНЫЕ УКАЗАТЕЛИ ==========\n\n";
    
    // ========== UNIQUE_PTR (эксклюзивное владение) ==========
    cout << "--- unique_ptr (эксклюзивное владение) ---\n";
    unique_ptr<Base> uptr1 = make_unique<Desc>();  // создаём объект Desc
    uptr1->print();
    
    // unique_ptr нельзя скопировать, только переместить
    unique_ptr<Base> uptr2 = move(uptr1);  // передаём владение
    cout << "uptr1 теперь пуст: " << (uptr1 ? "не пуст" : "пуст") << endl;
    uptr2->print();
    
    cout << "\n--- Передача unique_ptr в функцию ---\n";
    unique_ptr<Base> uptr3 = make_unique<Desc>();
    takeUniquePtr(uptr3);  // передаём по ссылке (владелец остаётся uptr3)
    uptr3->print();        // объект всё ещё существует
    
    cout << "\n--- Возврат unique_ptr из функции ---\n";
    unique_ptr<Base> uptr4 = returnUniquePtr();  // получаем владение
    uptr4->print();
    
    // ========== SHARED_PTR (разделяемое владение) ==========
    cout << "\n--- shared_ptr (разделяемое владение) ---\n";
    shared_ptr<Base> sptr1 = make_shared<Desc>();  // создаём объект
    cout << "Счётчик после создания: " << sptr1.use_count() << endl;
    
    shared_ptr<Base> sptr2 = sptr1;  // копируем, счётчик увеличивается
    cout << "Счётчик после копирования: " << sptr1.use_count() << endl;
    
    cout << "\n--- Передача shared_ptr в функцию ---\n";
    takeSharedPtr(sptr1);  // передаём по значению, счётчик увеличивается
    cout << "Счётчик после функции: " << sptr1.use_count() << endl;
    
    cout << "\n--- Умные указатели сами удаляют объекты ---\n";
    cout << "Выход из main: объекты удалятся автоматически\n";
    
    cout << "\n========== КОНЕЦ ПРОГРАММЫ ==========\n";
    return 0;
}

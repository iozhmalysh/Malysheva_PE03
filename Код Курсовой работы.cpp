#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cctype>

using namespace std;


//Очистка потока ввода после ошибки
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//Ввод целого числа с проверкой
int safeInputInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Ошибка! Введите число.\n";
            clearInput();
        } else {
            clearInput();
            return value;
        }
    }
}

//Ввод числа в диапазоне
int safeInputRange(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        value = safeInputInt(prompt);
        if (value >= minVal && value <= maxVal)
            return value;
        cout << "Ошибка! Введите от " << minVal << " до " << maxVal << ".\n";
    }
}

//Ввод непустой строки
string safeInputString(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (value.empty() || value.find_first_not_of(" \t") == string::npos) {
            cout << "Ошибка! Поле не может быть пустым.\n";
        } else {
            return value;
        }
    }
}

//Реализация вспомогательного класса Date, который представляет дату и проверяет доступность бронирования
class Date {
public:
    int day, month, year;
    
    Date(int d = 1, int m = 1, int y = 2026) : day(d), month(m), year(y) {}
    
    //Сравнение дат для проверки пересечения периодов
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
    
    void print() const {
        cout << day << "." << month << "." << year;
    }
    
    //Проверка корректности даты
    bool isValid() const {
        if (month < 1 || month > 12) return false;
        if (day < 1) return false;
        
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        //Проверка високосного года
        if (month == 2 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            return day <= 29;
        }
        return day <= daysInMonth[month - 1];
    }
    
    //Ввод даты с клавиатуры
    static Date inputDate() {
        int d, m;
        while (true) {
            d = safeInputInt("  День (число): ");
            m = safeInputInt("  Месяц (число): ");
            Date date(d, m, 2026);
            if (date.isValid()) {
                return date;
            }
            cout << "Ошибка! Неверная дата. Попробуйте снова.\n";
        }
    }
};

//Реализация вспомогательного класса BookingPeriod, который представляет временной период бронирования номера

class BookingPeriod {
public:
    Date startDate;
    Date endDate;
    string customerName;
    
    BookingPeriod(Date start, Date end, const string& customer = "")
        : startDate(start), endDate(end), customerName(customer) {}
    
   
    bool overlaps(const BookingPeriod& other) const {
        
        if (endDate < other.startDate || other.endDate < startDate) {
            return false;
        }
        return true;
    }
    
    void print() const {
        startDate.print();
        cout << " - ";
        endDate.print();
        if (!customerName.empty()) {
            cout << " (Клиент: " << customerName << ")";
        }
    }
};

//Реализация базового абстрактного класса GlampingUnit, который представляет объект размещения для бронирования

class GlampingUnit {
private:
    static int nextId;          
    int id;                    
    string name;                
    double pricePerNight;      
    vector<BookingPeriod> bookings;  
    
public:
    GlampingUnit(const string& unitName, double price)
        : name(unitName), pricePerNight(price) {
        id = nextId;
        nextId++;
    }
    
    virtual ~GlampingUnit() {}
    
    
    virtual string getType() const = 0;      
    virtual string getFeatures() const = 0;  
    
    
    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return pricePerNight; }
    
    
    bool isAvailable(const Date& start, const Date& end) const {
        BookingPeriod newPeriod(start, end);
        for (size_t i = 0; i < bookings.size(); i++) {
            if (bookings[i].overlaps(newPeriod)) {
                return false;
            }
        }
        return true;
    }
    
    //Добавление бронирования
    bool addBooking(const Date& start, const Date& end, const string& customer) {
        if (!isAvailable(start, end)) {
            return false;
        }
        bookings.push_back(BookingPeriod(start, end, customer));
        return true;
    }
    
    //Показать все бронирования модуля
    void showBookings() const {
        if (bookings.empty()) {
            cout << "  Нет бронирований. Модуль свободен.\n";
            return;
        }
        for (size_t i = 0; i < bookings.size(); i++) {
            cout << "  " << i + 1 << ". ";
            bookings[i].print();
            cout << endl;
        }
    }
    
    //Вывод информации о модуле
    virtual void printInfo() const {
        cout << "ID: " << id << " | " << getType() << " | " << name
             << " | Цена за ночь: " << fixed << setprecision(2) << pricePerNight << " руб.\n";
        cout << "Особенности: " << getFeatures() << endl;
        cout << "Оснащение: спальное место, мебель, мини-кухня, санузел, отопление, электричество.\n";
    }
};

//Инициализация статической переменной
int GlampingUnit::nextId = 100;

//Реализация производных классов от базового GlampingUnit

//Сафари-тент
class SafariTent : public GlampingUnit {
public:
    SafariTent(const string& name, double price) : GlampingUnit(name, price) {}
    
    string getType() const override {
        return "Сафари-тент";
    }
    
    string getFeatures() const override {
        return "Большая палатка из деревянного каркаса с влагозащитным тентом";
    }
};

//Купол
class Dome : public GlampingUnit {
public:
    Dome(const string& name, double price) : GlampingUnit(name, price) {}
    
    string getType() const override {
        return "Купол";
    }
    
    string getFeatures() const override {
        return "Сферическая конструкция из ПВХ с панорамным обзором";
    }
};

//Модульный дом
class ModularHouse : public GlampingUnit {
public:
    ModularHouse(const string& name, double price) : GlampingUnit(name, price) {}
    
    string getType() const override {
        return "Модульный дом";
    }
    
    string getFeatures() const override {
        return "Миниатюрный домик в стиле гостиничного номера";
    }
};


//Реализация вспомогательного класса Service, который представляет дополнительные услуги к бронированию
class Service {
private:
    string name;
    double price;
    
public:
    Service(const string& n, double p) : name(n), price(p) {}
    
    string getName() const { return name; }
    double getPrice() const { return price; }
    
    void print() const {
        cout << "  • " << name << " - " << fixed << setprecision(2) << price << " руб.\n";
    }
};

//Реализация структуры BookingInfo, которая хранит информацию о совершённом бронировании
struct BookingInfo {
    int bookingId;
    int unitId;
    string customerName;
    string customerPhone;
    Date startDate;
    Date endDate;
    vector<string> services;
    double totalPrice;
};


//Реализация вспомогательного класса GlampingManager, который хранит информацию о совершённом бронировании
class GlampingManager {
private:
    vector<GlampingUnit*> units;        //Указатели на модули 
    vector<Service> services;           //Список услуг
    vector<BookingInfo> bookingHistory; //История бронирований
    int nextBookingId;
    
public:
    GlampingManager() : nextBookingId(1000) {
        //Создание модулей
        units.push_back(new SafariTent("Сафари-тент 'Оазис'", 5000));
        units.push_back(new Dome("Купол 'Звёздный'", 8000));
        units.push_back(new ModularHouse("Модульный дом 'Лесной уют'", 10000));
        
        //Добавление услуг
        services.push_back(Service("Питание (3-разовое)", 10000));
        services.push_back(Service("Аренда мангального набора", 2000));
        services.push_back(Service("Анимация (2 часа)", 4000));
        services.push_back(Service("SPA-процедуры", 6500));
    }
    
    ~GlampingManager() {
       
        for (size_t i = 0; i < units.size(); i++) {
            delete units[i];
        }
    }

    //Найти модуль по ID
    GlampingUnit* findUnitById(int id) {
        for (size_t i = 0; i < units.size(); i++) {
            if (units[i]->getId() == id) {
                return units[i];
            }
        }
        return NULL;
    }
    
    //Показать все модули
    void showAllUnits() {
        cout << "\n=== ВСЕ МОДУЛИ ===\n";
        for (size_t i = 0; i < units.size(); i++) {
            units[i]->printInfo();
            cout << endl;
        }
    }
    //Показать доступные модули на период
    void showAvailableUnits(const Date& start, const Date& end) {
        cout << "\n=== ДОСТУПНЫЕ МОДУЛИ НА ПЕРИОД ";
        start.print();
        cout << " - ";
        end.print();
        cout << " ===\n";
        
        bool found = false;
        for (size_t i = 0; i < units.size(); i++) {
            if (units[i]->isAvailable(start, end)) {
                cout << "ID: " << units[i]->getId() << " | " << units[i]->getType()
                     << " | " << units[i]->getName()
                     << " | Цена: " << fixed << setprecision(2) << units[i]->getPrice() << " руб.\n";
                found = true;
            }
        }
        if (!found) {
            cout << "Нет доступных модулей.\n";
        }
    }
    
    //Показать график занятости модуля
    void showUnitBookings(int id) {
        GlampingUnit* unit = findUnitById(id);
        if (unit != NULL) {
            cout << "\n=== ГРАФИК ЗАНЯТОСТИ " << unit->getName() << " ===\n";
            unit->showBookings();
        } else {
            cout << "Модуль с ID " << id << " не найден.\n";
        }
    }
    
    //Показать все услуги
    void showServices() {
        cout << "\n=== ДОСТУПНЫЕ УСЛУГИ ===\n";
        for (size_t i = 0; i < services.size(); i++) {
            cout << i + 1 << ". ";
            services[i].print();
        }
    }
    
    //Поиск услуги по имени
    Service* findServiceByName(const string& name) {
        for (size_t i = 0; i < services.size(); i++) {
            if (services[i].getName() == name) {
                return &services[i];
            }
        }
        return NULL;
    }
    
    //Поиск бронирования по телефону
    void findBookingByPhone(const string& phone) {
        cout << "\n=== ПОИСК ПО ТЕЛЕФОНУ: " << phone << " ===\n";
        
        bool found = false;
        for (size_t i = 0; i < bookingHistory.size(); i++) {
            if (bookingHistory[i].customerPhone == phone) {
                found = true;
                printBooking(bookingHistory[i]);
            }
        }
        
        if (!found) {
            cout << "Бронирование не найдено.\n";
        }
    }
    
    //Печать информации о бронировании
    void printBooking(const BookingInfo& b) {
        cout << "\n----------------------------------------\n";
        cout << "ID брони: " << b.bookingId << endl;
        cout << "Клиент: " << b.customerName << endl;
        cout << "Телефон: " << b.customerPhone << endl;
        
        GlampingUnit* unit = findUnitById(b.unitId);
        if (unit != NULL) {
            cout << "Модуль: " << unit->getName() << " (" << unit->getType() << ")\n";
        }
        
        cout << "Период: ";
        b.startDate.print();
        cout << " - ";
        b.endDate.print();
        cout << endl;
        
        if (b.services.empty()) {
            cout << "Доп. услуги: не заказаны\n";
        } else {
            cout << "Доп. услуги:\n";
            for (size_t i = 0; i < b.services.size(); i++) {
                Service* s = findServiceByName(b.services[i]);
                if (s != NULL) {
                    cout << "  • " << s->getName() << " - " << s->getPrice() << " руб.\n";
                }
            }
        }
        
        cout << "ИТОГО: " << fixed << setprecision(2) << b.totalPrice << " руб.\n";
        cout << "----------------------------------------\n";
    }
    
    //Бронирование модуля
    bool bookUnit(int id, const string& customer, const string& phone,
                  const Date& start, const Date& end, const vector<int>& serviceNumbers) {
        
        if (end < start) {
            cout << "Ошибка! Дата выезда не может быть раньше даты заезда.\n";
            return false;
        }
        
        GlampingUnit* unit = findUnitById(id);
        if (unit == NULL) {
            cout << "Модуль не найден.\n";
            return false;
        }
        
        if (!unit->isAvailable(start, end)) {
            cout << "Ошибка! Модуль занят на этот период.\n";
            return false;
        }
        
        //Расчёт стоимости
        int nights = end.day - start.day;
        if (nights <= 0) nights = 1;
        
        double stayCost = unit->getPrice() * nights;
        double servicesCost = 0;
        vector<string> selectedServiceNames;
        
        //Добавляем выбранные услуги
        for (size_t i = 0; i < serviceNumbers.size(); i++) {
            int num = serviceNumbers[i];
            if (num >= 1 && num <= (int)services.size()) {
                servicesCost += services[num - 1].getPrice();
                selectedServiceNames.push_back(services[num - 1].getName());
            }
        }
        
        double totalPrice = stayCost + servicesCost;
        
        //Добавляем бронирование
        unit->addBooking(start, end, customer);
        
        //Сохраняем в историю
        BookingInfo newBooking;
        newBooking.bookingId = nextBookingId++;
        newBooking.unitId = id;
        newBooking.customerName = customer;
        newBooking.customerPhone = phone;
        newBooking.startDate = start;
        newBooking.endDate = end;
        newBooking.services = selectedServiceNames;
        newBooking.totalPrice = totalPrice;
        bookingHistory.push_back(newBooking);
        
        //Печать чека
        cout << "\n========================================\n";
        cout << "              ЧЕК БРОНИРОВАНИЯ\n";
        cout << "========================================\n";
        cout << "ID брони: " << newBooking.bookingId << endl;
        cout << "Клиент: " << customer << endl;
        cout << "Телефон: " << phone << endl;
        cout << "Модуль: " << unit->getName() << endl;
        cout << "Период: ";
        start.print();
        cout << " - ";
        end.print();
        cout << " (" << nights << " ночей)\n";
        cout << "Проживание: " << stayCost << " руб.\n";
        if (servicesCost > 0) {
            cout << "Услуги: " << servicesCost << " руб.\n";
        }
        cout << "----------------------------------------\n";
        cout << "ИТОГО: " << totalPrice << " руб.\n";
        cout << "========================================\n";
        
        return true;
    }
    
    //Показать историю всех бронирований
    void showBookingHistory() {
        if (bookingHistory.empty()) {
            cout << "\nИстория бронирований пуста.\n";
            return;
        }
        
        cout << "\n=== ИСТОРИЯ БРОНИРОВАНИЙ ===\n";
        for (size_t i = 0; i < bookingHistory.size(); i++) {
            cout << i + 1 << ". ID: " << bookingHistory[i].bookingId
                 << " | " << bookingHistory[i].customerName
                 << " | " << bookingHistory[i].customerPhone
                 << " | " << fixed << setprecision(2) << bookingHistory[i].totalPrice << " руб.\n";
        }
    }
};

//Главная функция - МЕНЮ

int main() {
    setlocale(LC_ALL, "ru");
    
    GlampingManager manager;
    int choice;
    
    do {
        cout << "\n========================================\n";
        cout << "        УПРАВЛЕНИЕ ГЛЭМПИНГОМ\n";
        cout << "========================================\n";
        cout << "1. Показать все помещения\n";
        cout << "2. Проверить доступность на даты\n";
        cout << "3. Показать график занятости модуля\n";
        cout << "4. Забронировать помещение\n";
        cout << "5. Показать историю бронирований\n";
        cout << "6. Найти бронирование по телефону\n";
        cout << "0. Выход\n";
        
        choice = safeInputRange("Ваш выбор: ", 0, 6);
        
        switch (choice) {
            case 1:
                manager.showAllUnits();
                break;
                
            case 2: {
                cout << "\n--- ПРОВЕРКА ДОСТУПНОСТИ ---\n";
                cout << "Дата заезда:\n";
                Date start = Date::inputDate();
                cout << "Дата выезда:\n";
                Date end = Date::inputDate();
                manager.showAvailableUnits(start, end);
                break;
            }
            
            case 3: {
                manager.showAllUnits();
                int id = safeInputInt("Введите ID модуля: ");
                manager.showUnitBookings(id);
                break;
            }
            
            case 4: {
                cout << "\n--- НОВОЕ БРОНИРОВАНИЕ ---\n";
                string customer = safeInputString("Имя клиента: ");
                string phone = safeInputString("Телефон клиента: ");
                
                cout << "\nДата заезда:\n";
                Date start = Date::inputDate();
                cout << "\nДата выезда:\n";
                Date end = Date::inputDate();
                
                manager.showAvailableUnits(start, end);
                
                int id = safeInputInt("\nID модуля для брони: ");
                
                manager.showServices();
                
                cout << "\nВыберите услуги (номера через пробел, 0 - без услуг):\n";
                cout << "Пример: 1 3 4\n";
                
                vector<int> selectedServices;
                string servicesInput;
                while (true) {
                    cout << "Ваш выбор: ";
                    getline(cin, servicesInput);
                    
                    if (servicesInput == "0") {
                        break;
                    }
                    
                    stringstream ss(servicesInput);
                    int num;
                    selectedServices.clear();
                    bool valid = true;
                    
                    while (ss >> num) {
                        if (num >= 1 && num <= 4) {
                            selectedServices.push_back(num);
                        } else {
                            valid = false;
                        }
                    }
                    
                    if (valid && !selectedServices.empty()) {
                        break;
                    }
                    cout << "Ошибка! Введите номера от 1 до 4 через пробел.\n";
                }
                
                manager.bookUnit(id, customer, phone, start, end, selectedServices);
                break;
            }
            
            case 5:
                manager.showBookingHistory();
                break;
                
            case 6: {
                string phone = safeInputString("Введите телефон: ");
                manager.findBookingByPhone(phone);
                break;
            }
            
            case 0:
                cout << "До свидания!\n";
                break;
        }
    } while (choice != 0);
    
    return 0;
}

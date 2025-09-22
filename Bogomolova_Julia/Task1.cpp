#include <iostream>   //Для работы с потоками ввода-вывода
#include <cstdlib>    //Для генерации чисел
#include <ctime>      //Для работы со временем
#include <string>     //Для работы со строками
#include <stdio.h>    //Для printf

typedef long long int RUB;

// Структура для хранения финансовых данных
struct Person {
    RUB bank_account;    // Счет 
    RUB income;          // Доход
    double inflationrate;// Инфляция
    RUB insurance;       // Страховки
    RUB travel;          // Путешествия
    RUB food;            // Еда
    RUB savings;         // Накопленные деньги
    double mortgagerate; // Ставка по ипотеке (для Элис)
    RUB mortgage;        // Платеж по ипотеке (для Элис)
    //RUB totalpaid;       // Общая сумма, заплаченная расходы (для Элис)
    RUB car;             // Трата на машину
    RUB belay;           // Страховка на машину
    RUB flat;
};

struct Person alice;
//struct Person bob;

// Инициализация Элис
void alice_init() {
    alice.bank_account = 20 * 1000 * 1000;
    alice.income = 200 * 1000;
    alice.inflationrate = 0; // 1% инфляция
    alice.insurance = 5 * 1000; // Какие-то фиксированные расходы
    //alice.totalpaid = alice.insurance;
    alice.travel = 1 * 1000;
    alice.food = 15 * 1000;
    alice.car = 0;
    alice.belay = 30 * 1000;
    alice.savings = 10 * 1000;
    alice.mortgage = static_cast<RUB>( alice.income * 0.4);
    alice.mortgagerate = 0.05; // Ставка по ипотеке 5%
    alice.flat = 0;
}

void alice_print() {
    printf("На счету Элис = %lld руб.\n", alice.bank_account);
}

void alice_income(const int year, const int month) {
    if (year == 2034 && month == 2) {
        alice.income = static_cast<RUB>(alice.income * 2); // Повышение
    }
    alice.bank_account += alice.income;
}

void alice_travel(const int year, const int month) {
    if (year % 5 == 0 && month == 6) { // Добавлено условие по месяцу, чтобы отпуск не добавлялся каждый месяц в году
        alice.travel = 10 * 1000 + alice.travel; // Раз в несколько лет отпуск
        alice.bank_account -= static_cast<RUB>(alice.travel * (alice.inflationrate + 1));
    }
}

void alice_mortgage(const int year, const int month) {
    while (alice.flat <= 6000 * 1000){
    if (month == 12) {
        alice.bank_account -= static_cast<RUB>(alice.mortgage * (alice.mortgagerate+1)); // Проценты по ипотеке
        alice.flat += alice.mortgage * (alice.mortgagerate + 1);
    }
        
    alice.bank_account -= alice.mortgage; // Основной платеж по ипотеке
        alice.flat +=alice.mortgage;
}
}    
void alice_car(const int year, const int month) {
    if (year == 2040 && month == 5) {
        alice.car = 50 * 1000; // Покупка машины
        alice.bank_account -= static_cast<RUB>((alice.car + alice.belay) * (alice.inflationrate + 1));
    }
}

void alice_food(const int year, const int month) {
    if (month % 2 == 0) {
        alice.food = static_cast<RUB>((5 * 1000 + alice.food) * (alice.inflationrate + 1)); 
        // Поход в рестораны
    }
    alice.bank_account -= static_cast<RUB>(alice.food * (alice.inflationrate + 1));
}

void simulation() {
    int year = 2025;
    int month = 9;

    while (!(year == 2045 && month == 10)) {
        alice_income(year, month);
        alice_mortgage(year, month);
        alice_travel(year, month);
        alice_food(year, month);
        alice_car(year, month);
        alice.bank_account +=  alice.savings;
        month++;
 
        if (month == 13) {
            year++;
            month = 1;
        }
    }
}

int main() {
    alice_init();

    simulation();

    alice_print();

    return 0;
}

#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <random>


class HashTable
{
private:
	std::string m_password;
	int m_idNumber{};
    std::unordered_map<std::string, int> list_of_users; //хеш-таблица сохранения паролей и номеров пользователей
   
public:
    std::unordered_map<std::string, int>::iterator it = list_of_users.begin();

	HashTable() {};
	HashTable(std::string password, int idNum) : m_password{ password }, m_idNumber{ idNum }{};
    bool on_guard(std::string password, int ID_Number); //допуск по паролю
    void fillMap(std::string password, int num);   //функция заполнения хеш-таблицы
    void extractMap();                             //извлечение таблицы из файла
    std::string setPassword(std::string password); //установка пароля
    int setId(int num);                            //установка личного номера
    int countPasses(const std::string name_file);  //подсчет числа строк в текстовом файле словаря
    std::string getpass(int n);                    //Извлечение из файла паролей для загрузки в хеш-таблицу
    int getID(int n);                              //Извлечение из файла личных номеров для загрузки в хеш-таблицу
    void deleteElement(std::string passwrd);       //удаление элемента
    void print();                                  //вывод хеш-таблицы на экран
    ~HashTable() {};

};

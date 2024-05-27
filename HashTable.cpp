#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <Windows.h>
#include <fstream>
#include <ios>
#include <algorithm>
#include "HashTable.h"


void HashTable::print() //Вывод хеш-таблицы на консоль. Используется только при тестировании программы
{
    for (it = list_of_users.begin(); it != list_of_users.end(); ++it)
    {
        std::cout << it->first << " - " << it->second<<'\n';
    }
}

void HashTable::fillMap(std::string password, int num) //заполнение таблицы при регистрации пользователя
{
    list_of_users.insert({ password, num });
    std::ofstream out("hashTable.txt", std::ios::app);

    for (it = list_of_users.begin(); it != list_of_users.end(); ++it)
    {
        std::cout << "Ваш пароль: " << it->first << "   Ваш личный номер: " << it->second << '\n';
        std::cout << '\n';
        out << it->first << " " << it->second << '\n';
    }
}

void HashTable::extractMap() //загрузка в таблицу данных, сохраненных в текстовом файле
{
    int n = countPasses("hashTable.txt") - 1;
    for (int i = 0; i < n; ++i)
    {
        list_of_users.insert({ getpass(i), getID(i) });
    }
    std::cout << '\n';
    if (list_of_users.empty() == 0)
    {
        return;
    }
}

std::string HashTable::setPassword(std::string password)
{
    m_password = password;
    return m_password;
}

int HashTable::setId(int num)
{
    m_idNumber = num;
    return num;
}

int HashTable::countPasses(const std::string name_file) //подсчет числа строк в файле 
{
    int numPasses = 0;
    std::ifstream input_file("hashTable.txt");
    std::string s;
    while (!input_file.eof())
    {
        std::getline(input_file, s);
        ++numPasses;
    }
    input_file.close();
    return numPasses;
}

int sizemass = 0;
std::vector<std::string> arr_pass(sizemass); //вспомогательный массив вывода паролей из текстового файла
int sizemass2 = 0;
std::vector<int> arr_id(sizemass2); //вспомогателльный массив вывода личных номеров

std::string HashTable::getpass(int n) //функция извлечения из файла списка паролей для загрузки хеш-таблицы
{
    std::string line;
    std::string str_pass;
    std::ifstream in("hashTable.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            str_pass = line.substr(0, 8); //извлекаем из строки подстроку пароля
            arr_pass.push_back(str_pass); //загружаем во вспомогательный массив arr_pass
            ++sizemass;
        }
    }
    in.close();     // закрываем файл
    return arr_pass[n];
}

int HashTable::getID(int n) //функция извлечения из файла личных номеров для загрузки хеш-таблицы при запуске программы
{
    std::string line;
    std::string id;
    std::ifstream inn("hashTable.txt"); // окрываем файл для чтения
    if (inn.is_open())
    {
        while (std::getline(inn, line))
        {
            id = line.substr(9);        //извлекаем из строки подстроку личного номера  
            arr_id.push_back(stoi(id)); //Преобразуем подстроку в целое и загружаем в arr_id
            ++sizemass2;
        }
    }
    inn.close();     // закрываем файл
    return arr_id[n];
}

bool HashTable::on_guard(std::string password, int ID_Number) //допуск пользователя в чат по паролю
{
    int it_second{};
    it = list_of_users.find(password);
    if (it != list_of_users.end())
    {
        it_second = it->second;
        if (it_second == ID_Number)
        {
            return true;
        }
        else
        {
            std::cout << "Несоответствие ID-номера и пароля" << '\n';
            return false;
        }
    }
    else
    {
        std::cout << "Неверный пароль" << '\n';
        return false;
    }
}

void HashTable::deleteElement(std::string passwrd) //удаление данных пользователя из хеш-таблицы
{
    list_of_users.erase(passwrd);
    std::ofstream out("hashTable.txt");
    for (it = list_of_users.begin(); it != list_of_users.end(); ++it)
    {
        out << it->first << " " << it->second << '\n';
    }
}

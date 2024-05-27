#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ios>
#include "User.h"


User::User() {}
User::User(int ID, std::string& family, std::string& name, std::string& patr, std::string& phone)
    : m_ID{ ID }, m_family{ family }, m_name{ name }, m_patr{ patr }, m_phone{ phone } {}
User::~User() {}


User user;                      //объявляем экземпляр класса

void User::setUsers(int number, std::string tel_number)
{
    std::cout << " Фамилия: ";
    std::cin >> m_family;
    std::cout << "     Имя: ";
    std::cin >> m_name;
    std::cout << "Отчество: ";
    std::cin >> m_patr;
    m_phone = tel_number;
    m_ID = number;

    std::cout << '\n';
}
void User::getUsers() //вывод пользователя на консоль при регистрации
{
    std::cout << '\n';
    std::cout << "________________________________________________________________________________________" << '\n';
    std::cout << " Личный номер: " << m_ID << '\n';
    std::cout << "      Фамилия: " << m_family << '\n';
    std::cout << "          Имя: " << m_name << '\n';
    std::cout << "     Отчество: " << m_patr << '\n';
    std::cout << "      Телефон: " << m_phone << '\n';
    std::cout << "________________________________________________________________________________________" << '\n';
}

std::ostream& operator<< (std::ostream& out, const User& user)
{
    out << user.m_ID << " " << user.m_family << " " << user.m_name << " " << user.m_patr << " " << " " << " " << user.m_phone; // причем тип функции также ссылочный, и воз-вращает параметр out в качестве возвращаемого типа
    return out;
}
std::istream& operator>> (std::istream& in, User& user)
{
    in >> user.m_ID;
    in >> user.m_family;
    in >> user.m_name;
    in >> user.m_patr;
    in >> user.m_phone;
    return in;
}

void User::getListUsers() //просмотр пользователем списка контактов
{
    std::cout << m_ID << " " << m_family << " " << m_name << " " << m_patr << " " << m_phone << '\n';
}

std::string User::getOneUserFromList() //извлечение данных пользователя одной строкой для функции getOneUser(int id_number) 
{
    std::string xx;
    xx = m_family + "_" + m_name + "_" + m_patr + "_" + m_phone;
    return xx;
}

int User::getIDnumber()
{
   return m_ID;
}

std::string User::getFamily()
{
    return m_family;
}

void User::FillArray(int number, std::string tel_number) //функция создания списка пользователей
{
    user.setUsers(number, tel_number);
    arr.push_back(user);
    for (int i = 0; i < (end(arr) - begin(arr)); ++i) //выводим созданный массив на консоль
    {
        arr[i].getUsers();
    }
    std::ofstream out("listOfUsers.txt", std::ios::app); //сохраняем массив в текстовый файл
    for (int i = 0; i < (end(arr) - begin(arr)); ++i)
    {
        out << arr[i] << '\n';
    }
    std::cout << '\n';
}

int User::Get_records_in_file(const std::string name_file) //Подсчет числа строк в файле списка пользователей                                                         */
{
    int count = 0;
    std::ifstream input_file("listOfUsers.txt");
    std::string s;
    while (!input_file.eof())
    {
        getline(input_file, s);
        ++count;
    }
    input_file.close();
    return count;
}

void User::DeleteEmptyLines(std::string file) //Удаление пустых строк из файла словаря
{
    std::ifstream in(file);
    std::string line, text;
    while (std::getline(in, line))
        if (!(line.empty() || line.find_first_not_of(' ') == std::string::npos))
        {
            text += line + "\n";
        }
    in.close();
    std::ofstream out(file);
    out << text;
}

void User::getListUsers_from_file() //функция извлечения списка пользователей из файла
{
    std::cout << "СПИСОК ПОЛЬЗОВАТЕЛЕЙ ЧАТА: " << '\n';
    std::cout << '\n';
    std::vector<User> arr(User::Get_records_in_file("listOfUsers.txt"));
    std::ifstream input_file("listOfUsers.txt");
    for (int i = 0; i < (Get_records_in_file("listOfUsers.txt")); ++i)
    {
        input_file >> arr[i];
    }
    input_file.close();
    for (int i = 0; i < (Get_records_in_file("listOfUsers.txt"))-1; ++i)
    {
        arr[i].getListUsers();
    }
}

std::string User::getOneUser(int id_number) //функция извлечения пользователя по личному номеру для вставки в сообщения
{
    
    std::vector<User> arr(User::Get_records_in_file("listOfUsers.txt"));
    std::ifstream input_file("listOfUsers.txt");
    for (int i = 0; i < (Get_records_in_file("listOfUsers.txt")); ++i)
    {
        input_file >> arr[i];
    }
    input_file.close();
    for (int i = 0; i < (Get_records_in_file("listOfUsers.txt")) - 1; ++i)
    {
        if (id_number == arr[i].getIDnumber())
        {
            std::string xxy;
            xxy=arr[i].getOneUserFromList();
            return xxy;
        }
    }
}

void User::getFamilies() //функция поиска поьзователей по фамилии
{
    std::vector<User> arr(User::Get_records_in_file("listOfUsers.txt"));
    std::ifstream input_file("listOfUsers.txt");
    std::string str;
    std::cout << "Введите фамилию искомого пользователя. Если в ответ ничего не выведется, " << '\n';
    std::cout << "то такой пользователь в списке отсутствует: "<<'\n';
    std::cin >> str;
    for (int i = 0; i < (Get_records_in_file("listOfUsers.txt")); ++i)
    {
        input_file >> arr[i];
    }
    input_file.close();
    for (int i = 0; i < (Get_records_in_file("listOfUsers.txt")) - 1; ++i)
    {
        if (str == arr[i].getFamily())
        {
            arr[i].getListUsers();
        }
    }
}

void User::deleteUser(int IDnumber) //функция удаления пользователя из списка контактов
{
    std::vector<User> arr(User::Get_records_in_file("listOfUsers.txt"));
    std::vector<User>::iterator it = arr.begin();
    std::ifstream input_file("listOfUsers.txt");
    int str = IDnumber;
    for (int i = 0; i < (Get_records_in_file("listOfUsers.txt")-1); ++i)
    {
        input_file >> arr[i];
    }
    for (int i = 0; i < (Get_records_in_file("listOfUsers.txt")-1); ++i)
    {
        if (str == arr[i].getIDnumber())
        {
            std::vector<User>::iterator it = arr.begin() + i;
            arr.erase(it);
        }
    }
    std::ofstream out("listOfUsers.txt"); //сохраняем массив в текстовый файл
    for (int i = 0; i < (end(arr) - begin(arr)-1); ++i)
    {
        out << arr[i] << '\n';
    }
    input_file.close();
}

#pragma once
#include <iostream>
#include<string>

class User
{
private:
    int m_ID{};             //личный номер
    std::string m_family;   //Фамилия
    std::string m_name;     //Имя
    std::string m_patr;     //Отчество
    std::string m_phone;    //Телефон

public:
    User();
    User(int ID, std::string& family, std::string& name, std::string& patr, std::string& phone);
    
    std::vector<User> arr;    //массив экземпляров класса User

    void setUsers(int number, std::string tel_number);
    void getUsers(); //вывод пользователя на консоль при регистрации
    void getListUsers();//просмотр пользователем списка контактов
    std::string getOneUserFromList(); //извлечение сводных данных пользователя
    int getIDnumber(); //извлечение личного номера
    std::string getFamily(); //извлечение фамилии
    void FillArray(int number, std::string tel_number); //регистрация нового пользователя
    static int Get_records_in_file(const std::string name_file);
    void getListUsers_from_file(); //функция извлечения списка пользователей из файла
    static std::string getOneUser(int id_number); //функция извлечения данных пользователя по личному номеру 
                                                  //для вставки в сообщения
    void getFamilies(); //поиск по фамилии
    void deleteUser(int IDnumber); //функция удаления пользователя из списка контактов
    void DeleteEmptyLines(std::string file); //Удаление пустых строк из файла словаря
    friend std::ostream& operator<< (std::ostream& out, const User& user);
    friend std::istream& operator>> (std::istream& in, User& user);
    ~User();
};

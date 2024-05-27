#pragma once
#include <iostream>

class HashTable;
class User;
class AllMessages
{
    std::string am_time;   //переменная текущего времени
    int am_idn_of{};       //переменная личного номера отправителя
    std::string am_nameOf; //переменная имени отправитела
    int am_idn_to{};       //переменная личного номера получателя
    std::string am_nameTo; //переменная имени получателя
    std::string am_text;   //переменная текста сообщения
public:
    AllMessages();
    AllMessages(std::string& time, int m_idn_of, std::string& nameOf, int m_idn_to, std::string& nameTo, std::string& text);
    std::string Time(); //получение текущего времени
    void setData_toAll(int id_number_of); //установка данных сообщений для всех
    void getData_toAll(); //получение и вывод введенных в массив данных
    void createMessages_toAll(int id_number_of); //создание сообщений для всех
    static int countRecords_All(const std::string name_file); // Подсчитываем число строк в файле общих сообщений
    void getMessages_toAll(); //извлечение общих сообщений
    int get_idn_of(); //извлечение  личного номера отправителя
    int get_idn_to(); //извлечение личного номера получателя
    void read_Messages_toAll(); //чтение общих сообщений
    friend std::ostream& operator<< (std::ostream& out, const  AllMessages& z);
    friend std::istream& operator>> (std::istream& in, AllMessages& z);
    ~AllMessages();
};
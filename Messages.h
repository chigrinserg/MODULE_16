#pragma once
#include <iostream>

class HashTable;
class User;
class Message
{
    std::string m_time;   //переменная текущего времени
    int m_idn_of{};       //переменная личного номера отправителя
    std::string m_nameOf; //переменная имени отправитела
    int m_idn_to{};       //переменная личного номера получателя
    std::string m_nameTo; //переменная имени получателя
    std::string m_text;   //переменная текста сообщения
public:
    Message();
    Message(std::string& time, int m_idn_of, std::string& nameOf, int m_idn_to, std::string& nameTo, std::string& text);
    std::string Time(); //получение текущего времени
    std::vector<Message> array; //массив записи сообщений
    void setData(int id_number_of, int id_number_in);//установка данных персональных сообщений
    void getData(); //получение и вывод введенных в массив данных
    void createMessages(int id_number_of, int id_number_in); //создание персональных сообщений
    void createMessages_toAll(int id_number_of); //создание сообщений для всех
    static int countRecords(const std::string name_file); //подсчет числа строк в текстовом файле
    int get_idn_of(); //извлечение  личного номера отправителя
    int get_idn_to(); //извлечение личного номера получателя
    void readPersonalMessages(int ID_Number); //чтение персональных сообщений
    void read_Messages_toAll(); //чтение общих сообщений
    friend std::ostream& operator<< (std::ostream& out, const Message& z);
    friend std::istream& operator>> (std::istream& in, Message& z);
    ~Message();
};
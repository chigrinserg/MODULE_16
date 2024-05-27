#define _CRT_SECURE_NO_WARNINGS //Введено для предотвращения сбоя в функции localtime(&timep)
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include "Messages.h"
#include "User.h"

Message::Message() {};
Message::Message(std::string& time, int idn_of, std::string& nameOf, int idn_to, std::string& nameTo, std::string& text)
{
    m_time = time;
    m_idn_of = idn_of;
    m_nameOf = nameOf;
    m_idn_to = idn_to;
    m_nameTo = nameTo;
    m_text = text;
}

Message::~Message() {};

std::string Message::Time() //Функция получения текущего времени
{
    time_t timep;
    struct tm* p;
    time(&timep); // Получаем, сколько секунд прошло с 1970 года, и сохраняем его в timep типа time_t
    p = localtime(&timep);// Используем localtime для преобразования количества секунд в структуру struct tm
    int day = p->tm_mday;
    int mon = 1 + p->tm_mon;
    int year = 1900 + p->tm_year;
    int hour = p->tm_hour;
    int min = p->tm_min;
    int sec = p->tm_sec;
    std::string currentTime = (std::to_string(day) + "." + std::to_string(mon) + "." + std::to_string(year) + "_" + std::to_string(hour) + ":"
        + std::to_string(min) + ":" + std::to_string(sec));
    return currentTime;
}

std::ostream& operator<< (std::ostream& out, const Message& z)
{
    out << z.m_time << " " << z.m_idn_of << " " << " " << z.m_nameOf << " " << z.m_idn_to << " " << z.m_nameTo << " " << z.m_text;
    return out;
}

std::istream& operator>> (std::istream& in, Message& z)
{
    in >> z.m_time;
    in >> z.m_idn_of;
    in >> z.m_nameOf;
    in >> z.m_idn_to;
    in >> z.m_nameTo;
    in >> z.m_text;
    return in;
}

void Message::setData(int id_number_of, int id_number_in)  //Установка данных сообщения
{
    m_time = Time();                           //вставка в сообщение времени отправки
    m_idn_of = id_number_of;
    m_nameOf = User::getOneUser(id_number_of); //вставка данных отправителя
    m_idn_to = id_number_in;
    m_nameTo = User::getOneUser(id_number_in); //вставка данных получателя
    std::cout << "  Сообщение: ";
    std::getline(std::cin >> std::ws, m_text); //обеспечивает ввод  текста с пробелами
    for (size_t i = static_cast<int>(m_text.find(' ')); i != -1; i = m_text.find(' ')) m_text.replace(i, 1, "_");
    /*Данная конструкция предназначена для замены в текстах сообщений пробелов символами подчеркивания.
    Приходится делать так, поскольку при загрузке строк в массив элементов класса функция getline() строки с
    пробелами не выводит. А при загрузке строк в массив типа std::string все пробелы выводятся нормально*/
}

void Message::getData() //Получение данных сообщения
{
    std::cout << "  Отправлено: " << m_time << '\n';
    std::cout << "     От кого: "<< m_idn_of <<" " << m_nameOf << '\n';
    std::cout << "        Кому: "<< m_idn_to<<" "<< m_nameTo << '\n';
    std::cout << "   СООБЩЕНИЕ: " << m_text << '\n';
    std::cout << '\n';
}

Message message; //Объявление экземпляра класса для использования в функции создания и сохранения сообщений

int Message::get_idn_of() //извлечение номера отправителя
{
    return m_idn_of;
}

int Message::get_idn_to() //извлечение номера получателя
{
    return m_idn_to;
}

void Message::createMessages(int id_number_of, int id_number_in) //ФУНКЦИЯ СОЗДАНИЯ ЛИЧНЫХ СООБЩЕНИЙ
{
    int size{ 1 };
    std::vector<Message> array(size); //массив сохранения сообщений
    for (int i = 0; i < size; ++i)
    {
        array[i].setData(id_number_of, id_number_in);
    }
    for (int j = 0; j < size; ++j)
    {
        int a{};
        std::cout << "Еще одно сообщение? Да - 1, Нет - 0" << '\n';
        std::cin >> a;
        if (a == 1)
        {
            ++size;
            message.setData(id_number_of, id_number_in);
            array.push_back(message);
        }
        else
            break;
    }
    for (int i = 0; i < (end(array) - begin(array)); ++i)
    {
        array[i].getData();
    }

    std::ofstream out("Messages.txt", std::ios::app); //сохраняем массив в текстовый файл
    for (int i = 0; i < (end(array) - begin(array)); ++i)
    {
        out << array[i] << '\n';
    }
}

int Message::countRecords(const std::string name_file) // Подсчитываем число строк в файле
{
    int count = 0;
    std::ifstream input_file("Messages.txt");
    std::string s;
    while (!input_file.eof())
    {
        getline(input_file, s);
        ++count;
    }
    input_file.close();
    return count;
}

void Message::readPersonalMessages(int ID_Number) //функция чтения персональных сообщений
{
    std::vector<Message>array(Message::countRecords("Messages.txt"));
    std::ifstream input_file("Messages.txt", std::ios::in);
    for (int i = 0; i < (Message::countRecords("Messages.txt")); ++i)
    {
        input_file >> array[i];
    }
    input_file.close();

    for (int i = 0; i < (Message::countRecords("Messages.txt"))-1; ++i)
    {
        /*-1 вводится для предотвращения вывода пустых сообщений, созданных конструктором по умолчанию
        при чтении последней пустой строки*/
        /*Нижеследующим условием предотвращается чтение пользователем не ему адресованных
        личных сообщений:*/
        if (ID_Number == array[i].get_idn_of() || ID_Number == array[i].get_idn_to())
        {
            array[i].getData();
        }
    }
    

}

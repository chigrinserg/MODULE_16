#define _CRT_SECURE_NO_WARNINGS //������� ��� �������������� ���� � ������� localtime(&timep)
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include "AllMessages.h"
#include "User.h"

AllMessages::AllMessages() {};
AllMessages::AllMessages(std::string& time, int idn_of, std::string& nameOf, int idn_to, std::string& nameTo, std::string& text)
{
    am_time = time;
    am_idn_of = idn_of;
    am_nameOf = nameOf;
    am_nameTo = nameTo;
    am_text = text;
}

AllMessages::~AllMessages() {};

std::string  AllMessages::Time() //������� ��������� �������� �������
{
    time_t timep;
    struct tm* p;
    time(&timep); // ��������, ������� ������ ������ � 1970 ����, � ��������� ��� � timep ���� time_t
    p = localtime(&timep);// ���������� localtime ��� �������������� ���������� ������ � ��������� struct tm
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

std::ostream& operator<< (std::ostream& out, const  AllMessages& z)
{
    out << z.am_time << " " << z.am_idn_of << " " << " " << z.am_nameOf << " " << z.am_nameTo << " " << z.am_text;
    return out;
}

std::istream& operator>> (std::istream& in, AllMessages& z)
{
    in >> z.am_time;
    in >> z.am_idn_of;
    in >> z.am_nameOf;
    in >> z.am_nameTo;
    in >> z.am_text;
    return in;
}


void  AllMessages::setData_toAll(int id_number_of) //��������� ������ ���������
{
    am_time = Time();                            //������� ������� �����������
    am_idn_of = id_number_of;
    am_nameOf = User::getOneUser(id_number_of);  //��������� ������ �����������
    am_nameTo = "����";
    std::cout << "  ���������: ";
    std::getline(std::cin >> std::ws, am_text);
    for (size_t i = static_cast<int>(am_text.find(' ')); i != -1; i = am_text.find(' ')) am_text.replace(i, 1, "_");
}


void  AllMessages::getData_toAll() //���������� ������ ���������
{
    std::cout << "  ����������: " << am_time << '\n';
    std::cout << "     �� ����: " << am_idn_of << " " << am_nameOf << '\n';
    std::cout << "        ����: " << am_nameTo << '\n';
    std::cout << "   ���������: " << am_text << '\n';
    std::cout << '\n';
}

AllMessages am;

int AllMessages::get_idn_of() //���������� �������� ������ �����������
{
    return am_idn_of;
}

int AllMessages::get_idn_to() //���������� ������� ������ ����������
{
    return am_idn_to;
}

void AllMessages::createMessages_toAll(int id_number_of) //������� �������� ��������� � ���������� �� � ����
{
    int size2{ 1 };
    std::vector<AllMessages> array_all(size2);

    for (int i = 0; i < size2; ++i)
    {
        array_all[i].setData_toAll(id_number_of);
    }
    for (int j = 0; j < size2; ++j)
    {
        int a{};
        std::cout << "���������? �� - 1, ��� - 0" << '\n';
        std::cin >> a;
        if (a == 1)
        {
            ++size2;
            am.setData_toAll(id_number_of);
            array_all.push_back(am);
        }
        else
            break;
    }
    for (int i = 0; i < (end(array_all) - begin(array_all)); ++i)
    {
        array_all[i].getData_toAll();
    }
    std::ofstream out("AllMessages.txt", std::ios::app); //��������� ������ � ��������� ����
    for (int i = 0; i < (end(array_all) - begin(array_all)); ++i)
    {
        out << array_all[i] << '\n';
    }
}

int AllMessages::countRecords_All(const std::string name_file) // ������������ ����� ����� � �����
{
    int count = 0;
    std::ifstream input_file("AllMessages.txt");
    std::string s;
    while (!input_file.eof())
    {
        getline(input_file, s);
        ++count;
    }
    input_file.close();
    return count;
}

void AllMessages::getMessages_toAll() //���������� ��������� �� �����
{
    int sise = AllMessages::countRecords_All("AllMessages.txt");
    std::vector<AllMessages>array(AllMessages::countRecords_All("AllMessages.txt"));
    std::ifstream input_file("AllMessages.txt", std::ios::in);
    for (int i = 0; i < (AllMessages::countRecords_All("AllMessages.txt")); ++i)
    {
        input_file >> array[i];
    }
    input_file.close();

    for (int i = 0; i < (AllMessages::countRecords_All("AllMessages.txt")) - 1; ++i)
    {
        array[i].getData_toAll();
    }
}

void AllMessages::read_Messages_toAll() //����� ��������� �� �����
{
    std::vector<AllMessages>array(AllMessages::countRecords_All("AllMessages.txt"));
    std::ifstream input_file("AllMessages.txt", std::ios::in);
    for (int i = 0; i < (AllMessages::countRecords_All("AllMessages.txt")); ++i)
    {
        input_file >> array[i];
    }
    input_file.close();

    for (int i = 0; i < (AllMessages::countRecords_All("AllMessages.txt"))-1; ++i)
    {
        array[i].getData_toAll();
    }
    /*-1 �������� ��� �������������� ������ ������ ���������, ��������� ������������� �� ���������
    ��� ������ ��������� ������ ������*/
}

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


User user;                      //��������� ��������� ������

void User::setUsers(int number, std::string tel_number)
{
    std::cout << " �������: ";
    std::cin >> m_family;
    std::cout << "     ���: ";
    std::cin >> m_name;
    std::cout << "��������: ";
    std::cin >> m_patr;
    m_phone = tel_number;
    m_ID = number;

    std::cout << '\n';
}
void User::getUsers() //����� ������������ �� ������� ��� �����������
{
    std::cout << '\n';
    std::cout << "________________________________________________________________________________________" << '\n';
    std::cout << " ������ �����: " << m_ID << '\n';
    std::cout << "      �������: " << m_family << '\n';
    std::cout << "          ���: " << m_name << '\n';
    std::cout << "     ��������: " << m_patr << '\n';
    std::cout << "      �������: " << m_phone << '\n';
    std::cout << "________________________________________________________________________________________" << '\n';
}

std::ostream& operator<< (std::ostream& out, const User& user)
{
    out << user.m_ID << " " << user.m_family << " " << user.m_name << " " << user.m_patr << " " << " " << " " << user.m_phone; // ������ ��� ������� ����� ���������, � ���-������� �������� out � �������� ������������� ����
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

void User::getListUsers() //�������� ������������� ������ ���������
{
    std::cout << m_ID << " " << m_family << " " << m_name << " " << m_patr << " " << m_phone << '\n';
}

std::string User::getOneUserFromList() //���������� ������ ������������ ����� ������� ��� ������� getOneUser(int id_number) 
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

void User::FillArray(int number, std::string tel_number) //������� �������� ������ �������������
{
    user.setUsers(number, tel_number);
    arr.push_back(user);
    for (int i = 0; i < (end(arr) - begin(arr)); ++i) //������� ��������� ������ �� �������
    {
        arr[i].getUsers();
    }
    std::ofstream out("listOfUsers.txt", std::ios::app); //��������� ������ � ��������� ����
    for (int i = 0; i < (end(arr) - begin(arr)); ++i)
    {
        out << arr[i] << '\n';
    }
    std::cout << '\n';
}

int User::Get_records_in_file(const std::string name_file) //������� ����� ����� � ����� ������ �������������                                                         */
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

void User::DeleteEmptyLines(std::string file) //�������� ������ ����� �� ����� �������
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

void User::getListUsers_from_file() //������� ���������� ������ ������������� �� �����
{
    std::cout << "������ ������������� ����: " << '\n';
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

std::string User::getOneUser(int id_number) //������� ���������� ������������ �� ������� ������ ��� ������� � ���������
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

void User::getFamilies() //������� ������ ������������ �� �������
{
    std::vector<User> arr(User::Get_records_in_file("listOfUsers.txt"));
    std::ifstream input_file("listOfUsers.txt");
    std::string str;
    std::cout << "������� ������� �������� ������������. ���� � ����� ������ �� ���������, " << '\n';
    std::cout << "�� ����� ������������ � ������ �����������: "<<'\n';
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

void User::deleteUser(int IDnumber) //������� �������� ������������ �� ������ ���������
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
    std::ofstream out("listOfUsers.txt"); //��������� ������ � ��������� ����
    for (int i = 0; i < (end(arr) - begin(arr)-1); ++i)
    {
        out << arr[i] << '\n';
    }
    input_file.close();
}

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <Windows.h>
#include <fstream>
#include <ios>
#include <algorithm>
#include "HashTable.h"


void HashTable::print() //����� ���-������� �� �������. ������������ ������ ��� ������������ ���������
{
    for (it = list_of_users.begin(); it != list_of_users.end(); ++it)
    {
        std::cout << it->first << " - " << it->second<<'\n';
    }
}

void HashTable::fillMap(std::string password, int num) //���������� ������� ��� ����������� ������������
{
    list_of_users.insert({ password, num });
    std::ofstream out("hashTable.txt", std::ios::app);

    for (it = list_of_users.begin(); it != list_of_users.end(); ++it)
    {
        std::cout << "��� ������: " << it->first << "   ��� ������ �����: " << it->second << '\n';
        std::cout << '\n';
        out << it->first << " " << it->second << '\n';
    }
}

void HashTable::extractMap() //�������� � ������� ������, ����������� � ��������� �����
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

int HashTable::countPasses(const std::string name_file) //������� ����� ����� � ����� 
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
std::vector<std::string> arr_pass(sizemass); //��������������� ������ ������ ������� �� ���������� �����
int sizemass2 = 0;
std::vector<int> arr_id(sizemass2); //���������������� ������ ������ ������ �������

std::string HashTable::getpass(int n) //������� ���������� �� ����� ������ ������� ��� �������� ���-�������
{
    std::string line;
    std::string str_pass;
    std::ifstream in("hashTable.txt"); // �������� ���� ��� ������
    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            str_pass = line.substr(0, 8); //��������� �� ������ ��������� ������
            arr_pass.push_back(str_pass); //��������� �� ��������������� ������ arr_pass
            ++sizemass;
        }
    }
    in.close();     // ��������� ����
    return arr_pass[n];
}

int HashTable::getID(int n) //������� ���������� �� ����� ������ ������� ��� �������� ���-������� ��� ������� ���������
{
    std::string line;
    std::string id;
    std::ifstream inn("hashTable.txt"); // �������� ���� ��� ������
    if (inn.is_open())
    {
        while (std::getline(inn, line))
        {
            id = line.substr(9);        //��������� �� ������ ��������� ������� ������  
            arr_id.push_back(stoi(id)); //����������� ��������� � ����� � ��������� � arr_id
            ++sizemass2;
        }
    }
    inn.close();     // ��������� ����
    return arr_id[n];
}

bool HashTable::on_guard(std::string password, int ID_Number) //������ ������������ � ��� �� ������
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
            std::cout << "�������������� ID-������ � ������" << '\n';
            return false;
        }
    }
    else
    {
        std::cout << "�������� ������" << '\n';
        return false;
    }
}

void HashTable::deleteElement(std::string passwrd) //�������� ������ ������������ �� ���-�������
{
    list_of_users.erase(passwrd);
    std::ofstream out("hashTable.txt");
    for (it = list_of_users.begin(); it != list_of_users.end(); ++it)
    {
        out << it->first << " " << it->second << '\n';
    }
}

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
    std::unordered_map<std::string, int> list_of_users; //���-������� ���������� ������� � ������� �������������
   
public:
    std::unordered_map<std::string, int>::iterator it = list_of_users.begin();

	HashTable() {};
	HashTable(std::string password, int idNum) : m_password{ password }, m_idNumber{ idNum }{};
    bool on_guard(std::string password, int ID_Number); //������ �� ������
    void fillMap(std::string password, int num);   //������� ���������� ���-�������
    void extractMap();                             //���������� ������� �� �����
    std::string setPassword(std::string password); //��������� ������
    int setId(int num);                            //��������� ������� ������
    int countPasses(const std::string name_file);  //������� ����� ����� � ��������� ����� �������
    std::string getpass(int n);                    //���������� �� ����� ������� ��� �������� � ���-�������
    int getID(int n);                              //���������� �� ����� ������ ������� ��� �������� � ���-�������
    void deleteElement(std::string passwrd);       //�������� ��������
    void print();                                  //����� ���-������� �� �����
    ~HashTable() {};

};

#pragma once
#include <iostream>
#include<string>

class User
{
private:
    int m_ID{};             //������ �����
    std::string m_family;   //�������
    std::string m_name;     //���
    std::string m_patr;     //��������
    std::string m_phone;    //�������

public:
    User();
    User(int ID, std::string& family, std::string& name, std::string& patr, std::string& phone);
    
    std::vector<User> arr;    //������ ����������� ������ User

    void setUsers(int number, std::string tel_number);
    void getUsers(); //����� ������������ �� ������� ��� �����������
    void getListUsers();//�������� ������������� ������ ���������
    std::string getOneUserFromList(); //���������� ������� ������ ������������
    int getIDnumber(); //���������� ������� ������
    std::string getFamily(); //���������� �������
    void FillArray(int number, std::string tel_number); //����������� ������ ������������
    static int Get_records_in_file(const std::string name_file);
    void getListUsers_from_file(); //������� ���������� ������ ������������� �� �����
    static std::string getOneUser(int id_number); //������� ���������� ������ ������������ �� ������� ������ 
                                                  //��� ������� � ���������
    void getFamilies(); //����� �� �������
    void deleteUser(int IDnumber); //������� �������� ������������ �� ������ ���������
    void DeleteEmptyLines(std::string file); //�������� ������ ����� �� ����� �������
    friend std::ostream& operator<< (std::ostream& out, const User& user);
    friend std::istream& operator>> (std::istream& in, User& user);
    ~User();
};

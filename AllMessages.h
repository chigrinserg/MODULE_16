#pragma once
#include <iostream>

class HashTable;
class User;
class AllMessages
{
    std::string am_time;   //���������� �������� �������
    int am_idn_of{};       //���������� ������� ������ �����������
    std::string am_nameOf; //���������� ����� �����������
    int am_idn_to{};       //���������� ������� ������ ����������
    std::string am_nameTo; //���������� ����� ����������
    std::string am_text;   //���������� ������ ���������
public:
    AllMessages();
    AllMessages(std::string& time, int m_idn_of, std::string& nameOf, int m_idn_to, std::string& nameTo, std::string& text);
    std::string Time(); //��������� �������� �������
    void setData_toAll(int id_number_of); //��������� ������ ��������� ��� ����
    void getData_toAll(); //��������� � ����� ��������� � ������ ������
    void createMessages_toAll(int id_number_of); //�������� ��������� ��� ����
    static int countRecords_All(const std::string name_file); // ������������ ����� ����� � ����� ����� ���������
    void getMessages_toAll(); //���������� ����� ���������
    int get_idn_of(); //����������  ������� ������ �����������
    int get_idn_to(); //���������� ������� ������ ����������
    void read_Messages_toAll(); //������ ����� ���������
    friend std::ostream& operator<< (std::ostream& out, const  AllMessages& z);
    friend std::istream& operator>> (std::istream& in, AllMessages& z);
    ~AllMessages();
};
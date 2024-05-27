#pragma once
#include <iostream>

class HashTable;
class User;
class Message
{
    std::string m_time;   //���������� �������� �������
    int m_idn_of{};       //���������� ������� ������ �����������
    std::string m_nameOf; //���������� ����� �����������
    int m_idn_to{};       //���������� ������� ������ ����������
    std::string m_nameTo; //���������� ����� ����������
    std::string m_text;   //���������� ������ ���������
public:
    Message();
    Message(std::string& time, int m_idn_of, std::string& nameOf, int m_idn_to, std::string& nameTo, std::string& text);
    std::string Time(); //��������� �������� �������
    std::vector<Message> array; //������ ������ ���������
    void setData(int id_number_of, int id_number_in);//��������� ������ ������������ ���������
    void getData(); //��������� � ����� ��������� � ������ ������
    void createMessages(int id_number_of, int id_number_in); //�������� ������������ ���������
    void createMessages_toAll(int id_number_of); //�������� ��������� ��� ����
    static int countRecords(const std::string name_file); //������� ����� ����� � ��������� �����
    int get_idn_of(); //����������  ������� ������ �����������
    int get_idn_to(); //���������� ������� ������ ����������
    void readPersonalMessages(int ID_Number); //������ ������������ ���������
    void read_Messages_toAll(); //������ ����� ���������
    friend std::ostream& operator<< (std::ostream& out, const Message& z);
    friend std::istream& operator>> (std::istream& in, Message& z);
    ~Message();
};
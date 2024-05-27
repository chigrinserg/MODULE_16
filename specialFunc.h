#pragma once
#include <iostream>
#include <string>
#include <random>
#include <conio.h>

std::string random_string(std::size_t length) 
/*Функция-генератор случайных комбинаций символов. Длина комбинации устанавливается
 параметром length. Получено с сайта /*https://inversepalindrome.com/blog/how-to-create-a-random-string-in-cpp  */
{
    const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);
    std::string random_string;
    for (int i = 0; i < length; ++i)
    {
        random_string += CHARACTERS[distribution(generator)];
    }
    return random_string;
}

int countNumber() //функция-счетчик, генератор личных номеров. Написана автором
{
    int count{};
    std::ifstream in("Numbers.txt");
    if (in.is_open())
    {
        in >> count;
    }
    in.close();
    ++count;
    std::ofstream out;
    out.open("Numbers.txt");
    if (out.is_open())
    {
        out << count << std::endl;
    }
    out.close();
    return count;
}

std::string autonumber() //маска ввода телефонного номера, написана автором
{
    std::string number;
    retry:
    std::cout << "Введите 10 цифр телефонного номера (без +7, восьмерки, скобок и дефисов): ";
    std::cin >> number;
    if (number.length() != 10)
    {
        std::cout << "Неверное количество цифр. Повторите ввод:" << '\n';
        goto retry;
    }
    std::string str1{ "+7(" };
    std::string str2{ ")" };
    std::string str3{ "-" };
    number.insert(0, str1);
    number.insert(6, str2);
    number.insert(10, str3);
    number.insert(13, str3);
    return number;
}

void DeleteEmptyLines(std::string file) //Удаление пустых строк из текстового файла 
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


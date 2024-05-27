#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <Windows.h>
#include <fstream>
#include <ios>
#include <stdlib.h>
#include <random>
#include <algorithm>
#include "HashTable.h"
#include "specialFunc.h"
#include "User.h"
#include "Messages.h"
#include "AllMessages.h"

int ID_Number = 0;
int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    User user;
    HashTable ht;
    Message m;
    AllMessages am;

    std::string password; //переменная пароля
    int ID_Number{};      //переменная личного номера
    char x = '1';         //переменная цикла входа в регистрацию

    std::cout << "ВНИМАНИЕ!  ЕСЛИ ВЫ ВХОДИТЕ В ЧАТ ВПЕРВЫЕ, ПРОЙДИТЕ РЕГИСТРАЦИЮ, ДЛЯ ЧЕГО НАЖМИТЕ  0." << '\n';
    std::cout << "      ЕСЛИ ВЫ - ЗАРЕГИСТРИРОВАННЫЙ ПОЛЬЗОВАТЕЛЬ, ДЛЯ ПРОДОЛЖЕНИЯ НАЖМИТЕ  1." << '\n';
    std::cout << "____________________________________________________________________________________" << '\n';
    again:
    std::cout << "Введите код операции: ";
    std::cin >> x;
    if (x != '1' && x != '0')
    {
        std::cout << "Неверный ввод команды! Повторите: " << '\n';
        goto again;
        /*Конечно, оператор goto во всех руководствах к использованию категорически не рекомендуется, но мне 
        представляется, что именно в условиях проверки ввода данных, с переходом на несколько строк назад, 
        он весьма удобен, так как упрощает написание кода и не перегружает его лишними циклами*/
    }

    while (x=='0')
    {
        std::cout << "РЕГИСТРАЦИЯ НОВОГО ПОЛЬЗОВАТЕЛЯ: " << '\n';
        std::cout<<'\n';
        std::string passw = random_string(8); //автоматическое создание пароля генератором случайных комбинаций
        int numb = countNumber();             //автоматическое создание личного номера функцией-счетчиком
        ht.fillMap(passw, numb);
        system("pause");
        std::string tel_number = autonumber();//ввод телефонного номера с помощью функции-маски ввода
        system("cls");
        user.FillArray(numb, tel_number);
        DeleteEmptyLines("listOfUsers.txt");
        std::cout << "Регистрация завершена успешно. Выполните повторный вход в программу" << '\n';
        exit(0);
    }
    system("cls");
    ht.extractMap(); //Загрузка контейнера хеш-таблицы из текстового файла
    std::cout << '\n';

    //ВХОД ПО ПАРОЛЮ
    int count{};
    do
    {
        std::string password;
        std::cout << "Введите пароль: ";
        std::cin >> password; 
        std::cout << "Введите личный номер: ";
        std::cin >> ID_Number;
        bool ssy = ht.on_guard(password, ID_Number);
        if (ssy == true)
        {
            std::cout << '\n';
            std::cout << "ВХОД РАЗРЕШЕН!" << '\n';
            break;
        }
        else
        {
            std::cout << "                                        ВВЕДИТЕ ВЕРНЫЕ ДАННЫЕ!" << '\n';
            ++count;
        }
    } while (count < 3);
    if (count >= 3)
    {
        system("cls");
        std::cout << '\n';
        std::cout << " -----------------------------------------------------------------------" << '\n';
        std::cout << "|       Сделаны три неверных попытки. Программа прекращает работу.      |" << '\n';
        std::cout << "|              Войдите повторно или пройдите регистрацию.               |" << '\n';
        std::cout << " -----------------------------------------------------------------------" << '\n';
        exit(0);
    }

    /*ЗАПОМИНАНИЕ ВВЕДЕННЫХ ПОЛЬЗОВАТЕЛЕМ ПРИ ВХОДЕ ЛИЧНОГО НОМЕРА И ПАРОЛЯ ДЛЯ ИХ ДАЛЬНЕЙШЕГО ИСПОЛЬЗОВАНИЯ
    В БЛОКАХ СОВЕРШЕНИЯ ОПЕРАЦИЙ: */
    std::string PSWD = password; //ЗАПОМИНАЕМ ВВЕДЕННЫЙ ПАРОЛЬ
    int IDN = ID_Number; //ЗАПОМИНАЕМ ВВЕДЕННЫЙ НОМЕР
    
    bool repeat{ true };
    while (true)
    {
            std::cout << '\n';
            std::cout << "ДОБРОГО ВРЕМЕНИ СУТОК, УВАЖАЕМЫЙ КЛИЕНТ. ПРИВЕТСТВУЕМ ВАС В НАШЕМ ЧАТЕ." << '\n';
            std::cout << "КАКУЮ ОПЕРАЦИЮ ВЫ ХОТИТЕ ВЫПОЛНИТЬ?" << '\n';
            std::cout << '\n';
            std::cout << "Просмотреть список пользователей...................1;" << '\n';
            std::cout << "Найти пользователей по фамилии ....................2;" << '\n';
            std::cout << "Написать конкретному пользователю .................3;" << '\n';
            std::cout << "Написать всем пользователям .......................4;" << '\n';
            std::cout << "Прочитать свои и адресованные Вам сообщения .......5;" << '\n';
            std::cout << "Прочитать общие сообщения для всех пользователей ..6;" << '\n';
            std::cout << "Удалить свои данные из списка пользователей .......7" << '\n';

            int id_number{};     //переменная личного номера блоках поиска по фамилии и написания сообщений
            int create{};        //переменная цикла повтора создания личных сообщений
            int create_all{};    //переменная цикла повтора создания общих сообщений
            int id_number_of{};  //переменная номера отправителя в блоке создания личных сообщений
            int id_number_in{};  //переменная номера получателя сообщений
            std::string passwrd; //переменная пароля в функции удаления данных
            int xyz{};           //переменная цикла повтора в блоке удаления данных
            int ax{};            //переменная переключателя switch
            std::cout << '\n';
            std::cout << "Введите код операции: ";
            std::cin >> ax;
            std::cout << '\n';
            switch (ax)
            {
            case 1:
                //ПРОСМОТР СПИСКА ПОЛЬЗОВАТЕЛЕЙ
                system("cls");
                user.getListUsers_from_file();
                std::cout << '\n';
                break;
            case 2:
                /*ПОИСК ПО ФАМИЛИИ*/
                system("cls");
                user.getFamilies();
                break;
            case 3:
                //СОЗДАНИЕ ПЕРСОНАЛЬНЫХ СООБЩЕНИЙ:
                system("cls");
                do
                {
                    std::cout << '\n';
                    id_number_of = IDN; //номер отправителя задается номером, введенным пользователем при входе
                    std::cout << "Введите личный номер получателя: ";
                    std::cin >> id_number;
                    id_number_in = id_number;
                    m.createMessages(id_number_of, id_number_in);
                    std::cout << "Написать другому пользователю? Да - 1, Нет - 0" << '\n';
                    std::cin >> create;
                } while (create == 1);
                user.DeleteEmptyLines("Messages.txt");
                break;
            case 4:
                //СОЗДАНИЕ ОБЩИХ СООБЩЕНИЙ:
                system("cls");
                do
                {
                    std::cout << '\n';
                    id_number_of = IDN;
                    am.createMessages_toAll(id_number_of);
                    std::cout << "Написать новое сообщение? Да - 1, Нет - 0" << '\n';
                    std::cin >> create_all;
                } while (create_all == 1);
                user.DeleteEmptyLines("Messages.txt");
                break;

            case 5:
                //ЧТЕНИЕ ЛИЧНЫХ СООБЩЕНИЙ:
                system("cls");
                id_number = IDN;
                m.readPersonalMessages(id_number);
                break;

            case 6:
                //ЧТЕНИЕ ОБЩИХ СООБЩЕНИЙ
                system("cls");
                am.read_Messages_toAll();
                break;

            case 7:
                //УДАЛЕНИЕ ЛИЧНЫХ ДАННЫХ
                system("cls");
                //ht.extractMap();
                std::cout << '\n';
                std::cout << "Вы действительно хотите удалить свои данные? Отмена операции будет невозможной!" << '\n';
                std::cout << "Да - 1, Нет - нажмите любую другую клавишу" << '\n';
                std::cin >> xyz;
                if (xyz == 1)
                {
                    passwrd = PSWD; //значение пароля задается значением, введенным при входе в программу
                    int ID_number = IDN; //значение задается номером, введенным пользователем при входе
                    user.deleteUser(ID_Number);
                    user.DeleteEmptyLines("listOfUsers.txt");
                    ht.deleteElement(passwrd);
                    std::cout << '\n';
                }
                else
                {
                    return 0;
                }

                break;
            }
        int z{};
        std::cout << '\n';
        std::cout << "Желаете выполнить еще одну операцию? Да - нажмите '1', нет - нажмите '0'" << '\n';
        std::cin >> z;
        if (z == 1)
        {
            repeat = true;
        }
        else
        {
            repeat = false;
            break;
        }
        system("cls");

    }
    return 0;
}



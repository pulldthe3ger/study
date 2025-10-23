#include <iostream>  // Для ввода и вывода в консоль
#include <fstream>   // Для работы с файлами
#include <cstring>   // Для работы со строками в стиле C
#include <iomanip>   // Для форматирования вывода

using namespace std; // Чтобы не писать std:: перед каждой функцией

const int MAX_BOOKS = 1000; // Максимальное количество книг

// Структура для хранения информации о книге
struct Book
{
    char name[101];    
    char author[51];   
    int year;          
    float rating;      
};


Book books[MAX_BOOKS];
int bookcnt = 0; 

// Функция для загрузки книг из файла
void loadBooks(const char *filename)
{
    ifstream fin(filename); 

    if (!fin) 
    {
        return; 
    }
    
    while (fin >> books[bookcnt].name 
               >> books[bookcnt].author 
               >> books[bookcnt].year 
               >> books[bookcnt].rating)
    {
        bookcnt++; // Увеличиваем счетчик после каждой прочитанной книги
    }

    fin.close(); // Закрываем файл
}

// Функция для сохранения одной книги в файл
void saveBookToFile(const char *filename, Book b)
{
    ofstream fout(filename, ios::app); // Открываем файл в режиме добавления

    if (!fout) // Если файл не открылся
    {
        cout << "Ошибка при сохранении файла!" << endl;
        return;
    }

    // Записываем данные книги в файл через пробелы
    fout << b.name << " " << b.author << " " << b.year << " " << b.rating << endl;

    fout.close(); // Закрываем файл
}

// Функция для добавления новой книги
void addBook()
{
    // Проверяем, не превышен ли лимит книг
    if (bookcnt >= MAX_BOOKS)
    {
        cout << "Достигнут лимит хранения книг!" << endl;
        return;
    }

    Book nb; // Создаем новую книгу

    // Ввод данных от пользователя
    cout << "Введите название книги: ";
    cin >> nb.name;

    cout << "Введите автора: ";
    cin >> nb.author;

    cout << "Введите год прочтения: ";
    cin >> nb.year;

    cout << "Введите вашу оценку (0-10): ";
    cin >> nb.rating;

    // Проверяем корректность оценки
    if (nb.rating < 0 || nb.rating > 10)
    {
        cout << "Ошибка: оценка должна быть от 0 до 10!" << endl;
        return;
    }

    // Добавляем книгу в массив и сохраняем в файл
    books[bookcnt++] = nb;
    saveBookToFile("books.txt", nb);

    cout << "Книга добавлена!" << endl;
}

// Функция для отображения всех книг
void showAllBooks()
{
    // Проверяем, есть ли книги для показа
    if (bookcnt == 0)
    {
        cout << "Нет данных о книгах." << endl;
        return;
    }

    // Заголовок таблицы
    cout << "\n--- Все книги ---" << endl;
    cout << left << setw(30) << "Название" 
                 << setw(25) << "Автор" 
                 << setw(10) << "Год" 
                 << "Оценка" << endl;
    cout << "--------------------------------------------------------" << endl;

    // Выводим каждую книгу
    for (int i = 0; i < bookcnt; i++)
    {
        cout << left << setw(30) << books[i].name 
                     << setw(25) << books[i].author 
                     << setw(10) << books[i].year 
                     << books[i].rating << "/10" << endl;
    }
}

// Функция для показа статистики
void showStats()
{
    // Проверяем, есть ли данные для статистики
    if (bookcnt == 0)
    {
        cout << "Нет данных для анализа." << endl;
        return;
    }

    float totalRating = 0;      // Общая сумма оценок
    float maxRating = 0;        // Максимальная оценка
    int bestBookIndex = 0;      // Индекс книги с максимальной оценкой

    // Считаем статистику
    for (int i = 0; i < bookcnt; i++)
    {
        totalRating += books[i].rating; // Суммируем оценки

        // Ищем книгу с максимальной оценкой
        if (books[i].rating > maxRating)
        {
            maxRating = books[i].rating;
            bestBookIndex = i;
        }
    }

    float averageRating = totalRating / bookcnt; // Средняя оценка

    // Выводим статистику
    cout << "\n--- Статистика ---" << endl;
    cout << "Количество прочитанных книг: " << bookcnt << endl;
    cout << "Средняя оценка: " << fixed << setprecision(1) << averageRating << "/10" << endl;
    cout << "Самая высоко оцененная книга: " << books[bestBookIndex].name
         << " (" << books[bestBookIndex].author << ") - " 
         << books[bestBookIndex].rating << "/10" << endl;
}

// Функция для показа меню
void showMenu()
{
    cout << "\n=== Трекер книг ===" << endl;
    cout << "1. Добавить книгу" << endl;
    cout << "2. Показать все книги" << endl;
    cout << "3. Показать статистику" << endl;
    cout << "4. Выход" << endl;
    cout << "Выберите пункт: ";
}

// Главная функция программы
int main()
{
    loadBooks("books.txt"); // Загружаем книги из файла при запуске

    int choice; // Переменная для выбора пользователя

    // Основной цикл программы
    do
    {
        showMenu();    // Показываем меню
        cin >> choice; // Читаем выбор пользователя

        // Обрабатываем выбор
        switch (choice)
        {
        case 1:
            addBook(); // Добавить книгу
            break;
        case 2:
            showAllBooks(); // Показать все книги
            break;
        case 3:
            showStats(); // Показать статистику
            break;
        case 4:
            cout << "Выход из программы.\n" << endl;
            break;
        default:
            cout << "Неверный выбор.\n" << endl;
        }
    } while (choice != 4);
    return 0; 
}
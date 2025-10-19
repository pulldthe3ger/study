#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAX_BOOKS=1000;
const char filename[]="books.txt";
struct Book
{
    char name_book[101];
    char author [51];
    int date;
    float rating;

};
Book books[MAX_BOOKS];
int book_count=0;

void loadBooks()
{
    ifstream fin(filename);
    if (!fin)
    {
        return;

    }
    char temp_nb[101];
    char temp_a[51];
    int temp_d;
    float temp_r; 
    while (fin.getline(temp_nb, 100, '|')&&
            fin.getline(temp_a, 50, '|')&&
            fin>>temp_d &&
            fin>>temp_r)
    {
        strcpy(books[book_count].name_book, temp_nb);
        strcpy(books[book_count].author, temp_a);
        books[book_count].date=temp_d;
        books[book_count].rating=temp_r;
        book_count++;
        fin.ignore();
        if (book_count>=MAX_BOOKS)
        {
            break;
        }

    }
    fin.close();

}
void SaveBook(Book book)
{
    ofstream fout(filename, ios::app);
    if (!fout)
    {
        cout <<"error open"<<endl;
        return;

    }
    fout<<book.name_book<<"|"<<book.author<<"|"<<" "<<book.date<<""<<book.rating<<endl;
    fout.close();

}
void clearBuffer()
{
    cin.clear();
    cin.ignore(1000, '\n');
}
void addBook()
{
    if (book_count >= MAX_BOOKS)
    {
        cout<<"LIMIT MEMORY"<<endl;
        return;

    }
    Book newBook;
    clearBuffer();
    cout<<"Напишите название книги"<<endl;
    cin.getline(newBook.name_book, 100);
    cout<<"Напишите ФИО автора в формате - 'И.И. Иванов'"<<endl;
    cin.getline(newBook.author,50);
    cout<<"Напишите дату прочтения книги в формате - 'гггг'"<<endl;
    cin>>newBook.date;
    cout<<"Оцените книгу по 10-балльной шкале"<<endl;
    cin>>newBook.rating;

    if(newBook.rating<0 || newBook.rating>10)
    {
        cout<<"Оценка от 1 до 10!!!"<<endl;
        return;
    }

    books[book_count]=newBook;
    book_count++;
    SaveBook(newBook);
    cout<<"Книга добавлена"<<endl;

}
void showAllBooks()
{
    if (book_count==0)
    {
        cout<<"Нет прочитанных книг"<<endl;
        return;

    }
    cout<<"\n--- Ваша библиотека ---"<<endl;
    cout<< left <<setw(30)<<"Название"
                <<setw(20)<<"Автор"
                <<setw(10)<<"Дата"
                <<"Оценка"<<endl;
    cout << "----------------------------------------------------" << endl;
    for (int i=0; i<book_count; i++)
    {
        cout<< left <<setw(30)<<books[i].name_book
                    <<setw(20)<<books[i].author
                    <<setw(10)<<books[i].date
                    <<books[i].rating<<"/10"<<endl;

    }
}
void showStats()
{
    if (book_count==0)
    {
        cout<<"Библиотека пуста"<<endl;
        return;
    }
    float totalR=0;
    float maxR=0;
    int bestB=0;
    for (int i=0; i<book_count; i++)
    {
        totalR+=books[i].rating;
        if (books[i].rating>maxR)
        {
            maxR=books[i].rating;
            bestB=i;
        }
    }
    float midR=totalR/book_count;
    cout<<"\n--- Статистика ---"<<endl;
    cout<<"Количество книг:"<<book_count<<endl;
    cout<<"Средняя оценка:"<<fixed<<setprecision(1)<<midR<<"/10"<<endl;
    cout<<"Самая лучшая книга:"<<books[bestB].name_book<<books[bestB].author<<books[bestB].rating<<endl;

}
void showMenu()
{
    cout<<"\n===Трекер книг==="<<endl;
    cout<<"1. Добавить книгу"<<endl;
    cout<<"2. Показать все книги"<<endl;
    cout<<"3. Показать статистику"<<endl;
    cout<<"4. Выход"<<endl;
    
    cout<<"Выберите пункт"<<endl;

}
int main()
{
    loadBooks();
    int ch;
    do
    {
        showMenu();
        cin>>ch;
        switch (ch)
        {
        case 1:
            addBook();

            break;
        case 2:
            showAllBooks();
            break;
        case 3:
            showStats();
        case 4:
            cout<<"Выход"<<endl;
        
        default:
            cout<<"Неверный выбор"<<endl;
        }
    }while (ch!=4);
    return 0;
}


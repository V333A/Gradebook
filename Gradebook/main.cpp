#include <iostream>

using namespace std;

class Gradebook
{
private:
    int* grades;
    int count;

public:

    explicit Gradebook(int count)
        : grades(nullptr), count(count)
    {
        if (this->count < 1)
            this->count = 1;

        grades = new int[this->count];

        for (int i = 0; i < this->count; i++)
            grades[i] = 0;
    }

    Gradebook(double count) = delete;

    Gradebook(const Gradebook& other) = delete;
    Gradebook& operator=(const Gradebook& other) = delete;

    ~Gradebook()
    {
        delete[] grades;
    }

    int& operator[](int lesson)
    {
        return grades[lesson];
    }

    int operator[](int lesson) const
    {
        return grades[lesson];
    }

    int getCount() const
    {
        return count;
    }

    double average() const
    {
        int sum = 0;
        int gradesCount = 0;

        for (int i = 0; i < count; i++)
        {
            if (grades[i] != 0)
            {
                sum += grades[i];
                gradesCount++;
            }
        }

        if (gradesCount == 0)
            return 0;

        return static_cast<double>(sum) / gradesCount;
    }

    explicit operator bool() const
    {
        for (int i = 0; i < count; i++)
        {
            if (grades[i] != 0)
                return true;
        }

        return false;
    }

    bool setGrade(int lesson, int grade)
    {
        if (lesson < 0 || lesson >= count)
            return false;

        if (grade < 1 || grade > 12)
            return false;

        grades[lesson] = grade;

        return true;
    }

    friend ostream& operator<<(ostream& out, const Gradebook& book)
    {
        out << "Оцінки: ";

        for (int i = 0; i < book.count; i++)
        {
            if (book.grades[i] == 0)
                out << "- ";
            else
                out << book.grades[i] << " ";
        }

        out << "| середній бал: " << book.average();

        return out;
    }

    friend istream& operator>>(istream& in, Gradebook& book)
    {
        for (int i = 0; i < book.count; i++)
        {
            int grade;

            in >> grade;

            if (grade < 0 || grade > 12)
                grade = 0;

            book.grades[i] = grade;
        }

        return in;
    }
};


int bestGrade(const Gradebook& book)
{
    int best = 0;

    for (int i = 0; i < book.getCount(); i++)
    {
        if (book[i] > best)
            best = book[i];
    }

    return best;
}


int main()
{
    Gradebook book(5);

    cout << book << endl;

    if (!book)
        cout << "Оцінок ще немає" << endl;

    book[0] = 10;
    book[1] = 12;
    book[3] = 9;

    cout << book << endl;

    cout << "Найкраща оцінка: "
        << bestGrade(book)
        << endl;


    // Gradebook copy = book;
    // копіювання заборонене

    // Gradebook wrong(5.5);
    // конструктор double видалений


    if (!book.setGrade(2, 15))
        cout << "Некоректна оцінка" << endl;


    Gradebook second(5);

    cout << "Введіть 5 оцінок: ";
    cin >> second;

    cout << second << endl;

    return 0;
}


/*
ПОЯСНИ

1. operator<< дружній, бо зліва стоїть cout, а не Gradebook.

2. Одна версія [] потрібна для зміни, друга для const-об'єктів.
   У bestGrade викликається const-версія.

3. [] повертає int&, тому не може перевірити значення при присвоєнні.
   setGrade може перевірити оцінку перед записом.

4. explicit не дозволяє зайві неявні перетворення в bool.
   if (book) і if (!book) при цьому працюють.

5. Без заборони копіювання скопіювався б тільки покажчик grades.
   Два об'єкти мали б один масив і могли б зробити подвійний delete[].
*/
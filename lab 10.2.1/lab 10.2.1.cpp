#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// Перелік спеціальностей
enum class Spec { CS, IT, ME, PhIT, TR };

// Масив рядків для виведення спеціальностей
string strSpec[] = { "Комп'ютернi науки", "Iнформатика", "Математика та економiка",
                     "Фiзика та iнформатика", "Трудове навчання" };

// Структура для зберігання даних про студента
struct Student
{
    string lname;      // прізвище
    int kurs;          // курс
    Spec spec;         // спеціальність
    int physics;       // оцінка з фізики
    int math;          // оцінка з математики
    int informatik;    // оцінка з інформатики
};

// Функція для створення масиву студентів
void Create(Student* s, int amSt) {
    int sp;
    for (int i = 0; i < amSt; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;
        cout << "Прiзвище: ";
        cin >> s[i].lname;

        // Перевірка введення курсу
        do {
            cout << "Курс (1-4): ";
            cin >> s[i].kurs;
            if (s[i].kurs < 1 || s[i].kurs > 4)
                cout << "Некоректне значення! Спробуйте ще раз." << endl;
        } while (s[i].kurs < 1 || s[i].kurs > 4);

        // Перевірка введення спеціальності
        do {
            cout << "Спецiальнiсть (0 - Комп'ютернi науки, 1 - Iнформатика, 2 - Математика та економiка, "
                << "3 - Фiзика та iнформатика, 4 - Трудове навчання): ";
            cin >> sp;
            if (sp < 0 || sp > 4)
                cout << "Некоректне значення! Спробуйте ще раз." << endl;
        } while (sp < 0 || sp > 4);
        s[i].spec = static_cast<Spec>(sp);

        cout << "Оцiнка з фiзики: ";
        cin >> s[i].physics;
        cout << "Оцiнка з математики: ";
        cin >> s[i].math;
        cout << "Оцiнка з інформатики: ";
        cin >> s[i].informatik;
        cout << endl;
    }
}

// Функція для виведення масиву студентів
void Print(Student* s, int amSt)
{
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
    cout << "| № |    Прiзвище   | Курс |      Спецiальнiсть     | Фiзика | Математика | Інформатика |"
        << endl;
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < amSt; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << "";
        cout << "| " << setw(14) << left << s[i].lname
            << "| " << setw(5) << right << s[i].kurs
            << "| " << setw(23) << left << strSpec[static_cast<int>(s[i].spec)]
            << "| " << setw(7) << s[i].physics
            << "| " << setw(11) << right << s[i].math
            << "| " << setw(7) << right << s[i].informatik;
        cout << " |" << endl;
    }
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
}

// Фізичне впорядкування масиву з використанням std::sort
void Sort(Student* p, const int N)
{
    std::sort(p, p + N, [](const Student& a, const Student& b) {
        if (a.spec != b.spec) return a.spec < b.spec;
        if (a.math != b.math) return a.math < b.math;
        return a.lname < b.lname;
        });
}

// Індексне впорядкування масиву
int* indexSort(Student* s, int N)
{
    int* P = new int[N];
    for (int i = 0; i < N; i++)
        P[i] = i;

    std::sort(P, P + N, [s](int a, int b) {
        if (s[a].spec != s[b].spec) return s[a].spec < s[b].spec;
        if (s[a].math != s[b].math) return s[a].math < s[b].math;
        return s[a].lname < s[b].lname;
        });
    return P;
}

// Бінарний пошук студента
int binSearch(Student* p, const int N, const string& prizv, const Spec spec, const int math)
{
    int L = 0, R = N - 1, m;
    while (L <= R) {
        m = (L + R) / 2;
        if (p[m].lname == prizv && p[m].spec == spec && p[m].math == math)
            return m;
        if ((p[m].spec < spec) ||
            (p[m].spec == spec && p[m].math < math) ||
            (p[m].spec == spec && p[m].math == math && p[m].lname < prizv))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    }
    return -1;
}

int main()
{
    // Видалено Windows специфічні рядки SetConsoleCP(1251) та SetConsoleOutputCP(1251);

    int amSt;
    cout << "Введіть кількість студентів: ";
    cin >> amSt;

    Student* s = new Student[amSt];

    int menuItem;
    do {
        cout << endl << "Виберіть дію:" << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [4] - індексне впорядкування та вивід даних" << endl;
        cout << " [5] - бінарний пошук студента за прізвищем, спеціальністю та оцінкою з математики" << endl;
        cout << " [0] - вихід та завершення програми" << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl;

        switch (menuItem)
        {
        case 1:
            Create(s, amSt);
            break;

        case 2:
            Print(s, amSt);
            break;

        case 3:
            Sort(s, amSt);
            cout << "Масив фізично впорядковано!" << endl;
            break;

        case 4:
        {
            int* P = indexSort(s, amSt);
            cout << "Індексне впорядкування: ";
            for (int i = 0; i < amSt; i++)
                cout << P[i] + 1 << " ";
            cout << endl;

            cout << endl << "Впорядкований масив за допомогою індексів:" << endl;
            for (int i = 0; i < amSt; i++)
            {
                cout << "| " << setw(2) << right << i + 1 << "";
                cout << "| " << setw(14) << left << s[P[i]].lname
                    << "| " << setw(5) << right << s[P[i]].kurs
                    << "| " << setw(23) << left << strSpec[static_cast<int>(s[P[i]].spec)]
                    << "| " << setw(7) << s[P[i]].physics
                    << "| " << setw(11) << right << s[P[i]].math
                    << "| " << setw(7) << right << s[P[i]].informatik << " |";
                cout << endl;
            }
            cout << "-----------------------------------------------------------------------------------------"
                << endl;
            delete[] P;
        }
        break;

        case 5:
            cout << "Введіть ключі пошуку:" << endl;
            string lastName;
            int math, specNum;
            cout << "  Прізвище: "; cin >> lastName;
            cout << "  Спеціальність (0-4): "; cin >> specNum;
            cout << "  Оцінка з математики: "; cin >> math;

            int found = binSearch(s, amSt, lastName, static_cast<Spec>(specNum), math);
            if (found != -1)
                cout << "Знайдено студента в позиції " << found + 1 << endl;
            else
                cout << "Студента не знайдено!" << endl;
            break;

        case 0:
            break;

        default:
            cout << "Помилка вводу! Введіть значення від 0 до 5." << endl;
        }
    } while (menuItem != 0);

    delete[] s;
    return 0;
}

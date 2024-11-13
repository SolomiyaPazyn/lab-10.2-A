#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;

enum Spec { CS, IT, ME, PhIT, TR };

string strSpec[] = { "Комп'ютернi науки", "Iнформатика", "Математика та економiка", "Фiзика та iнформатика", "Трудове навчання" };

// Структура для зберігання інформації про студентів
struct Student {
    string lname; 
    int kurs;     
    Spec spec;    
    int physics;  
    int math;     
    int informatik; 
};

// Функція для введення даних про студентів
void Create(Student* s, int amSt) {
    int sp;
    for (int i = 0; i < amSt; i++) {
        cout << "Прiзвище: ";
        cin >> s[i].lname;
        cout << "Курс: ";
        cin >> s[i].kurs;
        cout << "Спецiальнiсть (0 - Комп'ютернi науки, 1 - Iнформатика, 2 - Математика та економiка, 3 - Фiзика та iнформатика, 4 - Трудове навчання) ";
        cin >> sp;
        s[i].spec = (Spec)sp;
        cout << "Оцiнка з фiзики: ";
        cin >> s[i].physics;
        cout << "Оцiнка з математики: ";
        cin >> s[i].math;
        cout << "Оцiнка з інформатики: ";
        cin >> s[i].informatik;
        cout << endl;
    }
}

// Функція для виведення списку студентів на екран
void Print(Student* s, int amSt) {
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
    cout << "| № |    Прiзвище   | Курс |      Спецiальнiсть     | Фiзика | Математика | Інформатика |"
        << endl;
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < amSt; i++) {
        cout << "| " << setw(2) << right << i + 1 << "";
        cout << "| " << setw(14) << left << s[i].lname
            << "| " << setw(5) << right << s[i].kurs
            << "| " << setw(23) << left << strSpec[s[i].spec]
            << "| " << setw(7) << s[i].physics
            << "| " << setw(11) << right << s[i].math
            << "| " << setw(7) << right << s[i].informatik;
        cout << endl;
    }
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
}

// Функція для фізичного впорядкування масиву студентів
void Sort(Student* p, const int N) {
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((p[i1].spec > p[i1 + 1].spec) ||
                (p[i1].spec == p[i1 + 1].spec && p[i1].math > p[i1 + 1].math) ||
                (p[i1].spec == p[i1 + 1].spec && p[i1].math == p[i1 + 1].math &&
                    p[i1].lname > p[i1 + 1].lname)) {
                // Заміна елементів
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

// Функція для створення індексного масиву та впорядкування за індексом
int* indexSort(Student* s, const int N) {
    int* P = new int[N]; // Виділення пам'яті для індексного масиву
    for (int i = 0; i < N; i++)
        P[i] = i; // Ініціалізація масиву індексів

    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((s[P[i1]].spec > s[P[i1 + 1]].spec) ||
                (s[P[i1]].spec == s[P[i1 + 1]].spec && s[P[i1]].math > s[P[i1 + 1]].math) ||
                (s[P[i1]].spec == s[P[i1 + 1]].spec && s[P[i1]].math == s[P[i1 + 1]].math &&
                    s[P[i1]].lname > s[P[i1 + 1]].lname)) {
                // Заміна індексів
                int tmp = P[i1];
                P[i1] = P[i1 + 1];
                P[i1 + 1] = tmp;
            }
    return P; 
}

// Функція для виведення індексно-впорядкованого масиву студентів
void PrintIndexSorted(Student* s, int* P, const int N) {
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
    cout << "| № |    Прiзвище   | Курс |      Спецiальнiсть     | Фiзика | Математика | Інформатика |"
        << endl;
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << right << i + 1 << "";
        cout << "| " << setw(14) << left << s[P[i]].lname
            << "| " << setw(5) << right << s[P[i]].kurs
            << "| " << setw(23) << left << strSpec[s[P[i]].spec]
            << "| " << setw(7) << s[P[i]].physics
            << "| " << setw(11) << right << s[P[i]].math
            << "| " << setw(7) << right << s[P[i]].informatik;
        cout << endl;
    }
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
}

// Функція для бінарного пошуку студента за прізвищем, спеціальністю та оцінкою з математики
int binSearch(Student* p, const int N, const string prizv, const Spec spec, const int math) {
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].lname == prizv && p[m].spec == spec && p[m].math == math)
            return m; 
        if ((p[m].spec < spec) ||
            (p[m].spec == spec && p[m].math < math) ||
            (p[m].spec == spec && p[m].math == math && p[m].lname < prizv))
            L = m + 1; // Пошук у правій половині
        else
            R = m - 1; // Пошук у лівій половині
    } while (L <= R);
    return -1; 
}

int main() {
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251); 

    int amSt;
    cout << "Кількість студентів: ";
    cin >> amSt;

    // Виділення пам'яті для масиву структур Student
    Student* s = new Student[amSt];
    int menuItem;
    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [4] - індексне впорядкування та вивід даних" << endl;
        cout << " [5] - бінарний пошук студента" << endl;
        cout << " [0] - вихід та завершення програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl;

        switch (menuItem) {
        case 1:
            Create(s, amSt);
            break;
        case 2:
            Print(s, amSt);
            break;
        case 3:
            Sort(s, amSt);
            cout << "Дані впорядковано!" << endl;
            break;
        case 4: {
            int* P = indexSort(s, amSt); // Виділення пам'яті для індексного масиву
            PrintIndexSorted(s, P, amSt);
            delete[] P; 
            break;
        }
        case 5: {
            string prizv;
            int speciality, mathGrade;
            cout << "Введіть прізвище: "; cin >> prizv;
            cout << "Введіть спеціальність (0-4): "; cin >> speciality;
            cout << "Введіть оцінку з математики: "; cin >> mathGrade;

            int found = binSearch(s, amSt, prizv, (Spec)speciality, mathGrade);
            if (found >= 0)
                cout << "Знайдено студента в позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;
        }
        case 0:
            break;
        }
    } while (menuItem != 0);

    delete[] s; 
    return 0;
}

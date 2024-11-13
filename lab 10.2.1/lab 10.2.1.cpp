#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// ������ ��������������
enum class Spec { CS, IT, ME, PhIT, TR };

// ����� ����� ��� ��������� ��������������
string strSpec[] = { "����'�����i �����", "I����������", "���������� �� ������i��",
                     "�i���� �� i����������", "������� ��������" };

// ��������� ��� ��������� ����� ��� ��������
struct Student
{
    string lname;      // �������
    int kurs;          // ����
    Spec spec;         // ������������
    int physics;       // ������ � ������
    int math;          // ������ � ����������
    int informatik;    // ������ � �����������
};

// ������� ��� ��������� ������ ��������
void Create(Student* s, int amSt) {
    int sp;
    for (int i = 0; i < amSt; i++) {
        cout << "������� � " << i + 1 << ":" << endl;
        cout << "��i�����: ";
        cin >> s[i].lname;

        // �������� �������� �����
        do {
            cout << "���� (1-4): ";
            cin >> s[i].kurs;
            if (s[i].kurs < 1 || s[i].kurs > 4)
                cout << "���������� ��������! ��������� �� ���." << endl;
        } while (s[i].kurs < 1 || s[i].kurs > 4);

        // �������� �������� ������������
        do {
            cout << "����i����i��� (0 - ����'�����i �����, 1 - I����������, 2 - ���������� �� ������i��, "
                << "3 - �i���� �� i����������, 4 - ������� ��������): ";
            cin >> sp;
            if (sp < 0 || sp > 4)
                cout << "���������� ��������! ��������� �� ���." << endl;
        } while (sp < 0 || sp > 4);
        s[i].spec = static_cast<Spec>(sp);

        cout << "��i��� � �i����: ";
        cin >> s[i].physics;
        cout << "��i��� � ����������: ";
        cin >> s[i].math;
        cout << "��i��� � �����������: ";
        cin >> s[i].informatik;
        cout << endl;
    }
}

// ������� ��� ��������� ������ ��������
void Print(Student* s, int amSt)
{
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
    cout << "| � |    ��i�����   | ���� |      ����i����i���     | �i���� | ���������� | ����������� |"
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

// Գ����� ������������� ������ � ������������� std::sort
void Sort(Student* p, const int N)
{
    std::sort(p, p + N, [](const Student& a, const Student& b) {
        if (a.spec != b.spec) return a.spec < b.spec;
        if (a.math != b.math) return a.math < b.math;
        return a.lname < b.lname;
        });
}

// �������� ������������� ������
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

// �������� ����� ��������
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
    // �������� Windows ��������� ����� SetConsoleCP(1251) �� SetConsoleOutputCP(1251);

    int amSt;
    cout << "������ ������� ��������: ";
    cin >> amSt;

    Student* s = new Student[amSt];

    int menuItem;
    do {
        cout << endl << "������� ��:" << endl;
        cout << " [1] - �������� ����� � ���������" << endl;
        cout << " [2] - ���� ����� �� �����" << endl;
        cout << " [3] - ������� ������������� �����" << endl;
        cout << " [4] - �������� ������������� �� ���� �����" << endl;
        cout << " [5] - ������� ����� �������� �� ��������, ������������ �� ������� � ����������" << endl;
        cout << " [0] - ����� �� ���������� ��������" << endl;
        cout << "������ ��������: "; cin >> menuItem;
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
            cout << "����� ������� ������������!" << endl;
            break;

        case 4:
        {
            int* P = indexSort(s, amSt);
            cout << "�������� �������������: ";
            for (int i = 0; i < amSt; i++)
                cout << P[i] + 1 << " ";
            cout << endl;

            cout << endl << "������������� ����� �� ��������� �������:" << endl;
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
            cout << "������ ����� ������:" << endl;
            string lastName;
            int math, specNum;
            cout << "  �������: "; cin >> lastName;
            cout << "  ������������ (0-4): "; cin >> specNum;
            cout << "  ������ � ����������: "; cin >> math;

            int found = binSearch(s, amSt, lastName, static_cast<Spec>(specNum), math);
            if (found != -1)
                cout << "�������� �������� � ������� " << found + 1 << endl;
            else
                cout << "�������� �� ��������!" << endl;
            break;

        case 0:
            break;

        default:
            cout << "������� �����! ������ �������� �� 0 �� 5." << endl;
        }
    } while (menuItem != 0);

    delete[] s;
    return 0;
}

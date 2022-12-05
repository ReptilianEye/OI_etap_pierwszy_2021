#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;
vector<long long> ciagFibonacciego;

void generujCiagFibonacciego(long long n)
{
    ciagFibonacciego.push_back(1);
    ciagFibonacciego.push_back(1);
    int i = 1;
    long long kolejnyWyrazCiagu = ciagFibonacciego[i] + ciagFibonacciego[i - 1];
    while (kolejnyWyrazCiagu <= n)
    {
        ciagFibonacciego.push_back(kolejnyWyrazCiagu);
        i++;
        kolejnyWyrazCiagu = ciagFibonacciego[i] + ciagFibonacciego[i - 1];
    }
}
int znajdzLiczbeWCiagu(long long liczba)
{
    for (int i = ciagFibonacciego.size() - 1; i >= 0; i--)
    {
        if (ciagFibonacciego[i] == liczba)
            return i;
        if (ciagFibonacciego[i] < liczba)
            return i;
    }
    return -1;
}
int przeliczWzor(vector<int> pozycje)
{
    int wynik = 0;
    for (int i = 0; i < pozycje.size(); i++)
    {
        // cout << pozycje[i] << " ";
        wynik += pozycje[i];
        wynik++;
    }
    // cout << endl;
    wynik--;
    return wynik;
}
void DzieliNaCzynnikiFibIZwracaPozycjeRek(long long n, vector<int> dotychczasoweWyniki)
{
    int pozLiczby = znajdzLiczbeWCiagu(n);
    if (ciagFibonacciego[pozLiczby] == n)
    {
        dotychczasoweWyniki.push_back(pozLiczby);
        cout << przeliczWzor(dotychczasoweWyniki) << endl;
        exit(0);
        // return;
    }

    int i = pozLiczby;
    for (int i = pozLiczby; i >= 2; i--)
    {
        if (n % ciagFibonacciego[i] == 0)
        {
            long long liczbaDoZaglebienia = n / ciagFibonacciego[i];
            dotychczasoweWyniki.push_back(i);
            DzieliNaCzynnikiFibIZwracaPozycjeRek(liczbaDoZaglebienia, dotychczasoweWyniki);
            dotychczasoweWyniki.pop_back();
        }
    }
}

int main()
{
    long long n;

    cin >> n;
    generujCiagFibonacciego(n);
    DzieliNaCzynnikiFibIZwracaPozycjeRek(n, vector<int>());
    cout << "NIE" << endl;
    return 0;
}

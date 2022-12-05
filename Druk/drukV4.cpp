#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <math.h>
#include <stack>
#include <set>

//V4 ten sam algorytm z powrotmi, wyglada ze dziala
//wyszkiwanie wolnego punktu funkcja
//dodanie wstepu szukajacego dlugosci szablonow
//za wolny (dobry dla malych danych)

using namespace std;

class przylozonySzablon
{
public:
    int x, y;
    int kierunekPolozenia;
    int kierunekDoSprawdzenia;

    przylozonySzablon(int i, int j, int kierP, int kierS)
    {
        x = i;
        y = j;
        kierunekPolozenia = kierP;
        kierunekDoSprawdzenia = kierS;
    }
};

int n, m;
char **T;
bool **visited;

void drukujVisited()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (visited[i][j])
                cout << "1";
            else
                cout << "0";
        }
        cout << endl;
    }
    cout << endl;
}

void DrukujStos(stack<przylozonySzablon> s)
{
    stack<przylozonySzablon> kopiaS;
    kopiaS = s;

    for (int i = 0; i < s.size(); i++)
    {
        przylozonySzablon temp = kopiaS.top();
        kopiaS.pop();
        cout << temp.x << " " << temp.y << " " << temp.kierunekPolozenia << " " << temp.kierunekDoSprawdzenia << endl;
    }
    cout << endl;
}

pair<int, int> znajdujeWolnePole(bool **visited, int &pierwszyWiersz)
{
    for (int k = pierwszyWiersz; k < n; k++)
    {
        for (int l = 0; l < m; l++)
        {
            if (!visited[k][l])
            {
                pierwszyWiersz = k;
                return make_pair(k, l);
            }
        }
    }
    return make_pair(-1, -1);
}

bool sprawdzSzablon(string szablon)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            visited[i][j] = false;
        }
    }

    int pierwszyNiezapelnionyWiersz = 0;
    int dlugoscSzablonu = szablon.length();
    int doUzycia = (m * n) / dlugoscSzablonu;

    stack<przylozonySzablon> stos;

    int i = 0, j = 0;
    przylozonySzablon pierwszyKrok(i, j, 0, 0);
    stos.push(pierwszyKrok);

    while (!stos.empty())
    {
        // drukujVisited();
        // DrukujStos(stos);
        przylozonySzablon poprzedni = stos.top();
        stos.pop();
        int kierunek = poprzedni.kierunekDoSprawdzenia;
        i = poprzedni.x, j = poprzedni.y;

        poprzedni.kierunekDoSprawdzenia++;
        stos.push(poprzedni);
        //szukamy najstepnego miejsca do decyzji
        pair<int, int> kolejneWolne = znajdujeWolnePole(visited, pierwszyNiezapelnionyWiersz);

        //sprawdzamy czy wszystko pasuje
        if (kolejneWolne.first == -1)
        {
            return true;
        }
        //probujemy przylozyc kolejny szablon - poziomo
        if (kierunek == 0)
        {
            bool pasuje = true;
            if (kolejneWolne.second + dlugoscSzablonu <= m)
            {

                for (int k = 0; k < dlugoscSzablonu; k++)
                {
                    if (szablon[k] != T[kolejneWolne.first][kolejneWolne.second + k])
                    {
                        pasuje = false;
                        break;
                    }
                }
            }
            else
            {
                pasuje = false;
            }
            if (pasuje)
            {
                przylozonySzablon dodawany(kolejneWolne.first, kolejneWolne.second, 0, 0);
                for (int k = 0; k < dlugoscSzablonu; k++)
                {
                    if (visited[kolejneWolne.first][kolejneWolne.second + k] == true)
                    {
                        cout << "drukuje na sobie poziomo" << endl;
                    }
                    visited[kolejneWolne.first][kolejneWolne.second + k] = true;
                }
                stos.push(dodawany);
            }
        }
        //probujemy przylozyc kolejny szablon - pionowo
        else if (kierunek == 1)
        {
            bool pasuje = true;
            if (kolejneWolne.first + dlugoscSzablonu <= n)
            {

                for (int k = 0; k < dlugoscSzablonu; k++)
                {
                    if (szablon[k] != T[kolejneWolne.first + k][kolejneWolne.second])
                    {
                        pasuje = false;
                        break;
                    }
                }
            }
            else
            {
                pasuje = false;
            }
            if (pasuje)
            {
                przylozonySzablon dodawany(kolejneWolne.first, kolejneWolne.second, 1, 0);
                for (int k = 0; k < dlugoscSzablonu; k++)
                {
                    if (visited[kolejneWolne.first + k][kolejneWolne.second] == true)
                    {
                        cout << "drukuje na sobie pionowo" << endl;
                    }
                    visited[kolejneWolne.first + k][kolejneWolne.second] = true;
                }
                stos.push(dodawany);
            }
        }
        //nie udaje sie przylozyc - wracamy
        else
        {
            // cout << "wracam" << endl;
            stos.pop();
            if (!stos.empty())
            {
                for (int k = 0; k < dlugoscSzablonu; k++)
                {
                    if (poprzedni.kierunekPolozenia == 0)
                    {
                        if (visited[poprzedni.x][poprzedni.y + k] == false)
                        {
                            cout << "usuwam poziomo ktorego nie mam" << endl;
                        }
                        visited[poprzedni.x][poprzedni.y + k] = false;
                    }
                    else if (poprzedni.kierunekPolozenia == 1)
                    {
                        if (visited[poprzedni.x + k][poprzedni.y] == false)
                        {
                            cout << "usuwa pionowo ktorego nie ma" << endl;
                        }
                        visited[poprzedni.x + k][poprzedni.y] = false;
                    }
                }
                pierwszyNiezapelnionyWiersz = poprzedni.x;
            }
        }
    }

    //jesli nie przypasowal w zaden sposob
    return false;
}
vector<int> zwracaMozliweDlugosciSzablonuV2(vector<int> ilosciUnikalnychLiter)
{
    vector<int> mozliweDlugosci;
    int pole = n * m;
    int minim = min(n, m);
    int maxim = max(m, n);
    for (int i = ilosciUnikalnychLiter.size(); i <= maxim; i++)
    {
        if (n % i != 0 and m % i != 0)
            continue;
        if (pole % i != 0)
            continue;
        int iloscSzablonow = pole / i;
        bool czyDzieliWszystkie = true;
        for (int j = 0; j < ilosciUnikalnychLiter.size(); j++)
        {
            if (ilosciUnikalnychLiter[j] % iloscSzablonow != 0)
            {
                czyDzieliWszystkie = false;
                break;
            }
        }
        if (!czyDzieliWszystkie)
            continue;
        mozliweDlugosci.push_back(i);
    }
    return mozliweDlugosci;
}
string zwrocSzablon(int dlugosc, int kierunek)
{
    string szablon = "";
    for (int i = 0; i < dlugosc; i++)
    {
        if (kierunek == 0 and dlugosc <= m)
        {
            szablon = szablon + T[0][i];
        }
        if (kierunek == 1 and dlugosc <= n)
        {
            szablon = szablon + T[i][0];
        }
    }
    return szablon;
}
vector<string> przygotujSzablony(vector<int> mozliweDlugosci)
{
    vector<string> kandydaci;
    string szablon;
    for (int i = 0; i < mozliweDlugosci.size(); i++)
    {
        for (int j = 0; j < 2; j++)
        {
            szablon = zwrocSzablon(mozliweDlugosci[i], j);
            if (szablon[szablon.length() - 1] == T[n - 1][m - 1])
            {
                kandydaci.push_back(szablon);
            }
        }
    }
    return kandydaci;
}

int main()
{
    cin >> n >> m;
    T = new char *[n];
    for (int i = 0; i < n; i++)
        T[i] = new char[m];

    visited = new bool *[n];
    for (int i = 0; i < n; i++)
        visited[i] = new bool[m];

    string rzad;
    int *wystapienia = new int[26]{0};
    for (int i = 0; i < n; i++)
    {
        cin >> rzad;
        for (int j = 0; j < m; j++)
        {
            T[i][j] = rzad[j];
            wystapienia[rzad[j] - 'a']++;
        }
    }
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         cout << T[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    vector<int> ilosciUnikalnychLiter;
    for (int i = 0; i < 26; i++)
    {
        if (wystapienia[i] > 0)
        {
            // cout << char(i + 'a') << " " << wystapienia[i] << " ";
            ilosciUnikalnychLiter.push_back(wystapienia[i]);
        }
    }
    // cout << endl;

    vector<int> mozliweDlugosci = zwracaMozliweDlugosciSzablonuV2(ilosciUnikalnychLiter);
    // for (auto kandydat : mozliweDlugosci)
    // cout << kandydat << " ";
    // cout << endl;
    vector<string> kandydaci = przygotujSzablony(mozliweDlugosci);
    set<int> odpowiedzi;
    for (auto kandydat : kandydaci)
    {
        // cout << kandydat << endl;
        if (sprawdzSzablon(kandydat))
        {
            // cout<< "znaleziono taki "  << kandydat << endl;
            odpowiedzi.insert(kandydat.length());
        }
    }
    // sort(odpowiedzi.begin(), odpowiedzi.end());
    cout << odpowiedzi.size() << endl;
    for (auto i = odpowiedzi.begin(); i != odpowiedzi.end(); i++)
    {
        cout << *i << " ";
    }
    // cout << endl;
    return 0;
}

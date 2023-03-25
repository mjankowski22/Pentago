#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <time.h>
#include <cmath>
#include <vector>

using namespace std;

const int wiersze = 3;
const int kolumny = 3;
const int ilosc_zetonow = 5;

//funkcja sluzace do ustawienia pozycji planszy na ekranie

void wypiszPrzerwe()
{
    for (int i = 0; i < 15; i++)
    {
        cout << " ";
    }
}
void wypiszPrzerwePlansza()
{
    for (int i = 0; i < 29; i++)
    {
        cout << " ";
    }
}
void wypiszOdstep()
{
    for (int i = 0; i < 40; i++)
    {
        cout << endl;
    }
}

//funkcja wczytujaca imiona graczy przed rozgrywka

void wczytajImiona(char imie1[], char imie2[])
{
    wypiszPrzerwe();
    cout << "Podaj imie pierwszego gracza(zetony czerwone): ";
    cin >> imie1;
    wypiszPrzerwe();
    cout << "Podaj imie drugiego gracza(zetony niebieskie): ";
    cin >> imie2;
}

//funkcja zmieniajaca zetony podczas rozgrywki

void zmienZetony(char &znak1, char &znak2, char imie1[], char imie2[])
{
    bool poprawnaZmiana1 = true;
    bool poprawnaZmiana2 = true;
    char zeton;

    do
    {
        poprawnaZmiana1 = true;
        wypiszOdstep();
        wypiszPrzerwe();
        cout << imie1 << " podaj swoje nowe zetony: ";
        cin >> zeton;
        if (zeton != znak1 && zeton != znak2)
        {
            znak1 = zeton;
            poprawnaZmiana1 = true;
        }
        else
        {
            wypiszPrzerwe();
            cout << "Niepoprawne zetony";
            poprawnaZmiana1 = false;
        }
    } while (!poprawnaZmiana1);

    do
    {
        poprawnaZmiana2 = true;
        wypiszOdstep();
        wypiszPrzerwe();
        cout << imie2 << " podaj swoje nowe zetony: ";
        cin >> zeton;
        if (zeton != znak1 && zeton != znak2)
        {
            znak2 = zeton;
            poprawnaZmiana1 = true;
        }
        else
        {
            wypiszPrzerwe();
            cout << "Niepoprawne zetony";
            poprawnaZmiana2 = false;
        }
    } while (!poprawnaZmiana2);
}

//funkcja skleja 4 plansze w jedna aby latwiej sprawdzic warunek wygranej

void sklejPlansze(int plansza1[wiersze][kolumny], int plansza2[wiersze][kolumny], int plansza3[wiersze][kolumny], int plansza4[wiersze][kolumny], int sklejonaPlansza[wiersze * 2][kolumny * 2])
{

    for (int i = 0; i < wiersze; i++)
    {
        for (int j = 0; j < kolumny; j++)
        {
            sklejonaPlansza[i][j] = plansza1[i][j];
            sklejonaPlansza[i][j + kolumny] = plansza2[i][j];
            sklejonaPlansza[i + wiersze][j] = plansza3[i][j];
            sklejonaPlansza[i + wiersze][j + kolumny] = plansza4[i][j];
        }
    }
}

//funkcje obracajace plansze w przypadku gry w pentago

void obrocPlanszeZgodnie(int plansza[wiersze][kolumny], int obroconaPlansza[wiersze][kolumny])
{
    int m = 0, n = 0;
    for (int i = kolumny - 1; i >= 0; i--)
    {
        n = 0;
        for (int j = 0; j < wiersze; j++)
        {
            obroconaPlansza[j][i] = plansza[m][n];
            n++;
        }
        m++;
    }
}

void obrocPlanszePrzeciwnie(int plansza[wiersze][kolumny], int obroconaPlansza[wiersze][kolumny])
{
    int m = kolumny - 1;
    int n = 0;
    for (int i = 0; i < wiersze; i++)
    {
        n = 0;
        for (int j = 0; j < kolumny; j++)
        {
            obroconaPlansza[i][j] = plansza[n][m];
            n++;
        }
        m--;
    }
}

//funkcja odpowiadajaca za przypisanie jednej tablicy dwuwymiarowej do drugiej

void ustawPlansze(int plansza[wiersze][kolumny], int obroconaPlansza[wiersze][kolumny])
{
    for (int i = 0; i < wiersze; i++)
    {
        for (int j = 0; j < kolumny; j++)
        {
            plansza[i][j] = obroconaPlansza[i][j];
        }
    }
}

//funkcja wypisuje plansze na ekran

void rysuj(int plansza[wiersze * 2][kolumny * 2], char znak1, char znak2)
{

    char lacznik = 206, kreska_pionowa = 186, kreska_pozioma = 205, lacznik_lewy = 204, lacznik_prawy = 185, lacznik_gorny = 203, lacznik_dolny = 202,
         lacznik_lewy_gorny = 201, lacznik_lewy_dolny = 200, lacznik_prawy_gorny = 187, lacznik_prawy_dolny = 188;

    wypiszPrzerwePlansza();

    cout << lacznik_lewy_gorny;
    for (int i = 0; i < kolumny * 3 + kolumny - 1; i++)
    {
        if ((i + 1) % 4 == 0)
            cout << lacznik_gorny;
        else
            cout << kreska_pozioma;
    }
    cout << lacznik_prawy_gorny;
    cout << "  ";
    cout << lacznik_lewy_gorny;
    for (int i = 0; i < kolumny * 3 + kolumny - 1; i++)
    {
        if ((i + 1) % 4 == 0)
            cout << lacznik_gorny;
        else
            cout << kreska_pozioma;
    }
    cout << lacznik_prawy_gorny;

    for (int i = 0; i < wiersze; i++)
    {
        cout << endl;
        wypiszPrzerwePlansza();
        cout << kreska_pionowa;
        for (int j = 0; j < kolumny; j++)
        {
            cout << " ";
            if (plansza[i][j] == 1)
                cout << znak1;
            else if (plansza[i][j] == 2)
                cout << znak2;
            else
                cout << " ";
            cout << " ";
            cout << kreska_pionowa;
        }
        cout << "  ";
        cout << kreska_pionowa;
        for (int j = kolumny; j < kolumny * 2; j++)
        {
            cout << " ";
            if (plansza[i][j] == 1)
                cout << znak1;
            else if (plansza[i][j] == 2)
                cout << znak2;
            else
                cout << " ";
            cout << " ";
            cout << kreska_pionowa;
        }
        if (i != wiersze - 1)
        {
            cout << endl;
            wypiszPrzerwePlansza();

            cout << lacznik_lewy;
            for (int j = 0; j < kolumny; j++)
            {
                cout << kreska_pozioma << kreska_pozioma << kreska_pozioma;
                if (j != kolumny - 1)
                {
                    cout << lacznik;
                }
            }
            cout << lacznik_prawy;
            cout << "  ";

            cout << lacznik_lewy;
            for (int j = 0; j < kolumny; j++)
            {
                cout << kreska_pozioma << kreska_pozioma << kreska_pozioma;
                if (j != kolumny - 1)
                {
                    cout << lacznik;
                }
            }
            cout << lacznik_prawy;
        }
    }
    cout << endl;
    wypiszPrzerwePlansza();
    cout << lacznik_lewy_dolny;
    for (int i = 0; i < kolumny * 3 + kolumny - 1; i++)
    {
        if ((i + 1) % 4 == 0)
            cout << lacznik_dolny;
        else
            cout << kreska_pozioma;
    }
    cout << lacznik_prawy_dolny;
    cout << "  ";
    cout << lacznik_lewy_dolny;
    for (int i = 0; i < kolumny * 3 + kolumny - 1; i++)
    {
        if ((i + 1) % 4 == 0)
            cout << lacznik_dolny;
        else
            cout << kreska_pozioma;
    }
    cout << lacznik_prawy_dolny;
    cout << endl;
    wypiszPrzerwePlansza();
    cout << lacznik_lewy_gorny;
    for (int i = 0; i < kolumny * 3 + kolumny - 1; i++)
    {
        if ((i + 1) % 4 == 0)
            cout << lacznik_gorny;
        else
            cout << kreska_pozioma;
    }
    cout << lacznik_prawy_gorny;
    cout << "  ";
    cout << lacznik_lewy_gorny;
    for (int i = 0; i < kolumny * 3 + kolumny - 1; i++)
    {
        if ((i + 1) % 4 == 0)
            cout << lacznik_gorny;
        else
            cout << kreska_pozioma;
    }
    cout << lacznik_prawy_gorny;

    for (int i = wiersze; i < wiersze * 2; i++)
    {
        cout << endl;
        wypiszPrzerwePlansza();
        cout << kreska_pionowa;
        for (int j = 0; j < kolumny; j++)
        {
            cout << " ";
            if (plansza[i][j] == 1)
                cout << znak1;
            else if (plansza[i][j] == 2)
                cout << znak2;
            else
                cout << " ";
            cout << " ";
            cout << kreska_pionowa;
        }
        cout << "  ";
        cout << kreska_pionowa;
        for (int j = kolumny; j < kolumny * 2; j++)
        {
            cout << " ";
            if (plansza[i][j] == 1)
                cout << znak1;
            else if (plansza[i][j] == 2)
                cout << znak2;
            else
                cout << " ";
            cout << " ";
            cout << kreska_pionowa;
        }
        if (i != wiersze * 2 - 1)
        {
            cout << endl;
            wypiszPrzerwePlansza();

            cout << lacznik_lewy;
            for (int j = 0; j < kolumny; j++)
            {
                cout << kreska_pozioma << kreska_pozioma << kreska_pozioma;
                if (j != kolumny - 1)
                {
                    cout << lacznik;
                }
            }
            cout << lacznik_prawy;
            cout << "  ";

            cout << lacznik_lewy;
            for (int j = 0; j < kolumny; j++)
            {
                cout << kreska_pozioma << kreska_pozioma << kreska_pozioma;
                if (j != kolumny - 1)
                {
                    cout << lacznik;
                }
            }
            cout << lacznik_prawy;
        }
    }
    cout << endl;
    wypiszPrzerwePlansza();

    cout << lacznik_lewy_dolny;
    for (int i = 0; i < kolumny * 3 + kolumny - 1; i++)
    {
        if ((i + 1) % 4 == 0)
            cout << lacznik_dolny;
        else
            cout << kreska_pozioma;
    }
    cout << lacznik_prawy_dolny;
    cout << "  ";
    cout << lacznik_lewy_dolny;
    for (int i = 0; i < kolumny * 3 + kolumny - 1; i++)
    {
        if ((i + 1) % 4 == 0)
            cout << lacznik_dolny;
        else
            cout << kreska_pozioma;
    }
    cout << lacznik_prawy_dolny;

    cout << endl;
}

//funkcja sprawdza warunek wygranej

bool sprawdz_Wygrana(int tura, int plansza[wiersze * 2][kolumny * 2])
{

    int ile_zetonow = 0;

    //sprawdzanie wierszy
    for (int i = 0; i < wiersze * 2; i++)
    {
        ile_zetonow = 0;
        for (int j = 0; j < kolumny * 2; j++)
        {
            if (ile_zetonow < ilosc_zetonow)
            {
                if (plansza[i][j] == tura)
                    ile_zetonow++;
                else
                    ile_zetonow = 0;
            }
        }
        if (ile_zetonow >= ilosc_zetonow)
            return true;
    }
    //sprawdzanie kolumn
    for (int i = 0; i < kolumny * 2; i++)
    {
        ile_zetonow = 0;
        for (int j = 0; j < wiersze * 2; j++)
        {
            if (ile_zetonow < ilosc_zetonow)
            {
                if (plansza[j][i] == tura)
                    ile_zetonow++;
                else
                    ile_zetonow = 0;
            }
        }
        if (ile_zetonow >= ilosc_zetonow)
            return true;
    }
    //sprawdzanie przekatnych "\"

    //sprawdzenie pierwszej czesci przekatnych
    int i = wiersze * (-1);
    for (int g = 0; g < wiersze + 1; g++)
    {
        ile_zetonow = 0;
        for (int j = 1; j < wiersze * 2; j++)
        {
            if ((j + i - 1) >= 0)
            {
                if (ile_zetonow < ilosc_zetonow)
                {
                    if (plansza[j][j + i - 1] == tura)
                        ile_zetonow++;
                    else
                        ile_zetonow = 0;
                }
            }
        }
        i++;
        if (ile_zetonow >= ilosc_zetonow)
            return true;
    }

    //sprawdzenie głównej przekątnej
    ile_zetonow = 0;
    for (int j = 0; j < wiersze * 2; j++)
    {
        if (ile_zetonow < ilosc_zetonow)
        {
            if (plansza[j][j] == tura)
                ile_zetonow++;
            else
                ile_zetonow = 0;
        }
    }
    if (ile_zetonow >= ilosc_zetonow)
        return true;

    //sprawdzenie drugiej czesci przekatnych
    i = 1;
    for (int g = 0; g < wiersze + 1; g++)
    {
        ile_zetonow = 0;
        for (int j = 0; j < wiersze * 2 - 1; j++)
        {
            if ((j + i) < wiersze * 2)
            {
                if (ile_zetonow < ilosc_zetonow)
                {
                    if (plansza[j][j + i] == tura)
                        ile_zetonow++;
                    else
                        ile_zetonow = 0;
                }
            }
        }
        i++;
        if (ile_zetonow >= ilosc_zetonow)
            return true;
    }

    //sprawdzenie przekatnych "/"

    //sprawdzenie pierwszej czesci przekatnych
    i = 1;
    for (int g = 0; g < wiersze + 1; g++)
    {
        ile_zetonow = 0;
        for (int j = 0; j < wiersze * 2; j++)
        {
            if ((((j * 2) - i) * (-1)) >= 0)
            {
                if (ile_zetonow < ilosc_zetonow)
                {
                    if (plansza[j][(((j * 2) - i) * (-1))] == tura)
                        ile_zetonow++;
                    else
                        ile_zetonow = 0;
                }
            }
        }
        i++;
        if (ile_zetonow >= ilosc_zetonow)
            return true;
    }

    //sprawdzenie głównej przekatnej

    ile_zetonow = 0;
    int k = wiersze * 2 - 1;
    int m = 0;
    for (int j = 0; j < wiersze * 2; j++)
    {

        if (ile_zetonow < ilosc_zetonow)
        {
            if (plansza[m][k] == tura)
                ile_zetonow++;
            else
                ile_zetonow = 0;
        }
        m++;
        k--;
    }
    if (ile_zetonow >= ilosc_zetonow)
        return true;

    //sprawdzenie drugiej czesci przekatnych
    i = 9;
    for (int g = 0; g < wiersze + 1; g++)
    {
        ile_zetonow = 0;
        for (int j = 1; j < wiersze * 2; j++)
        {
            if (i - j < wiersze * 2)
            {
                if (ile_zetonow < ilosc_zetonow)
                {
                    if (plansza[j][j + i] == tura)
                        ile_zetonow++;
                    else
                        ile_zetonow = 0;
                }
            }
        }
        i--;
        if (ile_zetonow >= ilosc_zetonow)
            return true;
    }

    return false;
}

//funkcja wczytuje znaki reprezentujace zetony graczy

void wczytajZnaki(char &znak1, char &znak2, char imie1[], char imie2[])
{
    wypiszPrzerwe();
    cout << imie1 << " podaj znak reprezentujacy twoje zetony: ";
    cin >> znak1;

    bool inne_zetony = true;

    do
    {
        inne_zetony = true;
        wypiszPrzerwe();
        cout << imie2 << " podaj znak reprezentujacy twoje zetony: ";
        cin >> znak2;
        if (znak2 != znak1)
            inne_zetony = true;
        else
        {
            wypiszPrzerwe();
            cout << "Musisz podac inne zetony" << endl;
            inne_zetony = false;
        }
    } while (!inne_zetony);
}

//funkcja odpowiada za interpretacje pola przy cofaniu ruchu

bool cofnijRuch(int plansza[wiersze][kolumny], char pole, int tura, vector<char> &zapamietaneRuchy)
{
    switch (pole)
    {
    case '1':
    {
        if (plansza[2][0] != 0)
        {
            plansza[2][0] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '2':
    {
        if (plansza[2][1] != 0)
        {
            plansza[2][1] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '3':
    {
        if (plansza[2][2] != 0)
        {
            plansza[2][2] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '4':
    {
        if (plansza[1][0] != 0)
        {
            plansza[1][0] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '5':
    {
        if (plansza[1][1] != 0)
        {
            plansza[1][1] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '6':
    {
        if (plansza[1][2] != 0)
        {
            plansza[1][2] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '7':
    {
        if (plansza[0][0] != 0)
        {
            plansza[0][0] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '8':
    {
        if (plansza[0][1] != 0)
        {
            plansza[0][1] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '9':
    {
        if (plansza[0][2] != 0)
        {
            plansza[0][2] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    default:
    {
        return false;
    }
    }
}

//funkcja odpowiada za interpretacje pola przy wykonywaniu ruchu

bool wykonajRuch(int plansza[wiersze][kolumny], char pole, int tura, vector<char> &zapamietaneRuchy)
{
    switch (pole)
    {
    case '1':
    {
        if (plansza[2][0] == 0)
        {
            plansza[2][0] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '2':
    {
        if (plansza[2][1] == 0)
        {
            plansza[2][1] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '3':
    {
        if (plansza[2][2] == 0)
        {
            plansza[2][2] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '4':
    {
        if (plansza[1][0] == 0)
        {
            plansza[1][0] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '5':
    {
        if (plansza[1][1] == 0)
        {
            plansza[1][1] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '6':
    {
        if (plansza[1][2] == 0)
        {
            plansza[1][2] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '7':
    {
        if (plansza[0][0] == 0)
        {
            plansza[0][0] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '8':
    {
        if (plansza[0][1] == 0)
        {
            plansza[0][1] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    case '9':
    {
        if (plansza[0][2] == 0)
        {
            plansza[0][2] = tura;
            zapamietaneRuchy.push_back(pole);
            return true;
        }
        else
            return false;
        break;
    }
    default:
    {
        return false;
    }
    }
}

//funkcja odpowiada za mozliwosc przegladania rozgrywki po jej zakonczeniu

void przegladajRozgrywke(int plansza1[wiersze][kolumny], int plansza2[wiersze][kolumny], int plansza3[wiersze][kolumny], int plansza4[wiersze][kolumny], vector<char> zapamietaneRuchy, bool pentago, int tura, char znak1, char znak2)
{
    bool flaga = true;
    int wskaznik = (int)((int)(zapamietaneRuchy.size()) - 1);
    if (tura == 1)
        tura = 2;
    else
        tura = 1;
    while (flaga)
    {
        cout << endl;
        wypiszPrzerwe();
        if (pentago)
        {
            if (wskaznik != -1)
                cout << "Ostatni wykonany ruch: " << zapamietaneRuchy[wskaznik - 3] << zapamietaneRuchy[wskaznik - 2] << zapamietaneRuchy[wskaznik - 1] << zapamietaneRuchy[wskaznik] << endl;
        }
        else
        {
            if (wskaznik != -1)
                cout << "Ostatni wykonany ruch: " << zapamietaneRuchy[wskaznik - 1] << zapamietaneRuchy[wskaznik] << endl;
        }
        cout << endl;
        wypiszPrzerwe();
        cout << "1. Przegladaj w przod" << endl;
        wypiszPrzerwe();
        cout << "2. Przegladaj w tyl" << endl;
        wypiszPrzerwe();
        cout << "3. Zakoncz przegladanie" << endl;
        wypiszPrzerwe();
        cout << "Twoj wybor: ";
        char wybor;
        cin >> wybor;
        switch (wybor)
        {
        case '1':
        {
            if (wskaznik != (zapamietaneRuchy.size() - 1))
            {
                if (pentago)
                {
                    char planszaPierwsza = zapamietaneRuchy[wskaznik + 1];
                    char pole = zapamietaneRuchy[wskaznik + 2];
                    char planszaDruga = zapamietaneRuchy[wskaznik + 3];
                    char kierunek = zapamietaneRuchy[wskaznik + 4];
                    wskaznik += 4;
                    vector<char> wektorPomocniczy;
                    if (planszaPierwsza == 'q')
                    {
                        wykonajRuch(plansza1, pole, tura, wektorPomocniczy);
                    }
                    else if (planszaPierwsza == 'w')
                    {
                        wykonajRuch(plansza2, pole, tura, wektorPomocniczy);
                    }
                    else if (planszaPierwsza == 'a')
                    {
                        wykonajRuch(plansza3, pole, tura, wektorPomocniczy);
                    }
                    else if (planszaPierwsza == 's')
                    {
                        wykonajRuch(plansza4, pole, tura, wektorPomocniczy);
                    }
                    if (planszaDruga == 'q')
                    {
                        int obroconaPlansza[wiersze][kolumny];
                        if (kierunek == 'z')
                        {
                            obrocPlanszeZgodnie(plansza1, obroconaPlansza);
                            ustawPlansze(plansza1, obroconaPlansza);
                        }
                        else if (kierunek == 'x')
                        {
                            obrocPlanszePrzeciwnie(plansza1, obroconaPlansza);
                            ustawPlansze(plansza1, obroconaPlansza);
                        }
                    }
                    if (planszaDruga == 'w')
                    {
                        int obroconaPlansza[wiersze][kolumny];
                        if (kierunek == 'z')
                        {
                            obrocPlanszeZgodnie(plansza2, obroconaPlansza);
                            ustawPlansze(plansza2, obroconaPlansza);
                        }
                        else if (kierunek == 'x')
                        {
                            obrocPlanszePrzeciwnie(plansza2, obroconaPlansza);
                            ustawPlansze(plansza2, obroconaPlansza);
                        }
                    }
                    if (planszaDruga == 'a')
                    {
                        int obroconaPlansza[wiersze][kolumny];
                        if (kierunek == 'z')
                        {
                            obrocPlanszeZgodnie(plansza3, obroconaPlansza);
                            ustawPlansze(plansza3, obroconaPlansza);
                        }
                        else if (kierunek == 'x')
                        {
                            obrocPlanszePrzeciwnie(plansza3, obroconaPlansza);
                            ustawPlansze(plansza3, obroconaPlansza);
                        }
                    }
                    if (planszaDruga == 's')
                    {
                        int obroconaPlansza[wiersze][kolumny];
                        if (kierunek == 'z')
                        {
                            obrocPlanszeZgodnie(plansza4, obroconaPlansza);
                            ustawPlansze(plansza4, obroconaPlansza);
                        }
                        else if (kierunek == 'x')
                        {
                            obrocPlanszePrzeciwnie(plansza4, obroconaPlansza);
                            ustawPlansze(plansza4, obroconaPlansza);
                        }
                    }
                }
                else
                {
                    char planszaPierwsza = zapamietaneRuchy[wskaznik + 1];
                    char pole = zapamietaneRuchy[wskaznik + 2];
                    wskaznik += 2;
                    vector<char> wektorPomocniczy;
                    if (planszaPierwsza == 'q')
                    {
                        wykonajRuch(plansza1, pole, tura, wektorPomocniczy);
                    }
                    else if (planszaPierwsza == 'w')
                    {
                        wykonajRuch(plansza2, pole, tura, wektorPomocniczy);
                    }
                    else if (planszaPierwsza == 'a')
                    {
                        wykonajRuch(plansza3, pole, tura, wektorPomocniczy);
                    }
                    else if (planszaPierwsza == 's')
                    {
                        wykonajRuch(plansza4, pole, tura, wektorPomocniczy);
                    }
                }
                cout << endl;
                wypiszOdstep();
                int sklejonaPlansza[wiersze * 2][kolumny * 2];
                sklejPlansze(plansza1, plansza2, plansza3, plansza4, sklejonaPlansza);
                rysuj(sklejonaPlansza, znak1, znak2);
                if (tura == 2)
                    tura = 1;
                else
                    tura = 2;
            }
            else
            {
                wypiszPrzerwe();
                cout << "Nie mozna przegladac w przod";
            }
            break;
        }
        case '2':
        {
            if (wskaznik != -1)
            {
                if (pentago)
                {
                    char kierunek = zapamietaneRuchy[wskaznik];
                    char planszaPierwsza = zapamietaneRuchy[wskaznik - 1];
                    char pole = zapamietaneRuchy[wskaznik - 2];
                    char planszaDruga = zapamietaneRuchy[wskaznik - 3];
                    wskaznik = wskaznik - 4;
                    vector<char> wektorPomocniczy = {};
                    int obroconaPlansza[wiersze][kolumny];

                    if (planszaPierwsza == 'q')
                    {
                        if (kierunek == 'x')
                        {
                            obrocPlanszeZgodnie(plansza1, obroconaPlansza);
                            ustawPlansze(plansza1, obroconaPlansza);
                        }
                        else if (kierunek == 'z')
                        {
                            obrocPlanszePrzeciwnie(plansza1, obroconaPlansza);
                            ustawPlansze(plansza1, obroconaPlansza);
                        }
                    }
                    else if (planszaPierwsza == 'w')
                    {
                        if (kierunek == 'x')
                        {
                            obrocPlanszeZgodnie(plansza2, obroconaPlansza);
                            ustawPlansze(plansza2, obroconaPlansza);
                        }
                        else if (kierunek == 'z')
                        {
                            obrocPlanszePrzeciwnie(plansza2, obroconaPlansza);
                            ustawPlansze(plansza2, obroconaPlansza);
                        }
                    }
                    else if (planszaPierwsza == 'a')
                    {
                        if (kierunek == 'x')
                        {
                            obrocPlanszeZgodnie(plansza3, obroconaPlansza);
                            ustawPlansze(plansza3, obroconaPlansza);
                        }
                        else if (kierunek == 'z')
                        {
                            obrocPlanszePrzeciwnie(plansza3, obroconaPlansza);
                            ustawPlansze(plansza3, obroconaPlansza);
                        }
                    }
                    else if (planszaPierwsza == 's')
                    {
                        if (kierunek == 'x')
                        {
                            obrocPlanszeZgodnie(plansza4, obroconaPlansza);
                            ustawPlansze(plansza4, obroconaPlansza);
                        }
                        else if (kierunek == 'z')
                        {
                            obrocPlanszePrzeciwnie(plansza4, obroconaPlansza);
                            ustawPlansze(plansza4, obroconaPlansza);
                        }
                    }
                    if (planszaDruga == 'q')
                        cofnijRuch(plansza1, pole, 0, wektorPomocniczy);
                    else if (planszaDruga == 'w')
                        cofnijRuch(plansza2, pole, 0, wektorPomocniczy);
                    else if (planszaDruga == 'a')
                        cofnijRuch(plansza3, pole, 0, wektorPomocniczy);
                    else if (planszaDruga == 's')
                        cofnijRuch(plansza4, pole, 0, wektorPomocniczy);
                }
                else
                {
                    char pole = zapamietaneRuchy[wskaznik];
                    char plansza = zapamietaneRuchy[wskaznik - 1];
                    wskaznik -= 2;
                    vector<char> wektorPomocniczy;
                    if (plansza == 'q')
                        cofnijRuch(plansza1, pole, 0, wektorPomocniczy);
                    else if (plansza == 'w')
                        cofnijRuch(plansza2, pole, 0, wektorPomocniczy);
                    else if (plansza == 'a')
                        cofnijRuch(plansza3, pole, 0, wektorPomocniczy);
                    else if (plansza == 's')
                        cofnijRuch(plansza4, pole, 0, wektorPomocniczy);
                }
                cout << endl;
                wypiszOdstep();
                int sklejonaPlansza[wiersze * 2][kolumny * 2];
                sklejPlansze(plansza1, plansza2, plansza3, plansza4, sklejonaPlansza);
                rysuj(sklejonaPlansza, znak1, znak2);
                if (tura == 1)
                    tura = 2;
                else
                    tura = 1;
            }
            else
            {
                wypiszPrzerwe();
                cout << "Nie mozna przegladac w tyl";
            }
            break;
        }
        case '3':
        {
            flaga = false;
            break;
        }
        default:
        {
            break;
        }
        }
    }
}

//funkcja odpowiada za obsluge cofania ruchu

bool undo(bool pentago, vector<char> &zapamietaneRuchy, int plansza1[wiersze][kolumny], int plansza2[wiersze][kolumny], int plansza3[wiersze][kolumny], int plansza4[wiersze][kolumny])
{
    if (zapamietaneRuchy.size() != 0)
    {
        if (pentago)
        {
            char kierunek = zapamietaneRuchy[zapamietaneRuchy.size() - 1];
            zapamietaneRuchy.pop_back();
            char planszaPierwsza = zapamietaneRuchy[zapamietaneRuchy.size() - 1];
            zapamietaneRuchy.pop_back();
            char pole = zapamietaneRuchy[zapamietaneRuchy.size() - 1];
            zapamietaneRuchy.pop_back();
            char planszaDruga = zapamietaneRuchy[zapamietaneRuchy.size() - 1];
            zapamietaneRuchy.pop_back();
            vector<char> wektorPomocniczy;
            int obroconaPlansza[wiersze][kolumny];

            if (planszaPierwsza == 'q')
            {
                if (kierunek == 'x')
                {
                    obrocPlanszeZgodnie(plansza1, obroconaPlansza);
                    ustawPlansze(plansza1, obroconaPlansza);
                }
                else if (kierunek == 'z')
                {
                    obrocPlanszePrzeciwnie(plansza1, obroconaPlansza);
                    ustawPlansze(plansza1, obroconaPlansza);
                }
            }
            else if (planszaPierwsza == 'w')
            {
                if (kierunek == 'x')
                {
                    obrocPlanszeZgodnie(plansza2, obroconaPlansza);
                    ustawPlansze(plansza2, obroconaPlansza);
                }
                else if (kierunek == 'z')
                {
                    obrocPlanszePrzeciwnie(plansza2, obroconaPlansza);
                    ustawPlansze(plansza2, obroconaPlansza);
                }
            }
            else if (planszaPierwsza == 'a')
            {
                if (kierunek == 'x')
                {
                    obrocPlanszeZgodnie(plansza3, obroconaPlansza);
                    ustawPlansze(plansza3, obroconaPlansza);
                }
                else if (kierunek == 'z')
                {
                    obrocPlanszePrzeciwnie(plansza3, obroconaPlansza);
                    ustawPlansze(plansza3, obroconaPlansza);
                }
            }
            else if (planszaPierwsza == 's')
            {
                if (kierunek == 'x')
                {
                    obrocPlanszeZgodnie(plansza4, obroconaPlansza);
                    ustawPlansze(plansza4, obroconaPlansza);
                }
                else if (kierunek == 'z')
                {
                    obrocPlanszePrzeciwnie(plansza4, obroconaPlansza);
                    ustawPlansze(plansza4, obroconaPlansza);
                }
            }
            if (planszaDruga == 'q')
                cofnijRuch(plansza1, pole, 0, wektorPomocniczy);
            else if (planszaDruga == 'w')
                cofnijRuch(plansza2, pole, 0, wektorPomocniczy);
            else if (planszaDruga == 'a')
                cofnijRuch(plansza3, pole, 0, wektorPomocniczy);
            else if (planszaDruga == 's')
                cofnijRuch(plansza4, pole, 0, wektorPomocniczy);
        }
        else
        {
            char pole = zapamietaneRuchy[zapamietaneRuchy.size() - 1];
            zapamietaneRuchy.pop_back();
            char plansza = zapamietaneRuchy[zapamietaneRuchy.size() - 1];
            zapamietaneRuchy.pop_back();
            vector<char> wektorPomocniczy;
            if (plansza == 'q')
                cofnijRuch(plansza1, pole, 0, wektorPomocniczy);
            else if (plansza == 'w')
                cofnijRuch(plansza2, pole, 0, wektorPomocniczy);
            else if (plansza == 'a')
                cofnijRuch(plansza3, pole, 0, wektorPomocniczy);
            else if (plansza == 's')
                cofnijRuch(plansza4, pole, 0, wektorPomocniczy);
        }
        return true;
    }
    else
    {
        wypiszPrzerwe();
        cout << "Nie mozna cofnac ruchu!" << endl;
        return false;
    }
}

//funkcja odpowiada za wczytanie predefiniowanej planszy

void predefiniowanaPlansza(int plansza1[wiersze][kolumny], int plansza2[wiersze][kolumny], int plansza3[wiersze][kolumny], int plansza4[wiersze][kolumny])
{
    plansza1[0][0] = 0;
    plansza1[0][1] = 2;
    plansza1[0][2] = 0;
    plansza1[1][0] = 1;
    plansza1[1][1] = 1;
    plansza1[1][2] = 2;
    plansza1[2][0] = 0;
    plansza1[2][1] = 1;
    plansza1[2][2] = 0;

    plansza2[0][0] = 0;
    plansza2[0][1] = 1;
    plansza2[0][2] = 0;
    plansza2[1][0] = 1;
    plansza2[1][1] = 2;
    plansza2[1][2] = 0;
    plansza2[2][0] = 0;
    plansza2[2][1] = 0;
    plansza2[2][2] = 0;

    plansza3[0][0] = 1;
    plansza3[0][1] = 1;
    plansza3[0][2] = 0;
    plansza3[1][0] = 2;
    plansza3[1][1] = 0;
    plansza3[1][2] = 1;
    plansza3[2][0] = 0;
    plansza3[2][1] = 2;
    plansza3[2][2] = 0;

    plansza4[0][0] = 0;
    plansza4[0][1] = 0;
    plansza4[0][2] = 0;
    plansza4[1][0] = 0;
    plansza4[1][1] = 2;
    plansza4[1][2] = 0;
    plansza4[2][0] = 0;
    plansza4[2][1] = 2;
    plansza4[2][2] = 2;
}

//funkcja odpowiada za interpretacje pierwszego znaku wpisanego przez gracza, wyswietlenie menu itp.

void graj(bool &czyWygrana, int &turaGracza, int plansza1[wiersze][kolumny], int plansza2[wiersze][kolumny], int plansza3[wiersze][kolumny], int plansza4[wiersze][kolumny], char imie1[20], char imie2[20], int &runda, bool pentago, char &znak1, char &znak2, float &czasNaOpcje, vector<char> &zapamietaneRuchy, float czasy[2], float &czasNaPauze, bool &predefiniowana_Plansza)
{
    czasNaOpcje = 0;

    if (turaGracza == 1)
    {
        wypiszPrzerwe();
        cout << "Tura gracza: " << imie1 << " (zetony czerwone(" << znak1 << "))" << endl;
    }
    else
    {
        wypiszPrzerwe();
        cout << "Tura gracza: " << imie2 << " (zetony niebieskie(" << znak2 << "))" << endl;
    }
    char plansza;
    char pole;
    bool niepoprawny_ruch = false;

    do
    {
        niepoprawny_ruch = false;
        wypiszPrzerwe();
        cout << "Podaj plansze i numer pola: ";
        cin >> plansza;

        if (plansza == 'q')
        {
            cin >> pole;
            zapamietaneRuchy.push_back(plansza);
            if (wykonajRuch(plansza1, pole, turaGracza, zapamietaneRuchy))
            {

                niepoprawny_ruch = false;
            }
            else
            {
                wypiszPrzerwe();
                cout << "Niepoprawny ruch" << endl;
                niepoprawny_ruch = true;
            }
        }
        else if (plansza == 'w')
        {
            cin >> pole;
            zapamietaneRuchy.push_back(plansza);
            if (wykonajRuch(plansza2, pole, turaGracza, zapamietaneRuchy))
            {

                niepoprawny_ruch = false;
            }
            else
            {
                wypiszPrzerwe();
                cout << "Niepoprawny ruch" << endl;
                niepoprawny_ruch = true;
            }
        }
        else if (plansza == 'a')
        {
            cin >> pole;
            zapamietaneRuchy.push_back(plansza);
            if (wykonajRuch(plansza3, pole, turaGracza, zapamietaneRuchy))
            {

                niepoprawny_ruch = false;
            }
            else
            {
                wypiszPrzerwe();
                cout << "Niepoprawny ruch" << endl;
                niepoprawny_ruch = true;
            }
        }
        else if (plansza == 's')
        {
            cin >> pole;
            zapamietaneRuchy.push_back(plansza);
            if (wykonajRuch(plansza4, pole, turaGracza, zapamietaneRuchy))
            {

                niepoprawny_ruch = false;
            }
            else
            {
                wypiszPrzerwe();
                cout << "Niepoprawny ruch" << endl;
                niepoprawny_ruch = true;
            }
        }
        else if (plansza == 'm')
        {
            time_t begin, end;
            time(&begin);
            wypiszOdstep();
            wypiszPrzerwe();
            cout << "Opcje: " << endl;
            char wybor;
            wypiszPrzerwe();
            cout << "1. Zmien zetony" << endl;
            wypiszPrzerwe();
            cout << "0. Wyjdz z opcji" << endl;
            wypiszPrzerwe();
            cin >> wybor;
            switch (wybor)
            {
            case '1':
            {
                zmienZetony(znak1, znak2, imie1, imie2);
                wypiszPrzerwe();
                cout << "Poprawnie zmienione zetony" << endl;
                int sklejonaplansza[wiersze * 2][kolumny * 2];
                sklejPlansze(plansza1, plansza2, plansza3, plansza4, sklejonaplansza);
                rysuj(sklejonaplansza, znak1, znak2);
                niepoprawny_ruch = true;
                break;
            }
            case '0':
            {
                break;
            }
            default:
            {
                cout << "Niepoprawny wybor";
            }
            }
            time(&end);
            czasNaOpcje = end - begin;
        }
        else if (plansza == 'u')
        {

            if (!predefiniowana_Plansza)
            {
                if (undo(pentago, zapamietaneRuchy, plansza1, plansza2, plansza3, plansza4))
                {
                    if (turaGracza == 1)
                    {
                        turaGracza = 2;
                        runda--;
                    }
                    else
                    {
                        turaGracza = 1;
                    }
                    wypiszOdstep();
                    wypiszPrzerwe();
                    cout << "Runda: " << runda << "!" << endl;
                    wypiszPrzerwe();
                    cout << "Wpisz "
                         << "h"
                         << " aby uzyskac potrzebne komendy" << endl
                         << endl;
                    wypiszPrzerwe();
                    cout << "Twoj czas: " << czasy[turaGracza - 1] << "s" << endl;

                    int sklejonaPlansza[wiersze * 2][kolumny * 2];
                    sklejPlansze(plansza1, plansza2, plansza3, plansza4, sklejonaPlansza);
                    rysuj(sklejonaPlansza, znak1, znak2);
                    if (turaGracza == 1)
                    {
                        wypiszPrzerwe();
                        cout << "Tura gracza: " << imie1 << " (zetony czerwone(" << znak1 << "))" << endl;
                    }
                    else
                    {
                        wypiszPrzerwe();
                        cout << "Tura gracza: " << imie2 << " (zetony niebieskie(" << znak2 << "))" << endl;
                    }
                    niepoprawny_ruch = true;
                }
                else
                {
                    niepoprawny_ruch = true;
                }
            }
            else
            {
                cout << endl;
                wypiszPrzerwe();
                cout << "W przypadku wczytania planszy predefiniowanej nie mozna uzywac cofania ruchu" << endl;
            }
        }

        else if (plansza == 'h')
        {
            wypiszPrzerwe();
            cout << "Aby wykonac ruch wpisz q,w,a lub s aby wybrac plansze oraz nr od 1 do 9 aby wybrac pole" << endl;
            wypiszPrzerwe();
            cout << "Grajac w pentago ponownie wybierz plansze i wpisujac x lub z wybierz kierunek jej obrotu" << endl;
            wypiszPrzerwe();
            cout << "Wpisanie litery m spowoduje wejscie do opcji" << endl;
            wypiszPrzerwe();
            cout << "Wpisanie litery u spowoduje cofniecie ruchu" << endl;
            wypiszPrzerwe();
            cout << "Wpisanie litery p spowoduje uruchomienie pauzy" << endl;
            wypiszPrzerwe();
            cout << "Wpisanie litery o spowoduje wczytanie planszy predefiniowanej" << endl;

            niepoprawny_ruch = true;
        }
        else if (plansza == 'o')
        {
            predefiniowanaPlansza(plansza1, plansza2, plansza3, plansza4);
            predefiniowana_Plansza = true;
            runda = 9;
            turaGracza = 1;
            wypiszOdstep();
            wypiszPrzerwe();
            cout << "Runda: " << runda << "!" << endl;
            wypiszPrzerwe();
            cout << "Wpisz "
                 << "h"
                 << " aby uzyskac potrzebne komendy" << endl
                 << endl;
            wypiszPrzerwe();
            cout << "Twoj czas: " << czasy[turaGracza - 1] << "s" << endl;

            int sklejonaPlansza[wiersze * 2][kolumny * 2];
            sklejPlansze(plansza1, plansza2, plansza3, plansza4, sklejonaPlansza);
            rysuj(sklejonaPlansza, znak1, znak2);
            if (turaGracza == 1)
            {
                wypiszPrzerwe();
                cout << "Tura gracza: " << imie1 << " (zetony czerwone(" << znak1 << "))" << endl;
            }
            else
            {
                wypiszPrzerwe();
                cout << "Tura gracza: " << imie2 << " (zetony niebieskie(" << znak2 << "))" << endl;
            }
            niepoprawny_ruch = true;
        }
        else if (plansza == 'p')
        {
            time_t begin, end;
            time(&begin);
            wypiszOdstep();
            wypiszPrzerwePlansza();
            cout << "    PAUZA" << endl
                 << endl
                 << endl;
            wypiszPrzerwe();
            cout << "Wpisz dowolny znak i nacisnij enter aby przerwac pauze" << endl;
            wypiszPrzerwe();
            string dowolnyZnak;
            cin >> dowolnyZnak;
            time(&end);
            czasNaPauze = end - begin;

            wypiszOdstep();
            wypiszPrzerwe();
            cout << "Runda: " << runda << "!" << endl;
            wypiszPrzerwe();
            cout << "Wpisz "
                 << "h"
                 << " aby uzyskac potrzebne komendy" << endl
                 << endl;
            wypiszPrzerwe();
            cout << "Twoj czas: " << czasy[turaGracza - 1] << "s" << endl;

            int sklejonaPlansza[wiersze * 2][kolumny * 2];
            sklejPlansze(plansza1, plansza2, plansza3, plansza4, sklejonaPlansza);
            rysuj(sklejonaPlansza, znak1, znak2);
            if (turaGracza == 1)
            {
                wypiszPrzerwe();
                cout << "Tura gracza: " << imie1 << " (zetony czerwone(" << znak1 << "))" << endl;
            }
            else
            {
                wypiszPrzerwe();
                cout << "Tura gracza: " << imie2 << " (zetony niebieskie(" << znak2 << "))" << endl;
            }
            niepoprawny_ruch = true;
        }
        else
        {
            wypiszPrzerwe();
            cout << "Niepoprawny ruch" << endl;
            niepoprawny_ruch = true;
        }
    } while (niepoprawny_ruch);

    if (pentago)
    {
        char kierunek;
        niepoprawny_ruch = false;
        int obroconaPlansza[wiersze][kolumny];
        do
        {
            niepoprawny_ruch = false;
            wypiszPrzerwe();
            cout << "Podaj oznaczenie planszy i kierunek obrotu: ";
            cin >> plansza;
            if (plansza == 'q')
            {
                zapamietaneRuchy.push_back(plansza);
                cin >> kierunek;
                if (kierunek == 'z')
                {
                    obrocPlanszeZgodnie(plansza1, obroconaPlansza);
                    ustawPlansze(plansza1, obroconaPlansza);
                    zapamietaneRuchy.push_back(kierunek);
                    niepoprawny_ruch = false;
                }
                else if (kierunek == 'x')
                {
                    obrocPlanszePrzeciwnie(plansza1, obroconaPlansza);
                    ustawPlansze(plansza1, obroconaPlansza);
                    zapamietaneRuchy.push_back(kierunek);
                    niepoprawny_ruch = false;
                }
                else
                {
                    wypiszPrzerwe();
                    cout << "Niepoprawny ruch!" << endl;
                    niepoprawny_ruch = true;
                }
            }
            else if (plansza == 'w')
            {
                zapamietaneRuchy.push_back(plansza);
                cin >> kierunek;
                if (kierunek == 'z')
                {
                    obrocPlanszeZgodnie(plansza2, obroconaPlansza);
                    ustawPlansze(plansza2, obroconaPlansza);
                    zapamietaneRuchy.push_back(kierunek);
                    niepoprawny_ruch = false;
                }
                else if (kierunek == 'x')
                {
                    obrocPlanszePrzeciwnie(plansza2, obroconaPlansza);
                    ustawPlansze(plansza2, obroconaPlansza);
                    zapamietaneRuchy.push_back(kierunek);
                    niepoprawny_ruch = false;
                }
                else
                {
                    wypiszPrzerwe();
                    cout << "Niepoprawny ruch!" << endl;
                    niepoprawny_ruch = true;
                }
            }
            else if (plansza == 'a')
            {
                zapamietaneRuchy.push_back(plansza);
                cin >> kierunek;
                if (kierunek == 'z')
                {
                    obrocPlanszeZgodnie(plansza3, obroconaPlansza);
                    ustawPlansze(plansza3, obroconaPlansza);
                    zapamietaneRuchy.push_back(kierunek);
                    niepoprawny_ruch = false;
                }
                else if (kierunek == 'x')
                {
                    obrocPlanszePrzeciwnie(plansza3, obroconaPlansza);
                    ustawPlansze(plansza3, obroconaPlansza);
                    zapamietaneRuchy.push_back(kierunek);
                    niepoprawny_ruch = false;
                }
                else
                {
                    wypiszPrzerwe();
                    cout << "Niepoprawny ruch!" << endl;
                    niepoprawny_ruch = true;
                }
            }
            else if (plansza == 's')
            {
                zapamietaneRuchy.push_back(plansza);
                cin >> kierunek;
                if (kierunek == 'z')
                {
                    obrocPlanszeZgodnie(plansza4, obroconaPlansza);
                    ustawPlansze(plansza4, obroconaPlansza);
                    zapamietaneRuchy.push_back(kierunek);
                    niepoprawny_ruch = false;
                }
                else if (kierunek == 'x')
                {
                    obrocPlanszePrzeciwnie(plansza4, obroconaPlansza);
                    ustawPlansze(plansza4, obroconaPlansza);
                    zapamietaneRuchy.push_back(kierunek);
                    niepoprawny_ruch ;
                }
                else
                {
                    wypiszPrzerwe();
                    cout << "Niepoprawny ruch!" << endl;
                    niepoprawny_ruch = true;
                }
            }
            else
            {
                wypiszPrzerwe();
                cout << "Niepoprawny ruch!" << endl;
                niepoprawny_ruch = true;
            }

        } while (niepoprawny_ruch);

        wypiszPrzerwe();
        cout << "Poprawny ruch!" << endl;
    }
}

//funkcja odpowiada za stworzenie wszystkich potrzebnych zmiennych i obsluge calej gry

void gra()
{
    bool pentago = false;
    bool predefiniowana_Plansza = false;
    char wybor;
    wypiszPrzerwe();
    cout << "Wybierz gre: " << endl;
    wypiszPrzerwe();
    cout << "1. Kolko i kryzyk" << endl;
    wypiszPrzerwe();
    cout << "2. Pentago" << endl;

    bool poprawnyWybor = true;

    do
    {
        wybor = ' ';
        wypiszPrzerwe();
        cout << "Twoj wybor: ";
        cin >> wybor;
        switch (wybor)
        {
        case '1':
        {
            poprawnyWybor = true;
            break;
        }
        case '2':
        {
            poprawnyWybor = true;
            pentago = true;
            break;
        }
        default:
        {
            poprawnyWybor = false;
            wypiszPrzerwe();
            cout << "Niepoprawny wybor" << endl;
            break;
        }
        }
    } while (!poprawnyWybor);

    char imie1[20];
    char imie2[20];
    char znak1;
    char znak2;
    wczytajImiona(imie1, imie2);
    wczytajZnaki(znak1, znak2, imie1, imie2);
    float czas;
    bool przegranaPrzezCzas = false;
    wypiszPrzerwe();
    cout << "Wpisz czas dostepny dla gracza(w sekundach): ";
    cin >> czas;
    float czasy[2] = {czas, czas};
    float czasNaOpcje = 0;
    float czasNaPauze = 0;
    int plansza1[wiersze][kolumny] = {};
    int plansza2[wiersze][kolumny] = {};
    int plansza3[wiersze][kolumny] = {};
    int plansza4[wiersze][kolumny] = {};
    int turaGracza = 1;
    int runda = 1;
    bool czyWygrana = false;
    int sklejonaPlansza[wiersze * 2][kolumny * 2] = {};
    vector<char> zapamietaneRuchy;

    while (!czyWygrana && runda < 19)
    {

        wypiszOdstep();
        wypiszPrzerwe();
        cout << "Runda: " << runda << "!" << endl;
        wypiszPrzerwe();
        cout << "Wpisz "
             << "h"
             << " aby uzyskac potrzebne komendy" << endl
             << endl;
        wypiszPrzerwe();
        cout << "Twoj czas: " << czasy[turaGracza - 1] << "s" << endl;
        rysuj(sklejonaPlansza, znak1, znak2);
        time_t begin, end;
        time(&begin);
        graj(czyWygrana, turaGracza, plansza1, plansza2, plansza3, plansza4, imie1, imie2, runda, pentago, znak1, znak2, czasNaOpcje, zapamietaneRuchy, czasy, czasNaPauze, predefiniowana_Plansza);
        time(&end);
        czasy[turaGracza - 1] = floor(czasy[turaGracza - 1] - (end - begin) + czasNaOpcje + czasNaPauze);
        sklejPlansze(plansza1, plansza2, plansza3, plansza4, sklejonaPlansza);

        czyWygrana = sprawdz_Wygrana(turaGracza, sklejonaPlansza);

        if (czasy[turaGracza - 1] <= 0)
        {
            turaGracza++;
            czyWygrana = true;
            przegranaPrzezCzas = true;
            break;
        }

        if (czyWygrana)
            break;
        if (turaGracza == 1)
            turaGracza = 2;
        else
        {
            turaGracza = 1;
            runda++;
        }
    }

    if (czyWygrana)
    {

        wypiszOdstep();
        cout << "Runda: " << runda << "!" << endl;
        rysuj(sklejonaPlansza, znak1, znak2);
        wypiszPrzerwe();
        if (turaGracza == 1)
            cout << "Wygrana gracza " << imie1 << endl;
        else
            cout << "Wygrana gracza:  " << imie2 << endl
                 << endl
                 << endl;
        if (przegranaPrzezCzas)
        {
            wypiszPrzerwe();
            cout << "Czas twojego przeciwnika sie skonczyl" << endl;
        }
    }
    else
    {
        wypiszPrzerwe();
        cout << "Remis" << endl;
    }

    if (!predefiniowana_Plansza)
    {
        przegladajRozgrywke(plansza1, plansza2, plansza3, plansza4, zapamietaneRuchy, pentago, turaGracza, znak1, znak2);
    }
    else
    {
        cout << endl;
        wypiszPrzerwe();
        cout << "W przypadku wczytania planszy predefiniowanej nie mozna przegladac rozgrywki po jej zakonczeniu";
    }
}

int main()
{
    gra();

    return 0;
}
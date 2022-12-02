#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <time.h>
#include <iomanip>
#include <sstream>

using namespace std;
#define URLAUB 30
#define MAXIMUM_MITARBEITER 1

void startmenue();
void startview();
void mitarbeiter_anlegen();
void mitarbeiter_ausgeben();
void mitarbeiter_suchen();
void mitarbeiterview(int id);
void mitarbeitermenue(int id);
void mitarbeiter_loeschen(int id);
int urlaubs_Anspruch_Berechnen(tm geburtsDatum);

void urlaub_anlegen(int id);

void resturlaub_ausgeben(int id);

int personalnummer = 0;
int perszaehler = 0;

typedef struct
{
    int personalnummer = -1;
    int urlaub;
    int resturlaub;
    tm geburtstag;
    char name[50];
    char vorname[50];

} mitarbeiter;

mitarbeiter m[MAXIMUM_MITARBEITER];

ostream &operator<<(ostream &os, mitarbeiter const &arg)
{
    os << "Personalnummer: " << arg.personalnummer << endl;
    os << "Vorname: " << arg.vorname << endl;
    os << "Name: " << arg.name << endl;
    os << "Geburtstag: " << put_time(&arg.geburtstag, "%d.%m.%Y") << endl;
    os << "Urlaub: " << arg.urlaub << endl;
    os << "Resturlaub: " << arg.resturlaub << endl;
    cout << "--------------------------------------------------------------------------------" << endl;

    return os;
}

int main()
{
    // Menüauswahl
    startview();
    startmenue();
    // PROGRAMMENDE
}

void startview()
{
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "--------------------------------<< ESA 1 cpp >>---------------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "- 1> Mitarbeiter anlegen -" << endl;
    cout << "- 2> Mitarbeiterliste anzeigen -" << endl;
    cout << "- 3> Mitarbeiter suchen -" << endl;
    cout << "- 9> Programm beenden -" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Ihre Auswahl: ";
}

void mitarbeiterview()
{
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "--------------------------------<< Untermenu Mitarbeiter >>---------------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "- 1> Urlaub einreichen -" << endl;
    cout << "- 2> Resturlaub einsehen -" << endl;
    cout << "- 3> Mitarbeiter löschen -" << endl;

    cout << "- 9> zurück zum Hauptmenu -" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Ihre Auswahl: ";
}

void mitarbeitermenue(int id)
{
    // AUSWAHL MITARBEITERMENUE
    char eingabe;
    while (1)
    {
        eingabe = getchar();
        fflush(stdin);
        switch (eingabe)
        {
        case '1':
            urlaub_anlegen(id);
            break;
        case '2':
            resturlaub_ausgeben(id);
            break;
        case '3':
            mitarbeiter_loeschen(id);
            break;
        case '9':
            startview();
        default:
            break;
        }
    }
}

void resturlaub_ausgeben(int id)
{
    cout << m[id].resturlaub << " Tage eingereicht" << endl;
    mitarbeiterview();
}
int urlaubs_Anspruch_Berechnen(tm geburtsDatum)
{
    int anspruch = URLAUB;
    time_t now_t = time(0);
    tm now = *localtime(&now_t);

    if (now.tm_year - geburtsDatum.tm_year > 50)
    {
        return anspruch + 2;
    }
    return anspruch;
}
void urlaub_anlegen(int id)
{
    // GEBURTSTAG
    cout << "Bitte Startdatum eingeben (dd.mm.yyyy):" << endl;
    string startEingabe;
    string endEingabe;
    tm startDatum = {};
    tm endDatum = {};

    cin >> startEingabe;
    stringstream startStr(startEingabe);
    startStr >> get_time(&startDatum, "%d.%m.%Y");

    cout << "Bitte Enddatum eingeben (dd.mm.yyyy):" << endl;
    cin >> endEingabe;
    stringstream endStr(endEingabe);
    endStr >> get_time(&endDatum, "%d.%m.%Y");

    double secs = difftime(mktime(&endDatum), mktime(&startDatum));
    double days = secs / 60 / 60 / 24;

    if (m[id].resturlaub - days >= 0)
    {
        m[id].resturlaub -= days;
        cout << days << " Tage eingereicht" << endl;
    }
    else
    {
        cout << "Nicht genug Resturlaub" << endl;
    }
    mitarbeiterview();
}

void startmenue()
{
    // AUSWAHL STARTMENUE
    char eingabe;
    while (1)
    {
        eingabe = getchar();
        fflush(stdin);
        switch (eingabe)
        {
        case '1':
            mitarbeiter_anlegen();
            break;
        case '2':
            mitarbeiter_ausgeben();
            break;
        case '3':
            mitarbeiter_suchen();
            break;
        case '9':
            exit(EXIT_FAILURE);
            return;
        default:
            break;
        }
    }
}

void mitarbeiter_anlegen()
{

    if (perszaehler > MAXIMUM_MITARBEITER)
    {
        cout << "Keine freien Plätze im System" << endl;
        startview();
        return;
    }

    personalnummer++;

    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "--------------------------------<< ESA 1 cpp >>---------------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    // NAME
    cout << "Bitte Namen eingeben:" << endl;
    cin >> m[personalnummer].name;
    // VORNAME
    cout << "Bitte Voramen eingeben:" << endl;
    cin >> m[personalnummer].vorname;
    // GEBURTSTAG
    cout << "Bitte Geburtstag eingeben (dd.mm.yyyy):" << endl;
    string eingabe;
    tm gebDatum = {};

    cin >> eingabe;
    stringstream gebStream(eingabe);
    gebStream >> get_time(&gebDatum, "%d.%m.%Y");

    m[personalnummer].geburtstag = gebDatum;
    // PERSONALNUMMER
    m[personalnummer].personalnummer = personalnummer;

    m[personalnummer].urlaub = urlaubs_Anspruch_Berechnen(gebDatum);
    m[personalnummer].resturlaub = urlaubs_Anspruch_Berechnen(gebDatum);

    perszaehler++;
    // ZURüCK ZUM MENü
    startview();
}

void mitarbeiter_ausgeben()
{
    for (int i = 1; i <= personalnummer; ++i)
    {
        if (m[i].personalnummer != 0)
        {
            cout << m[i];
        }
    }
    startview();
}

void mitarbeiter_suchen()
{
    string str;
    cout << "Bitte Personalnummer fuer Suche eingeben - q fuer Abbruch:" << endl;

    getline(cin, str);
    if (str == "q")
    {
        startview();
        return;
    }
    int idx;
    idx = atoi(str.c_str());
    if (m[idx].personalnummer != 0)
    {
        cout << m[idx];
    }
    else
    {
        cout << "ERROR: Diese Personalnummer existiert nicht!" << endl;
        // ERNEUT ABFRAGEN
        mitarbeiter_suchen();
    }
    mitarbeiterview();
    mitarbeitermenue(idx);
}

void mitarbeiter_loeschen(int id)
{
    string str;
    cout << "Soll dieser Mitarbeiter wirklich gelöscht werden?" << endl;
    cout << m[id];
    cout << "Mit y bestätigen:" << endl;
    getline(cin, str);
    if (str == "y")
    {
        for (int i = id + 1; i < personalnummer; ++id)
        {
            m[i - 1] = m[i];
            i++;
        }
        personalnummer -= 1;
        cout << "Mitarbeiter gelöscht!" << endl;
        perszaehler--;
        startview();
        startmenue();
    }
    else
    {
        cout << "Aktion wurde abgebrochen." << endl;
        cout << m[id];
        mitarbeiterview();
        mitarbeitermenue(id);
    }
}

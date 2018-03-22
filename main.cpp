#include <iostream>
#include <fstream>

using namespace std;

struct tranzitie
{
    int stareaDinCarePleaca;
    char caracter;
    int stareaInCareAjunge;
};

/**
 *
 * @param cuvant reprezinta cuvantul pe care il vom verifica
 * @param stare reprezinta starea curenta in care se afla functia in apelul respectiv
 * @param numarDeTranzitii reprezinta numarul de tranzitii ale automatului
 * @param tranzitii reprezinta vectorul care contine toate tranzitiile automatului
 * @param numarStariObtinute reprezinta numarul de elemente ale vectorului de stari obtinute
 * @param stariObtinute reprezinta un vector in care vom depunde toate starile in care au luat sfarsit fiecare parcurgere
 */
void AFN(char cuvant[101], int stare, int numarDeTranzitii, tranzitie tranzitii[100], int &numarStariObtinute,
         int stariObtinute[100])
{
    int i;

    if (cuvant[0] == '\0')
    {
        stariObtinute[numarStariObtinute] = stare;
        numarStariObtinute++;
    } else
        for (i = 0; i < numarDeTranzitii; i++)
            if ((stare == tranzitii[i].stareaDinCarePleaca) && (cuvant[0] == tranzitii[i].caracter))
                AFN(cuvant + 1, tranzitii[i].stareaInCareAjunge, numarDeTranzitii, tranzitii, numarStariObtinute,
                    stariObtinute);
}

/**
 *
 * @param stare reprezinta starea pe care o vom verifica
 * @param stariFinale reprezinta vectorul de stari finale
 * @param numarStariFinale reprezinta numarul de elemente al vectorului de stari finale
 * @return functia va returna 1 daca "stare" este stare finala, altfel va returna 0
 */
int esteStareFinala(int stare, int stariFinale[100], int numarStariFinale)
{
    int i;

    for (i = 0; i < numarStariFinale; i++)
        if (stare == stariFinale[i])
            return 1;
    return 0;
}

int main()
{
    ifstream fisier("..\\Automat.txt");

    tranzitie tranzitii[100];
    int numarDeTranzitii;

    int stareInitiala;
    int numarStariFinale, stariFinale[100];
    int numarStariObtinute, stariObtinute[100];

    char cuvant[101];

    bool flag;
    int i;


    fisier >> stareInitiala;

    fisier >> numarStariFinale;
    for (i = 0; i < numarStariFinale; i++)
        fisier >> stariFinale[i];

    fisier >> numarDeTranzitii;
    for (i = 0; i < numarDeTranzitii; i++)
    {
        fisier >> tranzitii[i].stareaDinCarePleaca;
        fisier >> tranzitii[i].caracter;
        fisier >> tranzitii[i].stareaInCareAjunge;
    }

    fisier.close();

    cout << "Introduceti cuvantul:\n";
    cin.get(cuvant, 100);


    numarStariObtinute = 0;

    AFN(cuvant, stareInitiala, numarDeTranzitii, tranzitii, numarStariObtinute, stariObtinute);

    flag = 0;
    for (i = 0; (i < numarStariObtinute) && (flag == 0); i++)
        if (esteStareFinala(stariObtinute[i], stariFinale, numarStariFinale))
            flag = 1;

    if (flag == 1)
        cout << "\nCUVANT ACCEPTAT\n";
    else cout << "\nCUVANT NEACCEPTAT\n";

    return 0;
}

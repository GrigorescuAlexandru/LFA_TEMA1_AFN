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
 * @param cuvant
 * @param stare
 * @param numarDeTranzitii
 * @param tranzitii
 * @param numarStariObtinute
 * @param stariObtinute
 */
void AFN(char cuvant[101], int stare, int numarDeTranzitii, tranzitie tranzitii[100], int &numarStariObtinute,
         int stariObtinute[100])
{
    /**
       Intai vom verifica daca cuvantul mai are caractere (cuvantul nu mai are caractere in momentul in care primul element este NULL)
       Daca acesta nu mai are caractere, vom adauga starea obtinuta in vectorul de stari obtinute si vom creste numarStariObtinute cu 1

       Altfel, daca cuvantul mai are caractere, vom lua pe rand fiecare tranzitie a automatului si le vom selecta
       doar pe cele care pleaca din aceeasi stare care se afla in functie (daca stare == tranzitii[i].stareaDinCarePleaca)
       si care au tranzitia cu acelasi caracter (daca cuvant[0] == tranzitii[i].caracter)
       Pentru aceste tranzitii selectate, vom apela recursiv functia AFN pentru urmatorul caracter al cuvantului
       Vom trimite sirul de caractere cuvant+1 care semnifica string-ul respectiv fara primul caracter, deci in urmatoarea
       functie apelata, primul caracter va fi cel de-al doilea din functia actuala
    */

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
 * @param stare
 * @param stariFinale
 * @param numarStariFinale
 * @return
 */
int esteStareFinala(int stare, int stariFinale[100], int numarStariFinale)
{
    /**
       Vom lua starea respectiva (variabila "stare") si o vom compara cu fiecare element al vectorului de stari finale
       Daca gasim un element egal cu variabila stare atunci variabila stare este stare finala
    */

    int i;

    for (i = 0; i < numarStariFinale; i++)
        if (stare == stariFinale[i])
            return 1;
    return 0;
}

int main()
{
    /**
       Vom citi automatul dintr-un fisier
       Formatul fisierului:
       |-----------------------------------------------------------------|
       | Starea initiala                                                 |
       |                                                                 |
       | Nr de stari finale                                              |
       | StareFinala StareFinala StareFinala ...                         |
       |                                                                 |
       | Nr de tranzitii                                                 |
       | Stare1 Caracter Stare2  (Caracter ne duce din Stare1 in Stare2) |
       | Stare1 Caracter Stare2                                          |
       | Stare1 Caracter Stare2                                          |
       |  ...    ...     ...                                             |
       |-----------------------------------------------------------------|
    */

    ifstream fisier("..\\Automat.txt");

    // Vom retine fiecare tranzitie intr-un vector cu elemente de tip "tranzitie" (structura definita anterior)
    tranzitie tranzitii[100];
    int numarDeTranzitii;

    // Vom retine starea initiala intr-o singura variabila (deoarece in acest caz putem avea doar o singura stare initiala)
    // Starile finale le vom retine intr-un vector intrucat acestea pot fi mai multe decat una
    int stareInitiala;
    int numarStariFinale, stariFinale[100];

    // In urma verificarii daca cuvantul apartine acestui AFN, vom obtine mai multe stari pe care le vom retine intr-un vector
    int numarStariObtinute, stariObtinute[100];

    // Variabila care va fi egala cu 1 in cazul in care cel putin una dintre starile obtinute este stare finala, altfel va fi 0
    bool flag;

    // Cuvantul pe care trebuie sa il verificam
    char cuvant[101];

    int i;


    //-----------------------------------------------Citirea automatului din fisier si a cuvantului-------------------------------------------------

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

    //-----------------------------------------------------------Verificarea cuvantului--------------------------------------------------------------

    /**
       Initializam numarul de stari obtinute cu 0 si apelam functia recursiva AFN
       Acesta va creste cu 1 de fiecare data cand cuvantul ramane fara caractere pentru fiecare ramificare a parcurgerii
       In momentul in care intr-o stare incercam tranzitia cu un caracter care nu ne duce nicaieri din starea respectiva
       atunci ramificarea respectiva va lua sfarsit, deci cuvantul nu va ramane fara caractere pentru acea ramificare, deci
       nu se va adauga nimic in vectorul de stari obtinute pentru acea ramificare
    */

    numarStariObtinute = 0;
    AFN(cuvant, stareInitiala, numarDeTranzitii, tranzitii, numarStariObtinute, stariObtinute);

    //-------------------------------------------------Verificam rezultate obtinute de functia AFN----------------------------------------------------

    /**
     Initial, flag va fi 0, deci vom considera cuvantul ca fiind neacceptat
     Vom parcurge vectorul de stari obtinute si vom verifica daca cel putin una din starile acestui vector este stare finala
     folosind functia "esteStareFinala"
     Daca gasim cel putin o stare care este finala, flag va lua valoarea 1, ciclul se va opri (nu mai are rost sa cautam deoarece
     trebuie sa fie cel putin o stare care sa fie finala) si vom spune ca acest cuvant este acceptat, iar in caz contrar, neacceptat
    */

    flag = 0;
    for (i = 0; (i < numarStariObtinute) && (flag == 0); i++)
        if (esteStareFinala(stariObtinute[i], stariFinale, numarStariFinale))
            flag = 1; // in codeblocks nu imi dadea niciun warning pana acum:))

    if (flag == 1)
        cout << "\nCUVANT ACCEPTAT\n";
    else cout << "\nCUVANT NEACCEPTAT\n";

    return 0;
}

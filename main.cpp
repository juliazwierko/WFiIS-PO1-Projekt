//Projekt 1.
//1. Zaimplementuj klasy n-wymiarowego wektora double i n*n wymiarowej macierzy double. Wewnętrznie nie można korzystać
//z kontenerów !
//2. Dla każdej z klas przeładuj operator+ (dodawania) i operator<< wstawiania do strumienia
//(wypisywanie powinno się odbywać wierszami, tzn. że wektor jest kolumną a nie wierszem).
//3. Próby dodawania wektorów lub macierzy o niezgodnych wymiarach powinny się kończyć wyjątkiem
//(w razie potrzeby doczytaj ten fragment w dokumentacji, bez obaw to tylko jedna klasa bez ciała).
//4. Wśród możliwych konstruktorów zadbaj o konstruktor przyjmujący jako parametr obiekt klasy std::initializer_list<double>
//5. Zaimplementuj operatory indeksujące [] i [][] przy czym dla macierzy pierwszy operator[] 
// zwraca obiekt klasy wektor (czyli kolumnę).
//6. Dla macierzy przeładuj operator*() mnożenia macierzy przez macierz (o ile wymiary się zgadzają).
//7. Tablice i wektory mogą być duże, więc pamiętaj o konstruktorach i przypisaniach przenoszących.
#include <iostream>
#include "nwektor.h"
#include <cmath>
int main() {
    //              *KLASA nwektor*
    std::cout << "---Testowanie klasy nwektor---\n";
    nwektor w1=nwektor{{1,2,3,4,5,6,7}};
    nwektor w2=nwektor{{1,2,3,4,5,6,7,8,9,10,11}};
    // nwektor w3=w2+w1;  //powinno skutkować wyjątkiem;
    //użycie konstruktora i przypisania przenoszącego
    nwektor w4=std::move(w1);
    std::cout << "Wartosci wektora:\n" << w4 << "\n\n";
    nwektor w5;
    w5=std::move(w4); 
    //Przetestuj pozostałe operatory. Będą potrzebne !
    

    //              *KLASA nmacierz*
    std::cout << "---Testowanie klasy nmacierz---\n";
    nmacierz m1(3, 3);
    nmacierz m2(3, 3);
    std::cout << "Macierz m1: \n" << m1 << std::endl;
    std::cout << "Macierz m2: \n" << m2 << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m1[i][j] = i + j;
            m2[i][j] = i - j;
        }
    }
    std::cout << "Macierz m1: \n" << m1 << std::endl;
    std::cout << "Macierz m2: \n" << m2 << std::endl;
    
    nmacierz m3(3, 3);
    m3 = (m1 * m2);
    std::cout << "Wynik mnozenia m1*m2:\n"<< m3 << std::endl;

    nmacierz m4(3, 3);
    m4 = m1 + m2;
    std::cout << "Wynik dodawania m1+m2:\n" << m4 << std::endl;

    return 0;
}

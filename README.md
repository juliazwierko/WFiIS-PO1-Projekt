TO DO LIST:

---Julia---
1. Zaimplementuj klasy n-wymiarowego wektora double i n*n wymiarowej macierzy double. Wewnętrznie nie można korzystać
z kontenerów !
2. Dla każdej z klas przeładuj operator+ (dodawania) i operator<< wstawiania do strumienia
(wypisywanie powinno się odbywać wierszami, tzn. że wektor jest kolumną a nie wierszem).
3. Próby dodawania wektorów lub macierzy o niezgodnych wymiarach powinny się kończyć wyjątkiem
(w razie potrzeby doczytaj ten fragment w dokumentacji, bez obaw to tylko jedna klasa bez ciała).

---Mateusz---

4. Wśród możliwych konstruktorów zadbaj o konstruktor przyjmujący jako parametr obiekt klasy std::initializer_list<double>
5. Zaimplementuj operatory indeksujące [] i [][] przy czym dla macierzy pierwszy operator[]
zwraca obiekt klasy wektor (czyli kolumnę).

---Sebastian---

6. Dla macierzy przeładuj operator*() mnożenia macierzy przez macierz (o ile wymiary się zgadzają).
7. Tablice i wektory mogą być duże, więc pamiętaj o konstruktorach i przypisaniach przenoszących.

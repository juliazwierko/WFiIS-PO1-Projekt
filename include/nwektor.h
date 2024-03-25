#pragma once 

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <utility>

class nmacierz;

class nwektor {
public:
    friend class nmacierz;

    // Konstruktor domyślny
    nwektor() : elements(nullptr), size(0) {}

    // Konstruktor przyjmujący obiekt std::initializer_list<double>
    nwektor(std::initializer_list<double> values) : elements(new double[values.size()]), size(values.size()) {
        size_t i = 0;
        for (auto& value : values) {
            elements[i++] = value;
        }
    }
    
    // Destruktor
    ~nwektor() {
        delete[] elements;
    }

    // Konstruktor przenoszący
    nwektor(nwektor&& other) noexcept : elements(nullptr), size(0) {
        *this = std::move(other);
    }
    
    // Operator przypisania przenoszącego 
    nwektor& operator=(nwektor&& other) noexcept {
        if (this != &other) {
            delete[] elements;
            elements = other.elements;
            size = other.size;
            other.elements = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Operator dodawania
    nwektor operator+(const nwektor& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Wektor ma inny rozmiar");
        }
        nwektor result(size);

        for (unsigned i = 0; i < size; i++) {
            result.elements[i] = elements[i] + other.elements[i];
        }
        return result;
    }

    // Operator przypisania
    nwektor& operator=(const nwektor& other) {
        if (this != &other) {
            delete[] elements;
            size = other.size;
            elements = new double[size];
            for (size_t i = 0; i < size; ++i) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    //Operator [] do odczytu
    const double& operator[](const unsigned int index) const 
    {
        if(index >= size)
        {
            throw std::invalid_argument("Indeks poza wektorem");
        }
        return elements[index];
    }

    //Operator [] do dostępu do elementu
    double& operator[](const unsigned int index) 
    {
        if(index >= size)
        {
            throw std::invalid_argument("Indeks poza wektorem");
        }
        return elements[index];
    }
    
    // Operator wypisywania 
    friend std::ostream& operator<<(std::ostream& os, const nwektor& vec) {
        os << "( ";
        // os << "---Wypisanie wektora:---\n(";
        for (size_t i = 0; i < vec.size; ++i) {
            os << vec.elements[i] << " ";
        }
        os << ")";
        return os;
    }

private:
    double* elements;
    size_t size;

    // Prywatny konstruktor do tworzenia wektorów o określonym rozmiarze
    nwektor(size_t size) : elements(new double[size]), size(size) {}
};


class nmacierz
{
public:
    // Konstruktor domyślny
    nmacierz() : rows(0), cols(0), elements(nullptr) {}

    // Konstruktor przyjmujący liczbę wierszy i kolumn
    nmacierz(int rows, int cols) : rows(rows), cols(cols), elements(new nwektor[rows]) {
        for (int i = 0; i < rows; ++i) {
            elements[i] = nwektor(cols);
        }
    }

    // Konstruktor przenoszący
    nmacierz(nmacierz&& other) noexcept : rows(other.rows), cols(other.cols), elements(other.elements) {
        other.rows = 0;
        other.cols = 0;
        other.elements = nullptr;
    }

    // Operator przypisania przenoszącego
    nmacierz& operator=(nmacierz&& other) noexcept {
        if (this != &other) {
            deallocateMemory();
            rows = other.rows;
            cols = other.cols;
            elements = other.elements;
            other.rows = 0;
            other.cols = 0;
            other.elements = nullptr;
        }
        return *this;
    }

    // Destruktor
    ~nmacierz() {
        deallocateMemory();
    }

    //Operator [] do dostępu do wiersza
    nwektor& operator[](const int row) {
        if (row >= rows) {
            throw std::invalid_argument("Indeks poza macierzą");
        }
        return elements[row];
    }

    //Operator [] do odczytu wiersza
    const nwektor& operator[](const int row) const {
        if (row >= rows) {
            throw std::invalid_argument("Indeks poza macierzą");
        }
        return elements[row];
    }

    // Operator mnożenia macierzy
    nmacierz operator*(const nmacierz& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Nieprawidłowe wymiary macierzy do mnożenia");
        }
        nmacierz result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result[i][j] += elements[i][k] * other[k][j];
                }
            }
        }
        return result;
    }

    // Operator wypisywania
    friend std::ostream& operator<<(std::ostream& os, const nmacierz& matrix) {
        // os << "---Wypisanie macierzy:---\n";
        for (int i = 0; i < matrix.rows; ++i) {
            os << matrix.elements[i] << std::endl;
        }
        return os;
    }

    // Operator dodawania
    nmacierz operator+(const nmacierz& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Nieprawidłowe wymiary macierzy do dodawania");
        }
        nmacierz result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result[i][j] = elements[i][j] + other[i][j];
            }
        }
        return result;
    }

private:
    int rows;
    int cols;
    nwektor* elements;

    // Funkcja do dealokacji pamięci
    void deallocateMemory() {
        if (elements != nullptr) {
            delete[] elements;
            elements = nullptr;
        }
    }
};

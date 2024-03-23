#pragma once 

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <utility>

class nwektor {
private:
    double* elements;
    size_t size;

public:
    // Zadanie 1: Konstruktor przyjmujący obiekt std::initializer_list<double>
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

    // Operator dodawania (Zadanie 2)
    nwektor operator+(const nwektor& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors have different sizes");
        }
        nwektor result{};

        for (size_t i = 0; i < size; ++i) {
            result.elements[i] = elements[i] + other.elements[i];
        }

        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const nwektor& vec) {
        for (size_t i = 0; i < vec.size; ++i) {
            os << vec.elements[i] << "\n";
        }
        return os;
    }
};

// Zadanie 6: Klasa reprezentująca macierz n*n wymiarową
class nmacierz {
private:
    nwektor* rows;
    size_t size;

public:
    
    // Destruktor
    ~nmacierz() {
        delete[] rows;
    }

    // Operator dodawania (Zadanie 2)
    nmacierz operator+(const nmacierz& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Matrices have different sizes");
        }

        nmacierz result{};

        for (size_t i = 0; i < size; ++i) {
            result.rows[i] = rows[i] + other.rows[i];
        }

        return result;
    }
 

};

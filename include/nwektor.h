#pragma once 

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <utility>

class nwektor {
public:
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
        nwektor result{};

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

    // Operator wypisywania 
    friend std::ostream& operator<<(std::ostream& os, const nwektor& vec) {
        os << "---Wypisanie wektora:---\n(";
        for (size_t i = 0; i < vec.size; ++i) {
            os << vec.elements[i] << " ";
        }
        os << ")";
        return os;
    }

private:
    double* elements;
    size_t size;
};


// TU ma byc klasa dla macierzy:
// class ......

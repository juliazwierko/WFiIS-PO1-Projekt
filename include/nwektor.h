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
class nmacierz
{
public:
    nmacierz() : rows(0), cols(0), elements(nullptr) {}
    nmacierz(int rows, int cols) : rows(rows), cols(cols), elements(nullptr)
    {
        allocateMemory();
    }
    nmacierz(const nmacierz &other) : rows(other.rows), cols(other.cols), elements(nullptr)
    {
        copyFrom(other);
    }
    nmacierz(nmacierz &&other) noexcept : rows(other.rows), cols(other.cols), elements(other.elements)
    {
        other.rows = 0;
        other.cols = 0;
        other.elements = nullptr;
    }
    nmacierz &operator=(const nmacierz &other)
    {
        if (this != &other)
        {
            deallocateMemory();
            rows = other.rows;
            cols = other.cols;
            copyFrom(other);
        }
        return *this;
    }
    nmacierz &operator=(nmacierz &&other) noexcept
    {
        if (this != &other)
        {
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
    ~nmacierz()
    {
        deallocateMemory();
    }

    //Operator [] do dostepu
    double *operator[](const int row)
    {
        if(row >= rows)
        {
            throw std::invalid_argument("Indeks poza macierza");
        }
        return elements[row];
    }

    //Operator [] do odczytu
    const double *operator[](const int row) const
    {
        if(row >= rows)
        {
            throw std::invalid_argument("Indeks poza macierza");
        }
        return elements[row];
    }

    nmacierz operator*(nmacierz &other)
    {
        if (this->cols != other.rows)
        {
            throw std::invalid_argument("Liczba kolumn i wierszy nie zgadza się, nie da się pomnożyć");
        }
        else
        {
            nmacierz result(rows, other.cols);
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < other.cols; j++)
                {
                    result.elements[i][j] = 0;
                    for (int k = 0; k < other.rows; k++)
                    {
                        result.elements[i][j] += elements[i][k] * other.elements[k][j];
                    }
                }
            }
            return result;
        }
    }

    friend std::ostream &operator<<(std::ostream &out, const nmacierz &matrix);

private:
    int rows;
    int cols;
    double **elements;

    void allocateMemory()
    {
        elements = new double *[rows];
        for (int i = 0; i < rows; i++)
        {
            elements[i] = new double[cols];
        }
    }

    void copyFrom(const nmacierz &other)
    {
        allocateMemory();
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                elements[i][j] = other.elements[i][j];
            }
        }
    }

    void deallocateMemory()
    {
        if (elements != nullptr)
        {
            for (int i = 0; i < rows; i++)
            {
                delete[] elements[i];
            }
            delete[] elements;
            elements = nullptr;
        }
    }
};

std::ostream &operator<<(std::ostream &out, const nmacierz &matrix)
{
    out << "---Wypisanie macierzy:---\n";
    for (int i = 0; i < matrix.rows; i++)
    {
        out << "( ";
        for (int j = 0; j < matrix.cols; j++)
        {
            out << matrix.elements[i][j] << " ";
        }
        out << ")" << std::endl;
    }
    return out;
}

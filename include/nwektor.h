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
class nmacierz
{
public:
nmacierz() = default;
nmacierz(int rows, int cols): rows(rows),cols(cols) //dziala
{
    elements=new double*[rows];
    for(int i=0;i<rows;i++)
    {
        elements[i]=new double[cols];
    }
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            elements[i][j]=0;
        }
    }
}
nmacierz(const nmacierz &other) // Konstruktor kopiujacy //dziala
{
    cols=other.cols;
    rows=other.rows;
    elements=new double*[rows];
    for(int i=0;i<rows;i++)
    {
        elements[i]=new double[cols];
    }
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            elements[i][j]=other.elements[i][j];
        }
    }
}
nmacierz(nmacierz &&other) //Konstruktor przenoszący //dziala
{
    cols=other.cols;
    rows=other.rows;
    elements=new double*[rows];
    for(int i=0;i<rows;i++)
    {
        elements[i]=new double[cols];
    }
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            elements[i][j]=other.elements[i][j];
        }
    }
    delete [] other.elements;
    other.rows=0;
    other.cols=0; 
}
nmacierz & operator=(const nmacierz &other) // Przeladowanie operatora kopiujacego //dziala
{
    if(this!=&other)
    {
        delete [] elements;
        rows=other.rows;
        cols=other.cols;
        elements=new double*[rows];
        for(int i=0;i<rows;i++)
        {
            elements[i]=new double[cols];
        }
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                elements[i][j]=other.elements[i][j];
            }
        }

    }
    return *this;
}
nmacierz & operator=(nmacierz &&other ) //Przeladowanie, operator przenoszacy //dziala
{
    if(this!=&other)
    {
        delete [] elements;
        rows=other.rows;
        cols=other.cols;
        elements=new double*[rows];
        for(int i=0;i<rows;i++)
        {
            elements[i]=new double[cols];
        }
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                elements[i][j]=other.elements[i][j];
            }
        }
        delete [] other.elements;
        other.rows=0;
        other.cols=0;

    }
    return *this;
}
~nmacierz() //Destruktor
{
    delete [] elements;
}
double *operator[](unsigned int row)
{
    return elements[row];
}
nmacierz operator*(nmacierz &other) //Przeladowanie, operator mnozenia //NIE DZIALA
{
    
    if(this->cols!=other.rows)
    {
        throw std::invalid_argument("Liczba kolumn i wierszy nie zgadza sie, nie da sie pomnozyc");
    }
    else
    {
        
        nmacierz wynik(rows, other.cols);
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<other.cols;j++)
            {
                wynik.elements[i][j] = 0;
                for(int k=0; k<other.rows; k++)
                {
                    wynik.elements[i][j]+=elements[i][k]*other.elements[k][j];
                    
                    
                }
            }
        }
        
        return wynik;
    }
}
friend std::ostream & operator<<(std::ostream&out, const nmacierz &other);
private:
int rows;
int cols;
double **elements;
};

std::ostream & operator<<(std::ostream &out, const nmacierz &other) // Przeladowanie, operator do wypisywania
{
    out<<"---Wypisanie macierzy:---\n";
    for(int i=0;i<other.rows;i++)
    {
        out<<"(";
        for(int j=0;j<other.cols;j++)
        {
            out<<other.elements[i][j]<<" ";
        }
        out<<")"<<std::endl;
    }

    return out;
}
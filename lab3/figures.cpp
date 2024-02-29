#include "figures.hpp"

Figures::Figures() : size(0), figures{nullptr} {}

size_t Figures::getSize() const { return size; }

Figures::Figures(const size_t &n, unsigned char t) { 
    figures = new Figure*[n];
    for (size_t i = 0; i < n; ++i)
        figures[i] = nullptr;
    size = n;
}

Figures::Figures(const std::initializer_list<unsigned char> &t, size_t flag) {
    size = t.size();
    figures = new Figure*[size];
    size_t i = 0;
    for (const unsigned char &c : t) {
        if (flag == 1) {
            figures[i] = new Trapezoid();
        } else if (flag == 2) {
            figures[i] = new Rhombus();
        } else if (flag == 3) {
            figures[i] = new Pentagon();
        }
        ++i;
    }
}

void Figures::addFigure(Figure *figure) {
    Figure** newFigures = new Figure*[size + 1];
    for (size_t i = 0; i < size; ++i) 
        newFigures[i] = figures[i];
    newFigures[size] = figure;
    delete[] figures;
    figures = newFigures;
    ++size;
}

void Figures::deleteFigure(size_t ind) { 
    if (ind < size) {
        delete figures[ind];
        for (size_t i = ind; i < size - 1; ++i)
            figures[i] = figures[i+1];
        --size;
    } else {
        throw std::logic_error("Array out of bounds");
    }
}

double Figures::totalArea() const{
    double result = 0.0;
    for (size_t i = 0; i < size; ++i)
        result += figures[i]->square();
    return result;
}

Figure* Figures::getFigure(size_t ind) {
    if (ind < size) {
        return figures[ind];
    }
    return nullptr;
}

Figures::~Figures() noexcept {
    for (size_t i = 0; i < size; ++i) {
        if (figures[i]) {
            delete figures[i];
            figures[i] = nullptr;
        }
    }
    size = 0;
    delete[] figures;
    figures = nullptr;
}
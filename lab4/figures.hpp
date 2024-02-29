#pragma once

#include <memory>

#include <figure.hpp>
#include <pentagon.hpp>
#include <rhombus.hpp>
#include <trapezoid.hpp>


template <class T>
class Figures {
    public:

        Figures() : size(0), figures(nullptr) {}

        Figures(const size_t &n, unsigned char t) { 
            figures = std::make_unique<std::unique_ptr<Figure<T> >[]>(n);
            for (size_t i = 0; i < n; ++i)
                figures[i] = nullptr;
            size = n;
        }

        Figures(const std::initializer_list<unsigned char> &t, size_t flag) {
            size = t.size();
            figures = std::make_unique<std::unique_ptr<Figure<T> >[] >(size);
            size_t i = 0;
            for (const unsigned char &c : t) {
                if (flag == 1) {
                    figures[i] = std::make_unique<Trapezoid<T>>();
                } else if (flag == 2) {
                    figures[i] = std::make_unique<Rhombus<T>>();
                } else if (flag == 3) {
                    figures[i] = std::make_unique<Pentagon<T>>();
                }
                ++i;
            }
        }

        size_t getSize() const {
            return size;
        }

        void addFigure(std::unique_ptr<Figure<T>> figure) {
            auto newFigures = std::make_unique<std::unique_ptr<Figure<T>>[]>(size + 1);
            for (size_t i = 0; i < size; ++i) 
                newFigures[i] = std::move(figures[i]);
            newFigures[size] = std::move(figure);
            figures = std::move(newFigures);
            ++size;
        }

        void deleteFigure(size_t ind) { 
            if (ind < size) {
                figures[ind].reset();
                for (size_t i = ind; i < size - 1; ++i)
                    figures[i] = std::move(figures[i+1]);
                --size;
            } else {
            throw std::logic_error("Array out of bounds");
            }
        }

        double totalArea() const{
            double result = 0;
            for (size_t i = 0; i < size; ++i)
                result += figures[i]->square();
            return result;
        }

        std::unique_ptr<Figure<T> > getFigure(size_t ind) {
            if (ind < size) {
                return std::move(figures[ind]);
            }
            return nullptr;
        }
    private:
        size_t size;
        std::unique_ptr<std::unique_ptr<Figure<T> >[] > figures;
};
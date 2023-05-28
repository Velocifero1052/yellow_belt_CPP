//
// Created by comme on 5/28/2023.
//

#ifndef YELLOW_BELT_CPP_FIGURES_H
#define YELLOW_BELT_CPP_FIGURES_H
#include <string>
#include <cmath>
#include <memory>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>

class Figure {
public:
    virtual std::string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Rect: public Figure {
public:
    Rect(const std::string name_, double a_, double b_): name(name_), a(a_), b(b_) {
    }
    std::string Name() const override{ return name; }
    double Perimeter() const override{ return 2 * (a + b); }
    double Area() const override { return a * b; }
private:
    const std::string name;
    const double a, b;
};

class Triangle: public Figure {
public:
    Triangle(const std::string name_, double a_, double b_, double c_): name(name_), a(a_), b(b_), c(c_) {

    }
    std::string Name() const override{ return name; }
    double Perimeter() const override{ return a + b + c; }
    double Area() const override {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
private:
    const std::string name;
    const double a, b, c;
};

class Circle: public Figure {
public:
    Circle(const std::string name_, double r_): name(name_), r(r_) {

    }
    std::string Name() const override{ return name; }
    double Perimeter() const override{ return 2.0 * 3.14 * r; }
    double Area() const override {
        return 3.14 * r * r;
    }
private:
    const std::string name;
    const double r;
};

std::shared_ptr<Figure> CreateFigure(std::istringstream & ss){
    std::string name;
    ss >> name;
    if (name == "RECT"){
        double a, b;
        ss >> a >> b;
        return std::make_shared<Rect>(Rect(name, a, b));
    } else if (name == "TRIANGLE"){
        double a, b, c;
        ss >> a >> b >> c;
        return std::make_shared<Triangle>(Triangle(name, a, b, c));
    } else if (name == "CIRCLE") {
        double r;
        ss >> r;
        return std::make_shared<Circle>(Circle(name, r));
    } else return nullptr;
}

void test() {
    std::vector<std::shared_ptr<Figure>> figures;
    for (std::string line; getline(std::cin, line); ) {
        std::istringstream is(line);

        std::string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                std::cout << std::fixed << std::setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << std::endl;
            }
        }
    }
}

#endif //YELLOW_BELT_CPP_FIGURES_H

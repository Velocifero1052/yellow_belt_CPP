#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

class Figure {
public:
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Rect: public Figure {
public:
    Rect(const string name_, double a_, double b_): name(name_), a(a_), b(b_) {
    }
    string Name() const override{ return name; }
    double Perimeter() const override{ return 2 * (a + b); }
    double Area() const override { return a * b; }
private:
    const string name;
    const double a, b;
};

class Triangle: public Figure {
public:
    Triangle(const string name_, double a_, double b_, double c_): name(name_), a(a_), b(b_), c(c_) {

    }
    string Name() const override{ return name; }
    double Perimeter() const override{ return a + b + c; }
    double Area() const override {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
private:
    const string name;
    const double a, b, c;
};

class Circle: public Figure {
public:
    Circle(const string name_, double r_): name(name_), r(r_) {

    }
    string Name() const override{ return name; }
    double Perimeter() const override{ return 2.0 * 3.14 * r; }
    double Area() const override {
        return 3.14 * r * r;
    }
private:
    const string name;
    const double r;
};

shared_ptr<Figure> CreateFigure(istringstream & ss){
    string name;
    ss >> name;
    if (name == "RECT"){
        double a, b;
        ss >> a >> b;
        return make_shared<Rect>(Rect(name, a, b));
    } else if (name == "TRIANGLE"){
        double a, b, c;
        ss >> a >> b >> c;
        return make_shared<Triangle>(Triangle(name, a, b, c));
    } else if (name == "CIRCLE") {
        double r;
        ss >> r;
        return make_shared<Circle>(Circle(name, r));
    } else return nullptr;
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}
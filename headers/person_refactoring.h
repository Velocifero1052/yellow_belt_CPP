//
// Created by comme on 5/29/2023.
//

#ifndef YELLOW_BELT_CPP_PERSON_REFACTORING_H
#define YELLOW_BELT_CPP_PERSON_REFACTORING_H
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::vector;

class Person {
public:
    Person(const string& name, const string& profession): Name(name), Profession(profession) {}
    void Walk(const string& destination) const {
        cout << Profession << ": " << Name << " walks to: " << destination << endl;
    }
    string GetName() const {
        return Name;
    }
    string GetProfession() const {
        return Profession;
    }
private:
    const string Name;
    const string Profession;
};


class Student: public Person {
public:
    Student(const string& name, const string& favouriteSong): Person(name, "Student"), FavouriteSong(favouriteSong) {
    }

    void Learn() {
        cout << GetProfession() << ": " << GetName() << " learns" << endl;
    }

    void Walk(string destination) {
        cout << GetProfession() << ": " << GetName() << " walks to: " << destination << endl;
        cout << GetProfession() << ": " << GetName() << " sings a song: " << FavouriteSong << endl;
    }

    void SingSong() {
        cout << GetProfession() << ": " << GetName() << " sings a song: " << FavouriteSong << endl;
    }
private:
    const string FavouriteSong;
};


class Teacher: public Person {
public:
    Teacher(const string& name, const string& subject): Person(name, "Teacher"), Subject(subject) {
    }
    void Teach() {
        cout << GetProfession() << ": " << GetName() << " teaches: " << Subject << endl;
    }
private:
    const string Subject;
};


class Policeman: Person {
public:
    Policeman(const string& name): Person(name, "Policeman") {
    }
    void Check(Person p) const {
        cout << GetProfession() << ": " << GetName() << " checks " << p.GetProfession() << ". " << p.GetProfession() << "'s name is " << p.GetName() << endl;
    }
};


void VisitPlaces(Person person, vector<string> places) {
    for (auto p : places) {
        person.Walk(p);
    }
}

void tests(){
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
}


#endif //YELLOW_BELT_CPP_PERSON_REFACTORING_H

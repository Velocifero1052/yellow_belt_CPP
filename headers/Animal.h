//
// Created by comme on 5/27/2023.
//

#ifndef YELLOW_BELT_CPP_ANIMAL_H
#define YELLOW_BELT_CPP_ANIMAL_H
#include <string>
#include <iostream>

class Animal {
public:
    // ваш код
    Animal(std::string name): Name(name){
    }
    const std::string Name;
};


class Dog: public Animal {
public:
    // ваш код
    Dog(std::string name): Animal(name) {

    }
    void Bark() {
        std::cout << Name << " barks: woof!" << std::endl;
    }
};

#endif //YELLOW_BELT_CPP_ANIMAL_H

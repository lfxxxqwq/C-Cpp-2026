#include <bits/stdc++.h>
using namespace std;
class Animal {
public:
    virtual void speak() const = 0;
    virtual ~Animal() {}
};
class Dog : public Animal {
public:
    void speak() const override {
        system("Dog.wav");
    }
};
class Cat : public Animal {
public:
    void speak() const override {
        system("Cat.wav");
    }
};
class Zoo {
private:
    vector<unique_ptr<Animal>> animals;
public:
    void add(unique_ptr<Animal> animal) {
        if (animal == nullptr) return;
        animals.push_back(move(animal));
    }
    void speak() const {
        for (auto &animal : animals) {
            animal -> speak();
        }
    }
};
class Bird : public Animal {
public:
    void speak() const override {
        system("Bird.wav");
    }
};
class Wolfdog : public Dog {
public:
    void speak() const override {
        system("Wolfdog.wav");
    }
};
int main() {
    Zoo zoo;
    zoo.add(make_unique<Dog>());
    zoo.add(make_unique<Cat>());
    zoo.speak();
    zoo.add(make_unique<Bird>());
    zoo.add(make_unique<Wolfdog>());
    zoo.speak();
    return 0;
}

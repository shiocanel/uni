#include "Film.h"
#include <iostream>
#include <utility>

Film::Film(std::string titlu, std::string gen, int anAparitie, std::string actorPrincipal)
    : titlu(std::move(titlu)),
    gen(std::move(gen)),
    anAparitie(anAparitie),
    actorPrincipal(std::move(actorPrincipal)) {
}

const std::string& Film::getTitlu() const noexcept {
    return titlu;
}

const std::string& Film::getGen() const noexcept {
    return gen;
}

int Film::getAnAparitie() const noexcept {
    return anAparitie;
}

const std::string& Film::getActorPrincipal() const noexcept {
    return actorPrincipal;
}

void Film::setTitlu(const std::string& value) {
    titlu = value;
}

void Film::setGen(const std::string& value) {
    gen = value;
}

void Film::setAnAparitie(int value) {
    anAparitie = value;
}

void Film::setActorPrincipal(const std::string& value) {
    actorPrincipal = value;
}

std::ostream& operator<<(std::ostream& out, const Film& film) {
    out << film.getTitlu()
        << " | " << film.getGen()
        << " | " << film.getAnAparitie()
        << " | " << film.getActorPrincipal();
    return out;
}
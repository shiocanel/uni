#pragma once
#include <string>
#include <iosfwd>

class Film {
private:
    std::string titlu;
    std::string gen;
    int anAparitie{ 0 };
    std::string actorPrincipal;

public:
    Film() = default;
    Film(std::string titlu, std::string gen, int anAparitie, std::string actorPrincipal);

    Film(const Film& other) = default;
    Film(Film&& other) noexcept = default;

    Film& operator=(const Film& other) = default;
    Film& operator=(Film&& other) noexcept = default;

    ~Film() = default;

    const std::string& getTitlu() const noexcept;
    const std::string& getGen() const noexcept;
    int getAnAparitie() const noexcept;
    const std::string& getActorPrincipal() const noexcept;

    void setTitlu(const std::string& value);
    void setGen(const std::string& value);
    void setAnAparitie(int value);
    void setActorPrincipal(const std::string& value);
};

std::ostream& operator<<(std::ostream& out, const Film& film);
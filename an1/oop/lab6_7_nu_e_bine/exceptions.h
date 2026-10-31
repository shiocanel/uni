#pragma once
#include <string>
#include <vector>

class RepoException {
private:
    std::string msg;
public:
    RepoException(const std::string& m) : msg(m) {}
    std::string getMessage() const { 
        return msg; 
    }
};

class ValidationException {
private:
    std::string msg;
public:
    ValidationException(const std::string& m) : msg(m) {}
    std::string getMessage() const { 
        return msg; 
    }
};

class MovieValidator {
public:
    static void validate(const std::string& title, const std::string& genre, int year, const std::string& actor) {
        std::string errors;

        if (title.empty()) 
            errors += "Titlul nu poate fi vid!\n";
        if (genre.empty()) 
            errors += "Genul nu poate fi vid!\n";
        if (year < 0) 
            errors += "Anul aparitiei este invalid!\n";
        if (actor.empty()) 
            errors += "Actorul principal nu poate fi vid!\n";

        if (!errors.empty()) {
            throw ValidationException(errors);
        }
    }
};
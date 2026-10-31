#pragma once
#include "movie.h"
#include "vector_dinamic.h"
#include "exceptions.h"
#include <string>

using std::string;

class Repository {
private:
    VectorDinamic<Movie> movies;

public:
    Repository() = default;

    void store(const Movie& m);
    void remove(const string& title);
    void update(const string& title, const Movie& updatedMovie);
    int find(const string& title) const;

    const VectorDinamic<Movie>& getAll() const;
};
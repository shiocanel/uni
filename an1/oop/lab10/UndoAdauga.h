#pragma once
#include "ActiuneUndo.h"
#include "FilmRepository.h"
#include <string>

class UndoAdauga : public ActiuneUndo {
private:
    FilmRepository& repo;
    std::string titluAdaugat;

public:
    UndoAdauga(FilmRepository& repo, std::string titlu);
    void doUndo() override;
};
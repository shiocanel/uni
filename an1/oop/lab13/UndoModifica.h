#pragma once
#include "ActiuneUndo.h"
#include "FilmRepository.h"
#include <string>

class UndoModifica : public ActiuneUndo {
private:
    FilmRepository& repo;
    std::string titluCurent;
    Film filmVechi;

public:
    UndoModifica(FilmRepository& repo, std::string titluCurent, const Film& filmVechi);
    void doUndo() override;
};
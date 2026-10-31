#pragma once
#include "ActiuneUndo.h"
#include "FilmRepository.h"

class UndoSterge : public ActiuneUndo {
private:
    FilmRepository& repo;
    Film filmSters;

public:
    UndoSterge(FilmRepository& repo, const Film& film);
    void doUndo() override;
};
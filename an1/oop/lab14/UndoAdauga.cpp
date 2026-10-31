#include "UndoAdauga.h"

UndoAdauga::UndoAdauga(FilmRepository& repo, std::string titlu)
    : repo(repo), titluAdaugat(std::move(titlu)) {
}

void UndoAdauga::doUndo() {
    repo.removeFilm(titluAdaugat);
}
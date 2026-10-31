#include "UndoModifica.h"

UndoModifica::UndoModifica(FilmRepository& repo, std::string titluCurent, const Film& filmVechi)
    : repo(repo), titluCurent(std::move(titluCurent)), filmVechi(filmVechi) {
}

void UndoModifica::doUndo() {
    repo.updateFilm(titluCurent, filmVechi);
}
#include "UndoSterge.h"

UndoSterge::UndoSterge(FilmRepository& repo, const Film& film)
    : repo(repo), filmSters(film) {
}

void UndoSterge::doUndo() {
    repo.addFilm(filmSters);
}
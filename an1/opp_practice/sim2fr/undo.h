#pragma once
#include "repository.h"
#include <vector>

class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    virtual void doRedo() = 0;
    virtual ~ActiuneUndo() = default;
};

class UndoAnFabricatie : public ActiuneUndo {
private:
    Repository& repo;
    int delta;
public:
    UndoAnFabricatie(Repository& repo, int delta) : repo{ repo }, delta{ delta } {}
    void doUndo() override {
        repo.modificaAnTuturor(-delta);
    }
    void doRedo() override {
        repo.modificaAnTuturor(delta);
    }
};

class UndoSterge : public ActiuneUndo {
private:
    Repository& repo;
    vector<Masina> sterse;
public:
    UndoSterge(Repository& repo, const vector<Masina>& sterse) : repo{ repo }, sterse{ sterse } {}
    void doUndo() override {
        for (const auto& m : sterse) {
            repo.adauga(m);
        }
    }
    void doRedo() override {
        for (const auto& m : sterse) {
            repo.sterge(m.getNrInmatriculare());
        }
    }
};
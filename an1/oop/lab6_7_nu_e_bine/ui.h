#pragma once
#include "service.h"
#include <vector>

class UI {
private:
    Service& srv;

    void printMenu() const;
    void uiPrint(const std::vector<Movie>& movies) const;

public:
    UI(Service& srv);

    void run();
};
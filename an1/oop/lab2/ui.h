#ifndef UI_H
#define UI_H

#include "service.h"

/*
 * gestioneaza interactiunea cu utilizatorul si ciclul de viata al interfetei.
 * pre: service - pointer valid catre un service, test - flag pentru rulare ui (0) sau mod test (1).
 * post: executa operatiile alese de utilizator pana la inchiderea aplicatiei.
 */
void run(Service* service, int test);

#endif // !UI_H

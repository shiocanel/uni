#include <crtdbg.h>
#include <stdio.h>

#include "service.h"
#include "ui.h"
#include "test.h"

/*
 * Ruleaza toate testele unitare ale aplicatiei.
 * Pre: -
 * Post: Programul continua daca toate testele trec, altfel se opreste.
 */
int main() {
	// proiect de la: Rosca Crina
	runAllTests();
	printf("Tests finished!\n\n");

	Service service = createService();

	addProduct(&service, 1, "Laptop", "XPS13", "Dell", 5500, 3);
	addProduct(&service, 2, "Phone", "iPhone 14", "Apple", 6000, 5);
	addProduct(&service, 3, "Mouse", "G502", "Logitech", 300, 10);
	addProduct(&service, 4, "Keyboard", "K95", "Corsair", 800, 7);
	addProduct(&service, 5, "Monitor", "27GN800", "LG", 1200, 4);
	addProduct(&service, 6, "Headphones", "WH1000XM5", "Sony", 1500, 6);
	addProduct(&service, 7, "Tablet", "Tab S9", "Samsung", 4500, 3);
	addProduct(&service, 8, "GPU", "RTX 4070", "NVIDIA", 3500, 2);
	addProduct(&service, 9, "CPU", "Ryzen 7", "AMD", 2000, 8);
	addProduct(&service, 10, "SSD", "970 EVO", "Samsung", 700, 15);
	addProduct(&service, 11, "RAM", "Vengeance", "Corsair", 400, 20);
	addProduct(&service, 12, "Printer", "LaserJet", "HP", 900, 5);

	run(&service, 0);
	// 0 run ui
	// 1 dont

	destroyService(&service);

	_CrtDumpMemoryLeaks();
	return 0;
}

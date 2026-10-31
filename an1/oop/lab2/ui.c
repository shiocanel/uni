#include "ui.h"

#include <stdio.h>
#include <stdlib.h>

void printVector(Vector* v) {
	for (int i = 0; i < v->size; i++) {
		Product product = v->elements[i];
		printf("%d | %s | %s | %s | %lf | %d\n", product.id, product.name, product.model, product.producer, product.price, product.quantity);
	}
}

/*
 * gestioneaza interactiunea cu utilizatorul si ciclul de viata al interfetei.
 * pre: service - pointer valid catre un service, test - flag pentru rulare ui (0) sau mod test (1).
 * post: executa operatiile alese de utilizator pana la inchiderea aplicatiei.
 */
void run(Service* service, int test) {
	int option;

	while (1) {
		printf("\n=== MENU ===\n");
		printf("1) Add Product\n");
		printf("2) Update Product\n");
		printf("3) Delete Product\n");
		printf("4) View Products\n");
		printf("5) Filter Products\n");
		printf("6) Sort Products\n");
		printf("0) Exit\n");

		printf("Option: ");
		if (test == 0)
			scanf("%d", &option);
		else
			option = 0;

		if (option == 1) {
			int id;
			char name[100], model[100], producer[100];
			double price;
			int quantity;

			printf("ID: ");
			scanf("%d", &id);

			printf("Name: ");
			scanf("%s", name);

			printf("Model: ");
			scanf("%s", model);

			printf("Producer: ");
			scanf("%s", producer);

			printf("Price: ");
			scanf("%lf", &price);

			printf("Quantity: ");
			scanf("%d", &quantity);

			int res = addProduct(service, id, name, model, producer, price, quantity);

			if (res == 1)
				printf("Product added!\n");
			else
				printf("Error adding product!\n");
		}
		else if (option == 2) {
			int id;
			char name[100], model[100], producer[100];
			double price;
			int quantity;

			printf("ID to update: ");
			scanf("%d", &id);

			printf("New name: ");
			scanf("%s", name);

			printf("New model: ");
			scanf("%s", model);

			printf("New producer: ");
			scanf("%s", producer);

			printf("New price: ");
			scanf("%lf", &price);

			printf("New quantity: ");
			scanf("%d", &quantity);

			int res = updateProduct(service, id, name, model, producer, price, quantity);

			if (res == 1)
				printf("Updated!\n");
			else
				printf("Update failed!\n");
		}
		else if (option == 3) {
			int id;
			printf("ID to delete: ");
			scanf("%d", &id);

			int res = deleteProduct(service, id);

			if (res == 1)
				printf("Deleted!\n");
			else
				printf("Delete failed!\n");
		}
		else if (option == 4) {
			printVector(&(service->repo.products));
		}
		else if (option == 5) {
			int sub;
			printf("1) Producer\n");
			printf("2) Price\n");
			printf("3) Quantity\n");
			printf("Option: ");
			scanf("%d", &sub);

			if (sub == 1) {
				char producer[100];
				printf("Producer: ");
				scanf("%s", producer);

				Vector v = filterByProducer(service, producer);
				printVector(&v);
				destroyVector(&v);
			}
			else if (sub == 2) {
				double price;
				printf("Max price: ");
				scanf("%lf", &price);

				Vector v = filterByPrice(service, price);
				printVector(&v);
				destroyVector(&v);
			}
			else if (sub == 3) {
				int q;
				printf("Max quantity: ");
				scanf("%d", &q);

				Vector v = filterByQuantity(service, q);
				printVector(&v);
				destroyVector(&v);
			}
		}
		else if (option == 6) {
			int type, order;

			printf("1) Price\n");
			printf("2) Quantity\n");
			scanf("%d", &type);

			printf("1) Asc\n");
			printf("2) Desc\n");
			scanf("%d", &order);

			Vector v;

			if (type == 1)
				v = sortByPrice(service, order == 1);
			else
				v = sortByQuantity(service, order == 1);

			printVector(&v);
			destroyVector(&v);
		}

		else if (option == 0 || test == 1) {
			printf("Sa fie cu bine!!!\n");
			return;
		}
		else {
			printf("Invalid Command!!!\n");
		}
	}
}

#include "validator.h"
#include <string.h>

int validateProduct(int id, char* name, char* model, char* producer, double price, int quantity) {
	if (id < 0)
		return -1;
	if (name == NULL || strlen(name) == 0)
		return -1;
	if (model == NULL || strlen(model) == 0)
		return -1;
	if (producer == NULL || strlen(producer) == 0)
		return -1;
	if (price <= 0)
		return -1;
	if (quantity < 0)
		return -1;

	return 1;
}
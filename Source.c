//MICLESCU RAZVAN-AUXENIU, GRUPA 1060

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

typedef struct Car Car;
typedef struct Node Node;
typedef struct DoublyLinkedList DLList;

struct Car {
	int year;
	char* manufacturer;
	float cc;
};

struct Node {
	Car car;
	Node* next;
	Node* prev;
};

struct DoublyLinkedList {
	Node* start;
	Node* end;
};

void insertAtBeginning(DLList* list, Car car) {

	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;

	newNode->next = list->start;
	newNode->prev = NULL;

	if (list->start) {
		list->start->prev = newNode;
	}
	else {
		list->end = newNode;
	}

	list->start = newNode;
}

void insertAtEnd(DLList* list, Car car) {

	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;

	newNode->prev = list->end;
	newNode->next = NULL;

	if (list->start) {
		list->end->next = newNode;
	}
	else {
		list->start = newNode;
	}

	list->end = newNode;
}

Car deleteFromBeginning(DLList* list) {

	if (list->start) {

		Node* toBeDeleted = list->start;
		Car deletedCar = toBeDeleted->car;

		if (list->start->next) {
			list->start = list->start->next;
			list->start->prev = NULL;

			free(toBeDeleted);
			return deletedCar;
		}
		else {
			free(toBeDeleted);
			list->start = NULL;
			list->end = NULL;

			return deletedCar;
		}

	}
	else {
		printf("List is empty\n");
		Car err = { .year = 0, .manufacturer = "ERR", .cc = 0 };
		return err;
	}

}

Car deleteFromEnd(DLList* list) {
	if (list->end) {

		Node* toBeDeleted = list->end;
		Car deletedCar = toBeDeleted->car;

		if (list->end->prev) {
			list->end = list->end->prev;
			list->end->next = NULL;

			free(toBeDeleted);
			return deletedCar;
		}
		else {
			free(toBeDeleted);
			list->start = NULL;
			list->end = NULL;

			return deletedCar;
		}

	}
	else {
		printf("List is empty\n");
		Car err = { .year = 0, .manufacturer = "ERR", .cc = 0 };
		return err;
	}
}


// TODO
// Match condition and delete
Car deleteByManufacturer(DLList* list, const char* manufacturer) {
	if (!list->start) {
		printf("\nThis list is empty!");
		Car err = { .year = 0,.manufacturer = "ERR",.cc = 0 };
		return err;
	}
	Node* temp = list->start;
	while (temp) {
		if (strcmp(temp->car.manufacturer, manufacturer) == 0) {
			Node* del = temp;
			Car delCar = del->car;
			if (temp->prev) {
				temp->prev->next = temp->next;
			}
			else {
				list->start = temp->next;
			}
			if (temp->next) {
				temp->next->prev = temp->prev;
			}
			else {
				list->end = temp->prev;
			}
			temp = temp->next;
			free(del);
			return delCar;
		}
		else {
			temp = temp->next;
		}
	}
}

Car* deleteCarsByYearTreshold(DLList* list, int year, int* noDeleted) {
	if (!list->start) {
		printf("\nThis is an empty list");
		*noDeleted = 0;
		return NULL;
	}
	Node* temp = list->start;
	Car* deletedCars = NULL;
	*noDeleted = 0;
	while (temp) {
		if (temp->car.year <= year) {
			Node* del = temp;
			Car delCar = del->car;
			if (temp->prev) {
				temp->prev->next = temp->next;
			}
			else {
				list->start = temp->next;
			}
			if (temp->next) {
				temp->next->prev = temp->prev;
			}
			else {
				list->end = temp->prev;
			}
			temp = temp->next;
			free(del);
			deletedCars = realloc(deletedCars, (*noDeleted + 1) * sizeof(Car));
			deletedCars[(*noDeleted)++] = delCar;
		}
		else {
			temp = temp->next;
		}
	}
	return deletedCars;
}

void printCar(Car car) {
	printf("%s from %d has %5.2f\n", car.manufacturer, car.year, car.cc);
}

void parseListBtoE(DLList list) {
	if (list.start) {
		while (list.start) {
			printCar(list.start->car);
			list.start = list.start->next;
		}
	}
	else {
		printf("List is empty\n");
	}
}

void parseListEtoB(DLList list) {
	if (list.end) {
		while (list.end) {
			printCar(list.end->car);
			list.end = list.end->prev;
		}
	}
	else {
		printf("List is empty\n");
	}
}

Car readCarFromFile(FILE* f) {

	char buffer[LINESIZE];

	fgets(buffer, LINESIZE, f);

	Car car;

	char* carData = NULL;

	carData = strtok(buffer, ",");
	car.year = atoi(carData);

	carData = strtok(NULL, ",");
	car.manufacturer = malloc((strlen(carData) + 1) * sizeof(char));
	strcpy(car.manufacturer, carData);

	carData = strtok(NULL, ",");
	car.cc = atof(carData);

	return car;

}

void readCarsFromFile(DLList* start, int* noCars, const char* fileName) {

	FILE* f;
	f = fopen(fileName, "r");

	while (!feof(f)) {
		insertAtEnd(start, readCarFromFile(f));
		*noCars += 1;
	}

	fclose(f);

}

int main() {

	int noCars = 0;
	int noDeleted = 0;
	DLList list;

	list.start = NULL;
	list.end = NULL;

	readCarsFromFile(&list, &noCars, "cars.txt");

	parseListBtoE(list);

	printf("\n%d cars were read from file\n", noCars);

	printf("-------------------\n");

	//parseListEtoB(list);


	//printf("-------------------\n");
	//Car deletedCar = deleteFromBeginning(&list);
	//printf("Deleted car: \n");
	//printCar(deletedCar);
	//free(deletedCar.manufacturer);

	//printf("-------------------\n");
	//parseListBtoE(list);


	//printf("-------------------\n");
	//deletedCar = deleteFromEnd(&list);
	//printf("Deleted car: \n");
	//printCar(deletedCar);
	//free(deletedCar.manufacturer);

	//printf("-------------------\n");
	//parseListBtoE(list);

	//printf("-------------------\n");

	Car deletedCar = deleteByManufacturer(&list,"BMW");
	printf("Deleted car: \n");
	printCar(deletedCar);
	free(deletedCar.manufacturer);
	printf("-------------------\n");
	parseListBtoE(list);


	Car* deletedCars = NULL;
	deletedCars = deleteCarsByYearTreshold(&list, 2018, &noDeleted);

	printf("\nMasinile sterse: \n");
	for (int i = 0; i < noDeleted; i++) {
		printCar(deletedCars[i]);
		free(deletedCars[i].manufacturer);
	}
	printf("-------------------\n");
	parseListBtoE(list);


	return 0;
}

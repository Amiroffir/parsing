#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable : 4996)


struct oscarActor {
	int index;
	int year;
	int age;
	char movie[100];
	char name[100];
	struct oscarActor* next;
	struct oscarActor* prev;
};
struct oscarActor* head = NULL;
struct oscarActor* tail = NULL;

void addActor(int index, int year, int age, char movie[100], char name[100]) {
	struct oscarActor* currentActor;
	currentActor = (struct oscarActor*)malloc(sizeof(struct oscarActor));
	currentActor->index = index;
	currentActor->year = year;
	currentActor->age = age;
	strcpy(currentActor->movie, movie);
	strcpy(currentActor->name, name);
	currentActor->next = NULL;
	if (head == NULL) {
		head = currentActor;
		tail = currentActor;
		currentActor->prev = NULL;
	
	}
	else {
		tail->next = currentActor;
		currentActor->prev = tail;
		tail = currentActor;
	}
}


void parsingIntoList(char fileName[100]) {
	
		FILE* file;
		int index;
		int age;
		char str[100];
		char name[100];
		char movie[100];
		int year;
		int count = 0;
		char* token;
		file = fopen(fileName, "r");
		if (file == NULL)
		{
			printf("Error opening file\n");
			return;

		}
		fgets(str, 100, file) != NULL;
		while (fgets(str, 100, file) != NULL)
		{
			token = strtok(str, ",");
			count = 1;
			while (token != NULL)
			{
				switch (count)
				{
				case 1: index = atoi(token); 
					break;
				case 2: year = atoi(token);
					break;
				case 3: age = atoi(token);
				case 4: strcpy(name, token);
					break;
				case 5: strcpy(movie, token);
					break;
				default:
					break;
				}	
				token = strtok(NULL, ",");
				count++;
			}
			addActor(index, year, age, movie, name);
		}
		fclose(file);
}

void loadFile(char fileName[100]) {

	FILE* fp;
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("Error opening file\n");
		return;

	}
	parsingIntoList(fileName);
}

void printList() {
	struct oscarActor* currentActor = head;
	while (currentActor != NULL)
	{
		printf("%d, %d, %d, %s, %s\n", currentActor->index, currentActor->year, currentActor->age, currentActor->movie, currentActor->name);
		currentActor = currentActor->next;
	}
}

void PrintAllMoviesForYear(int Year) {
	{
		struct oscarActor* currentActor = head;
		while (currentActor != NULL)
		{
			if (currentActor->year == Year)
			{
				printf("%s\n", currentActor->movie);
			}
			currentActor = currentActor->next;
		}
	}
}
void GetMovieByIndex(int Index) {
	{
		struct oscarActor* currentActor = head;
		while (currentActor != NULL)
		{
			if (currentActor->index == Index)
			{
				printf("%s\n", currentActor->movie);
			}
			currentActor = currentActor->next;
		}
	} {
	}
}

	int main(){
		loadFile("oscar_age_female.csv");
		printList();
		return 0;
	};
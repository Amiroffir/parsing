#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable : 4996)

struct oscerActor_Header {
	int version;
	int itemsCount;
	char reserve[100];
};
struct oscerActor_Header header;
struct oscarActor {
	int index;
	int year;
	int age;
	char movie[100];
	char name[100];
	int popularity;
	struct oscarActor* next;
	struct oscarActor* prev;
};
struct oscarActor* head = NULL;
struct oscarActor* tail = NULL;

// add actor to the list
void addActor(int index, int year, int age, char movie[100], char name[100]) {
	struct oscarActor* currentActor;
	currentActor = (struct oscarActor*) malloc(sizeof(struct oscarActor));
	currentActor->index = index;
	currentActor->year = year;
	currentActor->age = age;
	strcpy(currentActor->movie, movie);
	strcpy(currentActor->name, name);
	currentActor->popularity = 0;
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

// parsing from a txt file into a list
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

// reading a txt file and parsing it into a list
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

// print the list
void printList() {
	struct oscarActor* currentActor = head;
	while (currentActor != NULL)
	{
		printf("%d, %d, %d, %s, %s\n", currentActor->index, currentActor->year, currentActor->age, currentActor->movie, currentActor->name);
		currentActor = currentActor->next;
	}
}

// print list by year
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
// print movie by index
void GetMovieByIndex(int Index) {

	struct oscarActor* currentActor = head;
	while (currentActor != NULL)
	{
		if (currentActor->index == Index)
		{
			printf("%s\n", currentActor->movie);
		}
		currentActor = currentActor->next;
	} 
}

// updating actor popularity
void updatePopularity(int Index) {
	struct oscarActor* currentActor = head;
	while (currentActor != NULL)
	{
		if (currentActor->index == Index)
		{
			currentActor->popularity++;
		}
		currentActor = currentActor->next;
	}
}

// returns the items count
int getItemCount() {
		int count = 0;
		struct oscarActor* currentActor = head;
		while (currentActor != NULL)
		{
			count++;
			currentActor = currentActor->next;
		}
		return count;
}
// runs a random numbers and updates the popularity if they're equal index in the list
void run() {
	int i = 0;
	time_t timeNow;
	srand(time(NULL));
	while (i < 1000) {
			int randomIndex = rand() % 100;
			if (randomIndex > 0 && randomIndex < getItemCount) {
				updatePopularity(randomIndex);
			}
			i++;
	}
}

// function that save linked list to a file

void save(char fileName[100]) {
	//struct oscerActor_Header header;
	header.version = 1;
	header.itemsCount = getItemCount();
	FILE* f;
	f = fopen(fileName, "w");
	if (f == NULL) {
		printf("Error");
	}
	// write the header only
	fwrite(&header, sizeof(struct oscerActor_Header), 1, f);
	
	// write to file all the items in the list one by one
	struct oscarActor* currActor = head;
	for (int i = 0; i < header.itemsCount; i++)
	{
		fwrite(currActor, sizeof(struct oscarActor), 1, f);
		currActor = currActor->next;
	}
	fclose(f);
}

// function that load linked from a file

void load(char fileName[100]) {
	FILE* f;
	f = fopen(fileName, "r");
	if (f == NULL) {
		printf("Error");
	}
	
	if (fread(&header, sizeof(struct oscerActor_Header), 1, f) != 0) {
		head = NULL;
		tail = NULL;
		for (int i = 0; i < header.itemsCount; i++)
		{
			struct oscarActor* currActor = (struct oscarActor*) malloc(sizeof(struct oscarActor));
			fread(currActor, sizeof(struct oscarActor), 1, f); 
			addActor(currActor->index, currActor->year, currActor->age, currActor->movie, currActor->name);
		}
	}
}

// print the most popular winner name
void mostPopularWinner() {
	int currMax = 0;
	char currPrint[100];
	struct oscarActor* currentActor = head;
	while (currentActor != NULL)
	{
		if (currentActor->popularity > currMax)
		{
			strcpy(currPrint, currentActor->name);
			currMax = currentActor->popularity;
		}
		currentActor = currentActor->next;
	}
	printf("%s %d", currPrint,currMax);
}

	int main(){
		//loadFile("C:\\Users\\Amir Offir\\VSC-workspace\\ZioNet Course\\oscar_age_female.csv");
		//save("acotesList.bin");
		load("C:\\Users\\Amir Offir\\Downloads\\hen4.bin");
		//load("acotesList.bin");
	printList();
		return 0;
	};
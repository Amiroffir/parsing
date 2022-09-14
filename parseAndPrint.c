#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable : 4996)




void parsing(char filename[100]) {
	{
		FILE* file;
		char str[100];
		char name[100];
		char movie[100];
		int year;
		int count = 0;
		char* token;
		file = fopen(filename, "r");
		if (file == NULL)
		{
			printf("error opening file\n");
			return;

		}
		fgets(str, 100, file) != NULL;
		while (fgets(str, 100, file) != NULL)
		{
			token = strtok(str, ",");
			count = 0;
			while (token != NULL)
			{
				if (count == 1)
				{
					year = atoi(token);

				}
				else if (count == 3)
				{
					strcpy(name, token);
				}
				else if (count == 4)
				{
					strcpy(movie, token);

				}
				token = strtok(NULL, ",");
				count++;

			}
			printf("the oscar goes to %s at %d movie %s\n", name, year, movie);
		}
		fclose(file);
	}
}
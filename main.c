#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const char str[] = "Out of cheese error +++ redo from start";

void printArray(char **arr, size_t n);
void allocFail(const char *msg);
void freeArray(char **arr, size_t n);

size_t setArray(char ***words, const char *str)
{
	size_t len = strlen(str);
	size_t nAllocatedWords = 1;
	*words = calloc(nAllocatedWords, sizeof(*words));
	if (*words == NULL) {
		allocFail("calloc() failed.");
	}
	size_t i = 0;
	size_t wordCount = 0;
	while (i < len) {
		while (isspace(str[i]))
			i++;
		size_t j = i;
		// count until next space.
		while (j < len && !isspace(str[j]))
			j++;			
		// i is the index of the first letter of word
		// j - 1 is the index of the last.
		if (i != j) {
			wordCount++;
			if (wordCount > nAllocatedWords) {
				nAllocatedWords += 10;
				char **tmp = NULL;
				tmp = realloc(*words, sizeof(**words) * nAllocatedWords);
				if (!tmp) {
					allocFail("realloc failed.");
				}
				*words = tmp;
			}
			size_t wordSize = j - i;
			char *tmp = calloc(wordSize + 1, sizeof(*tmp));
			if (!tmp) {
				allocFail("calloc failed.");
			}
			(*words)[wordCount - 1] = tmp;
			strncpy(tmp, &str[i], j - i);
			i = j + 1;
		}
	}
	return wordCount;
}


int main()
{
	char **arr = NULL;
	size_t n = setArray(&arr, str);
	printArray(arr, n);
	freeArray(arr, n);
	return 0;
}

void printArray(char **arr, size_t n)
{
	for (size_t i = 0; i < n; i++) {
		printf("%s\n", arr[i]);
	}
}

void allocFail(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

void freeArray(char **arr, size_t n)
{
	for (size_t i = 0; i < n; i++) {
		free(arr[i]);
	}
	free(arr);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TriePrediction.h"

// Function used to create a standard Trie.
// Initializes all children to NULL.
TrieNode *createTrieNode()
{
	int i;
	TrieNode *root = malloc(sizeof(TrieNode));

	for (i = 0; i < 26; i++)
    {
        root->children[i] = NULL;
	}

	root->subtrie = NULL;
	root->count = 0;

	return root;
}

// This particular function checks to see if there
// is any punctuation at the end of the string.
int append(char *str)
{
	int i = 1;
	int len = strlen(str);

	if(str[len - i] == '?' || str[len - i] == '.' || str[len - i] == '!')
    {
        return 1;
    }
    else
        return 0;
}

// This function creates a new string out of the existing one
// only containing lower case characters.
void stripPunctuators(char *str)
{
	int i, j;
	int len = strlen(str);
	char temp[1024];

	j = 0;

	for(i = 0; i < len; i++)
    {
        if(isalpha(str[i]))
        {
            temp[j] = str[i];
			temp[j] = (tolower(temp[j]));
			j++;
		}
	}

	temp[j] = '\0';

	// Copy the string stored in temp into str.
	strcpy(str, temp);
}

// Insert a string into the Trie. If the string already
// exists in the trie, simply increment the count of the
// string.
void insertString(TrieNode *current, char *str, int index)
{
	int p, i;
	int j = 0;
	int len = strlen(str);
	char n = str[index];
	char buffer[1024];

	if (index > len - 1)
		return;

	// Insert at this position
	p = n - 'a';

	if (current->children[p] == NULL)
    {
		current->children[p] = createTrieNode();
	}

	if (index == len - 1)
    {
		current->children[p]->count++;
	}

	// Recursive implementation to traverse through the string
	insertString(current->children[p], str, index + 1);
}

// Retrieve and return the specified string.
TrieNode *getNode(TrieNode *root, char *str)
{
    int val;
	if(str[0] == '\0')
    {
        if (root->count == 0)
			return NULL;
		else
			return root;
	}

	val = str[0] - 'a';

	// Recursive implementation to move onto the next char
	if (root->children[val] != NULL)
		return getNode(root->children[val], str + 1);
    else
        return NULL;
}

// Open the file, which is the corpus used, and create a trie
// from the sentence.
TrieNode *buildTrie(char *filename)
{
	TrieNode *root, *temp = NULL, *save;
	char input[1024];
	char str[1024];
	char *str1, buffer[1024];
	char prev[1024];

	FILE *file = fopen(filename, "r");

	root = createTrieNode();
	strcpy(prev, "");

	while(fscanf(file, "%s", input) != EOF)
    {
		// Make sure the string only contains lowercase letters
		strcpy(str, input);
		stripPunctuators(str);

		if(append(input) == 1)
        {
			if(temp == NULL)
				insertString(root, str, 0);
			else
            {
				insertString(root, str, 0);

				if(temp->subtrie == NULL)
					temp->subtrie = createTrieNode();

				insertString(temp->subtrie, str, 0);
				temp = NULL;
			}

			if(append(prev) == 1)
            {
				strcpy(prev, input);
				continue;
			}
		}
		else
        {
			insertString(root, str, 0);

			if(temp == NULL)
			{
				temp = getNode(root, str);
			}
			else
            {
				// Create a new trie.
				if(temp->subtrie == NULL)
				{
					temp->subtrie = createTrieNode();
				}

				insertString(temp->subtrie, str, 0);
				temp = getNode(root, str);
			}
		}

		strcpy(prev, input);
	}
	// Close the file and return the newly allocated trie
	fclose(file);
	return root;
}

// Checks for the most frequent word in the subtrie of the current trie.
// Called by mostFrequentWord.
void freqSub(TrieNode *root, char *str, int *countString, char *buffer, int j, int *init)
{
	if (root == NULL)
		return;

	if (root->count > 0)
    {
		if(*init == 0)
		{
			strcpy(str, buffer);
			*countString = root->count;
			*init = 1;
		}

		// Compare the counts of new words
		if(root->count > *countString)
        {
			*countString = root->count;
			strcpy(str, buffer);
		}

	}

	// Taken from Sean Szumlanski's printTrie function
	int i;
	buffer[j + 1] = '\0';

	for (i = 0; i < 26; i++)
    {
		buffer[j] = 'a' + i;
		freqSub(root->children[i], str, countString, buffer, j + 1, init);
	}

	// Set the last character to the NULL sentinel
	buffer[j] = '\0';
}
// Searches the trie for the most frequently occurring word. Uses freqSub
// as a helper function.
void mostFrequentWord(TrieNode *root, char *str)
{
	TrieNode *node = getNode(root, str);
	int a, b, *countStr = NULL;
    int *init = 0;
    int freq;
    char buffer[1024], buffer1[1024];

	// Some pointer magic
	init = &b;
	countStr = &a;

	if(node == NULL)
    {
		return;
	}

	if(node->subtrie == NULL)
		return;

	*init = 0;

	freqSub(node->subtrie, buffer1, countStr, buffer, 0, init);
	strcpy(str, buffer1);
}

// printTrieHelper from Sean Szumlanski. Called by printTrie
// to help format the trie.
void printTrieHelper(TrieNode *root, char *buffer, int k)
{
	int i;

	if (root == NULL)
		return;

	if (root->count > 0)
		printf("%s (%d)\n", buffer, root->count);

	buffer[k + 1] = '\0';

	for (i = 0; i < 26; i++) {
		buffer[k] = 'a' + i;

		printTrieHelper(root->children[i], buffer, k + 1);
	}

	buffer[k] = '\0';
}

// printTrie function from Sean Suzmlanski. Uses printTrieHelper
// to get the format of the trie correct.
void printTrie(TrieNode *root, int useSubtrieFormatting)
{
	char buffer[1026];

	if (useSubtrieFormatting) {
		strcpy(buffer, "- ");
		printTrieHelper(root, buffer, 2);
	}
	else {
		strcpy(buffer, "");
		printTrieHelper(root, buffer, 0);
	}
}

// This function is used to assist main in formating the trie.
void format(char *filename, TrieNode *root)
{
	FILE *file = fopen(filename, "r");
	int a, b, i = 0;
	TrieNode *tNode = NULL, *node = NULL;
	char c[1024];
	char cmd[1024], buffer[1024], input[1024];
	int len = strlen(cmd);

	while(fscanf(file, "%s", cmd) != EOF)
    {
		if(strcmp(cmd, "!") == 0)
		{
			printTrie(root, 0);
		}
		else if(strcmp(cmd, "@") == 0)
        {
			fscanf(file, "%s", cmd);
			fscanf(file, "%d", &i);
			printf("%s", cmd);

			strcpy(input, cmd);
			stripPunctuators(input);

			// Check if the node exists
			tNode = getNode(root, input);
			if(tNode == NULL)
            {
				printf("\n");
				continue;
			}

			mostFrequentWord(root, input);

			// Copy the frequent word
			strcpy(c, input);
			printf(" %s", c);

			if(i > 1)
            {
				for(b = 1; b < i; b++)
				{
					tNode = getNode(root, c);
					if(tNode->subtrie == NULL)
					{
						break;
					}

					mostFrequentWord(root, c);
					printf(" %s", c);
				}
			}
			printf("\n");
		}
		// The input is just a string..
		else
        {
			printf("%s\n", cmd);

			for(i = 0; i < len; i++)
            {
				cmd[i] = tolower(cmd[i]);
			}

            // If the string is not in the trie at all
            // print invalid string.
			if(getNode(root, cmd) == NULL)
            {
				printf("(INVALID STRING)\n");
				continue;
			}

			node = getNode(root, cmd);

			// If the subtrie of the node is empty,
			// print empty.
			if(node->subtrie == NULL)
            {
				printf("(EMPTY)\n");
				continue;
			}
			printTrie(node->subtrie, 1);
		}

	}

	fclose(file);
}

// Free all dynamically allocated memory associated with the
// current trie. This function is implemented recursively.
TrieNode *destroyTrie(TrieNode *root)
{
	int i;
	for(i = 0; i < 26; i++)
		if (root->children[i] != NULL)
			destroyTrie(root->children[i]);

	// If the root node has a subtrie, first destroy the subtrie
	// then free the root itself.
	if (root->subtrie != NULL)
		destroyTrie(root->subtrie);

	free(root);
	return NULL;
}

double difficultyRating(void)
{
	return 4.8;
}

double hoursSpent(void)
{
	return 27.0;
}

// Main function that takes in command line arguments.
int main(int argc, char **argv)
{
	TrieNode *root = NULL;
	root = buildTrie(argv[1]);

	// format is called within main
	format(argv[2], root);

	// Destroy the trie before freeing the root
	root = destroyTrie(root);
	free(root);

	return 0;
}

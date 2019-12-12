#ifndef __TRIE_PREDICTION_H
#define __TRIE_PREDICTION_H

#define MAX_WORDS_PER_LINE 30
#define MAX_CHARACTERS_PER_WORD 1023


typedef struct TrieNode
{
	// number of times this string occurs in the corpus
	int count;

	// 26 TrieNode pointers, one for each letter of the alphabet
	struct TrieNode *children[26];

	// the co-occurrence subtrie for this string
	struct TrieNode *subtrie;
} TrieNode;


// Functional Prototypes

TrieNode *buildTrie(char *filename);

TrieNode *destroyTrie(TrieNode *root);

double difficultyRating(void);

double hoursSpent(void);

#endif

//
//  main.c
//  lab10
//
//  Created by Suga Singh on 4/19/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int count;
};

// Trie structure
struct Trie {
    struct TrieNode* root;
};

// Create a new Trie node
struct TrieNode* createTrieNode() {
    struct TrieNode* x = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        x->children[i] = NULL;}
    x->count = 0;
    return x;}

// Inserts the word to the trie structure
void insert(struct Trie* pTrie, char* word) {
    struct TrieNode* x = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++) {
        int idx = word[i] - 'a';
        if (x->children[idx] == NULL) {
            x->children[idx] = createTrieNode();}
        
        x = x->children[idx];}
    x->count++;}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct Trie* pTrie, char* word) {
    struct TrieNode* x = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++) {
        int idx = word[i] - 'a';
        if (x->children[idx] == NULL) {
            return 0;}
        
        x = x->children[idx];}
    return x->count;}

// Deallocate the trie node
struct TrieNode* deallocateTrieNode(struct TrieNode* node) {
    if (node == NULL) {
        return NULL;}
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = deallocateTrieNode(node->children[i]);}
    free(node);
    return NULL;}

// Deallocate the trie structure
struct Trie* deallocateTrie(struct Trie* tr) {
    tr->root = deallocateTrieNode(tr->root);
    free(tr);
    return NULL;}

// Initializes a trie structure
struct Trie* createTrie() {
    struct Trie* pTrie = (struct Trie*)malloc(sizeof(struct Trie));
    pTrie->root = createTrieNode();
    return pTrie;
}

// This function will read the dictionary file, count the number of words,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** words) {
    FILE* x;
    int numWords = 0;
    char word[256];

    x = fopen(filename, "r");
    if (x == NULL) {
        perror("Error opening file");
        exit(1);}

    fscanf(x, "%d", &numWords);
    for (int i = 0; i < numWords; ++i) {
        fscanf(x, "%s", word);
        words[i] = strdup(word);}

    fclose;
    return numWords;}

int main(void) {
    char* inWords[256];
    int numWords = readDictionary("dictionary.txt", inWords);

    // Read the dictionary words
    printf("%d\n", numWords);
    for (int i = 0; i < numWords; ++i)
        printf("%s\n", inWords[i]);

    struct Trie* pTrie = createTrie();

    // Insert dictionary words into the trie
    for (int i = 0; i < numWords; i++)
        insert(pTrie, inWords[i]);

    // Test the occurrences of some words
    char* pWords[] = { "notaword", "ucf", "no", "note", "corg" };
    for (int i = 0; i < 5; i++)
        printf("\t%s %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));

    pTrie = deallocateTrie(pTrie);

    if (pTrie != NULL)
        printf("There is an error in this program\n");

    // Deallocate the memory for the dictionary words
    for (int i = 0; i < numWords; ++i)
        free(inWords[i]);

    return 0;
}

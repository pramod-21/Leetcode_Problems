#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000   // Hash table size
#define MAX_LEN    10000  // Max URL length

// Node for hash table entry
typedef struct Node {
    char* key;          // short URL
    char* value;        // original long URL
    struct Node* next;  // for collision handling (chaining)
} Node;

Node* hashTable[TABLE_SIZE];

// Simple hash function (sum of chars mod table size)
unsigned int hash(char* str) {
    unsigned int h = 0;
    while (*str) {
        h = (h * 31 + *str++) % TABLE_SIZE;
    }
    return h;
}

// Insert key-value pair into hash table
void insert(char* key, char* value) {
    unsigned int idx = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->next = hashTable[idx];
    hashTable[idx] = newNode;
}

// Search by key
char* search(char* key) {
    unsigned int idx = hash(key);
    Node* curr = hashTable[idx];
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            return curr->value;
        }
        curr = curr->next;
    }
    return NULL; // not found
}

// Encodes a URL to a shortened URL.
char* encode(char* longUrl) {
    // Hash the long URL into an ID
    unsigned int id = hash(longUrl);

    // Create short URL
    char* shortUrl = (char*)malloc(50);
    sprintf(shortUrl, "http://tinyurl.com/%u", id);

    // Store mapping in hash table
    insert(shortUrl, longUrl);

    return shortUrl;
}

// Decodes a shortened URL to its original URL.
char* decode(char* shortUrl) {
    return search(shortUrl);
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Node for linked list stack
struct Node {
    int data;
    struct Node* next;
};

struct Node* top = NULL; // stack top pointer

// Stack utility functions
int isEmpty() {
    return top == NULL;
}

void push(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) return; // memory allocation failed
    newNode->data = value;
    newNode->next = top;
    top = newNode;
}

int pop() {
    if (isEmpty()) return -1;
    struct Node* temp = top;
    int popped = temp->data;
    top = top->next;
    free(temp);
    return popped;
}

void clearStack() {
    while (!isEmpty()) {
        pop();
    }
}

// Matching brackets check
bool isMatchingPair(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '{' && closing == '}') ||
           (opening == '[' && closing == ']');
}

// Valid parentheses function
bool isValid(char* s) {
    clearStack(); // Reset stack for each call

    for (int i = 0; s[i] != '\0'; i++) {
        char ch = s[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty()) return false; // closing without opening
            char topChar = pop();
            if (!isMatchingPair(topChar, ch)) return false;
        }
    }
    return isEmpty(); // all brackets matched
}
#define MAX_LEVEL 16
#define P 0.5

typedef struct SkiplistNode {
    int val;
    struct SkiplistNode **forward;
} SkiplistNode;

typedef struct {
    SkiplistNode *head;
    int level;
} Skiplist;


SkiplistNode* createNode(int val, int level) {
    SkiplistNode* node = (SkiplistNode*)malloc(sizeof(SkiplistNode));
    node->val = val;
    node->forward = (SkiplistNode**)malloc(sizeof(SkiplistNode*) * level);
    for (int i = 0; i < level; i++) {
        node->forward[i] = NULL;
    }
    return node;
}

int randomLevel() {
    int lvl = 1;
    while ((double)rand() / RAND_MAX < P && lvl < MAX_LEVEL) {
        lvl++;
    }
    return lvl;
}


Skiplist* skiplistCreate() {
    srand((unsigned int)time(NULL));  
    Skiplist* list = (Skiplist*)malloc(sizeof(Skiplist));
    list->level = 1;
    list->head = createNode(-1, MAX_LEVEL);  
    return list;
}


bool skiplistSearch(Skiplist* obj, int target) {
    SkiplistNode* curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--) {
        while (curr->forward[i] && curr->forward[i]->val < target) {
            curr = curr->forward[i];
        }
    }
    curr = curr->forward[0];
    return curr && curr->val == target;
}

// Add
void skiplistAdd(Skiplist* obj, int num) {
    SkiplistNode* update[MAX_LEVEL];
    SkiplistNode* curr = obj->head;

    for (int i = obj->level - 1; i >= 0; i--) {
        while (curr->forward[i] && curr->forward[i]->val < num) {
            curr = curr->forward[i];
        }
        update[i] = curr;
    }

    int lvl = randomLevel();
    if (lvl > obj->level) {
        for (int i = obj->level; i < lvl; i++) {
            update[i] = obj->head;
        }
        obj->level = lvl;
    }

    SkiplistNode* newNode = createNode(num, lvl);
    for (int i = 0; i < lvl; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
}


bool skiplistErase(Skiplist* obj, int num) {
    SkiplistNode* update[MAX_LEVEL];
    SkiplistNode* curr = obj->head;

    for (int i = obj->level - 1; i >= 0; i--) {
        while (curr->forward[i] && curr->forward[i]->val < num) {
            curr = curr->forward[i];
        }
        update[i] = curr;
    }

    curr = curr->forward[0];
    if (!curr || curr->val != num) return false;

    for (int i = 0; i < obj->level; i++) {
        if (update[i]->forward[i] != curr) break;
        update[i]->forward[i] = curr->forward[i];
    }

    free(curr->forward);
    free(curr);

    while (obj->level > 1 && obj->head->forward[obj->level - 1] == NULL) {
        obj->level--;
    }

    return true;
}


void skiplistFree(Skiplist* obj) {
    SkiplistNode* curr = obj->head;
    while (curr) {
        SkiplistNode* next = curr->forward[0];
        free(curr->forward);
        free(curr);
        curr = next;
    }
    free(obj);
}


/**
 * Your Skiplist struct will be instantiated and called as such:
 * Skiplist* obj = skiplistCreate();
 * bool param_1 = skiplistSearch(obj, target);
 
 * skiplistAdd(obj, num);
 
 * bool param_3 = skiplistErase(obj, num);
 
 * skiplistFree(obj);
*/
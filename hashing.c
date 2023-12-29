

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 23

typedef struct KeyValue {
    char *key;
    char *value;
    bool isDeleted;
} KeyValue;

typedef struct {
    KeyValue **array;
    int size;
    float load_factor;
    // num of keys present
    int num_keys;
    // num of array indices of the table that are occupied
    int num_occupied_indices;
    // num of ops done so far
    int num_ops;
} HashTable;


KeyValue *createKeyValue(char *key, char *value) {
    KeyValue* newKeyValue = (KeyValue*)malloc(sizeof(KeyValue));
    if (newKeyValue != NULL) {
        newKeyValue->key = key;
        newKeyValue->value = value;
    }
    return newKeyValue;
}

HashTable* createHashTable() {
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    newTable->array = (KeyValue **)malloc(TABLE_SIZE * sizeof(KeyValue *));
    for (int i=0; i<TABLE_SIZE; i++)
        newTable->array[i] = NULL;

    newTable->size = TABLE_SIZE;
    newTable->load_factor = 0;
    newTable->num_keys = 0;
    newTable->num_occupied_indices = 0;
    newTable->num_ops = 0;
    return newTable;
}


// use sum of ascii values to convert string to int
int key_to_int(char* key){
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += (int)key[i];
    }
    return sum;
}

// return the index position in the table where the insertion happens
// return -1 if insertion fails
int insert_key_value(HashTable *ht, char *key, char *value) {
    int index = key_to_int(key) % ht->size;
    int initial_index = index;
    int num_probes = 1;

    while (ht->array[index] != NULL) {
        if (strcmp(ht->array[index]->key, key) == 0) {
            // Key already exists, update the value
            ht->array[index]->value = value;
            return index;
        }
        // Linear probing: Move to the next index
        index = (initial_index + num_probes * num_probes) % ht->size;
        num_probes++;
        ht->num_ops++;
    }

    // Insert the new key-value pair
    KeyValue *newKeyValue = createKeyValue(key, value);
    ht->array[index] = newKeyValue;
    ht->num_keys++;
    ht->num_occupied_indices++;
    ht->load_factor = (float)ht->num_keys / ht->size;
    ht->num_ops++;
    return index;
}


// return the value of the key in the table
// return NULL if key not found
char *search_key(HashTable *ht, char* key){
    int index = key_to_int(key) % ht->size;
    int initial_index = index;
    int num_probes = 1;
    while(ht->array[index] != NULL){
        if(strcmp(ht->array[index]->key, key)==0){
            return ht->array[index]->value;
        }

        index = ( initial_index + num_probes * num_probes ) % ht->size;
        num_probes++;
        ht->num_ops++;
    }

    return NULL;
}

// return the index position in the table where the deletion happens
// return -1 if deletion fails
int delete_key(HashTable *ht, char* key){
    int index = key_to_int(key) % ht->size;
    int initial_index = index;
    int num_probes = 1;

    while(ht->array[index]!=NULL){
        if(strcmp(ht->array[index]->key,key) == 0){
            free(ht->array[index]);
            ht->array[index] = NULL;
            ht->num_keys--;
            ht->num_ops++;
            ht->num_occupied_indices--;
            return index;
        }

        index = (initial_index + num_probes * num_probes) % ht->size;
        num_probes++;
        ht->num_ops++;
    }

    printf("Key not found.");
    return -1;
    
}

// this equals the number of keys in table/size of table
float get_load_factor(HashTable *ht) {
    return ((float)ht->num_keys) / ((float)ht->size) ;
}

// this equals the number of operations done so far/num of elems in table
int get_avg_probes(HashTable *ht){
    return ht->num_ops/ht->num_keys;
}

// display hash table visually
void display(HashTable *ht) {
    printf("Hash Table Contents:\n");
    for (int i = 0; i < ht->size; i++) {
        if (ht->array[i] != NULL) {
            printf("%d: Key='%s', Value='%s'\n", i, ht->array[i]->key, ht->array[i]->value);
        } else {
            printf("%d: NULL\n", i);
        }
    }
}

int main (){

    HashTable * ht = createHashTable();

    insert_key_value(ht, "first name", "Shreya");
    insert_key_value(ht, "last name", "Rathod");
    insert_key_value(ht, "uid", "2022300087");
    insert_key_value(ht, "sport", "football");
    insert_key_value(ht, "food", "Biryani");
    insert_key_value(ht, "holiday", "diwali");
    insert_key_value(ht, "role_model", "priyanka chopra");
    insert_key_value(ht, "subject", "DSA");
    insert_key_value(ht, "song", "yellow");
    insert_key_value(ht, "movie", "ERAS TOUR");
    insert_key_value(ht, "colour", "BLUE");
    insert_key_value(ht, "book", "Mansfield Park");

    display(ht);
    char value[20];
    strcpy(value, search_key(ht,"food"));
    printf("\nSearching value for Key:food-->");
    printf("Value:%s\n", value);

    delete_key(ht,"food");
    printf("\nHash Table after deleting:\n");

    display(ht);

    float load_factor = get_load_factor(ht);
    int avg_probes = get_avg_probes(ht);
    printf("\nLoad Factor:%f",load_factor);
    printf("\nAvg Probes:%d",avg_probes);
    



    return 0;
}
// -> Insert the following key, values in the table:
// 1. 'first name' -> <your first name>
// 2. 'last name' -> <your last name>
// 3. 'uid' -> <your uid>
// 4. 'sport' -> <your favorite sport>
// 5. 'food' -> <your favorite food>
// 6. 'holiday' -> <your favorite holiday destination>
// 7. 'role_model' -> <your role model>
// 8. 'subject' -> <your favourite subject>
// 9. 'song' -> <your favourite song>
// 10. 'movie' -> <your favorite movie>
// 11. 'colour' -> <your favorite colour>
// 12. 'book' -> <your favorite book>

// -> Test the table with search and delete operations
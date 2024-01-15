#include <stdio.h>
#include <stdlib.h>

typedef struct Vec {
    void **data;
    size_t count;
    size_t capacity;
} Vec;

typedef struct Person {
    char *name;
    char *surname;
    int age;
} Person;

void vec_pop(Vec *vec)
{
   if (vec->count <= 0) return;

   free(vec->data[vec->count - 1]);
   vec->count--;
   vec->capacity--;
}

void vec_shift(Vec *vec)
{
   if (vec->count <= 0) return;

   free(vec->data[0]);

   for (size_t i = 0; i < vec->count - 1; ++i) {
       vec->data[i] = vec->data[i + 1];
   }

   vec->count--;
   vec->capacity--;
}

void vec_push(Vec *vec, void *data) 
{
    if (vec->count == vec->capacity) {
        vec->capacity *= 2;
        vec->data = realloc(vec->data, vec->capacity * sizeof(void *));
        if (!vec->data) {
            fprintf(stderr, "ERROR: Failed to reallocate memory for vector data.\n");
            exit(EXIT_FAILURE);
        }
    }

    vec->data[vec->count] = data;
    vec->count++;

}

Vec* vec_init(size_t capacity) 
{
    Vec *vec = malloc(sizeof(Vec));
    if (!vec) {
       fprintf(stderr, "ERROR: Failed to allocate memory for vector.\n");
       exit(EXIT_FAILURE);
    }

    vec->data = malloc(capacity * sizeof(void *));
    if (!vec->data) {
       fprintf(stderr, "ERROR: Failed to allocate memory for vector data.\n");
       free(vec);
       exit(EXIT_FAILURE);
    }

    vec->count = 0;
    vec->capacity = capacity;

    return vec;
}

int main(void) 
{
    Vec *vec = vec_init(20);
 
    for (size_t i = 0; i < 100; ++i) {
        Person *person = malloc(sizeof(Person));
        person->name = "John";
        person->surname = "Doe";
        person->age = i;
        vec_push(vec, person);
    }

    vec_pop(vec);
    vec_shift(vec);
    vec_shift(vec);
    vec_pop(vec);
    for (size_t i = 0; i < vec->count; i++) {
        Person *p = (Person *)vec->data[i];
        printf("Name: %s, Surname: %s, Age: %d\n", p->name, p->surname, p->age);
    }

    free(vec->data);
    free(vec);

    return 0;
}


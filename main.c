#include "vec.h"
#define MAX_SIZE 100000

typedef struct Person {
    char *name;
    char *surname;
    int age;
} Person;

int main(void) 
{
    Vec *vec = vec_init(20);
 
    for (size_t i = 0; i < MAX_SIZE; ++i) {
        Person *person = malloc(sizeof(Person));
        person->name = "John";
        person->surname = "Doe";
        person->age = i;
        vec_push(vec, person);
    }

    for (size_t i = 0; i < vec->count; ++i) {
        Person *p = (Person *)vec->data[i];
        if (p->age % 2 == 0) 
            vec_remove(vec, i);
    }
    
    while( vec->count > 20) {
        vec_shift(vec);
    }

    while( vec->count > 2) {
        vec_pop(vec);
    }

    for (size_t i = 0; i < vec->count; ++i) {
        Person *p = (Person *)vec->data[i];
        printf("Name: %s, Surname: %s, Age: %d\n", p->name, p->surname, p->age);
    }

    vec_destory(vec);
    return 0;
}


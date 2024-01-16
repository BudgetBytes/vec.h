#include "vec.h"

typedef struct Person {
    char *name;
    char *surname;
    int age;
} Person;

int main(void) 
{
    Vec *vec = vec_init(20);
 
    for (size_t i = 0; i < 30; ++i) {
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
    vec_remove(vec, 200);
    for (size_t i = 0; i < vec->count; i++) {
        Person *p = (Person *)vec->data[i];
        printf("Name: %s, Surname: %s, Age: %d\n", p->name, p->surname, p->age);
    }

    vec_destory(vec);
    return 0;
}


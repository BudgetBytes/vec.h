#ifndef VEC_H
#define VEC_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Vec {
    void **data;
    size_t count;
    size_t capacity;
} Vec;

// Remove index element 
void vec_remove(Vec *vec, size_t index) {
    if (vec->count <= 0 || vec->count < index) {
        printf("ERROR: Cannot remove index %zu. Count->%zu.\n", index, vec->count);
        return;
    };

    free(vec->data[index]);
    for (size_t i = index; i < vec->count - 1; ++i) {
        vec->data[i] = vec->data[i + 1];
    }

    vec->count--;
    vec->capacity--;
}

// Remove last element 
void vec_pop(Vec *vec)
{
    if (vec->count <= 0) {
        printf("ERROR: Count->%zu.\n", vec->count);
        return;
    };

    free(vec->data[vec->count - 1]);
    vec->count--;
    vec->capacity--;
}

// Remove first element 
void vec_shift(Vec *vec)
{
    if (vec->count <= 0) {
        printf("ERROR: Count->%zu.\n", vec->count);
        return;
    }

    free(vec->data[0]);

    for (size_t i = 0; i < vec->count - 1; ++i) {
       vec->data[i] = vec->data[i + 1];
    }

   vec->count--;
   vec->capacity--;
}

// Append element 
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

// Destroy vector and free memory
void vec_destory(Vec *vec) {
    for (size_t i = 0; i < vec->count; ++i) free(vec->data[i]);
    free(vec->data);
    free(vec);
}

// Initialize vector
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

#endif //VEC_H




#include "lite_vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

lite_vector* lv_new_vec(size_t type_size) {
    lite_vector* new_vec1 = (lite_vector*)malloc(sizeof(lite_vector));
    
    //Return with null if memory allocation fails for new vector struct
    if(new_vec1 == NULL) {
        printf("Failed to create new vector\n");
        return NULL;
    }

    //Initializing the vector struct to default values
    new_vec1->length = 0;
    new_vec1->max_capacity = 1;
    new_vec1->type_size = type_size;

    //Allocate memory for the data pointer of a vector struct
    new_vec1->data = (void**)malloc(new_vec1->max_capacity * sizeof(void*));
    
    //Return w/ null if memory allocation fails for the struct's data pointer
    if(new_vec1->data == NULL) {
        lv_cleanup(new_vec1);
        return NULL;
    }

    return new_vec1;
}

void lv_cleanup(lite_vector* vec) {

    //Check if the vector contains data to clear it
    if(vec != NULL) {
        lv_clear(vec);
        free(vec->data);
    }

    free(vec);
}

size_t lv_get_length(lite_vector* vec) {
    
    //Returns length of vec if it contains data
    if(vec != NULL) { 
        return vec->length;
    }
    else {
        return 0;
    }
}

bool lv_clear(lite_vector* vec) {

    if(vec != NULL) {
        //Iterate through all pointers (strings) and frees them
        for(int i = 0; i < lv_get_length(vec); ++i) {
            free(vec->data[i]);
        }

        //Set the current vector length to zero since all items have been cleared
        vec->length = 0;

        return true;
    }

    return false;
}

void* lv_get(lite_vector* vec, size_t index) {
    //Check if the vector is not null and index is in range of total length
    if((vec != NULL) && (index < lv_get_length(vec))) {
        return vec->data[index];
    }

    return NULL;
}

/**
 * lv_resize is essentially private since we marked it static.
 * The job of this function is to attempt to resize the vector.
 * There may be functions you can call to do this for you, or
 * you may write it yourself.  Either way it isn't too hard.
 * With everything though, check to make sure the code worked
 * and return appropriately.  Do NOT destroy the data if the code
 * fails.  If the resize cannot complete, the original vector
 * must remain unaffected.
 */
static bool lv_resize(lite_vector* vec) {
    if(vec != NULL) {

        //Make a new max capacity limit with +1 and use it to resize
        size_t resize_cap = vec->max_capacity + 1;
        //Make a new data pointer for strings & reallocate memory for it
        void** new_data = realloc(vec->data, resize_cap * sizeof(void*));

        //Check if new data pointer memory reallocation fails to return false
        if (new_data == NULL) {
            return false;
        }

        //Replace the max capacity and string pointers with the new values
        vec->max_capacity = resize_cap;
        vec->data = new_data;

        return true;
    }

    return false;
}

bool lv_append(lite_vector* vec, void* element) {
    //Check if vector is not null, length is within max cap range, & resize is successful
    if((vec != NULL) && (lv_get_length(vec) < vec->max_capacity) && (lv_resize(vec) == true)) {

        //Allocate memory to the new appended string pointer
        vec->data[lv_get_length(vec)] = malloc(vec->type_size);
        
        //Check if the previous memory allocation failed and return false
        if(vec->data[lv_get_length(vec)] == NULL) {
            return false;
        }

        //Use memcpy to copy the element to the new string pointer in the vector
        memcpy(vec->data[lv_get_length(vec)], element, vec->type_size);
        //Update the vector's length by +1
        vec->length++;

        return true;
    }

    return false;
}

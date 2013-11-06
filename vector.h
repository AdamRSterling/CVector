#ifndef _GUARD_vector_h
#define _GUARD_vector_h

#include <stdlib.h>
#include <assert.h>

typedef struct Vect* Vector;

struct Vect {
   size_t capacity; // Maximum vector size
   size_t items; // Number of items in vector
   void** data; // Internal array

   // Functions associated with this vector
   void (*add)(Vector, void*);
   void (*set)(Vector, void*, int);
   void (*removeAt)(Vector, int);
   void* (*getAt)(Vector, int);
   size_t (*getSize)(Vector);
   void (*destructVector)(Vector);
};

Vector constructVector();
void add(Vector, void*);
void set(Vector, void*, int);
void removeAt(Vector, int);
void* getAt(Vector, int);
size_t getSize(Vector);
void destructVector(Vector);
#endif

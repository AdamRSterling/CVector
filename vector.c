#include "vector.h"

static void resize(Vector vec, size_t newCapacity)
{
   // Hidden function which takes care of well behaved resizing cases
   // Well behaved meaning when the array is growing, or shrinking without
   // shifting the array over.
   assert(newCapacity != 0);
   vec->data = realloc(vec->data, sizeof(void*) * newCapacity);
   vec->capacity = newCapacity;
}

Vector constructVector()
{
   Vector vec = (Vector)malloc(sizeof(struct Vect));

   // Initialize all function pointers
   vec->add = &add;
   vec->getAt = &getAt;
   vec->destructVector = &destructVector;
   vec->removeAt = &removeAt;
   vec->set = &set;
 
   // Initialize the internal fields.
   vec->capacity = 1;
   vec->items = 0;
   vec->data = calloc(vec->capacity, sizeof(void*));

   return vec;
}

void add(Vector vec, void* toAdd)
{
   vec->data[vec->items] = toAdd;
   vec->items++;

   if(vec->items == vec->capacity)
   // If we're at capacity, double the size of the vector.
   {
      resize(vec, vec->capacity * 2);
   }
}

void set(Vector vec, void* toSet, int index)
{
   assert(index >= 0 && index <= vec->capacity);
   // If within boundaries, set value at the index.
   vec->data[index] = toSet;
}

void removeAt(Vector vec, int index)
{
   assert(index >= 0 && index <= vec->capacity);
   // If within boundaries, remove value at the index.
   // Linear running time!
   vec->data[index] = NULL;

   if(vec->capacity == 1)
   // Do not resize if capacity is at 1, the minimum vector size.
   // Allocating an array of size 0 leads to bad results.
   {
      // Might be a good idea to log to stderr?
      return;
   }
  
   if(index != vec->items)
   // If removing at the end, copying the array might be avoidable.
   {
      void** newData;

      if(vec->items - 1 <= vec->capacity/4)
      // If the vector is 1/4th full, resize. 1/2 leads to
      // improper amoritization.
      {
         newData = calloc(vec->capacity/2, sizeof(void*));
         vec->capacity /= 2;
      }

      else
      // If not, no need to resize.
      {
         newData = calloc(vec->capacity, sizeof(void*));
      }
      
      int i, j;
      for(i = 0, j = 0; i < vec->items; i++)
      {
         if(vec->getAt(vec, i) != NULL)
         {
            newData[j] = vec->getAt(vec, i);
            j++;
         }
         // Move every value over to the left until done.
      }
      free(vec->data);
      vec->data = newData;
   }
   else if(vec->items - 1 <= vec->capacity / 4)
   // If removing from the end, BUT the array is too empty, resizing is needed.
   {
      resize(vec, vec->capacity/2);
   }
   vec->items--;
}

void* getAt(Vector vec, int index)
{
   assert(index >= 0 && index <= vec->capacity);
   return vec->data[index];
   // If within boundaries, return the value in the array at index.
}

size_t getSize(Vector vec)
{
   return vec->items;
   // Return the number of items. Consider changing name from getSize to
   // Something which makes the distinction between items and capacity clear.
}

void destructVector(Vector vec)
{
   free(vec->data);
   free(vec);
   // Clean up the internal data, then the vector.
}

#include "vector.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
   Vector vec = constructVector();


   vec->add(vec, "Hello");
   vec->add(vec, "world!");

   printf("%s, %s\n", (char*)vec->getAt(vec, 0), (char*)vec->getAt(vec, 1));
   // The vector cannot know the type of data being passed to it. Casting must
   // be done by the user for the vector to work.

   vec->add(vec, "Fizz");
   vec->add(vec, "Buzz");

   vec->set(vec, "Reset!", 3);

   printf("%s\n", (char*)vec->getAt(vec, 2));
   printf("%s\n", (char*)vec->getAt(vec, 3));

   vec->removeAt(vec, 0);
   vec->removeAt(vec, 0);
   vec->removeAt(vec, 0);
   vec->removeAt(vec, 0);

   vec->removeAt(vec, 0); // One too many removals. Error quietly handled.

   vec->add(vec, "Yet more stuff!");
   vec->add(vec, "But wait, there's more!");

   printf("%s %s\n", (char*)vec->getAt(vec, 0), (char*)vec->getAt(vec, 1));

   vec->destructVector(vec);

   return 0;
}

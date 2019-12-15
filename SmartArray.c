// SmartArray.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SmartArray.h"

// Creates a new SmartArray dynamically and initiallizes its values.
SmartArray *createSmartArray(int length)
{
	int i;

  // Initialization of the new struct which will be returned.
  SmartArray *newSmarty = malloc(sizeof(SmartArray *));

  // Setting the initial values of newSmarty.
  newSmarty->array = NULL;
  newSmarty->size = -1;
  newSmarty->capacity = -1;

  // Determining which length to use for newSmarty.
  if (length < DEFAULT_INIT_LEN)
  {
    length = DEFAULT_INIT_LEN;
    newSmarty->array = malloc(sizeof(char*) * length);

    // Sets all the pointers in newSmarty to NULL.
    for (i = 0; i < length; i++)
      newSmarty->array[i] = NULL;

    // Initializes newSmarty's other values.
    newSmarty->size = 0;
    newSmarty->capacity = length;
  }

  else
  {
    newSmarty->array = malloc(sizeof(char*) * length);

    Sets all the pointers in newSmarty to NULL.
    for (i = 0; i < length; i++)
      newSmarty->array[i] = NULL;

    // Initializes newSmarty's other values.
    newSmarty->size = 0;
    newSmarty->capacity = length;
  }

  // If something went wrong with malloc, return NULL.
  if (newSmarty == NULL || newSmarty->array == NULL)
    return NULL;

  printf("-> Created new SmartArray of size %d.\\n", length);

  return newSmarty;
}

// Destroys a SmartArray, frees any memory, and returns NULL.
SmartArray *destroySmartArray(SmartArray *smarty)
{
    int i, length;
    
    // Check if smarty has anything to destroy.
    if(smarty == NULL)
        return NULL;

		length = getSize(smarty);

    // Frees the nested arrays first.
    for(i = 0; i < length; i++)
    {
        free(smarty->array[i]);
        smarty->array[i] = NULL;
    }

    // Frees the internal array.
    free(smarty->array);
    smarty->array = NULL;

    // Frees the whole struct.
    free(smarty);
    smarty = NULL;

    return smarty;
}

// Expands a SmartArray and updates any internal variables.
SmartArray *expandSmartArray(SmartArray *smarty, int length)
{
    int i, lengthSmarty;
    char **tempArray = NULL;

    // Makes sure we can expand the given array.
    if(smarty->capacity >= length || smarty->array == NULL)
        return smarty;

    // Creates a temp array and sets up its values.
    tempArray = malloc(sizeof(char *) * length);

		lengthSmarty = getSize(smarty);
		
    for(i = 0; i < length; i++)
        tempArray[i] = NULL;
    for(i = 0; i < lengthSmarty; i++)
        tempArray[i] = smarty->array[i];

    // Destroys the memory of the old smarty struct.
    SmartArray *destroySmartArray(SmartArray *smarty)
    // Updates the variables.
    smarty->capacity = length;
    smarty->array = tempArray;

    printf("-> Expanded SmartArray to size %d.\\n", length);

    return smarty;
}

// Trims the length of the array if capcity is greater than size.
SmartArray *trimSmartArray(SmartArray *smarty)
{
    int i, length;
    char **tempArray = NULL;

		length = getSize(smarty);

    // Checks that the correct conditions are met (capacity > size).
    if(smarty->capacity > length)
    {
        // Creates a temp array with length equal to size.
        tempArray = malloc(sizeof(char *) * length);

        // Sets values for the temp array.
        for(i = 0; i < length; i++)
        {
            *(tempArray + i) = NULL;
            *(tempArray + i) = smarty->array[i];
        }

        // Destroys the memory of the old smarty struct.
        SmartArray *destroySmartArray(SmartArray *smarty);

        // Updates the variables.
        smarty->capacity = getSize(smarty);
        smarty->array = tempArray;

        printf("-> Trimmed SmartArray to size %d.\\n", smarty->capacity);
    }

    return smarty;
}

// Puts a copy of str into the next unused cell of smarty.
char *put(SmartArray *smarty, char *str)
{
    int i = 0, strLength = 0;

    // Verifies needed conditions.
    if(smarty == NULL || smarty->array == NULL || str == NULL)
      return NULL;

    // If size equals capacity, expands the array to have an extra cell
    // in order to put something in.
    if(smarty->size == smarty->capacity)
      smarty = expandSmartArray(smarty, (smarty->capacity * 2 + 1));

    // Finds unused cell in the array.
    while(smarty->array[i] != NULL && i < smarty->capacity)
      i++;

    strLength = strlen(str);

    // Double checks array doesn't need expanded.
    if(i >= smarty->capacity)
      expandSmartArray(smarty, (smarty->capacity * 2 + 1));

    // Allocates space.
    free(smarty->array[i]);
    smarty->array[i] = malloc(sizeof(char) * (strLength + 1));

    // Copies str into next available cell.
    strcpy(smarty->array[i], str);
    smarty->size++;

    return smarty->array[i];
}

// Gets the element at the given index and return.
char *get(SmartArray *smarty, int index)
{
    int length = getSize(smarty);

    // Checks conditions are met.
    if (smarty == NULL || index < 0 || index >= length)
      return NULL;

    return smarty->array[index];
}

//  Replaces a string at a valid index with a copy of str.
char *set(SmartArray *smarty, int index, char *str)
{
    int strLength = strlen(str);

    // Checks the conditions.
    if (index < 0 || index > smarty->size - 1 || smarty == NULL || str == NULL)
        return NULL;

    // Copies a string to a given index.
    free(smarty->array[index]);
    smarty->array[index] = malloc(sizeof(char) * strLength + 1);
    strcpy(smarty->array[index], str);

    return smarty->array[index];
}

// Inserts a copy of str at the specified index in the array.
char *insertElement(SmartArray *smarty, int index, char *str)
{
    int i = 0, j = 0, length;
    int strLength = strlen(str);

    // Makes sure smarty and str are valid.
    if(smarty == NULL || str == NULL)
      return NULL;

    // Expands the smarty if needed to insert element.
    if(smarty->size == smarty->capacity)
    	expandSmartArray(smarty, (smarty->capacity * 2 + 1));

    // Checks if all the cells are occupied.
    while(smarty->array[i] != NULL)
        i++;

    length = getSize(smarty);

    // Index will be placed in the first empty cell if it is
		// greater than the size.
    if(index > length)
        index = i;

    // Double checks if array needs expanded.
    if(i >= smarty->capacity)
    {
        expandSmartArray(smarty, ((smarty->capacity * 2) + 1));
        index = i;
    }

    length = getSize(smarty);

    // Shifts all elements to the right.
    for(j = length; j > index; j--)
    {
        smarty->array[j] = smarty->array[j - 1];
        smarty->array[j - 1] = NULL;
    }

    smarty->size++;

    // Copies a string to a given index.
    free(smarty->array[index]);
    smarty->array[index] = malloc(sizeof(char) * strLength);
    strcpy(smarty->array[index], str);

    return smarty->array[index];
}

// Removes and element at a specified index.
int removeElement(SmartArray *smarty, int index)
{
    int i = 0, length = getSize(smarty);

    //  Checks necessary conditions.
    if(smarty == NULL || index < 0 || index >= length || smarty->array[index] == NULL)
      return 0;

    free(smarty->array[index]);

    // Moves strings to new locations.
    for(i = index; i < length - 1; i++)
    {
        smarty->array[i] = smarty->array[i + 1];
        smarty->array[i + 1] = NULL;
    }

    smarty->size--;

    return 1;
}

// Returns the number of elements currently in the array.
int getSize(SmartArray *smarty)
{
    if (smarty == NULL)
        return -1;

    return smarty->size;
}

// Prints the strings currently in the array.
void printSmartArray(SmartArray *smarty)
{
    int i, length = getSize(smarty);

    //  If one of these conditions are met, the array is empty.
    if (smarty == NULL || smarty->size == 0 || smarty->array[0] == NULL)
    {
      printf("(empty array)\\n");
      return;
    }

    // Prints all the elements.
    else
    {
      for (i = 0; i < length; i++)
          printf("%s\\n", smarty->array[i]);
    }
    return;
    }
}

#include <stdio.h>
#include <string.h>
#include "SmartArray.h"

int main(void)
{
	int i; char buffer[32];

	SmartArray *smarty1 = createSmartArray(-1);
	SmartArray *smarty2 = createSmartArray(-1);

	FILE *ifp = fopen("names.txt", "rb");

	// Read all names from the file and add them to smarty1.
	while (fscanf(ifp, "%s", buffer) != EOF)
		put(smarty1, buffer);

	// Add the names to smarty2 in reverse order.
	for (i = getSize(smarty1) - 1; i >= 0; i--)
		put(smarty2, get(smarty1, i));

	// Print the contents of smarty1.
	printf("\n-- SMART ARRAY 1: --\n");
	printSmartArray(smarty1);

	// Print the contents of smarty2.
	printf("\n-- SMART ARRAY 2 (First Names): --\n");
	printSmartArray(smarty2);

	// Swap last names with first names in smarty2.
	for (i = 0; i < getSize(smarty2); i++)
	{
		if (strcmp(get(smarty2, i), "Andres") == 0)
			set(smarty2, i, "Posadas");
		else if (strcmp(get(smarty2, i), "Christopher") == 0)
			set(smarty2, i, "Sipes");
		else if (strcmp(get(smarty2, i), "Hanna") == 0)
			set(smarty2, i, "Reed");
		else if (strcmp(get(smarty2, i), "John") == 0)
			set(smarty2, i, "Lien");
		else if (strcmp(get(smarty2, i), "Kexin") == 0)
			set(smarty2, i, "Liao");
		else if (strcmp(get(smarty2, i), "Mohammad") == 0)
			set(smarty2, i, "Ahmadian");
		else if (strcmp(get(smarty2, i), "Richie") == 0)
			set(smarty2, i, "Wales");
		else if (strcmp(get(smarty2, i), "Sandesh") == 0)
			set(smarty2, i, "Sharma");
	}

	// Print the contents of smarty2.
	printf("\n-- SMART ARRAY 2 (Last Names): --\n");
	printSmartArray(smarty2);

	// Print smarty1 (in reverse order) and smarty2, to match up first and last
	// names.
	printf("\n-- COMBINED ARRAYS (First and Last Names): --\n");
	for (i = 0; i < getSize(smarty2); i++)
		printf("%s %s\n", get(smarty1, getSize(smarty1) - 1 - i), get(smarty2, i));

	// Add elements from smarty1 to the end of smarty1 (in reverse order).
	printf("\n");
	for (i = getSize(smarty1) - 1; i >= 0; i--)
		printf("Adding %s to smarty1 ...\n", put(smarty1, get(smarty1, i)));

	// Print the contents of smarty1.
	printf("\n-- SMART ARRAY 1: --\n");
	printSmartArray(smarty1);

	// Insert a string at the beginning of array smarty1.
	insertElement(smarty1, 0, "List of Names:");

	// Print the contents of smarty1.
	printf("\n-- SMART ARRAY 1: --\n");
	printSmartArray(smarty1);

	// Remove all elements from smarty1.
	while (getSize(smarty1))
		removeElement(smarty1, 0);

	// Print smarty1, which is now an empty array.
	printf("\n-- SMART ARRAY 1: --\n");
	printSmartArray(smarty1);

	// Destroy our smart arrays.
	smarty1 = destroySmartArray(smarty1);
	smarty2 = destroySmartArray(smarty2);

	// Make sure smarty1 is good and destroyed (and that destroySmartArray
	// doesn't segfault when passed a NULL pointer).
	smarty1 = destroySmartArray(smarty1);

	// Print the empty arrays one last time.
	printf("\n-- SMART ARRAY 1: --\n");
	printSmartArray(smarty1);

	printf("\n-- SMART ARRAY 2: --\n");
	printSmartArray(smarty2);

	return 0;
}

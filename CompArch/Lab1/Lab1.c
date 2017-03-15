#include "MemoryHeader.h"
#include <stdio.h>

int main() {
int val=0, v=0, flag=0;

printf("Set value in Memory[0] like 10");
sc_memorySet(0,10);
printf("\nValue: %d", Memory[0]);

printf("\nSet value in Memory[150] like 2");
sc_memorySet(150,2);
printf("\nValue: %d", Memory[150]);
sc_regGet(OVERFLOW_MEMORY, &flag);
printf("\n\nFlag OVERFLOW_MEMORY (if == 1 all is OK) : %d", flag);

printf("Get value from Memory[0] (if == 10 all is OK)");
sc_memoryGet(0, &val);
printf("\n%d\n", val);

printf("\nSet old value 10, New value 20\n");
sc_memorySet(1,10);
sc_memorySave("Memory");
sc_memorySet(1,20);
sc_memoryGet(1, &v);
printf("New value is %d", v);
sc_memoryLoad("Memory");
sc_memoryGet(1, &val);
printf("\nLoad memory and get old value: %d\n", val);

system("PAUSE");
}

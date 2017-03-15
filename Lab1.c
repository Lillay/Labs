#include <stdio.h>

#define OVERFLOW_IN_PROCESS 0 //переполнение при выполнении операции
#define ZERO_DIV 1 //деление на ноль
#define OVERFLOW_MEMORY 2 //переполнение памяти
#define IGNORING_STEP 3 // пропуск такта
#define WRONG_COMMAND 4 //неверная команда

int Memory[100];
int flag;
int code[38] = {
0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32,
0x33, 0x40, 0x41, 0x42, 0x43, 0x51, 0x52,
0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
0x67, 0x68, 0x69, 0x70, 0x71, 0x72, 0x73,
0x74, 0x75, 0x76};

int sc_memoryInit () {
    int i;
    for (i=0; i<100; i++) {
        Memory[i] = 0;
    }

    return 0;
}

int sc_memorySet (int address, int value) {
    if ( (address > 99) || (address < 0) ) {
            sc_regSet(OVERFLOW_MEMORY, 1);
            return -1;
    }
    else {
            Memory[address] = value;
    }
}

int sc_memoryGet (int address, int * value) {
    if ( (address > 99) || (address < 0) ) {
            sc_regSet(OVERFLOW_MEMORY, 1);
            return -1;
    }
    else {
            *value = Memory[address];
    }
}

int sc_memorySave (char * filename) {
    FILE *mf;
    mf = fopen(filename,"wb");

    if (mf) {
        fwrite(Memory, sizeof(int), sizeof(Memory), mf);
        fclose(mf);
        return 0;
    }
    return -1;
}

int sc_memoryLoad (char * filename) {
    FILE *mf;
    mf = fopen(filename,"rb");
    if (mf) {
        fread(Memory, sizeof(int), sizeof(Memory), mf);
        fclose(mf);
        return 0;
    }
    return -1;
}

int sc_regInit (void) {
    flag = 0;
    return 0;
}

int sc_regSet (int registr, int value) {
    if ((registr > -1) && (registr < 5)) {
        if ((value == 0) || (value == 1)) {
            if (value) {
                flag = flag|(1<<(registr-1));
                return 0;
            }
            else {
                flag = flag&(~(1<<(registr-1)));
                return 0;
            }
        }
        return -1;
    }
    return -1;
}

int sc_regGet(int registr, int *value) {
    if ((registr > -1) && (registr < 5)) {
        *value = (flag>>(registr-1))&0x1;
        return 0;
    }
    return -1;
}

int sc_commandEncode(int command, int operand, int *value) {
    int i=0, f=0;

    for (i=0; i<38; i++) {
        if (command == code[i]) {
            f = 1;
            break;
        }
    }

    if (f) {
        *value = command*128+operand;
        return 0;
    }
    else {
        return -1;
    }
}

int sc_commandDecode(int value, int *command, int *operand) {
    if ((command != NULL) && (operand != NULL)) {
        *command = value/128;
        *operand = value%128;
        return 0;
    }
    sc_regSet(WRONG_COMMAND, 1);
    return -1;
}

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

// Oliver Moreno
// 12/03/2021
// Tiny Machine Simulator implementing basic Instruction Set Architecture
// the first line of the input file was said to have a number to indicate the amount of commands in the file.
// there are 2 integers on each line (opcode and device/address) following the first line of the input file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct instruction {
    char opCode;
    char address;
} instruction;

instruction IM[100];
instruction MDR1[100];
instruction IR[100];
int DM[10]; 
int PC = 0, MAR = 0, AC = 0;

void instructionSet();
void loadCommand();
void addCommand();
void storeCommand();
void subtractCommand();
void inputCommand();
void outputCommand();
void endCommand();
void jumpCommand();
void skipCommand();

int main(int argc, char **argv) {

  int numCommands;

  FILE *ifp = fopen(argv[1], "r"); // "r" for read

    // scan in the number of commands
    fscanf(ifp, "%d\n", &numCommands);

    printf("\nAssembling Program...\nProgram Assembled.\n\nRun.\n\n");
    printf("PC = 0 | A = 0 | DM = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]\n");

      // fetch and execute cycle
      for (MAR = 0; MAR < numCommands; MAR++) {

          // FETCH
          MAR = PC; // MAR <- PC (Copy contents of PC into MAR)
          PC++; // PC <- PC + 1 (Increment PC)
          MDR1[MAR] = IM[MAR]; // MDR <- IM[MAR] (Load content of memory location into MDR)
          IR[MAR] = MDR1[MAR]; // IR <- MDR (Copy value stored in MDR to IR)

              // read in the opcode and address/device
              fscanf(ifp, "%c %c %*[^\n]\n", &IR[MAR].opCode, &IR[MAR].address);
              // converts characters to integers
              IR[MAR].opCode = IR[MAR].opCode-'0';
              IR[MAR].address = IR[MAR].address-'0';
              //printf("%d %d\n", IR[MAR].opCode, IR[MAR].address);

              // EXECUTE
              instructionSet();

              // status update displaying Program Counter, Accumulator, and Data Memory
              printf("PC = %d | A = %d | DM = [", PC, AC);
                  for (int j = 0; j < 10; j++) {
                      printf("%d, ", DM[j]);
                          if (j == 9)
                            printf("%d]\n", DM[j]);
                  }
      }

  fclose(ifp);

  return 0;
}

// set of instructions containing commands to execute
void instructionSet() {

  if (IR[MAR].opCode == 1) loadCommand();

  if (IR[MAR].opCode == 2) addCommand();

  if (IR[MAR].opCode == 3) storeCommand();

  if (IR[MAR].opCode == 4) subtractCommand();

  if (IR[MAR].opCode == 5) inputCommand();
  
  if (IR[MAR].opCode == 6) outputCommand();
  
  if (IR[MAR].opCode == 7) endCommand();
  
  if (IR[MAR].opCode == 8) jumpCommand();

  if (IR[MAR].opCode == 9) skipCommand();
}

// Execution: 01 LOAD
void loadCommand() {
    int tmp = IR[MAR].address; // MAR <- IR.ADDR (Copy the IR address value field into MAR)
    printf("/* loading from address %d /*\n", tmp); // MDR <- MEM[MAR]
    AC = DM[tmp]; // A <- MDR (Copy content of MDR into A register)
}
// Execution: 02 ADD
void addCommand() {
    int tmp = IR[tmp].address; // MAR <- IR.ADDR (Copy the IR address value field into MAR)
    printf("/* adding value at address %d to value in accumulator */\n", tmp); // MDR <- MEM[MAR]
    AC = AC + DM[tmp]; // A <- A + MDR (Add contents of MDR and A register and store into A )
}
// Execution: 03 STORE
void storeCommand() {
    int tmp = IR[MAR].address; // MAR <- IR.ADDR (Copy the IR address value field into MAR)
    printf("/* storing accumulator to memory location %d */\n", tmp); // MDR <- A
    DM[tmp] = AC; // MEM[MAR] <- MDR (Copy content of MDR into a memory location)
}
// Execution: 04 SUBTRACT
void subtractCommand() {
    int tmp = IR[MAR].address; // MAR <- IR.ADDR (Copy the IR address value field into MAR)
    printf("/* subtracting value at address %d from accumulator */\n", tmp); // MDR <- MEM[MAR]
    AC = AC - DM[tmp]; // A <- A - MDR (Subtract contents of A register and MDR and store into A)
}
// Execution: 05 INPUT
void inputCommand() {
    printf("/* input value */\n"); 
    scanf("%d", &AC); // A <- Input value from keyboard
}
// Execution: 06 OUTPUT
void outputCommand() {
    printf("/* outputting accumulator to screen */\n%d\n", AC); // Screen <- A
}
// Execution: 07 END
void endCommand() {
    printf("Program complete.\n"); // STOP: program ends normally
    exit(0); // Run <- 0
}
// Execution: 08 JMP
void jumpCommand() {
    PC = IR[MAR].address; // PC <- IR.ADDR
}
// Execution: 09 SKIP
void skipCommand() {
    if (AC == 0) // IF (A == 0) PC <- PC + 1
        PC++;
}
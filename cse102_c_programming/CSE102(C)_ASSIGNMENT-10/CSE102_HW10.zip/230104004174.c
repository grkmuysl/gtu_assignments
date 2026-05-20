#include <stdio.h>
#include <string.h>

typedef struct {
    char codes[100][100];
    char type[100][100];
    char operations[100][100];

} Instructions;

typedef struct{
    char register_A[8] , register_B[8], program_counter[16], instruction_register[24];

} Registers;

int to_binary(int decimal_number){ /* convert decimal to binary */
   int binary_number = 0, bolum_sayisi = 0, eklenecek_sayi = 1, binary_icin_eklenecek = 900000000, i;

    while(decimal_number > 0){
        int mod = decimal_number % 2; /* 1 veya 0 */
        decimal_number /= 2;
        binary_number = binary_number + eklenecek_sayi * mod;
        eklenecek_sayi *= 10; /* her basamaktan sonra 10 üzerini arttiriyorum */

    }
    printf("\nbinary: %08d\n" , binary_number);
    printf("returned binary: %d\n" , binary_number + binary_icin_eklenecek); /* return edebilmek icin basina 9 ekliyorum */

    return binary_number;
}


int to_decimal(char binary_number[8]) { /* convert binary to decimal */
    int decimal_number = 0, i, j;

    for(i = 0; i < 8; i++){
        int eklenecek_sayi = 2;
        if(binary_number[i] == '1'){ /* binary number in basamagi 1 ise */
            for(j = 0; j < 7 - i - 1; j++){
                eklenecek_sayi *= 2;
            }
            decimal_number += eklenecek_sayi;
        }

    }
    printf("Decimal number is: %d \n" , decimal_number);
    return decimal_number;
}

void registersExecute(char opCode[8], int* register_A, int* register_B, int num){
    int tempNum ,i;

    if(strcmp(opCode, "00000001") == 0){ /* ADD A B */
        tempNum = *register_A + *register_B;
        *register_A = tempNum;
    }else if(strcmp(opCode, "00000010") == 0){ /* ADDI A I */
        tempNum = *register_A + num;
        *register_A = tempNum;
    }else if(strcmp(opCode, "00000100") == 0){ /* AND A B */
        if(*register_A == 0 || *register_B == 0){
            *register_A = 0;
        }
    }else if(strcmp(opCode, "00000101") == 0){ /* ANDI A I*/
        if(*register_A == 0 || num == 0){
            *register_A = 0;
        }
    }else if(strcmp(opCode, "00000111") == 0){ /* OR A B */
        if(*register_A == 1 || *register_B == 1){
            *register_A = 1;
        }
    }else if(strcmp(opCode, "00001000") == 0){ /* ORI A I */
        if(*register_A == 1 || num == 1){
            *register_A = 1;
        }
    }else if(strcmp(opCode, "00001010") == 0){ /* SUB A B */
        tempNum = *register_A - *register_B;
        *register_A = tempNum;
    }else if(strcmp(opCode, "00001011") == 0){ /* SUBI A I */
        tempNum = *register_A - num;
        *register_A = tempNum;
    }else if(strcmp(opCode, "00001101") == 0){ /* INC A */
         *register_A += 1;
    }else if(strcmp(opCode, "00001110") == 0){ /* DEC A */
         *register_B -= 1;
    }else if(strcmp(opCode, "00001111") == 0){ /* SHL A I  sola kaydirmak 2^n ile carpmak demek*/
        tempNum = 1;
        for(i = 0; i < num; i++){
            tempNum *= 2;
        }
        tempNum *= *register_A;
        *register_A = tempNum;
    }else if(strcmp(opCode, "00010000") == 0){ /* SHR A I saga kaydirmak 2^n ile bolmek demek */
        tempNum = 1;
        for(i = 0; i < num; i++){
            tempNum /= 2;
        }
        tempNum *= *register_A;
        *register_A = tempNum;
    }else if(strcmp(opCode, "00010100") == 0){ /* NOR A B */
        if(*register_A == 0 && *register_B == 0){
            *register_A = 1;
        }else{
            *register_A = 0;
        }
    }else if(strcmp(opCode, "00010111") == 0){ /* SWP A B */
        tempNum = *register_A;
        *register_A = *register_B;
        *register_B = tempNum;
    }else if(strcmp(opCode, "00011010") == 0){ /* PRI A */
        /*tempNum = to_decimal(*register_A); */
        printf("The value is: %d \n" , tempNum);
    }else if(opCode == "00011011"){ /* PRII I */
       /* tempNum = to_decimal(num); */
        printf("The value is: %d \n" , tempNum);
    }else if(strcmp(opCode, "00011011") == 0){ /* LDAI A I */
         *register_A = num;
    }else if(strcmp(opCode, "00011110") == 0){ /* EXIT */

    }
}

void find_opcode(char instruction_str[], Instructions all_instructions, int line_num , char inst_opCode[10]) {
    int i, j, isEqual = 0;
    int length_of_instruction = strlen(instruction_str);

    for (i = 0; i < line_num; i++) {
        char *result = strstr(all_instructions.operations[i], instruction_str);
        if (result != NULL) { /* eslesme var ise */
            isEqual = 1;
            for (j = 0; j < length_of_instruction; j++) {
                if (instruction_str[j] != all_instructions.operations[i][j]) {
                    isEqual = 0;
                    break;
                }
            }
            if (isEqual == 1) {  /* eslesme varsa */
                strcpy(inst_opCode, all_instructions.codes[i]);
                break;
            }
        }
    }
    printf("Opcode is :%s \n" , inst_opCode);
}


void execute_program(Instructions instructions, int line_num){
    Instructions myInst;
    char fileName[50];
    printf("enter a file name:");
    scanf("%s" , fileName);

    FILE* myFile2 = fopen(fileName , "r");

    if(myFile2 == NULL){
        printf("dosya acilamadi \n");
     
    }

    int order;
    char code[10] , register_a[10], register_b[10], inst_opCode[10];

    while (fscanf(myFile2, "%d %s %s %s", &order, code, register_a, register_b) == 4) {

    find_opcode(code, instructions, line_num , inst_opCode); /* talimatin opcode unu buluyorum ardindan inst_opCode'a atiyorum */

}
    fclose(myFile2);

}

int main() {

    Instructions all_instructions;

    FILE* myFile = fopen("//home//gorkem//Desktop//instructions 1.txt" , "r");

    if(myFile == NULL){
        printf("dosya acilamadi! \n");
    }

    /* instructionslari okuyup struct içerisindeki arrayda tutuyorum */

    char line[100];
    int current_line = 0;
    while(fgets(line,sizeof(line),myFile)){

        char* token = strtok(line,"|"); /* | isaretine gore cumleyi boler */
        if(token != NULL){
            strcpy(all_instructions.codes[current_line] , token);
        }

        token = strtok(NULL, "|");
        if(token != NULL){
            strcpy(all_instructions.type[current_line] , token);
        }

        token = strtok(NULL , "|");
        if(token != NULL){
            strcpy(all_instructions.operations[current_line] , token);
        }

        current_line += 1;
    }


    execute_program(all_instructions, current_line);
    to_binary(10);
    to_decimal("00001010");
    fclose(myFile);
    return 0;
}

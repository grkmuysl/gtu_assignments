#include <stdio.h>

int main() {
    /* Check for errors. */
    FILE *dataFile;
    dataFile = fopen("//home//gorkem//Desktop//data.txt" , "r");
    if (dataFile == NULL) {
        printf("An error occured while opening the file. \n");
        return 1;
    }

    int sayi1, sayi2, sayi3;
    int firstX_0,firstX_1= 0; /* these are flags */
    int max_x_0 , max_x_1 , max_y_0 ,max_y_1 ,min_x_0 , min_x_1 , min_y_0 ,min_y_1;
    while (fscanf(dataFile, "%d %d %d", &sayi1, &sayi2, &sayi3) != EOF) {

        if(sayi3 == 0){ /* checking the points where class is 0. */
            if(firstX_0 == 0){ /*since the first reading , I set the max and min values equal to the first number. */
                max_x_0 = sayi1;
                min_x_0 = sayi1;
                max_y_0 = sayi2;
                min_y_0 = sayi2;
                firstX_0 = 1; /* I changed the flag to 1. so that it would sync only the first time. */
            }
            if(sayi1 >max_x_0 ){ /* check for max and min values.*/
                max_x_0 = sayi1;
            }
            if(sayi2 > max_y_0){
                max_y_0 = sayi2;
            }
            if(sayi1 < min_x_0){
                min_x_0 = sayi1;
            }
            if(sayi2 < min_y_0){
                min_y_0 = sayi2;
            }

        }else if(sayi3 == 1){ /* checking the points where class is 0. */
            if(firstX_1 == 0){ /*since the first reading , I set the max and min values equal to the first number. */
                max_x_1 = sayi1;
                min_x_1 = sayi1;
                max_y_1 = sayi2;
                min_y_1 = sayi2;
                firstX_1 = 1; /* I changed the flag to 1. so that it would sync only the first time. */
            }
            if(sayi1 >max_x_1 ){ /* check for max and min values.*/
                max_x_1 = sayi1;
            }
            if(sayi2 > max_y_1){
                max_y_1 = sayi2;
            }
             if(sayi1 < min_x_1){
                min_x_1 = sayi1;
            }
            if(sayi2 < min_y_1){
                min_y_1 = sayi2;
            }
        }
    }

/* QUESTION - 2*/
    int sepx,sepy;
    int r1, r2, r3, r4;
    int errorCount = 0;
    int minError , minErrorFlag = 0;
    int bestSeperatorX, bestSeperatorY , bestR1,bestR2,bestR3,bestR4 ;
    int minValueForSeperatorX , maxValueForSeperatorX , minValueForSeperatorY , maxValueForSeperatorY;

    if(min_x_0 < min_x_1 ){  /* Check max and min values of x and y For separators.*/
        minValueForSeperatorX = min_x_0;
    }else{
        minValueForSeperatorX = min_x_1;
    }
    if(min_y_0 < min_y_1 ){
        minValueForSeperatorY = min_y_0;
    }else{
        minValueForSeperatorY = min_y_1;
    }

    if(max_x_0 < min_y_1 ){
        maxValueForSeperatorX = max_x_0;
    }else{
        maxValueForSeperatorX = min_y_1;
    }
    if(max_y_0 < max_y_1 ){
        maxValueForSeperatorY = max_y_0;
    }else{
        maxValueForSeperatorY = max_y_1;
    }

    for (sepx = minValueForSeperatorX; sepx <= maxValueForSeperatorY; sepx++) { /* calculate every possibility for separators and  labels.*/
        for (sepy = min_x_0; sepy <= maxValueForSeperatorY; sepy++) {
            for (r1 = 0; r1 <= 1; r1++) {
                for (r2 = 0; r2 <= 1; r2++) {
                    for (r3 = 0; r3 <= 1; r3++) {
                        for (r4 = 0; r4 <= 1; r4++) {
                            /* reverting to the beginning of the file for reading.*/
                            FILE *dataFile2;
                            dataFile2 = fopen("//home//gorkem//Desktop//data.txt" , "r");

                            errorCount = 0;

                            while (fscanf(dataFile2, "%d %d %d", &sayi1, &sayi2, &sayi3) != EOF) { /* check one by one and take the best combination */
                                if (sayi1 <= sepx && sayi2 > sepy) {                                /*with the least errorCount. */
                                    if (sayi3 != r1) {
                                        errorCount += 1;
                                    }
                                } else if (sayi1 > sepx && sayi2 > sepy) {
                                    if (sayi3 != r2) {
                                        errorCount += 1;
                                    }
                                } else if (sayi1 <= sepx && sayi2 <= sepy) {
                                    if (sayi3 != r3) {
                                        errorCount += 1;
                                    }
                                } else if (sayi1 > sepx && sayi2 <= sepy) {
                                    if (sayi3 != r4) {
                                        errorCount += 1;
                                    }
                                }
                            }
                            if(minErrorFlag == 0){ /* I set the first ErrorCount equal to minError. */
                                minError = errorCount;
                                minErrorFlag = 1; /* I set the minErrorFlag to 1. for prevent it from looping again */
                            }else{
                                if(errorCount < minError){ /*take the best combination with for errorcount. */
                                    minError = errorCount;
                                    bestSeperatorX = sepx;
                                    bestSeperatorY = sepy;
                                    bestR1 = r1;
                                    bestR2 = r2;
                                    bestR3 = r3;
                                    bestR4 = r4;

                                }
                            }
                            fclose(dataFile2); /* due to revert beginning.*/
                        }
                    }
                }
            }
        }
    }

    fclose(dataFile); // close the file.

    FILE *dataFile3;
    dataFile3 = fopen("//home//gorkem//Desktop//test 1.txt" , "r");
    if (dataFile3 == NULL) {
        printf("An error occured while opening the file. \n");
        return 1;
    }
    int trueCountFor2 = 0;
    int numberOfDataPoints = 0;
    while (fscanf(dataFile3, "%d %d %d", &sayi1, &sayi2, &sayi3) != EOF){
        numberOfDataPoints += 1;
        if (sayi1 <= bestSeperatorX && sayi2 > bestSeperatorY) { /* check the points according to best Separators*/
            if (sayi3 == bestR1) {
                trueCountFor2 += 1; /* Increase trueCountFor2 by 1 for each correct match.*/
            }
        } else if (sayi1 > bestSeperatorX && sayi2 > bestSeperatorY) {
            if (sayi3 == bestR2) {
                trueCountFor2 += 1;
            }
        } else if (sayi1 <= bestSeperatorX && sayi2 <= bestSeperatorY) {
            if (sayi3 == bestR3) {
                trueCountFor2 += 1;
            }
        } else if (sayi1 > bestSeperatorX && sayi2 <= bestSeperatorY) {
            if (sayi3 == bestR4) {
                trueCountFor2 += 1;
            }
        }
    }

    int successRate = trueCountFor2 * 100 / numberOfDataPoints;
    fclose(dataFile3);

      /* QUESTION -3 and MENU  */
    FILE *dataFile4;
    dataFile4 = fopen("//home//gorkem//Desktop//test-final.txt" , "r");
    if (dataFile4 == NULL) {
        printf("An error occured while opening the file. \n");
        return 1;
    }

    int choice;
    int continueToInput = 1;
    printf("MENU:\n 1.Explore Data(RESULT OF QUESTION-1).\n 2.Train Model(RESULT OF QUESTION-2).\n 3.Test Model(RESULT OF QUESTION-3).\n 4.EXIT.\n");

    while(continueToInput == 1){
        printf("Please choose the process: ");
        scanf("%d" ,&choice);
        switch(choice){
            case 1:
                printf("\nMinimum and Maximum X and Y values:\n");
                printf("Class 0: X in [%d %d], Y in [%d %d] \n",min_x_0,max_x_0,min_y_0,max_y_0 );
                printf("Class 1: X in [%d %d], Y in [%d %d] \n",min_x_1,max_x_1,min_y_1,max_y_1 );
                break;

            case 2:
                printf("\nBest seperator coordinates: X = %d, Y = %d, Total Error = %d \n" ,bestSeperatorX , bestSeperatorY ,minError );
                printf("Region Labels: \n");
                printf("R1: Class Label %d \nR2: Class Label %d \nR3: Class Label %d \nR4: Class Label %d \n" ,bestR1,bestR2,bestR3,bestR4);
                printf("success rate : %% %d \n \n" , successRate );
                break;

            case 3:


                while (fscanf(dataFile4, "%d %d", &sayi1, &sayi2) != EOF){ /* guesses for test-final text's points. according to best separators.*/
                    numberOfDataPoints += 1;
                    if (sayi1 <= bestSeperatorX && sayi2 > bestSeperatorY) {
                        printf("For this point: X = %d, Y = %d " , sayi1 , sayi2);
                        printf("Class should be: %d \n" , bestR1);

                    }else if (sayi1 > bestSeperatorX && sayi2 > bestSeperatorY) {
                        printf("For this point: X = %d, Y = %d " , sayi1 , sayi2);
                        printf("Class should be: %d \n" , bestR2);
                    }else if (sayi1 <= bestSeperatorX && sayi2 <= bestSeperatorY) {
                        printf("For this point: X = %d, Y = %d " , sayi1 , sayi2);
                        printf("Class should be: %d \n" , bestR3);
                    }else if (sayi1 > bestSeperatorX && sayi2 <= bestSeperatorY) {
                        printf("For this point: X = %d, Y = %d " , sayi1 , sayi2);
                        printf("Class should be: %d \n" , bestR4);
                    }
                }
                fclose(dataFile4);
                break;
            case 4:
                printf("The program is closing...\n");
                continueToInput = 0;
                break;
            default:
                printf("\nPlease choose a valid process!\n");
        }
        if(continueToInput == 1){ /* check if user want to continue or not.*/
            printf("\nIf you want to continue please press 1. Otherwise press any key: ");
            scanf("%d" ,&continueToInput);
        }

    }



    return 0;
}

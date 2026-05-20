#include <stdio.h>

void initializeGame(int stoneCount, int lines[5][35]){
    int i;
    if(stoneCount <= 9){ /* tas sayisi tek basamakli ise*/
        for(i = 7; i < 28; i += 4){
            lines[1][i] = stoneCount;
            lines[3][i] = stoneCount;
        }
    }else{
        for(i = 7; i < 28; i += 4){
            int onlar_basamagi;
            onlar_basamagi = stoneCount / 10;
            /*onlar basamagi */
            lines[1][i-1] = onlar_basamagi;
            lines[3][i-1] = onlar_basamagi;
            /* birler basamagi*/
            lines[1][i] = stoneCount % 10;
            lines[3][i] = stoneCount % 10;
        }
    }
}

void printBoard(int lines[5][35]){
    int i, k;
    for(i = 0; i < 5; i++){
        for(k = 0 ; k < 35; k++){
            /* -1 ise => + , -2 ise => - , -3 ise => - | , -4 ise => ' ' yazdir. */
            if(lines[i][k] == -1 ){
                printf("+");
            }else if(lines[i][k] == -2){
                printf("-");
            }else if(lines[i][k] == -3){
                printf("|");
            }else if(lines[i][k] == -4){
                printf(" ");
            }else{
                printf("%d" ,lines[i][k]);
            }
        }
        printf("\n");
    }
}

int distributeStonesForPlayer(int indexOfCup , int countOfStone, int lineOfCups,int lines[5][35], int isPlayer){ /* kullanici icin tas dagitimi*/
    int enSonIndex;
    if(countOfStone >= 10){ /* cift basamakli ise*/
        lines[lineOfCups][indexOfCup - 1] = -4;
    }
    lines[lineOfCups][indexOfCup] = 0; /* tum taslari aldim.*/
    int i;
    for(i = indexOfCup + 4 ; i < 28; i += 4){ /* islem sonunda i = 31 olur*/
        if(countOfStone > 0){
            lines[lineOfCups][i] += 1;
            enSonIndex =  i;
            if(lines[lineOfCups][i] > 9){ /* cift basamakli ise*/
                lines[lineOfCups][i - 1] = lines[lineOfCups][i] / 10;
                lines[lineOfCups][i] = lines[lineOfCups][i] % 10;
            }
           countOfStone -= 1;
        }
    }
    if(countOfStone > 0 && i > 27 && isPlayer == 1){ /* player icin large cup'a at.*/
        lines[2][32] += 1;
        enSonIndex =  32;
        if(lines[2][32] > 9){ /*cift basamakli ise */
            lines[2][31] = lines[2][32] / 10;
            lines[2][32] = lines[2][32] % 10;
        }
        countOfStone -= 1;
    }
    if(countOfStone > 0 && i > 27){
        lineOfCups = 1; /* ust satira gecti*/
        int k;
        for(k = 27; k > 6; k -= 4){
            if(countOfStone > 0){
                lines[lineOfCups][k] += 1;
                enSonIndex = k;
                if(lines[lineOfCups][k] > 9){ /* cift basamakli ise*/
                lines[lineOfCups][k - 1] = lines[lineOfCups][k] / 10;
                lines[lineOfCups][k] = lines[lineOfCups][k] % 10;
                }
                countOfStone -= 1;
            }
        }
        if(countOfStone > 0 && k == 3 ){ /* sol uste geldiyse*/
            int j;
            lineOfCups = 3;
            for(j = 7; j < 28 ; j += 4){
                if(countOfStone > 0){
                    lines[lineOfCups ][j] += 1;
                    enSonIndex =  j;
                    countOfStone -= 1;
                    if(lines[lineOfCups][j] > 9){ /* cift basamakli ise*/
                        lines[lineOfCups][j - 1] = lines[lineOfCups][j] / 10;
                        lines[lineOfCups][j] = lines[lineOfCups][j] % 10;
                    }
                }
            }
        }
    }
    return enSonIndex + (lineOfCups*100); /* ust taraf icin 100-127 arasi bir deger donecek alt taraf icin ise 300-327 arasi*/
}

int distributeStonesForComputer(int indexOfCup , int countOfStone, int lineOfCups,int lines[5][35], int isComputer){
    int enSonIndex;
    if(countOfStone >= 10){ /* cift basamakli ise*/
        lines[lineOfCups][indexOfCup - 1] = -4;
    }
    lines[lineOfCups][indexOfCup] = 0; /* tum taslari aldim.*/
    int i;
    for(i = indexOfCup - 4 ; i > 6; i -= 4){ /* islem sonunda i = 3 olur*/
        if(countOfStone > 0){
            lines[lineOfCups][i] += 1;
            enSonIndex = i;
            if(lines[lineOfCups][i] > 9){ /* cift basamakli ise*/
                lines[lineOfCups][i - 1] = lines[lineOfCups][i] / 10;
                lines[lineOfCups][i] = lines[lineOfCups][i] % 10;
            }
           countOfStone -= 1;
        }
    }
    if(countOfStone > 0 && i < 7 && isComputer == 1){ /* computer's large cup'a at.*/
        lines[2][3] += 1;
        enSonIndex =  3;
         if(lines[2][3] > 9){ /*cift basamakli ise */
            lines[2][2] = lines[2][3] / 10;
            lines[2][3] = lines[2][3] % 10;
        }
        countOfStone -= 1;
    }
    if(countOfStone > 0 && i == 3){
        lineOfCups = 3; /* alt satira gecti*/
        int k;
        for(k = 7; k < 28; k += 4){
            if(countOfStone > 0){
                lines[lineOfCups][k] += 1;
                enSonIndex = k;
                if(lines[lineOfCups][k] > 9){ /* cift basamakli ise*/
                lines[lineOfCups][k - 1] = lines[lineOfCups][k] / 10;
                lines[lineOfCups][k] = lines[lineOfCups][k] % 10;
                }
                countOfStone -= 1;
            }
        }
        if(countOfStone > 0 && k == 31 ){ /* sag alta geldiyse*/
            int j;
            lineOfCups = 1;
            for(j = 27; j > 6 ; j -= 4){
                if(countOfStone > 0){
                    lines[lineOfCups ][j] += 1;
                    enSonIndex = j;
                    countOfStone -= 1;
                    if(lines[lineOfCups][j] > 9){ /* cift basamakli ise*/
                        lines[lineOfCups][j - 1] = lines[lineOfCups][j] / 10;
                        lines[lineOfCups][j] = lines[lineOfCups][j] % 10;
                    }
                }
            }
        }
    }
    return enSonIndex + (lineOfCups*100);
}

int move(int indexOfCup , int lines[5][35], int turn, int lineOfCups){
    int isComputer, isPlayer;
    if(turn == 1 && lineOfCups != 3){
        isPlayer = 0;
    }else if(turn == 1 && lineOfCups == 3){
        isPlayer = 1;
    }else if(turn != 1 && lineOfCups == 1){
        isComputer = 1;
    }else if(turn != 1 && lineOfCups == 3){
        isComputer = 0;
    }

    int countOfStone, sonIndex;
    if(lines[lineOfCups][indexOfCup - 1] > 0){ /* iki basamakli ise*/
        countOfStone = lines[lineOfCups][indexOfCup - 1] * 10 + lines[lineOfCups][indexOfCup];;
    }else{
       countOfStone = lines[lineOfCups][indexOfCup];
    }
    if(turn == 1 && isPlayer == 1){
        sonIndex = distributeStonesForPlayer(indexOfCup,countOfStone,lineOfCups,lines, isPlayer);
    }else if(turn == 1 && isPlayer != 1){
        sonIndex = distributeStonesForComputer(indexOfCup,countOfStone,lineOfCups,lines, isComputer);
    }else if(turn != 1 && isComputer == 1){
        sonIndex = distributeStonesForComputer(indexOfCup,countOfStone,lineOfCups,lines, isComputer);
    }else if(turn != 1 && isComputer != 1){
        sonIndex = distributeStonesForPlayer(indexOfCup,countOfStone,lineOfCups,lines, isPlayer);
    }
    printBoard(lines);
    return sonIndex;
}

int isGameEndF(int lines[5][35]){   /* oyun bitti mi kontrol et*/
        if(((lines[1][6] <= 0) && lines[1][7] == 0 && lines[1][11] == 0 &&
            (lines[1][14] <= 0) && lines[1][15] == 0 && lines[1][19] == 0 &&
            (lines[1][22] <= 0) && lines[1][23] == 0 && lines[1][27] == 0) ||
            ((lines[3][6] <= 0) && lines[3][7] == 0  && lines[3][11] == 0 &&
            (lines[3][14] <= 0) && lines[3][15] == 0 && lines[3][19] == 0 &&
            (lines[3][22] <= 0) && lines[3][23] == 0 && lines[3][27] == 0)){
            int scoreOfPlayer , scoreOfComputer;
            scoreOfPlayer = lines[2][31] * 10 + lines[2][32];
            scoreOfComputer = lines[2][2] * 10 + lines[2][3];
            if(scoreOfPlayer > scoreOfComputer){
                printf("You won! Your score is: %d \n", scoreOfPlayer);

            }else{
                printf("Computer won! Computer's score is: %d \n", scoreOfComputer);

            }
            return 1;
        }
        return 0;
}

int gamePlay(int lines[5][35]){
    int isGameEnd = 0;
    int selectedCup, indexOfCup , turn = 1;

    while(isGameEnd == 0){
        isGameEnd = isGameEndF(lines);
        if(isGameEnd == 1){
            break;
        }
        if(turn == 1){
            printf("Your turn! \n");
        }else{
            printf("Computer's turn! \n");
        }
        printf("Please select a cup: ");
        scanf(" %d" , &selectedCup);
        switch(selectedCup){
            case 1:
                indexOfCup = 7;
                break;
            case 2:
                indexOfCup = 11;
                break;
            case 3:
                indexOfCup = 15;
                break;
            case 4:
                indexOfCup = 19;
                break;
            case 5:
                indexOfCup = 23;
                break;
            case 6:
                indexOfCup = 27;
                break;
            default:
                printf("Please enter a valid cup!\n");
        }

        int lineOfCups;
        if(turn == 1){
            lineOfCups = 3;
        }else{
            lineOfCups = 1;
        }
        int sonIndex;
        sonIndex = move(indexOfCup, lines, turn, lineOfCups);

        int isTurnChanged = 0;
        while(isTurnChanged == 0){

            if(sonIndex > 300){ /* son tas alt siraya yerlesmis demek.*/

                sonIndex = sonIndex - 300;
                if(sonIndex == 32 || sonIndex == 3){ /* buyuk kaba geldi demek*/
                    break;
                }else if(lines[3][sonIndex] == 1){ /* bos kaba geldi demek*/
                    if(turn == 1){
                        turn = 2;
                    }else{
                        turn = 1;
                    }


                }

                move(sonIndex, lines, turn, 3);
                break;
                isGameEnd = isGameEndF(lines);

            }else{ /* ust siraya yerlesmik demek */
                sonIndex = sonIndex - 100;
                if(sonIndex == 32 || sonIndex == 3){ /* buyuk kaba geldi demek*/
                    break;
                }else if(lines[1][sonIndex] == 1){ /* bos kaba geldi demek*/
                    if(turn == 2){
                        turn = 1;
                    }else{
                        turn = 2;
                    }
                    break;
                }
                move(sonIndex, lines, turn, 1);
            }
                 break;
        }
    }
    return 0;
}

int main(){
    int lines[5][35] = {
        {-1,-2,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-2,-1},
        {-3,-4,-4,-4,-4,-3,-4,0,-4,-3,-4,0,-4,-3,-4,0,-4,-3,-4,0,-4,-3,-4,0,-4,-3,-4,0,-4,-3,-4,-4,-4,-4,-3},
        {-3,-4,0,0,-4,-3,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-3,-4,0,0,-4,-3},
        {-3,-4,-4,-4,-4,-3,-4,0,-4,-3,-4,0,-4,-3,-4,0,-4,-3,-4,0,-4,-3,-4,0,-4,-3,-4,0,-4,-3,-4,-4,-4,-4,-3},
        {-1,-2,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-1,-2,-2,-2,-2,-1}
    };
    int stoneCount;
    do {
        printf("Enter stone count: ");
        scanf("%d", &stoneCount);
        if (stoneCount < 1) {
            printf("Please enter a valid count!\n");
        }
    } while (stoneCount < 1);

    initializeGame(stoneCount,lines);
    printBoard(lines);
    gamePlay(lines);
    return 0;
}

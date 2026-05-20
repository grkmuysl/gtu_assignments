#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialize_game();
void print_board();
void move_player(char direction);

int class_1_1_x, class_1_1_y,class_1_2_x, class_1_2_y,class_1_3_x, class_1_3_y,class_1_4_x, class_1_4_y; /* toplanmasi gereken sayilar icin x ve y koordinatlarinin tanimlanmasi*/
int class_2_1_x, class_2_1_y, class_2_2_x, class_2_2_y, class_2_3_x, class_2_3_y ;
int positionP_x = 9, positionP_y = 9; /* P nin ilk pozisyon */
int sizeOfBoard_x ,sizeOfBoard_y;
int totalECTS = 0;
int canPassFirstWall = 0 , canPassSecondWall = 0 , isPassedFirstWall = 0 , isPassedSecondWall = 0 ; /* duvar gecisleri icin flaglar*/
char direction;
int isGameEnd = 0;

int main() {

    initialize_game();
    print_board();
    move_player(direction);
    
    return 0;
}
void initialize_game(){

    int areTheySame1 = 1 , areTheySame2 = 1;
    int minFor1 = 8 , maxFor1 = 10 , minFor2 = 6 , maxFor2 = 12; /* duvarlarin konuma gore toplanmasi gereken konumlarin max-min koordinlari */
    int range1 = maxFor1 - minFor1 + 1; /* random uretim icin range */
    int range2 = maxFor2 - minFor2 + 1; 

    srand(time(NULL));

    // min ile max arasında rastgele bir sayı uret onlari da 1 lerin konumu yap.
    while(areTheySame1 == 1){
        class_1_1_x = rand() % range1 + minFor1;
        class_1_1_y = rand() % range1 + minFor1 - 1;
        class_1_2_x = rand() % range1 + minFor1;
        class_1_2_y = rand() % range1 + minFor1 - 1;
        class_1_3_x = rand() % range1 + minFor1;
        class_1_3_y = rand() % range1 + minFor1 - 1;
        class_1_4_x = rand() % range1 + minFor1;
        class_1_4_y = rand() % range1 + minFor1 - 1;
        /* uretilen noktalar birbirine esit mi diye kontrol et.*/
        if((class_1_1_x == class_1_2_x && class_1_1_y == class_1_2_y) ||
           (class_1_1_x == class_1_3_x && class_1_1_y == class_1_3_y) ||
           (class_1_1_x == class_1_4_x && class_1_1_y == class_1_4_y) ||
           (class_1_2_x == class_1_3_x && class_1_2_y == class_1_3_y) ||
           (class_1_2_x == class_1_4_x && class_1_2_y == class_1_4_y) ||
           (class_1_3_x == class_1_4_x && class_1_3_y == class_1_4_y) ){
                areTheySame1 = 1;
        }else if((class_1_1_x == 9 && class_1_1_x == 9 ) ||  /* uretilen noktalar P'nin ilk pozisyonuna esit mi (9,9) kontrol et.*/
                 (class_1_2_x == 9 && class_1_2_x == 9 ) ||
                 (class_1_3_x == 9 && class_1_3_x == 9 ) ||
                 (class_1_4_x == 9 && class_1_4_x == 9 )){
           areTheySame1 = 1;
        }else{
            areTheySame1 = 0;
        }
    }

    while(areTheySame2 == 1){
        class_2_1_x = rand() % range2 + minFor2;
        class_2_2_x = rand() % range2 + minFor2;
        class_2_3_x = rand() % range2 + minFor2;

        // 1. sayi icin yap
        if(class_2_1_x == 6 || class_2_1_x == 12 ){ /* sayinin satir degeri 6 veya 12 ise y degeri 6 ile 12 arasinda bir dger alabilir.*/
            class_2_1_y = rand() % range2  + minFor2 - 1;
        }else{ /* sayinin satir degeri 6 veya 12 degil ise y degeri 5 ya da 11 degerlerini alabilir.*/
            int sixOrTwelve = rand() % 2; /* 0 veya 1 sayisi uret. 0 ise y degeri 6 olacak 1 ise y degeri 12 olacak.*/
            if(sixOrTwelve == 0){
                class_2_1_y = 5;
            }else{
                class_2_1_y = 11;
            }

        }
        // ikinci sayi icin yap
        if(class_2_2_x == 6 || class_2_2_x == 12 ){ /* sayinin satir degeri 6 veya 12 ise y degeri 6 ile 12 arasinda bir dger alabilir.*/
            class_2_2_y = rand() % range2  + minFor2 - 1;
        }else{ 
            int sixOrTwelve = rand() % 2; /* 0 veya 1 sayisi uret. 0 ise y degeri 5 olacak 1 ise y degeri 11 olacak.*/
            if(sixOrTwelve == 0){
                class_2_2_y = 5;
            }else{
                class_2_2_y = 11;
            }

        }
        // ucuncu sayi icin yap
        if(class_2_3_x == 6 || class_2_3_x == 12 ){ /* sayinin satir degeri 6 veya 12 ise y degeri 6 ile 12 arasinda bir dger alabilir.*/
            class_2_3_y = rand() % range2 + minFor2 - 1;
        }else{ /* sayinin satir degeri 6 veya 12 degil ise y degexri 5 ya da 11 degerlerini alabilir.*/
            int sixOrTwelve = rand() % 2; /* 0 veya 1 sayisi uret. 0 ise y degeri 5 olacak 1 ise y degeri 11 olacak.*/
            if(sixOrTwelve == 0){
                class_2_3_y = 5;
            }else{
                class_2_3_y = 11;
            }

        }

        /* uretilen noktalar birbirine esit mi diye kontrol et.*/
        if((class_2_1_x == class_2_2_x && class_2_1_y == class_2_2_y) ||
           (class_2_1_x == class_2_3_x && class_2_1_y == class_2_3_y) ||
           (class_2_2_x == class_2_3_x && class_2_2_y == class_2_3_y) ){
            areTheySame2 = 1;
        }else{
            areTheySame2 = 0;
        }
    }

    /* size of board belirle. */
    sizeOfBoard_x = 16;
    sizeOfBoard_y = 16;
}

void print_board(){
    int lineOfBoard = 1; /* o an yazdirilan satir degiskeni */
    char line1[16] = {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'}; /* line 1-2-3-4-14-15-16*/
    char line5[16] = {'.','.','.','.','#','#','#','#','#','#','#','#','#','.','.','.'}; /*line5-13 */
    char line6[16] = {'.','.','.','.','#','.','.','.','.','.','.','.','#','.','.','.'}; /* line6-12 */
    char line7[16] = {'.','.','.','.','#','.','#','#','#','#','#','.','#','.','.','.'}; /* line7-11*/
    char line8[16] = {'.','.','.','.','#','.','#','.','.','.','#','.','#','.','.','.'}; /*line 8-9-10 */

    /* print line1 to line4 */
    for(int line = 1; line <= 4 ; line++){
         for(int i = 0; i<16 ; i++){
            if(line == positionP_x && i == positionP_y - 1){ /* ilk 4 satir icin noktalarin pozisyon P'ye esitse P yazdir.*/
                printf("P");
            }else{
                printf("%c" ,line1[i]);
            }

            printf(" ");
        }
        lineOfBoard++; /* her cizimden sonra lineOfBoard 1 arttirildi*/
        printf("\n");

    }
    /* print line5 */
    for(int j = 0; j<16 ; j++){
        if((lineOfBoard == positionP_x && j == positionP_y - 1) && (line5[j] != '#')){ /* noktanin pozisyon P'nin pozisyona esitse ve duvar degilse*/
            printf("P");
        }else if((lineOfBoard == positionP_x && j == positionP_y - 1) && (line5[j] == '#')){ /* noktanin pozisyon P'nin pozisyona esitse ve duvarsa*/

        }else{
            printf("%c" ,line5[j]);
        }

        printf(" ");
    }
    lineOfBoard++;
    printf("\n");

    /* print line6 */
    for(int k = 0 ; k < 16 ; k++){
        if(lineOfBoard == positionP_x && k == positionP_y - 1){
             printf("P");
        }
        else if(class_2_1_x == lineOfBoard && class_2_1_y == k ||
           class_2_2_x == lineOfBoard && class_2_2_y == k ||
           class_2_3_x == lineOfBoard && class_2_3_y == k
           ){
            printf("2");
        }else{
                printf("%c" ,line6[k]);
        }
        printf(" ");
    }
    lineOfBoard++;
    printf("\n");

    /* print line7 */
    for(int l = 0 ; l < 16 ; l++){
        if(lineOfBoard == positionP_x && l == positionP_y - 1){
            printf("P");
        }
        else if(class_2_1_x == lineOfBoard && class_2_1_y == l ||    /*class2leri ekrana yaz */
            class_2_2_x == lineOfBoard && class_2_2_y == l ||
            class_2_3_x == lineOfBoard && class_2_3_y == l
        ){
            printf("2");
        }else{
             printf("%c" ,line7[l]);
        }
        printf(" ");
    }
    lineOfBoard++;
    printf("\n");

    /* print line8 to line10 */
    for(int line = 8; line <= 10 ; line++){
         for(int i = 0; i<16 ; i++){

            if(line == positionP_x && i == positionP_y - 1){ /* Initial P location.*/
                printf("P");
            }else if(class_1_1_x == lineOfBoard && i == class_1_1_y  || /* 1 leri ekrana yazdir. */
                     class_1_2_x == lineOfBoard && i == class_1_2_y ||
                     class_1_3_x == lineOfBoard && i == class_1_3_y ||
                     class_1_4_x == lineOfBoard && i == class_1_4_y ){

                    printf("1");
            }else{
                    if(i == 5 || i == 11){
                        if( class_2_1_x == lineOfBoard && class_2_1_y == i ||
                            class_2_2_x == lineOfBoard && class_2_2_y == i ||
                            class_2_3_x == lineOfBoard && class_2_3_y == i){
                                printf("2");
                            }else{
                                printf("%c" ,line8[i]);
                            }
                    }else{
                        printf("%c" ,line8[i]);
                    }
            }
            printf(" ");
        }
        lineOfBoard++;
        printf("\n");
    }

    /* print line11 */
    for(int i = 0 ; i < 16 ; i++){
        if(lineOfBoard == positionP_x && i == positionP_y - 1){
            printf("P"); /* p denk gelirse p'yi yazdir */
        }
        else if(class_2_1_x == lineOfBoard && class_2_1_y == i ||
            class_2_2_x == lineOfBoard && class_2_2_y == i ||
            class_2_3_x == lineOfBoard && class_2_3_y == i
        ){
            printf("2");
        }else{
            printf("%c" ,line7[i]);
        }

        printf(" ");
    }
    lineOfBoard++;
    printf("\n");

    /* print line12 */
    for(int i = 0 ; i < 16 ; i++){
        if(lineOfBoard == positionP_x && i == positionP_y - 1){
            printf("P");
        }
        else if(class_2_1_x == lineOfBoard && class_2_1_y == i ||
           class_2_2_x == lineOfBoard && class_2_2_y == i ||
           class_2_3_x == lineOfBoard && class_2_3_y == i
        ){
            printf("2");
        }else{
            printf("%c" ,line6[i]);
        }

        printf(" ");
    }
    lineOfBoard++;
    printf("\n");

    /* print line13 */
    for(int i = 0 ; i < 16 ; i++){
        if(lineOfBoard == positionP_x && i == positionP_y - 1){
            printf("P");
        }else{
            printf("%c" ,line5[i]);

        }
         printf(" ");

    }
    lineOfBoard++;
    printf("\n");

    /* print line14 to line16 */
    for(int line = 14; line <= 16 ; line++){
         for(int i = 0; i<16 ; i++){
            if(line == positionP_x && i == positionP_y - 1){ /* noktalarin pozisyon P'ye esitse P yazdir.*/
                printf("P");
            }else{
                if(line==16 && i == 15 ){
                    printf("X");
                    lineOfBoard--;
                }else{
                    printf("%c" ,line1[i]);
                }
            }
            printf(" ");
        }
        lineOfBoard++;
        printf("\n");

    }
    /* ilk calistirma icin.*/
    printf("Total ECTS: %d \n" ,totalECTS);
    printf("Enter your move: ");
    scanf("%c" , &direction);

}

void move_player(char direction){
    if(direction == 'A' || direction == 'a'){
        /* ilk duvar icin */
        if(positionP_y > 1){
            if(positionP_y == 8){ /* icteki duvarin dibindeyse ve duvari gecebilirse*/
                if(canPassFirstWall == 1 ){
                    if(isPassedFirstWall == 0){
                        positionP_y -= 2;
                        isPassedFirstWall = 1;
                    }else{
                        positionP_y -= 1;
                    }
                }else{
                    printf("\nYou don't have enough points to pass the wall! \n");
                }
            }else{

                /* ikinci duvar icin*/
                if(positionP_y == 6){ /* distaki duvarin dibindeyse ve duvari gecebilirse*/
                    if(canPassSecondWall == 1 ){
                        if(isPassedSecondWall == 0){
                            positionP_y -= 2;
                            isPassedSecondWall = 1;
                        }else{
                            positionP_y -= 1;
                        }
                    }else{
                        printf("\nYou don't have enough points to pass the wall! \n");
                    }
                }else{
                    positionP_y -= 1;
                }
            }
        }
        /* class_1 ler icin puan toplama */
            if(positionP_x == class_1_1_x && positionP_y - 1 == class_1_1_y ){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_1_x = 99; // farkli bir sayi yaptim
                class_1_1_y = 99;
            }else if(positionP_x == class_1_2_x && positionP_y - 1 == class_1_2_y){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_2_x = 99; // farkli bir sayi yaptim
                class_1_2_y = 99;
            }else if(positionP_x == class_1_3_x && positionP_y - 1 == class_1_3_y){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_3_x = 99; // farkli bir sayi yaptim
                class_1_3_y = 99;
            }else if(positionP_x == class_1_4_x && positionP_y - 1 == class_1_4_y){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_4_x = 99; // farkli bir sayi yaptim
                class_1_4_y = 99;
            }

            /* class_2 ler icin puan toplama */
            if(positionP_x == class_2_1_x && positionP_y - 1 == class_2_1_y ){
                totalECTS += 8;
                if(totalECTS == 56){
                    canPassSecondWall = 1;
                }
                class_2_1_x = 99; // farkli bir sayi yaptim
                class_2_1_y = 99;
            }else if(positionP_x == class_2_2_x && positionP_y - 1 == class_2_2_y){
                totalECTS += 8;
                if(totalECTS == 56){
                    canPassSecondWall = 1;
                }
                class_2_2_x = 99; // farkli bir sayi yaptim
                class_2_2_y = 99;
            }else if(positionP_x == class_2_3_x && positionP_y - 1 == class_2_3_y){
                totalECTS += 8;
                if(totalECTS == 56){
                    canPassSecondWall = 1;
                }
                class_2_3_x = 99; // farkli bir sayi yaptim
                class_2_3_y = 99;
            }

        print_board();

    }else if(direction == 'D' || direction == 'd'){
            if(positionP_y < 16){

                /* ilk duvar icin */
                if(positionP_y == 10){
                    if(canPassFirstWall == 1){ /*  icteki duvarin dibindeyse ve duvari gecebilirse*/

                        if(isPassedFirstWall == 0){
                             positionP_y += 2;
                            isPassedFirstWall = 1;
                        }else{
                            positionP_y += 1;
                        }

                    }else{
                        printf("\nYou don't have enough points to pass the wall! \n");
                    }
                }else{
                    /* ikinci duvar icin*/
                    if(positionP_y == 12){ /* distaki duvarin dibindeyse ve duvari gecebilirse*/
                        if(canPassSecondWall == 1 ){
                            if(isPassedSecondWall == 0){
                                positionP_y += 2;
                                isPassedSecondWall = 1;
                            }else{
                                positionP_y += 1;
                            }

                        }else{
                            printf("\nYou don't have enough points to pass the wall! \n");
                        }
                    }else{
                        positionP_y += 1;
                    }
                }
            }


            /* class_1 ler icin puan toplama */
            if(positionP_x == class_1_1_x && positionP_y - 1 == class_1_1_y ){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_1_x = 99; // farkli bir sayi yaptim
                class_1_1_y = 99;
            }else if(positionP_x == class_1_2_x && positionP_y - 1 == class_1_2_y){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_2_x = 99; // farkli bir sayi yaptim
                class_1_2_y = 99;
            }else if(positionP_x == class_1_3_x && positionP_y - 1 == class_1_3_y){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_3_x = 99; // farkli bir sayi yaptim
                class_1_3_y = 99;
            }else if(positionP_x == class_1_4_x && positionP_y - 1 == class_1_4_y){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_4_x = 99; // farkli bir sayi yaptim
                class_1_4_y = 99;
            }



            /* class_2 ler icin puan toplama */
            if(positionP_x == class_2_1_x && positionP_y - 1 == class_2_1_y ){
                totalECTS += 8;
                if(totalECTS == 56){
                    canPassSecondWall = 1;
                }
                class_2_1_x = 99; // farkli bir sayi yaptim
                class_2_1_y = 99;
            }else if(positionP_x == class_2_2_x && positionP_y - 1 == class_2_2_y){
                totalECTS += 8;
                if(totalECTS == 56){
                    canPassSecondWall = 1;
                }
                class_2_2_x = 99; // farkli bir sayi yaptim
                class_2_2_y = 99;
            }else if(positionP_x == class_2_3_x && positionP_y - 1 == class_2_3_y){
                totalECTS += 8;
                if(totalECTS == 56){
                    canPassSecondWall = 1;
                }
                class_2_3_x = 99; // farkli bir sayi yaptim
                class_2_3_y = 99;
            }

            print_board();
            if(positionP_y == 16 && positionP_x == 16){
                printf("\nYOU WON !\n");
                isGameEnd = 1;
            }
    }else if(direction == 'S' || direction == 's'){

            if(positionP_x < 16){
                /* ilk duvar icin*/
                if(positionP_x == 10 ){
                    if(canPassFirstWall == 1 ){ /*  icteki duvarin dibindeyse ve duvari gecebilirse*/
                        if(isPassedFirstWall == 0){
                            positionP_x += 2;
                            isPassedFirstWall = 1;
                        }else{
                            positionP_x += 1;
                        }
                }else{
                    printf("\nYou don't have enough points to pass the wall! \n");
                }
                }else{
                    /* ikinci duvar icin*/
                    if(positionP_x == 12){ /* distaki duvarin dibindeyse ve duvari gecebilirse*/
                        if(canPassSecondWall == 1 ){
                            if(isPassedSecondWall == 0){
                                positionP_x += 2;
                                isPassedSecondWall = 1;
                            }else{
                                positionP_x += 1;
                            }
                        }else{
                            printf("\nYou don't have enough points to pass the wall! \n");
                        }
                    }else{
                        positionP_x += 1;
                    }

                }
            }
            /* class_1 ler icin puan toplama */
            if(positionP_x == class_1_1_x && positionP_y - 1 == class_1_1_y ){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_1_x = 99; // farkli bir sayi yaptim
                class_1_1_y = 99;
            }else if(positionP_x == class_1_2_x && positionP_y - 1 == class_1_2_y){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_2_x = 99; // farkli bir sayi yaptim
                class_1_2_y = 99;
            }else if(positionP_x == class_1_3_x && positionP_y - 1 == class_1_3_y){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_3_x = 99; // farkli bir sayi yaptim
                class_1_3_y = 99;
            }else if(positionP_x == class_1_4_x && positionP_y - 1 == class_1_4_y){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_4_x = 99; // farkli bir sayi yaptim
                class_1_4_y = 99;
            }


            /* class_2 ler icin puan toplama */
            if(positionP_x == class_2_1_x && positionP_y - 1 == class_2_1_y ){
                totalECTS += 8;
                if(totalECTS == 56){
                    canPassSecondWall = 1;
                }
                class_2_1_x = 99; // farkli bir sayi yaptim
                class_2_1_y = 99;
            }else if(positionP_x == class_2_2_x && positionP_y - 1 == class_2_2_y){
                totalECTS += 8;
                if(totalECTS == 56){
                    canPassSecondWall = 1;
                }
                class_2_2_x = 99; // farkli bir sayi yaptim
                class_2_2_y = 99;
            }else if(positionP_x == class_2_3_x && positionP_y - 1 == class_2_3_y){
                totalECTS += 8;
                if(totalECTS == 56){
                    canPassSecondWall = 1;
                }
                class_2_3_x = 99; // farkli bir sayi yaptim
                class_2_3_y = 99;
            }

            print_board();

            /*oyun bitti mi kontrol */
            if(positionP_y == 16 && positionP_x == 16){
                printf("\nYOU WON !\n");
                isGameEnd = 1;
                return;
            }
    }else if(direction == 'W' || direction == 'w'){
            if(positionP_x > 1){
                /* ilk duvar icin */
                if(positionP_x == 8 ){
                    if(canPassFirstWall == 1){ /*  icteki duvarin dibindeyse ve duvari gecebilirse*/
                        if(isPassedFirstWall == 0){
                            positionP_x -= 2;
                            isPassedFirstWall = 1;
                        }else{
                            positionP_x -= 1;
                        }
                    }else{
                        printf("\nYou don't have enough points to pass the wall! \n");
                    }
                }else{
                     /* ikinci duvar icin*/
                    if(positionP_x == 6){ /* distaki duvarin dibindeyse ve duvari gecebilirse*/
                        if(canPassSecondWall == 1 ){
                            if(isPassedSecondWall == 0){
                                positionP_x -= 2;
                                isPassedSecondWall = 1;
                            }else{
                                positionP_x -= 1;
                            }

                        }else{
                            printf("\nYou don't have enough points to pass the wall! \n");
                        }
                    }else{
                        positionP_x -= 1;
                    }



                }
            }
            /* class_1 ler icin puan toplama */
            if(positionP_x == class_1_1_x && positionP_y - 1 == class_1_1_y ){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_1_x = 99; // farkli bir sayi yaptim
                class_1_1_y = 99;
            }else if(positionP_x == class_1_2_x && positionP_y - 1 == class_1_2_y){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_2_x = 99; // farkli bir sayi yaptim
                class_1_2_y = 99;
            }else if(positionP_x == class_1_3_x && positionP_y - 1 == class_1_3_y){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_3_x = 99; // farkli bir sayi yaptim
                class_1_3_y = 99;
            }else if(positionP_x == class_1_4_x && positionP_y - 1 == class_1_4_y){
                totalECTS += 8;
                if(totalECTS == 32){
                    canPassFirstWall = 1;
                }
                class_1_4_x = 99; // farkli bir sayi yaptim
                class_1_4_y = 99;
            }


            /* class_2 ler icin puan toplama */
            if(positionP_x == class_2_1_x && positionP_y - 1 == class_2_1_y ){
                totalECTS += 8;
                if(totalECTS == 56){
                    canPassSecondWall = 1;
                }
                class_2_1_x = 99; // farkli bir sayi yaptim
                class_2_1_y = 99;
            }else if(positionP_x == class_2_2_x && positionP_y - 1 == class_2_2_y){
                totalECTS += 8;
                if(totalECTS == 56){
                    canPassSecondWall = 1;
                }
                class_2_2_x = 99; // farkli bir sayi yaptim
                class_2_2_y = 99;
            }else if(positionP_x == class_2_3_x && positionP_y - 1 == class_2_3_y){
                totalECTS += 8;
                if(totalECTS == 56){
                    canPassSecondWall = 1;
                }
                class_2_3_x = 99; // farkli bir sayi yaptim
                class_2_3_y = 99;
            }
            print_board();
    }else{
        printf("Enter a valid direction. \n");
    }

    while(isGameEnd == 0){
        printf("Enter your move: ");
        scanf("%c" , &direction);
        move_player(direction);
    }

}




#include <stdio.h>


typedef struct Forest {
    char map[100][100];
    int width; /* size of map*/
    int height;
    int flower_x[100]; /* coordinates of rare flower */
    int flower_y[100];
} Forest;

typedef struct Botanist {
    int coord_x; /* coordinates of botanist */
    int coord_y;
    int number_of_bottle; /* number of bottle */
} Botanist;

void display_forest(Forest *forest, Botanist *botanist, int collected_flowers){ /* ormani ekrana yazdir. */
    int i,j ;

    for(i = 0; i < forest->height ;i++){
        for(j = 0; j < 2*(forest->width) - 1; j++){ /* virguller de birer karakter olarak sayiliyor ama index e dahil edilmiyor */

            if(i == botanist->coord_y && j == botanist->coord_x){ /* botanistin koordinatlari ise B yazdir */
                printf("B");
            }else{
                printf("%c" , forest->map[i][j]);  /* botanistin koordinatlari degil ise array'i yazdir */
            }
        }
        printf("\n");
    }
    printf("\nCollected Flowers: %d Number of Bottles: %d\n" , collected_flowers, botanist->number_of_bottle );

}


void search(Forest *forest, Botanist *botanist, int collected_flowers, int initial_flowers_count){

    int i,j;
    if((collected_flowers == initial_flowers_count) || botanist->number_of_bottle == 0){ /* oyun bitti mi kontrol et */
        printf("YOU WON THE GAME! \n");

    }else{
        int new_coord_x, new_coord_y ;
        char moveInput;
        printf("\nEnter your move! (Left: a, Right: d, Up: w, Down: s, EXIT: e):");
        scanf(" %c", &moveInput);

        /* botanisti hareket ettir. */
        switch(moveInput){
            case 'd':
            /* gitmek istenilen noktanin koordinatlarini gecici olarak kaydet.*/
                new_coord_x = botanist->coord_x + 2; /* virgullerden dolayi indexi 2 artir.*/
                new_coord_y = botanist->coord_y;

                if(forest->map[new_coord_y][new_coord_x] == 'X'){ /* gidilmek istenilen noktada cicek varsa bu blok calisir */
                    /* cicek toplama islemi */
                    botanist->number_of_bottle -= 1;
                    collected_flowers += 1;
                    /* cicek toplanirsa yerine bosluk yazdir */
                    forest->map[new_coord_y][new_coord_x] = ' ';
                    botanist->coord_x += 2;
                    printf("\nBotanist: I've found it!\n\n");
                    display_forest(forest,botanist,collected_flowers);
                    search(forest,botanist, collected_flowers, initial_flowers_count);

                }else{ /* cicek degilse bu bloka girer */
                    if(forest->map[new_coord_y][new_coord_x] == ' '){ /* bosluk ise */
                        botanist->coord_x += 2; /* gidilebiliyorsa koordinatlar guncellenir */
                        printf("\n");
                        display_forest(forest,botanist,collected_flowers);
                        search(forest,botanist, collected_flowers, initial_flowers_count);
                    }else{ /* eger agac ise uyari yazdir ve ilerleme */
                        printf("You cannot move in this direction!\n");
                        display_forest(forest,botanist,collected_flowers);
                        search(forest,botanist, collected_flowers, initial_flowers_count);
                    }
                }
                break;
            case 'a':
                new_coord_x = botanist->coord_x - 2;
                new_coord_y = botanist->coord_y;

                if(forest->map[new_coord_y][new_coord_x] == 'X'){

                    /* cicek toplama islemi */
                    botanist->number_of_bottle -= 1;
                    collected_flowers += 1;
                    forest->map[new_coord_y][new_coord_x] = ' ';
                    botanist->coord_x -= 2;
                    printf("\nBotanist: I've found it!\n\n");
                    display_forest(forest,botanist,collected_flowers);
                    search(forest,botanist, collected_flowers, initial_flowers_count);

                }else{
                    if(forest->map[new_coord_y][new_coord_x] == ' '){
                       botanist->coord_x -= 2;
                        printf("\n");
                        display_forest(forest,botanist,collected_flowers);
                        search(forest,botanist, collected_flowers, initial_flowers_count);
                    }else{
                        printf("You cannot move in this direction!\n");

                        search(forest,botanist, collected_flowers, initial_flowers_count);
                    }
                }
                break;
            case 's':
                new_coord_x = botanist->coord_x;
                new_coord_y = botanist->coord_y + 1;

                 if(forest->map[new_coord_y][new_coord_x] == 'X'){
                    /* cicek toplama islemi */

                    botanist->number_of_bottle -= 1;
                    collected_flowers += 1;
                    forest->map[new_coord_y][new_coord_x] = ' ';
                    botanist->coord_y += 1;
                    printf("\nBotanist: I've found it!\n\n");
                    display_forest(forest,botanist,collected_flowers);
                    search(forest,botanist, collected_flowers, initial_flowers_count);

                }else{
                    if(forest->map[new_coord_y][new_coord_x] == ' '){ /* yuruyebilirse */
                        botanist->coord_y += 1;
                        printf("\n");
                        display_forest(forest,botanist,collected_flowers);
                        search(forest,botanist, collected_flowers, initial_flowers_count);
                    }else{
                        printf("You cannot move in this direction!\n");

                        search(forest,botanist, collected_flowers, initial_flowers_count);
                    }

                }
                break;
            case 'w':
                new_coord_x = botanist->coord_x;
                new_coord_y = botanist->coord_y - 1;

                if(forest->map[new_coord_y][new_coord_x] == 'X'){
                    /* cicek toplama islemi */
                    botanist->number_of_bottle -= 1;
                    collected_flowers += 1;
                    forest->map[new_coord_y][new_coord_x] = ' ';
                    botanist->coord_y -= 1;
                    printf("\nBotanist: I've found it!\n\n");
                    display_forest(forest,botanist,collected_flowers);
                    search(forest,botanist, collected_flowers, initial_flowers_count);

                }else{
                    if(forest->map[new_coord_y][new_coord_x] == ' '){
                    botanist->coord_y -= 1;
                    printf("\n");
                    display_forest(forest,botanist,collected_flowers);
                    search(forest,botanist, collected_flowers, initial_flowers_count);
                    }else{
                        printf("You cannot move in this direction!\n");
                        search(forest,botanist, collected_flowers, initial_flowers_count);
                    }
                }
                break;

            case 'e':
                printf("Exiting the program...");
                break;
            default:
                printf("Please enter a valid input! \n");
                search(forest,botanist, collected_flowers, initial_flowers_count);
                break;
        }

    }
    /* mapin son halini dosyaya yazma islemi */
    FILE* lastTxt = fopen("//home//gorkem//Desktop//last.txt" , "w");
    fprintf(lastTxt,"%d %d\n" , forest->width, forest->height);
    fprintf(lastTxt,"%d %d %d\n" , botanist->coord_y, botanist->coord_x  / 2, botanist->number_of_bottle);

    for(i = 0; i < forest->height ; i++){
        for(j = 0; j < 2*(forest->width) - 1 ; j++){
            if( i == botanist->coord_y && j == botanist->coord_x){
                fprintf(lastTxt,"B"); /* botanistin koordinatlarinda ekrana B yazdir */
            }else{
                fprintf(lastTxt,"%c" , forest->map[i][j]);
            }

        }
            fprintf(lastTxt,"\n");
    }

        fclose(lastTxt);
}


void init_game(Forest *forest, Botanist *botanist) {
    FILE *dosya = fopen("//home//gorkem//Desktop//init.txt", "r"); /* open and read the file */

    if (dosya == NULL) {
        printf("dosya acilamadi.");
        return;
    }
    int sayi1, sayi2,sayi3, cicek_sayisi = 0;

    /* ilk satirdaki verileri oku ve kaydet */
    fscanf(dosya, "%d,%d", &sayi1, &sayi2);
    forest->width = sayi1;
    forest->height = sayi2;

    /* ikinci satirdaki verileri oku ve kaydet */
    fscanf(dosya, "%d,%d,%d", &sayi1, &sayi2, &sayi3);
    botanist->coord_y = sayi1;
    botanist->coord_x = sayi2;
    botanist->number_of_bottle = sayi3;

    int satir_sayisi = -1, current_column = 0 ; /* satir sayisini -1 den baslatmamin sebebi dosyanin 3. satirindan itibaren mapi yazdiriyorum */
    char karakter;
    while ((karakter = fgetc(dosya)) != EOF) { /* kaldigim son yer \n oldugu icin orayi atlayip okumaya devam ediyor */
        if (satir_sayisi >= 0) { /* 1. satirdan itibaren okuma islemi */

            if(karakter == 'X'){ /* ciceklerin koordinatlarini kaydet. */
                forest->flower_x[cicek_sayisi] = current_column;
                forest->flower_y[cicek_sayisi] = satir_sayisi;
                cicek_sayisi++;
            }
            if(karakter == 'B'){ /* botanistin koordinatlarini kaydet. */
                botanist->coord_x = current_column;
                botanist->coord_y = satir_sayisi;
                forest->map[satir_sayisi][current_column] = ' ';
            }else{
                forest->map[satir_sayisi][current_column] = karakter;
            }

            current_column++;
        }
        if (karakter == '\n') {
            satir_sayisi++;
            current_column = 0;
        }
    }
    fclose(dosya);

    /* collected_flowers 0 dan oyunu baslat */
    display_forest(forest,botanist,0);
    search(forest,botanist, 0, cicek_sayisi);
}


int main() {
    Forest forest;
    Botanist botanist;
    init_game(&forest, &botanist);

    return 0;
}

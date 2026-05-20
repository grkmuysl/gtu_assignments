#include <stdio.h>
#include <string.h>

#define MAX_ROW 5
#define MAX_COLUMN 34

void search_p1(char stars[][MAX_COLUMN], int num_rows, int matches[][2], int* num_matches) {
    char row_pattern[] = "***++++***++++***";
    int i, j, k;
    int pattern_len = strlen(row_pattern);
    *num_matches = 0;
    for (i = 0; i < num_rows; i++) {
        for (j = 0; j < MAX_COLUMN; j++) {
            if (stars[i][j] == row_pattern[0]) { /* Desenin ilk karakteri eslesti */
                int isMatch = 1;
                for (k = 1; k < pattern_len; k++) { /* ardindan soldan saga dogru desenin kalani eslesiyor mu kontrol et.*/
                    if (stars[i][j + k] != row_pattern[k]) {
                        isMatch = 0;                 /* eslesme olmaz ise isMatch degerini 0 yap */
                        break;
                    }
                }
                if (isMatch) { /* eslesme tamamen saglaniyorsa index degerlerini kaydet + num_matches degiskenini bir arttir. */
                    matches[*num_matches][0] = i + 1;
                    matches[*num_matches][1] = j + 1;
                    (*num_matches)++;
                }
            }
        }
    }
    int l;
    for(l = 0; l < *num_matches; l++){ /* eslesen degerleri eslesme sayisi kadar ekrana yazdir */
        printf("P1 @ (%d,%d)\n", matches[l][0], matches[l][1]);
    }
}
void search_p2(char stars[][MAX_COLUMN], int num_rows, int matches[][2], int* num_matches) {
    char row_pattern[] = "+*+*+";
    int i, j, k ;
    int pattern_len = strlen(row_pattern);
    *num_matches = 0;
    for (i = 0; i < num_rows; i++) {
        for (j = 0; j < MAX_COLUMN; j++) {
            if (stars[i][j] == row_pattern[0]) { /* Desenin ilk karakteri eslesti */
                int isMatch = 1;
                for (k = 1; k < pattern_len; k++) {
                    if (stars[i + k][j] != row_pattern[k]) { /* ardindan yukaridan asagiya dogru eslesme saglaniyor mu kontol et */
                        isMatch = 0;
                        break;
                    }
                }
                if (isMatch) {
                    matches[*num_matches][0] = i + 1;
                    matches[*num_matches][1] = j + 1;
                    (*num_matches)++;
                }
            }
        }
    }
    int l;
    for(l = 0; l < *num_matches; l++){ /* eslesenleri yazdirma islemi */
        printf("P2 @ (%d,%d)\n", matches[l][0], matches[l][1]);
    }
}
void search_p3(char stars[][MAX_COLUMN], int num_rows, int matches[][2], int* num_matches){
    char row_pattern[] = "+**+++****+++**+";
    int i, j, k ;
    int pattern_len = strlen(row_pattern);
    *num_matches = 0;
    for (i = 0; i < num_rows; i++) {
        for (j = 0; j < MAX_COLUMN; j++) {
            if (stars[i][j] == row_pattern[0]) { /* Desenin ilk karakteri eslesti */
                int isMatch = 1;
                for (k = 1; k < pattern_len; k++) {
                    if (stars[i + k][j + k] != row_pattern[k]) { /* soldan saga ve yukaridan asagiya dogru satir ve sutun degerleri birer arttırılarak capraz eslesmeyi kontrol et*/
                        isMatch = 0;
                        break;
                    }
                }
                if (isMatch) {
                    matches[*num_matches][0] = i + 1;
                    matches[*num_matches][1] = j + 1;
                    (*num_matches)++;
                }
            }
        }
    }
    int l;
    for(l = 0; l < *num_matches; l++){
        printf("P3 @ (%d,%d)\n", matches[l][0], matches[l][1]);
    }
}
void read_file(FILE* myFile) {  /* dosyayi okuyup verileri starts array'ine kaydet */
    char stars[MAX_ROW][MAX_COLUMN], c; 
    int row = 0, column = 0;

    while ((c = fgetc(myFile)) != EOF) {
        if (c == '\n') {
            row++;
            column = 0;
        } else {
            stars[row][column] = c;
            column++;
        }
    }
    int num_matches , matches[num_matches + 1][2]; /* fonksiyonlari calistir */
    search_p1(stars, MAX_ROW, matches, &num_matches);
    search_p2(stars, MAX_ROW, matches, &num_matches);
    search_p3(stars, MAX_ROW, matches, &num_matches);
}

int main() {
    FILE* myFile = fopen("//home//gorkem//Desktop//input2.txt", "r");
    if (myFile == NULL) {
        printf("Dosya acilamadi!\n");
        return 0;
    }
    read_file(myFile);
    fclose(myFile);
    return 0;
}

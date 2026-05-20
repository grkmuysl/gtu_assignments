#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    const char *face;
    const char *suit;
} Card;

void generate_cards(Card all_cards[52] , Card card , int type){ /* tum kartlari uret */

    int i , j; /* j eklenecek kartin all_cards icerisindeki indexi belirtir */

    /* type 'e gore suit i belirle */
    if(type == 0){
        card.suit = "Hearts";
        j = 0;
    }else if(type == 1){
        card.suit = "Diamonds";
        j = 13;
    }else if(type == 2){
        card.suit = "Clubs";
        j = 26;
    }else if(type == 3){
        card.suit = "Spades";
        j = 39;
    }

    for(i = 0; i < 13; i++){ /* kart numalarina gore face'i belirleyip card degiskenine atiyorum */
        switch (i){
            case 0:
                card.face = "Ace";
                break;
            case 1:
                card.face = "Deuce";
                break;
            case 2:
                card.face = "Three";
                break;
            case 3:
                card.face = "Four";
                break;
            case 4:
                card.face = "Five";
                break;
            case 5:
                card.face = "Six";
                break;
            case 6:
                card.face = "Seven";
                break;
            case 7:
                card.face = "Eight";
                break;
            case 8:
                card.face = "Nine";
                break;
            case 9:
                card.face = "Ten";
                break;
            case 10:
                card.face = "Jack";
                break;
            case 11:
                card.face = "Queen";
                break;
            case 12:
                card.face = "King";
                break;
        }
        all_cards[j] = card; /* uretilen karti desteye ekledim index'i 1 arttirdim ki sonraki kartlar ayni yere eklenmesin */
        j++; /* sirasiyla once hearts-diamonds-clubs-spades kartlari 13er tane olmak uzere all_cards icerisine eklendi */
    }
}

int is_number_in_array(int all_numbers[], int length, int number){ /* gonderilen sayinin array icerisinde olup olmadigini kontrol eder */
    
    int i;
    for(i = 0; i < length; i++){
        if(all_numbers[i] == number){
            return 1; /* sayi array icerisinde ise 1 dondur */
        }
    }
    return 0; /* sayi array icerisinde degil ise 0 dondur */
}

void generate_random_indexes(int random_indexes_of_cards[52]){ /* karistirma islemi icin rastgele indeks uretiyorum */
    srand(time(0));
    int random_number;
    int count = 0; /* array icerisine eklenen toplam kart sayisi */

    while(count < 52){ /* uretilen index sayisi 52 den dusuk oldugu surece uretmeye devam et */
        random_number = rand() % 52;

        if(is_number_in_array(random_indexes_of_cards, count, random_number) == 0){ /* random uretilen sayi array icerisinde varsa tekrar uret */
            random_indexes_of_cards[count] = random_number;
            count++;
        }
    }


}

int main() {
    Card card;
    Card all_cards[52] , shuffled_deck[52];

    /* tum kartlari sirayla uretip all_cards destesine ekliyorum */
    /* generate Hearts */
    generate_cards(all_cards , card , 0);

    /* generate Diamonds */
    generate_cards(all_cards , card , 1);

    /* generate Clubs */
    generate_cards(all_cards , card , 2);

    /* generate Spades */
    generate_cards(all_cards , card , 3);

    int random_indexes_of_cards[52] , i; /* tum kartlarin karisik indexlerini tutan array */

    /* tum kartlarin indexlerini rastgele uretip random_indexes_of_cards array'ine kaydediyorum. */
    generate_random_indexes(random_indexes_of_cards);

    for(i = 0; i < 52; i++){
        /* all_cards array'inden elemanlari sirayla alip rastgele siralanmis indekslere gore shuffled_deck array'ine diziyorum */
        int index_of_card = random_indexes_of_cards[i];
        shuffled_deck[index_of_card] = all_cards[i];
    }

    for(i = 0; i < 26; i++){ /* istenilen formatta ekrana yazdir */
        printf("%s of %s %15s of %s \n" , shuffled_deck[i].suit , shuffled_deck[i].face , shuffled_deck[i + 26].suit , shuffled_deck[i + 26].face);
    }
    return 0;
}

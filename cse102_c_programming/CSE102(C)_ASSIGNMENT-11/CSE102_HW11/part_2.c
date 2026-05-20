#include <stdio.h>
#include <string.h>

typedef struct {
    char* name;
    char citiesServed[4]; /* 3 tane sehir + 1 tane de null karakter icin */
} Hospital;

int is_covered(char cities[6], char covered_cities[6]) { /* secilen sehirler tum sehirleri kapsiyor mu kontrol et */
    int is_A_in = 0, is_B_in = 0, is_C_in = 0, is_D_in = 0, is_E_in = 0, is_F_in = 0 , i;
    for (i = 0; i < 6; i++) {
        if (covered_cities[i] == cities[0]) { /* kapsanan sehirler icin 1 yap */
            is_A_in = 1;
        } else if (covered_cities[i] == cities[1]) {
            is_B_in = 1;
        } else if (covered_cities[i] == cities[2]) {
            is_C_in = 1;
        } else if (covered_cities[i] == cities[3]) {
            is_D_in = 1;
        } else if (covered_cities[i] == cities[4]) {
            is_E_in = 1;
        } else if (covered_cities[i] == cities[5]) {
            is_F_in = 1;
        }
    }
    return (is_A_in && is_B_in && is_C_in && is_D_in && is_E_in && is_F_in); /* bir tanesi dahi 0 ise tum sehirler kapsanmiyor demektir o yuzden 0 doner */
}

int find_hospitals(int indexes_of_selected_hospitals[], int initial_index, int number_of_selected_hosp, int max_hospitals, char cities[6], char locations[4][3] , Hospital hospitals[4]) {

    if (number_of_selected_hosp == max_hospitals) { /* max_hospitals kadar hastane secildiyse covered durumunu kontrol et */
        char covered_cities[6] = {0};
        int covered_count = 0 , i;

        for (i = 0; i < max_hospitals; i++) {
            int index = indexes_of_selected_hospitals[i] , j;
            for (j = 0; j < 3; j++) { /* her bir hastane maximum 3 sehir kapsar */
                if (strchr(covered_cities, locations[index][j]) == NULL ) { /* eklenecek sehir onceden eklenmisse tekrar ekleme */
                    covered_cities[covered_count++] = locations[index][j];
                }
            }
        }

        if (is_covered(cities, covered_cities)) { /* tum sehirler kapsaniyor ise donguye gir */
            printf("\nYes, can offer health care to all!\n\n");
		
            for (i = 0; i < max_hospitals; i++) {
                printf("%s \n", hospitals[indexes_of_selected_hospitals[i]].name );
                printf("Hospital locations: %s\n" , hospitals[indexes_of_selected_hospitals[i]].citiesServed);
            }

            return 1;
        }
        return 0;

    } else { /* max hospital sayisina ulasilmamis ise indexi ve secilen hastane sayisini bir arttir */
    	int i;
        for (i = initial_index; i < 4; i++) {
            indexes_of_selected_hospitals[number_of_selected_hosp] = i;
            if (find_hospitals(indexes_of_selected_hospitals, i + 1, number_of_selected_hosp + 1, max_hospitals, cities, locations , hospitals)) { /* tekrarlanmamasi icin if bloguna aliyorum */
                return 1;
            }
        }
    }
    return 0;
}

int main() {

    Hospital hospitals[] = { /* hastaneleri tanimla */
        { "Hospital - 1", "ABC" },
        { "Hospital - 2", "ACD" },
        { "Hospital - 3", "BF" },
        { "Hospital - 4", "CEF" }
    };

    char cities[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
    
    /* locations[0] 1. hastanenin kapsadigi alani, locations[0] 2. hastanenin kapsadigi alani ... temsil ediyor */ 
    char locations[4][3] = {{'A', 'B', 'C'}, {'A', 'C', 'D'}, {'B', 'F', '\0'}, {'C', 'E', 'F'}}; 

    int max_hospitals;
    printf("Enter the maximum number of hospitals that can be constructed(1-4): ");
    scanf("%d", &max_hospitals);

    if (max_hospitals > 0 && max_hospitals < 5) { /* girilen hastane sayisini kontrol et */
        int indexes_of_selected_hospitals[4] = {0}; /* basta hic hastane secilmemis */
        if (!find_hospitals(indexes_of_selected_hospitals, 0, 0, max_hospitals, cities, locations , hospitals)) {
            printf("No, some cities are not covered.\n");
        }
    }else{
        printf("Please enter a valid number!");
    }

    return 0;
}

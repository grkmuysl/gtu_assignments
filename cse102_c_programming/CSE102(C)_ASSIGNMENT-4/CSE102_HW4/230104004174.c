#include <stdio.h>
int midtermAverage , finalAverage;
char first_initial(FILE *id_fp , int id) {
    char karakter;
    int okunan_sayi = 0;

     while ((karakter = fgetc(id_fp)) != EOF) {

       while (fscanf(id_fp, "%d;", &okunan_sayi) == 1) {
            if(okunan_sayi == id){
                        karakter = fgetc(id_fp);
            }
        }
    }
    return karakter;
}

char last_initial(FILE *id_fp , int id) {
    char karakter;
    int okunan_sayi = 0 , okunan_noktali_virgul = 0;

     while ((karakter = fgetc(id_fp)) != EOF) {

        while (fscanf(id_fp, "%d;", &okunan_sayi) == 1) {
            if(okunan_sayi == id){

                        while((karakter = fgetc(id_fp)) != EOF && okunan_noktali_virgul < 1 ){

                            if(karakter == ';'){
                                okunan_noktali_virgul++;
                            }
                            if(okunan_noktali_virgul > 0){ /* adin sonundaki noktali virgul gectikten sonra*/
                                    karakter = fgetc(id_fp);
                            }
                        }
            }
        }
    }
    return karakter;
}

void calculate_average_midterm(FILE *id_fp  ){
    int okunan_sayi = 0;
    int student_id,not1,not2,not3,not4;
    int total_midterms = 0  , number_of_students = 0 , average_of_midterms = 0;

    /* average midterm */
    while (fscanf(id_fp, "%d;%d;%d;%d;%d\n", &student_id, &not1, &not2, &not3, &not4) == 5) {

            int average_of_midterms = (not1 + not2) / 2;
            total_midterms += average_of_midterms;
            number_of_students++;
    }
    while(fscanf(id_fp, "%d;%d;%d;%d\n", &student_id, &not1, &not2, &not3) == 4) {
            total_midterms += not1;
            number_of_students++;
    }
    average_of_midterms = (total_midterms / number_of_students);
    midtermAverage = average_of_midterms;


}
void calculate_average_final(FILE *id_fp  ){
    int okunan_sayi = 0;
    int student_id,not1,not2,not3,not4;
    int total_final = 0  , number_of_students = 0 , average_of_final = 0;

    /* average final */
    while (fscanf(id_fp, "%d;%d;%d;%d;%d\n", &student_id, &not1, &not2, &not3, &not4) == 5) {

            total_final += not3;
            number_of_students++;
    }
    while(fscanf(id_fp, "%d;%d;%d;%d\n", &student_id, &not1, &not2, &not3) == 4) {
            total_final += not1;
            number_of_students++;
    }
    average_of_final = (total_final / number_of_students);
    finalAverage = average_of_final;

}

int average_grade(FILE *id_fp , int id) {
    char karakter;
    int okunan_sayi = 0;
    int student_id,not1,not2,not3,not4;
    int GPA = 0;
    /* return gpa*/
    while (fscanf(id_fp, "%d;%d;%d;%d;%d\n", &student_id, &not1, &not2, &not3, &not4) == 5) {

            int midterm = (not1+not2 / 2);
            if(student_id == id){
                if(midterm < 40 && midterm < midtermAverage && (not3 < 40 && not3 < finalAverage)){
                    GPA = 1;
                }else if(midterm > 40 && midterm < midtermAverage && (not3 > 40 && not3 < finalAverage)){
                    GPA = 2.5;
                }else if(midterm > 40 && midterm < midtermAverage && (not3 > 40 && not3 > finalAverage)){
                    GPA = 3;
                }else if(midterm > 40 && midterm > midtermAverage && (not3 < 90 && not3 > finalAverage)){
                    GPA = 3.5;
                }else if(midterm > 90  && (not3 < 90)){
                    GPA = 4;
                }
            }
    }

    while(fscanf(id_fp, "%d;%d;%d;%d\n", &student_id, &not1, &not2, &not3) == 4) {

            int midterm = not1;
            if(student_id == id){
                if(midterm < 40 && midterm < midtermAverage && (not2 < 40 && not2 < finalAverage)){
                    GPA = 1;
                }else if(midterm > 40 && midterm < midtermAverage && (not2 > 40 && not2 < finalAverage)){
                    GPA = 2.5;
                }else if(midterm > 40 && midterm < midtermAverage && (not2 > 40 && not2 > finalAverage)){
                    GPA = 3;
                }else if(midterm > 40 && midterm > midtermAverage && (not2 < 90 && not2 > finalAverage)){
                    GPA = 3.5;
                }else if(midterm > 90  && (not2 < 90)){
                    GPA = 4;
                }
            }
    }
    printf("Student's GPA is: %d \n" , GPA);
    return GPA;
}

int get_id_fi(FILE * id_fp, char first_initial){
    FILE *students1;
    students1 = fopen("//home//gorkem//Desktop//students1.txt", "w");

    char karakter;
    int okunan_sayi = 0;

    printf("List of students whose names start with %c: \n", first_initial);
    while ((karakter = fgetc(id_fp)) != EOF) {
       while (fscanf(id_fp, "%d;", &okunan_sayi) == 1) {
            karakter = fgetc(id_fp);
            if(karakter == first_initial){
                fprintf(students1, "%d\n" , okunan_sayi); /* birden fazla ogrenciyi return edemedigim icin bu sekilde printledim.*/
            }
        }
    }
    fclose(students1);
    /* dosya okuma */
    FILE *students1_1;
    students1_1 = fopen("//home//gorkem//Desktop//students1.txt", "r");
    if (students1_1 == NULL) {
        printf("Dosya acilamadi.\n");
        return 1;
    }
    int isFileEmpty = fgetc(students1_1);
    fclose(students1_1);
    students1_1 = fopen("//home//gorkem//Desktop//students1.txt", "r"); /* acip kapatmamin sebebi bos olup olmadigini kontrol etmek.*/
    char ch;
    if (isFileEmpty == EOF) {
        printf("There is no result.\n");
    }else{
        while ((ch = fgetc(students1_1)) != EOF) {
        printf("%c", ch);
        }
    }
    fclose(students1_1);
    return 0;
}

int get_id_li(FILE *id_fp, char last_initial) {

    FILE *students2;
    students2 = fopen("//home//gorkem//Desktop//students2.txt", "w");

    char karakter;
    int okunan_sayi = 0;

    printf("List of students whose last-name start with %c: \n", last_initial);
    while ((karakter = fgetc(id_fp)) != EOF) {
       while (fscanf(id_fp, "%d;", &okunan_sayi) == 1) {

            while(karakter != ';'){ /* soyismin oncesindeki noktali virgule kadar gel */
                karakter = fgetc(id_fp);

            } /* soyismin ilk harfini oku*/
            karakter = fgetc(id_fp);
            if(karakter == last_initial){
                fprintf(students2, "%d\n" , okunan_sayi);
            }
        }
    }
    fclose(students2);
    /* dosya okuma */
    FILE *students1_2;
    students1_2 = fopen("//home//gorkem//Desktop//students2.txt", "r");
    if (students1_2 == NULL) {
        printf("Dosya acilamadi.\n");
        return 1;
    }
    int isFileEmpty = fgetc(students1_2);
    fclose(students1_2);
    students1_2 = fopen("//home//gorkem//Desktop//students2.txt", "r");
    char ch;
    if (isFileEmpty == EOF) {
        printf("There is no result.\n");
    }else{
        while ((ch = fgetc(students1_2)) != EOF) {
        printf("%c", ch);
        }
    }
    fclose(students1_2);
    return 0;

}

void number_of_classes(FILE *id_fp, int user_id){
    int id,classId,department,not3,not4;

     while (fscanf(id_fp, "%d;%d;%d;%d;%d\n", &id, &classId, &department, &not3, &not4) == 5) {

    }
    while(fscanf(id_fp, "%d;%d;%d;%d\n", &id, &classId, &department, &not3) == 4) {

    }
    while(fscanf(id_fp, "%d;%d;%d\n", &id, &classId, &department) == 3) {
        if(user_id == id){
            printf("# of the classes for instructor: %d \n" ,classId );
        }
    }
}
void print_course_id(FILE *id_fp, int user_id){

    int id,classId,department,not3,not4;
    while (fscanf(id_fp, "%d;%d;%d;%d;%d\n", &id, &classId, &department, &not3, &not4) == 5) {
        if(user_id == id){
            printf("Course ID is : %d \n" ,not4 );
        }
    }
    while(fscanf(id_fp, "%d;%d;%d;%d\n", &id, &classId, &department, &not3) == 4) {
            if(user_id == id){
                printf("Course ID is : %d \n" ,not3 );
            }
    }
}

void print_average_grade_of_course(FILE *id_fp, int course_id){
    int id,midterm1,midterm2,final_n,courseId , totalGPA = 0 , totalStudent = 0;

     while (fscanf(id_fp, "%d;%d;%d;%d;%d\n", &id, &midterm1, &midterm2, &final_n, &courseId) == 5) {
            totalGPA += average_grade(id_fp, id);
            totalStudent++;
    }
    while(fscanf(id_fp, "%d;%d;%d;%d\n", &id, &midterm1, &final_n, &courseId) == 4) {
            totalGPA += average_grade(id_fp, id);
            totalStudent++;
    }
    int averageGPA = totalGPA / totalStudent;
    printf("Average GPA for class %d : %d" ,course_id , averageGPA );
}

int main() {
    FILE *dosya;
    FILE *dosya2;
    char option;
    int isCont = 1;
    dosya = fopen("//home//gorkem//Desktop//first 1.txt", "r"); /* okuma şeklinde aç*/

    dosya2 = fopen("//home//gorkem//Desktop//second 1.txt", "r"); /* okuma şeklinde aç*/

    if (dosya == NULL) {
        printf("Dosya bulunamadi.\n");
        return 1;
    }
    if (dosya2 == NULL) {
        printf("Dosya bulunamadi.\n");
        return 1;
    }
    /* average final ve midterm i bulup global degiskeni degistirdim*/
    calculate_average_midterm(dosya);
    fclose(dosya);
    dosya = fopen("//home//gorkem//Desktop//first 1.txt", "r"); /*okuma şeklinde aç*/
    calculate_average_final(dosya);
    fclose(dosya);

    while(isCont == 1){
        char letterGrade;
        int studentId , instructorId , userId , courseId;
        printf("\nChoose an option: ");
        fflush(stdin); /* Tamponu temizle*/
        scanf("%c" , &option);

        if(option == 'p'){ /* yapamadim*/
            break;
        }else if(option == 'n'){

            char letter;
            printf("Enter a letter for the initial:");
            fflush(stdin); /* Tamponu temizle */
            scanf("%c" , &letter);
            dosya = fopen("//home//gorkem//Desktop//second 1.txt", "r");
            get_id_fi(dosya,letter);
            fclose(dosya);
        }else if(option == 'g'){
            printf("Enter the studentId for the GPA:");
            scanf("%d" , &studentId);
            dosya = fopen("//home//gorkem//Desktop//first 1.txt", "r");
            int gpaOfStudent = average_grade(dosya ,studentId);
            fclose(dosya);
            if(gpaOfStudent == 1){
                letterGrade = 'F';
                printf("Studen'ts letter grade is:%c \n" , letterGrade);
            }else if(gpaOfStudent == 2.5){
                letterGrade = 'D';
                printf("Studen'ts letter grade is:%c \n" , letterGrade);
            }else if(gpaOfStudent == 3){
                letterGrade = 'C';
                printf("Studen'ts letter grade is:%c \n" , letterGrade);
            }else if(gpaOfStudent == 3.5){
                letterGrade = 'B';
                printf("Studen'ts letter grade is:%c \n" , letterGrade);
            }else if(gpaOfStudent == 4){
                letterGrade = 'A';
                printf("Studen'ts letter grade is:%c \n" , letterGrade);
            }

        }else if(option == 'c'){ /* dogru calismiyor hatayi bulamadim*/
            printf("Enter the course ID:");
            scanf("%d" , &courseId);
            dosya = fopen("//home//gorkem//Desktop//first 1.txt", "r");
            print_average_grade_of_course(dosya , courseId);
            fclose(dosya);
        }else if(option == 't'){
            printf("Enter the instuctor ID:");
            scanf("%d" , &instructorId);
            dosya = fopen("//home//gorkem//Desktop//first 1.txt", "r");
            number_of_classes(dosya , instructorId);
            fclose(dosya);
        }else if(option == 'd'){ /* yapamadim */
            break;

        }else if(option == 'l'){
            printf("Enter the USER ID:");
            scanf("%d" , &userId);
            if(userId < 200000000){
                printf("This user is not a student! \n");
            }else{
                dosya = fopen("//home//gorkem//Desktop//first 1.txt", "r"); /* okuma şeklinde aç */
                print_course_id(dosya , userId);
                fclose(dosya);
            }
        }else if(option == 'e'){
            printf("Exiting... \n");
            isCont = 0;
            break;
        }
    }

    return 0;
}

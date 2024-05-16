#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // Definiše maksimalnu veličinu rečnika

int dict[MAX_SIZE][2]; // Dvodimenzionalni niz za čuvanje parova ključ-vrednost
int size = 0; // Trenutna veličina rečnika

// Deklaracije funkcija
void add(int key, int value); // Funkcija za dodavanje ili ažuriranje para ključ-vrednost
int get(int key, int defaultValue); // Funkcija za dobijanje vrednosti za dati ključ, vraća podrazumevanu vrednost ako ključ ne postoji
void remove_key(int key); // Funkcija za uklanjanje para ključ-vrednost iz rečnika
int* get_keys(); // Funkcija koja vraća niz svih ključeva
int* get_values(); // Funkcija koja vraća niz svih vrednosti

int main() {
    int command;
    // Glavna petlja koja prihvata komande dok se ne unese 0
    while (scanf("%d", &command) != EOF && command != 0) {
        int key, value;
        switch (command) {
            case 1:
                scanf("%d %d", &key, &value); // Unesi ključ i vrednost
                add(key, value); // Dodaj ili ažuriraj ključ-vrednost par
                break;
            case 2:
                scanf("%d %d", &key, &value); // Unesi ključ i podrazumevanu vrednost
                printf("%d\n", get(key, value)); // Prikaži vrednost za dati ključ ili podrazumevanu vrednost
                break;
            case 3:
                scanf("%d", &key); // Unesi ključ koji treba ukloniti
                remove_key(key); // Ukloni ključ-vrednost par
                break;
            case 4:
                printf("%d\n", size); // Prikaži trenutnu veličinu rečnika
                break;
            case 5: {
                int* keys = get_keys(); // Dobij niz ključeva
                for (int i = 0; i < size; i++) {
                    if (i != 0) {
                        printf(" ");
                    }
                    printf("%d", keys[i]); // Prikaži sve ključeve
                }
                printf("\n");
                free(keys); // Oslobodi memoriju
                break;
            }
            case 6: {
                int* values = get_values(); // Dobij niz vrednosti
                for (int i = 0; i < size; i++) {
                    if (i != 0) {
                        printf(" ");
                    }
                    printf("%d", values[i]); // Prikaži sve vrednosti
                }
                printf("\n");
                free(values); // Oslobodi memoriju
                break;
            }
        }
    }
    return 0;
}

// Definicije funkcija

// Funkcija za dodavanje ili ažuriranje para ključ-vrednost
void add(int key, int value) {
    int i = 0;
    // Pronađi poziciju gde treba umetnuti novi ključ, održavajući redosled
    while (i < size && dict[i][0] < key) {
        i++;
    }
    if (i < size && dict[i][0] == key) {
        // Ključ već postoji, ažuriraj vrednost
        dict[i][1] = value;
    } else {
        // Ključ ne postoji, dodaj novi par ključ-vrednost
        for (int j = size; j > i; j--) {
            dict[j][0] = dict[j-1][0];
            dict[j][1] = dict[j-1][1];
        }
        dict[i][0] = key;
        dict[i][1] = value;
        size++;
    }
}

// Funkcija za dobijanje vrednosti za dati ključ, vraća podrazumevanu vrednost ako ključ ne postoji
int get(int key, int defaultValue) {
    for (int i = 0; i < size; i++) {
        if (dict[i][0] == key) {
            return dict[i][1];
        }
    }
    return defaultValue;
}

// Funkcija za uklanjanje para ključ-vrednost iz rečnika
void remove_key(int key) {
    int i = 0;
    // Pronađi ključ koji treba ukloniti
    while (i < size && dict[i][0] != key) {
        i++;
    }
    if (i < size) {
        // Pomeri sve elemente iza uklonjenog ključa za jedno mesto unazad
        for (int j = i; j < size - 1; j++) {
            dict[j][0] = dict[j+1][0];
            dict[j][1] = dict[j+1][1];
        }
        size--;
    }
}

// Funkcija koja vraća niz svih ključeva
int* get_keys() {
    int* keys = malloc(size * sizeof(int)); // Alocira memoriju za niz ključeva
    for (int i = 0; i < size; i++) {
        keys[i] = dict[i][0];
    }
    return keys;
}

// Funkcija koja vraća niz svih vrednosti
int* get_values() {
    int* values = malloc(size * sizeof(int)); // Alocira memoriju za niz vrednosti
    for (int i = 0; i < size; i++) {
        values[i] = dict[i][1];
    }
    return values;
}

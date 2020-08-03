#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define IdxMax 10000
#define true 1
#define false 0

typedef int IdxType;  /* type indeks */
typedef int ElType;   /* type elemen tabel */
typedef struct { 
	ElType TI[IdxMax + 1]; /* memori tempat penyimpan elemen (container) */
	IdxType Idx; /* >=0, banyaknya elemen efektif */
    IdxType MaxElement; /* >=0, banyaknya elemen efektif */
} PolinomStandar;

typedef struct { 
	PolinomStandar Polinom1;
    IdxType Idx1;
    PolinomStandar Polinom2;
    IdxType Idx2;
} hasilBagiPolinom;

typedef struct { 
	PolinomStandar Polinom1;
    IdxType Idx1;
    PolinomStandar Polinom2;
    IdxType Idx2;
    PolinomStandar Polinom3;
    IdxType Idx3;
} hasilKaliPolinom;

PolinomStandar bangunPolinom(){
    PolinomStandar Polinom;
    IdxType pangkatTertinggi;
    int benarPangkatTertinggi = false;
    printf("Masukkan nilai pangkat tertinggi : "); scanf("%d",&Polinom.Idx); 
    pangkatTertinggi = Polinom.Idx;
    for (int i = Polinom.Idx; i >= 0; i--){
        if (rand() % 2 == 0){
           Polinom.TI[i] = (((rand() % 10) * (rand() % 10)) % 10 ) * (-1);
        } else {
            Polinom.TI[i] = (((rand() % 10) * (rand() % 10)) % 10 ) * (-1);
        }
        // scanf("%d",&Polinom.TI[i]); 
        if ((benarPangkatTertinggi == false) && (Polinom.TI[pangkatTertinggi] != 0 || pangkatTertinggi == 0)){
            benarPangkatTertinggi = true;
        } else if (benarPangkatTertinggi == false){
            pangkatTertinggi -= 1;
        }
    }
    Polinom.Idx = pangkatTertinggi;
    printf("\n");
    return Polinom;
} 

void cetakPolinom(PolinomStandar Polinom){
    for (int i = Polinom.Idx; i >= 0 ; i--){
        if ((Polinom.TI[i] <= 0 || Polinom.Idx == 0) && i == 0) {
            printf("%d", Polinom.TI[i]);
        } else if (Polinom.TI[i] > 0 && i == 0) {
            printf("+ %d", Polinom.TI[i]);
        } else if (i == 1) {
            if (Polinom.TI[i] == 1 && Polinom.Idx == 1) {
                printf("x ");
            } else if ((Polinom.TI[i] == -1) && Polinom.Idx == 1) {
                printf("- x ");
            } else if (Polinom.TI[i] < 0 || (Polinom.Idx == i && Polinom.TI[i] != 0)) {
                printf("%d x",Polinom.TI[i]);
            } else if (Polinom.TI[i] > 0){
                printf("+ %d x",Polinom.TI[i]);
            }
        } else{
            if (Polinom.TI[i] == 1 && Polinom.Idx == i) {
                printf("x^%d",i);
            } else if ((Polinom.TI[i] == -1) && Polinom.Idx == i) {
                printf("- x^%d",i);
            } else if (Polinom.TI[i] == 1) {
                printf("+ x^%d",i);
            } else if (Polinom.TI[i] < 0 || (Polinom.Idx == i && Polinom.TI[i] != 0)) {
                printf("%d x^%d",Polinom.TI[i],i);
            } else if (Polinom.TI[i] > 0){
                printf("+ %d x^%d",Polinom.TI[i],i);
            }
        }
    }
    printf("\n");
    printf("\n");
}

PolinomStandar jumlahPolinom(PolinomStandar Polinom1, PolinomStandar Polinom2){
    PolinomStandar PolinomHasil;
    if (Polinom1.Idx > Polinom2.Idx){
        PolinomHasil.Idx = Polinom1.Idx;
    } else{
        PolinomHasil.Idx = Polinom2.Idx;
    }
    for (int i = 0; i <= PolinomHasil.Idx; i++){
        PolinomHasil.TI[i] = 0; 
        if (i <= Polinom2.Idx) {
            PolinomHasil.TI[i] += Polinom2.TI[i];
        }
        if (i <= Polinom1.Idx){
            PolinomHasil.TI[i] += Polinom1.TI[i];
        }
    }
    return PolinomHasil;
}

PolinomStandar kaliPolinom_konstanta(PolinomStandar Polinom1,int konstanta){
    PolinomStandar PolinomHasil;
    for (int k = 0; k <= Polinom1.Idx; k++){
        PolinomHasil.TI[k] = Polinom1.TI[k] * konstanta; 
    }
    PolinomHasil.Idx = Polinom1.Idx;
    return PolinomHasil;
}

IdxType pilihIndex(PolinomStandar Polinom1, PolinomStandar Polinom2){
    IdxType Hasil;
    if (Polinom1.Idx >= Polinom2.Idx){
        Hasil = Polinom2.Idx/2;
    } else {
        Hasil = Polinom1.Idx/2;
    }
    return Hasil;
}

hasilBagiPolinom bagiPolinom(PolinomStandar Polinom, IdxType Index){
    hasilBagiPolinom hasil;
    int i;
    for (i = 0; i <= Index; i++){
        hasil.Polinom1.TI[i] = Polinom.TI[i];
        hasil.Polinom2.TI[i] = Polinom.TI[i + Index + 1];
    }
    hasil.Polinom1.Idx = Index;
    hasil.Polinom2.Idx = Polinom.Idx - (Index + 1);
    hasil.Idx1 = 0;
    hasil.Idx2 = Index + 1;
    return hasil;
}

PolinomStandar gabungPolinom(hasilKaliPolinom Polinom){
    PolinomStandar PolinomHasil;
    IdxType pangkatTertinggi;
    int benarPangkatTertinggi = false;
    PolinomHasil.Idx = Polinom.Polinom3.Idx + Polinom.Idx3;
    pangkatTertinggi = PolinomHasil.Idx;
    for (int k = 0; k <= PolinomHasil.Idx; k++){
        PolinomHasil.TI[k] = 0;
    }
    for (int i = 0; i <= PolinomHasil.Idx; i++){
        if (i <= Polinom.Polinom1.Idx) {
            PolinomHasil.TI[i + Polinom.Idx1] += Polinom.Polinom1.TI[i];
        }
        if (i <= Polinom.Polinom2.Idx) {
            PolinomHasil.TI[i + Polinom.Idx2] += Polinom.Polinom2.TI[i];
        }
        if (i <= Polinom.Polinom3.Idx){
            PolinomHasil.TI[i + Polinom.Idx3] += Polinom.Polinom3.TI[i];
        }
    }
    while ((benarPangkatTertinggi == false) && (PolinomHasil.TI[pangkatTertinggi] == 0)){
        if (pangkatTertinggi == 0){
            benarPangkatTertinggi = true;
        } else {
            pangkatTertinggi -= 1;
        }
    }
    PolinomHasil.Idx = pangkatTertinggi;
    return PolinomHasil;
}

PolinomStandar kaliPolinom_bruteForce(PolinomStandar Polinom1, PolinomStandar Polinom2){
    PolinomStandar PolinomHasil;
    PolinomHasil.Idx = Polinom1.Idx + Polinom2.Idx;
    for (int k = 0; k <= PolinomHasil.Idx; k++){
        PolinomHasil.TI[k] = 0; 
    }
    for (int i = 0; i <= Polinom1.Idx; i++){
        for (int j = 0; j <= Polinom2.Idx; j++){
            PolinomHasil.TI[i + j] += Polinom1.TI[i] * Polinom2.TI[j]; 
        }
    }
    return PolinomHasil;
}

PolinomStandar kaliPolinom_divideAndConquer(PolinomStandar Polinom1, PolinomStandar Polinom2){
    PolinomStandar hasilAkhir;
    if ((Polinom1.Idx < 10) || (Polinom2.Idx < 10)){
        return kaliPolinom_bruteForce(Polinom1,Polinom2);
    }
    // algoritma divide
    IdxType Index = pilihIndex(Polinom1,Polinom2);
    hasilBagiPolinom hasilbagiPolinom1 = bagiPolinom(Polinom1,Index);
    hasilBagiPolinom hasilbagiPolinom2 = bagiPolinom(Polinom2,Index);

    // algoritma conquer
    hasilKaliPolinom PolinomHasil;
    PolinomStandar polinm;

    PolinomHasil.Idx1 = 0;
    PolinomHasil.Idx2 = hasilbagiPolinom1.Idx1 + hasilbagiPolinom2.Idx2;
    PolinomHasil.Idx3 = hasilbagiPolinom1.Idx2 + hasilbagiPolinom2.Idx2;

    PolinomHasil.Polinom1.Idx = hasilbagiPolinom1.Polinom1.Idx + hasilbagiPolinom2.Polinom1.Idx;
    PolinomHasil.Polinom2.Idx = hasilbagiPolinom1.Polinom1.Idx + hasilbagiPolinom2.Polinom2.Idx;
    PolinomHasil.Polinom3.Idx = hasilbagiPolinom1.Polinom2.Idx + hasilbagiPolinom2.Polinom2.Idx;
    
    PolinomHasil.Polinom1 = kaliPolinom_divideAndConquer(hasilbagiPolinom1.Polinom1,hasilbagiPolinom2.Polinom1);
    PolinomHasil.Polinom3 = kaliPolinom_divideAndConquer(hasilbagiPolinom1.Polinom2,hasilbagiPolinom2.Polinom2);
    PolinomHasil.Polinom2 = jumlahPolinom(kaliPolinom_divideAndConquer(jumlahPolinom(hasilbagiPolinom1.Polinom1, hasilbagiPolinom1.Polinom2), jumlahPolinom(hasilbagiPolinom2.Polinom1, hasilbagiPolinom2.Polinom2)),jumlahPolinom(kaliPolinom_konstanta(PolinomHasil.Polinom3,-1),kaliPolinom_konstanta(PolinomHasil.Polinom1,-1)));
    
    // algoritma merge
    hasilAkhir = gabungPolinom(PolinomHasil);
    return hasilAkhir;
}

int main(){
    clock_t start1,start2,end1,end2;
    double dif1,dif2;
    PolinomStandar Polinom, Polinom1,Polinom2, hasilKaliPolinom_bruteForce, hasilKaliPolinom_divideAndConquer;
    hasilBagiPolinom hasilBagiPolinom;
    Polinom1 = bangunPolinom();
        printf("Polinom 1 adalah \n"); cetakPolinom(Polinom1);
    Polinom2 = bangunPolinom();
        printf("Polinom 2 adalah \n"); cetakPolinom(Polinom2);

    start1 = clock();
    hasilKaliPolinom_bruteForce = kaliPolinom_bruteForce(Polinom1,Polinom2);
    end1 = clock();
    dif1 = (double) (end1 - start1) / CLOCKS_PER_SEC;
    printf("Hasil kali Polinom 1 dan Polinom 2 secara Brute Force adalah \n"); cetakPolinom(hasilKaliPolinom_bruteForce); printf("dengan Total waktu yang diperlukan adalah %f seconds. \n", dif1);
    
    start2 = clock();
    hasilKaliPolinom_divideAndConquer = kaliPolinom_divideAndConquer(Polinom1,Polinom2);
    end2 = clock();
    dif2 = (double) (end2 - start2) / CLOCKS_PER_SEC;
    printf("Hasil kali Polinom 1 dan Polinom 2 secara Divide and Conquer adalah \n"); cetakPolinom(hasilKaliPolinom_divideAndConquer); printf("dengan Total waktu yang diperlukan adalah %f seconds. \n", dif2);
    return 0;
} 
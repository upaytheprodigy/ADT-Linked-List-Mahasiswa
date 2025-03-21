#include <limits.h>
#include <malloc.h>
#include "mahasiswa.h"
#include <string.h>

void CreateList(List *L){
    First(*L) = Nil;
}

address Alokasi(namaType X, nilaiType Y){
    address P;
    P = (address) malloc(sizeof(Mhs));
    if(P != Nil){
        strcpy(Nama(P), X);
        Nilai(P) = Y;
        Next(P) = Nil;
    }
}

void Dealokasi(address P){
    free(P);
}

void DeleteAll(List *L){
    address P;
    while(First(*L) != Nil){
        DeleteFirst(L, &P);
        Dealokasi(P);
    }
}

boolean IsEmpty(List L){
    return First(L) == Nil;
}

void InsVFirst(List *L, namaType X, nilaiType Y){
    address P;
    P = Alokasi(X, Y);
    if(P != Nil){
        InsertFirst(L, P);
    }
}

void InsVLast(List *L, namaType X, nilaiType Y){
    address P;
    P = Alokasi(X, Y);
    if(P != Nil){
        InsertLast(L, P);
    }
}

void InsertFirst(List *L, address P){
    Next(P) = First(*L);
    First(*L) = P;
}

void InsertAfter(List *L, address P, address Prec){
    Next(P) = Next(Prec);
    Next(Prec) = P;
}

void InsertLast(List *L, address P){
    address Last;
    if(IsEmpty(*L)){
        InsertFirst(L, P);
    } else {
        Last = First(*L);
        while(Next(Last) != Nil){
            Last = Next(Last);
        }
        InsertAfter(L, P, Last);
    }
}

void Insert(List *L, address P){
    if(IsEmpty(*L)){
        InsertFirst(L, P);
    } else {
        InsertLast(L, P);
    }
}

void DelVFirst(List *L, namaType *X, nilaiType *Y){
    address P;
    DeleteFirst(L, &P);
    if(P != Nil){
        strcpy(*X, Nama(P));
        *Y = Nilai(P);
        Dealokasi(P);
    }
}

void DelVLast(List *L, namaType *X, nilaiType *Y){
    address P;
    DeleteLast(L, &P);
    if(P != Nil){
        strcpy(*X, Nama(P));
        *Y = Nilai(P);
        Dealokasi(P);
    }
}

void DeleteFirst(List *L, address *P){
    *P = First(*L);
    First(*L) = Next(First(*L));
    Next(*P) = Nil;
}

void DeleteAfter(List *L, address *P, address Prec){
    *P = Next(Prec);
    Next(Prec) = Next(Next(Prec));
    Next(*P) = Nil;
}

void DeleteLast(List *L, address *P){
    address Last, PrecLast;
    Last = First(*L);
    PrecLast = Nil;
    while(Next(Last) != Nil){
        PrecLast = Last;
        Last = Next(Last);
    }
    if(PrecLast == Nil){
        DeleteFirst(L, P);
    } else {
        DeleteAfter(L, P, PrecLast);
    }
}

void DelP(List *L, namaType X){
    address P, Prec;
    P = Search(*L, X);
    if(P != Nil){
        Prec = SearchPrec(*L, X);
        if(Prec == Nil){
            DeleteFirst(L, &P);
        } else {
            DeleteAfter(L, &P, Prec);
        }
        Dealokasi(P);
    }
}

address Search(List L, namaType X){
    address P;
    P = First(L);
    while(P != Nil && strcmp(Nama(P), X) != 0){
        P = Next(P);
    }
    return P;
}

address SearchPrec(List L, namaType X){
    address P;
    P = First(L);
    while(Next(P) != Nil && strcmp(Nama(Next(P)), X) != 0){
        P = Next(P);
    }
    return P;
}

boolean FSearch(List L, address P){
    address P1;
    P1 = First(L);
    while(P1 != Nil && P1 != P){
        P1 = Next(P1);
    }
    return P1 != Nil;
}

void PrintInfo(List L){
    address P;
    P = First(L);
    while(P != Nil){
        printf("Nama: %s, Nilai UTS: %d\n", Nama(P), Nilai(P));
        P = Next(P);
    }
}

void Menu(){
    printf("Menu\n");
    printf("1. Isi Data Mahasiswa\n");
    printf("2. Tampilkan Data Mahasiswa Pertama\n");
    printf("3. Lihat Jumlah Mahasiswa\n");
    printf("4. Copy Nilai > 70 Daftar Lain\n");
    printf("5. Tampikan Data Mahasiswa Kedua\n");
    printf("6. Hapus Duplikat\n");
    printf("7. Hapus Semua Data\n");
    printf("8. Keluar\n");
    printf("Pilihan: ");
}

void SubMenu(List *L) {
    int pilihan;
    printf("Urutkan berdasarkan:\n");
    printf("1. Nama\n");
    printf("2. Nilai\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan);
    
    int tipeUrutan;
    printf("1. Ascending\n");
    printf("2. Descending\n");
    printf("Pilihan: ");
    scanf("%d", &tipeUrutan);

    if (pilihan == 1 || pilihan == 2) {
        SortList(L, pilihan == 1, tipeUrutan == 1);
        if (pilihan == 1) {
            if (tipeUrutan == 1) {
                printf("Daftar Nama Mahasiswa (A-Z)\n");
            } else {
                printf("Daftar Nama Mahasiswa (Z-A)\n");
            }
        } else {
            if (tipeUrutan == 1) {
                printf("Daftar Nilai Mahasiswa (0-100)\n");
            } else {
                printf("Daftar Nilai Mahasiswa (100-0)\n");
            }
        }
    } else {
        printf("Pilihan anda tidak valid!!\n");
        return;
    }

    PrintInfo(*L);
}

void SortList(List *L, int byNama, int ascending) {
    if (IsEmpty(*L)) {
        printf("Daftar kosong, tidak dapat diurutkan.\n");
        return;
    }

    address P, Q;
    namaType tempNama;
    nilaiType tempNilai;

    P = First(*L);
    while (P != Nil) {
        Q = Next(P);
        while (Q != Nil) {
            int compare;
            if (byNama) {
                // Urutkan berdasarkan nama
                compare = strcmp(Nama(P), Nama(Q));
            } else {
                // Urutkan berdasarkan nilai
                compare = Nilai(P) - Nilai(Q);
            }

            // Tentukan apakah perlu menukar data
            if ((ascending && compare > 0) || (!ascending && compare < 0)) {
                // Tukar data
                strcpy(tempNama, Nama(P));
                tempNilai = Nilai(P);
                strcpy(Nama(P), Nama(Q));
                Nilai(P) = Nilai(Q);
                strcpy(Nama(Q), tempNama);
                Nilai(Q) = tempNilai;
            }
            Q = Next(Q);
        }
        P = Next(P);
    }
}

int countElement(List L){
    address P;
    int count = 0;
    P = First(L);
    while(P != Nil){
        count++;
        P = Next(P);
    }
    return count;
}

void CopyAbove70(List L1, List *L2){
    address P;
    namaType tempNama;
    nilaiType tempNilai;
    P = First(L1);
    while(P != Nil){
        if(Nilai(P) > 70){
            strcpy(tempNama, Nama(P));
            tempNilai = Nilai(P);
            InsVLast(L2, tempNama, tempNilai);
        }
        P = Next(P);
    }
}

void RemoveDuplicate(List *L){
    address P, Q, Prec;
    P = First(*L);
    while(P != Nil){
        Q = Next(P);
        Prec = P;
        while(Q != Nil){
            if(strcmp(Nama(P), Nama(Q)) == 0){
                DeleteAfter(L, &Q, Prec);
                Dealokasi(Q);
            } else {
                Prec = Q;
                Q = Next(Q);
            }
        }
        P = Next(P);
    }
}


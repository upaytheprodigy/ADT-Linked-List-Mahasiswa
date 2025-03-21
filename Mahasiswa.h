#ifndef mahasiswa_H
#define mahasiswa_H
#include "boolean.h"
#include <stdio.h>
#define Nil NULL
#define Nama(P) (P)->nama
#define Nilai(P) (P)->nilai
#define Next(P) (P)->next
#define First(L) (L).First

typedef char namaType[50];
typedef int nilaiType;
typedef struct Mahasiswa *address;
typedef struct Mahasiswa {
	namaType nama;
	nilaiType nilai;
	address next;
} Mhs;

typedef struct {
	  address First;
} List;



// Consturctor
void CreateList(List *L);
address Alokasi(namaType X, nilaiType Y);
void Dealokasi(address P);

// Destructor
void DeleteAll(List *L);

// Validator
boolean IsEmpty(List L);

// Get/Set
void InsVFirst(List *L, namaType X, nilaiType Y);
void InsVLast(List *L, namaType X, nilaiType Y);
void InsertFirst(List *L, address P);
void InsertAfter(List *L, address P, address Prec);
void InsertLast(List *L, address P);
void Insert(List *L, address P);

void DelVFirst(List *L, namaType *X, nilaiType *Y);
void DelVLast(List *L, namaType *X, nilaiType *Y);
void DeleteFirst(List *L, address *P);
void DeleteAfter(List *L, address *P, address Prec);
void DeleteLast(List *L, address *P);
void DelP(List *L, namaType X);

// Search
address Search(List L, namaType X);
address SearchPrec(List L, namaType X);
boolean FSearch(List L, address P);

// PrintObject
void PrintInfo(List L);

// Other
void Menu();
void SubMenu(List *L);
void SortList(List *L, int byNama, int ascending);
int countElement(List L);
void CopyAbove70(List L, List *L2);
void RemoveDuplicate(List *L);



#endif
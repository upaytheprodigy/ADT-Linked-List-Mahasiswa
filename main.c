#include "mahasiswa.h"
#include <stdio.h>
#include <string.h>

int main(){
    List L1, L2;
    namaType nama;
    nilaiType nilai;
    address P, Prec;
    int pilihan;
    CreateList(&L1);
    CreateList(&L2);

    do{
        Menu();
        scanf("%d", &pilihan);
        getchar();
        
        switch (pilihan){
        case 1:
            printf("Masukkan nama: ");
            fgets(nama, sizeof(nama), stdin);
            nama[strcspn(nama, "\n")] = 0;
            printf("Masukkan nilai: ");
            scanf("%d", &nilai);
            Insert(&L1, Alokasi(nama, nilai));
            printf("Data berhasil dimasukkan\n");
            break;
        case 2:
            if (IsEmpty(L1)){
                printf("Data kosong\n");
            } else {
                SubMenu(&L1);
            }
            break;
        case 3:
            printf("Jumlah Mahasiswa: %d\n", countElement(L1));
            break;
        case 4:
            CopyAbove70(L1, &L2);
            printf("Data mahasiswa dengan nilai di atas 70 berhasil disalin\n");
            break;

        case 5:
            if (IsEmpty(L2)){
                printf("Data mahasiswa dengan nilai di atas 70 kosong\n");
            } else {
                printf("Data mahasiswa dengan nilai di atas 70\n");
                PrintInfo(L2);
            }
            break;
        case 6:
            RemoveDuplicate(&L1);
            printf("Duplikat berhasil dihapus\n");
            break;
        case 7:{
            char confirm;
            printf("Apakah anda yakin ingin menghapus semua data? (y/n): ");
            scanf("%c", &confirm);
            if (confirm == 'y' || confirm == 'Y'){
                DeleteAll(&L1);
                DeleteAll(&L2);
                printf("Data berhasil dihapus\n");
            } else {
                printf("Data tidak jadi dihapus\n");
            }
            break;
        }
        case 8:
            printf("Program selesai\n");
            DeleteAll(&L1);
            DeleteAll(&L2);
            break;
        default:
            printf("Pilihan anda tidak valid\n");
            break;
        }
    } while (pilihan != 8);

    return 0;
}

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <cstring>
using namespace std;

struct film{
    char nama[100];
    int harga;
    int tahun;
    float rating;
};

film film[58];
int jumlahFile = 0;

//fungsi buat ngambil data di file
void ngambilData(){

    FILE *cihuy_ptr = fopen("netfilm_db.txt","r");
    if(cihuy_ptr==nullptr){
        cout << "Data masih kosong." << endl << endl;
        return;
    }

    jumlahFile = 0;

    while(fscanf(cihuy_ptr," %[^;];%d;%d;%f\n",
        film[jumlahFile].nama,
        &film[jumlahFile].harga,
        &film[jumlahFile].tahun,
        &film[jumlahFile].rating) != EOF){

        jumlahFile++;
    }

    fclose(cihuy_ptr);
}

//fungsi buat nyimpen data yang ada di array ke dalam file
void simpanData(){

    FILE *cihuy_ptr = fopen("netfilm_db.txt","w");
    if(cihuy_ptr==nullptr){
        cout << "Data masih kosong." << endl << endl;
        return;
    }

    for(int i=0;i<jumlahFile;i++){
        fprintf(cihuy_ptr,"%s;%d;%d;%.1f\n",
        film[i].nama,
        film[i].harga,
        film[i].tahun,
        film[i].rating);
    }

    fclose(cihuy_ptr);
}

//fungsi buat nampilin daftar film
void lihatFilm(){

    ngambilData();

    cout << "|==================================|" << endl;
    cout << "|   DAFTAR FILM TERGACOR NETFILM   |" << endl;
    cout << "|==================================|" << endl << endl;

    cout << string(60,'=') << endl;

    cout << left
    << setw(4) << "No"
    << setw(30) << "Judul"
    << setw(10) << "Harga"
    << setw(8) << "Tahun"
    << setw(8) << "Rating" << endl;

    cout<<string(60,'=') << endl;

    for(int i=0; i<jumlahFile; i++){

        cout << left
        << setw(4) << i+1
        << setw(30) << film[i].nama
        << setw(10) << film[i].harga
        << setw(8) << film[i].tahun
        << setw(8) << film[i].rating << endl;

        cout << string(60,'-') << endl;
    }

    cout << endl;
}

//fungsi buat nginput film baru ke dalam file
void tambahFilm(){

    cin.ignore();

    cout << "|================================|" << endl;
    cout << "|   SOKIN NGAFF TAMBAH FILMNYA   |" << endl;
    cout << "|================================|" << endl << endl;

    cout << "========================================================" << endl;

    cout << "Judul Film  : ";
    cin.getline(film[jumlahFile].nama,100);

    cout << "Harga Film  : ";
    cin >> film[jumlahFile].harga;

    cout << "Tahun Rilis : ";
    cin >> film[jumlahFile].tahun;

    cout << "Rating Film : ";
    cin >> film[jumlahFile].rating;

    cout << "========================================================" << endl;

    jumlahFile++;
    simpanData();

    cout << "Data berhasil ditambahkan." << endl << endl;
}

//fungsi buat ngorting film berdasarkan rating
void sortRating_Quick(int low,int high){

    int i = low;
    int j = high;
    float pivot = film[(low+high)/2].rating;

    while(i <= j){

        while(film[i].rating > pivot) i++;
        while(film[j].rating < pivot) j--;

        if(i <= j){
            swap(film[i],film[j]);
            i++;
            j--;
        }
    }

    if(low < j) sortRating_Quick(low,j);
    if(i < high) sortRating_Quick(i,high);
}

//fungsi buat sorting film berdasarkan huruf pertama pada nama
void sortAbjad_Bubble(){

    ngambilData();

    for(int i=0; i<jumlahFile-1; i++){
        for(int j=0; j<jumlahFile-1; j++){

            if(strcmp(film[j].nama,film[j+1].nama)>0){
                swap(film[j],film[j+1]);
            }

        }
    }

    simpanData();
}

//fungsi buat nyari film pake linear search(tanpa sentinel)
int cariLinear(char filmcari[]){

    for(int i=0; i<jumlahFile; i++){
        if(strcmp(film[i].nama,filmcari)==0){
            return i;
        }
    }

    return -1;
}

//fungsi buat nyari film pake binary search
int cariBinary(char filmcari[]){

    int awal = 0;
    int akhir = jumlahFile-1;

    while(awal <= akhir){

        int tengah = (awal+akhir)/2;

        int cmp = strcmp(film[tengah].nama,filmcari);

        if(cmp == 0)
            return tengah;

        else if(cmp < 0)
            awal = tengah + 1;

        else
            akhir = tengah - 1;
    }

    return -1;
}

//fungsi buat nyari film sebelum diarahin ke metode pencarian
void cariFilm(){

    char filmcari[100];

    cin.ignore();

    cout << "Masukkan Judul Film : ";
    cin.getline(filmcari,100);

    int posisi;

    if(jumlahFile < 30)
        posisi = cariLinear(filmcari);
    else{
        sortAbjad_Bubble();
        posisi = cariBinary(filmcari);
    }

    if(posisi != -1){

        cout << "==========================================" << endl;
        cout << "Filmnya ketemu wak!" << endl;
        cout << "==========================================" << endl;
        cout << "Judul  : " << film[posisi].nama << endl;
        cout << "Harga  : " << film[posisi].harga << endl;
        cout << "Tahun  : " << film[posisi].tahun << endl;
        cout << "Rating : " << film[posisi].rating << endl;
        cout << "==========================================" << endl << endl;
    }
    else{
        cout << "Alamak filenya ngga ketemu wak." << endl << endl;
    }
}

//program utama yang isinya menu yang terhubung sama fungsi yang udah dibuat
int main(){

    while(true){
		
		menu :
		
        int pilih;

        cout << "|=======================================|" << endl;
        cout << "|      NETFILM SYSTEM - DASHBOARD       |" << endl;
        cout << "|=======================================|" << endl;
        cout << "|                                       |" << endl;
        cout << "|  [1] Lihat Katalog Film               |" << endl;
        cout << "|  [2] Urutkan Rating (Quick Sort)      |" << endl;
        cout << "|  [3] Urutkan Abjad (Bubble Sort)      |" << endl;
        cout << "|  [4] Cari Film                        |" << endl;
        cout << "|  [5] Tambah Film Baru                 |" << endl;
        cout << "|  [0] Keluar & Simpan                  |" << endl;
        cout << "|                                       |" << endl;
        cout << "|=======================================|" << endl;

        cout << "Input pilihanmu: ";
        cin >> pilih;
        


        if(pilih==1){
			system("cls");
            lihatFilm();
            goto lanjut;
        }

        else if(pilih==2){
			system("cls");
            ngambilData();
            sortRating_Quick(0,jumlahFile-1);
            simpanData();
            lihatFilm();
            cout << "Data berhasil disortir berdasarkan rating" << endl << endl;
            goto lanjut;
        }

        else if(pilih==3){
			system ("cls");
            sortAbjad_Bubble();
            lihatFilm();
            cout << "Data berhasil disortir berdasarkan judul (A-Z)." << endl << endl;
            goto lanjut;
        }

        else if(pilih==4){
			system("cls");
            cariFilm();
            goto lanjut;
        }

        else if(pilih==5){
			system("cls");
            tambahFilm();
            goto lanjut;
        }

        else if(pilih==0){
			system("cls");
            simpanData();
            cout << "Data tekah disimpan, sampai jumpa." << endl;
            return 0;
        }

        else{
            cout << "Input tidak valid. Silahkan input ulang." << endl << endl;
            
        }
        
    }
    
    
    lanjut : {
		
		string lanjut;
		cout << "apakah anda ingin kembali ke menu? (y/t) : ";
		cin >> lanjut;
		
		if(lanjut=="Y"||lanjut=="y"){ system("cls"); goto menu;}
		
		else if(lanjut=="t"||lanjut=="T"){simpanData(); cout << "Data tekah disimpan, sampai jumpa." << endl; return 0;}
		
		else {cout << "input tidak valid. silahkan input ulang" << endl << endl; goto lanjut; }
		
		
		}
   
    return 0;
}

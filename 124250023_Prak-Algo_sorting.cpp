#include <iostream>
using namespace std;

void buble(string arr[], int n){
	
	for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < n - 1 - i; j++) {
         if (arr[j] > arr[j + 1]) {
            swap(arr[j], arr[j + 1]);
            }
        }
    }
    cout << endl;
    cout << "Setelah disorting : ";
    
    for (int i = 0; i < n; i++) {
      cout << arr[i] << " ";
	}
}

void quick(string array[], int awal, int akhir) {

    int low = awal, high = akhir;
    string pivot = array[(awal + akhir) / 2];

    do {
		
        while (array[low] > pivot)
            low++;

        while (array[high] < pivot)
            high--;


        if (low <= high) {
            swap(array[low], array[high]);
            low++;
            high--;
        }

    } while (low <= high);


    if (awal < high)
        quick(array, awal, high);

    if (low < akhir)
        quick(array, low, akhir);
        
    
}


int main(){
	
	int n;
	
	cout << "================================" << endl;
	cout << "Selamat datang di tempat sorting" << endl;
	cout << "================================" << endl;
	
	play : {
		
		cout << "Jumlah nama yang akan diinput: "; 
		cin >> n;
		string gawatrektor[n];
		
		for(int i=0; i<n; i++){
			cout << "Nama ke " << i+1 << " : ";
			cin >> gawatrektor[i];
			}
		
		pilih : {
			
			int pilih;
			cout << "______________________" << endl;
			cout << "Pilih metode sorting: " << endl;
			cout << "1. Buble Sort" << endl;
			cout << "2. Quick Sort" << endl;
			cout << "----------------------" << endl;
			cout << "Pilih: ";cin >> pilih;
			
			cout << "Sebelum disorting : ";
			for(int i=0; i<n; i++){
				cout << gawatrektor[i] << "  ";
			}
			
			if(pilih==1) {buble(gawatrektor, n);
			}
			
			else if(pilih==2) {
				quick(gawatrektor, 0, n-1);
				
				cout << endl;
				cout << "Setelah disorting : "; 
				for (int i = 0; i<n; i++) {
					cout << gawatrektor[i] << "  ";}
				}
			
			else { cout << "Input tidak valid. Silahkan input ulang" << endl; goto pilih;}
			}
			
		
		lanjut : {
			
			int lanjut;
			cout << endl;
			cout << "Ingin melakukan sorting lagi? (1/0)  ";
			cin >> lanjut;
			
			if(lanjut==0) {cout << "Sampai jumpa lagi" << endl; return 0;}
			
			else if(lanjut==1) {goto play;}
			
			else {cout << "input tidak valid. Silahkan input ulang" << endl; goto lanjut;}
			
			}
		}
	}

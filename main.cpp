#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>

void tambahsiswa();

int getOption();

using namespace std;



struct siswa{
	string nis;
	string nama;
	string kelas;
	};



int main(){
	int pilihan = getOption();
	char lanjut;
	
	while(pilihan != 5){
		
		switch(pilihan){
			case 1:
			   cout<<"wealah wak!\n";
			   tambahsiswa();
			   break;
			
			default:
			   cout<<"PILIHAN TIDAK ADA!\n";
			   break;
			}
		
		cout<<"MASIH LANJUT? ";
		cin.get(lanjut);
		
		if(lanjut == 'n' | lanjut == 'N'){
			break;
		}
		else{
			pilihan = getOption();
		}
		}
	
	return 0;
}



int getOption(){
	system("clear");
	int opsi;
	
	cout<<"PERPUSTAKAAN JAYA MAJU\n";
	cout<<"=======================\n";
	cout<<"OPSI MENU : \n";
	cout<<"1. MENAMBAH SISWA"<<endl;
	cout<<"5. EXIT"<<endl;
	cout<<"PILIHAN ANDA : ";
	cin>>opsi;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	return opsi;
	}



void tambahsiswa(){
	fstream myfile;
	string buffer;
	
	myfile.open("siswa.txt", ios::out | ios::in);
	
	if(myfile.is_open()){
		cout<<"data ditemukan, melanjutkan operasi"<<endl;
		}
	else{
		cout<<"data tidak ditemukan, membuat data baru..."<<endl;
		myfile.close();
		myfile.open("siswa.txt", ios::trunc | ios::out);
		myfile <<setw(5)<<"NIS  "<<"|"<<setw(16)<<"NAMA           "<<"|"<<setw(11)<<"KELAS     "<<setw(10)<<"space : "<<15<<endl;
		}
		
		siswa tambah;
		cout<<"NIS : ";
		cin>>tambah.nis;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout<<"NAMA : ";
		getline(cin, tambah.nama);
		cout<<"KELAS : ";
		getline(cin, tambah.kelas);
		
		myfile.seekp(4, fstream::end);
		
		myfile <<setw(5)<< tambah.nis <<"|"<<setw(16)<<tambah.nama<<"|"<<setw(11)<<tambah.kelas<<endl;
	
	myfile.close();
	
	}
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>

using namespace std;

//deklarasi fungsi (meski fungsinya diprogram setelah int main, tetapi jika dideklarasikan terlebih dahulu maka akan otomatis didahulukan eksekusinya)
void tampilsiswa();
void tampilbuku();
void tambahsiswa();
void tambahbuku();
bool carisiswa(string cari);
int caribuku(string cari, int* jumlah, int* pos);
void tampilpinjam();
void pinjam();
void mengembalikan();
int getOption();


//deklarasi struct
struct buku{
	int pos, jumlah;
};

struct siswa{
	string nis;
	string nama;
	string kelas;
	};


//program utama
int main(){
	//deklarasi variabel
	int pilihan = getOption();//nilai variabel diambil dari pengembalian nilai fungsi getOption
	int jumlah, pos;
	string input;
	char lanjut;
	
	while( pilihan != 10 ){
		
		switch( pilihan ){
			case 1:
			   //memanggil fungsi
			   tambahsiswa();
			   break;
			   
			case 2:
			    tambahbuku();
			    break;
			    
			case 3:
			    cout << "NIS : ";
			    cin >> input;
			    cin.ignore(numeric_limits<streamsize>::max(), '\n');//menghindari enter masuk ke getline
			    carisiswa(input);
			    break;
			
			case 4:
			    cout<<"ISBN : ";
			    cin>>input;
			    cin.ignore(numeric_limits<streamsize>::max(), '\n');
			    caribuku(input, &jumlah, &pos);
			    cout << "JUMLAH : " << jumlah << endl;
			    break;
			    
			case 5:
			    tampilsiswa();
			    break;
			    
			case 6:
			    tampilbuku();
			    break;
			    
			case 7:
			    tampilpinjam();
			    break;
			    
			case 8:
			    pinjam();
			    break;
			    
			case 9:
			    mengembalikan();
			    break;
			    
			
			default:
			   cout<<"PILIHAN TIDAK ADA!\n";
			   break;
			}
			
		cout<<"MASIH LANJUT? ";
		cin>>lanjut;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
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
	system("clear");//membersihkan console log
	int opsi;
	
	cout<<"PERPUSTAKAAN JAYA MAJU\n";
	cout<<"=======================\n";
	cout<<"OPSI MENU : \n";
	cout<<"1. MENAMBAH SISWA"<<endl;
	cout<<"2. MENAMBAH BUKU"<<endl;
	cout<<"3. MENCARI SISWA"<<endl;
	cout<<"4. MENCARI BUKU"<<endl;
	cout<<"5. MENAMPILKAN SISWA"<<endl;
	cout<<"6. MENAMPILKAN BUKU"<<endl;
	cout<<"7. MENAMPILKAN PEMINJAMAN"<<endl;
	cout<<"8. PINJAM"<<endl;
	cout<<"9. MENGEMBALIKAN"<<endl;
	cout<<"10. EXIT"<<endl;
	cout<<"PILIHAN ANDA : ";
	cin>>opsi;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	return opsi;//mengembalikan nilai dari variabel opsi

}



void tambahsiswa(){
	fstream myfile;//deklarasi
	bool ketemu = false;
	
	myfile.open("siswa.txt", ios::out | ios::in);//membuka file dengan fungsi keluaran(menulis data) dan masukan(membaca data)
	
	if(myfile.is_open()){//kondisi jika file terbuka
		cout<<"data ditemukan, melanjutkan operasi"<<endl;
		myfile.close();
		//menutup file dan membukanya kembali dengan fungsi keluaran(menulis data) dan append/menambah data
		myfile.open("siswa.txt", ios::out | ios::app);
		}
	else{
		cout<<"data tidak ditemukan, membuat data baru..."<<endl;
		myfile.close();
		//menutup file lalu membukanya kembali dengan fungsi keluaran(menulis data) dan membuat&/menimpa
		myfile.open("siswa.txt", ios::out | ios::trunc);
		myfile<<left<<setw(6)<<"NIS"<<"|"<<setw(30)<<"NAMA"<<"|"<<setw(13)<<"KELAS"<<endl;
		
		}
		
		siswa tambah;
		while(true){
			cout<<"NIS (5 digit): ";
			cin>>tambah.nis;
			if(tambah.nis.length() == 5){
				break;
			}
			else{
				cout<<"TOLONG PERIKSA KEMBALI INPUTAN ANDA! "<<endl;
				}
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		ketemu = carisiswa(tambah.nis);
		
		if(ketemu == true){
			cout<<"NIS SUDAH TERDAFTAR!"<<endl;
		}
		else{
		cout<<"NAMA : ";
		getline(cin, tambah.nama);
		cout<<"KELAS : ";
		getline(cin, tambah.kelas);
		
		myfile <<left<<setw(6)<< tambah.nis <<"|"<<setw(30)<<tambah.nama<<"|"<<setw(13)<<tambah.kelas<<endl;
		}
	
	myfile.close();
	
}
	


bool carisiswa(string cari){
	
	ifstream myfile;
	string buffer, temp, nama, kelas;
	bool ketemu = false;
	
	myfile.open("siswa.txt");
	
	if(!myfile.is_open()){
		
		cout<<"DATA TIDAK DITEMUKAN SILAHKAN MEMBUAT DATA SISWA BARU!";
		
	}
	else{
		getline(myfile, buffer);
		
		while(!myfile.eof()){
			
			myfile >> temp;
			getline(myfile, buffer);
			
			if(temp == cari){
				ketemu = true;
				break;
			}
			
		}
		
		if(ketemu == true){
			buffer.erase(0,2);
			
			for(int i=0; i<30; i++){
				nama += buffer[i];
			}
			for(int i=30; i>0; i--){
				if(nama[i - 1] == ' '){
					nama.erase(nama.end() - 1);
				}
				else{
					break;
				}
			}
			
			buffer.erase(0,31);
			
			kelas = buffer;
			
			for(int i=13; i>0; i--){
				if(kelas[i - 1] == ' '){
					kelas.erase(kelas.end() - 1);
				}
				else{
					break;
				}
			}
			
			cout<<"NAMA : "<<nama<<endl<<"KELAS : "<<kelas<<endl;
			
		}
		else{
			ketemu = false;
		}
		
	}
	myfile.close();
	return ketemu;
	
}

void tambahbuku(){
	fstream myfile;
	string isbn, judul;
	int jumlah;
	buku tambah;
	tambah.jumlah = 0;
	
	myfile.open("buku.txt", ios::out | ios::in);
	
	if(myfile.is_open()){
		cout<<"data ditemukan, melanjutkan operasi"<<endl;
		myfile.close();
		myfile.open("buku.txt", ios::out | ios::in);
		}
	else{
		cout<<"data tidak ditemukan, membuat data baru..."<<endl;
		myfile.close();
		myfile.open("buku.txt", ios::out | ios::trunc);
		myfile<<left<<setw(6)<<"ISBN"<<"|"<<setw(30)<<"JUDUL"<<"|"<<setw(3)<<"JUMLAH"<<endl;
		
		}
		
		while(true){
			cout<<"ISBN(5 digit) : ";
			cin>>isbn;
			if(isbn.length() == 5){
				break;
			}
			else{
				cout<<"TOLONG PERIKSA INPUTAN ANDA!"<<endl;
			}
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		caribuku(isbn, &tambah.jumlah, &tambah.pos);
		
		if(tambah.jumlah > 0){
			cout<<"MASUKKAN JUMLAH TAMBAH : ";
			cin>>jumlah;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			jumlah += tambah.jumlah;
			myfile.seekp(tambah.pos + 38, ios::beg);
			myfile << left << setw(3) << jumlah;
		}
		else{
			myfile.seekp(0, ios::end);
		cout<<"JUDUL : ";
		getline(cin, judul);
		cout<<"JUMLAH : ";
		cin>>jumlah;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		myfile <<left<<setw(6)<<isbn <<"|"<<setw(30)<<judul<<"|"<<setw(3)<<jumlah<<endl;
		
		}
	
	myfile.close();
	
}


int caribuku(string cari, int* jumlah, int* pos){
	ifstream myfile;
	string buffer, temp, judul, isbn;
	int ketemu = 0;
	
	myfile.open("buku.txt", ios::in);
	
	if(!myfile.is_open()){
		cout<<"DATA TIDAK DITEMUKAN, SILAHKAN BUAT DATA BARU!"<<endl;
		myfile.close();
	}
	else{
		getline(myfile, buffer);
		
		while(!myfile.eof()){
			myfile>>temp;
			getline(myfile, buffer);
			if(temp == cari){
				//cout<<myfile.tellg();
				ketemu = 1;
				break;
			}
			
		}
		
		if(ketemu == 1){
			*pos = myfile.tellg();
			*pos -= 42;
			buffer.erase(0,2);
			
			for(int i=0; i<30; i++){
				judul += buffer[i];
			}
			for(int i=30; i>0; i--){
				if(judul[i - 1] == ' '){
					judul.erase(judul.end() - 1);
				}
				else{
					break;
				}
			}
			
			buffer.erase(0,31);
			
			isbn = temp;
			
			*jumlah = stoi(buffer);
			
			cout<<"JUDUL : "<<judul<<endl;
		}
		else{
			*jumlah = 0;
		}
		
		
	}
	myfile.close();
	
	return 0;
}

void tampilsiswa(){
	ifstream myfile;
	string hasil;
	
	myfile.open("siswa.txt");
	if(!myfile.is_open()){
		cout<<"DATA TIDAK DITEMUKAN, SILAHKAN BUAT DATA BARU!"<<endl;
	}
	else{
		while(!myfile.eof()){
			getline(myfile, hasil);
			cout<<hasil<<endl;
		}
		
	}
	
	myfile.close();
}

void tampilbuku(){
	ifstream myfile;
	string hasil;
	
	myfile.open("buku.txt");
	if(!myfile.is_open()){
		cout<<"DATA TIDAK DITEMUKAN, SILAHKAN BUAT DATA BARU!"<<endl;
	}
	else{
		while(!myfile.eof()){
			getline(myfile, hasil);
			cout<<hasil<<endl;
		}
		
	}
	
	myfile.close();
}

void pinjam(){
	fstream myfile;
	string nis, isbn, buffer, cari, salin;
	buku pinjam;
	bool siswa;
	int jumlahpinjam, ketemu = 0, temp, pos, max;
	
	myfile.open("pinjam.txt", ios::out | ios::in);
	if(!myfile.is_open()){
		myfile.close();
		myfile.open("pinjam.txt", ios::trunc | ios::out | ios::in);
		myfile << left << setw(6) << "NIS" << "|" << setw(6) << "ISBN" << "|" << setw(3) << "JUMLAH" << endl;
	}
	myfile.close();
	
	cout<<"BUKU YANG TERSEDIA : "<<endl;
	tampilbuku();
	
	cout<<"MASUKKAN NIS SISWA : ";
	cin>>nis;
	cout<<"MASUKKAN ISBN BUKU : ";
	cin>>isbn;
	cout<<"MASUKKAN JUMLAH BUKU : ";
	cin>>jumlahpinjam;
	
	siswa = carisiswa(nis);
	caribuku(isbn, &pinjam.jumlah, &pinjam.pos);
	cout<<"JUMLAH : "<< pinjam.jumlah << endl;
	
	if(siswa == true && pinjam.jumlah >= jumlahpinjam){
		pinjam.jumlah -= jumlahpinjam;
		
		myfile.open("buku.txt", ios::out | ios::in);
		myfile.seekp(pinjam.pos + 38);
		myfile << left << setw(3) << pinjam.jumlah;
		myfile.close();
		
		myfile.open("pinjam.txt", ios::out | ios::in);
		myfile.seekg(-2, ios::end);
		max = myfile.tellg();
		
		myfile.seekg(0, ios::beg);
		getline(myfile, buffer);
		while(!myfile.eof()){
			myfile >> cari;
			getline(myfile, buffer);
			
			if(cari == nis){
				ketemu = 1;
				break;
			}
		}
		
		if(ketemu == 0){
			myfile.close();
			myfile.open("pinjam.txt", ios::out | ios::in);
			myfile.seekp(0, ios::end);
			myfile << left << setw(6) << nis << "|" << setw(6) << isbn << "|" << setw(3) << jumlahpinjam << endl;
		}
		else{
			buffer.erase(0,2);
			cout<<"weee"<<endl;
			
			while(!myfile.eof()){
				buffer.erase(5, 9);
				cout<<buffer<<"i"<<endl;
				if(buffer == isbn){
					cout<<"weeee"<<endl;
					break;
				}
				if(myfile.tellp() >= max){
					ketemu = 0;
					pos = myfile.tellp();
					break;
				}
				myfile >> cari;
				if(cari == "-"){
					getline(myfile, buffer);
					buffer.erase(0,6);
				}
				else{
					myfile.seekp(-5, ios::cur);
					pos = myfile.tellp();
					ketemu = 0;
					break;
				}
				
			}
			
			if(ketemu == 0){
				while(!myfile.eof()){
					getline(myfile, buffer);
					salin += buffer + '\n';
				}
				myfile.close();
				myfile.open("pinjam.txt", ios::out | ios::in);
				
				myfile.seekp(pos, ios::beg);
				salin.erase(salin.end() - 1);
				myfile << left << setw(6) << "-" << "|" << setw(6) << isbn << "|" << setw(3) << jumlahpinjam << endl << salin;
			}
			else{
				myfile.seekp(-4, ios::cur);
				pos = myfile.tellp();
				myfile >> temp;
				
				jumlahpinjam += temp;
				myfile.seekp(pos, ios::beg);
				myfile << left << setw(3) << jumlahpinjam;
			}
			
			
		}
		
	}
	else{
		cout<<"SISWA ATAU BUKU BELUM TERDAFTAR ATAU TIDAK MENCUKUPI!"<<endl;
	}
	myfile.close();
	
}

void tampilpinjam(){
	ifstream myfile;
	string nis, isbn, buffer1;
	int buffer, buffer2, i=0, max;
	
	myfile.open("pinjam.txt");
	if(!myfile.is_open()){
		cout<<"DATA TIDAK DITEMUKAN, SILAHKAN BUAT DATA BARU!"<<endl;
	}
	else{
		myfile.seekg(-1, ios::end);
		max = myfile.tellg();
		myfile.seekg(1, ios::beg);
		getline(myfile, buffer1);
		while(!myfile.eof()){
			myfile >> nis;
			if(nis == "-"){
				myfile.seekg(6, ios::cur);
				myfile >> isbn;
			}
			else{
				myfile.seekg(2, ios::cur);
				carisiswa(nis);
			}
			
			myfile >> isbn;
			myfile.seekg(2, ios::cur);
			getline(myfile, buffer1);
			caribuku(isbn, &buffer, &buffer2);
			cout<<"JUMLAH : "<< buffer1 <<endl;
			if(myfile.tellg() >= max-2){
				break;
			}
		}
		
	}
	
	myfile.close();
}


void mengembalikan(){
	fstream myfile;
	buku kembali;
	string nis, isbn, cari, cari2, buffer;
	int jumlahkembali, jumlahbuku, pos;
	bool siswa = false;
	
	myfile.open("pinjam.txt", ios::out | ios::in);
	
	if(!myfile.is_open()){
		cout<<"DATA TIDAK DITEMUKAN, SILAHKAN BUAT BARU!"<<endl;
	}
	else{
		cout<<"MASUKKAN NIS SISWA : ";
		cin>>nis;
		cout<<"MASUKKAN ISBN BUKU : ";
		cin>>isbn;
		cout<<"MASUKKAN JUMLAH BUKU : ";
		cin>>jumlahkembali;
		
		getline(myfile, buffer);
		while(!myfile.eof()){
			myfile >> cari;
			if(cari == nis){
				siswa = true;
				break;
			}
			getline(myfile, buffer);
		}
		if(siswa == true){
		while(!myfile.eof()){
			myfile.seekg(2, ios::cur);
			myfile >> cari2;
			getline(myfile, buffer);
			
			if(cari2 == isbn){
				pos = myfile.tellg();
				myfile.seekg((pos-4), ios::beg);
				myfile>>jumlahbuku;
				break;
			}
			myfile >> cari;
			if(cari == "-"){
				myfile.seekg(4, ios::cur);
				continue;
			}
			else{
				jumlahbuku = 0;
				break;
			}
		}
		
		if(jumlahbuku >= jumlahkembali){
			myfile.close();
			myfile.open("pinjam.txt", ios::out | ios::in);
			
			myfile.seekp(pos - 4, ios::beg);
			jumlahbuku -= jumlahkembali;
			myfile << left << setw(3) << jumlahbuku;
			myfile.close();
			carisiswa(nis);
			caribuku(isbn, &kembali.jumlah, &kembali.pos);
			
			myfile.open("buku.txt", ios::out | ios::in);
			myfile.seekp(kembali.pos + 38);
			jumlahkembali += kembali.jumlah;
			myfile << left << setw(3) << jumlahkembali;
			
		}
		else{
			cout<<"JUMLAH TIDAK WAJAR ATAU BUKU TIDAK ADA!"<<endl;
		}
		
		}
		else{
			cout<<"SISWA TIDAK MEMINJAM!"<<endl;
		}
	}
	
	myfile.close();
}
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<math.h>
#include"console.h"
using namespace std;

struct kieungaythang{
	int ngay;
	int thang;
	int nam;
};
class sinhvien{
	public:
		int masv;
		string malop;
		string ngaythang;
		string hoten;
		kieungaythang ngaysinh;
		float diemtb;
		
		void nhap_ds(ifstream &filein, vector<sinhvien> &ds);
		void gi_file_hososinhvien(ofstream &fileout);
		sinhvien doc_thongtin(ifstream &filein);
};
void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}

void menu_tk(vector<sinhvien> ds);
void Menu(ifstream &filein, vector<sinhvien> ds);
void menusx(vector<sinhvien> ds);
void menu_sx(vector<sinhvien> ds, int n);
void menu_tim(vector<sinhvien> ds, int n);
void menutim(vector<sinhvien> ds);
void quay_lai(vector<sinhvien> ds);
void in_ds(vector<sinhvien> ds);
void khung_ds(int x, int y);
void lumangsv(ifstream &filein, vector<sinhvien> &d);
void hotro();
void ve_khung1(int x, int y);
void ve_khung(int x, int y);

bool chuanhoaKitu(string name) {
	int kt = 0;
	for (int t = 0; t < name.length() -1; t++) {
		if ((name[t] >= 65 && name[t] <= 90) || (name[t] >= 97 && name[t] <= 122) || name[t] == 32) {
		}
		else kt++;
	}
	if (kt == 0) return true;
	else return false;
}

void chuanhoaten(string &name){
	while(name[0] == 32){
		name.replace(0, 1, "");
	}
	if(name[0] >= 97)
	name[0] = name[0] - 32;
	for(int i = 0; i <name.length() -1; i++){
		while(name[i] == 32 && name[i +1] == 32)
		name.replace(i, 1, "");
		if(name[i] == 32 && name[i +1] >= 97)
		name[i +1] = name[i + 1] - 32;
	}
	if(name[name.length() - 1] == 32)
	name.replace(name.length() - 1, 1, "");
}

bool chuanhoaNgaySinh(int d, int m, int y) {
	int k = 0;
	if ( y >= 1900 && y <= 2016){
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
	{
		if (d > 31 || d < 0)   k++;
	}
	else
		if (m == 4 || m == 6 || m == 9 || m == 11)
		{
			if (d > 30 || d < 0) k++;
		}
		else
			if (m == 2)
			{
				if (y % 4 == 0)
				{
					if (d > 29 || d < 0) k++;
				}
				else {
					if (d > 28 || d < 0) k++;
				}
			}
			else k++;

			if (k == 0) return true;
			else return false;
	}
}

bool chuanhoaDiem(float x) {
	if (x >= 0 && x <= 10) return true;
	else return false;

}

void sinhvien::gi_file_hososinhvien(ofstream &fileout){
	fileout<<malop<<", "<<masv<<" "<<hoten<<", "<<diemtb<<" "<<ngaysinh.ngay<<"/"<<ngaysinh.thang<<"/"<<ngaysinh.nam<<endl;
}

sinhvien sinhvien::doc_thongtin(ifstream &filein){
	sinhvien a;	
	getline(filein, a.malop, ',');
	filein >> a.masv;
	getline(filein, a.hoten, ',');
	filein >> a.diemtb;
	getline(filein, a.ngaythang);
	return a;
}
void lumangsv(ifstream &filein, vector<sinhvien> &d){
	sinhvien sv;
	while(filein.eof() == false){
			d.push_back(sv.doc_thongtin(filein));
		}
}

void sx_chon_masv(vector<sinhvien> &a){
	int n = a.size();
	for(int i = 0; i < n - 2; i++){
		int min = i;
		for(int j = i + 1; j < n -1 ; j++ ){
		if(a[j].masv < a[min].masv)
		min = j;
		}
		if(i != min){
			sinhvien tam = a[i];
			a[i] = a[min];
			a[min] = tam;
		}
	}
}
void sx_chon_diem(vector<sinhvien> &a){
	int n = a.size();
	for(int i = 0; i < n - 2; i++){
		int min = i;
		for(int j = i + 1; j < n -1 ; j++ ){
		if(a[j].diemtb < a[min].diemtb)
		min = j;
		}
		if(i != min){
			sinhvien tam = a[i];
			a[i] = a[min];
			a[min] = tam;
		}
	}
}
string nam(string b){
	string a;
	for(int i = b.length() - 1; i >=0 ; i--)
	if(b[i] >= '0' && b[i] <= '9')
	a.insert(a.begin() + 0, b[i]);
	else
	break;
	return a;
}
string thang(string b){
	string a;
	for(int i = b.length() - 6; i >=0 ; i--)
	if(b[i] >= '0' && b[i] <= '9')
	a.insert(a.begin() + 0, b[i]);
	else
	break;
	return a;
}
string ngay(string b){
	string a;
	for(int i =1; i<3 ; i++)
	if(b[i] >= '0' && b[i] <= '9')
	a.push_back(b[i]);
	else
	break;
	return a;
}
void sx_chon_date(vector<sinhvien> &a){
	int i, min, j, n = a.size();
	for( i = 0; i < n - 2; i++){
		min = i;
		for(j = i + 1; j < n -1 ; j++ ){
			if( nam(a[min].ngaythang) > nam(a[j].ngaythang) )
			min = j;
			else if( nam(a[min].ngaythang) == nam(a[j].ngaythang) ){
				if( thang(a[min].ngaythang) > thang(a[j].ngaythang) )
				min = j;
				else if( thang(a[min].ngaythang) == thang(a[j].ngaythang) ){
				if( ngay(a[min].ngaythang) > ngay(a[j].ngaythang) )
					min = j;
				}
			}
		}
		
		if(i != min){
			sinhvien tam = a[i];
			a[i] = a[min];
			a[min] = tam;
		}
	}
}

string ten(string b){
	string a;
	for(int i = b.length() - 1; i >=0 ; i--){
		a.insert(a.begin() + 0, b[i]);
		if(b[i-1] == 32 )
		break;
	}
	return a;
}
string ten_c(string b){
	string a;
	for(int i = b.length() - 1; i >=0 ; i--){
		if(b[i-1] == 32 ){
			a.push_back(b[i]);
			break;
		}
	}
	return a;
}
string dem(string f){
	string h;
	int t = 0;
	for(int i = 1 ; i < f.length() -1 ; i++){
		if(f[i] == 32 ){
			t = t +1;
		}
		if(t == 1){
			h.push_back(f[i]);
		}
		if(t > 1)
		break;
	}
	h.replace(0, 1, "");
	return h;
}
string dem_c(string f){
	string h;
	for(int i = 1 ; i < f.length() - 1; i++){
		if(f[i] == 32 ){
			h.push_back(f[i+1]);
			break;
		}
	}
	return h;
}
string ho(string f){
	string d;
	for(int i =1; i < 9; i++){
		d.push_back(f[i]);
		if(f[i +1] == 32)
		break;
	}
	return d;
}
string ho_c(string f){
	string h;
	h.push_back(f[1]);
	return h;
}
string lop_c(string a){
	string b;
	b.push_back(a[2]);
	return b;
}
void sx_chon_ten(vector<sinhvien> &d){
	int i, j, min, n = d.size();
	for(i = 0; i < n -2 ; i++){
		min = i;
		for(j = i+1 ; j < n -1 ; j++){
			if(ten(d[min].hoten) > ten(d[j].hoten))
			min = j;
			else if(ten(d[min].hoten) == ten(d[j].hoten)){
				if(dem(d[min].hoten) > dem(d[j].hoten))
				min = j;
				else if( dem(d[min].hoten) == dem(d[j].hoten) ){
					if(ho(d[min].hoten) > ho(d[j].hoten))
					min = j;
				}
			}
		}
		
		if(min != i){
			sinhvien tam = d[i];
			d[i] = d[min];
			d[min] = tam;
		}
	}
}

void sx_chon_malop(vector<sinhvien> &d){
	int i, j, min, n = d.size();
	for(i = 0; i < n -2 ; i++ ){
		min = i;
		for( j = i + 1; j < n -1; j ++){
			if(d[min].malop > d[j].malop)
			min = j;
			else if(d[min].malop == d[j].malop){
				if(ten(d[min].hoten) > ten(d[j].hoten))
				min = j;
				else if(ten(d[min].hoten) == ten(d[j].hoten)){
					if(dem(d[min].hoten) > dem(d[j].hoten))
					min = j;
					else if( dem(d[min].hoten) == dem(d[j].hoten) ){
						if(ho(d[min].hoten) > ho(d[j].hoten))
						min = j;
						else if( ho(d[min].hoten) == ho(d[j].hoten) ){
							if( nam(d[min].ngaythang) > nam(d[j].ngaythang) )
							min = j;
							else if( nam(d[min].ngaythang) == nam(d[j].ngaythang) ){
								if( thang(d[min].ngaythang) > thang(d[j].ngaythang) )
								min = j;
								else if( thang(d[min].ngaythang) == thang(d[j].ngaythang) ){
									if( ngay(d[min].ngaythang) > ngay(d[j].ngaythang) )
									min = j;
								}
							}
						}
					}
				}
			}
		}
		if(min != i){
			sinhvien tam = d[i];
			d[i] = d[min];
			d[min] = tam;
		}
	}
}

void sx_nb_masv(vector<sinhvien> &a){
	int n = a.size();
	for(int i = 0; i < n - 2; i++){
		for(int j = n -2 ; j >i ; j-- )
			if(a[j].masv < a[j - 1].masv){
				swap(a[j], a[j - 1]);
			}
	}
}

void sx_nb_date(vector<sinhvien> &a){
	int i, j, n = a.size();
	for( i = 0; i < n - 2; i++)
		for(j = n-2; j > i; j-- ){
			if( nam(a[j - 1].ngaythang) > nam(a[j].ngaythang) )
			swap(a[j -1], a[j]);
			else if( nam(a[j - 1].ngaythang) == nam(a[j].ngaythang) ){
				if( thang(a[j - 1].ngaythang) > thang(a[j].ngaythang) )
				swap(a[j - 1], a[j]);
				else if( thang(a[j -1].ngaythang) == thang(a[j].ngaythang) ){
					if( ngay(a[j - 1].ngaythang) > ngay(a[j].ngaythang) )
					swap(a[j - 1], a[j]);
				}
			}
		}
}

void sx_nb_ten(vector<sinhvien> &d){
	int i, j, n = d.size();
	for(i = 0; i < n -2 ; i++)
		for(j = n -2; j > i; j --){
			if(ten(d[j - 1].hoten) > ten(d[j].hoten))
			swap(d[j - 1], d[j]);
			else if(ten(d[j - 1].hoten) == ten(d[j].hoten)){
				if(dem(d[j - 1].hoten) > dem(d[j].hoten))
				swap(d[j - 1], d[j]);
				else if( dem(d[j - 1].hoten) == dem(d[j].hoten) ){
					if(ho(d[j - 1].hoten) > ho(d[j].hoten))
					swap(d[j - 1], d[j]);
				}
			}
		}
}

void sx_nb_malop(vector<sinhvien> &d){
	int i, j, n = d.size();
	for(i = 0; i < n -2 ; i++ )
		for( j = n-2; j > i; j--){
			if(d[j - 1].malop > d[j].malop)
			swap(d[j -1], d[j]);
			else if(d[j - 1].malop == d[j].malop){
				if(ten(d[j - 1].hoten) > ten(d[j].hoten))
				swap(d[j -1], d[j]);
				else if(ten(d[j - 1].hoten) == ten(d[j].hoten)){
					if(dem(d[j - 1].hoten) > dem(d[j].hoten))
					swap(d[j -1], d[j]);
					else if( dem(d[j - 1].hoten) == dem(d[j].hoten) ){
						if(ho(d[j - 1].hoten) > ho(d[j].hoten))
						swap(d[j -1], d[j]);
						else if( ho(d[j - 1].hoten) == ho(d[j].hoten) ){
							if( nam(d[j - 1].ngaythang) > nam(d[j].ngaythang) )
							swap(d[j -1], d[j]);
							else if( nam(d[j - 1].ngaythang) == nam(d[j].ngaythang) ){
								if( thang(d[j - 1].ngaythang) > thang(d[j].ngaythang) )
								swap(d[j -1], d[j]);
								else if( thang(d[j - 1].ngaythang) == thang(d[j].ngaythang) ){
									if( ngay(d[j - 1].ngaythang) > ngay(d[j].ngaythang) )
									swap(d[j -1], d[j]);
								}
							}
						}
					}
				}
			}
		}
}

void sx_chen_masv(vector<sinhvien> &a){
	sinhvien tam;
	int j;
	for(int i = 1; i<a.size() -1 ; i++ ){
		tam = a[i];
		j = i - 1;
		while(j >= 0 && tam.masv < a[j].masv){
			a[j + 1] = a [j];
			j = j - 1;
		}
		a[j + 1] = tam;
	}
}

void sx_chen_date(vector<sinhvien> &a){
	sinhvien tam;
	int j;
	for(int i = 1; i<a.size() -1 ; i++ ){
		tam = a[i];
		j = i - 1;
		while(j >= 0 && nam(tam.ngaythang) < nam(a[j].ngaythang)){
			a[j + 1] = a [j];
			j = j - 1;
		}
		while(j >= 0 && nam(tam.ngaythang) == nam(a[j].ngaythang) && thang(tam.ngaythang) < thang(a[j].ngaythang) ){
			a[j + 1] = a[j];
			j = j -1;
		}
		while(j >= 0 && nam(tam.ngaythang) == nam(a[j].ngaythang) && thang(tam.ngaythang) == thang(a[j].ngaythang) && ngay(tam.ngaythang) < ngay(a[j].ngaythang) ){
			a[j + 1] = a[j];
			j = j -1;
		}
		a[j + 1] = tam;
	}
}

void sx_chen_ten(vector<sinhvien> &a){
	sinhvien tam;
	int j;
	for(int i = 1; i<a.size()-1 ; i++ ){
		tam = a[i];
		j = i - 1;
		while(j >= 0 && ten(tam.hoten) < ten(a[j].hoten)){
			a[j + 1] = a [j];
			j = j - 1;
		}
		while(j >= 0 && ten(tam.hoten) == ten(a[j].hoten) && dem(tam.hoten) < dem(a[j].hoten) ){
			a[j + 1] = a[j];
			j = j -1;
		}
		while(j >= 0 && ten(tam.hoten) == ten(a[j].hoten) && dem(tam.hoten) == dem(a[j].hoten) && ho(tam.hoten) < ho(a[j].hoten) ){
			a[j + 1] = a[j];
			j = j -1;
		}
		a[j + 1] = tam;
	}
}

void sx_chen_malop(vector<sinhvien> &a){
	sinhvien tam;
	int j;
	for(int i = 1; i<a.size()-1 ; i++ ){
		tam = a[i];
		j = i - 1;
		while(j >= 0 && tam.malop < a[j].malop){
			a[j + 1] = a [j];
			j = j - 1;
		}
		while(j >= 0 && tam.malop == a[j].malop && ten(tam.hoten) < ten(a[j].hoten)){
			a[j + 1] = a [j];
			j = j - 1;
		}
		while(j >= 0 && tam.malop == a[j].malop && ten(tam.hoten) == ten(a[j].hoten) && dem(tam.hoten) < dem(a[j].hoten) ){
			a[j + 1] = a[j];
			j = j -1;
		}
		while(j >= 0 && tam.malop == a[j].malop && ten(tam.hoten) == ten(a[j].hoten) && dem(tam.hoten) == dem(a[j].hoten) && ho(tam.hoten) < ho(a[j].hoten) ){
			a[j + 1] = a[j];
			j = j -1;
		}
		while(j >= 0 && tam.malop == a[j].malop && ten(tam.hoten) == ten(a[j].hoten) && dem(tam.hoten) == dem(a[j].hoten) && ho(tam.hoten) == ho(a[j].hoten) && nam(tam.ngaythang) < nam(a[j].ngaythang)){
			a[j + 1] = a [j];
			j = j - 1;
		}
		while(j >= 0 && tam.malop == a[j].malop && ten(tam.hoten) == ten(a[j].hoten) && dem(tam.hoten) == dem(a[j].hoten) && ho(tam.hoten) == ho(a[j].hoten) && nam(tam.ngaythang) == nam(a[j].ngaythang) && thang(tam.ngaythang) < thang(a[j].ngaythang) ){
			a[j + 1] = a[j];
			j = j -1;
		}
		while(j >= 0 && tam.malop == a[j].malop && ten(tam.hoten) == ten(a[j].hoten) && dem(tam.hoten) == dem(a[j].hoten) && ho(tam.hoten) == ho(a[j].hoten) && nam(tam.ngaythang) == nam(a[j].ngaythang) && thang(tam.ngaythang) == thang(a[j].ngaythang) && ngay(tam.ngaythang) < ngay(a[j].ngaythang) ){
			a[j + 1] = a[j];
			j = j -1;
		}
		a[j + 1] = tam;
	}
}

void sx_nhanh_masv(vector<sinhvien> &a, int left, int right){
	int i = left, j = right;
	sinhvien x = a[(left + right)/ 2];
	do{
		while(a[i].masv < x.masv && i<right) i++;
 		while(a[j].masv > x.masv && j > left) j--;
    	if( i <= j){
    		swap(a[i], a[j]);
        	i++; j--;
		}	
	}while(i <= j);
	if (left<j) sx_nhanh_masv(a,left,j);
	if (i<right) sx_nhanh_masv(a,i,right);
}
int ep_kieu(string s){
	int a = 0, n = s.size();
	int mu = n - 1;
	for(int i = 0; i < n; i++){
		a = a + (s[i] - '0')*pow(10,mu);
		mu--;
	}
	return a;
}
void tk_tt_ten(vector<sinhvien> d){
	system("cls");
	ShowCur(true);
	string t;
	cout<<"\n\t DANH SACH TIM DUOC ";
	khung_ds(2,3);
	gotoXY(4,4); cout<<"Stt";
	gotoXY(8,4); cout<<"Ma lop";
	gotoXY(17,4); cout<<"Ma sv";
	gotoXY(30,4); cout<<"Ho va ten";
	gotoXY(49,4); cout<<"Ngay sinh";
	gotoXY(60,4); cout<<"DTBTL";
	gotoXY(80,2); cout<<"Tim kiem theo Ho ten";
	fflush(stdin);
	gotoXY(80,3); cout<<"Nhap vao ho ten can tim: ";
	ve_khung(80,4); 
	gotoXY(81,5); getline(cin,t);
	int j = 0, n = d.size();
	for(int i =0; i < n -1; i++){
		if(t == d[i].hoten ||t == ten_c(d[i].hoten) || t == dem_c(d[i].hoten) || t == ho_c(d[i].hoten) || t == ten(d[i].hoten) || t == dem(d[i].hoten) || t == ho(d[i].hoten)){
			khung_ds(2,6+3*j);
			gotoXY(5,7+3*j); cout<<j+1;
			gotoXY(9,7+3*j); cout<<d[i].malop;
			gotoXY(16,7+3*j); cout<<d[i].masv;
			gotoXY(25,7+3*j); cout<<d[i].hoten;
			gotoXY(48,7+3*j); cout<<d[i].ngaythang;
			gotoXY(62,7+3*j); cout<<d[i].diemtb;
			j++;
		}
	}
	quay_lai(d);
}

void tk_tt_malop(vector<sinhvien> d){
	system("cls");
	ShowCur(true);
	string t;
	cout<<"\n\t DANH SACH TIM DUOC ";
	khung_ds(2,3);
	gotoXY(4,4); cout<<"Stt";
	gotoXY(8,4); cout<<"Ma lop";
	gotoXY(17,4); cout<<"Ma sv";
	gotoXY(30,4); cout<<"Ho va ten";
	gotoXY(49,4); cout<<"Ngay sinh";
	gotoXY(60,4); cout<<"DTBTL";
	gotoXY(80,2); cout<<"Tim kiem theo Ma lop";
	fflush(stdin);
	gotoXY(80,3); cout<<"Nhap vao ma lop can tim: ";
	ve_khung(80,4); 
	gotoXY(81,5); getline(cin,t);
	
	int n = d.size();
	int j = 0;
	for(int i =0; i < n -1; i++){
		if(t == d[i].malop || t == lop_c(d[i].malop)){
			khung_ds(2,6+3*j);
			gotoXY(5,7+3*j); cout<<j+1;
			gotoXY(9,7+3*j); cout<<d[i].malop;
			gotoXY(16,7+3*j); cout<<d[i].masv;
			gotoXY(25,7+3*j); cout<<d[i].hoten;
			gotoXY(48,7+3*j); cout<<d[i].ngaythang;
			gotoXY(62,7+3*j); cout<<d[i].diemtb;
			j++;
		}	
	}
	quay_lai(d);
}

void tk_tt_ngaysinh(vector<sinhvien> d){
	system("cls");
	ShowCur(true);
	string t;
	cout<<"\n\t DANH SACH TIM DUOC ";
	khung_ds(2,3);
	gotoXY(4,4); cout<<"Stt";
	gotoXY(8,4); cout<<"Ma lop";
	gotoXY(17,4); cout<<"Ma sv";
	gotoXY(30,4); cout<<"Ho va ten";
	gotoXY(49,4); cout<<"Ngay sinh";
	gotoXY(60,4); cout<<"DTBTL";
	gotoXY(80,2); cout<<"Tim kiem theo Ngay sinh";
	fflush(stdin);
	gotoXY(80,3); cout<<"Nhap vao ngay sinh can tim: ";
	ve_khung(80,4); 
	gotoXY(81,5); getline(cin,t);
	int j = 0, n = d.size();
	for(int i =0; i < n -1; i++){
		if(t == d[i].ngaythang || t == nam(d[i].ngaythang) || t == thang(d[i].ngaythang) || t == ngay(d[i].ngaythang)){
			khung_ds(2,6+3*j);
			gotoXY(5,7+3*j); cout<<j+1;
			gotoXY(9,7+3*j); cout<<d[i].malop;
			gotoXY(16,7+3*j); cout<<d[i].masv;
			gotoXY(25,7+3*j); cout<<d[i].hoten;
			gotoXY(48,7+3*j); cout<<d[i].ngaythang;
			gotoXY(62,7+3*j); cout<<d[i].diemtb;
			j++;
		}	
	}
	quay_lai(d);
}

void tk_tt_masv(vector<sinhvien> d){
	system("cls");
	ShowCur(true);
	int t;
	cout<<"\n\t DANH SACH TIM DUOC ";
	khung_ds(2,3);
	gotoXY(4,4); cout<<"Stt";
	gotoXY(8,4); cout<<"Ma lop";
	gotoXY(17,4); cout<<"Ma sv";
	gotoXY(30,4); cout<<"Ho va ten";
	gotoXY(49,4); cout<<"Ngay sinh";
	gotoXY(60,4); cout<<"DTBTL";
	gotoXY(80,2); cout<<"Tim kiem theo Ma sv";
	gotoXY(80,3); cout<<"Nhap vao ma sv can tim: ";
	ve_khung(80,4); 
	gotoXY(81,5); cin>>t;
	int n = d.size();
	int j = 0;
	for(int i =0; i < n -1; i++){
		if(t == d[i].masv){
			khung_ds(2,6+3*j);
			gotoXY(5,7+3*j); cout<<j+1;
			gotoXY(9,7+3*j); cout<<d[i].malop;
			gotoXY(16,7+3*j); cout<<d[i].masv;
			gotoXY(25,7+3*j); cout<<d[i].hoten;
			gotoXY(48,7+3*j); cout<<d[i].ngaythang;
			gotoXY(62,7+3*j); cout<<d[i].diemtb;
			j++;
		}	
	}
	quay_lai(d);
}

void tk_tt_diem(vector<sinhvien> d){
	system("cls");
	ShowCur(true);
	float t;
	cout<<"\n\t DANH SACH TIM DUOC ";
	khung_ds(2,3);
	gotoXY(4,4); cout<<"Stt";
	gotoXY(8,4); cout<<"Ma lop";
	gotoXY(17,4); cout<<"Ma sv";
	gotoXY(30,4); cout<<"Ho va ten";
	gotoXY(49,4); cout<<"Ngay sinh";
	gotoXY(60,4); cout<<"DTBTL";
	gotoXY(80,2); cout<<"Tim kiem theo DTBTL";
	gotoXY(80,3); cout<<"Nhap vao diem can tim: ";
	ve_khung(80,4); 
	gotoXY(81,5); cin>>t;
	int j = 0, n = d.size();
	for(int i =0; i < n -1; i++){
		if(t == d[i].diemtb){
			khung_ds(2,6+3*j);
			gotoXY(5,7+3*j); cout<<j+1;
			gotoXY(9,7+3*j); cout<<d[i].malop;
			gotoXY(16,7+3*j); cout<<d[i].masv;
			gotoXY(25,7+3*j); cout<<d[i].hoten;
			gotoXY(48,7+3*j); cout<<d[i].ngaythang;
			gotoXY(62,7+3*j); cout<<d[i].diemtb;
			j++;
		}	
	}
	quay_lai(d);
}

void tk_tt_batky(vector<sinhvien> d){
	system("cls");
	ShowCur(true);
	string t;
	cout<<"\n\t DANH SACH TIM DUOC ";
	khung_ds(2,3);
	gotoXY(4,4); cout<<"Stt";
	gotoXY(8,4); cout<<"Ma lop";
	gotoXY(17,4); cout<<"Ma sv";
	gotoXY(30,4); cout<<"Ho va ten";
	gotoXY(49,4); cout<<"Ngay sinh";
	gotoXY(60,4); cout<<"DTBTL";
	
	gotoXY(80,2); cout<<"Tim kiem Bat ky";
	fflush(stdin);
	gotoXY(80,3); cout<<"Nhap tu can tim: ";
	ve_khung(80,4); 
	gotoXY(81,5); getline(cin,t);
	
	int j = 0, n = d.size();
	int t1 = ep_kieu(t);
	for(int i =0; i < n -1; i++){
		if(t1 == d[i].diemtb ||t1 == d[i].masv ||t == ten_c(d[i].hoten) || t == dem_c(d[i].hoten) || t == ho_c(d[i].hoten) || t == lop_c(d[i].malop) || t == ten(d[i].hoten) || t == dem(d[i].hoten) || t == ho(d[i].hoten) || t == d[i].malop || t == d[i].hoten || t == d[i].ngaythang || t == nam(d[i].ngaythang) || t == thang(d[i].ngaythang) || t == ngay(d[i].ngaythang)){
			khung_ds(2,6+3*j);
			gotoXY(5,7+3*j); cout<<j+1;
			gotoXY(9,7+3*j); cout<<d[i].malop;
			gotoXY(16,7+3*j); cout<<d[i].masv;
			gotoXY(25,7+3*j); cout<<d[i].hoten;
			gotoXY(48,7+3*j); cout<<d[i].ngaythang;
			gotoXY(62,7+3*j); cout<<d[i].diemtb;
			j++;
		}	
	}
	
	quay_lai(d);
}

void tk_np_masv(vector<sinhvien> d){
	system("cls");
	ShowCur(true);
	int g, t = 0, p = d.size() - 2;
	sx_chon_masv(d);
	int m;
	cout<<"\n\t DANH SACH TIM DUOC ";
	khung_ds(2,3);
	gotoXY(4,4); cout<<"Stt";
	gotoXY(8,4); cout<<"Ma lop";
	gotoXY(17,4); cout<<"Ma sv";
	gotoXY(30,4); cout<<"Ho va ten";
	gotoXY(49,4); cout<<"Ngay sinh";
	gotoXY(60,4); cout<<"DTBTL";
	gotoXY(80,2); cout<<"Tim kiem theo Ma sv";
	gotoXY(80,3); cout<<"Nhap vao ma sv can tim: ";
	ve_khung(80,4); 
	gotoXY(81,5); cin>>m;
	while(t <= p){
		g = (t + p)/2;
		if(m < d[g].masv) p = g -1;
		else if(m > d[g].masv) t = g +1;
		else{
			khung_ds(2,6);
			gotoXY(5,7); cout<<1;
			gotoXY(9,7); cout<<d[g].malop;
			gotoXY(16,7); cout<<d[g].masv;
			gotoXY(25,7); cout<<d[g].hoten;
			gotoXY(48,7); cout<<d[g].ngaythang;
			gotoXY(62,7); cout<<d[g].diemtb;
			break;
		}
	}
	quay_lai(d);
}
void tk_np_diem(vector<sinhvien> d){
	system("cls");
	ShowCur(true);
	int g, t = 0, p = d.size() - 2;
	float m;
	sx_chon_diem(d);
	cout<<"\n\t DANH SACH TIM DUOC ";
	khung_ds(2,3);
	gotoXY(4,4); cout<<"Stt";
	gotoXY(8,4); cout<<"Ma lop";
	gotoXY(17,4); cout<<"Ma sv";
	gotoXY(30,4); cout<<"Ho va ten";
	gotoXY(49,4); cout<<"Ngay sinh";
	gotoXY(60,4); cout<<"DTBTL";
	gotoXY(80,2); cout<<"Tim kiem theo DTBTL";
	gotoXY(80,3); cout<<"Nhap vao diem can tim: ";
	ve_khung(80,4); 
	gotoXY(81,5); cin>>m;
	while(t <= p){
		g = (t + p)/2;
		if(m < d[g].diemtb) p = g -1;
		else if(m > d[g].diemtb) t = g +1;
		else{
			int j = 0, dem = g;
			while(d[g].diemtb == m && g < (d.size() - 1)){
				khung_ds(2,6+3*j);
				gotoXY(5,7+3*j); cout<<j+1;
				gotoXY(9,7+3*j); cout<<d[g].malop;
				gotoXY(16,7+3*j); cout<<d[g].masv;
				gotoXY(25,7+3*j); cout<<d[g].hoten;
				gotoXY(48,7+3*j); cout<<d[g].ngaythang;
				gotoXY(62,7+3*j); cout<<d[g].diemtb;
				g++;
				j++;
			}
			g = dem -1;
			while(d[g].diemtb == m && g >= 0 ){
				khung_ds(2,6+3*j);
				gotoXY(5,7+3*j); cout<<j+1;
				gotoXY(9,7+3*j); cout<<d[g].malop;
				gotoXY(16,7+3*j); cout<<d[g].masv;
				gotoXY(25,7+3*j); cout<<d[g].hoten;
				gotoXY(48,7+3*j); cout<<d[g].ngaythang;
				gotoXY(62,7+3*j); cout<<d[g].diemtb;
				g--;
				j++;
			}
			break;
		}
	}
	quay_lai(d);
}

void tk_sl_sv(vector<sinhvien> ds){
	int a =0, b = 0, c = 0, d = 0, t, n = ds.size() -1;
	for(int i = 0; i < n; i++){
		if(ds[i].malop == "15A")
		a++;
		if(ds[i].malop == "15B")
		b++;
		if(ds[i].malop == "15C")
		c++;
		if(ds[i].malop == "15D")
		d++;
	}
	t = a + b + c + d;
	cout<<"\tSO LUONG SINH VIEN THEO TUNG LOP"<<endl;
	cout<<"\t ______________________________"<<endl;
	cout<<"\t|    Ten lop    | So sinh vien |"<<endl;
	cout<<"\t|_______________|______________|"<<endl;
	cout<<"\t|     15A       |"<<setw(14)<<right<<a<<"|"<<endl;
	cout<<"\t|_______________|______________|"<<endl;
	cout<<"\t|     15B       |"<<setw(14)<<right<<b<<"|"<<endl;
	cout<<"\t|_______________|______________|"<<endl;
	cout<<"\t|     15C       |"<<setw(14)<<right<<c<<"|"<<endl;
	cout<<"\t|_______________|______________|"<<endl;
	cout<<"\t|     15D       |"<<setw(14)<<right<<d<<"|"<<endl;
	cout<<"\t|_______________|______________|"<<endl;
	cout<<"\t|     TONG      |"<<setw(14)<<right<<t<<"|"<<endl;
	cout<<"\t|_______________|______________|"<<endl;
	quay_lai(ds);
}

void quay_lai(vector<sinhvien> ds){
	char c;
	ifstream filein;
	filein.open("data.txt", ios_base::in);
	TextColor(4);
	gotoXY(85,10);
	cout<<"<< Ve MENU CHINH";
	do{
		c = getch();
		switch(c){
			case 75:
			case 13:
				system("cls");
				Menu(filein, ds);
				break;
		}
	}while(c != 27);
}
void tk_kqht_sv(vector<sinhvien> ds){
	int ay = 0, atb = 0, ak = 0, ag = 0, ax = 0, at, by = 0, btb = 0, bk = 0, bg = 0, bx = 0, bt, cy = 0, ctb = 0, ck = 0, cg = 0, cx = 0, ct, dy = 0, dtb = 0, dk = 0, dg = 0, dx = 0, dt, n = ds.size() -1;
	for(int i = 0; i < n; i++){
		if(ds[i].malop == "15A"){
			if(ds[i].diemtb < 5) ay++;
			else if(ds[i].diemtb < 6.5) atb++;
			else if(ds[i].diemtb < 8) ak++;
			else if(ds[i].diemtb < 9) ag++;
			else ax++;
		}
		if(ds[i].malop == "15B"){
			if(ds[i].diemtb < 5) by++;
			else if(ds[i].diemtb < 6.5) btb++;
			else if(ds[i].diemtb < 8) bk++;
			else if(ds[i].diemtb < 9) bg++;
			else bx++;
		}
		if(ds[i].malop == "15C"){
			if(ds[i].diemtb < 5) cy++;
			else if(ds[i].diemtb < 6.5) ctb++;
			else if(ds[i].diemtb < 8) ck++;
			else if(ds[i].diemtb < 9) cg++;
			else cx++;
		}
		if(ds[i].malop == "15D"){
			if(ds[i].diemtb < 5) dy++;
			else if(ds[i].diemtb < 6.5) dtb++;
			else if(ds[i].diemtb < 8) dk++;
			else if(ds[i].diemtb < 9) dg++;
			else dx++;
		}
	}
	at = ay + atb + ak + ag + ax; bt = by + btb + bk + bg + bx; ct = cy + ctb + ck + cg + cx; dt = dy + dtb + dk + dg + dx;
	float pay, patb, pak, pag, pax, pby, pbtb, pbk, pbg, pbx, pcy, pctb, pck, pcg, pcx, pdy, pdtb, pdk, pdg, pdx;
	pay = (float)ay/at*100; patb = (float)atb/at*100; pak = (float)ak/at*100; pag = (float)ag/at*100; pax = (float)ax/at*100;
	pby = (float)by/bt*100; pbtb = (float)btb/bt*100; pbk = (float)bk/bt*100; pbg = (float)bg/bt*100; pbx = (float)bx/bt*100;
	pcy = (float)cy/ct*100; pctb = (float)ctb/ct*100; pck = (float)ck/ct*100; pcg = (float)cg/ct*100; pcx = (float)cx/ct*100;
	pdy = (float)dy/dt*100; pdtb = (float)dtb/dt*100; pdk = (float)dk/dt*100; pdg = (float)dg/dt*100; pdx = (float)dx/dt*100;
	int y, tb, k, g, xs, t;
	y = ay + by + cy + dy; tb = atb + btb + ctb + dtb; k = ak + bk + ck + dk; g = ag + bg + cg + dg; xs = ax + bx + cx + dx;
	t = y + tb + k + g + xs;
	float py, ptb, pk, pg, pxs;
	py = (float)y/t*100; ptb = (float)tb/t*100; pk = (float)k/t*100; pg = (float)g/t*100; pxs = (float)xs/t*100;
	
	cout<<"\t\t\tTHONG KE KET QUA HOC TAP CUA SINH VIEN"<<endl;
	cout<<"\t _______________________________________________________________"<<endl;
	cout<<"\t|        | Xuat sac |   Gioi   |   Kha    |Trung binh|   Yeu    |"<<endl;
	cout<<"\t| Ma Lop |__________|__________|__________|__________|__________|"<<endl;
	cout<<"\t|        | SL |  %  | SL |  %  | SL |  %  | SL |  %  | SL |  %  |"<<endl;
	cout<<"\t|________|____|_____|____|_____|____|_____|____|_____|____|_____|"<<endl;
	cout<<"\t|  15A   |"<<setw(4)<<right<<ax<<"|"<<setw(5)<<right<<setprecision(2)<<pax<<"|"<<setw(4)<<right<<ag<<"|"<<setw(5)<<right<<setprecision(2)<<pag<<"|"<<setw(4)<<right<<ak<<"|"<<setw(5)<<right<<setprecision(2)<<pak<<"|"<<setw(4)<<right<<atb<<"|"<<setw(5)<<right<<setprecision(2)<<patb<<"|"<<setw(4)<<right<<ay<<"|"<<setw(5)<<right<<setprecision(2)<<pay<<"|"<<endl;    
	cout<<"\t|________|____|_____|____|_____|____|_____|____|_____|____|_____|"<<endl;
	cout<<"\t|  15B   |"<<setw(4)<<right<<bx<<"|"<<setw(5)<<right<<setprecision(2)<<pbx<<"|"<<setw(4)<<right<<bg<<"|"<<setw(5)<<right<<setprecision(2)<<pbg<<"|"<<setw(4)<<right<<bk<<"|"<<setw(5)<<right<<setprecision(2)<<pbk<<"|"<<setw(4)<<right<<btb<<"|"<<setw(5)<<right<<setprecision(2)<<pbtb<<"|"<<setw(4)<<right<<by<<"|"<<setw(5)<<right<<setprecision(2)<<pby<<"|"<<endl;    
	cout<<"\t|________|____|_____|____|_____|____|_____|____|_____|____|_____|"<<endl;
	cout<<"\t|  15C   |"<<setw(4)<<right<<cx<<"|"<<setw(5)<<right<<setprecision(2)<<pcx<<"|"<<setw(4)<<right<<cg<<"|"<<setw(5)<<right<<setprecision(2)<<pcg<<"|"<<setw(4)<<right<<ck<<"|"<<setw(5)<<right<<setprecision(2)<<pck<<"|"<<setw(4)<<right<<ctb<<"|"<<setw(5)<<right<<setprecision(2)<<pctb<<"|"<<setw(4)<<right<<cy<<"|"<<setw(5)<<right<<setprecision(2)<<pcy<<"|"<<endl;   
	cout<<"\t|________|____|_____|____|_____|____|_____|____|_____|____|_____|"<<endl;
	cout<<"\t|  15D   |"<<setw(4)<<right<<dx<<"|"<<setw(5)<<right<<setprecision(2)<<pdx<<"|"<<setw(4)<<right<<dg<<"|"<<setw(5)<<right<<setprecision(2)<<pdg<<"|"<<setw(4)<<right<<dk<<"|"<<setw(5)<<right<<setprecision(2)<<pdk<<"|"<<setw(4)<<right<<dtb<<"|"<<setw(5)<<right<<setprecision(2)<<pdtb<<"|"<<setw(4)<<right<<dy<<"|"<<setw(5)<<right<<setprecision(2)<<pdy<<"|"<<endl;  
	cout<<"\t|________|____|_____|____|_____|____|_____|____|_____|____|_____|"<<endl;
	cout<<"\t|  TONG  |"<<setw(4)<<right<<xs<<"|"<<setw(5)<<right<<setprecision(2)<<pxs<<"|"<<setw(4)<<right<<g<<"|"<<setw(5)<<right<<setprecision(2)<<pg<<"|"<<setw(4)<<right<<k<<"|"<<setw(5)<<right<<setprecision(2)<<pk<<"|"<<setw(4)<<right<<tb<<"|"<<setw(5)<<right<<setprecision(2)<<ptb<<"|"<<setw(4)<<right<<y<<"|"<<setw(5)<<right<<setprecision(2)<<py<<"|"<<endl;    
	cout<<"\t|________|____|_____|____|_____|____|_____|____|_____|____|_____|"<<endl;

	quay_lai(ds);
}

void ve_khung1(int x, int y){
	gotoXY(x,y);
	cout<<(char)218;
	for(int i = 0; i < 30; i++)	cout<<(char)196;
	cout<<(char)191;
	gotoXY(x,y+1);
	cout<<(char)179;
	gotoXY(x+31,y+1);
	cout<<(char)179;	
	gotoXY(x,y+2);
	cout<<(char)192;
	for(int i = 0; i < 30; i++) cout<<(char)196;
	cout<<(char)217;
}
void khung_ds(int x, int y){
	gotoXY(x,y);
	cout<<(char)218;
	for(int i = 0; i < 58; i++){
		if(i == 4) cout<<(char)194;
		if(i == 10) cout<<(char)194;
		if(i == 19) cout<<(char)194;
		if(i == 41) cout<<(char)194;
		if(i == 52) cout<<(char)194;
		else cout<<(char)196;
	}	
	cout<<(char)191;
	gotoXY(x,y+1);
	cout<<(char)179;
	gotoXY(x+5,y+1);
	cout<<(char)179;
	gotoXY(x+12,y+1);
	cout<<(char)179;
	gotoXY(x+22,y+1);
	cout<<(char)179;
	gotoXY(x+45,y+1);
	cout<<(char)179;
	gotoXY(x+57,y+1);
	cout<<(char)179;
	gotoXY(x+63,y+1);
	cout<<(char)179;	
	gotoXY(x,y+2);
	cout<<(char)192;
	for(int i = 0; i < 58; i++){
		if(i == 4) cout<<(char)193;
		if(i == 10) cout<<(char)193;
		if(i == 19) cout<<(char)193;
		if(i == 41) cout<<(char)193;
		if(i == 52) cout<<(char)193;
		else cout<<(char)196;
	}
	cout<<(char)217;
}

void ve_khung(int x, int y){
	gotoXY(x,y);
	cout<<(char)218;
	for(int i = 0; i < 20; i++)	cout<<(char)196;
	cout<<(char)191;
	gotoXY(x,y+1);
	cout<<(char)179;
	gotoXY(x+21,y+1);
	cout<<(char)179;	
	gotoXY(x,y+2);
	cout<<(char)192;
	for(int i = 0; i < 20; i++) cout<<(char)196;
	cout<<(char)217;
}
void menu_sx(vector<sinhvien> ds, int n){
	char c;
	int chon = 0;
	string a[10] = {"Sap xep Chon","Sap xep Noi bot","Sap xep Chen","Sap xep Nhanh"};
	TextColor(5);
	ve_khung(53,7);
	TextColor(10);
	gotoXY(55,8);
	cout<<a[0];
	TextColor(5);
	for(int i = 1; i < 4; i++){
		ve_khung(53,3*i+7);	
		gotoXY(55,3*i+8);
		cout<<a[i];
	}
	do{
		c = getch();
		switch(c){
			case 72:
				TextColor(5);
				gotoXY(55, 3*chon+8);
				cout<<a[chon];
				chon--;
				if(chon < 0) chon = 3;
				TextColor(10);
				gotoXY(55,3*chon+8);
				cout<<a[chon];
				break;
			case 77:
			case 80:
				TextColor(5);
				gotoXY(55, 3*chon+8);
				cout<<a[chon];
				chon++;
				if(chon > 3) chon = 0;
				TextColor(10);
				gotoXY(55,3*chon+8);
				cout<<a[chon];
				break;
			case 75:
				for(int i = 0; i < 15; i++){
					gotoXY(53, i+7);
					cout<<"                       ";	
				}
				menusx(ds);
				break;
			case 13:
				system("cls");
				if(n == 0 && chon ==0 || chon == 3) sx_chon_malop(ds);
				if(n == 1 && chon ==0 || chon == 3) sx_chon_masv(ds);
				if(n == 2 && chon ==0 || chon == 3) sx_chon_ten(ds);
				if(n == 3 && chon ==0 || chon == 3) sx_chon_date(ds);
				if(n == 4) sx_chon_diem(ds);
				if(n == 0 && chon == 1) sx_nb_malop(ds);
				if(n == 1 && chon == 1) sx_nb_masv(ds);
				if(n == 2 && chon == 1) sx_nb_ten(ds);
				if(n == 3 && chon == 1) sx_nb_date(ds);
				if(n == 0 && chon == 2) sx_chen_malop(ds);
				if(n == 1 && chon == 2) sx_chen_masv(ds);
				if(n == 2 && chon == 2) sx_chen_ten(ds);
				if(n == 3 && chon == 2) sx_chen_date(ds);
				
				in_ds(ds);
				break;	
		}
	}while(c != 27);
}
void menu_tim(vector<sinhvien> ds, int n){
	char c;
	int chon = 0;
	string a[10] = {"Tim kiem tuan tu","Tim kiem nhi phan"};
	TextColor(5);
	ve_khung(53,7);
	TextColor(10);
	gotoXY(55,8);
	cout<<a[0];
	TextColor(5);
	ve_khung(53,3+7);	
	gotoXY(55,3+8);
	cout<<a[1];
	do{
		c = getch();
		switch(c){
			case 72:
				TextColor(5);
				gotoXY(55, 3*chon+8);
				cout<<a[chon];
				chon--;
				if(chon < 0) chon = 1;
				TextColor(10);
				gotoXY(55,3*chon+8);
				cout<<a[chon];
				break;
			case 77:
			case 80:
				TextColor(5);
				gotoXY(55, 3*chon+8);
				cout<<a[chon];
				chon++;
				if(chon > 1) chon = 0;
				TextColor(10);
				gotoXY(55,3*chon+8);
				cout<<a[chon];
				break;
			case 75:
				for(int i = 0; i < 10; i++){
					gotoXY(53, i+7);
					cout<<"                       ";	
				}
				menutim(ds);
				break;
			case 13:
				if(n == 0 ) tk_tt_malop(ds);
				if(n == 1 && chon == 0) tk_tt_masv(ds);
				if(n == 2 ) tk_tt_ten(ds);
				if(n == 3 ) tk_tt_ngaysinh(ds);
				if(n == 4 && chon == 0) tk_tt_diem(ds);
				if(n == 5 ) tk_tt_batky(ds);
				if(n == 1 && chon == 1) tk_np_masv(ds);
				if(n == 4 && chon == 1) tk_np_diem(ds); 
				break;	
		}
	}while(c != 27);
}
void menusx(vector<sinhvien> ds){
	char c;
	ifstream filein;
	filein.open("data.txt", ios_base::in);
	int chon = 0;
	string a[10] = {"Theo ma lop       >","Theo ma sinh vien >","Theo ten          >","Theo ngay sinh    >","Theo diem         >"};
	TextColor(5);
	ve_khung(28,5);
	TextColor(10);
	gotoXY(30,6);
	cout<<a[0];
	TextColor(5);
	for(int i = 1; i < 5; i++){
		ve_khung(28,3*i+5);	
		gotoXY(30,3*i+6);
		cout<<a[i];
	}
	do{
		c = getch();
		switch(c){
			case 72:
				TextColor(5);
				gotoXY(30, 3*chon+6);
				cout<<a[chon];
				chon--;
				if(chon < 0) chon = 4;
				TextColor(10);
				gotoXY(30,3*chon+6);
				cout<<a[chon];
				break;
			case 80:
				TextColor(5);
				gotoXY(30, 3*chon+6);
				cout<<a[chon];
				chon++;
				if(chon > 4) chon = 0;
				TextColor(10);
				gotoXY(30,3*chon+6);
				cout<<a[chon];
				break;
			case 75:
				for(int i = 0; i < 15; i++){
					gotoXY(28, i+5);
					cout<<"                       ";	
				}
				Menu(filein, ds);
				break;
			case 77:
			case 13:
				menu_sx(ds,chon);
				break;
		}
	}while(c != 27);
}
void menutim(vector<sinhvien> ds){
	char c;
	ifstream filein;
	filein.open("data.txt", ios_base::in);
	int chon = 0;
	string a[10] = {"Theo ma lop       >","Theo ma sinh vien >","Theo ten          >","Theo ngay sinh    >","Theo diem         >","Tim kien bat ky   >"};
	TextColor(5);
	ve_khung(28,3);
	TextColor(10);
	gotoXY(30,4);
	cout<<a[0];
	TextColor(5);
	for(int i = 1; i < 6; i++){
		ve_khung(28,3*i+3);	
		gotoXY(30,3*i+4);
		cout<<a[i];
	}
	do{
		c = getch();
		switch(c){
			case 72:
				TextColor(5);
				gotoXY(30, 3*chon+4);
				cout<<a[chon];
				chon--;
				if(chon < 0) chon = 5;
				TextColor(10);
				gotoXY(30,3*chon+4);
				cout<<a[chon];
				break;
			case 80:
				TextColor(5);
				gotoXY(30, 3*chon+4);
				cout<<a[chon];
				chon++;
				if(chon > 5) chon = 0;
				TextColor(10);
				gotoXY(30,3*chon+4);
				cout<<a[chon];
				break;
			case 75:
				for(int i = 0; i < 20; i++){
					gotoXY(28, i+3);
					cout<<"                       ";	
				}
				Menu(filein, ds);
				break;
			case 77:
			case 13:
				menu_tim(ds,chon);
				break;
		}
	}while(c != 27);
}

void menu_tk(vector<sinhvien> ds){
	char c;
	ifstream filein;
	filein.open("data.txt", ios_base::in);
	int chon = 0;
	string a[5] = {"So luong sinh vien theo lop","Phan loai ket qua hoc tap"};
	TextColor(5);
	ve_khung1(28,5);
	TextColor(10);
	gotoXY(30,6);
	cout<<a[0];
	TextColor(5);
	for(int i = 1; i < 2; i++){
		ve_khung1(28,3*i+5);	
		gotoXY(30,3*i+6);
		cout<<a[i];
	}
	do{
		c = getch();
		switch(c){
			case 72:
				TextColor(5);
				gotoXY(30, 3*chon+6);
				cout<<a[chon];
				chon--;
				if(chon < 0) chon = 1;
				TextColor(10);
				gotoXY(30,3*chon+6);
				cout<<a[chon];
				break;
			case 77:
			case 80:
				TextColor(5);
				gotoXY(30, 3*chon+6);
				cout<<a[chon];
				chon++;
				if(chon > 1) chon = 0;
				TextColor(10);
				gotoXY(30,3*chon+6);
				cout<<a[chon];
				break;
			case 75:
				for(int i = 0; i < 6; i++){
					gotoXY(28 ,i + 5);
					cout<<"                                 ";
				}
				Menu(filein, ds);
				break;
			case 13:
				system("cls");
				if(chon == 0) tk_sl_sv(ds);
				if(chon == 1) tk_kqht_sv(ds);
				break;
		}
	}while(c != 27);
}

void hotro(){
	TextColor(7);
	gotoXY(1,23); cout<<"Phim len, xuong de di chuyen  ||  Enter hoac -> de chon  ||  <- de quay lai";
	gotoXY(30,27); cout<<"Sinh vien thuc hien: Ly Van Chan, Lop: CNTT 15";
}

void Menu(ifstream &filein, vector<sinhvien> ds){
	ShowCur(false);
	char c;
	sinhvien sv;
	int chon = 0 ;
	string a[10] = {"Them moi ho so  ","In danh sach    ","Sap xep         >","Tim kiem        >", "Thong ke        >", "Esc -> Thoat"};
	TextColor(5);
	gotoXY(8,2); cout<<"MENU CHINH";
	hotro();
	TextColor(5);
	ve_khung(3,3);
	TextColor(10);
	gotoXY(6,4);
	cout<<a[0];
	TextColor(5);
	for(int i = 1; i < 6; i++){
		ve_khung(3,3*i+3);	
		gotoXY(6,3*i+4);
		cout<<a[i];
	}	
	do{
		c = getch();
		switch(c){
			case 72:
			case 75:
				TextColor(5);
				gotoXY(6, 3*chon+4);
				cout<<a[chon];
				chon--;
				if(chon < 0) chon = 5;
				TextColor(10);
				gotoXY(6,3*chon+4);
				cout<<a[chon];
				break;
			case 80:
				TextColor(5);
				gotoXY(6, 3*chon+4);
				cout<<a[chon];
				chon++;
				if(chon > 5) chon = 0;
				TextColor(10);
				gotoXY(6,3*chon+4);
				cout<<a[chon];
				break;
			case 77:
			case 13:
				if(chon == 0){
					system("cls");
					sv.nhap_ds(filein, ds);
				}
				else if(chon == 1){
					system("cls");
					in_ds(ds);
				}
				else if(chon == 2) menusx(ds);
				
				else if(chon == 3) menutim(ds);
				
				else if(chon == 4) menu_tk(ds);
				
				else exit(0);
								
				break;
		}
	}while(c != 27 && c != 13);
}



void in_ds(vector<sinhvien> ds){
	char c;
	int page = 1, i = 0, n = ds.size() - 1;
	
	do{
		gotoXY(80,3); cout<<"Enter 2 lan de quay lai";
		gotoXY(80,4); cout<<"-> chuyen trang tiep";
		gotoXY(80,5); cout<<"<- quay lai trang truoc";
		khung_ds(1,2);
		gotoXY(3,3); cout<<"Stt";
		gotoXY(7,3); cout<<"Ma lop";
		gotoXY(16,3); cout<<"Ma sv";
		gotoXY(29,3); cout<<"Ho va ten";
		gotoXY(48,3); cout<<"Ngay sinh";
		gotoXY(59,3); cout<<"DTBTL";
		int j = 0;
		while(i < 8*page && i < n){
			khung_ds(1,5+3*j);	
			gotoXY(4,6+3*j); cout<<i+1;
			gotoXY(7,6+3*j); cout<<ds[i].malop;
			gotoXY(15,6+3*j); cout<<ds[i].masv;
			gotoXY(24,6+3*j); cout<<ds[i].hoten;
			gotoXY(47,6+3*j); cout<<ds[i].ngaythang;
			gotoXY(61,6+3*j); cout<<ds[i].diemtb;
			i++;
			j++;
		}	
		c = getch();
		switch(c){
			case 72:
			case 75:
				if(page > 1){
					system("cls");
					page--;	
					if(page < n/8)
						i = i - 16;
					else{
						int dem = n - 8*page;
						i = i - 8 - dem;
					}
				} 
				break;
			case 77:
			case 80:
				if(page < (n/8+1)){
					system("cls");
					page++;	
				} 
				break;
			
		}
	}while(c != 13);
	quay_lai(ds);
}

void sinhvien::nhap_ds(ifstream &filein, vector<sinhvien> &ds){
	ShowCur(true);
	int t;
	sinhvien sv;
	char c;
	string a[3] = {"Cap nhat", "Huy"};
	cout<<"\nThem moi bao nhieu sinh vien: ";
	TextColor(8);
	ve_khung(32,0);
	gotoXY(33,1); cin>>t;
	TextColor(14);
	khung_ds(1,4);
	gotoXY(3,5); cout<<"Stt";
	gotoXY(7,5); cout<<"Ma lop";
	gotoXY(16,5); cout<<"Ma sv";
	gotoXY(29,5); cout<<"Ho va ten";
	gotoXY(47,5); cout<<"Ngay sinh";
	gotoXY(59,5); cout<<"DTBTL";

	for(int i = 0; i < t; i++){
		gotoXY(5,3);
		cout<<"Nhap thong tin sinh vien thu "<<i+1;
		khung_ds(1,7+3*i);
		gotoXY(8,15); cout<<"                  ";
		gotoXY(4,8+3*i); cout<<i+1;
		gotoXY(7,8+3*i);
		fflush(stdin);
		getline(cin,sv.malop);
		int dem = 0 ;
		sv.masv = 11111111;
		do{
			gotoXY(14,8+3*i); cout<<"         ";
			
			if(sv.masv < 9999999 || sv.masv > 99999999){
				gotoXY(10,20);
				cout<<"Ma sinh vien phai co 8 so, nhap lai !!";	
			}
			
			if(dem > 0){
				gotoXY(10,20);
				cout<<"Ma sinh vien da ton tai, nhap lai ma khac!!";	
			}
			dem = 0 ;
			gotoXY(14,8+3*i);
			cin>>sv.masv;
			gotoXY(10,20); cout<<"                                            ";
			int n = ds.size();
			for(int i = 0; i < n -1 ; i++){
				if(sv.masv == ds[i].masv)
				dem = dem +1;
			}
		}while(dem > 0 || sv.masv < 9999999 || sv.masv > 99999999);
		fflush(stdin);
		do{
			gotoXY(25,8+3*i); cout<<"                     ";
			gotoXY(25,8+3*i);
			getline(cin,sv.hoten);
			chuanhoaten(sv.hoten);
			gotoXY(25,8+3*i); cout<<"                     ";
			gotoXY(25,8+3*i); cout<<sv.hoten;
		}while(chuanhoaKitu(sv.hoten) == false );
		do{
			gotoXY(47,8+3*i); cout<<"          ";
			gotoXY(49,8+3*i); cout<<"/";
			gotoXY(52,8+3*i);cout<<"/";
			gotoXY(47,8+3*i); cin>>sv.ngaysinh.ngay;
			gotoXY(50,8+3*i);cin>>sv.ngaysinh.thang;
			gotoXY(53,8+3*i);cin>>sv.ngaysinh.nam;
		}while(chuanhoaNgaySinh(sv.ngaysinh.ngay, sv.ngaysinh.thang, sv.ngaysinh.nam) == false);
		do{
			gotoXY(59,8+3*i); cout<<"  ";
			gotoXY(59,8+3*i); cin>>sv.diemtb;
		}while(chuanhoaDiem(sv.diemtb) == false);
		int chon = 0;
		TextColor(10);
		gotoXY(8,15); cout<<a[0];
		TextColor(5);
		gotoXY(20,15); cout<<a[1];
		do{
			c = getch();
		switch(c){
			case 72:
			case 75:
				TextColor(5);
				gotoXY(8+12*chon, 15);
				cout<<a[chon];
				chon--;
				if(chon < 0) chon = 1;
				TextColor(10);
				gotoXY(8+12*chon, 15);
				cout<<a[chon];
				break;
			case 77:
			case 80:
				TextColor(5);
				gotoXY(8 + 12*chon, 15);
				cout<<a[chon];
				chon++;
				if(chon > 1) chon = 0;
				TextColor(10);
				gotoXY(8 + 12*chon, 15);
				cout<<a[chon];
				break;
			case 13:
				if(chon == 0){
					ofstream fileout;
					fileout.open("data.txt", ios_base::app);
					sv.gi_file_hososinhvien(fileout);
					ds.clear();
					filein.close();
					filein.open("data.txt", ios_base::in);
					lumangsv(filein, ds);
				}
				break;
		}
	}while(c != 13);				
	}
	quay_lai(ds);
}

int main(){
	ShowCur(false);
	sinhvien sv;
	vector<sinhvien> ds;
	ofstream fileout;
	fileout.open("data.txt", ios_base::app);
	ifstream filein;
	filein.open("data.txt", ios_base::in);
	lumangsv(filein, ds);
	Menu(filein, ds);
	
	return 0;
}


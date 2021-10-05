#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class NamSinh
{
private:
	int ngay;
	int thang;
	int nam;
public:
	int Getter_Ngay()
	{
		return ngay;
	}
	void Setter_Ngay(int NGAY)
	{
		ngay = NGAY;
	}

	int Getter_Thang()
	{
		return thang;
	}
	void Setter_Thang(int THANG)
	{
		thang = THANG;
	}

	int Getter_Nam()
	{
		return nam;
	}
	void Setter_Nam(int NAM)
	{
		nam = NAM;
	}
};
class NhanVien
{
protected:
	string maNhanVien;
	string tenNhanVien;
	NamSinh namsinh;
	string diaChi;
	float heSoLuong;
	float luongCoBan;
public:
	virtual void Doc_File(ifstream &filein);
	virtual void Xuat_Thong_Tin();
	virtual long Tinh_Luong_Hang_Thang() = 0;
	void Ghi_Thong_Tin_Nhan_Vien_Vao_File(ofstream &fileout, NhanVien *ds[], int n);
	int Lay_Ngay_Sinh();
	int Lay_Thang_Sinh();
	int Lay_Nam_Sinh();
};
void NhanVien::Doc_File(ifstream &filein)
{   char a;
	getline(filein, maNhanVien, ',');
	//filein.seekg(1, ios::cur);
	//filein >> a;
	getline(filein, tenNhanVien, ',');
	int ngay;
	filein >> ngay;
	namsinh.Setter_Ngay(ngay);
	//filein.seekg(1, ios::cur);
	filein >>a;
	int thang;
	filein >> thang;
	namsinh.Setter_Thang(thang);
	//filein.seekg(1, ios::cur);
	filein >>a;
	int nam;
	filein >> nam;
	namsinh.Setter_Nam(nam);
	//filein.seekg(2, ios::cur);
	filein >>a;
	getline(filein, diaChi, ',');
	filein >> heSoLuong;
	//filein.seekg(1, ios::cur);
	filein >>a;
	filein >> luongCoBan;
	//filein.seekg(1, ios::cur);
	filein >>a;
}

void NhanVien::Xuat_Thong_Tin()
{
	cout << "\nMa nhan vien: " << maNhanVien << endl;
	cout << "\nHo ten nhan vien: " << tenNhanVien << endl;
	cout << "\nNgay thang nam sinh: " << namsinh.Getter_Ngay() << "/" << namsinh.Getter_Thang() << "/" << namsinh.Getter_Nam() << endl;
	cout << "\nDia chi: " << diaChi << endl;
	cout << "\nHe so luong: " << heSoLuong << endl;
	cout << "\nLuong co ban: " << (size_t)luongCoBan << endl;
}
class NhanVienLapTrinh : public NhanVien
{
private:
	float tienLamNgoaiGio;
public:
	void Doc_File(ifstream &filein);
	void Xuat_Thong_Tin();
	long Tinh_Luong_Hang_Thang();
};
void NhanVienLapTrinh::Doc_File(ifstream &filein)
{
	NhanVien::Doc_File(filein);
	filein >> tienLamNgoaiGio;
}

void NhanVienLapTrinh::Xuat_Thong_Tin()
{
	NhanVien::Xuat_Thong_Tin();
	cout << "\nTien lam ngoai gio: " << (size_t)tienLamNgoaiGio << endl;
	cout << "\nTien luong nhan duoc hang thang: " << (size_t)Tinh_Luong_Hang_Thang() << endl;
}
long NhanVienLapTrinh::Tinh_Luong_Hang_Thang()
{
	return (luongCoBan * heSoLuong) + tienLamNgoaiGio;
}
class NhanVienThietKe : public NhanVien
{
private:
	float tienThuong;
public:
	void Doc_File(ifstream &filein);
	void Xuat_Thong_Tin();
	long Tinh_Luong_Hang_Thang();
};
void NhanVienThietKe::Doc_File(ifstream &filein)
{
	NhanVien::Doc_File(filein);
	filein >> tienThuong;
}

void NhanVienThietKe::Xuat_Thong_Tin()
{
	NhanVien::Xuat_Thong_Tin();
	cout << "\nTien thuong: " << (size_t)tienThuong << endl;
	cout << "\nTien luong nhan duoc hang thang: " << (size_t)Tinh_Luong_Hang_Thang() << endl;
}

long NhanVienThietKe::Tinh_Luong_Hang_Thang()
{
	return (luongCoBan * heSoLuong) + tienThuong;
}

void NhanVien::Ghi_Thong_Tin_Nhan_Vien_Vao_File(ofstream &fileout, NhanVien *ds[], int n)
{
	fileout << "\nMa nhan vien: " << maNhanVien << endl;
	fileout << "\nHo ten nhan vien: " << tenNhanVien << endl;
	fileout << "\nNgay thang nam sinh: " << namsinh.Getter_Ngay() << "/" << namsinh.Getter_Thang() << "/" << namsinh.Getter_Nam() << endl;
	fileout << "\nDia chi: " << diaChi << endl;
	fileout << "\nHe so luong: " << heSoLuong << endl;
	fileout << "\nLuong co ban: " << (size_t)luongCoBan << endl;
	fileout << "\nTien luong nhan duoc hang thang: " << (size_t)Tinh_Luong_Hang_Thang() << endl;
}
// Phuong th?c l?y ngày sinh
int NhanVien::Lay_Ngay_Sinh()
{
	return namsinh.Getter_Ngay();
}
// Phuong th?c l?y tháng sinh
int NhanVien::Lay_Thang_Sinh()
{
	return namsinh.Getter_Thang();
}
// Phuong th?c l?y nam sinh
int NhanVien::Lay_Nam_Sinh()
{
	return namsinh.Getter_Nam();
}
void Menu(NhanVien *ds[], int &n)
{
	ifstream filein;
	filein.open("F:\\Github\\QuanLiNhanVien\\NhanVien.txt", ios_base::in);
	int luachon;
	while (true)
	{
		system("cls");
		cout << "\n\n\t\t ============ QUAN LY NHAN VIEN ============\n";
		cout << "\n\t1. Doc thong tin sinh vien tu file NHANVIEN.TXT";
		cout << "\n\t2. Xuat thong tin sinh vien";
		cout << "\n\t3. Thong ke luong nhan vien giam dan ra tap tin THONGKELUONG.TXT";
		cout << "\n\t4. Sap xep nhan vien tang dan theo nam sinh ra tap tin NAMSINHTANGDAN.TXT";
		cout << "\n\t0. Ket thuc";
		cout << "\n\n\t\t =================== END ===================\n";

		cout << "\nMoi nhap lua chon: ";
		cin >> luachon;
		if (luachon < 0 || luachon > 4)
		{
			cout << "\nLuachon cua ban khong hop le. Xin vui long nhap lai!!!";
			system("pause");
		}
		else if (luachon == 1)
		{
			filein >> n;
			NhanVien *x = NULL;
			for (int i = 0; i < n; i++)
			{
				char c,d;
				filein >> c;
				filein >>d;
				//filein.seekg(-1, ios::cur);
				if (c == 'P')
				{
					x = new NhanVienLapTrinh();
					x->Doc_File(filein);
				}
				else if (c == 'D')
				{
					x = new NhanVienThietKe();
					x->Doc_File(filein);
				}
				ds[i] = x;
			}
			cout << "\nDu lieu tu file NHANVIEN.TXT da duoc doc thanh cong!!!\n";
			system("pause");
		}
		else if (luachon == 2)
		{
			cout << "\n\n\t\t =============== DANH SACH NHAN VIEN ===============\n";
			for (int i = 0; i < n; i++)
			{
				cout << "\n\n\t\t DANH SACH NHAN VIEN THU " << i + 1 << endl;
				ds[i]->Xuat_Thong_Tin();
			}
			system("pause");
		}
		else if (luachon == 3)
		{
			ofstream fileout;
			fileout.open("THONGKELUONG.TXT", ios_base::out);
			for (int i = 0; i < n - 1; i++)
			{
				for (int j = i + 1; j < n; j++)
				{
					if (ds[i]->Tinh_Luong_Hang_Thang() < ds[j]->Tinh_Luong_Hang_Thang())
					{
						NhanVien *temp = ds[i];
						ds[i] = ds[j];
						ds[j] = temp;
					}
				}
			}
			for (int i = 0; i < n; i++)
			{
				ds[i]->Ghi_Thong_Tin_Nhan_Vien_Vao_File(fileout, ds, n);
			}
			cout << "\nDu lieu cua ban da duoc luu vao file THONGKELUONG.TXT\n";
			system("pause");
			fileout.close();
		}

		else if (luachon == 4)
		{
			ofstream fileout;
			fileout.open("NAMSINHTANGDAN.TXT", ios_base::out);
			for (int i = 0; i < n - 1; i++)
			{
				for (int j = i + 1; j < n; j++)
				{
					if ((ds[i]->Lay_Ngay_Sinh() > ds[j]->Lay_Ngay_Sinh()) && (ds[i]->Lay_Thang_Sinh() > ds[j]->Lay_Thang_Sinh()) && (ds[i]->Lay_Nam_Sinh() > ds[j]->Lay_Nam_Sinh()))
					{
						NhanVien* temp = ds[i];
						ds[i] = ds[j];
						ds[j] = temp;
					}
				}
			}
			for (int i = 0; i < n; i++)
			{
				ds[i]->Ghi_Thong_Tin_Nhan_Vien_Vao_File(fileout, ds, n);
			}
			cout << "\nDu lieu cua ban da duoc luu vao file NAMSINHTANGDAN.TXT\n";
			system("pause");
			fileout.close();
		}
		else
		{
			break;
		}
	}
	filein.close();
}
int main()
{
	NhanVien *ds[100];
	int n = 0;
	Menu(ds, n);
	system("pause");
	return 0;
}
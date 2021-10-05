#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class namsinh{
    int ngay;
    int thang;
    int nam;
    public:
      int getNgay(){
          return ngay;
      }
      void setNgay(int ngay){
          this->ngay = ngay;
      }
      int getThang(){
          return thang;
      }
      void setThang(int thang){
          this->thang = thang;
      }
      int getNam(){
          return nam;
      }
      void setNam(int nam){
          this->nam = nam;
      }
};

class nhanvien {
    protected:
    string manhanvien;
    string tennhanvien;
    namsinh ns;
    string diachi;
    double hesoluong;
    double luongcb;
    bool KT; //true : IT, false : DS
    public: 
      virtual void docfile(ifstream &in){
          char a;  // đọc kí tự cần bỏ
          getline(in,manhanvien,',');
          //in.seekg(1,ios::cur); //dịch con trỏ chỉ vị của file tại vị trí hiện tại sang 1 byte
          getline(in,tennhanvien,',');

          int ngay;
          in >> ngay;
          ns.setNgay(ngay);
          //in.seekg(1,ios::cur); //dịch con trỏ chỉ vị của file tại vị trí hiện tại sang 1 byte, bỏ qua kí tự /
          in >>a;
          int thang;
          in >> thang;
          ns.setThang(thang);
          in >>a;
          //in.seekg(1,ios::cur); //dịch con trỏ chỉ vị của file tại vị trí hiện tại sang 1 byte, bỏ qua kí tự /
          int nam;
          in >> nam;
          ns.setNam(nam);

          //in.seekg(2,ios::cur); //dịch con trỏ chỉ vị của file tại vị trí hiện tại sang 2 byte, bỏ qua kí tự " " và ","
          in >> a;
          getline(in,diachi,',');
          in >> hesoluong;
          in >> a;
          //in.seekg(1,ios::cur); //bỏ qua dấu phẩy, khoảng trắng vs dữ liệu số thì k càn
          in >>luongcb;
          in >> a;
          //in.seekg(1, ios::cur);

    }
    virtual void xuat(){
          cout <<"\nMa nhan vien: "<<manhanvien<<endl;
          cout <<"Ten nhan vien: "<<tennhanvien<<endl;
          cout <<"Dia chi: "<<diachi<<endl;
          cout <<"Ngay thang nam sinh: "<<ns.getNgay()<<"/"<<ns.getThang()<<"/"<<ns.getNam()<<endl;
          cout <<"He so luong: "<<hesoluong<<endl;
          cout <<"Luong co ban: "<<(size_t)luongcb<<endl;
      }
    bool Getter_KT(){
		return KT;
	}
	// cập nhật dữ liệu
	void Setter_KT(bool kt){
		KT = kt;
	}
    virtual long Tinh_Luong_Hang_Thang() = 0;
    void Ghi_Thong_Tin_Nhan_Vien_Vao_File(ofstream &out, nhanvien *ds[], int n){
        out << "\nMa nhan vien: " << manhanvien << endl;
	    out << "\nHo ten nhan vien: " << tennhanvien << endl;
	    out << "\nNgay thang nam sinh: " << ns.getNgay() << "/" << ns.getThang() << "/" << ns.getNam() << endl;
	    out << "\nDia chi: " << diachi << endl;
	    out << "\nHe so luong: " << hesoluong << endl;
	    out << "\nLuong co ban: " << (size_t)luongcb << endl;
	    out << "\nTien luong nhan duoc hang thang: " << (size_t)Tinh_Luong_Hang_Thang() << endl;
    }
	int Lay_Ngay_Sinh();
	int Lay_Thang_Sinh();
	int Lay_Nam_Sinh();

};

class nhanvienIT :public nhanvien{
    private:
       double tienlamthem;
    public:
       void docfile(ifstream &in){
           nhanvien::docfile(in);
           in >>tienlamthem;
       }
       void xuat(){
           nhanvien::xuat();
           cout<<"Tien lam them: "<<(size_t)tienlamthem<<endl;
           cout << "\nTien luong nhan duoc hang thang: " << (size_t)Tinh_Luong_Hang_Thang() << endl;
       }
       long Tinh_Luong_Hang_Thang(){
           return (luongcb*hesoluong)+tienlamthem;
       }
};

class nhanvienDS :public nhanvien{
    private:
       double tienthuong;
    public:
       void docfile(ifstream &in){
           nhanvien::docfile(in);
           in >> tienthuong;
       }
       void xuat(){
           nhanvien::xuat();
           cout <<"Tien thuong: "<<(size_t)tienthuong<<endl;
           cout << "\nTien luong nhan duoc hang thang: " << (size_t)Tinh_Luong_Hang_Thang() << endl;
       }
       long Tinh_Luong_Hang_Thang(){
           return ( luongcb * hesoluong ) + tienthuong;
       }
};

void menu(nhanvien *ds[], int &n){
    int cv;
    ifstream filein;
    filein.open("F:\\Github\\QuanLiNhanVien\\NhanVien.txt", ios_base::in);
    do{
        system("cls"); // xóa hết các thứ có trong màn hình console trước cái lệnh này
		cout << "============ MENU ============"<<endl;
		cout << "1. Doc thong tin nhan vien tu file"<<endl;
        cout << "2. Xuat thong tin nhan vien"<<endl;
        cout << "3. Xuat ra file ds nv giam dan theo luong"<<endl;
		cout << "0. Thoat"<<endl;
		cout << "============ END ============"<<endl;

		cout << "\nNhap lua chon: ";
		cin >> cv;
        if (cv == 1) {
            filein >>n;   // đọc số lượng nhân viên
            nhanvien *x = NULL;
            for(int i=0; i<n; i++) {
                char c,d;
                filein >> c; filein >>d;
                //filein.seekg(-1, ios::cur);  //dịch con trỏ sang bên trái 1 đơn vị (do đọc c ở trên) để phần dưới tiếp tục đọc bth
                if(c=='P') {
                    x = new nhanvienIT();
                    x->docfile(filein);
                    x->Setter_KT(true);
                } else if (c=='D') {
                    x = new nhanvienDS();
                    x->docfile(filein);
                    x->Setter_KT(false);
                }
                ds[i]=x;
            }
            system("pause");
        } else if(cv == 2){
            cout << "============ MENU ============"<<endl;
		    cout << "1. Xuat thong tin nhan vien IT"<<endl;
            cout << "2. Xuat thong tin nhan vien DS"<<endl;
            cout << "0.Thoat"<<endl;
            int cv2;
            cout <<"Nhap lua chon: "; cin >>cv2;
            if (cv2==1) {
                cout <<"\nDanh Sach Nhan Vien IT";
                for(int i=0;i<n;i++){
                   if(ds[i]->Getter_KT()==true) ds[i]->xuat();
                }
                system("pause");
            } else if (cv2==2) {
                cout <<"\nDanh Sach Nhan Vien DS";
                for(int i=0;i<n;i++){
                    if(ds[i]->Getter_KT()==false) ds[i]->xuat();
                }  
                system("pause"); 
            } else break;
        } else if(cv == 3){
            ofstream fileout;
			fileout.open("F:\\Github\\QuanLiNhanVien\\ThongKeLuong.txt", ios_base::out);
			for (int i = 0; i < n - 1; i++)
			{
				for (int j = i + 1; j < n; j++)
				{
					if (ds[i]->Tinh_Luong_Hang_Thang() < ds[j]->Tinh_Luong_Hang_Thang())
					{
						nhanvien *temp = ds[i];
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
    } while(cv!=0);
    filein.close();

}


int main(){
    nhanvien *ds[100];    // khai báo mảng 1 chiều các con trỏ lưu trữ 2 loại nhân viên 
    int n=0;
    menu(ds,n);

    return 0;
}
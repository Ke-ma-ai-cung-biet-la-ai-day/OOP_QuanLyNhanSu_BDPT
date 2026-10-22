#include "NhanVienVanPhong.h"

// 1. Constructors & Destructor
NhanVienVanPhong::NhanVienVanPhong() 
    : NhanVien(), soNgayLamViec_(0), donGiaNgay_(0.0) {}

NhanVienVanPhong::NhanVienVanPhong(const std::string& maNV, 
                                 const std::string& hoTen, 
                                 const std::string& ngaySinh, 
                                 const std::string& diaChi, 
                                 int soNgayLamViec, 
                                 double donGiaNgay)
    : NhanVien(maNV, hoTen, ngaySinh, diaChi), 
      soNgayLamViec_(soNgayLamViec), 
      donGiaNgay_(donGiaNgay) {}

NhanVienVanPhong::~NhanVienVanPhong() {}

// 2. Getters & Setters
int NhanVienVanPhong::getSoNgayLamViec() const { 
    return soNgayLamViec_; 
}

void NhanVienVanPhong::setSoNgayLamViec(int soNgayLamViec) { 
    soNgayLamViec_ = soNgayLamViec; 
}

double NhanVienVanPhong::getDonGiaNgay() const { 
    return donGiaNgay_; 
}

void NhanVienVanPhong::setDonGiaNgay(double donGiaNgay) { 
    donGiaNgay_ = donGiaNgay; 
}

// 3. Định nghĩa lại phương thức TinhLuong() đa hình
double NhanVienVanPhong::TinhLuong() {
    return soNgayLamViec_ * donGiaNgay_;
}

// 4. Nhập dữ liệu (Gọi lại hàm Nhap của lớp cha)
void NhanVienVanPhong::Nhap(std::istream& in) {
    NhanVien::Nhap(in); // Nhập maNV, hoTen, ngaySinh, diaChi
    std::cout << "Nhap so ngay lam viec: ";
    in >> soNgayLamViec_;
    std::cout << "Nhap don gia ngay: ";
    in >> donGiaNgay_;
}

// 5. Xuất dữ liệu ra stream (Căn chỉnh dạng bảng đẹp mắt bằng <iomanip>)
void NhanVienVanPhong::Xuat(std::ostream& out) const {
    NhanVien::Xuat(out); // In thong tin co ban
    out << std::left << std::setw(12) << "Van Phong"
        << std::setw(15) << soNgayLamViec_
        << std::setw(15) << std::fixed << std::setprecision(0) << donGiaNgay_
        << std::setw(18) << TinhLuong();
}

// 6. Hiển thị thông tin
void NhanVienVanPhong::HienThiThongTin() const {
    this->Xuat(std::cout);
    std::cout << std::endl;
}

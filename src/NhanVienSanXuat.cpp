#include "NhanVienSanXuat.h"

// 1. Constructors & Destructor
NhanVienSanXuat::NhanVienSanXuat() 
    : NhanVien(), soSanPham_(0), donGiaSanPham_(0.0) {}

NhanVienSanXuat::NhanVienSanXuat(const std::string& maNV, 
                                 const std::string& hoTen, 
                                 const std::string& ngaySinh, 
                                 const std::string& diaChi, 
                                 int soSanPham, 
                                 double donGiaSanPham)
    : NhanVien(maNV, hoTen, ngaySinh, diaChi), 
      soSanPham_(soSanPham), 
      donGiaSanPham_(donGiaSanPham) {}

NhanVienSanXuat::~NhanVienSanXuat() {}

// 2. Getters & Setters
int NhanVienSanXuat::getSoSanPham() const { 
    return soSanPham_; 
}

void NhanVienSanXuat::setSoSanPham(int soSanPham) { 
    soSanPham_ = soSanPham; 
}

double NhanVienSanXuat::getDonGiaSanPham() const { 
    return donGiaSanPham_; 
}

void NhanVienSanXuat::setDonGiaSanPham(double donGiaSanPham) { 
    donGiaSanPham_ = donGiaSanPham; 
}

// 3. Định nghĩa lại phương thức TinhLuong() đa hình
double NhanVienSanXuat::TinhLuong() {
    return soSanPham_ * donGiaSanPham_;
}

// 4. Nhập dữ liệu (Gọi lại hàm Nhap của lớp cha)
void NhanVienSanXuat::Nhap(std::istream& in) {
    NhanVien::Nhap(in); // Nhập maNV, hoTen, ngaySinh, diaChi
    std::cout << "Nhap so san pham: ";
    in >> soSanPham_;
    std::cout << "Nhap don gia san pham: ";
    in >> donGiaSanPham_;
}

// 5. Xuất dữ liệu ra stream (Căn chỉnh bảng bằng <iomanip>)
void NhanVienSanXuat::Xuat(std::ostream& out) const {
    NhanVien::Xuat(out); // In thông tin cơ bản
    out << std::left << std::setw(12) << "San Xuat"
        << std::setw(15) << soSanPham_
        << std::setw(15) << std::fixed << std::setprecision(0) << donGiaSanPham_
        << std::setw(18) << TinhLuong();
}

// 6. Hiển thị thông tin
void NhanVienSanXuat::HienThiThongTin() const {
    this->Xuat(std::cout);
    std::cout << std::endl;
}

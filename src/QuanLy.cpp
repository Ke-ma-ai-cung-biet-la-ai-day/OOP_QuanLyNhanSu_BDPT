#include "QuanLy.h"

// 1. Constructors & Destructor
QuanLy::QuanLy() 
    : NhanVien(), luongCoBan_(0.0), luongTrachNhiem_(0.0) {}

QuanLy::QuanLy(const std::string& maNV, 
               const std::string& hoTen, 
               const std::string& ngaySinh, 
               const std::string& diaChi, 
               double luongCoBan, 
               double luongTrachNhiem)
    : NhanVien(maNV, hoTen, ngaySinh, diaChi), 
      luongCoBan_(luongCoBan), 
      luongTrachNhiem_(luongTrachNhiem) {}

QuanLy::~QuanLy() {}

// 2. Getters & Setters
double QuanLy::getLuongCoBan() const { 
    return luongCoBan_; 
}

void QuanLy::setLuongCoBan(double luongCoBan) { 
    luongCoBan_ = luongCoBan; 
}

double QuanLy::getLuongTrachNhiem() const { 
    return luongTrachNhiem_; 
}

void QuanLy::setLuongTrachNhiem(double luongTrachNhiem) { 
    luongTrachNhiem_ = luongTrachNhiem; 
}

// 3. Định nghĩa lại phương thức TinhLuong() đa hình
double QuanLy::TinhLuong() {
    return luongCoBan_ + luongTrachNhiem_;
}

// 4. Nhập dữ liệu (Tái sử dụng hàm Nhap của lớp cha NhanVien)
void QuanLy::Nhap(std::istream& in) {
    NhanVien::Nhap(in); // Nhập maNV, hoTen, ngaySinh, diaChi
    std::cout << "Nhap luong co ban: ";
    in >> luongCoBan_;
    std::cout << "Nhap luong trach nhiem: ";
    in >> luongTrachNhiem_;
}

// 5. Xuất dữ liệu ra stream (Căn chỉnh định dạng cột khớp với các lớp con khác)
void QuanLy::Xuat(std::ostream& out) const {
    NhanVien::Xuat(out); // In thông tin cơ bản
    out << std::left << std::setw(12) << "Quan Ly"
        << std::setw(15) << std::fixed << std::setprecision(0) << luongCoBan_
        << std::setw(15) << std::fixed << std::setprecision(0) << luongTrachNhiem_
        << std::setw(18) << TinhLuong();
}

// 6. Hiển thị thông tin
void QuanLy::HienThiThongTin() const {
    this->Xuat(std::cout);
    std::cout << std::endl;
}

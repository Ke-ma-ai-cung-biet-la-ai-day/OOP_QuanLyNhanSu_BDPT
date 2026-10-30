#include "QuanLy.h"
#include <iomanip>

QuanLy::QuanLy() 
    : NhanVien(), luongCoBan_(0), luongTrachNhiem_(0), heSoChucVu_(1.0) {}

QuanLy::QuanLy(const std::string& maNhanVien, const std::string& hoTen, const std::string& ngaySinh, const std::string& diaChi,
               const int& luongCoBan, const int& luongTrachNhiem, const double& heSoChucVu)
    : NhanVien(maNhanVien, hoTen, ngaySinh, diaChi), 
      luongCoBan_(luongCoBan), luongTrachNhiem_(luongTrachNhiem), heSoChucVu_(heSoChucVu) {}

QuanLy::~QuanLy(){}
int QuanLy::getLuongCoBan() const { return luongCoBan_; }
void QuanLy::setLuongCoBan(const int& luongCoBan) { luongCoBan_ = luongCoBan; }
int QuanLy::getLuongTrachNhiem() const { return luongTrachNhiem_; }
void QuanLy::setLuongTrachNhiem(const int& luongTrachNhiem) { luongTrachNhiem_ = luongTrachNhiem; }
double QuanLy::getHeSoChucVu() const { return heSoChucVu_; }
void QuanLy::setHeSoChucVu(const double& heSoChucVu) { heSoChucVu_ = heSoChucVu; }

double QuanLy::tinhLuong() const {
    return (luongCoBan_ * heSoChucVu_) + luongTrachNhiem_;
}

void QuanLy::nhap(std::istream& in) {
    NhanVien::nhap(in);
    std::cout << "Nhap luong co ban (VND): ";
    in >> luongCoBan_;
    std::cout << "Nhap he so chuc vu (VD: 1.2, 1.5, ...): ";
    in >> heSoChucVu_;
    std::cout << "Nhap luong trach nhiem (VND): ";
    in >> luongTrachNhiem_;
}

void QuanLy::xuat(std::ostream& out) const {
    NhanVien::xuat(out);
    out << std::left 
        << std::setw(20) << "Quan Ly"
        << std::setw(18) << (std::to_string(luongCoBan_) + " VND")
        << std::setw(18) << (std::to_string(luongTrachNhiem_) + " VND")
        << std::setw(18) << ("He so chuc vu: " + std::to_string(heSoChucVu_).substr(0,3))
        << std::setw(18) << dinhDangTien(tinhLuong());
}

void QuanLy::hienThiThongTin() const{
    xuat(std::cout);
    std::cout << std::endl;
}

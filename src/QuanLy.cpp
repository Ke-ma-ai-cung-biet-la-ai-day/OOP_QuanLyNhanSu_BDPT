#include "QuanLy.h"
#include <iomanip>

QuanLy::QuanLy() 
    : NhanVien(), luongCoBan_(0.0), heSoChucVu_(1.0), luongTrachNhiem_(0.0) {}

QuanLy::QuanLy(std::string maNV, std::string hoTen, std::string ngaySinh, std::string diaChi,
               double luongCoBan, double luongTrachNhiem, double heSoChucVu)
    : NhanVien(maNV, hoTen, ngaySinh, diaChi), 
      luongCoBan_(luongCoBan), luongTrachNhiem_(luongTrachNhiem), heSoChucVu_(heSoChucVu) {}

QuanLy::~QuanLy(){}
double QuanLy::getLuongCoBan() const { return luongCoBan_; }
void QuanLy::setLuongCoBan(double luongCB) { luongCoBan_ = luongCB; }
double QuanLy::getHeSoChucVu() const { return heSoChucVu_; }
void QuanLy::setHeSoChucVu(double heSo) { heSoChucVu_ = heSo; }
double QuanLy::getLuongTrachNhiem() const { return luongTrachNhiem_; }
void QuanLy::setLuongTrachNhiem(double luongTN) { luongTrachNhiem_ = luongTN; }

double QuanLy::TinhLuong() const {
    return (luongCoBan_ * heSoChucVu_) + luongTrachNhiem_;
}

void QuanLy::Nhap(std::istream& in) {
    NhanVien::Nhap(in);
    std::cout << "Nhap luong co ban (VND): ";
    in >> luongCoBan_;
    std::cout << "Nhap he so chuc vu (VD: 1.2, 1.5): ";
    in >> heSoChucVu_;
    std::cout << "Nhap luong trach nhiem (VND): ";
    in >> luongTrachNhiem_;
}

void QuanLy::Xuat(std::ostream& out) const {
    NhanVien::Xuat(out);
    out << std::left 
        << std::setw(20) << "Quan Ly Cap Cao"
        << std::setw(18) << ("HSCV: " + std::to_string(heSoChucVu_).substr(0,3))
        << std::setw(18) << "Trach Nhiem"
        << std::setw(18) << std::fixed << std::setprecision(0) << TinhLuong();
}

void QuanLy::hienThiThongTin() const{
    Xuat(std::cout);
    std::cout << std::endl;
}

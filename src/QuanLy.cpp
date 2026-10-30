#include "QuanLy.h"
#include <iomanip>

QuanLy::QuanLy() 
    : NhanVien(), luongCoBan_(0), heSoChucVu_(1.0), luongTrachNhiem_(0) {}

QuanLy::QuanLy(const std::string& maNhanVien, const std::string& hoTen, const std::string& ngaySinh, const std::string& diaChi,
               int& luongCoBan, int& luongTrachNhiem, double& heSoChucVu)
    : NhanVien(maNhanVien, hoTen, ngaySinh, diaChi), 
      luongCoBan_(luongCoBan), luongTrachNhiem_(luongTrachNhiem), heSoChucVu_(heSoChucVu) {}

QuanLy::~QuanLy(){}
double QuanLy::getLuongCoBan() const { return luongCoBan_; }
void QuanLy::setLuongCoBan(const int& luongCB) { luongCoBan_ = luongCB; }
double QuanLy::getHeSoChucVu() const { return heSoChucVu_; }
void QuanLy::setHeSoChucVu(const int& heSo) { heSoChucVu_ = heSo; }
double QuanLy::getLuongTrachNhiem() const { return luongTrachNhiem_; }
void QuanLy::setLuongTrachNhiem(const int& luongTN) { luongTrachNhiem_ = luongTN; }

double QuanLy::tinhLuong() const {
    return (luongCoBan_ * heSoChucVu_) + luongTrachNhiem_;
}

void QuanLy::nhap(std::istream& in) {
    NhanVien::nhap(in);
    std::cout << "Nhap luong co ban (VND): ";
    in >> luongCoBan_;
    std::cout << "Nhap he so chuc vu (VD: 1.2, 1.5): ";
    in >> heSoChucVu_;
    std::cout << "Nhap luong trach nhiem (VND): ";
    in >> luongTrachNhiem_;
}

void QuanLy::xuat(std::ostream& out) const {
    NhanVien::xuat(out);
    out << std::left 
        << std::setw(20) << "Quan Ly Cap Cao"
        << std::setw(18) << ("HSCV: " + std::to_string(heSoChucVu_).substr(0,3))
        << std::setw(18) << "Trach Nhiem"
        << std::setw(18) << std::fixed << std::setprecision(0) << tinhLuong();
        << std::setw(18) << dinhDangTien(tinhLuong());
}

void QuanLy::hienThiThongTin() const{
    xuat(std::cout);
    std::cout << std::endl;
}

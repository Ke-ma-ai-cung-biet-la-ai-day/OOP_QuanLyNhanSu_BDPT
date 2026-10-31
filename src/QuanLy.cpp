#include "QuanLy.h"
#include <iostream>
#include <iomanip>
#include <string>

// Ma mau Console
namespace MauSacQuanLy {
    const std::string RESET = "\033[0m";
    const std::string XANH_CYAN = "\033[36m";
    const std::string XANH_LA = "\033[32m";
    const std::string XANH_DUONG = "\033[34m";
    const std::string VANG = "\033[33m";
    const std::string TIM = "\033[35m";
    const std::string TRANG = "\033[37m";
    const std::string DAM = "\033[1m";
}

QuanLy::QuanLy()
    : NhanVien(), luongCoBan_(0), luongTrachNhiem_(0), heSoChucVu_(1.0) {}

QuanLy::QuanLy(const std::string& maNhanVien, const std::string& hoTen, const std::string& ngaySinh, const std::string& diaChi,
               const int& luongCoBan, const int& luongTrachNhiem, const double& heSoChucVu)
    : NhanVien(maNhanVien, hoTen, ngaySinh, diaChi),
      luongCoBan_(luongCoBan), luongTrachNhiem_(luongTrachNhiem), heSoChucVu_(heSoChucVu) {}

QuanLy::~QuanLy() {}

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
    std::cout << MauSacQuanLy::XANH_CYAN
              << "\n"
              << "                 THONG TIN NHAN VIEN QUAN LY\n"
              << "===========================================================\n\n"
              << MauSacQuanLy::RESET;
    std::cout << MauSacQuanLy::XANH_LA
              << "       Nhap luong co ban (VND)       : "
              << MauSacQuanLy::TRANG;
    in >> luongCoBan_;
    std::cout << MauSacQuanLy::VANG
              << "       Nhap he so chuc vu            : "
              << MauSacQuanLy::TRANG;
    in >> heSoChucVu_;
    std::cout << MauSacQuanLy::TIM
              << "       Nhap luong trach nhiem (VND)  : "
              << MauSacQuanLy::TRANG;
    in >> luongTrachNhiem_;
    std::cout << MauSacQuanLy::XANH_CYAN
              << "\n===========================================================\n"
              << MauSacQuanLy::RESET;
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
void QuanLy::hienThiThongTin() const {
    xuat(std::cout);
    std::cout << std::endl;
}

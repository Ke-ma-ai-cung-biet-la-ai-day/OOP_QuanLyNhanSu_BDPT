#include "NhanVienSanXuat.h"
#include <iomanip>

NhanVienSanXuat::NhanVienSanXuat() 
    : NhanVien(), soSanPham_(0), donGiaSanPham_(0.0) {}

NhanVienSanXuat::NhanVienSanXuat(std::string maNV, std::string hoTen, std::string ngaySinh, std::string diaChi,
                                 int soSanPham, double donGiaSanPham)
    : NhanVien(maNV, hoTen, ngaySinh, diaChi), 
      soSanPham_(soSanPham), donGiaSanPham_(donGiaSanPham) {}

// Xác định heSoKPI_ theo 5 mốc sản phẩm
double NhanVienSanXuat::TinhHeSoKPI() const {
    if (soSanPham_ > 110) return 1.2;
    if (soSanPham_ > 100) return 1.1;
    if (soSanPham_ == 100) return 1.0;
    if (soSanPham_ >= 80) return 0.95;
    return 0.9;
}

// Lương = Sản phẩm * Đơn giá + (Sản phẩm - 100) * Đơn giá * KPI
double NhanVienSanXuat::TinhLuong() const {
    double luongCoBan = soSanPham_ * donGiaSanPham_;
    int chenhLech = soSanPham_ - DINH_MUC;
    return luongCoBan + (chenhLech * donGiaSanPham_ * TinhHeSoKPI());
}

void NhanVienSanXuat::Nhap(std::istream& in) {
    NhanVien::Nhap(in);
    std::cout << "Nhap so san pham lam duoc: ";
    in >> soSanPham_;
    std::cout << "Nhap don gia san pham (VND): ";
    in >> donGiaSanPham_;
}

void NhanVienSanXuat::Xuat(std::ostream& out) const {
    NhanVien::Xuat(out);
    out << std::left 
        << std::setw(20) << "San Xuat"
        << std::setw(18) << (std::to_string(soSanPham_) + " SP")
        << std::setw(18) << ("KPI " + std::to_string(TinhHeSoKPI()).substr(0,4))
        << std::setw(18) << std::fixed << std::setprecision(0) << TinhLuong();
}

int NhanVienSanXuat::getSoSanPham() const { return soSanPham_; }
void NhanVienSanXuat::setSoSanPham(int soSP) { soSanPham_ = soSP; }
double NhanVienSanXuat::getDonGiaSanPham() const { return donGiaSanPham_; }
void NhanVienSanXuat::setDonGiaSanPham(double donGia) { donGiaSanPham_ = donGia; }

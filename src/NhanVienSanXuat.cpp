#include "NhanVienSanXuat.h"

NhanVienSanXuat::NhanVienSanXuat() 
    : NhanVien(), soSanPham_(0), donGiaSanPham_(0.0) {}

NhanVienSanXuat::NhanVienSanXuat(const std::string& maNhanVien, const std::string& hoTen, const std::string& ngaySinh, const std::string& diaChi,
                                 int& soSanPham, int& donGiaSanPham)
    : NhanVien(maNhanVien, hoTen, ngaySinh, diaChi), 
      soSanPham_(soSanPham), donGiaSanPham_(donGiaSanPham) {}

NhanVienSanXuat::~NhanVienSanXuat(){}

int NhanVienSanXuat::getSoSanPham() const { return soSanPham_; }
void NhanVienSanXuat::setSoSanPham(const int& soSanPham) { soSanPham_ = soSanPham; }
int NhanVienSanXuat::getDonGiaSanPham() const { return donGiaSanPham_; }
void NhanVienSanXuat::setDonGiaSanPham(const int& donGiaSanPham) { donGiaSanPham_ = donGiaSanPham; }

double NhanVienSanXuat::tinhHeSoKPI() const {
    if (soSanPham_ > 110) return 1.2;
    if (soSanPham_ > 100) return 1.1;
    if (soSanPham_ == 100) return 1.0;
    if (soSanPham_ >= 80) return 0.8;
    return 0.85;
}

double NhanVienSanXuat::tinhLuong() const {
    double luongCoBan = soSanPham_ * donGiaSanPham_;
    int chenhLech = soSanPham_ - DINH_MUC;
    return luongCoBan + (chenhLech * donGiaSanPham_ * tinhHeSoKPI());
}

void NhanVienSanXuat::nhap(std::istream& in) {
    NhanVien::nhap(in);
    std::cout << "Nhap so san pham lam duoc: ";
    in >> soSanPham_;
    std::cout << "Nhap don gia san pham (VND): ";
    in >> donGiaSanPham_;
}

void NhanVienSanXuat::xuat(std::ostream& out) const {
    NhanVien::xuat(out);
    out << std::left 
        << std::setw(20) << "San xuat"
        << std::setw(18) << (std::to_string(soSanPham_) + " san pham")
        << std::setw(18) << ("KPI " + std::to_string(tinhHeSoKPI()).substr(0,3))
        << std::setw(18) << dinhDangTien(tinhLuong());
}

void NhanVienSanXuat::hienThiThongTin() const {
    xuat(std::cout);
    std::cout << std::endl;
}

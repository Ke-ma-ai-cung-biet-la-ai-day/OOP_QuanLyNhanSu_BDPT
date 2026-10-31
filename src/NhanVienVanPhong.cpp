#include "NhanVienVanPhong.h"
#include <iostream>
#include <iomanip>
#include <string>

// Ma mau Console
namespace MauSacVanPhong {
    const std::string RESET = "\033[0m";
    const std::string XANH_CYAN = "\033[36m";
    const std::string XANH_LA = "\033[32m";
    const std::string XANH_DUONG = "\033[34m";
    const std::string VANG = "\033[33m";
    const std::string TIM = "\033[35m";
    const std::string TRANG = "\033[37m";
    const std::string DAM = "\033[1m";
}

NhanVienVanPhong::NhanVienVanPhong()
    : NhanVien(), soNgayLamViec_(0), donGiaNgay_(0), soGioTangCa_(0) {}

NhanVienVanPhong::NhanVienVanPhong(const std::string& maNhanVien, const std::string& hoTen, const std::string& ngaySinh, const std::string& diaChi,
                                   const int& soNgayLamViec, const int& donGiaNgay, const int& soGioTangCa)
    : NhanVien(maNhanVien, hoTen, ngaySinh, diaChi),
      soNgayLamViec_(soNgayLamViec), donGiaNgay_(donGiaNgay), soGioTangCa_(soGioTangCa) {}

NhanVienVanPhong::~NhanVienVanPhong() {}

int NhanVienVanPhong::getSoNgayLamViec() const { return soNgayLamViec_; }
void NhanVienVanPhong::setSoNgayLamViec(const int& soNgayLamViec) { soNgayLamViec_ = soNgayLamViec; }
int NhanVienVanPhong::getDonGiaNgay() const { return donGiaNgay_; }
void NhanVienVanPhong::setDonGiaNgay(const int& donGiaNgay) { donGiaNgay_ = donGiaNgay; }
int NhanVienVanPhong::getSoGioTangCa() const { return soGioTangCa_; }
void NhanVienVanPhong::setSoGioTangCa(const int& soGioTangCa) { soGioTangCa_ = soGioTangCa; }

double NhanVienVanPhong::tinhHeSoKPI() const {
    if (soNgayLamViec_ >= 22) return 1.2;
    if (soNgayLamViec_ >= 18) return 1.0;
    return 0.9;
}
double NhanVienVanPhong::tinhLuong() const {
    double luongChinh = soNgayLamViec_ * donGiaNgay_;
    double tienOT = soGioTangCa_ * TIEN_TANG_CA;
    return luongChinh + (tienOT * tinhHeSoKPI());
}
void NhanVienVanPhong::nhap(std::istream& in) {
    NhanVien::nhap(in);

    std::cout << MauSacVanPhong::XANH_CYAN
              << "              THONG TIN NHAN VIEN VAN PHONG\n"
              << "===========================================================\n\n"
              << MauSacVanPhong::RESET;
    std::cout << MauSacVanPhong::XANH_LA
              << "       Nhap so ngay lam viec       : "
              << MauSacVanPhong::TRANG;
    in >> soNgayLamViec_;
    std::cout << MauSacVanPhong::VANG
              << "       Nhap don gia ngay (VND)     : "
              << MauSacVanPhong::TRANG;
    in >> donGiaNgay_;
    std::cout << MauSacVanPhong::TIM
              << "       Nhap so gio tang ca (OT)    : "
              << MauSacVanPhong::TRANG;
    in >> soGioTangCa_;
    std::cout << MauSacVanPhong::XANH_CYAN
              << "\n===========================================================\n"
              << MauSacVanPhong::RESET;
}
void NhanVienVanPhong::xuat(std::ostream& out) const {
    NhanVien::xuat(out);
    out << std::left
        << std::setw(20) << "Van Phong"
        << std::setw(18) << (std::to_string(soNgayLamViec_) + " ngay")
        << std::setw(18) << (std::to_string(soGioTangCa_) + "gio tang ca (KPI " + std::to_string(tinhHeSoKPI()).substr(0,3) + ")")
        << std::setw(18) << dinhDangTien(tinhLuong());
}
void NhanVienVanPhong::hienThiThongTin() const {
    xuat(std::cout);
    std::cout << std::endl;
}


#include "NhanVien.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

// Ma mau Console
namespace MauSacNhanVien {
    const std::string RESET = "\033[0m";
    const std::string XANH_CYAN = "\033[36m";
    const std::string XANH_LA = "\033[32m";
    const std::string XANH_DUONG = "\033[34m";
    const std::string VANG = "\033[33m";
    const std::string TIM = "\033[35m";
    const std::string TRANG = "\033[37m";
    const std::string DAM = "\033[1m";
}

NhanVien::NhanVien() {
    maNhanVien_ = "";
    hoTen_ = "";
    ngaySinh_ = "";
    diaChi_ = "";
}

NhanVien::NhanVien(const std::string& maNhanVien, const std::string& hoTen, const std::string& ngaySinh, const std::string& diaChi) {
    maNhanVien_ = maNhanVien;
    hoTen_ = hoTen;
    ngaySinh_ = ngaySinh;
    diaChi_ = diaChi;
}

NhanVien::~NhanVien() {}

const std::string& NhanVien::getMaNhanVien() const { return maNhanVien_; }
void NhanVien::setMaNhanVien(const std::string& maNhanVien) { maNhanVien_ = maNhanVien; }
const std::string& NhanVien::getHoTen() const { return hoTen_; }
void NhanVien::setHoTen(const std::string& hoTen) { hoTen_ = hoTen; }
const std::string& NhanVien::getNgaySinh() const { return ngaySinh_; }
void NhanVien::setNgaySinh(const std::string& ngaySinh) { ngaySinh_ = ngaySinh; }
const std::string& NhanVien::getDiaChi() const { return diaChi_; }
void NhanVien::setDiaChi(const std::string& diaChi) { diaChi_ = diaChi; }

std::string NhanVien::dinhDangTien(double soTien) const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(0) << soTien;
    std::string s = oss.str();
    int index = (int)s.length() - 3;
    while (index > 0) {
        s.insert(index, ".");
        index -= 3;
    }
    return s;
}

void NhanVien::nhap(std::istream& in) {
    std::cout << MauSacNhanVien::XANH_CYAN << MauSacNhanVien::DAM
              << "\n"
              << "===========================================================\n"
              << "                    NHAP THONG TIN NHAN VIEN\n"
              << "===========================================================\n\n"
              << MauSacNhanVien::RESET;

    std::cout << MauSacNhanVien::XANH_LA
              << "       Nhap ma nhan vien        : "
              << MauSacNhanVien::TRANG;
    std::getline(in >> std::ws, maNhanVien_);

    std::cout << MauSacNhanVien::VANG
              << "       Nhap ho va ten           : "
              << MauSacNhanVien::TRANG;
    std::getline(in >> std::ws, hoTen_);

    std::cout << MauSacNhanVien::TIM
              << "       Nhap ngay sinh (dd/mm/yyyy): "
              << MauSacNhanVien::TRANG;
    std::getline(in >> std::ws, ngaySinh_);

    std::cout << MauSacNhanVien::XANH_DUONG
              << "       Nhap dia chi             : "
              << MauSacNhanVien::TRANG;
    std::getline(in >> std::ws, diaChi_);

    std::cout << MauSacNhanVien::XANH_CYAN
              << "\n===========================================================\n"
              << MauSacNhanVien::RESET;
}
void NhanVien::xuat(std::ostream& out) const {
    out << std::left
        << std::setw(10) << maNhanVien_
        << std::setw(22) << hoTen_
        << std::setw(14) << ngaySinh_
        << std::setw(20) << diaChi_;
}
void NhanVien::hienThiThongTin() const {
    this->xuat(std::cout);
}
std::istream& operator>>(std::istream& in, NhanVien& nv) {
    nv.nhap(in);
    return in;
}
std::ostream& operator<<(std::ostream& out, const NhanVien& nv) {
    nv.xuat(out);
    return out;
}

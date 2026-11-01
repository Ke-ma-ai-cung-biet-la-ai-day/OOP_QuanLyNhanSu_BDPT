#include "QuanLy.h"
#include <iostream>
#include <iomanip>
#include <string>

namespace MauSacQuanLy {
    const std::string RESET = "\033[0m"; 
        const std::string CAM = "\033[38;5;208m";
    const std::string HONG = "\033[38;5;206m";
        const std::string VANG_SANG = "\033[38;5;228m"; 
        const std::string TRANG = "\033[37m"; 
        const std::string DO = "\033[31m";
}

QuanLy::QuanLy() : NhanVien(), luongCoBan_(0), luongTrachNhiem_(0), heSoChucVu_(1.0) {}
QuanLy::QuanLy(const std::string& ma, const std::string& ten, const std::string& ns, const std::string& dc,
    const int& lcb, const int& ltn, const double& hscv)
    : NhanVien(ma, ten, ns, dc), luongCoBan_(lcb), luongTrachNhiem_(ltn), heSoChucVu_(hscv) {
}
QuanLy::~QuanLy() {}

int QuanLy::getLuongCoBan() const { return luongCoBan_; }
void QuanLy::setLuongCoBan(const int& lcb) { luongCoBan_ = lcb; }
int QuanLy::getLuongTrachNhiem() const { return luongTrachNhiem_; }
void QuanLy::setLuongTrachNhiem(const int& ltn) { luongTrachNhiem_ = ltn; }
double QuanLy::getHeSoChucVu() const { return heSoChucVu_; }
void QuanLy::setHeSoChucVu(const double& hscv) { heSoChucVu_ = hscv; }

double QuanLy::tinhLuong() const {
    return (luongCoBan_ * heSoChucVu_) + luongTrachNhiem_; 
}

void QuanLy::nhap(std::istream& in) {
    NhanVien::nhap(in); 

        const int CHIEU_RONG_KHUNG = 66; 
        const int LE_CAN_GIUA = (142 - CHIEU_RONG_KHUNG) / 2; 
        const int KHOANG_TRONG = CHIEU_RONG_KHUNG - 4;
        const std::string pad(LE_CAN_GIUA, ' '); 

        auto inDongNhapDuLieu = [&](const std::string& mau, const std::string& nhan, const std::string& strVal) {
        int doDaiDuLieu = (int)strVal.length(); 
            int khoangDemPhai = KHOANG_TRONG - 2 - 26 - 2 - doDaiDuLieu; 
            if (khoangDemPhai < 1) khoangDemPhai = 1; 

                std::cout << "\033[1A\r" << pad
                << MauSacQuanLy::CAM << "||  " << MauSacQuanLy::RESET
                << mau << std::left << std::setw(26) << nhan
                << ": " << MauSacQuanLy::RESET
                << MauSacQuanLy::TRANG << strVal << MauSacQuanLy::RESET
                << std::string(khoangDemPhai, ' ')
                << MauSacQuanLy::CAM << "||\n" << MauSacQuanLy::RESET;
        };

    auto inDongLoi = [&](const std::string& msg) {
        int lePhaiLoi = KHOANG_TRONG - 2 - static_cast<int>(msg.length());
        if (lePhaiLoi < 1) lePhaiLoi = 1;

        std::cout << pad << MauSacQuanLy::CAM << "||  " << MauSacQuanLy::RESET
            << MauSacQuanLy::DO << msg << MauSacQuanLy::RESET
            << std::string(lePhaiLoi, ' ')
            << MauSacQuanLy::CAM << "||\n" << MauSacQuanLy::RESET;
        };

    // Nhap Luong co ban (10.000.000 - 20.000.000)
    while (true) {
        std::cout << pad << MauSacQuanLy::CAM << "||  " << MauSacQuanLy::RESET
            << MauSacQuanLy::CAM << std::left << std::setw(26) << "Luong co ban (VND)"
            << ": " << MauSacQuanLy::RESET;
        if (in >> luongCoBan_ && luongCoBan_ >= 10000000 && luongCoBan_ <= 20000000) {
            inDongNhapDuLieu(MauSacQuanLy::CAM, "Luong co ban (VND)", std::to_string(luongCoBan_));
            break;
        }
        in.clear();
        std::string dem;
        std::getline(in, dem);
        inDongLoi("Luong tu 10.000.000 den 20.000.000!");
    }

    // Nhap He so chuc vu (1.2 - 2.5)
    while (true) {
        std::cout << pad << MauSacQuanLy::CAM << "||  " << MauSacQuanLy::RESET
            << MauSacQuanLy::VANG_SANG << std::left << std::setw(26) << "He so chuc vu"
            << ": " << MauSacQuanLy::RESET;
        if (in >> heSoChucVu_ && heSoChucVu_ >= 1.2 && heSoChucVu_ <= 2.5) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2) << heSoChucVu_;
            inDongNhapDuLieu(MauSacQuanLy::VANG_SANG, "He so chuc vu", oss.str());
            break;
        }
        in.clear();
        std::string dem;
        std::getline(in, dem);
        inDongLoi("He so chuc vu tu 1.2 den 2.5!");
    }

    // Nhap Luong trach nhiem (2.000.000 - 8.000.000)
    while (true) {
        std::cout << pad << MauSacQuanLy::CAM << "||  " << MauSacQuanLy::RESET
            << MauSacQuanLy::HONG << std::left << std::setw(26) << "Luong trach nhiem (VND)"
            << ": " << MauSacQuanLy::RESET;
        if (in >> luongTrachNhiem_ && luongTrachNhiem_ >= 2000000 && luongTrachNhiem_ <= 8000000) {
            inDongNhapDuLieu(MauSacQuanLy::HONG, "Luong trach nhiem (VND)", std::to_string(luongTrachNhiem_));
            break;
        }
        in.clear();
        std::string dem;
        std::getline(in, dem);
        inDongLoi("Luong tu 2.000.000 den 8.000.000!");
    }

    std::string boDem;
    std::getline(in, boDem);

        std::cout << pad
        << MauSacQuanLy::CAM
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacQuanLy::RESET;
}

void QuanLy::xuat(std::ostream& out) const {
    NhanVien::xuat(out); 
        out << std::left
        << std::setw(20) << "Quan Ly"
        << std::setw(18) << (std::to_string(luongCoBan_) + " VND")
        << std::setw(18) << (std::to_string(luongTrachNhiem_) + " VND")
        << std::setw(18) << ("He so chuc vu: " + std::to_string(heSoChucVu_).substr(0, 3))
        << std::setw(18) << dinhDangTien(tinhLuong()); 
}

void QuanLy::hienThiThongTin() const {
    xuat(std::cout); 
        std::cout << std::endl; 
}
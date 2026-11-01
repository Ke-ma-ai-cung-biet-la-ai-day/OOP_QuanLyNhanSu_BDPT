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
    const int LE_CAN_GIUA = (142 - CHIEU_RONG_KHUNG) / 2; // 38 khoang trang
    const int KHOANG_TRONG = CHIEU_RONG_KHUNG - 4;        // 62 ky tu ben trong ||
    const std::string pad(LE_CAN_GIUA, ' ');

    // Lambda in dong nhap lieu: 62 - (2 + 26 + 2) - doDai = 32 - doDai
    auto inDongNhapDuLieu = [&](const std::string& mau, const std::string& nhan, const std::string& strVal) {
        int doDaiDuLieu = static_cast<int>(strVal.length());
        int khoangDemPhai = 32 - doDaiDuLieu;
        if (khoangDemPhai < 0) khoangDemPhai = 0;

        std::cout << "\033[1A\r" << pad
            << MauSacQuanLy::CAM << "||  " << MauSacQuanLy::RESET
            << mau << std::left << std::setw(26) << nhan
            << ": " << MauSacQuanLy::RESET
            << MauSacQuanLy::TRANG << strVal << MauSacQuanLy::RESET
            << std::string(khoangDemPhai, ' ')
            << MauSacQuanLy::CAM << "||\n" << MauSacQuanLy::RESET;
        };

    // Lambda in dong thong bao loi mau do: 62 - 2 (le trai) - doDaiLoi = 60 - doDaiLoi
    auto inDongLoi = [&](const std::string& msg) {
        int lePhaiLoi = 60 - static_cast<int>(msg.length());
        if (lePhaiLoi < 0) lePhaiLoi = 0;

        std::cout << pad << MauSacQuanLy::CAM << "||  " << MauSacQuanLy::RESET
            << MauSacQuanLy::DO << msg << MauSacQuanLy::RESET
            << std::string(lePhaiLoi, ' ')
            << MauSacQuanLy::CAM << "||\n" << MauSacQuanLy::RESET;
        };

    // 1. Nhap Luong co ban (10.000.000 - 20.000.000)
    while (true) {
        std::cout << pad << MauSacQuanLy::CAM << "||  " << MauSacQuanLy::RESET
            << MauSacQuanLy::CAM << std::left << std::setw(26) << "Luong co ban (VND)"
            << ": " << MauSacQuanLy::RESET;

        std::string s;
        std::getline(in, s);
        if (!s.empty() && s.back() == '\r') s.pop_back();

        inDongNhapDuLieu(MauSacQuanLy::CAM, "Luong co ban (VND)", s);

        try {
            size_t pos = 0;
            int val = std::stoi(s, &pos);
            if (pos == s.length() && val >= 10000000 && val <= 20000000) {
                luongCoBan_ = val;
                break;
            }
        }
        catch (...) {}

        inDongLoi("Luong tu 10.000.000 den 20.000.000!");
    }

    // 2. Nhap He so chuc vu (1.2 - 2.5)
    while (true) {
        std::cout << pad << MauSacQuanLy::CAM << "||  " << MauSacQuanLy::RESET
            << MauSacQuanLy::VANG_SANG << std::left << std::setw(26) << "He so chuc vu"
            << ": " << MauSacQuanLy::RESET;

        std::string s;
        std::getline(in, s);
        if (!s.empty() && s.back() == '\r') s.pop_back();

        inDongNhapDuLieu(MauSacQuanLy::VANG_SANG, "He so chuc vu", s);

        try {
            size_t pos = 0;
            double val = std::stod(s, &pos);
            if (pos == s.length() && val >= 1.2 && val <= 2.5) {
                heSoChucVu_ = val;
                break;
            }
        }
        catch (...) {}

        inDongLoi("He so chuc vu tu 1.2 den 2.5!");
    }

    // 3. Nhap Luong trach nhiem (2.000.000 - 8.000.000)
    while (true) {
        std::cout << pad << MauSacQuanLy::CAM << "||  " << MauSacQuanLy::RESET
            << MauSacQuanLy::HONG << std::left << std::setw(26) << "Luong trach nhiem (VND)"
            << ": " << MauSacQuanLy::RESET;

        std::string s;
        std::getline(in, s);
        if (!s.empty() && s.back() == '\r') s.pop_back();

        inDongNhapDuLieu(MauSacQuanLy::HONG, "Luong trach nhiem (VND)", s);

        try {
            size_t pos = 0;
            int val = std::stoi(s, &pos);
            if (pos == s.length() && val >= 2000000 && val <= 8000000) {
                luongTrachNhiem_ = val;
                break;
            }
        }
        catch (...) {}

        inDongLoi("Luong tu 2.000.000 den 8.000.000!");
    }

    // Dong day hop
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
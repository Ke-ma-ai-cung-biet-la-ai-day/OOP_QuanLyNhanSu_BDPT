#include "NhanVienSanXuat.h"
#include <iostream>
#include <iomanip>
#include <string>

namespace MauSacSanXuat {
    const std::string RESET = "\033[0m";
        const std::string CAM = "\033[38;5;208m";
    const std::string HONG = "\033[38;5;206m";
        const std::string TRANG = "\033[37m";
        const std::string DO = "\033[31m";
}

NhanVienSanXuat::NhanVienSanXuat() : NhanVien(), soSanPham_(0), donGiaSanPham_(0) {}
NhanVienSanXuat::NhanVienSanXuat(const std::string& ma, const std::string& ten, const std::string& ns, const std::string& dc,
    const int& ssp, const int& dgsp)
    : NhanVien(ma, ten, ns, dc), soSanPham_(ssp), donGiaSanPham_(dgsp) {
}
NhanVienSanXuat::~NhanVienSanXuat() {}

int NhanVienSanXuat::getSoSanPham() const { return soSanPham_; }
void NhanVienSanXuat::setSoSanPham(const int& ssp) { soSanPham_ = ssp; }
int NhanVienSanXuat::getDonGiaSanPham() const { return donGiaSanPham_; }
void NhanVienSanXuat::setDonGiaSanPham(const int& dgsp) { donGiaSanPham_ = dgsp; }

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

    const int CHIEU_RONG_KHUNG = 66;
    const int LE_CAN_GIUA = (142 - CHIEU_RONG_KHUNG) / 2;
    const int KHOANG_TRONG = CHIEU_RONG_KHUNG - 4;
    const std::string pad(LE_CAN_GIUA, ' ');

    auto inVaDocSo = [&](const std::string& mau, const std::string& nhan, int minVal, int maxVal, int& giaTri) {
        while (true) {
            std::cout << pad
                << MauSacSanXuat::CAM << "||  " << MauSacSanXuat::RESET
                << mau << std::left << std::setw(26) << nhan
                << ": " << MauSacSanXuat::RESET;

            std::string chuoiNhap;
            std::getline(in >> std::ws, chuoiNhap);

            int doDaiDuLieu = static_cast<int>(chuoiNhap.length());
            int khoangDemPhai = KHOANG_TRONG - 4 - 26 - doDaiDuLieu;
            if (khoangDemPhai < 0) khoangDemPhai = 0;

            std::cout << "\033[1A\r" << pad
                << MauSacSanXuat::CAM << "||  " << MauSacSanXuat::RESET
                << mau << std::left << std::setw(26) << nhan
                << ": " << MauSacSanXuat::RESET
                << MauSacSanXuat::TRANG << chuoiNhap << MauSacSanXuat::RESET
                << std::string(khoangDemPhai, ' ')
                << MauSacSanXuat::CAM << "||\n" << MauSacSanXuat::RESET;

            try {
                size_t pos = 0;
                int val = std::stoi(chuoiNhap, &pos);
                if (pos == chuoiNhap.length() && val >= minVal && val <= maxVal) {
                    giaTri = val;
                    break;
                }
            }
            catch (...) {}

            std::string msg = "Gia tri tu " + std::to_string(minVal) + " den " + std::to_string(maxVal) + "!";
            int lePhaiLoi = KHOANG_TRONG - 2 - static_cast<int>(msg.length());
            if (lePhaiLoi < 0) lePhaiLoi = 0;

            std::cout << pad << MauSacSanXuat::CAM << "||  " << MauSacSanXuat::RESET
                << MauSacSanXuat::DO << msg << MauSacSanXuat::RESET
                << std::string(lePhaiLoi, ' ')
                << MauSacSanXuat::CAM << "||\n" << MauSacSanXuat::RESET;
        }
        };

    inVaDocSo(MauSacSanXuat::CAM, "So san pham lam duoc", 0, 500, soSanPham_);
    inVaDocSo(MauSacSanXuat::HONG, "Don gia san pham (VND)", 40000, 80000, donGiaSanPham_);

    std::cout << pad
        << MauSacSanXuat::CAM
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacSanXuat::RESET;
}

void NhanVienSanXuat::xuat(std::ostream& out) const {
    NhanVien::xuat(out); 
        out << std::left
        << std::setw(20) << "San xuat"
        << std::setw(18) << (std::to_string(soSanPham_) + " san pham")
        << std::setw(18) << ("KPI " + std::to_string(tinhHeSoKPI()).substr(0, 3))
        << std::setw(18) << dinhDangTien(tinhLuong());
}

void NhanVienSanXuat::hienThiThongTin() const {
    xuat(std::cout);
        std::cout << std::endl;
}
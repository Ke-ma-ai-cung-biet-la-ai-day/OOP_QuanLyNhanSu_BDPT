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

    // Ham template lambda doc duoc ca int va double, tu dong xoa dong loi
    auto inVaDocSo = [&](auto& giaTri, const std::string& mau, const std::string& nhan,
        double minVal, double maxVal, const std::string& msg, bool laSoThuc = false) {
            bool coLoi = false;
            while (true) {
                std::cout << pad << MauSacQuanLy::CAM << "||  " << MauSacQuanLy::RESET
                    << mau << std::left << std::setw(26) << nhan
                    << ": " << MauSacQuanLy::RESET;

                std::string s;
                std::getline(in >> std::ws, s);

                bool hopLe = false;
                try {
                    size_t pos = 0;
                    if (laSoThuc) {
                        double val = std::stod(s, &pos);
                        if (pos == s.length() && val >= minVal && val <= maxVal) {
                            giaTri = val;
                            hopLe = true;
                        }
                    }
                    else {
                        int val = std::stoi(s, &pos);
                        if (pos == s.length() && val >= minVal && val <= maxVal) {
                            giaTri = val;
                            hopLe = true;
                        }
                    }
                }
                catch (...) {}

                // Neu nhap dung: xoa dong loi truoc do va dong nhap tam, day dong dung len co vien ||
                if (hopLe) {
                    if (coLoi) {
                        std::cout << "\033[1A\033[2K\r"; // Xoa dong vua go
                        std::cout << "\033[1A\033[2K\r"; // Xoa dong loi do
                    }
                    else {
                        std::cout << "\033[1A\033[2K\r"; // Xoa dong vua go
                    }

                    int doDaiDuLieu = static_cast<int>(s.length());
                    int khoangDemPhai = 32 - doDaiDuLieu;
                    if (khoangDemPhai < 0) khoangDemPhai = 0;

                    std::cout << pad
                        << MauSacQuanLy::CAM << "||  " << MauSacQuanLy::RESET
                        << mau << std::left << std::setw(26) << nhan
                        << ": " << MauSacQuanLy::RESET
                        << MauSacQuanLy::TRANG << s << MauSacQuanLy::RESET
                        << std::string(khoangDemPhai, ' ')
                        << MauSacQuanLy::CAM << "||\n" << MauSacQuanLy::RESET;
                    break;
                }

                // Neu nhap sai: xoa dong vua go de in lai dong loi mau do khong co vien ||
                if (coLoi) {
                    std::cout << "\033[1A\033[2K\r";
                    std::cout << "\033[1A\033[2K\r";
                }
                else {
                    std::cout << "\033[1A\033[2K\r";
                }

                std::cout << pad << "    " << MauSacQuanLy::DO << ">> " << msg << MauSacQuanLy::RESET << "\n";
                coLoi = true;
            }
        };

    // Su dung duy nhat 1 ham cho ca 3 thuoc tinh
    inVaDocSo(luongCoBan_, MauSacQuanLy::CAM, "Luong co ban (VND)", 10000000, 20000000, "Luong tu 10.000.000 den 20.000.000!");
    inVaDocSo(heSoChucVu_, MauSacQuanLy::VANG_SANG, "He so chuc vu", 1.2, 2.5, "He so chuc vu tu 1.2 den 2.5!", true);
    inVaDocSo(luongTrachNhiem_, MauSacQuanLy::HONG, "Luong trach nhiem (VND)", 2000000, 8000000, "Luong tu 2.000.000 den 8.000.000!");

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
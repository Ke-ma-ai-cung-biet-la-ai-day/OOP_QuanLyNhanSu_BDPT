#include "NhanVienVanPhong.h"
#include <iostream>
#include <iomanip>
#include <string>

namespace MauSacVanPhong {
    const std::string RESET = "\033[0m"; 
        const std::string CAM = "\033[38;5;208m";
    const std::string HONG = "\033[38;5;206m"; 
        const std::string XANH_LA_SANG = "\033[38;5;120m";
        const std::string TRANG = "\033[37m"; 
        const std::string DO = "\033[31m";
}

NhanVienVanPhong::NhanVienVanPhong()
    : NhanVien(), soNgayLamViec_(0), donGiaNgay_(0), soGioTangCa_(0) {
}

NhanVienVanPhong::NhanVienVanPhong(const std::string& ma, const std::string& ten, const std::string& ns, const std::string& dc,
    const int& snl, const int& dgn, const int& sgtc)
    : NhanVien(ma, ten, ns, dc), soNgayLamViec_(snl), donGiaNgay_(dgn), soGioTangCa_(sgtc) {
}

NhanVienVanPhong::~NhanVienVanPhong() {}

int NhanVienVanPhong::getSoNgayLamViec() const { return soNgayLamViec_; }
void NhanVienVanPhong::setSoNgayLamViec(const int& snl) { soNgayLamViec_ = snl; }
int NhanVienVanPhong::getDonGiaNgay() const { return donGiaNgay_; }
void NhanVienVanPhong::setDonGiaNgay(const int& dgn) { donGiaNgay_ = dgn; }
int NhanVienVanPhong::getSoGioTangCa() const { return soGioTangCa_; }
void NhanVienVanPhong::setSoGioTangCa(const int& sgtc) { soGioTangCa_ = sgtc; }

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

    const int CHIEU_RONG_KHUNG = 66;
    const int LE_CAN_GIUA = (142 - CHIEU_RONG_KHUNG) / 2;
    const int KHOANG_TRONG = CHIEU_RONG_KHUNG - 4;
    const std::string pad(LE_CAN_GIUA, ' ');

    auto inVaDocSo = [&](const std::string& mau, const std::string& nhan, int minVal, int maxVal, int& giaTri) {
        bool coLoi = false;
        while (true) {
            std::cout << pad
                << MauSacVanPhong::CAM << "||  " << MauSacVanPhong::RESET
                << mau << std::left << std::setw(26) << nhan
                << ": " << MauSacVanPhong::RESET;

            std::string chuoiNhap;
            std::getline(in >> std::ws, chuoiNhap);

            bool hopLe = false;
            try {
                size_t pos = 0;
                int val = std::stoi(chuoiNhap, &pos);
                if (pos == chuoiNhap.length() && val >= minVal && val <= maxVal) {
                    giaTri = val;
                    hopLe = true;
                }
            }
            catch (...) {}

            if (hopLe) {
                if (coLoi) {
                    std::cout << "\033[1A\033[2K\r"; // Xóa dòng vừa gõ
                    std::cout << "\033[1A\033[2K\r"; // Xóa dòng lỗi
                }
                else {
                    std::cout << "\033[1A\033[2K\r"; // Xóa dòng vừa gõ
                }

                int doDaiDuLieu = static_cast<int>(chuoiNhap.length());
                int khoangDemPhai = 32 - doDaiDuLieu;
                if (khoangDemPhai < 0) khoangDemPhai = 0;

                std::cout << pad
                    << MauSacVanPhong::CAM << "||  " << MauSacVanPhong::RESET
                    << mau << std::left << std::setw(26) << nhan
                    << ": " << MauSacVanPhong::RESET
                    << MauSacVanPhong::TRANG << chuoiNhap << MauSacVanPhong::RESET
                    << std::string(khoangDemPhai, ' ')
                    << MauSacVanPhong::CAM << "||\n" << MauSacVanPhong::RESET;
                break;
            }

            if (coLoi) {
                std::cout << "\033[1A\033[2K\r";
                std::cout << "\033[1A\033[2K\r";
            }
            else {
                std::cout << "\033[1A\033[2K\r";
            }

            std::string msg = "Gia tri tu " + std::to_string(minVal) + " den " + std::to_string(maxVal) + "!";
            std::cout << pad << "    " << MauSacVanPhong::DO << ">> " << msg << MauSacVanPhong::RESET << "\n";
            coLoi = true;
        }
    };

    inVaDocSo(MauSacVanPhong::CAM, "So ngay lam viec", 0, 31, soNgayLamViec_);
    inVaDocSo(MauSacVanPhong::HONG, "Don gia ngay (VND)", 200000, 500000, donGiaNgay_);
    inVaDocSo(MauSacVanPhong::XANH_LA_SANG, "So gio tang ca (OT)", 0, 40, soGioTangCa_);

    std::cout << pad
        << MauSacVanPhong::CAM
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacVanPhong::RESET;
}

void NhanVienVanPhong::xuat(std::ostream& out) const {
    NhanVien::xuat(out); 
        out << std::left
        << std::setw(20) << "Van Phong"
        << std::setw(18) << (std::to_string(soNgayLamViec_) + " ngay")
        << std::setw(18) << (std::to_string(soGioTangCa_) + "gio tang ca (KPI " + std::to_string(tinhHeSoKPI()).substr(0, 3) + ")")
        << std::setw(18) << dinhDangTien(tinhLuong()); 
}

void NhanVienVanPhong::hienThiThongTin() const {
    xuat(std::cout);
        std::cout << std::endl;
}
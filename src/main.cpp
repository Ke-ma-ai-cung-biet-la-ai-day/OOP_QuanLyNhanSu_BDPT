#include "QuanLyNhanSu.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

// Ma mau ANSI Console
namespace MauSac {
    const std::string RESET = "\033[0m";
    const std::string XANH_CYAN = "\033[36m";
    const std::string XANH_LA = "\033[32m";
    const std::string DO = "\033[31m";
    const std::string VANG = "\033[33m";
    const std::string TIM = "\033[35m";
    const std::string TRANG = "\033[37m";
    const std::string DAM = "\033[1m";
}

void hienThiMenu() {
    const int CHIEU_RONG = 142;
    const int KHOANG_TRONG = CHIEU_RONG - 4; // 138 ky tu ben trong 2 bien '||'

    auto inDongVienNgang = [&]() {
        std::cout << MauSac::XANH_CYAN
            << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
            << MauSac::RESET;
        };

    auto inDongCanGiua = [&](const std::string& mauChu, const std::string& noiDung) {
        int doDai = static_cast<int>(noiDung.length());
        int leTrai = (KHOANG_TRONG - doDai) / 2;
        int lePhai = KHOANG_TRONG - doDai - leTrai;

        std::cout << MauSac::XANH_CYAN << "||" << MauSac::RESET
            << std::string(leTrai, ' ')
            << mauChu << noiDung << MauSac::RESET
            << std::string(lePhai, ' ')
            << MauSac::XANH_CYAN << "||" << MauSac::RESET << "\n";
        };

    const int DO_RONG_KHOI = 26;
    const int LE_KHOI = (KHOANG_TRONG - DO_RONG_KHOI) / 2; // 56 khoang trang
    const int DEM_PHAI = KHOANG_TRONG - LE_KHOI - DO_RONG_KHOI;

    auto inDongLuaChon = [&](const std::string& mauChu, const std::string& text) {
        std::cout << MauSac::XANH_CYAN << "||" << MauSac::RESET
            << std::string(LE_KHOI, ' ')
            << mauChu << std::left << std::setw(DO_RONG_KHOI) << text << MauSac::RESET
            << std::string(DEM_PHAI, ' ')
            << MauSac::XANH_CYAN << "||" << MauSac::RESET << "\n";
        };

    std::cout << "\n";
    inDongVienNgang();
    inDongCanGiua(MauSac::XANH_CYAN + MauSac::DAM, "HE THONG QUAN LY NHAN SU");

    std::cout << MauSac::XANH_CYAN
        << "||" << std::string(KHOANG_TRONG, '-') << "||\n"
        << MauSac::RESET;

    inDongLuaChon(MauSac::XANH_LA, "[1] Them nhan vien moi");
    inDongLuaChon(MauSac::DO, "[2] Xoa nhan vien theo ma");
    inDongLuaChon(MauSac::VANG, "[3] Tim kiem nhan vien");
    inDongLuaChon(MauSac::TIM, "[4] Hien thi thong tin");
    inDongLuaChon(MauSac::TRANG, "[5] Thoat chuong trinh");

    inDongVienNgang();

    const std::string cauNhacMenu = ">> Nhap lua chon chuc nang (1-5): ";
    const int leNhapMenu = (CHIEU_RONG - static_cast<int>(cauNhacMenu.length())) / 2 - 1;

    std::cout << std::string(leNhapMenu, ' ')
        << MauSac::VANG << MauSac::DAM
        << cauNhacMenu
        << MauSac::RESET;
}

// Ham dung cho nhan Enter
void dungManHinhChoEnter() {
    const std::string cauNhac = ">> Nhan Enter de ve Menu chinh...";
    const int le = (142 - static_cast<int>(cauNhac.length())) / 2;

    std::cout << "\n" << std::string(le, ' ')
        << MauSac::VANG << MauSac::DAM << cauNhac << MauSac::RESET;

    std::string boDem;
    std::getline(std::cin, boDem);
}

// Ham don sach man hinh console
void xoaManHinh() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

int main() {
    // Khoi tao doi tuong, tu dong doc file NhanVien.txt
    QuanLyNhanSu ql;

        // Lambda can giua dong thong bao loi dua tren chieu rong chuan 142
        auto inLoiCanGiua = [](const std::string& thongBao) {
        const int CHIEU_RONG = 142;
        int le = (CHIEU_RONG - static_cast<int>(thongBao.length())) / 2;
        if (le < 0) le = 0;
        std::cout << "\n" << std::string(le, ' ')
            << MauSac::DO << MauSac::DAM << thongBao << MauSac::RESET << "\n";
        };

    int luaChon = 0; 
        while (true) {
            hienThiMenu(); 
                if (!(std::cin >> luaChon)) {
                    std::cin.clear(); 
                        std::string dem; 
                        std::getline(std::cin, dem); 

                        // Can giua khi nguoi dung nhap chu hoac ky tu dac biet
                        inLoiCanGiua("LUA CHON KHONG HOP LE, VUI LONG NHAP SO TU 1 DEN 5!");
                    dungManHinhChoEnter();
                    xoaManHinh();
                    continue; 
                }
            std::string dem;
                std::getline(std::cin, dem); 
                std::cout << "\n\n"; 

                switch (luaChon) {
                case 1: 
                    std::cout << MauSac::XANH_LA; 
                    ql.nhapDanhSach(); 
                    std::cout << MauSac::RESET; 
                    break; 
                case 2: {
                    std::cout << MauSac::DO; 
                        std::string maXoa; 
                        ql.giaoDienKetQuaXoa(ql, maXoa); 
                        std::cout << MauSac::RESET; 
                        break; 
                }
                case 3: 
                    std::cout << MauSac::VANG;
                    ql.timKiemMenu(); 
                    std::cout << MauSac::RESET; 
                    break; 
                case 4: 
                    std::cout << MauSac::TIM; 
                    ql.hienThiDanhSach();
                    std::cout << MauSac::RESET; 
                    break; 
                case 5: 
                    std::cout << MauSac::XANH_LA; 
                    ql.thoatChuongTrinh(); 
                    std::cout << MauSac::RESET;
                    return 0; 
                default: 
                    // Can giua khi nguoi dung nhap so ngoai khoang 1-5 (vi du: 0, 6, 99...)
                    inLoiCanGiua("LUA CHON PHAI NAM TRONG KHOANG TU 1 DEN 5!");
                    break; 
                }

            // Cho nguoi dung doc ket qua xong nhan Enter moi xoa man hinh ve Menu
            dungManHinhChoEnter();
            xoaManHinh();
        } 
    return 0;
}
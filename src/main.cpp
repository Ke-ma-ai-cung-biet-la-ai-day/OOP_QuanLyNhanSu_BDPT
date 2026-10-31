#include "QuanLyNhanSu.h"
#include <iostream>
#include <string>

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
    std::cout << MauSac::XANH_CYAN
        << "\n================ MENU QUAN LY NHAN SU ================\n"
        << MauSac::RESET
        << MauSac::XANH_LA
        << "[1] Them nhan vien moi\n"
        << MauSac::DO
        << "[2] Xoa nhan vien theo Ma\n"
        << MauSac::VANG
        << "[3] Tim kiem nhan vien\n"
        << MauSac::TIM
        << "[4] Hien thi thong tin\n"
        << MauSac::TRANG
        << "[5] Thoat chuong trinh\n"
        << MauSac::XANH_CYAN
        << "======================================================\n"
        << MauSac::VANG << MauSac::DAM
        << "Nhap lua chon (1-5): "
        << MauSac::RESET;
}
int main() {
    // Khi khoi tao doi tuong, file "NhanVien.txt" se duoc tu dong nap ngam
    QuanLyNhanSu ql;

    int luaChon = 0;
    while (true) {
        hienThiMenu();
        if (!(std::cin >> luaChon)) {
            std::cin.clear();
            std::string dem;
            std::getline(std::cin, dem);
            std::cout << MauSac::DO
                << "Lua chon khong hop le, vui long nhap so tu 1 den 5!\n"
                << MauSac::RESET;
            continue;
        }
        // Xoa ky tu '\n' con sot lai trong bo dem sau khi nhap so thanh cong
        std::string dem;
        std::getline(std::cin, dem);

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
            std::cout << MauSac::DO
                << "Lua chon phai tu 1 den 5!\n"
                << MauSac::RESET;
            break;
        }
    }
    return 0;
}

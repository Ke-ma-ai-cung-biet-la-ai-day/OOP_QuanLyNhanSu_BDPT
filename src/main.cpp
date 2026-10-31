#include "QuanLyNhanSu.h"
#include <iostream>
#include <string>

void hienThiMenu() {
    std::cout << "\n================ MENU QUAN LY NHAN SU ================\n"
        << "[1] Them nhan vien moi\n"
        << "[2] Xoa nhan vien theo Ma\n"
        << "[3] Tim kiem nhan vien\n"
        << "[4] Hien thi thong tin\n"
        << "[5] Thoat chuong trinh\n"
        << "======================================================\n"
        << "Nhap lua chon (1-5): ";
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
            std::cout << "Lua chon khong hop le, vui long nhap so tu 1 den 5!\n";
            continue;
        }

        // Xoa ky tu '\n' con sot lai trong bo dem sau khi nhap so thanh cong
        std::string dem;
        std::getline(std::cin, dem);

        switch (luaChon) {
        case 1:
            ql.nhapDanhSach();
            break;
        case 2: {
            std::string maXoa;
            ql.giaoDienKetQuaXoa(ql, maXoa);
            break;
        }
        case 3:
            ql.timKiemMenu();
            break;
        case 4:
            ql.hienThiDanhSach();
            break;
        case 5:
            ql.thoatChuongTrinh();
            return 0;
        default:
            std::cout << "Lua chon phai tu 1 den 5!\n";
            break;
        }
    }

    return 0;
}
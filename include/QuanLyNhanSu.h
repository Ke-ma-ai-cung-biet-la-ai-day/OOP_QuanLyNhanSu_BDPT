#include <iostream>
#include <limits>
#include <string>
#include "QuanLyNhanSu.h"

// Hàm hiển thị Menu điều khiển chính
void InMenuChinh() {
    std::cout << "\n=========================================================\n";
    std::cout << "          HE THONG QUAN LY NHAN SU - HE C++             \n";
    std::cout << "=========================================================\n";
    std::cout << "1. Them nhan vien moi (Nhap tu ban phim)\n";
    std::cout << "2. Hien thi danh sach nhan vien (Dang bang)\n";
    std::cout << "3. Tim kiem nhan vien (Theo Ma hoac Tu khoa Ten)\n";
    std::cout << "4. Xoa nhan vien theo Ma dinh danh\n";
    std::cout << "5. Sap xep danh sach (Menu da tieu chi)\n";
    std::cout << "6. Thong ke so luong va tong quy luong\n";
    std::cout << "7. Nap du lieu mau (5 nhan vien khoi tao san)\n";
    std::cout << "0. Thoat chuong trinh\n";
    std::cout << "=========================================================\n";
    std::cout << "Moi ban chon chuc nang (0-7): ";
}

int main() {
    QuanLyNhanSu ql;
    int luaChon = -1;

    do {
        InMenuChinh();

        // Bẫy lỗi nhập liệu
        if (!(std::cin >> luaChon)) {
            std::cout << "-> Loi: Vui long chi nhap so nguyen tu 0 den 7!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (luaChon) {
            case 1:
                ql.NhapDanhSach();
                break;

            case 2:
                ql.XuatDanhSach();
                break;

            case 3:
                ql.TimKiemMenu();
                break;

            case 4: {
                std::string maNV;
                std::cout << "\n================ XOA NHAN VIEN ================\n";
                std::cout << "Nhap Ma NV can xoa: ";
                std::cin >> maNV;
                if (ql.XoaNhanVienTheoMa(maNV)) {
                    std::cout << "-> Xoa nhan vien co ma '" << maNV << "' THANH CONG!\n";
                } else {
                    std::cout << "-> Loi: Khong tim thay nhan vien co ma '" << maNV << "' trong he thong!\n";
                }
                break;
            }

            case 5:
                ql.SapXepMenu();
                break;

            case 6:
                ql.ThongKeQuyLuong();
                break;

            case 7:
                ql.NapDuLieuMau();
                break;

            case 0:
                ql.GiaiPhongBoNho();
                std::cout << "\nCam on ban da su dung phan mem Quan Ly Nhan Su. Tam biet!\n";
                break;

            default:
                std::cout << "-> Lua chon khong hop le! Vui long chon so tu 0 den 7.\n";
                break;
        }

    } while (luaChon != 0);

    return 0;
}

#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
#include "QuanLyNhanSu.h"

// Hàm làm sạch màn hình Console (Windows / Linux / macOS)
void XoaManHinh() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Hàm tạm dừng chờ người dùng nhấn ENTER để trở về Menu chính
void DungManHinh() {
    std::cout << "\n----------------------------------------------------------------------------------\n";
    std::cout << "[i] Nhan phim ENTER de quay lai Menu chinh...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    XoaManHinh();
}

// Giao diện Menu chính 5 chức năng tinh gọn
void InMenuChinh() {
    std::cout << "=========================================================\n";
    std::cout << "          HE THONG QUAN LY NHAN SU - HE C++             \n";
    std::cout << "=========================================================\n";
    std::cout << "1. Nhap/Them moi thong tin nhan vien\n";
    std::cout << "2. Xoa thong tin dua tren ma nhan vien\n";
    std::cout << "3. Tim kiem thong tin nhan vien\n";
    std::cout << "4. Hien thi danh sach nhan vien (Tich hop Thong ke quy luong)\n";
    std::cout << "5. Nap/Doc lai du lieu tu file txt\n";
    std::cout << "0. Thoat chuong trinh\n";
    std::cout << "=========================================================\n";
    std::cout << "Moi ban chon chuc nang (0-5): ";
}

int main() {
    QuanLyNhanSu ql;

    // Tự động đọc dữ liệu mẫu từ file .txt ngay khi khởi động chương trình
    ql.DocTuFile("danhsach_nhanvien.txt");

    int luaChon = -1;
    XoaManHinh();

    do {
        InMenuChinh();

        // Bẫy lỗi khi người dùng nhập ký tự không phải số
        if (!(std::cin >> luaChon)) {
            std::cout << "\n-> Loi: Vui long chi nhap so nguyen tu 0 den 5!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            DungManHinh();
            continue;
        }

        switch (luaChon) {
            case 1:
                XoaManHinh();
                ql.NhapDanhSach();
                DungManHinh();
                break;

            case 2: {
                XoaManHinh();
                std::string maNV;
                std::cout << "======================== XOA NHAN VIEN ========================\n";
                std::cout << "Nhap Ma NV can xoa: ";
                std::cin >> maNV;
                if (ql.XoaNhanVienTheoMa(maNV)) {
                    std::cout << "-> Xoa nhan vien co ma '" << maNV << "' THANH CONG!\n";
                } else {
                    std::cout << "-> Loi: Khong tim thay nhan vien co ma '" << maNV << "' trong he thong!\n";
                }
                DungManHinh();
                break;
            }

            case 3:
                XoaManHinh();
                ql.TimKiemMenu();
                DungManHinh();
                break;

            case 4:
                XoaManHinh();
                // Hiển thị danh sách phân loại bộ phận + Thống kê tổng số lượng & quỹ lương ở cuối
                ql.XuatDanhSach(); 
                DungManHinh();
                break;

            case 5:
                XoaManHinh();
                std::cout << "==================== NAP DU LIEU TU FILE TXT ====================\n";
                ql.DocTuFile("danhsach_nhanvien.txt");
                std::cout << "-> Da nap lai du lieu tu file 'danhsach_nhanvien.txt' thanh cong!\n";
                DungManHinh();
                break;

            case 0:
                ql.GiaiPhongBoNho(); // Giải phóng mảng con trỏ Heap
                XoaManHinh();
                std::cout << "======================================================================\n";
                std::cout << "   Da xoa moi thong tin va giải phong bo nho. Tam biet!              \n";
                std::cout << "======================================================================\n";
                break;

            default:
                std::cout << "\n-> Lua chon khong hop le! Vui long chon so tu 0 den 5.\n";
                DungManHinh();
                break;
        }

    } while (luaChon != 0);

    return 0;
}

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>

#include "QuanLyNhanSu.h"

// 1. Hàm hỗ trợ xóa màn hình tương thích cả Windows và Linux/macOS
void XoaManHinh() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("cls");
#else
    std::system("clear");
#endif
}

// 2. Hàm tạm dừng màn hình chờ người dùng nhấn Enter
void DungManHinh() {
    std::cout << "\nNhan Enter de tiep tuc...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// 3. Hàm nạp sẵn dữ liệu giả lập (Demo nhanh cho thầy/cô chấm bài)
void KhoiTaoDuLieuMau(QuanLyNhanSu& ql) {
    ql.ThemNhanVien(new NhanVienVanPhong("NV01", "Nguyen Van A", "12/05/1995", "Ha Noi", 22, 350000));
    ql.ThemNhanVien(new NhanVienSanXuat("NV02", "Tran Thi B", "20/08/1998", "Nam Dinh", 150, 40000));
    ql.ThemNhanVien(new QuanLy("NV03", "Le Van C", "05/01/1990", "Da Nang", 12000000, 5000000));
    ql.ThemNhanVien(new NhanVienVanPhong("NV04", "Pham Thi D", "15/11/1997", "Hai Phong", 20, 300000));
    ql.ThemNhanVien(new NhanVienSanXuat("NV05", "Hoang Van E", "02/03/1996", "Can Tho", 200, 45000));
}

// 4. Màn hình giao diện Menu
void HienThiMenu() {
    std::cout << "=========================================================\n";
    std::cout << "     HE THONG QUAN LY NHAN SU (OBJECT ORIENTED C++)      \n";
    std::cout << "=========================================================\n";
    std::cout << "  1. Nhap danh sach nhan vien moi                        \n";
    std::cout << "  2. Hien thi danh sach nhan vien (Dang bang)            \n";
    std::cout << "  3. Tim kiem nhan vien (Theo Ma hoac Ten)               \n";
    std::cout << "  4. Xoa nhan vien theo Ma NV                            \n";
    std::cout << "  5. Sap xep danh sach theo luong giam dan               \n";
    std::cout << "  6. Thong ke tong quy luong va so luong                 \n";
    std::cout << "  7. Nap du lieu mau (Tự động tạo 5 NV demo)             \n";
    std::cout << "  0. Thoat chuong trinh                                  \n";
    std::cout << "=========================================================\n";
    std::cout << "Nhap lua chon cua ban [0-7]: ";
}

// 5. Hàm main chính
int main() {
    QuanLyNhanSu ql;
    int luaChon = -1;

    do {
        XoaManHinh();
        HienThiMenu();

        // Kiểm tra xử lý lỗi khi người dùng nhập ký tự chữ thay vì nhập số
        if (!(std::cin >> luaChon)) {
            std::cout << "\n[Loi] Vui long nhap mot so nguyen hop le!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            DungManHinh();
            continue;
        }

        switch (luaChon) {
        case 1: {
            XoaManHinh();
            std::cout << "=== 1. NHAP DANH SACH NHAN VIEN MOI ===\n";
            ql.NhapDanhSach();
            DungManHinh();
            break;
        }
        case 2: {
            XoaManHinh();
            std::cout << "=== 2. DANH SACH NHAN VIEN ===\n";
            ql.XuatDanhSach();
            DungManHinh();
            break;
        }
        case 3: {
            XoaManHinh();
            std::cout << "=== 3. TIM KIEM NHAN VIEN ===\n";
            std::cout << "  1. Tim kiem chinh xac theo Ma NV\n";
            std::cout << "  2. Tim kiem theo Tu khoa Ten\n";
            std::cout << "Lua chon [1-2]: ";
            int subChon = 0;
            std::cin >> subChon;

            if (subChon == 1) {
                std::string ma;
                std::cout << "Nhap Ma NV can tim: ";
                std::cin >> ma;
                NhanVien* nv = ql.TimKiemTheoMa(ma);
                if (nv != nullptr) {
                    std::cout << "\n[Ket qua tim kiem]:\n";
                    nv->HienThiThongTin();
                    std::cout << std::endl;
                } else {
                    std::cout << "\nKhong tim thay nhan vien co Ma NV: " << ma << std::endl;
                }
            } else if (subChon == 2) {
                std::string ten;
                std::cout << "Nhap Ten/Tu khoa can tim: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, ten);
                auto dsKetQua = ql.TimKiemTheoTen(ten);
                if (!dsKetQua.empty()) {
                    std::cout << "\n[Tim thay " << dsKetQua.size() << " nhan vien phu hop]:\n";
                    for (auto nv : dsKetQua) {
                        nv->HienThiThongTin();
                        std::cout << std::endl;
                    }
                } else {
                    std::cout << "\nKhong tim thay nhan vien nao chua tu khoa: " << ten << std::endl;
                }
            } else {
                std::cout << "\nLua chon khong hop le!\n";
            }
            DungManHinh();
            break;
        }
        case 4: {
            XoaManHinh();
            std::cout << "=== 4. XOA NHAN VIEN THEO MA ===\n";
            std::string ma;
            std::cout << "Nhap Ma NV can xoa: ";
            std::cin >> ma;
            if (ql.XoaNhanVienTheoMa(ma)) {
                std::cout << "\n=> Da xoa thanh cong nhan vien co Ma NV: " << ma << std::endl;
            } else {
                std::cout << "\n=> Khong tim thay nhan vien co Ma NV: " << ma << " de xoa!" << std::endl;
            }
            DungManHinh();
            break;
        }
        case 5: {
            XoaManHinh();
            std::cout << "=== 5. SAP XEP DANH SACH THEO LUONG GIAM DAN ===\n";
            ql.SapXepLuongGiamDan();
            std::cout << "=> Da sap xep danh sach theo luong giam dan!\n";
            ql.XuatDanhSach();
            DungManHinh();
            break;
        }
        case 6: {
            XoaManHinh();
            std::cout << "=== 6. THONG KE TONG QUY LUONG ===\n";
            std::cout << "Tong so luong nhan vien: " << ql.getDanhSach().size() << std::endl;
            std::cout << "Tong quy luong cong ty  : " << std::fixed << std::setprecision(0) 
                      << ql.TinhTongLuong() << " VND" << std::endl;
            DungManHinh();
            break;
        }
        case 7: {
            XoaManHinh();
            std::cout << "=== 7. NAP DU LIEU MAU ===\n";
            KhoiTaoDuLieuMau(ql);
            std::cout << "=> Da nap thanh cong 5 nhan vien mau vao he thong!\n";
            ql.XuatDanhSach();
            DungManHinh();
            break;
        }
        case 0: {
            std::cout << "\nCam on ban da su dung chuong trinh Quan ly nhan su. Tam biet!\n";
            break;
        }
        default:
            std::cout << "\n[Loi] Lua chon khong hop le! Vui long chon tu 0 den 7.\n";
            DungManHinh();
            break;
        }

    } while (luaChon != 0);

    return 0;
}


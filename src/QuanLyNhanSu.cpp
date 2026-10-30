#include "QuanLyNhanSu.h"

#include "NhanVienSanXuat.h"
#include "NhanVienVanPhong.h"
#include "QuanLy.h"

#include <iomanip>
#include <iostream>

const std::string QuanLyNhanSu::TIEN_TO_MA = "NV";

QuanLyNhanSu::QuanLyNhanSu() {}

QuanLyNhanSu::~QuanLyNhanSu() {
    giaiPhongBoNho();
}

void QuanLyNhanSu::themNhanVien(NhanVien* nhanVien) {
    if (nhanVien == nullptr) {
        std::cout << "Khong the them nhan vien rong (nullptr).\n";
        return;
    }
    if (!kiemTraDinhDangMa(nhanVien->getMaNhanVien())) {
        std::cout << "Ma nhan vien \"" << nhanVien->getMaNhanVien() << "\" sai dinh dang (VD: "
                  << TIEN_TO_MA << "0001), khong the them.\n";
        delete nhanVien;
        return;
    }
    if (kiemTraTrungMa(nhanVien->getMaNhanVien())) {
        std::cout << "Ma nhan vien \"" << nhanVien->getMaNhanVien() << "\" da ton tai, khong the them.\n";
        delete nhanVien;
        return;
    }
    dsNhanVien_.push_back(nhanVien);
}

bool QuanLyNhanSu::kiemTraTrungMa(const std::string& maNhanVien) const {
    return timKiemTheoMa(maNhanVien) != nullptr;
}

void QuanLyNhanSu::nhapDanhSach() {
    int loai = 0;
    while (true) {
        std::cout << "\n================ CHON LOAI NHAN VIEN ================\n"
                  << LOAI_VAN_PHONG << ". Nhan vien Van phong\n"
                  << LOAI_SAN_XUAT << ". Nhan vien San xuat\n"
                  << LOAI_QUAN_LY << ". Quan ly (Cap cao)\n"
                  << LOAI_KET_THUC << ". Ket thuc nhap\n";
        if (!docSoNguyen("Chon loai (0-3): ", LOAI_KET_THUC, LOAI_QUAN_LY, loai)) {
            return;
        }
        if (loai == LOAI_KET_THUC) {
            return;
        }
        if (!nhapNhanVienMoi(loai)) {
            return;
        }
    }
}

bool QuanLyNhanSu::xoaNhanVien(const std::string& maNhanVien) {
    for (std::vector<NhanVien*>::iterator it = dsNhanVien_.begin(); it != dsNhanVien_.end(); ++it) {
        if ((*it)->getMaNhanVien() == maNhanVien) {
            delete *it;
            dsNhanVien_.erase(it);
            return true;
        }
    }
    return false;
}

NhanVien* QuanLyNhanSu::timKiemTheoMa(const std::string& maNhanVien) const {
    for (NhanVien* nhanVien : dsNhanVien_) {
        if (nhanVien->getMaNhanVien() == maNhanVien) {
            return nhanVien;
        }
    }
    return nullptr;
}

std::vector<NhanVien*> QuanLyNhanSu::timKiemTheoTen(const std::string& hoTen) const {
    std::vector<NhanVien*> ketQua;
    const std::string tuKhoa = chuyenThuong(hoTen);
    for (NhanVien* nhanVien : dsNhanVien_) {
        if (chuyenThuong(nhanVien->getHoTen()).find(tuKhoa) != std::string::npos) {
            ketQua.push_back(nhanVien);
        }
    }
    return ketQua;
}

void QuanLyNhanSu::timKiemMenu() {
    if (dsNhanVien_.empty()) {
        std::cout << "\n-> Danh sach rong, khong the tim kiem!\n";
        return;
    }

    int luaChon = -1;
    do {
        std::cout << "\n================ TIM KIEM NHAN VIEN ================\n"
                  << "1. Tim chinh xac theo Ma NV\n"
                  << "2. Tim theo tu khoa Ho ten\n"
                  << "0. Quay lai\n";
        if (!docSoNguyen("Chon (0-2): ", 0, 2, luaChon)) {
            return;
        }

        if (luaChon == 1) {
            std::string maNhanVien;
            if (!docChuoi("Nhap Ma NV can tim: ", maNhanVien)) {
                return;
            }
            NhanVien* nhanVien = timKiemTheoMa(maNhanVien);
            if (nhanVien == nullptr) {
                std::cout << "-> Khong tim thay nhan vien co ma: " << maNhanVien << "\n";
            } else {
                std::cout << "\n-> KET QUA TIM KIEM:\n";
                inDanhSachNhanVien(std::vector<NhanVien*>(1, nhanVien));
            }
        } else if (luaChon == 2) {
            std::string hoTen;
            if (!docChuoi("Nhap tu khoa Ho ten can tim: ", hoTen)) {
                return;
            }
            std::vector<NhanVien*> ketQua = timKiemTheoTen(hoTen);
            if (ketQua.empty()) {
                std::cout << "-> Khong tim thay nhan vien nao co ten chua tu khoa: '" << hoTen << "'\n";
            } else {
                std::cout << "\n-> TIM THAY " << ketQua.size() << " NHAN VIEN PHU HOP:\n";
                inDanhSachNhanVien(ketQua);
            }
        }
    } while (luaChon != 0);
}

void QuanLyNhanSu::hienThiDanhSach() const {
    if (dsNhanVien_.empty()) {
        std::cout << "\n-> Danh sach nhan vien hien dang rong!\n";
        return;
    }

    std::cout << "\n" << std::string(DO_RONG_BANG / 2 - 10, '=') << " DANH SACH NHAN VIEN "
              << std::string(DO_RONG_BANG / 2 - 10, '=') << "\n";
    inDanhSachNhanVien(dsNhanVien_);
    std::cout << std::string(DO_RONG_BANG, '=') << "\n";
    std::cout << "-> Tong so nhan vien: " << dsNhanVien_.size() << " nguoi.\n";
    std::cout << "-> Tong quy luong phai tra: " << dsNhanVien_.front()->dinhDangTien(thongKeQuyLuong()) << " VND\n";
}

double QuanLyNhanSu::thongKeQuyLuong() const {
    double tongLuong = 0.0;
    for (const NhanVien* nhanVien : dsNhanVien_) {
        tongLuong += nhanVien->tinhLuong();
    }
    return tongLuong;
}

void QuanLyNhanSu::giaiPhongBoNho() {
    for (NhanVien* nhanVien : dsNhanVien_) {
        delete nhanVien;
    }
    dsNhanVien_.clear();
}

void QuanLyNhanSu::napDuLieuMau() {
    giaiPhongBoNho(); 
    int soSanPham = 0;
    int donGiaSanPham = 0;
    int soNgayLamViec = 0;
    int donGiaNgay = 0;
    int soGioTangCa = 0;
    int luongCoBan = 0;
    int luongTrachNhiem = 0;
    double heSoChucVu = 0.0;

    soNgayLamViec = 22;
    donGiaNgay = 350000;
    soGioTangCa = 10;
    themNhanVien(new NhanVienVanPhong("NV0001", "Nguyen Van An", "15/03/1992", "Ha Noi", soNgayLamViec, donGiaNgay, soGioTangCa));

    soSanPham = 115;
    donGiaSanPham = 45000;
    themNhanVien(new NhanVienSanXuat("NV0002", "Tran Thi Binh", "20/08/1995", "Nam Dinh", soSanPham, donGiaSanPham));

    luongCoBan = 15000000;
    luongTrachNhiem = 3000000;
    heSoChucVu = 1.5;
    themNhanVien(new QuanLy("NV0003", "Le Hoang Cuong", "10/01/1988", "Da Nang", luongCoBan, luongTrachNhiem, heSoChucVu));

    soNgayLamViec = 17;
    donGiaNgay = 320000;
    soGioTangCa = 0;
    themNhanVien(new NhanVienVanPhong("NV0004", "Pham Minh Dung", "05/11/1998", "Hai Phong", soNgayLamViec, donGiaNgay, soGioTangCa));

    soSanPham = 75;
    donGiaSanPham = 48000;
    themNhanVien(new NhanVienSanXuat("NV0005", "Vo Thi Giang", "12/07/1996", "Can Tho", soSanPham, donGiaSanPham));

    std::cout << "\n-> Nap thanh cong " << dsNhanVien_.size() << " nhan vien mau (du 3 loai) vao he thong!\n";
}

bool QuanLyNhanSu::nhapNhanVienMoi(int loai) {
    while (true) {
        NhanVien* nhanVien = taoNhanVienTheoLoai(loai);

        std::cout << "\nDinh dang ma: " << TIEN_TO_MA << " + " << SO_CHU_SO_MA
                  << " chu so (VD: " << TIEN_TO_MA << "0001).\n";
        const std::string maGoiY = taoMaGoiY();
        if (!maGoiY.empty()) {
            std::cout << "Goi y ma tiep theo: " << maGoiY << "\n";
        }
        nhanVien->nhap(std::cin);

        if (std::cin.eof()) {
            delete nhanVien;
            return false;
        }
        if (std::cin.fail()) {
            std::cin.clear();
            boQuaDongThua();
            std::cout << "-> Du lieu nhap khong hop le, vui long nhap lai nhan vien nay.\n";
            delete nhanVien;
            continue;
        }

        std::string maNhanVien = nhanVien->getMaNhanVien();
        while (!kiemTraDinhDangMa(maNhanVien) || kiemTraTrungMa(maNhanVien)) {
            if (!kiemTraDinhDangMa(maNhanVien)) {
                std::cout << "-> Loi: Ma NV '" << maNhanVien << "' sai dinh dang (VD: " << TIEN_TO_MA << "0001)!\n";
            } else {
                std::cout << "-> Loi: Ma NV '" << maNhanVien << "' da ton tai! Vui long nhap lai.\n";
            }
            if (!docChuoi("Nhap lai Ma Nhan Vien: ", maNhanVien)) {
                delete nhanVien;
                return false;
            }
        }
        nhanVien->setMaNhanVien(maNhanVien);

        themNhanVien(nhanVien);
        std::cout << "-> Them nhan vien moi thanh cong!\n";
        return true;
    }
}

std::string QuanLyNhanSu::taoMaGoiY() const {
    for (int so = 1; so <= SO_MA_TOI_DA; ++so) {
        std::string chuSo = std::to_string(so);
        while (static_cast<int>(chuSo.size()) < SO_CHU_SO_MA) {
            chuSo.insert(0, 1, '0');
        }
        const std::string ma = TIEN_TO_MA + chuSo;
        if (!kiemTraTrungMa(ma)) {
            return ma;
        }
    }
    return "";
}

bool QuanLyNhanSu::kiemTraDinhDangMa(const std::string& maNhanVien) {
    const std::string::size_type doDaiTienTo = TIEN_TO_MA.size();
    if (maNhanVien.size() != doDaiTienTo + SO_CHU_SO_MA) {
        return false;
    }
    if (maNhanVien.compare(0, doDaiTienTo, TIEN_TO_MA) != 0) {
        return false;
    }
    for (std::string::size_type i = doDaiTienTo; i < maNhanVien.size(); ++i) {
        if (maNhanVien[i] < '0' || maNhanVien[i] > '9') {
            return false;
        }
    }
    return true;
}

void QuanLyNhanSu::boQuaDongThua() {
    std::string boDem;
    std::getline(std::cin, boDem);
}

bool QuanLyNhanSu::docSoNguyen(const std::string& thongBao, int tuGiaTri, int denGiaTri, int& ketQua) {
    while (true) {
        std::cout << thongBao;
        int giaTri = 0;
        if (std::cin >> giaTri) {
            boQuaDongThua();
            if (giaTri >= tuGiaTri && giaTri <= denGiaTri) {
                ketQua = giaTri;
                return true;
            }
            std::cout << "-> Gia tri phai nam trong khoang [" << tuGiaTri << ", " << denGiaTri << "].\n";
        } else {
            if (std::cin.eof()) {
                return false;
            }
            std::cin.clear();
            boQuaDongThua();
            std::cout << "-> Du lieu khong hop le, vui long nhap so nguyen.\n";
        }
    }
}

bool QuanLyNhanSu::docChuoi(const std::string& thongBao, std::string& ketQua) {
    while (true) {
        std::cout << thongBao;
        std::string chuoi;
        if (!std::getline(std::cin >> std::ws, chuoi)) {
            return false;
        }
        if (!chuoi.empty()) {
            ketQua = chuoi;
            return true;
        }
        std::cout << "-> Khong duoc de trong, vui long nhap lai.\n";
    }
}

std::string QuanLyNhanSu::chuyenThuong(const std::string& chuoi) {
    std::string ketQua = chuoi;
    for (char& kyTu : ketQua) {
        if (kyTu >= 'A' && kyTu <= 'Z') {
            kyTu = static_cast<char>(kyTu + ('a' - 'A'));
        }
    }
    return ketQua;
}

NhanVien* QuanLyNhanSu::taoNhanVienTheoLoai(int loai) {
    switch (loai) {
        case LOAI_VAN_PHONG:
            return new NhanVienVanPhong();
        case LOAI_SAN_XUAT:
            return new NhanVienSanXuat();
        default:
            return new QuanLy();
    }
}

void QuanLyNhanSu::inTieuDeBang() {
    std::cout << std::left
              << std::setw(DO_RONG_MA) << "Ma NV"
              << std::setw(DO_RONG_HO_TEN) << "Ho va Ten"
              << std::setw(DO_RONG_NGAY_SINH) << "Ngay Sinh"
              << std::setw(DO_RONG_DIA_CHI) << "Dia Chi"
              << std::setw(DO_RONG_LOAI) << "Chuc Vu / Loai"
              << std::setw(DO_RONG_CHI_TIET) << "So Luong / Cong"
              << std::setw(DO_RONG_CHI_TIET) << "Ghi Chu / KPI"
              << std::setw(DO_RONG_CHI_TIET) << "Thuc Nhan (VND)" << '\n'
              << std::string(DO_RONG_BANG, '-') << '\n';
}

void QuanLyNhanSu::inDanhSachNhanVien(const std::vector<NhanVien*>& danhSach) {
    inTieuDeBang();
    for (const NhanVien* nhanVien : danhSach) {
        nhanVien->hienThiThongTin();
    }
}

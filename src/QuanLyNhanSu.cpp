#include "QuanLyNhanSu.h"

#include "NhanVienSanXuat.h"
#include "NhanVienVanPhong.h"
#include "QuanLy.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace MauSacNhanSu {
    const std::string RESET = "\033[0m";
    const std::string XANH_CYAN = "\033[36m";
    const std::string XANH_LA = "\033[32m";
    const std::string XANH_LA_SANG = "\033[38;5;120m";
    const std::string XANH_DUONG = "\033[34m";
    const std::string XANH_NGOC = "\033[38;5;44m";
    const std::string DO = "\033[31m";
    const std::string CAM = "\033[38;5;208m";
    const std::string VANG = "\033[33m";
    const std::string VANG_SANG = "\033[38;5;228m";
    const std::string TIM = "\033[35m";
    const std::string TIM_NHAT = "\033[38;5;141m";
    const std::string HONG = "\033[38;5;206m";
    const std::string TRANG = "\033[37m";
    const std::string DAM = "\033[1m";
}

namespace {
    const int CHIEU_RONG_CHUAN = 142;

    const int DO_RONG_MAN_HINH = CHIEU_RONG_CHUAN;
    const int DO_RONG_KET_QUA = CHIEU_RONG_CHUAN;
    const int DO_RONG_THONG_KE = CHIEU_RONG_CHUAN;
    const int DO_RONG_BANG = CHIEU_RONG_CHUAN;
    const int DO_RONG_THOAT = CHIEU_RONG_CHUAN;

    const int SO_COT = 8;
    const int DO_RONG_COT[SO_COT] = { 14, 20, 12, 16, 14, 14, 20, 15 };

    const int LOAI_VAN_PHONG = 1;
    const int LOAI_SAN_XUAT = 2;
    const int LOAI_QUAN_LY = 3;
    const int TIM_THEO_MA = 1;
    const int TIM_THEO_TEN = 2;
    const int DINH_MUC_SAN_PHAM = 100;

    // Cấu hình quy chuẩn mã nhân viên 8 ký tự
    const std::string TIEN_TO_VP = "NVVP";
    const std::string TIEN_TO_SX = "NVSX";
    const std::string TIEN_TO_QL = "NVQL";
    const int DO_DAI_MA = 8;
}

// ==========================================
// KHỞI TẠO (TỰ NẠP FILE) & HỦY
// ==========================================

QuanLyNhanSu::QuanLyNhanSu() {
    std::ifstream kiemTra("Data/NhanVien.txt");
    if (kiemTra.is_open()) {
        kiemTra.close();
        napDuLieuTuFile("Data/NhanVien.txt");
    }
    else {
        napDuLieuTuFile("NhanVien.txt");
    }
}

QuanLyNhanSu::~QuanLyNhanSu() {
    giaiPhongBoNho();
}

void QuanLyNhanSu::giaiPhongBoNho() {
    for (NhanVien* nhanVien : dsNhanVien_) {
        delete nhanVien;
    }
    dsNhanVien_.clear();
}

// ==========================================
// 1. CHỨC NĂNG THÊM MỚI
// ==========================================


void QuanLyNhanSu::nhapDanhSach() {
    inTieuDeManHinh("THEM NHAN VIEN MOI");

        // Khối 3 dòng lựa chọn vẫn giữ căn giữa
    const int LE_CON = (DO_RONG_MAN_HINH - 34) / 2; // (142 - 34) / 2 = 54
    const std::string pad(LE_CON, ' ');

    std::cout << MauSacNhanSu::XANH_LA
        << pad << "[" << LOAI_VAN_PHONG << "] Nhan vien Van phong (" << TIEN_TO_VP << "xxxx)\n"
        << MauSacNhanSu::VANG
        << pad << "[" << LOAI_SAN_XUAT << "] Nhan vien San xuat (" << TIEN_TO_SX << "xxxx)\n"
        << MauSacNhanSu::TIM
        << pad << "[" << LOAI_QUAN_LY << "] Quan ly (" << TIEN_TO_QL << "xxxx)\n"
        << MauSacNhanSu::RESET; 

    std::cout << MauSacNhanSu::XANH_CYAN << MauSacNhanSu::DAM;
    inDongKe('-', DO_RONG_MAN_HINH);
    std::cout << MauSacNhanSu::RESET;

    const std::string cauNhacLoai = ">> Chon loai nhan vien (1-3): ";
    // Tính khoảng đệm dựa trên độ dài chuỗi chữ thuần (không chứa mã màu)
    const int leNhapLoai = (DO_RONG_MAN_HINH - static_cast<int>(cauNhacLoai.length())) / 2 - 1;

    // Ghép khoảng đệm + Mã màu Vàng + In Đậm + Nội dung câu nhắc + Mã RESET
    const std::string chuoiHienThi = std::string(leNhapLoai, ' ')
        + MauSacNhanSu::VANG
        + MauSacNhanSu::DAM
        + cauNhacLoai
        + MauSacNhanSu::RESET;

    int loai = 0;
    if (!docSoNguyen(chuoiHienThi, LOAI_VAN_PHONG, LOAI_QUAN_LY, loai)) {
        return;
    }

    std::cout << "\n\n";

    nhapNhanVienMoi(*this, loai);
}

void QuanLyNhanSu::themNhanVien(NhanVien* nhanVien) {
    if (nhanVien == nullptr) {
        std::cout << "Khong the them nhan vien rong (nullptr).\n";
        return;
    }
    if (!kiemTraDinhDangMa(nhanVien->getMaNhanVien())) {
        std::cout << "Ma nhan vien \"" << nhanVien->getMaNhanVien()
            << "\" sai dinh dang (VD: NVVP0001, NVSX0001, NVQL0001), khong the them.\n";
        delete nhanVien;
        return;
    }
    if (kiemTraTrungMa(nhanVien->getMaNhanVien())) {
        std::cout << "Ma nhan vien \"" << nhanVien->getMaNhanVien() << "\" da ton tai, khong the them.\n";
        delete nhanVien;
        return;
    }
    dsNhanVien_.push_back(nhanVien);
    sapXepDanhSach();
}

bool QuanLyNhanSu::kiemTraTrungMa(const std::string& maNhanVien) const {
    return timKiemTheoMa(maNhanVien) != nullptr;
}

// ==========================================
// 2. CHỨC NĂNG XÓA
// ==========================================

void QuanLyNhanSu::giaoDienKetQuaXoa(QuanLyNhanSu& quanLy, std::string& maNhanVien) {
    inTieuDeManHinh("XOA NHAN VIEN THEO MA");

    const int CHIEU_RONG_KHUNG = 66;
    const int LE_CAN_GIUA = (DO_RONG_MAN_HINH - CHIEU_RONG_KHUNG) / 2; // 38 khoang trang
    const int KHOANG_TRONG = CHIEU_RONG_KHUNG - 4;                     // 62 ky tu long khung
    const std::string pad(LE_CAN_GIUA, ' ');

    auto inThongBaoCanGiua = [](const std::string& mau, const std::string& text) {
        int le = (DO_RONG_MAN_HINH - static_cast<int>(text.length())) / 2;
        if (le < 0) le = 0;
        std::cout << std::string(le, ' ') << mau << text << MauSacNhanSu::RESET << "\n";
        };

    if (quanLy.dsNhanVien_.empty()) {
        std::cout << "\n";
        inThongBaoCanGiua(MauSacNhanSu::DO + MauSacNhanSu::DAM, "DANH SACH NHAN VIEN DANG RONG, KHONG THE XOA!");
        std::cout << "\n";
        return;
    }

    // 1. In khung hop mau DO (Tone mau canh bao dac trung cua chuc nang Xoa)
    std::cout << "\n" << pad << MauSacNhanSu::DO
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacNhanSu::RESET;

    std::string tieuDe = "XAC NHAN XOA NHAN VIEN";
    int leTieuDeTrai = (KHOANG_TRONG - (int)tieuDe.length()) / 2;
    int leTieuDePhai = KHOANG_TRONG - (int)tieuDe.length() - leTieuDeTrai;

    std::cout << pad
        << MauSacNhanSu::DO << "||" << MauSacNhanSu::RESET
        << std::string(leTieuDeTrai, ' ')
        << MauSacNhanSu::DO << MauSacNhanSu::DAM << tieuDe << MauSacNhanSu::RESET
        << std::string(leTieuDePhai, ' ')
        << MauSacNhanSu::DO << "||" << MauSacNhanSu::RESET << "\n";

    std::cout << pad
        << MauSacNhanSu::DO
        << "||" << std::string(KHOANG_TRONG, '-') << "||\n"
        << MauSacNhanSu::RESET;

    // Nhan nhap ma mau Cam noi bat, vien hop giu mau Do dong bo
    std::cout << pad
        << MauSacNhanSu::DO << "||  " << MauSacNhanSu::RESET
        << MauSacNhanSu::CAM << std::left << std::setw(26) << "Nhap Ma can xoa"
        << ": " << MauSacNhanSu::RESET;

    if (!std::getline(std::cin >> std::ws, maNhanVien)) {
        return;
    }

    int doDaiMa = (int)maNhanVien.length();
    int khoangDemPhai = KHOANG_TRONG - 2 - 26 - 2 - doDaiMa;
    if (khoangDemPhai < 1) khoangDemPhai = 1;

    std::cout << "\033[1A\r" << pad
        << MauSacNhanSu::DO << "||  " << MauSacNhanSu::RESET
        << MauSacNhanSu::CAM << std::left << std::setw(26) << "Nhap Ma can xoa"
        << ": " << MauSacNhanSu::RESET
        << MauSacNhanSu::TRANG << maNhanVien << MauSacNhanSu::RESET
        << std::string(khoangDemPhai, ' ')
        << MauSacNhanSu::DO << "||\n" << MauSacNhanSu::RESET;

    // Dong day hop
    std::cout << pad
        << MauSacNhanSu::DO
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacNhanSu::RESET;

    // 2. Kiem tra ton tai
    NhanVien* nv = quanLy.timKiemTheoMa(maNhanVien);
    if (nv == nullptr) {
        std::cout << "\n";
        inThongBaoCanGiua(MauSacNhanSu::DO + MauSacNhanSu::DAM, "KHONG TIM THAY NHAN VIEN CO MA '" + maNhanVien + "' DE XOA!");
        std::cout << "\n";
        return;
    }

    // 3. Cau hoi xac nhan: Mau Vang in dam, lua chon (Y/N) to mau Xanh Cyan de de phan biet
    std::string cauHoi = ">> Ban co chac chan muon xoa nhan vien '" + nv->getHoTen() + "' (" + maNhanVien + ") khong?";
    std::string tuyChon = " (Y/N): ";
    int tongDoDai = static_cast<int>(cauHoi.length() + tuyChon.length());
    int leHoi = (DO_RONG_MAN_HINH - tongDoDai) / 2;
    if (leHoi < 0) leHoi = 0;

    std::cout << "\n" << std::string(leHoi, ' ')
        << MauSacNhanSu::VANG << MauSacNhanSu::DAM << cauHoi
        << MauSacNhanSu::XANH_CYAN << MauSacNhanSu::DAM << tuyChon
        << MauSacNhanSu::RESET;

    char xacNhan;
    std::cin >> xacNhan;
    boQuaDongThua();

    if (xacNhan == 'y' || xacNhan == 'Y') {
        quanLy.xoaNhanVien(maNhanVien);
        std::cout << "\n";
        inThongBaoCanGiua(MauSacNhanSu::XANH_DUONG + MauSacNhanSu::DAM, "DA XOA THANH CONG NHAN VIEN CO MA '" + maNhanVien + "'!");
    }
    else {
        std::cout << "\n";
        inThongBaoCanGiua(MauSacNhanSu::DO, "DA HUY THAO TAC XOA NHAN VIEN!");
    }
    std::cout << "\n";
}
bool QuanLyNhanSu::xoaNhanVien(const std::string& maNhanVien) {
    for (std::vector<NhanVien*>::iterator it = dsNhanVien_.begin(); it != dsNhanVien_.end(); ++it) {
        if ((*it)->getMaNhanVien() == maNhanVien) {
            delete* it;
            dsNhanVien_.erase(it);
            return true;
        }
    }
    return false;
}

// ==========================================
// 3. CHỨC NĂNG TÌM KIẾM
// ==========================================

void QuanLyNhanSu::timKiemMenu() {
    auto inThongBaoCanGiua = [](const std::string& mau, const std::string& text) {
        int le = (DO_RONG_MAN_HINH - static_cast<int>(text.length())) / 2;
        if (le < 0) le = 0;
        std::cout << std::string(le, ' ') << mau << text << MauSacNhanSu::RESET << "\n";
        };

    if (dsNhanVien_.empty()) {
        std::cout << "\n";
        inThongBaoCanGiua(MauSacNhanSu::DO + MauSacNhanSu::DAM, "DANH SACH NHAN VIEN DANG RONG, KHONG THE TIM KIEM!");
        std::cout << "\n";
        return;
    }

    inTieuDeManHinh("TIM KIEM NHAN VIEN");

    const int LE_CON = (DO_RONG_MAN_HINH - 44) / 2;
    const std::string pad(LE_CON, ' ');

    std::cout << MauSacNhanSu::VANG
        << pad << "[" << TIM_THEO_MA << "] Tim kiem chinh xac theo Ma nhan vien\n"
        << pad << "[" << TIM_THEO_TEN << "] Tim kiem theo Tu khoa Ho va Ten\n"
        << MauSacNhanSu::RESET;

    std::cout << MauSacNhanSu::XANH_CYAN << MauSacNhanSu::DAM;
    inDongKe('-', DO_RONG_MAN_HINH);
    std::cout << MauSacNhanSu::RESET;

    const std::string cauNhacKieu = ">> Chon kieu tim kiem (1-2): ";
    const int leNhapKieu = (DO_RONG_MAN_HINH - static_cast<int>(cauNhacKieu.length())) / 2 - 1;

    const std::string chuoiHienThi = std::string(leNhapKieu, ' ')
        + MauSacNhanSu::VANG
        + MauSacNhanSu::DAM
        + cauNhacKieu
        + MauSacNhanSu::RESET;

    int luaChon = 0;
    if (!docSoNguyen(chuoiHienThi, TIM_THEO_MA, TIM_THEO_TEN, luaChon)) {
        return;
    }

    const int CHIEU_RONG_KHUNG = 66;
    const int LE_CAN_GIUA = (DO_RONG_MAN_HINH - CHIEU_RONG_KHUNG) / 2;
    const int KHOANG_TRONG = CHIEU_RONG_KHUNG - 4;
    const std::string padKhung(LE_CAN_GIUA, ' ');

    std::cout << "\n" << padKhung << MauSacNhanSu::CAM
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacNhanSu::RESET;

    std::string tieuDeKhung = (luaChon == TIM_THEO_MA) ? "NHAP MA NHAN VIEN CAN TIM" : "NHAP TU KHOA HO TEN CAN TIM";
    int leTieuDeTrai = (KHOANG_TRONG - (int)tieuDeKhung.length()) / 2;
    int leTieuDePhai = KHOANG_TRONG - (int)tieuDeKhung.length() - leTieuDeTrai;

    std::cout << padKhung
        << MauSacNhanSu::CAM << "||" << MauSacNhanSu::RESET
        << std::string(leTieuDeTrai, ' ')
        << MauSacNhanSu::CAM << MauSacNhanSu::DAM << tieuDeKhung << MauSacNhanSu::RESET
        << std::string(leTieuDePhai, ' ')
        << MauSacNhanSu::CAM << "||" << MauSacNhanSu::RESET << "\n";

    std::cout << padKhung
        << MauSacNhanSu::CAM
        << "||" << std::string(KHOANG_TRONG, '-') << "||\n"
        << MauSacNhanSu::RESET;

    std::string nhanNhap = (luaChon == TIM_THEO_MA) ? "Ma nhan vien" : "Tu khoa ten";
    std::cout << padKhung
        << MauSacNhanSu::CAM << "||  " << MauSacNhanSu::RESET
        << MauSacNhanSu::VANG << std::left << std::setw(26) << nhanNhap
        << ": " << MauSacNhanSu::RESET;

    std::string tuKhoa;
    if (!std::getline(std::cin >> std::ws, tuKhoa)) {
        return;
    }

    int doDaiTuKhoa = static_cast<int>(tuKhoa.length());
    int khoangDemPhai = KHOANG_TRONG - 2 - 26 - 2 - doDaiTuKhoa;
    if (khoangDemPhai < 1) khoangDemPhai = 1;

    std::cout << "\033[1A\r" << padKhung
        << MauSacNhanSu::CAM << "||  " << MauSacNhanSu::RESET
        << MauSacNhanSu::VANG << std::left << std::setw(26) << nhanNhap
        << ": " << MauSacNhanSu::RESET
        << MauSacNhanSu::TRANG << tuKhoa << MauSacNhanSu::RESET
        << std::string(khoangDemPhai, ' ')
        << MauSacNhanSu::CAM << "||\n" << MauSacNhanSu::RESET;

    std::cout << padKhung
        << MauSacNhanSu::CAM
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacNhanSu::RESET;

    // Tìm kiếm nhân viên
    NhanVien* nv = nullptr;
    if (luaChon == TIM_THEO_MA) {
        nv = timKiemTheoMa(tuKhoa);
    }
    else {
        std::vector<NhanVien*> ds = timKiemTheoTen(tuKhoa);
        if (!ds.empty()) {
            nv = ds[0]; // Lấy nhân viên tìm thấy đầu tiên
        }
    }

    // Nếu không tìm thấy
    if (nv == nullptr) {
        std::cout << "\n";
        inThongBaoCanGiua(MauSacNhanSu::DO + MauSacNhanSu::DAM, "KHONG TIM THAY NHAN VIEN PHU HOP!");
        std::cout << "\n";
        return;
    }

    // 1. Nhận diện chức vụ và các trường thông số đặc thù (mỗi trường 1 màu riêng)
    std::string tenBoPhan = "";
    std::string thongBaoLoai = "";

    // Cấu trúc lưu: {Màu nhãn, Tên nhãn, Giá trị}
    struct ThuocTinhRieng {
        std::string mau;
        std::string nhan;
        std::string giaTri;
    };
    std::vector<ThuocTinhRieng> danhSachThuocTinh;

    if (const NhanVienVanPhong* vp = dynamic_cast<const NhanVienVanPhong*>(nv)) {
        tenBoPhan = "Nhan vien Van phong";
        thongBaoLoai = "KET QUA: NHAN VIEN VAN PHONG (" + nv->getMaNhanVien() + ")";
        danhSachThuocTinh.push_back({ MauSacNhanSu::HONG, "So ngay lam viec", std::to_string(vp->getSoNgayLamViec()) + " ngay" });
        danhSachThuocTinh.push_back({ MauSacNhanSu::TIM, "So gio tang ca (OT)", std::to_string(vp->getSoGioTangCa()) + " gio" });
        danhSachThuocTinh.push_back({ MauSacNhanSu::XANH_CYAN, "He so KPI", dinhDangThapPhan(vp->tinhHeSoKPI(), 2) });
    }
    else if (const NhanVienSanXuat* sx = dynamic_cast<const NhanVienSanXuat*>(nv)) {
        tenBoPhan = "Nhan vien San xuat";
        thongBaoLoai = "KET QUA: NHAN VIEN SAN XUAT (" + nv->getMaNhanVien() + ")";
        danhSachThuocTinh.push_back({ MauSacNhanSu::HONG, "So san pham lam duoc", std::to_string(sx->getSoSanPham()) + " SP" });
        danhSachThuocTinh.push_back({ MauSacNhanSu::TIM, "Dinh muc quy dinh", std::to_string(DINH_MUC_SAN_PHAM) + " SP" });
        danhSachThuocTinh.push_back({ MauSacNhanSu::XANH_CYAN, "He so KPI", dinhDangThapPhan(sx->tinhHeSoKPI(), 2) });
    }
    else if (const QuanLy* ql = dynamic_cast<const QuanLy*>(nv)) {
        tenBoPhan = "Quan ly";
        thongBaoLoai = "KET QUA: QUAN LY (" + nv->getMaNhanVien() + ")";
        danhSachThuocTinh.push_back({ MauSacNhanSu::HONG, "Luong co ban", dinhDangSoTien(ql->getLuongCoBan()) + " VND" });
        danhSachThuocTinh.push_back({ MauSacNhanSu::VANG_SANG, "He so chuc vu", dinhDangThapPhan(ql->getHeSoChucVu(), 2) });
        danhSachThuocTinh.push_back({ MauSacNhanSu::TIM, "Luong trach nhiem", dinhDangSoTien(ql->getLuongTrachNhiem()) + " VND" });
    }

    // 2. In tiêu đề thông báo kết quả căn giữa màn hình
    std::cout << "\n";
    inThongBaoCanGiua(MauSacNhanSu::XANH_LA + MauSacNhanSu::DAM, thongBaoLoai);
    std::cout << "\n";

    // 3. Lambda in từng dòng thẻ hồ sơ
    const std::string MAU_VIEN = MauSacNhanSu::XANH_CYAN;

    auto inDongHoSo = [&](const std::string& mauNhan, const std::string& nhan, const std::string& mauGiaTri, const std::string& giaTri) {
        int doDaiDuLieu = static_cast<int>(giaTri.length());
        int khoangDemPhai = KHOANG_TRONG - 2 - 26 - 2 - doDaiDuLieu;
        if (khoangDemPhai < 1) khoangDemPhai = 1;

        std::cout << padKhung
            << MAU_VIEN << "||  " << MauSacNhanSu::RESET
            << mauNhan << std::left << std::setw(26) << nhan
            << ": " << MauSacNhanSu::RESET
            << mauGiaTri << giaTri << MauSacNhanSu::RESET
            << std::string(khoangDemPhai, ' ')
            << MAU_VIEN << "||\n" << MauSacNhanSu::RESET;
        };

    // Vẽ nắp thẻ hồ sơ
    std::cout << padKhung << MAU_VIEN
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacNhanSu::RESET;

    std::string tieuDeThe = "HO SO NHAN VIEN";
    int leTheTrai = (KHOANG_TRONG - (int)tieuDeThe.length()) / 2;
    int leThePhai = KHOANG_TRONG - (int)tieuDeThe.length() - leTheTrai;

    // Dòng "HO SO NHAN VIEN" màu Xanh Dương in đậm
    std::cout << padKhung
        << MAU_VIEN << "||" << MauSacNhanSu::RESET
        << std::string(leTheTrai, ' ')
        << MauSacNhanSu::XANH_DUONG << MauSacNhanSu::DAM << tieuDeThe << MauSacNhanSu::RESET
        << std::string(leThePhai, ' ')
        << MAU_VIEN << "||" << MauSacNhanSu::RESET << "\n";

    std::cout << padKhung << MAU_VIEN
        << "||" << std::string(KHOANG_TRONG, '-') << "||\n"
        << MauSacNhanSu::RESET;

    // Khu 1: Thông tin cơ bản - Mỗi thuộc tính một màu riêng
    inDongHoSo(MauSacNhanSu::VANG, "Ma nhan vien", MauSacNhanSu::TRANG, nv->getMaNhanVien());
    inDongHoSo(MauSacNhanSu::XANH_LA_SANG, "Ho va ten", MauSacNhanSu::TRANG, nv->getHoTen());
    inDongHoSo(MauSacNhanSu::TIM_NHAT, "Ngay sinh", MauSacNhanSu::TRANG, nv->getNgaySinh());
    inDongHoSo(MauSacNhanSu::XANH_NGOC, "Dia chi", MauSacNhanSu::TRANG, nv->getDiaChi());

    // Đường vạch phân cách
    std::cout << padKhung << MAU_VIEN
        << "||" << std::string(KHOANG_TRONG, '-') << "||\n"
        << MauSacNhanSu::RESET;

    // Khu 2: Vị trí & Thông số công việc
    inDongHoSo(MauSacNhanSu::CAM, "Chuc vu / Bo phan", MauSacNhanSu::CAM + MauSacNhanSu::DAM, tenBoPhan);
    for (const auto& item : danhSachThuocTinh) {
        inDongHoSo(item.mau, item.nhan, MauSacNhanSu::TRANG, item.giaTri);
    }

    // Đường vạch phân cách trước mục lương
    std::cout << padKhung << MAU_VIEN
        << "||" << std::string(KHOANG_TRONG, '-') << "||\n"
        << MauSacNhanSu::RESET;

    // Khu 3: Thực nhận (Giữ nguyên màu xanh lá)
    inDongHoSo(MauSacNhanSu::XANH_LA + MauSacNhanSu::DAM, "THUC NHAN (LUONG)",
        MauSacNhanSu::XANH_LA + MauSacNhanSu::DAM, dinhDangSoTien(nv->tinhLuong()) + " VND");

    // Đáy thẻ hồ sơ
    std::cout << padKhung << MAU_VIEN
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacNhanSu::RESET << "\n";
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

// ==========================================
// 4. HIỂN THỊ (TÍCH HỢP SẮP XẾP & THỐNG KÊ)
// ==========================================

void QuanLyNhanSu::inDauNhom(const std::string& tieuDe, const std::string& cot5, const std::string& cot6, const std::string& cot7) {
    const int KHOANG_TRONG = DO_RONG_BANG - 4;

    std::cout << "\n" << MauSacNhanSu::TIM << MauSacNhanSu::DAM
        << tieuDe << "\n" << MauSacNhanSu::RESET;

        std::cout << MauSacNhanSu::XANH_CYAN
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacNhanSu::RESET;

        std::cout << MauSacNhanSu::VANG << MauSacNhanSu::DAM; 
        inHangBang({ "Ma nhan vien", "Ho va Ten", "Ngay sinh", "Dia chi", cot5, cot6, cot7, "Thuc nhan (VND)" });
        std::cout << MauSacNhanSu::RESET;

        std::cout << MauSacNhanSu::XANH_CYAN
        << "|-" << std::string(14, '-') << "|-" << std::string(20, '-')
        << "|-" << std::string(12, '-') << "|-" << std::string(16, '-')
        << "|-" << std::string(14, '-') << "|-" << std::string(14, '-')
        << "|-" << std::string(20, '-') << "|-" << std::string(15, '-') << "|\n"
        << MauSacNhanSu::RESET;
}

void QuanLyNhanSu::inCuoiNhom(const std::string& tenNhom, int soLuong, double tongLuong) {
    const int KHOANG_TRONG = DO_RONG_BANG - 4;

        std::cout << MauSacNhanSu::XANH_CYAN
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacNhanSu::RESET;

        std::string chuoiSubtotal = "=> So luong Nhan vien " + tenNhom + ": " + std::to_string(soLuong)
        + " nguoi | Tong luong: " + dinhDangSoTien(tongLuong) + " VND";
        int lePhai = DO_RONG_BANG - static_cast<int>(chuoiSubtotal.length());
        if (lePhai < 0) lePhai = 0;

            std::cout << std::string(lePhai, ' ')
            << MauSacNhanSu::XANH_LA << MauSacNhanSu::DAM
            << chuoiSubtotal << "\n"
            << MauSacNhanSu::RESET;
}

void QuanLyNhanSu::inNhomVanPhong(const std::vector<const NhanVienVanPhong*>& danhSach) {
    double tongLuong = 0.0;
        inDauNhom("I. NHAN VIEN VAN PHONG (" + std::to_string(danhSach.size()) + " nguoi)",
            "Ngay cong", "Gio tang ca", "He so KPI");
        for (const NhanVienVanPhong* nhanVien : danhSach) {
            inHangBang({ nhanVien->getMaNhanVien(), nhanVien->getHoTen(), nhanVien->getNgaySinh(), nhanVien->getDiaChi(),
                        std::to_string(nhanVien->getSoNgayLamViec()) + " ngay",
                        std::to_string(nhanVien->getSoGioTangCa()) + " gio",
                        dinhDangThapPhan(nhanVien->tinhHeSoKPI(), 2),
                        dinhDangSoTien(nhanVien->tinhLuong()) });
                tongLuong += nhanVien->tinhLuong();
        }
    inCuoiNhom("Van Phong", static_cast<int>(danhSach.size()), tongLuong);
}

void QuanLyNhanSu::inNhomSanXuat(const std::vector<const NhanVienSanXuat*>& danhSach) {
    double tongLuong = 0.0;
        inDauNhom("II. NHAN VIEN SAN XUAT (" + std::to_string(danhSach.size()) + " nguoi)",
            "So san pham", "Dinh muc", "He so KPI");
        for (const NhanVienSanXuat* nhanVien : danhSach) {
            inHangBang({ nhanVien->getMaNhanVien(), nhanVien->getHoTen(), nhanVien->getNgaySinh(), nhanVien->getDiaChi(),
                        std::to_string(nhanVien->getSoSanPham()) + " SP",
                        std::to_string(DINH_MUC_SAN_PHAM) + " SP",
                        dinhDangThapPhan(nhanVien->tinhHeSoKPI(), 2),
                        dinhDangSoTien(nhanVien->tinhLuong()) });
                tongLuong += nhanVien->tinhLuong();
        }
    inCuoiNhom("San Xuat", static_cast<int>(danhSach.size()), tongLuong);
}

void QuanLyNhanSu::inNhomQuanLy(const std::vector<const QuanLy*>& danhSach) {
    double tongLuong = 0.0;
        inDauNhom("III. QUAN LY (" + std::to_string(danhSach.size()) + " nguoi)",
            "Luong co ban", "He so chuc vu", "Luong trach nhiem");
        for (const QuanLy* nhanVien : danhSach) {
            inHangBang({ nhanVien->getMaNhanVien(), nhanVien->getHoTen(), nhanVien->getNgaySinh(), nhanVien->getDiaChi(),
                        dinhDangSoTien(nhanVien->getLuongCoBan()),
                        dinhDangThapPhan(nhanVien->getHeSoChucVu(), 2),
                        dinhDangSoTien(nhanVien->getLuongTrachNhiem()),
                        dinhDangSoTien(nhanVien->tinhLuong()) });
                tongLuong += nhanVien->tinhLuong();
        }
    inCuoiNhom("Quan Ly", static_cast<int>(danhSach.size()), tongLuong);
}

double QuanLyNhanSu::thongKeQuyLuong() const {
    int soVanPhong = 0;
    int soSanXuat = 0;
    int soQuanLy = 0;
    double tongLuong = 0.0;

    for (const NhanVien* nhanVien : dsNhanVien_) {
        tongLuong += nhanVien->tinhLuong();
        if (dynamic_cast<const NhanVienVanPhong*>(nhanVien) != nullptr) {
            ++soVanPhong;
        }
        else if (dynamic_cast<const NhanVienSanXuat*>(nhanVien) != nullptr) {
            ++soSanXuat;
        }
        else if (dynamic_cast<const QuanLy*>(nhanVien) != nullptr) {
            ++soQuanLy;
        }
    }

    const int CHIEU_RONG_KHUNG = 66;
    const int LE_CAN_GIUA = (DO_RONG_MAN_HINH - CHIEU_RONG_KHUNG) / 2; // 38 khoang trang
    const int KHOANG_TRONG = CHIEU_RONG_KHUNG - 4;                     // 62 ky tu ben trong ||
    const std::string pad(LE_CAN_GIUA, ' ');
    const std::string MAU_VIEN = MauSacNhanSu::XANH_CYAN;

    // 1. Gom toan bo danh sach muc can hien thi
    struct MucThongKe {
        std::string mauNhan;
        std::string nhan;
        std::string mauGiaTri;
        std::string giaTri;
    };

    std::vector<MucThongKe> dsMuc = {
        { MauSacNhanSu::XANH_NGOC, "Tong so nhan vien toan cong ty", MauSacNhanSu::TRANG + MauSacNhanSu::DAM, std::to_string(dsNhanVien_.size()) + " nguoi" },
        { MauSacNhanSu::XANH_LA,   "Nhan vien Van phong",            MauSacNhanSu::TRANG,                      std::to_string(soVanPhong) + " nguoi" },
        { MauSacNhanSu::VANG,      "Nhan vien San xuat",             MauSacNhanSu::TRANG,                      std::to_string(soSanXuat) + " nguoi" },
        { MauSacNhanSu::TIM,       "Quan ly",                        MauSacNhanSu::TRANG,                      std::to_string(soQuanLy) + " nguoi" }
    };

    // 2. Tu dong tim do dai cua nhan dai nhat (Dynamic Width)
    int doRongCotNhan = 0;
    for (const auto& item : dsMuc) {
        if (static_cast<int>(item.nhan.length()) > doRongCotNhan) {
            doRongCotNhan = static_cast<int>(item.nhan.length());
        }
    }

    // Nap hop
    std::cout << "\n" << pad << MAU_VIEN
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacNhanSu::RESET;

    std::string tieuDe = "THONG KE QUY LUONG VA NHAN SU";
    int leTrai = (KHOANG_TRONG - (int)tieuDe.length()) / 2;
    int lePhai = KHOANG_TRONG - (int)tieuDe.length() - leTrai;

    std::cout << pad
        << MAU_VIEN << "||" << MauSacNhanSu::RESET
        << std::string(leTrai, ' ')
        << MauSacNhanSu::XANH_DUONG << MauSacNhanSu::DAM << tieuDe << MauSacNhanSu::RESET
        << std::string(lePhai, ' ')
        << MAU_VIEN << "||" << MauSacNhanSu::RESET << "\n";

    std::cout << pad << MAU_VIEN
        << "||" << std::string(KHOANG_TRONG, '-') << "||\n"
        << MauSacNhanSu::RESET;

    // 3. In cac muc: Tu dong can le theo doRongCotNhan vua tim duoc
    for (const auto& item : dsMuc) {
        int doDaiDuLieu = static_cast<int>(item.giaTri.length());
        // Cong thuc dong vien phai tu dong: 62 - (2 + doRongCotNhan + 2) - doDaiDuLieu
        int khoangDemPhai = KHOANG_TRONG - 4 - doRongCotNhan - doDaiDuLieu;
        if (khoangDemPhai < 0) khoangDemPhai = 0;

        std::cout << pad
            << MAU_VIEN << "||  " << MauSacNhanSu::RESET
            << item.mauNhan << std::left << std::setw(doRongCotNhan) << item.nhan
            << ": " << MauSacNhanSu::RESET
            << item.mauGiaTri << item.giaTri << MauSacNhanSu::RESET
            << std::string(khoangDemPhai, ' ')
            << MAU_VIEN << "||\n" << MauSacNhanSu::RESET;
    }

    std::cout << pad << MAU_VIEN
        << "||" << std::string(KHOANG_TRONG, '-') << "||\n"
        << MauSacNhanSu::RESET;

    // Dong Tong quy luong cung can theo doRongCotNhan
    std::string nhanTong = "TONG QUY LUONG PHAI CHI";
    std::string valTong = dinhDangSoTien(tongLuong) + " VND";
    int khoangDemPhaiTong = KHOANG_TRONG - 4 - doRongCotNhan - static_cast<int>(valTong.length());
    if (khoangDemPhaiTong < 0) khoangDemPhaiTong = 0;

    std::cout << pad
        << MAU_VIEN << "||  " << MauSacNhanSu::RESET
        << MauSacNhanSu::XANH_LA << MauSacNhanSu::DAM << std::left << std::setw(doRongCotNhan) << nhanTong
        << ": " << MauSacNhanSu::RESET
        << MauSacNhanSu::XANH_LA << MauSacNhanSu::DAM << valTong << MauSacNhanSu::RESET
        << std::string(khoangDemPhaiTong, ' ')
        << MAU_VIEN << "||\n" << MauSacNhanSu::RESET;

    std::cout << pad << MAU_VIEN
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacNhanSu::RESET << "\n";

    return tongLuong;
}

void QuanLyNhanSu::hienThiDanhSach() {
    if (dsNhanVien_.empty()) {
        std::cout << "\n";
            std::string thongBao = "DANH SACH NHAN VIEN HIEN DANG RONG!";
            int le = (DO_RONG_MAN_HINH - static_cast<int>(thongBao.length())) / 2;
            if (le < 0) le = 0;
                std::cout << std::string(le, ' ') << MauSacNhanSu::DO << MauSacNhanSu::DAM
                << thongBao << MauSacNhanSu::RESET << "\n\n"; 
                return;
    }

    sapXepDanhSach();

        std::vector<const NhanVienVanPhong*> vanPhong;
        std::vector<const NhanVienSanXuat*> sanXuat; 
        std::vector<const QuanLy*> quanLy; 
        for (const NhanVien* nhanVien : dsNhanVien_) {
            if (const NhanVienVanPhong* vp = dynamic_cast<const NhanVienVanPhong*>(nhanVien)) {
                vanPhong.push_back(vp);
            }
            else if (const NhanVienSanXuat* sx = dynamic_cast<const NhanVienSanXuat*>(nhanVien)) {
                sanXuat.push_back(sx);
            }
            else if (const QuanLy* ql = dynamic_cast<const QuanLy*>(nhanVien)) {
                quanLy.push_back(ql);
            }
        }

    inTieuDeManHinh("DANH SACH NHAN VIEN PHAN THEO BO PHAN (DA SAP XEP THEO MA)");

        if (!vanPhong.empty()) {
            inNhomVanPhong(vanPhong);
        }
    if (!sanXuat.empty()) {
        inNhomSanXuat(sanXuat); 
    }
    if (!quanLy.empty()) {
        inNhomQuanLy(quanLy);
    }

    thongKeQuyLuong(); 
}

void QuanLyNhanSu::sapXepDanhSach() {
    std::sort(dsNhanVien_.begin(), dsNhanVien_.end(), soSanhTheoMa); 
}

// ==========================================
// 5. THOÁT CHƯƠNG TRÌNH
// ==========================================

void QuanLyNhanSu::thoatChuongTrinh() {
    giaiPhongBoNho(); // Giai phong toan bo bo nho cap phat dong

    // Don sach man hinh console
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    const int CHIEU_RONG_KHUNG = 66;
    const int LE_CAN_GIUA = (DO_RONG_MAN_HINH - CHIEU_RONG_KHUNG) / 2; // 38 khoang trang
    const int KHOANG_TRONG = CHIEU_RONG_KHUNG - 4;                     // Chinh xac 62 ky tu
    const std::string pad(LE_CAN_GIUA, ' ');
    const std::string MAU_VIEN = MauSacNhanSu::XANH_CYAN;

    auto inDongCanGiuaKhung = [&](const std::string& mauChu, const std::string& noiDung) {
        int doDai = static_cast<int>(noiDung.length());
        int leTrai = (KHOANG_TRONG - doDai) / 2;
        int lePhai = KHOANG_TRONG - doDai - leTrai;

        std::cout << pad
            << MAU_VIEN << "||" << MauSacNhanSu::RESET
            << std::string(leTrai, ' ')
            << mauChu << noiDung << MauSacNhanSu::RESET
            << std::string(lePhai, ' ')
            << MAU_VIEN << "||" << MauSacNhanSu::RESET << "\n";
        };

    std::cout << "\n\n";

    // 1. Nap hop (62 dau '=')
    std::cout << pad << MAU_VIEN
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacNhanSu::RESET;

    // 2. Tieu de thiep
    inDongCanGiuaKhung(MauSacNhanSu::XANH_DUONG + MauSacNhanSu::DAM, "TAM BIET & HEN GAP LAI");

    // 3. Duong phan cach tren (chinh xac 62 dau '-')
    std::cout << pad << MAU_VIEN
        << "||" << std::string(KHOANG_TRONG, '-') << "||\n"
        << MauSacNhanSu::RESET;

    // Khoang trong dem tren
    inDongCanGiuaKhung(MauSacNhanSu::RESET, "");

    // 4. Noi dung loi cam on
    inDongCanGiuaKhung(MauSacNhanSu::VANG + MauSacNhanSu::DAM, "Cam on ban da su dung HE THONG QUAN LY NHAN SU!");
    inDongCanGiuaKhung(MauSacNhanSu::CAM, "Chuc ban mot ngay hoc tap va lam viec that tot!");

    // Khoang trong dem duoi
    inDongCanGiuaKhung(MauSacNhanSu::RESET, "");

    // 5. Duong phan cach duoi (chinh xac 62 dau '-')
    std::cout << pad << MAU_VIEN
        << "||" << std::string(KHOANG_TRONG, '-') << "||\n"
        << MauSacNhanSu::RESET;

    // 6. Trang thai ky thuat (Do dai 48 ky tu -> leTrai = lePhai = 7 khoang trang)
    inDongCanGiuaKhung(MauSacNhanSu::XANH_LA, "Trang thai: Da giai phong tai nguyen & luu an toan.");

    // 7. Thong tin phien ban & nhom BDPT (Do dai 42 ky tu -> leTrai = lePhai = 10 khoang trang)
    inDongCanGiuaKhung(MauSacNhanSu::TRANG + MauSacNhanSu::DAM, "Phien ban: 1.0.0 | Phat trien boi Nhom BDPT");

    // 8. Day hop (62 dau '=')
    std::cout << pad << MAU_VIEN
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacNhanSu::RESET << "\n\n";

    std::exit(EXIT_SUCCESS);
}

// ==========================================
// HELPER: XỬ LÝ CHUỖI, ĐỊNH DẠNG & GIAO DIỆN
// ==========================================

void QuanLyNhanSu::inHangBang(const std::vector<std::string>& cacCot) {
    std::cout << std::left; 
        for (int i = 0; i < SO_COT; ++i) {
            std::cout << MauSacNhanSu::XANH_CYAN
                << "| "
                << MauSacNhanSu::RESET
                << std::setw(DO_RONG_COT[i]) << cacCot[i]; 
        }
    std::cout << MauSacNhanSu::XANH_CYAN
        << "|"
        << MauSacNhanSu::RESET << "\n";
}

int QuanLyNhanSu::layPhanSo(const std::string& maNhanVien) {
    if (maNhanVien.size() < DO_DAI_MA) {
        return 0;
    }
    int phanSo = 0;
        for (std::string::size_type i = 4; i < maNhanVien.size(); ++i) {
            if (maNhanVien[i] >= '0' && maNhanVien[i] <= '9') {
                phanSo = phanSo * 10 + (maNhanVien[i] - '0');
            }
        }
    return phanSo; 
}

bool QuanLyNhanSu::soSanhTheoMa(const NhanVien* nhanVienA, const NhanVien* nhanVienB) {
    std::string maA = nhanVienA->getMaNhanVien();
        std::string maB = nhanVienB->getMaNhanVien();

        std::string tienToA = (maA.size() >= 4) ? maA.substr(0, 4) : "";
        std::string tienToB = (maB.size() >= 4) ? maB.substr(0, 4) : "";

        auto layDoUuTien = [](const std::string& tienTo) {
        if (tienTo == TIEN_TO_VP) return 1;
            if (tienTo == TIEN_TO_SX) return 2;
                if (tienTo == TIEN_TO_QL) return 3;
                    return 4;
        };

    int uuTienA = layDoUuTien(tienToA);
        int uuTienB = layDoUuTien(tienToB);

        if (uuTienA != uuTienB) {
            return uuTienA < uuTienB;
        }

    return layPhanSo(maA) < layPhanSo(maB);
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
                std::cout << "Gia tri phai nam trong khoang [" << tuGiaTri << ", " << denGiaTri << "].\n"; 
            }
            else {
                if (std::cin.eof()) {
                    return false;
                }
                std::cin.clear();
                    boQuaDongThua();
                    std::cout << "Du lieu khong hop le, vui long nhap so nguyen.\n";
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
        std::cout << "Khong duoc de trong, vui long nhap lai.\n"; 
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

std::string QuanLyNhanSu::dinhDangThapPhan(double giaTri, int soChuSo) {
    std::ostringstream oss;
        oss << std::fixed << std::setprecision(soChuSo) << giaTri;
        return oss.str();
}

std::string QuanLyNhanSu::dinhDangSoTien(double soTien) {
    NhanVienVanPhong nhanVienTam;
        return nhanVienTam.dinhDangTien(soTien);
}

void QuanLyNhanSu::inDongKe(char kyTu, int doDai) {
    std::cout << std::string(doDai, kyTu) << "\n";
}

void QuanLyNhanSu::inTieuDeManHinh(const std::string& tieuDe) {
    int doDaiMoiBen = (DO_RONG_MAN_HINH - static_cast<int>(tieuDe.size()) - 2) / 2; 
        std::cout << MauSacNhanSu::XANH_CYAN
        << MauSacNhanSu::DAM
        << "\n"
        << std::string(doDaiMoiBen, '=')
        << " " << tieuDe << " "
        << std::string(doDaiMoiBen, '=')
        << MauSacNhanSu::RESET << "\n";
}

// ==========================================
// HELPER: NẠP DỮ LIỆU TỰ ĐỘNG TỪ FILE
// ==========================================

void QuanLyNhanSu::napDuLieuTuFile(const std::string& tenFile) {
    std::ifstream file(tenFile);
    if (!file.is_open()) {
        std::cout << "[THONG BAO]: Khong tim thay file '" << tenFile << "', he thong khoi dong voi danh sach rong.\n";
        return;
    }

    giaiPhongBoNho();
    std::string dong;
    int loaiHienTai = 0;
    int demThanhCong = 0;

    while (std::getline(file, dong)) {
        if (dong.empty() || dong[0] == '#') {
            continue;
        }

        if (dong == "[VAN_PHONG]") { loaiHienTai = LOAI_VAN_PHONG; continue; }
        if (dong == "[SAN_XUAT]") { loaiHienTai = LOAI_SAN_XUAT;  continue; }
        if (dong == "[QUAN_LY]") { loaiHienTai = LOAI_QUAN_LY;   continue; }

        std::stringstream ss(dong);
        std::string muc;
        std::vector<std::string> parts;
        while (std::getline(ss, muc, '|')) {
            parts.push_back(muc);
        }

        try {
            NhanVien* nv = nullptr;
            if (loaiHienTai == LOAI_VAN_PHONG && parts.size() >= 7) {
                nv = new NhanVienVanPhong(parts[0], parts[1], parts[2], parts[3],
                    std::stoi(parts[4]), std::stoi(parts[5]), std::stoi(parts[6]));
            }
            else if (loaiHienTai == LOAI_SAN_XUAT && parts.size() >= 6) {
                nv = new NhanVienSanXuat(parts[0], parts[1], parts[2], parts[3],
                    std::stoi(parts[4]), std::stoi(parts[5]));
            }
            else if (loaiHienTai == LOAI_QUAN_LY && parts.size() >= 7) {
                nv = new QuanLy(parts[0], parts[1], parts[2], parts[3],
                    std::stoi(parts[4]), std::stoi(parts[5]), std::stod(parts[6]));
            }

            if (nv != nullptr) {
                themNhanVien(nv);
                demThanhCong++;
            }
        }
        catch (...) {
            continue;
        }
    }

    file.close();
    std::cout << "=> Da tu dong nap san " << demThanhCong << " nhan vien tu file '" << tenFile << "' vao he thong.\n";
}

// ==========================================
// HELPER: HỖ TRỢ CHỨC NĂNG THÊM MỚI
// ==========================================

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

std::string QuanLyNhanSu::tenLoai(int loai) {
    switch (loai) {
    case LOAI_VAN_PHONG:
        return "VAN PHONG";
    case LOAI_SAN_XUAT:
        return "SAN XUAT";
    default:
        return "QUAN LY";
    }
}

void QuanLyNhanSu::nhapNhanVienMoi(QuanLyNhanSu& quanLy, int loai) {
    std::string tienToYeuCau;
    std::string mauLoai;

    if (loai == LOAI_VAN_PHONG) {
        tienToYeuCau = TIEN_TO_VP;
        mauLoai = MauSacNhanSu::XANH_LA;
    }
    else if (loai == LOAI_SAN_XUAT) {
        tienToYeuCau = TIEN_TO_SX;
        mauLoai = MauSacNhanSu::VANG;
    }
    else {
        tienToYeuCau = TIEN_TO_QL;
        mauLoai = MauSacNhanSu::TIM;
    }

    auto inThongBaoCanGiua = [](const std::string& mau, const std::string& text) {
        int le = (DO_RONG_MAN_HINH - static_cast<int>(text.length())) / 2;
        if (le < 0) le = 0;
        std::cout << std::string(le, ' ') << mau << text << MauSacNhanSu::RESET << "\n";
        };

    while (true) {
        NhanVien* nhanVien = taoNhanVienTheoLoai(loai);

        std::string thongBao = "--- NHAP THONG TIN NHAN VIEN " + tenLoai(loai) + " ---";
        inThongBaoCanGiua(mauLoai + MauSacNhanSu::DAM, thongBao);

        nhanVien->nhap(std::cin);

        if (std::cin.eof()) {
            delete nhanVien;
            return;
        }
        if (std::cin.fail()) {
            std::cin.clear();
            boQuaDongThua();
            std::cout << "\n";
            inThongBaoCanGiua(MauSacNhanSu::DO + MauSacNhanSu::DAM, "LOI: DU LIEU NHAP KHONG HOP LE, VUI LONG NHAP LAI!");
            delete nhanVien;
            continue;
        }

        std::string maNhanVien = nhanVien->getMaNhanVien();
        while (true) {
            bool hopLeDinhDang = kiemTraDinhDangMa(maNhanVien);
            bool dungTienToLoai = (maNhanVien.size() == DO_DAI_MA && maNhanVien.substr(0, 4) == tienToYeuCau);
            bool biTrungMa = quanLy.kiemTraTrungMa(maNhanVien);

            if (hopLeDinhDang && dungTienToLoai && !biTrungMa) {
                break;
            }

            std::cout << "\n";
            if (!hopLeDinhDang || !dungTienToLoai) {
                std::string loiDinhDang = "LOI: Ma phai bat dau bang '" + tienToYeuCau + "' va co 4 chu so (VD: " + tienToYeuCau + "0001)!";
                inThongBaoCanGiua(MauSacNhanSu::DO + MauSacNhanSu::DAM, loiDinhDang);
            }
            else {
                std::string loiTrung = "LOI: Ma nhan vien '" + maNhanVien + "' da ton tai!";
                inThongBaoCanGiua(MauSacNhanSu::DO + MauSacNhanSu::DAM, loiTrung);
            }

            std::string cauNhacLai = "Nhap lai Ma Nhan Vien: ";
            int leNhapLai = (DO_RONG_MAN_HINH - static_cast<int>(cauNhacLai.length()) - 10) / 2;
            std::cout << "\n" << std::string(leNhapLai, ' ') << MauSacNhanSu::VANG << cauNhacLai << MauSacNhanSu::RESET;
            if (!std::getline(std::cin >> std::ws, maNhanVien)) {
                delete nhanVien;
                return;
            }
        }
        nhanVien->setMaNhanVien(maNhanVien);

        quanLy.themNhanVien(nhanVien);

        std::cout << "\n";
        inThongBaoCanGiua(MauSacNhanSu::XANH_DUONG + MauSacNhanSu::DAM, "THEM NHAN VIEN MOI THANH CONG!");
        std::cout << "\n";
        return;
    }
}

bool QuanLyNhanSu::kiemTraDinhDangMa(const std::string& maNhanVien) {
    if (maNhanVien.size() != DO_DAI_MA) {
        return false;
    }

    std::string tienTo = maNhanVien.substr(0, 4);
    if (tienTo != TIEN_TO_VP && tienTo != TIEN_TO_SX && tienTo != TIEN_TO_QL) {
        return false;
    }

    for (int i = 4; i < DO_DAI_MA; ++i) {
        if (maNhanVien[i] < '0' || maNhanVien[i] > '9') {
            return false;
        }
    }
    return true;
}

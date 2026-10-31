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
    const std::string XANH_DUONG = "\033[34m";
    const std::string DO = "\033[31m";
    const std::string VANG = "\033[33m";
    const std::string TIM = "\033[35m";
    const std::string TRANG = "\033[37m";
    const std::string DAM = "\033[1m";
}

namespace {
    const int DO_RONG_MAN_HINH = 66;
    const int DO_RONG_KET_QUA = 136;
    const int DO_RONG_THONG_KE = 63;
    const int DO_RONG_BANG = 137;
    const int DO_RONG_THOAT = 70;
    const int SO_COT = 8;
    const int DO_RONG_COT[SO_COT] = { 10, 20, 12, 16, 14, 14, 18, 16 };

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
    napDuLieuTuFile("Data/NhanVien.txt");
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
    std::cout << MauSacNhanSu::XANH_LA
        << "[" << LOAI_VAN_PHONG << "] Nhan vien Van phong (" << TIEN_TO_VP << "xxxx)\n"
        << MauSacNhanSu::VANG
        << "[" << LOAI_SAN_XUAT << "] Nhan vien San xuat (" << TIEN_TO_SX << "xxxx)\n"
        << MauSacNhanSu::TIM
        << "[" << LOAI_QUAN_LY << "] Quan ly cap cao (" << TIEN_TO_QL << "xxxx)\n"
        << MauSacNhanSu::RESET;
    inDongKe('-', DO_RONG_MAN_HINH);
    int loai = 0;
    if (!docSoNguyen("Chon loai nhan vien (1-3): ", LOAI_VAN_PHONG, LOAI_QUAN_LY, loai)) {
        return;
    }
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
    inTieuDeManHinh("XOA NHAN VIEN");
    if (!docChuoi("Nhap Ma nhan vien can xoa: ", maNhanVien)) {
        return;
    }
    if (quanLy.xoaNhanVien(maNhanVien)) {
        std::cout << MauSacNhanSu::XANH_LA
                  << "XOA NHAN VIEN CO MA '" << maNhanVien << "' THANH CONG!\n"
                  << MauSacNhanSu::RESET;
    }
    else {
        std::cout << MauSacNhanSu::DO
                  << "KHONG TIM THAY NHAN VIEN CO MA '" << maNhanVien << "' DE XOA!\n"
                  << MauSacNhanSu::RESET;
    }
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
    if (dsNhanVien_.empty()) {
        std::cout << "\nDANH SACH RONG, KHONG THE TIM KIEM!\n";
        return;
    }

    inTieuDeManHinh("TIM KIEM NHAN VIEN");
    std::cout << "[" << TIM_THEO_MA << "] Tim kiem chinh xac theo Ma Nhan Vien\n"
        << "[" << TIM_THEO_TEN << "] Tim kiem theo Tu khoa Ho va Ten\n";
    inDongKe('-', DO_RONG_MAN_HINH);

    int luaChon = 0;
    if (!docSoNguyen("Chon kieu tim kiem (1-2): ", TIM_THEO_MA, TIM_THEO_TEN, luaChon)) {
        return;
    }

    std::vector<NhanVien*> ketQua;
    if (luaChon == TIM_THEO_MA) {
        std::string maNhanVien;
        if (!docChuoi("Nhap ma nhan vien can tim: ", maNhanVien)) {
            return;
        }
        NhanVien* nhanVien = timKiemTheoMa(maNhanVien);
        if (nhanVien != nullptr) {
            ketQua.push_back(nhanVien);
        }
    }
    else {
        std::string tuKhoa;
        if (!docChuoi("Nhap tu khoa Ten can tim: ", tuKhoa)) {
            return;
        }
        ketQua = timKiemTheoTen(tuKhoa);
    }

    if (ketQua.empty()) {
        std::cout << "KHONG TIM THAY NHAN VIEN PHU HOP!\n";
        return;
    }
    std::cout << "TIM THAY " << ketQua.size() << " NHAN VIEN PHU HOP:\n";
    inDongKe('-', DO_RONG_KET_QUA);
    for (const NhanVien* nhanVien : ketQua) {
        nhanVien->hienThiThongTin();
    }
    inDongKe('-', DO_RONG_KET_QUA);
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

void QuanLyNhanSu::hienThiDanhSach() {
    if (dsNhanVien_.empty()) {
        std::cout << "\nDANH SACH NHAN VIEN HIEN DANG RONG!\n";
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

    std::cout << "\n";
    inDongKe('=', DO_RONG_BANG);
    std::cout << "DANH SACH NHAN VIEN PHAN THEO BO PHAN (DA SAP XEP TANG DAN THEO MA)\n";
    inDongKe('=', DO_RONG_BANG);
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

    inTieuDeManHinh("THONG KE QUY LUONG VA NHAN SU");
    std::cout << "1. Tong so nhan vien toan cong ty: " << dsNhanVien_.size() << " nguoi\n"
        << "2. Nhan vien Van phong: " << soVanPhong << " nguoi\n"
        << "3. Nhan vien San xuat: " << soSanXuat << " nguoi\n"
        << "4. Quan ly cap cao: " << soQuanLy << " nguoi\n";
    inDongKe('-', DO_RONG_THONG_KE);
    std::cout << MauSacNhanSu::XANH_LA
              << MauSacNhanSu::DAM
              << "TONG QUY LUONG PHAI CHI: " << dinhDangSoTien(tongLuong) << " VND\n"
              << MauSacNhanSu::RESET;
    return tongLuong;
}

// ==========================================
// 5. THOÁT CHƯƠNG TRÌNH
// ==========================================

void QuanLyNhanSu::thoatChuongTrinh() {
    giaiPhongBoNho();

    std::cout << "\n";
    inDongKe('=', DO_RONG_THOAT);
    std::cout << "Cam on ban da su dung phan mem Quan Ly Nhan Su C++. Tam biet!\n";
    inDongKe('=', DO_RONG_THOAT);
    std::exit(EXIT_SUCCESS);
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
        return "QUAN LY CAP CAO";
    }
}

void QuanLyNhanSu::nhapNhanVienMoi(QuanLyNhanSu& quanLy, int loai) {
    std::string tienToYeuCau;
    if (loai == LOAI_VAN_PHONG) tienToYeuCau = TIEN_TO_VP;
    else if (loai == LOAI_SAN_XUAT) tienToYeuCau = TIEN_TO_SX;
    else tienToYeuCau = TIEN_TO_QL;

    while (true) {
        NhanVien* nhanVien = taoNhanVienTheoLoai(loai);
        std::cout << "--- NHAP THONG TIN NHAN VIEN " << tenLoai(loai) << " ---\n";
        nhanVien->nhap(std::cin);

        if (std::cin.eof()) {
            delete nhanVien;
            return;
        }
        if (std::cin.fail()) {
            std::cin.clear();
            boQuaDongThua();
            std::cout << MauSacNhanSu::DO
                      << "DU LIEU NHAP KHONG HOP LE, VUI LONG NHAP LAI!\n"
                      << MauSacNhanSu::RESET;
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

            if (!hopLeDinhDang || !dungTienToLoai) {
                std::cout << MauSacNhanSu::VANG<<"LOI: Ma nhan vien '" << maNhanVien << "' phai bat dau bang '"
                    << tienToYeuCau << "' va co 4 chu so (VD: " << tienToYeuCau << "0001)!\n"<<MauSacNhanSu::RESET;
            }
            else {
                std::cout << MauSacNhanSu::DO << "LOI: Ma nhan vien '" << maNhanVien << "' da ton tai!\n"<< MauSacNhanSu::RESET;
            }

            if (!docChuoi("Nhap lai Ma Nhan Vien: ", maNhanVien)) {
                delete nhanVien;
                return;
            }
        }
        nhanVien->setMaNhanVien(maNhanVien);

        quanLy.themNhanVien(nhanVien);
        std::cout << MauSacNhanSu::XANH_LA
                  << "THEM NHAN VIEN MOI THANH CONG!\n"
                  << MauSacNhanSu::RESET;
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

// ==========================================
// HELPER: HỖ TRỢ SẮP XẾP & HIỂN THỊ
// ==========================================

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

void QuanLyNhanSu::inDauNhom(const std::string& tieuDe, const std::string& cot5, const std::string& cot6, const std::string& cot7) {
    std::cout << MauSacNhanSu::TIM
              << MauSacNhanSu::DAM
              << tieuDe << "\n"
              << MauSacNhanSu::RESET;
    std::cout << MauSacNhanSu::XANH_CYAN;
    inDongKe('-', DO_RONG_BANG);
    std::cout << MauSacNhanSu::VANG
              << MauSacNhanSu::DAM;
    inHangBang({ "Ma nhan vien", "Ho va ten", "Ngay sinh", "Dia chi", cot5, cot6, cot7, "Thuc nhan (VND)" });
    std::cout << MauSacNhanSu::XANH_CYAN;
    inDongKe('-', DO_RONG_BANG);
    std::cout << MauSacNhanSu::RESET;
}
void QuanLyNhanSu::inCuoiNhom(const std::string& tenNhom, int soLuong, double tongLuong) {
    std::cout << MauSacNhanSu::XANH_CYAN;
    inDongKe('-', DO_RONG_BANG);
    std::cout << MauSacNhanSu::XANH_LA
              << MauSacNhanSu::DAM
              << "=> Subtotal " << tenNhom << ": " << soLuong << " nhan vien | Tong luong: "
              << dinhDangSoTien(tongLuong) << " VND\n"
              << MauSacNhanSu::RESET;
}

void QuanLyNhanSu::inNhomVanPhong(const std::vector<const NhanVienVanPhong*>& danhSach) {
    double tongLuong = 0.0;
    inDauNhom("I. NHAN VIEN VAN PHONG (" + std::to_string(danhSach.size()) + " nguoi)",
        "Ngay cong", "Gio tang ca", "He so KPI");
    for (const NhanVienVanPhong* nhanVien : danhSach) {
        inHangBang({ nhanVien->getMaNhanVien(), nhanVien->getHoTen(), nhanVien->getNgaySinh(), nhanVien->getDiaChi(),
                    std::to_string(nhanVien->getSoNgayLamViec()) + " ngay",
                    std::to_string(nhanVien->getSoGioTangCa()) + "h",
                    dinhDangThapPhan(nhanVien->tinhHeSoKPI(), 2),
                    dinhDangSoTien(nhanVien->tinhLuong()) });
        tongLuong += nhanVien->tinhLuong();
    }
    inCuoiNhom("Van Phong", static_cast<int>(danhSach.size()), tongLuong);
}

void QuanLyNhanSu::inNhomSanXuat(const std::vector<const NhanVienSanXuat*>& danhSach) {
    double tongLuong = 0.0;
    inDauNhom("II. NHAN VIEN SAN XUAT (" + std::to_string(danhSach.size()) + " nguoi)",
        "So San Pham", "Dinh Muc", "He so KPI");
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
    inDauNhom("III. QUAN LY CAP CAO (" + std::to_string(danhSach.size()) + " nguoi)",
        "Luong CB", "He So CV", "Luong Trach Nhiem");
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

// ==========================================
// HELPER: NHẬP LIỆU BÀN PHÍM
// ==========================================

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

// ==========================================
// HELPER: XỬ LÝ CHUỖI, ĐỊNH DẠNG & GIAO DIỆN
// ==========================================

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

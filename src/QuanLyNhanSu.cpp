#include "QuanLyNhanSu.h"

#include "NhanVienSanXuat.h"
#include "NhanVienVanPhong.h"
#include "QuanLy.h"

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>

const int DO_RONG_MAN_HINH = 66;
const int DO_RONG_KET_QUA = 136;
const int DO_RONG_THONG_KE = 63;
const int DO_RONG_BANG = 120;
const int DO_RONG_THOAT = 70;
const int SO_COT = 8;
const int DO_RONG_COT[SO_COT] = {10, 20, 12, 16, 14, 14, 18, 16};

const int LOAI_VAN_PHONG = 1;
const int LOAI_SAN_XUAT = 2;
const int LOAI_QUAN_LY = 3;
const int TIM_THEO_MA = 1;
const int TIM_THEO_TEN = 2;
const int DINH_MUC_SAN_PHAM = 100;

const std::string TIEN_TO_MA = "NV";
const int SO_CHU_SO_MA = 4;

void boQuaDongThua() {
    std::string boDem;
    std::getline(std::cin, boDem);
}

bool docSoNguyen(const std::string& thongBao, int tuGiaTri, int denGiaTri, int& ketQua) {
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
        } else {
            if (std::cin.eof()) {
                return false;
            }
            std::cin.clear();
            boQuaDongThua();
            std::cout << "Du lieu khong hop le, vui long nhap so nguyen.\n";
        }
    }
}

bool docChuoi(const std::string& thongBao, std::string& ketQua) {
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

std::string chuyenThuong(const std::string& chuoi) {
    std::string ketQua = chuoi;
    for (char& kyTu : ketQua) {
        if (kyTu >= 'A' && kyTu <= 'Z') {
            kyTu = static_cast<char>(kyTu + ('a' - 'A'));
        }
    }
    return ketQua;
}

bool kiemTraDinhDangMa(const std::string& maNhanVien) {
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

int layPhanSo(const std::string& maNhanVien) {
    int phanSo = 0;
    for (std::string::size_type i = TIEN_TO_MA.size(); i < maNhanVien.size(); ++i) {
        phanSo = phanSo * 10 + (maNhanVien[i] - '0');
    }
    return phanSo;
}

bool soSanhTheoMa(const NhanVien* nhanVienA, const NhanVien* nhanVienB) {
    return layPhanSo(nhanVienA->getMaNhanVien()) < layPhanSo(nhanVienB->getMaNhanVien());
}

std::string dinhDangThapPhan(double giaTri, int soChuSo) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(soChuSo) << giaTri;
    return oss.str();
}

std::string dinhDangSoTien(double soTien) {
    NhanVienVanPhong nhanVienTam;
    return nhanVienTam.dinhDangTien(soTien);
}

NhanVien* taoNhanVienTheoLoai(int loai) {
    switch (loai) {
        case LOAI_VAN_PHONG:
            return new NhanVienVanPhong();
        case LOAI_SAN_XUAT:
            return new NhanVienSanXuat();
        default:
            return new QuanLy();
    }
}

std::string tenLoai(int loai) {
    switch (loai) {
        case LOAI_VAN_PHONG:
            return "VAN PHONG";
        case LOAI_SAN_XUAT:
            return "SAN XUAT";
        default:
            return "QUAN LY CAP CAO";
    }
}

void inDongKe(char kyTu, int doDai) {
    std::cout << std::string(doDai, kyTu) << "\n";
}

void inTieuDeManHinh(const std::string& tieuDe) {
    int doDaiMoiBen = (DO_RONG_MAN_HINH - static_cast<int>(tieuDe.size()) - 2) / 2;
    std::cout << "\n" << std::string(doDaiMoiBen, '=') << " " << tieuDe << " "
              << std::string(doDaiMoiBen, '=') << "\n";
}

void giaoDienKetQuaXoa(QuanLyNhanSu& quanLy, std::string& maNhanVien) {
    inTieuDeManHinh("XOA NHAN VIEN");
    
    if (!docChuoi("Nhap Ma nhan vien can xoa: ", maNhanVien)) {
        return; 
    }

    if (quanLy.xoaNhanVien(maNhanVien)) {
        std::cout << "XOA NHAN VIEN CO MA '" << maNhanVien << "' THANH CONG!\n";
    } else {
        std::cout << "KHONG TIM THAY NHAN VIEN CO MA '" << maNhanVien << "' DE XOA!\n";
    }
}

void nhapNhanVienMoi(QuanLyNhanSu& quanLy, int loai) {
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
            std::cout << "DU LIEU NHAP KHONG HOP LE, VUI LONG NHAP LAI!\n";
            delete nhanVien;
            continue;
        }

        std::string maNhanVien = nhanVien->getMaNhanVien();
        while (!kiemTraDinhDangMa(maNhanVien) || quanLy.kiemTraTrungMa(maNhanVien)) {
            if (!kiemTraDinhDangMa(maNhanVien)) {
                std::cout << "LOI: Ma NV '" << maNhanVien << "' sai dinh dang (VD: " << TIEN_TO_MA << "0001)!\n";
            } else {
                std::cout << "LOI: Ma NV '" << maNhanVien << "' da ton tai!\n";
            }
            if (!docChuoi("Nhap lai Ma Nhan Vien: ", maNhanVien)) {
                delete nhanVien;
                return;
            }
        }
        nhanVien->setMaNhanVien(maNhanVien);

        quanLy.themNhanVien(nhanVien);
        std::cout << "THEM NHAN VIEN MOI THANH CONG!\n";
        return;
    }
}

void inHangBang(const std::vector<std::string>& cacCot) {
    std::cout << std::left;
    for (int i = 0; i < SO_COT; ++i) {
        std::cout << std::setw(DO_RONG_COT[i]) << cacCot[i];
    }
    std::cout << "\n";
}

void inDauNhom(const std::string& tieuDe, const std::string& cot5, const std::string& cot6, const std::string& cot7) {
    std::cout << tieuDe << "\n";
    inDongKe('-', DO_RONG_BANG);
    inHangBang({"Ma NV", "Ho va Ten", "Ngay Sinh", "Dia Chi", cot5, cot6, cot7, "Thuc Nhan (VND)"});
    inDongKe('-', DO_RONG_BANG);
}

void inCuoiNhom(const std::string& tenNhom, int soLuong, double tongLuong) {
    inDongKe('-', DO_RONG_BANG);
    std::cout << "=> Subtotal " << tenNhom << ": " << soLuong << " nhan vien | Tong luong: "
              << dinhDangSoTien(tongLuong) << " VND\n";
}

void inNhomVanPhong(const std::vector<const NhanVienVanPhong*>& danhSach) {
    double tongLuong = 0.0;
    inDauNhom("I. NHAN VIEN VAN PHONG (" + std::to_string(danhSach.size()) + " nguoi)",
              "Ngay Cong", "Gio OT", "He so KPI");
    for (const NhanVienVanPhong* nhanVien : danhSach) {
        inHangBang({nhanVien->getMaNhanVien(), nhanVien->getHoTen(), nhanVien->getNgaySinh(), nhanVien->getDiaChi(),
                    std::to_string(nhanVien->getSoNgayLamViec()) + " ngay",
                    std::to_string(nhanVien->getSoGioTangCa()) + "h OT",
                    dinhDangThapPhan(nhanVien->tinhHeSoKPI(), 2),
                    dinhDangSoTien(nhanVien->tinhLuong())});
        tongLuong += nhanVien->tinhLuong();
    }
    inCuoiNhom("Van Phong", static_cast<int>(danhSach.size()), tongLuong);
}

void inNhomSanXuat(const std::vector<const NhanVienSanXuat*>& danhSach) {
    double tongLuong = 0.0;
    inDauNhom("II. NHAN VIEN SAN XUAT (" + std::to_string(danhSach.size()) + " nguoi)",
              "So San Pham", "Dinh Muc", "He so KPI");
    for (const NhanVienSanXuat* nhanVien : danhSach) {
        inHangBang({nhanVien->getMaNhanVien(), nhanVien->getHoTen(), nhanVien->getNgaySinh(), nhanVien->getDiaChi(),
                    std::to_string(nhanVien->getSoSanPham()) + " SP",
                    std::to_string(DINH_MUC_SAN_PHAM) + " SP",
                    dinhDangThapPhan(nhanVien->tinhHeSoKPI(), 2),
                    dinhDangSoTien(nhanVien->tinhLuong())});
        tongLuong += nhanVien->tinhLuong();
    }
    inCuoiNhom("San Xuat", static_cast<int>(danhSach.size()), tongLuong);
}

void inNhomQuanLy(const std::vector<const QuanLy*>& danhSach) {
    double tongLuong = 0.0;
    inDauNhom("III. QUAN LY CAP CAO (" + std::to_string(danhSach.size()) + " nguoi)",
              "Luong CB", "He So CV", "Luong Trach Nhiem");
    for (const QuanLy* nhanVien : danhSach) {
        inHangBang({nhanVien->getMaNhanVien(), nhanVien->getHoTen(), nhanVien->getNgaySinh(), nhanVien->getDiaChi(),
                    dinhDangSoTien(nhanVien->getLuongCoBan()),
                    dinhDangThapPhan(nhanVien->getHeSoChucVu(), 2),
                    dinhDangSoTien(nhanVien->getLuongTrachNhiem()),
                    dinhDangSoTien(nhanVien->tinhLuong())});
        tongLuong += nhanVien->tinhLuong();
    }
    inCuoiNhom("Quan Ly", static_cast<int>(danhSach.size()), tongLuong);
}

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
    sapXepDanhSach();
}

bool QuanLyNhanSu::kiemTraTrungMa(const std::string& maNhanVien) const {
    return timKiemTheoMa(maNhanVien) != nullptr;
}

void QuanLyNhanSu::nhapDanhSach() {
    inTieuDeManHinh("THEM NHAN VIEN MOI");
    std::cout << "[" << LOAI_VAN_PHONG << "] Nhan vien Van phong\n"
              << "[" << LOAI_SAN_XUAT << "] Nhan vien San xuat\n"
              << "[" << LOAI_QUAN_LY << "] Quan ly cap cao\n";
    inDongKe('-', DO_RONG_MAN_HINH);

    int loai = 0;
    if (!docSoNguyen("Chon loai nhan vien (1-3): ", LOAI_VAN_PHONG, LOAI_QUAN_LY, loai)) {
        return;
    }
    nhapNhanVienMoi(*this, loai);
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
        std::cout << "\nDANH SACH RONG, KHONG THE TIM KIEM!\n";
        return;
    }

    inTieuDeManHinh("TIM KIEM NHAN VIEN");
    std::cout << "[" << TIM_THEO_MA << "] Tim kiem chinh xac theo Ma NV\n"
              << "[" << TIM_THEO_TEN << "] Tim kiem theo Tu khoa Ho va Ten\n";
    inDongKe('-', DO_RONG_MAN_HINH);

    int luaChon = 0;
    if (!docSoNguyen("Chon kieu tim kiem (1-2): ", TIM_THEO_MA, TIM_THEO_TEN, luaChon)) {
        return;
    }

    std::vector<NhanVien*> ketQua;
    if (luaChon == TIM_THEO_MA) {
        std::string maNhanVien;
        if (!docChuoi("Nhap Ma NV can tim: ", maNhanVien)) {
            return;
        }
        NhanVien* nhanVien = timKiemTheoMa(maNhanVien);
        if (nhanVien != nullptr) {
            ketQua.push_back(nhanVien);
        }
    } else {
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

void QuanLyNhanSu::hienThiDanhSach() const {
    if (dsNhanVien_.empty()) {
        std::cout << "\nDANH SACH NHAN VIEN HIEN DANG RONG!\n";
        return;
    }

    std::vector<const NhanVienVanPhong*> vanPhong;
    std::vector<const NhanVienSanXuat*> sanXuat;
    std::vector<const QuanLy*> quanLy;
    for (const NhanVien* nhanVien : dsNhanVien_) {
        if (const NhanVienVanPhong* nhanVienVanPhong = dynamic_cast<const NhanVienVanPhong*>(nhanVien)) {
            vanPhong.push_back(nhanVienVanPhong);
        } else if (const NhanVienSanXuat* nhanVienSanXuat = dynamic_cast<const NhanVienSanXuat*>(nhanVien)) {
            sanXuat.push_back(nhanVienSanXuat);
        } else if (const QuanLy* nhanVienQuanLy = dynamic_cast<const QuanLy*>(nhanVien)) {
            quanLy.push_back(nhanVienQuanLy);
        }
    }

    std::cout << "\n";
    inDongKe('=', DO_RONG_BANG);
    std::cout << "DANH SACH NHAN VIEN PHAN THEO BO PHAN\n";
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
        } else if (dynamic_cast<const NhanVienSanXuat*>(nhanVien) != nullptr) {
            ++soSanXuat;
        } else if (dynamic_cast<const QuanLy*>(nhanVien) != nullptr) {
            ++soQuanLy;
        }
    }

    inTieuDeManHinh("THONG KE TOAN CONG TY");
    std::cout << "1. Tong so nhan vien hien co: " << dsNhanVien_.size() << " nguoi\n"
              << "2. Nhan vien Van phong: " << soVanPhong << " nguoi\n"
              << "3. Nhan vien San xuat: " << soSanXuat << " nguoi\n"
              << "4. Quan ly cap cao: " << soQuanLy << " nguoi\n";
    inDongKe('-', DO_RONG_THONG_KE);
    std::cout << "TONG QUY LUONG PHAI CHI: " << dinhDangSoTien(tongLuong) << " VND\n";
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

    std::cout << "\nNAP THANH CONG " << dsNhanVien_.size() << " NHAN VIEN MAU VAO HE THONG!\n";
}

void QuanLyNhanSu::thoatChuongTrinh() {
    giaiPhongBoNho();

    std::cout << "\n";
    inDongKe('=', DO_RONG_THOAT);
    std::cout << "Cam on ban da su dung phan mem Quan Ly Nhan Su C++. Tam biet!\n";
    inDongKe('=', DO_RONG_THOAT);
    std::exit(EXIT_SUCCESS);
}

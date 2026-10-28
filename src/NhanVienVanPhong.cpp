#include "NhanVienVanPhong.h"
#include <iomanip>

NhanVienVanPhong::NhanVienVanPhong() 
    : NhanVien(), soNgayLamViec_(0), donGiaNgay_(0.0), soGioTangCa_(0.0) {}

NhanVienVanPhong::NhanVienVanPhong(std::string maNV, std::string hoTen, std::string ngaySinh, std::string diaChi,
                                   int soNgayLamViec, double donGiaNgay, double soGioTangCa)
    : NhanVien(maNV, hoTen, ngaySinh, diaChi), 
      soNgayLamViec_(soNgayLamViec), donGiaNgay_(donGiaNgay), soGioTangCa_(soGioTangCa) {}

// Quyết định heSoKPI_ dựa trên số ngày làm việc
double NhanVienVanPhong::TinhHeSoKPI() const {
    if (soNgayLamViec_ >= 22) return 1.2;
    if (soNgayLamViec_ >= 18) return 1.0;
    return 0.9;
}

// Lương = Ngày làm * Đơn giá + OT * 150.000 * KPI
double NhanVienVanPhong::TinhLuong() const {
    double luongChinh = soNgayLamViec_ * donGiaNgay_;
    double tienOT = soGioTangCa_ * 150000.0;
    return luongChinh + (tienOT * TinhHeSoKPI());
}

void NhanVienVanPhong::Nhap(std::istream& in) {
    NhanVien::Nhap(in);
    std::cout << "Nhap so ngay lam viec: ";
    in >> soNgayLamViec_;
    std::cout << "Nhap don gia ngay (VND): ";
    in >> donGiaNgay_;
    std::cout << "Nhap so gio tang ca (OT): ";
    in >> soGioTangCa_;
}

void NhanVienVanPhong::Xuat(std::ostream& out) const {
    NhanVien::Xuat(out);
    out << std::left 
        << std::setw(20) << "Van Phong"
        << std::setw(18) << (std::to_string(soNgayLamViec_) + " ngay")
        << std::setw(18) << (std::to_string((int)soGioTangCa_) + "h OT (KPI " + std::to_string(TinhHeSoKPI()).substr(0,3) + ")")
        << std::setw(18) << std::fixed << std::setprecision(0) << TinhLuong();
}

int NhanVienVanPhong::getSoNgayLamViec() const { return soNgayLamViec_; }
void NhanVienVanPhong::setSoNgayLamViec(int soNgay) { soNgayLamViec_ = soNgay; }
double NhanVienVanPhong::getDonGiaNgay() const { return donGiaNgay_; }
void NhanVienVanPhong::setDonGiaNgay(double donGia) { donGiaNgay_ = donGia; }
double NhanVienVanPhong::getSoGioTangCa() const { return soGioTangCa_; }
void NhanVienVanPhong::setSoGioTangCa(double soGio) { soGioTangCa_ = soGio; }

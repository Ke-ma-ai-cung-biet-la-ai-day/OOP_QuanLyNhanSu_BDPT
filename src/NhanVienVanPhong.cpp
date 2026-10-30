#include "NhanVienVanPhong.h"
#include <iomanip>

NhanVienVanPhong::NhanVienVanPhong() 
    : NhanVien(), soNgayLamViec_(0), donGiaNgay_(0.0), soGioTangCa_(0.0) {}

NhanVienVanPhong::NhanVienVanPhong(const std::string& maNhanVien, const std::string& hoTen, const std::string& ngaySinh, const std::string& diaChi,
                                   int& soNgayLamViec, int& donGiaNgay, int& soGioTangCa)
    : NhanVien(maNhanVien, hoTen, ngaySinh, diaChi), 
      soNgayLamViec_(soNgayLamViec), donGiaNgay_(donGiaNgay), soGioTangCa_(soGioTangCa) {}

NhanVienVanPhong::~NhanVienVanPhong(){}

int NhanVienVanPhong::getSoNgayLamViec() const { return soNgayLamViec_; }
void NhanVienVanPhong::setSoNgayLamViec(const int& soNgay) { soNgayLamViec_ = soNgay; }
double NhanVienVanPhong::getDonGiaNgay() const { return donGiaNgay_; }
void NhanVienVanPhong::setDonGiaNgay(const int& donGia) { donGiaNgay_ = donGia; }
int NhanVienVanPhong::getSoGioTangCa() const { return soGioTangCa_; }
void NhanVienVanPhong::setSoGioTangCa(const int& soGio) { soGioTangCa_ = soGio; }

double NhanVienVanPhong::tinhHeSoKPI() const {
    if (soNgayLamViec_ >= 22) return 1.2;
    if (soNgayLamViec_ >= 18) return 1.0;
    return 0.9;
}


double NhanVienVanPhong::tinhLuong() const {
    double luongChinh = soNgayLamViec_ * donGiaNgay_;
    double tienOT = soGioTangCa_ * TIEN_TANG_CA;
    return luongChinh + (tienOT * tinhHeSoKPI());
}

void NhanVienVanPhong::hienThiThongTin() const {
    xuat(std::cout);
    std::cout << std:: endl;
}

void NhanVienVanPhong::nhap(std::istream& in) {
    NhanVien::nhap(in);
    std::cout << "Nhap so ngay lam viec: ";
    in >> soNgayLamViec_;
    std::cout << "Nhap don gia ngay (VND): ";
    in >> donGiaNgay_;
    std::cout << "Nhap so gio tang ca (OT): ";
    in >> soGioTangCa_;
}

void NhanVienVanPhong::xuat(std::ostream& out) const {
    NhanVien::xuat(out);
    out << std::left 
        << std::setw(20) << "Van Phong"
        << std::setw(18) << (std::to_string(soNgayLamViec_) + " ngay")
        << std::setw(18) << (std::to_string(soGioTangCa_) + "h OT (KPI " + std::to_string(tinhHeSoKPI()).substr(0,3) + ")")
        << std::setw(18) << std::fixed << std::setprecision(0) << tinhLuong();
}


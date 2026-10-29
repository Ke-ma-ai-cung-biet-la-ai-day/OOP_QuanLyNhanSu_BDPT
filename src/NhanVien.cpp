#include "NhanVien.h"


NhanVien::NhanVien() {
    maNhanVien_ = "";
    hoTen_ = "";
    ngaySinh = "";
    diaChi = "";
}
NhanVien::NhanVien(const std::string& maNhanVien, const std::string& hoTen, const std::string& ngaySinh, const std::string& diaChi) {
    maNhanVien_ = maNhanVien;
    hoTen_ = hoTen;
    ngaySinh = ngaySinh;
    diaChi = diaChi;    
}
NhanVien::~NhanVien() {}

const std::string& NhanVien::getMaNhanVien() const { return maNhanVien_; }
void NhanVien::setMaNhanVien(const std::string& maNhanVien) { maNhanVien_ = maNhanVien; }
const std::string& NhanVien::getHoTen() const { return hoTen_; }
void NhanVien::setHoTen(const std::string& hoTen) { hoTen_ = hoTen; }
const std::string& NhanVien::getNgaySinh() const { return ngaySinh_; }
void NhanVien::setNgaySinh(const std::string& ngaySinh) { ngaySinh_ = ngaySinh; }
const std::string& NhanVien::getDiaChi() const { return diaChi_; }
void NhanVien::setDiaChi(const std::string& diaChi) { diaChi_ = diaChi; }

std::string dinhDangTien (double soTien) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision (0) << soTien;
    std::string s = oss.str();
    int vitri = (int)s.length() - 3;
    while (vitri > 0) {
        s.insert(viTri, ".");
        viTri -= 3;
    }
    return s;
}

void NhanVien::nhap(std::istream& in) {
    std::cout << "Nhap ma nhan vien: ";
    std::getline(in >> std::ws, maNhanVien_);
    std::cout << "Nhap ho va ten: ";
    std::getline(in >> std::ws, hoTen_);
    std::cout << "Nhap ngay sinh (dd/mm/yyyy): ";
    std::getline(in >> std::ws, ngaySinh_);
    std::cout << "Nhap dia chi: ";
    std::getline(in >> std::ws, diaChi_);
}
void NhanVien::xuat(std::ostream& out) const {
    out << std::left << std::setw(10) << maNhanVien_ << std::setw(22) << hoTen_ << std::setw(14) << ngaySinh_ << std::setw(20) << diaChi_;
}
void NhanVien::hienThiThongTin() const {
    this->xuat(std::cout);
}

std::istream& operator>>(std::istream& in, NhanVien& nv) {
    nv.nhap(in);
    return in;
}
std::ostream& operator<<(std::ostream& out, const NhanVien& nv) {
    nv.xuat(out);
    return out;
}

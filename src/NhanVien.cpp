#include "NhanVien.h"

// Constructors & Destructor
NhanVien::NhanVien() 
    : maNV_(""), hoTen_(""), ngaySinh_(""), diaChi_("") {}

NhanVien::NhanVien(const std::string& maNV, const std::string& hoTen, const std::string& ngaySinh, const std::string& diaChi)
    : maNV_(maNV), hoTen_(hoTen), ngaySinh_(ngaySinh), diaChi_(diaChi) {}

NhanVien::~NhanVien() {}

// Cài đặt Getters (Trả về tham chiếu hằng, không copy dữ liệu)
const std::string& NhanVien::getMaNV() const { return maNV_; }
void NhanVien::setMaNV(const std::string& maNV) { maNV_ = maNV; }

const std::string& NhanVien::getHoTen() const { return hoTen_; }
void NhanVien::setHoTen(const std::string& hoTen) { hoTen_ = hoTen; }

const std::string& NhanVien::getNgaySinh() const { return ngaySinh_; }
void NhanVien::setNgaySinh(const std::string& ngaySinh) { ngaySinh_ = ngaySinh; }

const std::string& NhanVien::getDiaChi() const { return diaChi_; }
void NhanVien::setDiaChi(const std::string& diaChi) { diaChi_ = diaChi; }

// Nhập / Xuất dữ liệu
void NhanVien::Nhap(std::istream& in) {
    std::cout << "Nhap ma nhan vien: ";
    std::getline(in >> std::ws, maNV_);
    std::cout << "Nhap ho va ten: ";
    std::getline(in, hoTen_);
    std::cout << "Nhap ngay sinh (dd/mm/yyyy): ";
    std::getline(in, ngaySinh_);
    std::cout << "Nhap dia chi: ";
    std::getline(in, diaChi_);
}

void NhanVien::Xuat(std::ostream& out) const {
    out << std::left << std::setw(10) << maNV_ 
        << std::setw(22) << hoTen_ 
        << std::setw(14) << ngaySinh_ 
        << std::setw(20) << diaChi_;
}

void NhanVien::HienThiThongTin() const {
    this->Xuat(std::cout);
}

std::istream& operator>>(std::istream& in, NhanVien& nv) {
    nv.Nhap(in);
    return in;
}

std::ostream& operator<<(std::ostream& out, const NhanVien& nv) {
    nv.Xuat(out);
    return out;
}

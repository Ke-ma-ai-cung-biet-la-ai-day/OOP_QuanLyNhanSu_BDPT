#ifndef QUANLY_H
#define QUANLY_H

#include "NhanVien.h"

class QuanLy : public NhanVien {
private:
    double luongCoBan_;       // Lương cơ bản cố định
    double luongTrachNhiem_;  // Phụ cấp lương trách nhiệm

public:
    // 1. Constructors & Destructor
    QuanLy();
    QuanLy(const std::string& maNV, 
           const std::string& hoTen, 
           const std::string& ngaySinh, 
           const std::string& diaChi, 
           double luongCoBan, 
           double luongTrachNhiem);
    virtual ~QuanLy();

    // 2. Getters & Setters
    double getLuongCoBan() const;
    void setLuongCoBan(double luongCoBan);

    double getLuongTrachNhiem() const;
    void setLuongTrachNhiem(double luongTrachNhiem);

    // 3. Ghi đè các phương thức đa hình (Polymorphism)
    double TinhLuong() override;
    void Nhap(std::istream& in) override;
    void Xuat(std::ostream& out) const override;
    void HienThiThongTin() const override;
};

#endif // QUANLY_H

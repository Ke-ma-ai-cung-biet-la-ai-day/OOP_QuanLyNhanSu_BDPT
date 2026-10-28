#ifndef QUAN_LY_H
#define QUAN_LY_H

#include "NhanVien.h"

class QuanLy : public NhanVien {
private:
    double luongCoBan_;
    double heSoChucVu_;
    double luongTrachNhiem_;

public:
    QuanLy();
    QuanLy(std::string maNV, std::string hoTen, std::string ngaySinh, std::string diaChi,
           double luongCoBan, double heSoChucVu, double luongTrachNhiem);

    // Ghi đè tính lương đa hình
    double TinhLuong() const override;

    // Ghi đè Nhập / Xuất dữ liệu
    void Nhap(std::istream& in) override;
    void Xuat(std::ostream& out) const override;

    // Getters / Setters
    double getLuongCoBan() const;
    void setLuongCoBan(double luongCB);
    double getHeSoChucVu() const;
    void setHeSoChucVu(double heSo);
    double getLuongTrachNhiem() const;
    void setLuongTrachNhiem(double luongTN);
};

#endif // QUAN_LY_H

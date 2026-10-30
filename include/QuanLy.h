#ifndef QUAN_LY_H
#define QUAN_LY_H

#include "NhanVien.h"

class QuanLy : public NhanVien {
private:
    int luongCoBan_;
    int luongTrachNhiem_;
    double heSoChucVu_;

public:
    QuanLy();
    QuanLy(const std::string& maNhanVien, const std::string& hoTen, const std::string& ngaySinh, const std::string& diaChi,
           const int& luongCoBan, const int& luongTrachNhiem, const double& heSoChucVu);


    virtual ~QuanLy();
    
    int getLuongCoBan() const;
    void setLuongCoBan(const int& luongCoBan);
    int getLuongTrachNhiem() const;
    void setLuongTrachNhiem(const int& luongTrachNhiem);
    double getHeSoChucVu() const;
    void setHeSoChucVu(const double& heSoChucVu);

    double tinhLuong() const override;

    void nhap(std::istream& in) override;
    void xuat(std::ostream& out) const override;

    void hienThiThongTin() const override;

};

#endif // QUAN_LY_H

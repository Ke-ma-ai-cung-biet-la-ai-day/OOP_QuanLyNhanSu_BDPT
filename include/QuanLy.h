#ifndef QUAN_LY_H
#define QUAN_LY_H

#include "NhanVien.h"

class QuanLy : public NhanVien {
private:
    double luongCoBan_;
    double luongTrachNhiem_;
    double heSoChucVu_;

public:
    QuanLy();
    QuanLy(std::string maNV, std::string hoTen, std::string ngaySinh, std::string diaChi,
           double luongCoBan, double luongTrachNhiem, double heSoChucVu);


    virtual ~QuanLy();
    
    double getLuongCoBan() const;
    void setLuongCoBan(double luongCB);
    double getHeSoChucVu() const;
    void setHeSoChucVu(double heSo);
    double getLuongTrachNhiem() const;
    void setLuongTrachNhiem(double luongTN);

    double TinhLuong() const override;

    void Nhap(std::istream& in) override;
    void Xuat(std::ostream& out) const override;

    void hienThiThongTin() const override;

};

#endif 

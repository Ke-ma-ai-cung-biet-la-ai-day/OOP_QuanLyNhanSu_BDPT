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
           int& luongCoBan, int& luongTrachNhiem, double& heSoChucVu);


    virtual ~QuanLy();
    
    int getLuongCoBan() const;
    void setLuongCoBan(const int& luongCB);
    int getHeSoChucVu() const;
    void setHeSoChucVu(const int& heSo);
    double getLuongTrachNhiem() const;
    void setLuongTrachNhiem(const double& luongTN);

    double tinhLuong() const override;

    void nhap(std::istream& in) override;
    void xuat(std::ostream& out) const override;

    void hienThiThongTin() const override;

};

#endif 

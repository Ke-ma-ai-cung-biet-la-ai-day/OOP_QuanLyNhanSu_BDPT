#ifndef NHAN_VIEN_SAN_XUAT_H
#define NHAN_VIEN_SAN_XUAT_H

#include "NhanVien.h"

class NhanVienSanXuat : public NhanVien {
private:
    int soSanPham_;
    double donGiaSanPham_;

    static const int DINH_MUC = 100;

public:
    NhanVienSanXuat();
    NhanVienSanXuat(std::string maNV, std::string hoTen, std::string ngaySinh, std::string diaChi,
                    int soSanPham, double donGiaSanPham);

    virtual ~NhanVienSanXuat();

    int getSoSanPham() const;
    void setSoSanPham(int soSP);
    double getDonGiaSanPham() const;
    void setDonGiaSanPham(double donGia);

    double TinhHeSoKPI() const;

    double TinhLuong() const override;

    void hienThiThongTin() const override;

    void Nhap(std::istream& in) override;
    void Xuat(std::ostream& out) const override;

    
};

#ifndef NHAN_VIEN_VAN_PHONG_H
#define NHAN_VIEN_VAN_PHONG_H

#include "NhanVien.h"

class NhanVienVanPhong : public NhanVien {
private:
    int soNgayLamViec_;
    double donGiaNgay_;
    int soGioTangCa_; 

public:
    NhanVienVanPhong();
    NhanVienVanPhong(std::string maNV, std::string hoTen, std::string ngaySinh, std::string diaChi,
                     int soNgayLamViec, double donGiaNgay, int soGioTangCa);
    
    virtual ~NhanVienVanPhong();

    int getSoNgayLamViec() const;
    void setSoNgayLamViec(int soNgay);
    double getDonGiaNgay() const;
    void setDonGiaNgay(double donGia);
    int getSoGioTangCa() const;
    void setSoGioTangCa(int soGio);

    double TinhHeSoKPI() const;

    double TinhLuong() const override;

    void hienThiThongTin() const override;

    void Nhap(std::istream& in) override;
    void Xuat(std::ostream& out) const override;

    
};

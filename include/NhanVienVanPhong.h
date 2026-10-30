#ifndef NHAN_VIEN_VAN_PHONG_H
#define NHAN_VIEN_VAN_PHONG_H

#include "NhanVien.h"

class NhanVienVanPhong : public NhanVien {
private:
    int soNgayLamViec_;
    int donGiaNgay_;
    int soGioTangCa_; 
    static const int TIEN_TANG_CA = 150000;

public:
    NhanVienVanPhong();
    NhanVienVanPhong(const std::string& maNhanVien, const std::string& hoTen, const std::string& ngaySinh, const std::string& diaChi,
                     int& soNgayLamViec, int& donGiaNgay, int& soGioTangCa);
    
    virtual ~NhanVienVanPhong();

    int getSoNgayLamViec() const;
    void setSoNgayLamViec(const int& soNgay);
    int getDonGiaNgay() const;
    void setDonGiaNgay(const int& donGia);
    int getSoGioTangCa() const;
    void setSoGioTangCa(const int& soGio);

    double tinhHeSoKPI() const;

    double tinhLuong() const override;

    void hienThiThongTin() const override;

    void nhap(std::istream& in) override;
    void xuat(std::ostream& out) const override;

};

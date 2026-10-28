#ifndef NHAN_VIEN_VAN_PHONG_H
#define NHAN_VIEN_VAN_PHONG_H

#include "NhanVien.h"

class NhanVienVanPhong : public NhanVien {
private:
    int soNgayLamViec_;
    double donGiaNgay_;
    double soGioTangCa_; // Giờ OT

public:
    NhanVienVanPhong();
    NhanVienVanPhong(std::string maNV, std::string hoTen, std::string ngaySinh, std::string diaChi,
                     int soNgayLamViec, double donGiaNgay, double soGioTangCa);

    // Phương thức phụ trợ tính KPI theo số ngày làm việc
    double TinhHeSoKPI() const;

    // Ghi đè tính lương đa hình
    double TinhLuong() const override;

    // Ghi đè Nhập / Xuất dữ liệu
    void Nhap(std::istream& in) override;
    void Xuat(std::ostream& out) const override;

    // Getters / Setters
    int getSoNgayLamViec() const;
    void setSoNgayLamViec(int soNgay);
    double getDonGiaNgay() const;
    void setDonGiaNgay(double donGia);
    double getSoGioTangCa() const;
    void setSoGioTangCa(double soGio);
};

#endif // NHAN_VIEN_VAN_PHONG_H

#ifndef NHAN_VIEN_SAN_XUAT_H
#define NHAN_VIEN_SAN_XUAT_H

#include "NhanVien.h"

class NhanVienSanXuat : public NhanVien {
private:
    int soSanPham_;
    double donGiaSanPham_;

    // Định mức hằng số tĩnh dùng chung cho toàn bộ nhân viên sản xuất
    static const int DINH_MUC = 100;

public:
    NhanVienSanXuat();
    NhanVienSanXuat(std::string maNV, std::string hoTen, std::string ngaySinh, std::string diaChi,
                    int soSanPham, double donGiaSanPham);

    // Phương thức phụ trợ tính KPI theo mức sản phẩm
    double TinhHeSoKPI() const;

    // Ghi đè tính lương đa hình
    double TinhLuong() const override;

    // Ghi đè Nhập / Xuất dữ liệu
    void Nhap(std::istream& in) override;
    void Xuat(std::ostream& out) const override;

    // Getters / Setters
    int getSoSanPham() const;
    void setSoSanPham(int soSP);
    double getDonGiaSanPham() const;
    void setDonGiaSanPham(double donGia);
};

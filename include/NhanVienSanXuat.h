#ifndef NHAN_VIEN_SAN_XUAT_H
#define NHAN_VIEN_SAN_XUAT_H

#include "NhanVien.h"
#include <iomanip>
#include <string>

class NhanVienSanXuat : public NhanVien {
private:
    int soSanPham_;
    int donGiaSanPham_;
    static const int DINH_MUC = 100;
public:
    NhanVienSanXuat();
    NhanVienSanXuat(const std::string& maNhanVien, const std::string& hoTen, const std::string& ngaySinh, const std::string& diaChi,
                    const int& soSanPham, const int& donGiaSanPham);

    virtual ~NhanVienSanXuat();

    int getSoSanPham() const;
    void setSoSanPham(const int& soSanPham);
    int getDonGiaSanPham() const;
    void setDonGiaSanPham(const int& donGiaSanPham);

    double tinhHeSoKPI() const;

    double tinhLuong() const override;

    void nhap(std::istream& in) override;
    void xuat(std::ostream& out) const override;

    void hienThiThongTin() const override;
 
};

#endif // NHAN_VIEN_SAN_XUAT_H

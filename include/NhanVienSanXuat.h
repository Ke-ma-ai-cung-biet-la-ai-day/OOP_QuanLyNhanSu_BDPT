#ifndef NHANVIENSANXUAT_H
#define NHANVIENSANXUAT_H

#include "NhanVien.h"

class NhanVienSanXuat : public NhanVien {
private:
    int soSanPham_;         // Số lượng sản phẩm hoàn thành
    double donGiaSanPham_;  // Đơn giá cho mỗi sản phẩm

public:
    // 1. Constructors & Destructor
    NhanVienSanXuat();
    NhanVienSanXuat(const std::string& maNV, 
                    const std::string& hoTen, 
                    const std::string& ngaySinh, 
                    const std::string& diaChi, 
                    int soSanPham, 
                    double donGiaSanPham);
    virtual ~NhanVienSanXuat();

    // 2. Getters & Setters
    int getSoSanPham() const;
    void setSoSanPham(int soSanPham);

    double getDonGiaSanPham() const;
    void setDonGiaSanPham(double donGiaSanPham);

    // 3. Ghi đè các phương thức đa hình (Polymorphism)
    double TinhLuong() override;
    void Nhap(std::istream& in) override;
    void Xuat(std::ostream& out) const override;
    void HienThiThongTin() const override;
};

#endif // NHANVIENSANXUAT_H

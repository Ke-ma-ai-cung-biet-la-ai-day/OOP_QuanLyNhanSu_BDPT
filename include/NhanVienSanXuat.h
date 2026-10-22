#ifndef NHANVIENVANPHONG_H
#define NHANVIENVANPHONG_H

#include "NhanVien.h"

class NhanVienVanPhong : public NhanVien {
private:
    int soNgayLamViec_;     // Số ngày làm việc trong tháng
    double donGiaNgay_;     // Đơn giá lương theo ngày

public:
    // 1. Constructors & Destructor
    NhanVienVanPhong();
    NhanVienVanPhong(const std::string& maNV, 
                     const std::string& hoTen, 
                     const std::string& ngaySinh, 
                     const std::string& diaChi, 
                     int soNgayLamViec, 
                     double donGiaNgay);
    virtual ~NhanVienVanPhong();

    // 2. Getters & Setters
    int getSoNgayLamViec() const;
    void setSoNgayLamViec(int soNgayLamViec);

    double getDonGiaNgay() const;
    void setDonGiaNgay(double donGiaNgay);

    // 3. Ghi đè các phương thức đa hình (Polymorphism)
    double TinhLuong() override;
    void Nhap(std::istream& in) override;
    void Xuat(std::ostream& out) const override;
    void HienThiThongTin() const override;
};

#endif // NHANVIENVANPHONG_H

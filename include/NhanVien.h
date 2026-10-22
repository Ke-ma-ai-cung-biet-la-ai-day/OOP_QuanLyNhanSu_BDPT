#ifndef NHANVIEN_H
#define NHANVIEN_H

#include <iostream>
#include <string>
#include <iomanip>

class NhanVien {
protected:
    std::string maNV_;     // Mã nhân viên
    std::string hoTen_;    // Họ và tên
    std::string ngaySinh_; // Ngày sinh (dd/mm/yyyy)
    std::string diaChi_;   // Địa chỉ

public:
    // 1. Constructors & Destructor
    NhanVien();
    NhanVien(const std::string& maNV, 
             const std::string& hoTen, 
             const std::string& ngaySinh, 
             const std::string& diaChi);
    virtual ~NhanVien();

    // 2. Getters & Setters tối ưu chuẩn C++
    const std::string& getMaNV() const;            // Trả về const reference, hàm const
    void setMaNV(const std::string& maNV);

    const std::string& getHoTen() const;
    void setHoTen(const std::string& hoTen);

    const std::string& getNgaySinh() const;
    void setNgaySinh(const std::string& ngaySinh);

    const std::string& getDiaChi() const;
    void setDiaChi(const std::string& diaChi);

    // 3. Phương thức ảo / Thuần ảo
    virtual double TinhLuong() = 0;
    virtual void Nhap(std::istream& in);
    virtual void Xuat(std::ostream& out) const;
    virtual void HienThiThongTin() const;

    // 4. Operator Overloading
    friend std::istream& operator>>(std::istream& in, NhanVien& nv);
    friend std::ostream& operator<<(std::ostream& out, const NhanVien& nv);
};

#endif // NHANVIEN_H

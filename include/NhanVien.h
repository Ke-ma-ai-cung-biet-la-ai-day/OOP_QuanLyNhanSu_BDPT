#ifndef NHANVIEN_H
#define NHANVIEN_H

#include <iostream>
#include <string>
#include <iomanip>

class NhanVien {
private:
    std::string maNhanVien_;     
    std::string hoTen_;    
    std::string ngaySinh_; 
    std::string diaChi_;   
public:
    NhanVien();
    NhanVien(const std::string& maNhanVien, const std::string& hoTen, const std::string& ngaySinh, const std::string& diaChi);
    virtual ~NhanVien();

    const std::string& getMaNhanVien() const;            
    void setMaNhanVien(const std::string& maNhanVien);
    const std::string& getHoTen() const;
    void setHoTen(const std::string& hoTen);
    const std::string& getNgaySinh() const;
    void setNgaySinh(const std::string& ngaySinh);
    const std::string& getDiaChi() const;
    void setDiaChi(const std::string& diaChi);

    virtual void Nhap(std::istream& in);
    virtual void Xuat(std::ostream& out) const;
    virtual double tinhLuong() = 0;
    virtual void hienThiThongTin() const;

    friend std::istream& operator>>(std::istream& in, NhanVien& nv);
    friend std::ostream& operator<<(std::ostream& out, const NhanVien& nv);
};

#endif // NHANVIEN_H

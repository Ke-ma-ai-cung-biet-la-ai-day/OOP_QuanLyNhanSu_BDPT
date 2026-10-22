#ifndef QUANLYNHANSU_H
#define QUANLYNHANSU_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "NhanVien.h"
#include "NhanVienVanPhong.h"
#include "NhanVienSanXuat.h"
#include "QuanLy.h"

class QuanLyNhanSu {
private:
    std::vector<NhanVien*> dsNhanVien_; // Danh sách con trỏ quản lý nhân viên đa hình

public:
    // 1. Constructor & Destructor
    QuanLyNhanSu();
    ~QuanLyNhanSu();

    // 2. Quản lý bộ nhớ
    void GiaiPhongBoNho();

    // 3. Getter danh sách
    const std::vector<NhanVien*>& getDanhSach() const;

    // 4. Các chức năng Thêm / Nhập / Xuất
    void ThemNhanVien(NhanVien* nv);
    void NhapDanhSach();
    void XuatDanhSach() const;

    // 5. Tìm kiếm & Xóa
    NhanVien* TimKiemTheoMa(const std::string& maNV) const;
    std::vector<NhanVien*> TimKiemTheoTen(const std::string& hoTen) const;
    bool XoaNhanVienTheoMa(const std::string& maNV);

    // 6. Sắp xếp & Thống kê
    void SapXepLuongGiamDan();
    double TinhTongLuong() const;
};

#endif // QUANLYNHANSU_H

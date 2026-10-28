#ifndef QUAN_LY_NHAN_SU_H
#define QUAN_LY_NHAN_SU_H

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
    std::vector<NhanVien*> dsNhanVien_;

public:
    QuanLyNhanSu();
    ~QuanLyNhanSu();

    void GiaiPhongBoNho();
    void ThemNhanVien(NhanVien* nv);
    bool KiemTraTrungMa(const std::string& maNV) const;

    // Các phương thức thực thi chức năng
    void NhapDanhSach();
    void XuatDanhSach() const;

    NhanVien* TimKiemTheoMa(const std::string& maNV) const;
    std::vector<NhanVien*> TimKiemTheoTen(const std::string& ten) const;
    void TimKiemMenu() const;

    bool XoaNhanVienTheoMa(const std::string& maNV);
    void SapXepMenu();

    double TinhTongLuong() const;
    void ThongKeQuyLuong() const;

    void NapDuLieuMau();

    bool CapNhatThongTin(const std::string& maNV);
    void CapNhatMenu();
};

#endif // QUAN_LY_NHAN_SU_H

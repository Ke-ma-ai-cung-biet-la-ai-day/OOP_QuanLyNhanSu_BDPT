#ifndef QUANLYNHANSU_H
#define QUANLYNHANSU_H

#include "NhanVien.h"

#include <string>
#include <vector>

class QuanLyNhanSu {
private:
    std::vector<NhanVien*> dsNhanVien_;

public:
    QuanLyNhanSu();
    ~QuanLyNhanSu();

    void themNhanVien(NhanVien* nhanVien);
    bool kiemTraTrungMa(const std::string& maNhanVien) const;
    void nhapDanhSach();
    bool xoaNhanVien(const std::string& maNhanVien);
    NhanVien* timKiemTheoMa(const std::string& maNhanVien) const;
    std::vector<NhanVien*> timKiemTheoTen(const std::string& hoTen) const;
    void timKiemMenu();
    void hienThiDanhSach() const;
    void sapXepDanhSach();
    double thongKeQuyLuong() const;
    void giaiPhongBoNho();
    void napDuLieuMau();
    void thoatChuongTrinh();
};

#endif

#ifndef QUAN_LY_NHAN_SU_H
#define QUAN_LY_NHAN_SU_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

// Include các lớp đối tượng nhân viên
#include "NhanVien.h"
#include "NhanVienVanPhong.h"
#include "NhanVienSanXuat.h"
#include "QuanLy.h"

class QuanLyNhanSu {
private:
    // Mảng động quản lý các con trỏ nhân viên đa hình
    std::vector<NhanVien*> dsNhanVien_;

public:
    // =========================================================================
    // 1. KHỞI TẠO, HỦY VÀ QUẢN LÝ BỘ NHỚ LÕI
    // =========================================================================
    QuanLyNhanSu();
    ~QuanLyNhanSu();

    void GiaiPhongBoNho();
    void ThemNhanVien(NhanVien* nv);
    bool KiemTraTrungMa(const std::string& maNV) const;

    // =========================================================================
    // 2. CÁC PHƯƠNG THỨC XỬ LÝ CHỨC NĂNG (ĐỒNG BỘ THEO MENU CONSOLE LỰA CHỌN 1 - 8)
    // =========================================================================

    // --- Option 1: Nhập / Thêm mới nhân viên ---
    void NhapDanhSach();

    // --- Option 2: Hiển thị danh sách nhân viên dạng bảng ---
    void XuatDanhSach() const;

    // --- Option 3: Tìm kiếm nhân viên (Theo Mã chính xác hoặc Tên từ khóa) ---
    NhanVien* TimKiemTheoMa(const std::string& maNV) const;
    std::vector<NhanVien*> TimKiemTheoTen(const std::string& ten) const;
    void TimKiemMenu() const;

    // --- Option 4: Xóa nhân viên theo mã định danh ---
    bool XoaNhanVienTheoMa(const std::string& maNV);

    // --- Option 5: Sắp xếp danh sách (Menu đa tiêu chí: Lương, Mã NV, Họ tên) ---
    void SapXepMenu();

    // --- Option 6: Thống kê tổng số lượng và quỹ lương ---
    double TinhTongLuong() const;
    void ThongKeQuyLuong() const;

    // --- Option 7: Nạp dữ liệu mẫu khởi tạo sẵn (5 nhân viên đủ 3 loại) ---
    void NapDuLieuMau();

    // --- Option 8: Cập nhật thông tin nhân viên theo mã ---
    bool CapNhatThongTin(const std::string& maNV);
    void CapNhatMenu();
};

#endif // QUAN_LY_NHAN_SU_H

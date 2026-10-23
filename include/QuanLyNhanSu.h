#ifndef QUAN_LY_NHAN_SU_H
#define QUAN_LY_NHAN_SU_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

// Include các lớp nhân viên liên quan
#include "NhanVien.h"
#include "NhanVienVanPhong.h"
#include "NhanVienSanXuat.h"
#include "QuanLy.h"

class QuanLyNhanSu {
private:
    // Mảng động chứa danh sách con trỏ quản lý đa hình
    std::vector<NhanVien*> dsNhanVien_;

public:
    // --- Khởi tạo và Hủy ---
    QuanLyNhanSu();
    ~QuanLyNhanSu();

    // --- Các hàm tiện ích & Quản lý bộ nhớ ---
    void ThemNhanVien(NhanVien* nv);
    void GiaiPhongBoNho();
    bool KiemTraTrungMa(const std::string& maNV) const;

    // --- Các chức năng tương ứng 8 Lựa chọn trên Menu Console ---
    
    // Option 1: Nhập / Thêm mới nhân viên
    void NhapDanhSach();

    // Option 2: Hiển thị danh sách dạng bảng căn chỉnh thẳng hàng
    void XuatDanhSach() const;

    // Option 3: Tìm kiếm nhân viên (Theo Mã chính xác hoặc Tên chứa từ khóa)
    NhanVien* TimKiemTheoMa(const std::string& maNV) const;
    std::vector<NhanVien*> TimKiemTheoTen(const std::string& ten) const;
    void TimKiemMenu() const;

    // Option 4: Xóa nhân viên theo mã định danh
    bool XoaNhanVienTheoMa(const std::string& maNV);

    // Option 5: Sắp xếp danh sách theo thực nhận lương giảm dần (Dùng Lambda)
    void SapXepLuongGiamDan();

    // Option 6: Thống kê số lượng nhân viên và tổng quỹ lương
    double TinhTongLuong() const;
    void ThongKeQuyLuong() const;

    // Option 7: Nạp dữ liệu mẫu ngẫu nhiên (5 nhân viên đủ 3 loại)
    void NapDuLieuMau();
};

#endif // QUAN_LY_NHAN_SU_H

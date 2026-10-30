#ifndef QUANLYNHANSU_H
#define QUANLYNHANSU_H

#include "NhanVien.h"

#include <string>
#include <vector>

class QuanLyNhanSu {
private:
    std::vector<NhanVien*> dsNhanVien_;

    static const int DO_RONG_MA = 10;
    static const int DO_RONG_HO_TEN = 22;
    static const int DO_RONG_NGAY_SINH = 14;
    static const int DO_RONG_DIA_CHI = 20;
    static const int DO_RONG_LOAI = 20;
    static const int DO_RONG_CHI_TIET = 18;
    static const int DO_RONG_BANG = DO_RONG_MA + DO_RONG_HO_TEN + DO_RONG_NGAY_SINH
                                    + DO_RONG_DIA_CHI + DO_RONG_LOAI + 3 * DO_RONG_CHI_TIET;

    static const int LOAI_KET_THUC = 0;
    static const int LOAI_VAN_PHONG = 1;
    static const int LOAI_SAN_XUAT = 2;
    static const int LOAI_QUAN_LY = 3;

    static const std::string TIEN_TO_MA;
    static const int SO_CHU_SO_MA = 4;
    static const int SO_MA_TOI_DA = 9999;

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
    double thongKeQuyLuong() const;
    void giaiPhongBoNho();
    void napDuLieuMau();

private:
    bool nhapNhanVienMoi(int loai);
    std::string taoMaGoiY() const;
    static bool kiemTraDinhDangMa(const std::string& maNhanVien);
    static void boQuaDongThua();
    static bool docSoNguyen(const std::string& thongBao, int tuGiaTri, int denGiaTri, int& ketQua);
    static bool docChuoi(const std::string& thongBao, std::string& ketQua);
    static std::string chuyenThuong(const std::string& chuoi);
    static NhanVien* taoNhanVienTheoLoai(int loai);
    static void inTieuDeBang();
    static void inDanhSachNhanVien(const std::vector<NhanVien*>& danhSach);
};

#endif

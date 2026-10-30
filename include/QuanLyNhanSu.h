#ifndef QUANLYNHANSU_H
#define QUANLYNHANSU_H

#include "NhanVien.h"

#include <string>
#include <vector>

class QuanLyNhanSu {
private:
    std::vector<NhanVien*> dsNhanVien_;

    static void boQuaDongThua();
    static bool docSoNguyen(const std::string& thongBao, int tuGiaTri, int denGiaTri, int& ketQua);
    static bool docChuoi(const std::string& thongBao, std::string& ketQua);
    static std::string chuyenThuong(const std::string& chuoi);
    static bool kiemTraDinhDangMa(const std::string& maNhanVien);
    static int layPhanSo(const std::string& maNhanVien);
    static bool soSanhTheoMa(const NhanVien* nhanVienA, const NhanVien* nhanVienB);
    static std::string dinhDangThapPhan(double giaTri, int soChuSo);
    static std::string dinhDangSoTien(double soTien);
    static NhanVien* taoNhanVienTheoLoai(int loai);
    static std::string tenLoai(int loai);
    static void inDongKe(char kyTu, int doDai);
    static void inTieuDeManHinh(const std::string& tieuDe);
    static void nhapNhanVienMoi(QuanLyNhanSu& quanLy, int loai);
    static void inHangBang(const std::vector<std::string>& cacCot);
    static void inDauNhom(const std::string& tieuDe, const std::string& cot5,
                          const std::string& cot6, const std::string& cot7);
    static void inCuoiNhom(const std::string& tenNhom, int soLuong, double tongLuong);
    static void inNhomVanPhong(const std::vector<const class NhanVienVanPhong*>& danhSach);
    static void inNhomSanXuat(const std::vector<const class NhanVienSanXuat*>& danhSach);
    static void inNhomQuanLy(const std::vector<const class QuanLy*>& danhSach);

    QuanLyNhanSu(const QuanLyNhanSu&) = delete;
    QuanLyNhanSu& operator=(const QuanLyNhanSu&) = delete;

public:
    QuanLyNhanSu();
    ~QuanLyNhanSu();

    bool kiemTraTrungMa(const std::string& maNhanVien) const;
    void nhapDanhSach();
    void themNhanVien(NhanVien* nhanVien);
    NhanVien* timKiemTheoMa(const std::string& maNhanVien) const;
    std::vector<NhanVien*> timKiemTheoTen(const std::string& hoTen) const;
    void timKiemMenu();
    bool xoaNhanVien(const std::string& maNhanVien);
    void hienThiDanhSach() const;
    void sapXepDanhSach();
    double thongKeQuyLuong() const;
    void napDuLieuMau();
    void thoatChuongTrinh();
    void giaiPhongBoNho();

    static void giaoDienKetQuaXoa(QuanLyNhanSu& quanLy, std::string& maNhanVien);
};

#endif

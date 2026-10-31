#ifndef QUANLYNHANSU_H
#define QUANLYNHANSU_H

#include "NhanVien.h"

#include <string>
#include <vector>

// Forward declarations
class NhanVienVanPhong;
class NhanVienSanXuat;
class QuanLy;

class QuanLyNhanSu {
private:
    std::vector<NhanVien*> dsNhanVien_;

    // Chặn sao chép đối tượng
    QuanLyNhanSu(const QuanLyNhanSu&) = delete;
    QuanLyNhanSu& operator=(const QuanLyNhanSu&) = delete;

    // Helper: Nạp dữ liệu tự động từ file lúc khởi tạo
    void napDuLieuTuFile(const std::string& tenFile = "Data/NhanVien.txt");

    // Helper: Chức năng Thêm mới
    static NhanVien* taoNhanVienTheoLoai(int loai);
    static std::string tenLoai(int loai);
    static void nhapNhanVienMoi(QuanLyNhanSu& quanLy, int loai);
    static bool kiemTraDinhDangMa(const std::string& maNhanVien);

    // Helper: Sắp xếp & Hiển thị
    static int layPhanSo(const std::string& maNhanVien);
    static bool soSanhTheoMa(const NhanVien* nhanVienA, const NhanVien* nhanVienB);
    static void inHangBang(const std::vector<std::string>& cacCot);
    static void inDauNhom(const std::string& tieuDe, const std::string& cot5,
        const std::string& cot6, const std::string& cot7);
    static void inCuoiNhom(const std::string& tenNhom, int soLuong, double tongLuong);
    static void inNhomVanPhong(const std::vector<const NhanVienVanPhong*>& danhSach);
    static void inNhomSanXuat(const std::vector<const NhanVienSanXuat*>& danhSach);
    static void inNhomQuanLy(const std::vector<const QuanLy*>& danhSach);

    // Helper: Nhập liệu an toàn từ bàn phím
    static void boQuaDongThua();
    static bool docSoNguyen(const std::string& thongBao, int tuGiaTri, int denGiaTri, int& ketQua);
    static bool docChuoi(const std::string& thongBao, std::string& ketQua);

    // Helper: Xử lý chuỗi, định dạng & giao diện
    static std::string chuyenThuong(const std::string& chuoi);
    static std::string dinhDangThapPhan(double giaTri, int soChuSo);
    static std::string dinhDangSoTien(double soTien);
    static void inDongKe(char kyTu, int doDai);
    static void inTieuDeManHinh(const std::string& tieuDe);

public:
    // Khởi tạo (tự động load file) & Hủy
    QuanLyNhanSu();
    ~QuanLyNhanSu();
    void giaiPhongBoNho();

    // 1. Chức năng Thêm mới
    void nhapDanhSach();
    void themNhanVien(NhanVien* nhanVien);
    bool kiemTraTrungMa(const std::string& maNhanVien) const;

    // 2. Chức năng Xóa
    void giaoDienKetQuaXoa(QuanLyNhanSu& quanLy, std::string& maNhanVien);
    bool xoaNhanVien(const std::string& maNhanVien);

    // 3. Chức năng Tìm kiếm
    void timKiemMenu();
    NhanVien* timKiemTheoMa(const std::string& maNhanVien) const;
    std::vector<NhanVien*> timKiemTheoTen(const std::string& hoTen) const;

    // 4. Chức năng Hiển thị (tích hợp sắp xếp tăng dần theo mã & thống kê quỹ lương)
    void hienThiDanhSach();
    void sapXepDanhSach();
    double thongKeQuyLuong() const;

    // 5. Chức năng Thoát chương trình
    void thoatChuongTrinh();
};

#endif // QUANLYNHANSU_H
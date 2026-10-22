#include "QuanLyNhanSu.h"

// 1. Constructor
QuanLyNhanSu::QuanLyNhanSu() {}

// Destructor: Tự động giải phóng toàn bộ bộ nhớ con trỏ tránh Memory Leak
QuanLyNhanSu::~QuanLyNhanSu() {
    GiaiPhongBoNho();
}

// Giải phóng bộ nhớ thủ công khi cần xóa danh sách
void QuanLyNhanSu::GiaiPhongBoNho() {
    for (NhanVien* nv : dsNhanVien_) {
        delete nv; // Gọi virtual destructor của NhanVien
    }
    dsNhanVien_.clear();
}

// Lấy danh sách nhân viên (const reference)
const std::vector<NhanVien*>& QuanLyNhanSu::getDanhSach() const {
    return dsNhanVien_;
}

// 2. Thêm một nhân viên vào danh sách
void QuanLyNhanSu::ThemNhanVien(NhanVien* nv) {
    if (nv != nullptr) {
        dsNhanVien_.push_back(nv);
    }
}

// 3. Nhập danh sách nhân viên từ bàn phím
void QuanLyNhanSu::NhapDanhSach() {
    int soLuong = 0;
    std::cout << "Nhap so luong nhan vien can them: ";
    std::cin >> soLuong;

    for (int i = 0; i < soLuong; ++i) {
        std::cout << "\n--- NHAP THONG TIN NHAN VIEN THU " << (i + 1) << " ---\n";
        std::cout << "Chon loai nhan vien:\n";
        std::cout << "  1. Nhan vien Van phong\n";
        std::cout << "  2. Nhan vien San xuat\n";
        std::cout << "  3. Quan ly\n";
        std::cout << "Lua chon cua ban (1-3): ";
        
        int loai = 0;
        std::cin >> loai;

        NhanVien* nv = nullptr;
        if (loai == 1) {
            nv = new NhanVienVanPhong();
        } else if (loai == 2) {
            nv = new NhanVienSanXuat();
        } else if (loai == 3) {
            nv = new QuanLy();
        } else {
            std::cout << "Loai nhan vien khong hop le! Bo qua luot nhap nay.\n";
            continue;
        }

        // Gọi hàm Nhap() đa hình
        nv->Nhap(std::cin);

        // Kiểm tra trùng mã nhân viên
        if (TimKiemTheoMa(nv->getMaNV()) != nullptr) {
            std::cout << "Loi: Ma nhan vien '" << nv->getMaNV() << "' da ton tai! Huy nhap nhan vien nay.\n";
            delete nv; // Giải phóng ngay lập tức nếu bị trùng
        } else {
            ThemNhanVien(nv);
            std::cout << "=> Them nhan vien thanh cong!\n";
        }
    }
}

// 4. Xuất danh sách dạng bảng căn chỉnh hoàn chỉnh
void QuanLyNhanSu::XuatDanhSach() const {
    if (dsNhanVien_.empty()) {
        std::cout << "\n[Thong bao] Danh sach nhan vien hien dang rong!\n";
        return;
    }

    std::cout << "\n========================================================================================================================\n";
    std::cout << std::left << std::setw(10) << "Ma NV" 
              << std::setw(22) << "Ho Ten" 
              << std::setw(14) << "Ngay Sinh" 
              << std::setw(20) << "Dia Chi" 
              << std::setw(12) << "Loai NV" 
              << std::setw(15) << "SL / LCB" 
              << std::setw(15) << "Don Gia / PC" 
              << std::setw(18) << "Thuc Nhan (VND)" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------\n";

    for (const NhanVien* nv : dsNhanVien_) {
        nv->HienThiThongTin();
    }

    std::cout << "========================================================================================================================\n";
    std::cout << "Tong so nhan vien: " << dsNhanVien_.size() 
              << " | Tong quy luong: " << std::fixed << std::setprecision(0) << TinhTongLuong() << " VND\n\n";
}

// 5. Tìm kiếm nhân viên theo Mã NV
NhanVien* QuanLyNhanSu::TimKiemTheoMa(const std::string& maNV) const {
    for (NhanVien* nv : dsNhanVien_) {
        if (nv->getMaNV() == maNV) {
            return nv;
        }
    }
    return nullptr;
}

// Tìm kiếm danh sách nhân viên theo Tên (chứa từ khóa)
std::vector<NhanVien*> QuanLyNhanSu::TimKiemTheoTen(const std::string& hoTen) const {
    std::vector<NhanVien*> ketQua;
    for (NhanVien* nv : dsNhanVien_) {
        if (nv->getHoTen().find(hoTen) != std::string::npos) {
            ketQua.push_back(nv);
        }
    }
    return ketQua;
}

// 6. Xóa nhân viên theo Mã NV (Giải phóng bộ nhớ an toàn)
bool QuanLyNhanSu::XoaNhanVienTheoMa(const std::string& maNV) {
    for (auto it = dsNhanVien_.begin(); it != dsNhanVien_.end(); ++it) {
        if ((*it)->getMaNV() == maNV) {
            delete *it;            // 解放 - Giải phóng vùng nhớ con trỏ
            dsNhanVien_.erase(it); // Xóa phần tử khỏi vector
            return true;
        }
    }
    return false;
}

// 7. Sắp xếp danh sách theo lương giảm dần (Lambda & std::sort)
void QuanLyNhanSu::SapXepLuongGiamDan() {
    std::sort(dsNhanVien_.begin(), dsNhanVien_.end(), [](NhanVien* a, NhanVien* b) {
        return a->TinhLuong() > b->TinhLuong();
    });
}

// 8. Tính tổng quỹ lương của công ty
double QuanLyNhanSu::TinhTongLuong() const {
    double tong = 0.0;
    for (NhanVien* nv : dsNhanVien_) {
        tong += nv->TinhLuong();
    }
    return tong;
}

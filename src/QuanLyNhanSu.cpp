#include "QuanLyNhanSu.h"

// --- Constructor & Destructor ---
QuanLyNhanSu::QuanLyNhanSu() {}

QuanLyNhanSu::~QuanLyNhanSu() {
    GiaiPhongBoNho();
}

// --- Quản lý bộ nhớ con trỏ an toàn (Tránh Memory Leak) ---
void QuanLyNhanSu::GiaiPhongBoNho() {
    for (NhanVien* nv : dsNhanVien_) {
        delete nv; // Giải phóng vùng nhớ Heap đã cấp phát qua 'new'
    }
    dsNhanVien_.clear(); // Xóa các con trỏ rác khỏi vector
}

// Kiểm tra trùng Mã Nhân Viên
bool QuanLyNhanSu::KiemTraTrungMa(const std::string& maNV) const {
    for (const NhanVien* nv : dsNhanVien_) {
        if (nv->getMaNV() == maNV) {
            return true;
        }
    }
    return false;
}

// Thêm con trỏ nhân viên vào vector
void QuanLyNhanSu::ThemNhanVien(NhanVien* nv) {
    if (nv != nullptr) {
        dsNhanVien_.push_back(nv);
    }
}

// --- OPTION 1: Nhập / Thêm mới nhân viên ---
void QuanLyNhanSu::NhapDanhSach() {
    int loai = 0;
    std::cout << "\n================ CHON LOAI NHAN VIEN ================\n";
    std::cout << "1. Nhan vien Van phong\n";
    std::cout << "2. Nhan vien San xuat\n";
    std::cout << "3. Quan ly (Cap cao)\n";
    std::cout << "Chon (1-3): ";
    std::cin >> loai;

    if (loai < 1 || loai > 3) {
        std::cout << "-> Loai nhan vien khong hop le!\n";
        return;
    }

    NhanVien* nv = nullptr;
    if (loai == 1) nv = new NhanVienVanPhong();
    else if (loai == 2) nv = new NhanVienSanXuat();
    else if (loai == 3) nv = new QuanLy();

    // Nhập dữ liệu và kiểm tra bẫy trùng mã
    std::string maTmp;
    while (true) {
        std::cout << "Nhap Ma Nhan Vien: ";
        std::cin >> maTmp;
        if (KiemTraTrungMa(maTmp)) {
            std::cout << "-> Loi: Ma NV '" << maTmp << "' da ton tai! Vui long nhap lai.\n";
        } else {
            nv->setMaNV(maTmp);
            break;
        }
    }

    // Gọi hàm nhập riêng của từng lớp con
    std::cin >> *nv; 
    ThemNhanVien(nv);
    std::cout << "-> Them nhan vien moi thanh cong!\n";
}

// --- OPTION 2: Hiển thị danh sách dạng bảng căn chỉnh ngăn nắp ---
void QuanLyNhanSu::XuatDanhSach() const {
    if (dsNhanVien_.empty()) {
        std::cout << "\n-> Danh sach nhan vien hien dang rong!\n";
        return;
    }

    std::cout << "\n================================================ DANH SACH NHAN VIEN ================================================\n";
    std::cout << std::left 
              << std::setw(10) << "Ma NV"
              << std::setw(22) << "Ho va Ten"
              << std::setw(14) << "Ngay Sinh"
              << std::setw(16) << "Dia Chi"
              << std::setw(20) << "Chuc Vu / Loai"
              << std::setw(18) << "SL / LCB"
              << std::setw(18) << "Don Gia / Phu Cap"
              << std::setw(18) << "Thuc Nhan (VND)" << "\n";
    std::cout << std::string(136, '-') << "\n";

    for (const NhanVien* nv : dsNhanVien_) {
        std::cout << *nv << "\n"; // Quá tải toán tử << gọi hàm xuất đa hình
    }

    std::cout << std::string(136, '=') << "\n";
    std::cout << "-> Tong so nhan vien: " << dsNhanVien_.size() << " nguoi.\n";
    std::cout << "-> Tong quy luong phai tra: " << std::fixed << std::setprecision(0) << TinhTongLuong() << " VND\n";
}

// --- OPTION 3: Tìm kiếm nhân viên ---
NhanVien* QuanLyNhanSu::TimKiemTheoMa(const std::string& maNV) const {
    for (NhanVien* nv : dsNhanVien_) {
        if (nv->getMaNV() == maNV) {
            return nv;
        }
    }
    return nullptr;
}

std::vector<NhanVien*> QuanLyNhanSu::TimKiemTheoTen(const std::string& ten) const {
    std::vector<NhanVien*> ketQua;
    for (NhanVien* nv : dsNhanVien_) {
        if (nv->getHoTen().find(ten) != std::string::npos) {
            ketQua.push_back(nv);
        }
    }
    return ketQua;
}

void QuanLyNhanSu::TimKiemMenu() const {
    if (dsNhanVien_.empty()) {
        std::cout << "\n-> Danh sach rong, khong the tim kiem!\n";
        return;
    }

    int chon = 0;
    std::cout << "\n1. Tim kiem chinh xac theo Ma NV\n";
    std::cout << "2. Tim kiem theo Tu khoa Ten\n";
    std::cout << "Chon (1-2): ";
    std::cin >> chon;

    if (chon == 1) {
        std::string maNV;
        std::cout << "Nhap Ma NV can tim: ";
        std::cin >> maNV;
        NhanVien* nv = TimKiemTheoMa(maNV);
        if (nv != nullptr) {
            std::cout << "\n-> KET QUA TIM KIEM:\n";
            std::cout << *nv << "\n";
        } else {
            std::cout << "-> Khong tim thay nhan vien co ma: " << maNV << "\n";
        }
    } else if (chon == 2) {
        std::string ten;
        std::cout << "Nhap tu khoa Ten can tim: ";
        std::cin.ignore();
        std::getline(std::cin, ten);
        std::vector<NhanVien*> kq = TimKiemTheoTen(ten);
        if (!kq.empty()) {
            std::cout << "\n-> TIM THAY " << kq.size() << " NHAN VIEN PHU HOP:\n";
            for (const NhanVien* nv : kq) {
                std::cout << *nv << "\n";
            }
        } else {
            std::cout << "-> Khong tim thay nhan vien nao chua tu khoa: '" << ten << "'\n";
        }
    }
}

// --- OPTION 4: Xóa nhân viên theo Mã ---
bool QuanLyNhanSu::XoaNhanVienTheoMa(const std::string& maNV) {
    for (auto it = dsNhanVien_.begin(); it != dsNhanVien_.end(); ++it) {
        if ((*it)->getMaNV() == maNV) {
            delete *it;            // Giải phóng vùng nhớ Heap
            dsNhanVien_.erase(it); // Xóa con trỏ ra khỏi vector
            return true;
        }
    }
    return false;
}

// --- OPTION 5: Sắp xếp lương giảm dần (Sử dụng std::sort và biểu thức Lambda) ---
void QuanLyNhanSu::SapXepLuongGiamDan() {
    if (dsNhanVien_.empty()) {
        std::cout << "\n-> Danh sach rong, khong can sap xep!\n";
        return;
    }

    std::sort(dsNhanVien_.begin(), dsNhanVien_.end(), [](const NhanVien* a, const NhanVien* b) {
        return a->TinhLuong() > b->TinhLuong(); // Đa hình gọi TinhLuong()
    });

    std::cout << "\n-> Da sap xep danh sach theo thuc nhan luong GIAM DAN thanh cong!\n";
}

// --- OPTION 6: Thống kê tổng quỹ lương ---
double QuanLyNhanSu::TinhTongLuong() const {
    double tong = 0;
    for (const NhanVien* nv : dsNhanVien_) {
        tong += nv->TinhLuong(); // Lời gọi đa hình tính lương
    }
    return tong;
}

void QuanLyNhanSu::ThongKeQuyLuong() const {
    std::cout << "\n================ THONG KE QUY LUONG ================\n";
    std::cout << "Tong so luong nhan vien : " << dsNhanVien_.size() << " nguoi.\n";
    std::cout << "Tong quy luong phai chi  : " << std::fixed << std::setprecision(0) << TinhTongLuong() << " VND\n";
    std::cout << "====================================================\n";
}

// --- OPTION 7: Nạp dữ liệu mẫu (Khởi tạo sẵn 5 nhân viên thuộc đủ 3 loại) ---
void QuanLyNhanSu::NapDuLieuMau() {
    // Dọn dẹp dữ liệu cũ nếu có
    GiaiPhongBoNho();

    // Khởi tạo các đối tượng mẫu bằng Constructor có tham số
    ThemNhanVien(new NhanVienVanPhong("NV01", "Nguyen Van An", "15/03/1992", "Ha Noi", 22, 350000));
    ThemNhanVien(new NhanVienSanXuat("NV02", "Tran Thi Binh", "20/08/1995", "Nam Dinh", 180, 45000));
    ThemNhanVien(new QuanLy("NV03", "Le Hoang Cuong", "10/01/1988", "Da Nang", 18000000, 5000000));
    ThemNhanVien(new NhanVienVanPhong("NV04", "Pham Minh Dung", "05/11/1998", "Hai Phong", 20, 320000));
    ThemNhanVien(new NhanVienSanXuat("NV05", "Vo Thi Giang", "12/07/1996", "Can Tho", 210, 48000));

    std::cout << "\n-> Nap thanh cong 5 nhan vien mau (du 3 loai nhan vien) vao he thong!\n";
}

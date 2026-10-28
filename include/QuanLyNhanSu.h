#include "QuanLyNhanSu.h"

QuanLyNhanSu::QuanLyNhanSu() {}

QuanLyNhanSu::~QuanLyNhanSu() {
    GiaiPhongBoNho();
}

void QuanLyNhanSu::GiaiPhongBoNho() {
    for (NhanVien* nv : dsNhanVien_) {
        delete nv;
    }
    dsNhanVien_.clear();
}

void QuanLyNhanSu::ThemNhanVien(NhanVien* nv) {
    if (nv != nullptr) {
        dsNhanVien_.push_back(nv);
    }
}

bool QuanLyNhanSu::KiemTraTrungMa(const std::string& maNV) const {
    for (const NhanVien* nv : dsNhanVien_) {
        if (nv->getMaNV() == maNV) return true;
    }
    return false;
}

void QuanLyNhanSu::NhapDanhSach() {
    int loai = 0;
    std::cout << "\n================ CHON LOAI NHAN VIEN ================\n";
    std::cout << "1. Nhan vien Van phong\n";
    std::cout << "2. Nhan vien San xuat\n";
    std::cout << "3. Quan ly (Cap cao)\n";
    std::cout << "Chon loai (1-3): ";
    std::cin >> loai;

    if (loai < 1 || loai > 3) {
        std::cout << "-> Loai nhan vien khong hop le!\n";
        return;
    }

    NhanVien* nv = nullptr;
    if (loai == 1) nv = new NhanVienVanPhong();
    else if (loai == 2) nv = new NhanVienSanXuat();
    else if (loai == 3) nv = new QuanLy();

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

    std::cin >> *nv; 
    ThemNhanVien(nv);
    std::cout << "-> Them nhan vien moi thanh cong!\n";
}

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
              << std::setw(18) << "So Luong / Cong"
              << std::setw(18) << "Ghi Chu / KPI"
              << std::setw(18) << "Thuc Nhan (VND)" << "\n";
    std::cout << std::string(136, '-') << "\n";

    for (const NhanVien* nv : dsNhanVien_) {
        std::cout << *nv << "\n";
    }

    std::cout << std::string(136, '=') << "\n";
    std::cout << "-> Tong so nhan vien: " << dsNhanVien_.size() << " nguoi.\n";
    std::cout << "-> Tong quy luong phai tra: " << std::fixed << std::setprecision(0) << TinhTongLuong() << " VND\n";
}

NhanVien* QuanLyNhanSu::TimKiemTheoMa(const std::string& maNV) const {
    for (NhanVien* nv : dsNhanVien_) {
        if (nv->getMaNV() == maNV) return nv;
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
            std::cout << "-> Khong tim thay nhan vien nào chua tu khoa: '" << ten << "'\n";
        }
    }
}

bool QuanLyNhanSu::XoaNhanVienTheoMa(const std::string& maNV) {
    for (auto it = dsNhanVien_.begin(); it != dsNhanVien_.end(); ++it) {
        if ((*it)->getMaNV() == maNV) {
            delete *it;
            dsNhanVien_.erase(it);
            return true;
        }
    }
    return false;
}

void QuanLyNhanSu::SapXepMenu() {
    if (dsNhanVien_.empty()) {
        std::cout << "\n-> Danh sach rong, khong the sap xep!\n";
        return;
    }

    int chon = 0;
    std::cout << "\n================ CHON TIEU CHI SAP XEP ================\n";
    std::cout << "1. Luong Thuc Nhan GIAM DAN (Mac dinh)\n";
    std::cout << "2. Luong Thuc Nhan TANG DAN\n";
    std::cout << "3. Ma Nhan Vien (A -> Z)\n";
    std::cout << "4. Ho va Ten (A -> Z)\n";
    std::cout << "Chon tieu chi (1-4): ";
    std::cin >> chon;

    switch (chon) {
        case 1:
            std::sort(dsNhanVien_.begin(), dsNhanVien_.end(), [](const NhanVien* a, const NhanVien* b) {
                return a->TinhLuong() > b->TinhLuong();
            });
            std::cout << "-> Da sap xep danh sach theo Luong Thuc Nhan GIAM DAN!\n";
            break;
        case 2:
            std::sort(dsNhanVien_.begin(), dsNhanVien_.end(), [](const NhanVien* a, const NhanVien* b) {
                return a->TinhLuong() < b->TinhLuong();
            });
            std::cout << "-> Da sap xep danh sach theo Luong Thuc Nhan TANG DAN!\n";
            break;
        case 3:
            std::sort(dsNhanVien_.begin(), dsNhanVien_.end(), [](const NhanVien* a, const NhanVien* b) {
                return a->getMaNV() < b->getMaNV();
            });
            std::cout << "-> Da sap xep danh sach theo Ma NV (A -> Z)!\n";
            break;
        case 4:
            std::sort(dsNhanVien_.begin(), dsNhanVien_.end(), [](const NhanVien* a, const NhanVien* b) {
                return a->getHoTen() < b->getHoTen();
            });
            std::cout << "-> Da sap xep danh sach theo Ho va Ten (A -> Z)!\n";
            break;
        default:
            std::cout << "-> Lua chon khong hop le!\n";
            return;
    }

    XuatDanhSach();
}

double QuanLyNhanSu::TinhTongLuong() const {
    double tong = 0;
    for (const NhanVien* nv : dsNhanVien_) {
        tong += nv->TinhLuong();
    }
    return tong;
}

void QuanLyNhanSu::ThongKeQuyLuong() const {
    std::cout << "\n================ THONG KE QUY LUONG ================\n";
    std::cout << "Tong so luong nhan vien : " << dsNhanVien_.size() << " nguoi.\n";
    std::cout << "Tong quy luong phai chi  : " << std::fixed << std::setprecision(0) << TinhTongLuong() << " VND\n";
    std::cout << "====================================================\n";
}

void QuanLyNhanSu::NapDuLieuMau() {
    GiaiPhongBoNho(); // Dọn sạch dữ liệu cũ

    // Nạp dữ liệu mẫu phù hợp với Constructor mới
    ThemNhanVien(new NhanVienVanPhong("NV01", "Nguyen Van An", "15/03/1992", "Ha Noi", 22, 350000, 10));
    ThemNhanVien(new NhanVienSanXuat("NV02", "Tran Thi Binh", "20/08/1995", "Nam Dinh", 115, 45000));
    ThemNhanVien(new QuanLy("NV03", "Le Hoang Cuong", "10/01/1988", "Da Nang", 15000000, 1.5, 3000000));
    ThemNhanVien(new NhanVienVanPhong("NV04", "Pham Minh Dung", "05/11/1998", "Hai Phong", 17, 320000, 0));
    ThemNhanVien(new NhanVienSanXuat("NV05", "Vo Thi Giang", "12/07/1996", "Can Tho", 75, 48000));

    std::cout << "\n-> Nap thanh cong 5 nhan vien mau (du 3 loai) vao he thong!\n";
}

bool QuanLyNhanSu::CapNhatThongTin(const std::string& maNV) {
    NhanVien* nv = TimKiemTheoMa(maNV);
    if (nv == nullptr) return false;

    std::cout << "\n-> NHAN VIEN DUOC CHON DE CAP NHAT:\n";
    std::cout << *nv << "\n";
    std::cout << "--------------------------------------------------------\n";
    std::cout << "Luu y: Ma NV '" << maNV << "' duoc giu nguyen lam dinh danh.\n";

    std::string maCu = nv->getMaNV();
    std::cin >> *nv;
    nv->setMaNV(maCu);

    return true;
}

void QuanLyNhanSu::CapNhatMenu() {
    if (dsNhanVien_.empty()) {
        std::cout << "\n-> Danh sach rong, khong the cap nhat!\n";
        return;
    }

    std::string maNV;
    std::cout << "\n================ CAP NHAT THONG TIN NHAN VIEN ================\n";
    std::cout << "Nhap Ma NV can cap nhat: ";
    std::cin >> maNV;

    if (CapNhatThongTin(maNV)) {
        std::cout << "-> Cap nhat thong tin nhan vien co ma '" << maNV << "' THANH CONG!\n";
        XuatDanhSach();
    } else {
        std::cout << "-> Loi: Khong tim thay nhan vien co ma '" << maNV << "' trong he thong!\n";
    }
}

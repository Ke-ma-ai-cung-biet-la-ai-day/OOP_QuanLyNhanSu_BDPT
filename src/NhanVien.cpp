#include "NhanVien.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>

namespace MauSacNhanVien {
    const std::string RESET = "\033[0m";
    const std::string XANH_LA_SANG = "\033[38;5;120m";
    const std::string CAM = "\033[38;5;208m";
    const std::string VANG = "\033[33m";
    const std::string TIM_NHAT = "\033[38;5;141m";
    const std::string XANH_NGOC = "\033[38;5;44m";
    const std::string TRANG = "\033[37m";
    const std::string DO = "\033[31m";
    const std::string DAM = "\033[1m";
}

namespace {
    // 1. Chuan hoa khoang trang: Xoa space dau/cuoi va gom nhieu space giua thanh 1 space
    std::string chuanHoaKhoangTrang(const std::string& s) {
        std::string ketQua = "";
        std::stringstream ss(s);
        std::string tu;
        while (ss >> tu) {
            if (!ketQua.empty()) ketQua += " ";
            ketQua += tu;
        }
        return ketQua;
    }

    // 2. Chuan hoa viet hoa chu cai dau moi tu (Title Case) cho Ho va Ten
    std::string vietHoaDauTu(const std::string& s) {
        std::string chuan = chuanHoaKhoangTrang(s);
        bool vietHoa = true;
        for (char& c : chuan) {
            if (std::isspace(static_cast<unsigned char>(c))) {
                vietHoa = true;
            }
            else if (vietHoa) {
                c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
                vietHoa = false;
            }
            else {
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            }
        }
        return chuan;
    }

    bool kiemTraTenHopLe(const std::string& s) {
        std::string daChuanHoa = chuanHoaKhoangTrang(s);
        if (daChuanHoa.empty()) return false;
        for (char c : daChuanHoa) {
            if (std::isdigit(static_cast<unsigned char>(c))) return false;
        }
        return true;
    }

    bool kiemTraNgaySinhHopLe(const std::string& s) {
        if (s.length() != 10) return false;
        if (s[2] != '/' || s[5] != '/') return false;
        for (int i = 0; i < 10; ++i) {
            if (i == 2 || i == 5) continue;
            if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
        }
        int d = std::stoi(s.substr(0, 2));
        int m = std::stoi(s.substr(3, 2));
        int y = std::stoi(s.substr(6, 4));

        if (m < 1 || m > 12) return false;
        if (d < 1 || d > 31) return false;
        if (y < 1960 || y > 2008) return false;
        return true;
    }
}

NhanVien::NhanVien() : maNhanVien_(""), hoTen_(""), ngaySinh_(""), diaChi_("") {}
NhanVien::NhanVien(const std::string& ma, const std::string& ten, const std::string& ns, const std::string& dc)
    : maNhanVien_(ma), hoTen_(ten), ngaySinh_(ns), diaChi_(dc) {
}
NhanVien::~NhanVien() {}

const std::string& NhanVien::getMaNhanVien() const { return maNhanVien_; }
void NhanVien::setMaNhanVien(const std::string& ma) { maNhanVien_ = ma; }
const std::string& NhanVien::getHoTen() const { return hoTen_; }
void NhanVien::setHoTen(const std::string& ten) { hoTen_ = ten; }
const std::string& NhanVien::getNgaySinh() const { return ngaySinh_; }
void NhanVien::setNgaySinh(const std::string& ns) { ngaySinh_ = ns; }
const std::string& NhanVien::getDiaChi() const { return diaChi_; }
void NhanVien::setDiaChi(const std::string& dc) { diaChi_ = dc; }

std::string NhanVien::dinhDangTien(double soTien) const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(0) << soTien;
    std::string s = oss.str();
    int index = (int)s.length() - 3;
    while (index > 0) {
        s.insert(index, ",");
        index -= 3;
    }
    return s;
}

void NhanVien::nhap(std::istream& in) {
    const int CHIEU_RONG_KHUNG = 66;
    const int LE_CAN_GIUA = (142 - CHIEU_RONG_KHUNG) / 2; // 38 khoảng trắng
    const int KHOANG_TRONG = CHIEU_RONG_KHUNG - 4;        // 62 ký tự lòng khung
    const std::string pad(LE_CAN_GIUA, ' ');

    std::cout << "\n" << pad << MauSacNhanVien::CAM
        << "++" << std::string(KHOANG_TRONG, '=') << "++\n"
        << MauSacNhanVien::RESET;

    std::string tieuDe = "THONG TIN NHAN VIEN";
    int leTieuDeTrai = (KHOANG_TRONG - (int)tieuDe.length()) / 2;
    int leTieuDePhai = KHOANG_TRONG - (int)tieuDe.length() - leTieuDeTrai;

    std::cout << pad
        << MauSacNhanVien::CAM << "||" << MauSacNhanVien::RESET
        << std::string(leTieuDeTrai, ' ')
        << MauSacNhanVien::CAM << MauSacNhanVien::DAM << tieuDe << MauSacNhanVien::RESET
        << std::string(leTieuDePhai, ' ')
        << MauSacNhanVien::CAM << "||" << MauSacNhanVien::RESET << "\n";

    std::cout << pad
        << MauSacNhanVien::CAM
        << "||" << std::string(KHOANG_TRONG, '-') << "||\n"
        << MauSacNhanVien::RESET;

    auto inVaDocChuoi = [&](const std::string& mau, const std::string& nhan, std::string& giaTri,
        bool (*kiemTraHopLe)(const std::string&), const std::string& thongBaoLoi, bool laHoTen, bool laDiaChi) {
            bool coLoi = false;

            while (true) {
                std::cout << pad
                    << MauSacNhanVien::CAM << "||  " << MauSacNhanVien::RESET
                    << mau << std::left << std::setw(26) << nhan
                    << ": " << MauSacNhanVien::RESET;

                std::getline(in >> std::ws, giaTri);

                // Chuẩn hóa chuỗi tự động: thu gọn khoảng cách thừa và viết hoa chữ cái đầu cho cả Họ tên & Địa chỉ
                if (laHoTen || laDiaChi) {
                    giaTri = vietHoaDauTu(giaTri);
                }

                // Nếu dữ liệu hợp lệ
                if (kiemTraHopLe == nullptr || kiemTraHopLe(giaTri)) {
                    if (coLoi) {
                        // Nếu trước đó có dòng lỗi: lùi 2 dòng (dòng vừa gõ + dòng lỗi đỏ) và xóa sạch
                        std::cout << "\033[1A\033[2K\r";
                        std::cout << "\033[1A\033[2K\r";
                    }
                    else {
                        // Nếu gõ đúng ngay từ đầu: chỉ cần lùi lên dòng vừa gõ
                        std::cout << "\033[1A\033[2K\r";
                    }

                    // In đè lại dòng chuẩn xác có đóng viền || khép kín
                    int doDaiDuLieu = static_cast<int>(giaTri.length());
                    int khoangDemPhai = 32 - doDaiDuLieu;
                    if (khoangDemPhai < 0) khoangDemPhai = 0;

                    std::cout << pad
                        << MauSacNhanVien::CAM << "||  " << MauSacNhanVien::RESET
                        << mau << std::left << std::setw(26) << nhan
                        << ": " << MauSacNhanVien::RESET
                        << MauSacNhanVien::TRANG << giaTri << MauSacNhanVien::RESET
                        << std::string(khoangDemPhai, ' ')
                        << MauSacNhanVien::CAM << "||\n" << MauSacNhanVien::RESET;
                    break;
                }

                // Nếu nhập sai:
                if (coLoi) {
                    std::cout << "\033[1A\033[2K\r";
                    std::cout << "\033[1A\033[2K\r";
                }
                else {
                    std::cout << "\033[1A\033[2K\r";
                }

                std::cout << pad << "    " << MauSacNhanVien::DO << ">> " << thongBaoLoi << MauSacNhanVien::RESET << "\n";
                coLoi = true;
            }
        };

    inVaDocChuoi(MauSacNhanVien::XANH_LA_SANG, "Ma nhan vien", maNhanVien_, nullptr, "", false, false);
    inVaDocChuoi(MauSacNhanVien::VANG, "Ho va ten", hoTen_, kiemTraTenHopLe, "Ten khong duoc chua so/de trong!", true, false);
    inVaDocChuoi(MauSacNhanVien::TIM_NHAT, "Ngay sinh (dd/mm/yyyy)", ngaySinh_, kiemTraNgaySinhHopLe, "Dinh dang dd/mm/yyyy (18-65 tuoi)!", false, false);
    // Nhập địa chỉ: tự động nhận diện nhiều khoảng trắng và viết hoa chữ cái đầu mỗi từ
    inVaDocChuoi(MauSacNhanVien::XANH_NGOC, "Dia chi", diaChi_, [](const std::string& s) { return !chuanHoaKhoangTrang(s).empty(); }, "Dia chi khong duoc de trong!", false, true);
}

void NhanVien::xuat(std::ostream& out) const {
    out << std::left
        << std::setw(10) << maNhanVien_
        << std::setw(22) << hoTen_
        << std::setw(14) << ngaySinh_
        << std::setw(20) << diaChi_;
}

void NhanVien::hienThiThongTin() const {
    this->xuat(std::cout);
}

std::istream& operator>>(std::istream& in, NhanVien& nv) {
    nv.nhap(in);
    return in;
}

std::ostream& operator<<(std::ostream& out, const NhanVien& nv) {
    nv.xuat(out);
    return out;
}
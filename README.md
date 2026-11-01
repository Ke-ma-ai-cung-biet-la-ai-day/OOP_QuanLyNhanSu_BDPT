# OOP_QuanLyNhanSu_BDPT
Đồ án Lập trình hướng đối tượng - Hệ thống Quản lý nhân sự.

CÂY THƯ MỤC TRONG GITHUB:
```text
OOP_QuanLyNhanSu_BDPT/
│
├── Data
│   └── NhanVien.txt               # File dữ liệu danh sách nhân sự mẫu (tự nạp khi khởi động)
│
├── include                        # File Headers (.h)
│   ├── NhanVien.h                 # Lớp cơ sở trừu tượng NhanVien
│   ├── NhanVienSanXuat.h          # Lớp kế thừa: Nhân viên Sản xuất
│   ├── NhanVienVanPhong.h         # Lớp kế thừa: Nhân viên Văn phòng
│   ├── QuanLy.h                   # Lớp kế thừa: Quản lý
│   └── QuanLyNhanSu.h             # Lớp điều phối hệ thống & giao diện menu
│
├── src                            # File Sources (.cpp)
│   ├── main.cpp                   # Điểm khởi chạy chương trình & vòng lặp Menu chính
│   ├── NhanVien.cpp               # Cài đặt phương thức chung & form nhập cơ bản
│   ├── NhanVienSanXuat.cpp        # Cài đặt tính lương, KPI & form nhập nhân viên sản xuất
│   ├── NhanVienVanPhong.cpp       # Cài đặt tính lương, KPI & form nhập nhân viên văn phòng
│   ├── QuanLy.cpp                 # Cài đặt tính lương & form nhập quản lý
│   └── QuanLyNhanSu.cpp           # Cài đặt 5 chức năng chính & tiện ích bảng/hộp thoại ANSI
│
├── .gitignore                     # Bỏ qua các file rác build Visual Studio (.vs, x64, Debug,...)
├── QuanLyNhanSu.sln               # File Solution của Visual Studio
├── QuanLyNhanSu.vcxproj           # File cấu hình Project C++
├── QuanLyNhanSu.vcxproj.filters   # File lưu cấu trúc nhóm ảo (Header/Source Files)
└── README.md                      # Tài liệu giới thiệu & hướng dẫn cài đặt đồ án
```

HƯỚNG DẪN QUY TRÌNH LÀM VIỆC GITHUB:
1. Lấy toàn bộ code mới nhất về máy: git pull origin main
2. Thực hiện code
3. Biên dịch và kiểm thử thành công
4. Đóng gói và lưu trữ: git status # Xem lại file nào đã sửa git add <đường_dẫn_file> # Đưa file cần lưu vào gói hàng git commit -m "feat: Description" # Đóng dấu lưu vào kho cá nhân
5. Cập nhật lên nhánh main: git pull origin main # Kéo thêm lần nữa đề phòng có ai vừa push git push origin main # Đẩy code lên GitHub

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

QuanLyChuyenBayNoiDia
│
├── data/                               # Cơ sở dữ liệu dạng văn bản và tệp lưu trữ thông tin vé
│   ├── DATA_VE/                        # Thư mục chứa các phiếu thông tin vé riêng lẻ (<MãVé>.txt)
│   ├── Admin.txt                       # Lưu thông tintài khoản và mật khẩu của Quản trị viên
│   ├── MayBay.txt                      # Lưu thông tin số hiệu máy bay và số lượng chỗ ngồi trong máy bay
│   ├── ChuyenBay.txt                   # Lưu thông tin danh sách các chuyến bay nội địa
│   └── KhachHang.txt                   # Lưu thông tin danh sách các khách hàng đã đặt vé thành công                     
│
├── include/                            # Thư mục chứa các tệp tiêu đề khai báo (Header files - .h)
│   ├── MayBay.h                        # Khai báo cấu trúc lớp Máy bay
│   ├── ChuyenBay.h                     # Khai báo cấu trúc lớp Chuyến bay
│   ├── KhachHang.h                     # Khai báo cấu trúc lớp Khách hàng
│   ├── Ve.h                            # Khai báo cấu trúc lớp Vé
│   ├── BST.h                           # Khai báo cấu trúc Cây AVL tự cân bằng (Template)
│   ├── LinkedList.h                    # Khai báo cấu trúc Danh sách liên kết đơn (Template)
│   ├── FileStore.h                     # Khai báo các chức năng đọc/ghi tệp tin và đồng bộ dữ liệu
│   ├── ThongKe.h                       # Khai báo các chức năng tra cứu và hiển thị thông tin thống kê
│   ├── Validation.h                    # Khai báo các chức năng kiểm tra ràng buộc và chuẩn hóa dữ liệu
│   └── UI_Menu.h                       # Khai báo cơ chế tương tác trong giao diện ứng dụng console
│
├── src/                                # Thư mục chứa các tệp cài đặt mã nguồn (.cpp)
│   ├── MayBay.cpp                      # Định nghĩa các phương thức của lớp MayBay
│   ├── ChuyenBay.cpp                   # Định nghĩa các phương thức của lớp ChuyenBay
│   ├── KhachHang.cpp                   # Định nghĩa các phương thức của lớp KhachHang
│   ├── Ve.cpp                          # Định nghĩa các phương thức của lớp Ve
│   ├── FileStore.cpp                   # Cài đặt chức năng đọc/ghi tệp tin và đồng bộ dữ liệu
│   ├── ThongKe.cpp                     # Cài đặt chức năng tra cứu và hiển thị thông tin thống kê
│   ├── Validation.cpp                  # Cài đặt chức năng kiểm tra ràng buộc và chuẩn hóa dữ liệu
│   ├── UI_Menu.cpp                     # Cài đặt cơ chế tương tác trong giao diện ứng dụng console
│   └── main.cpp                        # Điểm khởi chạy và điều phối luồng hoạt động chính của chương trình
│                            
└── README.md                           # Giới thiệu chương trình hệ thống và hướng dẫn biên dịch, cài đặt

HƯỚNG DẪN QUY TRÌNH LÀM VIỆC GITHUB:
1. Lấy toàn bộ code mới nhất về máy: git pull origin main
2. Thực hiện code
3. Biên dịch và kiểm thử thành công
4. Đóng gói và lưu trữ: git status # Xem lại file nào đã sửa git add <đường_dẫn_file> # Đưa file cần lưu vào gói hàng git commit -m "feat: Description" # Đóng dấu lưu vào kho cá nhân
5. Cập nhật lên nhánh main: git pull origin main # Kéo thêm lần nữa đề phòng có ai vừa push git push origin main # Đẩy code lên GitHub

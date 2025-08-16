# Hệ Thống Quản Lý Thư Viện (LMS) - C++20

## Mô tả
Hệ thống quản lý thư viện được viết bằng C++20, sử dụng CMake để build trên cả Windows và Linux. Hệ thống hỗ trợ hai loại người dùng: Thủ thư và Độc giả, mỗi loại có các chức năng riêng biệt.

## Tính năng chính

### Chức năng chung
- **List**: Xem danh sách sách, người dùng
- **Search**: Tìm kiếm sách theo nhiều tiêu chí
- **View**: Xem thông tin chi tiết
- **Add new**: Thêm mới sách, người dùng
- **Delete**: Xóa sách, người dùng

### Chức năng Thủ thư
- Quản lý sách (thêm, sửa, xóa, tìm kiếm)
- Quản lý độc giả
- Tạo báo cáo thống kê
- Xem thống kê thư viện

### Chức năng Độc giả
- Mượn và trả sách
- Xem lịch sử mượn sách
- Tìm kiếm sách
- Xem sách có sẵn
- Cập nhật thông tin cá nhân

## Cấu trúc dự án

```
thuvien/
├── CMakeLists.txt          # File cấu hình CMake
├── include/                # Thư mục chứa header files
│   ├── User.h             # Class User cơ bản
│   ├── Librarian.h        # Class Thủ thư
│   ├── Reader.h           # Class Độc giả
│   ├── Book.h             # Class Sách
│   ├── Library.h          # Class Thư viện chính
│   ├── FileManager.h      # Class quản lý file
│   ├── Menu.h             # Class giao diện menu
│   └── Utils.h            # Class tiện ích
├── src/                   # Thư mục chứa source files
│   ├── main.cpp           # File main chính
│   ├── User.cpp           # Implementation User
│   ├── Librarian.cpp      # Implementation Thủ thư
│   ├── Reader.cpp         # Implementation Độc giả
│   ├── Book.cpp           # Implementation Sách
│   ├── Library.cpp        # Implementation Thư viện
│   ├── FileManager.cpp    # Implementation quản lý file
│   ├── Menu.cpp           # Implementation menu
│   └── Utils.cpp          # Implementation tiện ích
├── data/                  # Thư mục chứa dữ liệu
│   ├── books.txt          # Dữ liệu sách
│   ├── librarians.txt     # Dữ liệu thủ thư
│   └── readers.txt        # Dữ liệu độc giả
└── README.md              # File hướng dẫn này
```

## Yêu cầu hệ thống

### Windows
- Visual Studio 2019/2022 hoặc MinGW-w64
- CMake 3.16 trở lên
- C++20 compiler

### Linux
- GCC 10+ hoặc Clang 10+
- CMake 3.16 trở lên
- C++20 compiler

## Cách build và chạy

### Windows

#### Sử dụng Visual Studio
```bash
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release
```

#### Sử dụng MinGW
```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

### Linux
```bash
mkdir build
cd build
cmake ..
make
```

### Chạy chương trình
```bash
# Windows
.\bin\LibraryManagementSystem.exe

# Linux
./bin/LibraryManagementSystem
```

## Tài khoản mặc định

- **Username**: admin
- **Password**: admin123
- **Loại**: Thủ thư

## Cách sử dụng

### 1. Đăng nhập
- Chọn "1. Dang nhap" từ menu chính
- Nhập username và password
- Hệ thống sẽ hiển thị menu tương ứng với loại tài khoản

### 2. Menu Thủ thư
- **Thêm sách mới**: Nhập thông tin sách chi tiết
- **Xóa sách**: Nhập ID sách cần xóa
- **Cập nhật sách**: Sửa thông tin sách
- **Danh sách sách**: Xem tất cả sách trong thư viện
- **Tìm kiếm sách**: Tìm sách theo từ khóa
- **Quản lý độc giả**: Xem danh sách độc giả
- **Tạo báo cáo**: Xem báo cáo tổng quan
- **Xem thống kê**: Thống kê chi tiết

### 3. Menu Độc giả
- **Mượn sách**: Nhập ID sách cần mượn
- **Trả sách**: Nhập ID sách cần trả
- **Lịch sử mượn**: Xem sách đã mượn
- **Tìm kiếm sách**: Tìm sách theo từ khóa
- **Sách có sẵn**: Xem sách có thể mượn
- **Cập nhật thông tin**: Sửa thông tin cá nhân

### 4. Lưu và thoát
- Chọn "Thoat" từ menu
- Xác nhận lưu dữ liệu
- Dữ liệu sẽ được lưu vào các file .txt trong thư mục data/

## Cấu trúc dữ liệu

### Format file sách (books.txt)
```
ID|Tieu de|Tac gia|ISBN|Nha xuat ban|Nam xuat ban|The loai|Trang thai|Vi tri|Tong ban sao|Ban sao co san|Mo ta|Thoi gian cap nhat
```

### Format file thủ thư (librarians.txt)
```
Username|Password|Ho ten|Email|Loai nguoi dung|Employee ID|Phong ban
```

### Format file độc giả (readers.txt)
```
Username|Password|Ho ten|Email|Loai nguoi dung|Reader ID|So sach toi da|Trang thai|Lich su muon sach
```



## Tính năng kỹ thuật

- **C++20**: Sử dụng các tính năng mới của C++20
- **Cross-platform**: Hỗ trợ Windows và Linux
- **CMake**: Hệ thống build hiện đại
- **File I/O**: Lưu trữ dữ liệu dạng text
- **Memory Management**: Sử dụng smart pointers
- **Error Handling**: Xử lý lỗi toàn diện
- **Input Validation**: Kiểm tra dữ liệu đầu vào

## Mở rộng

Hệ thống có thể được mở rộng thêm các tính năng:
- Giao diện đồ họa (GUI)
- Cơ sở dữ liệu (SQLite, MySQL)
- Mạng (Client-Server)
- Báo cáo PDF
- Backup tự động
- Quản lý phòng đọc sách

## Liên hệ

Nếu có vấn đề hoặc câu hỏi, vui lòng tạo issue trên repository hoặc liên hệ trực tiếp.

## License

Dự án này được phát hành dưới giấy phép MIT.

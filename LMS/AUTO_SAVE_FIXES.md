# Sửa lỗi không lưu dữ liệu xuống file .txt

## Vấn đề ban đầu
Khi thực hiện các hoạt động như đăng ký, thêm, xóa, sửa, mượn và trả sách, dữ liệu không được lưu xuống file .txt. Dữ liệu chỉ được lưu khi:
1. Khởi tạo thư viện lần đầu
2. Thoát chương trình đúng cách

## Các cải tiến đã thực hiện

### 1. Lưu dữ liệu tự động sau mỗi hoạt động
- **Thêm sách**: Tự động lưu sau khi thêm sách thành công
- **Xóa sách**: Tự động lưu sau khi xóa sách thành công  
- **Cập nhật sách**: Tự động lưu sau khi cập nhật sách thành công
- **Thêm người dùng**: Tự động lưu sau khi thêm người dùng thành công
- **Xóa người dùng**: Tự động lưu sau khi xóa người dùng thành công
- **Mượn sách**: Tự động lưu cả sách và thông tin người dùng
- **Trả sách**: Tự động lưu cả sách và thông tin người dùng
- **Cập nhật profile**: Tự động lưu thông tin người dùng

### 2. Hệ thống Auto Save thông minh
- **Bật/Tắt auto save**: Người dùng có thể bật/tắt tính năng tự động lưu
- **Cài đặt khoảng thời gian**: Có thể thay đổi số thao tác trước khi tự động lưu (mặc định: 5 thao tác)
- **Thông báo rõ ràng**: Hiển thị thông báo khi tự động lưu dữ liệu

### 3. Xử lý thoát chương trình an toàn
- **Signal handler**: Bắt sự kiện Ctrl+C, Ctrl+Break để lưu dữ liệu trước khi thoát
- **Graceful shutdown**: Đảm bảo dữ liệu được lưu ngay cả khi chương trình bị tắt đột ngột

### 4. Menu cài đặt Auto Save
- Thêm tùy chọn "Cài đặt tự động lưu" trong menu thủ thư
- Cho phép:
  - Bật/Tắt auto save
  - Thay đổi số thao tác trước khi lưu
  - Lưu dữ liệu ngay lập tức

## Các file đã được sửa đổi

### 1. `src/Library.cpp`
- Thêm lưu dữ liệu tự động trong các hàm: `addUser()`, `removeUser()`, `addBook()`, `removeBook()`, `updateBook()`, `borrowBook()`, `returnBook()`
- Thêm các hàm auto save: `enableAutoSave()`, `isAutoSaveEnabled()`, `setAutoSaveInterval()`, `getAutoSaveInterval()`, `incrementOperationCount()`
- Thêm biến theo dõi: `autoSaveEnabled`, `autoSaveInterval`, `operationCount`

### 2. `include/Library.h`
- Thêm khai báo các hàm auto save
- Thêm các biến thành viên cho auto save

### 3. `src/Menu.cpp`
- Thêm lưu dữ liệu trong `updateProfile()` và `updateReader()`
- Thêm menu "Cài đặt tự động lưu" với hàm `configureAutoSave()`
- Cập nhật menu thủ thư để bao gồm tùy chọn auto save

### 4. `include/Menu.h`
- Thêm khai báo hàm `configureAutoSave()`

### 5. `src/main.cpp`
- Thêm signal handler để xử lý thoát chương trình an toàn
- Thêm biến global để truy cập thư viện từ signal handler

## Cách sử dụng

### 1. Auto Save mặc định
- Auto save được bật mặc định
- Lưu dữ liệu sau mỗi 5 thao tác
- Hiển thị thông báo "[AUTO-SAVE] Đang lưu dữ liệu..." khi tự động lưu

### 2. Cài đặt Auto Save
1. Đăng nhập với tài khoản thủ thư
2. Chọn "9. Cài đặt tự động lưu"
3. Chọn các tùy chọn:
   - Bật/Tắt auto save
   - Thay đổi số thao tác (1-20)
   - Lưu dữ liệu ngay lập tức

### 3. Thoát an toàn
- Sử dụng "Thoát" từ menu để lưu dữ liệu trước khi thoát
- Hoặc nhấn Ctrl+C để lưu dữ liệu và thoát an toàn

## Lợi ích

1. **Đảm bảo dữ liệu không bị mất**: Dữ liệu được lưu ngay sau mỗi thao tác quan trọng
2. **Tự động hóa**: Không cần nhớ lưu dữ liệu thủ công
3. **Linh hoạt**: Có thể tùy chỉnh cài đặt auto save
4. **An toàn**: Xử lý thoát chương trình đột ngột
5. **Thông báo rõ ràng**: Người dùng biết khi nào dữ liệu được lưu

## Kiểm tra

Để kiểm tra tính năng hoạt động:
1. Thực hiện các thao tác như thêm sách, mượn sách, v.v.
2. Kiểm tra file trong thư mục `data/` để xem dữ liệu được cập nhật
3. Thử thoát chương trình bằng Ctrl+C để kiểm tra signal handler
4. Khởi động lại chương trình để xác nhận dữ liệu được lưu đúng

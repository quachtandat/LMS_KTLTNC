# Cải tiến hệ thống quản lý thư viện

## Các cải tiến đã thực hiện

### 1. **Quản lý mượn trả sách với file .txt**
- **File mới**: `borrow_records.txt` để lưu thông tin mượn trả sách
- **Thông tin lưu trữ**:
  - Record ID (tự động tạo)
  - Username của độc giả
  - Tên sách (thay vì ID)
  - Book ID (để tham chiếu)
  - Ngày mượn, hạn trả, ngày trả
  - Trạng thái đã trả hay chưa

### 2. **Sử dụng tên sách thay vì ID**
- **Mượn sách**: Nhập tên sách thay vì ID
- **Trả sách**: Nhập tên sách thay vì ID
- **Xóa sách**: Nhập tên sách thay vì ID
- **Cập nhật sách**: Nhập tên sách thay vì ID
- **Lịch sử mượn trả**: Hiển thị tên sách thay vì ID

### 3. **Tự động tạo ID**
- **Sách**: Tự động tạo Book ID (BK1001, BK1002, ...)
- **Độc giả**: Tự động tạo Reader ID (RD001, RD002, ...)
- **Borrow Record**: Tự động tạo Record ID (BR000001, BR000002, ...)

### 4. **Cải tiến giao diện người dùng**
- **Thông báo rõ ràng**: Hiển thị tên sách trong các thông báo
- **Lịch sử mượn trả**: Bảng hiển thị đẹp với thông tin đầy đủ
- **Cảnh báo quá hạn**: Hiển thị sách quá hạn và số ngày quá hạn

## Cấu trúc file dữ liệu mới

### `borrow_records.txt`
```
BR000001|username|The Great Gatsby|BK1001|1703123456|0|1704209856|0
BR000002|username|To Kill a Mockingbird|BK1002|1703123456|1703209856|1704209856|1
```

**Format**: `RecordID|Username|BookTitle|BookID|BorrowDate|ReturnDate|DueDate|IsReturned`

## Các hàm mới đã thêm

### Trong `Library` class:
- `findBookByTitle()`: Tìm sách theo tên
- `generateBookId()`: Tạo Book ID tự động
- `generateReaderId()`: Tạo Reader ID tự động
- `addBorrowRecord()`: Thêm record mượn sách
- `updateBorrowRecord()`: Cập nhật record trả sách
- `getBorrowRecordsByUsername()`: Lấy lịch sử mượn trả của user
- `getAllBorrowRecords()`: Lấy tất cả record mượn trả
- `loadBorrowRecords()`: Tải dữ liệu từ file
- `saveBorrowRecords()`: Lưu dữ liệu xuống file

### Trong `FileManager` class:
- `saveBorrowRecordsToFile()`: Lưu borrow records xuống file
- `loadBorrowRecordsFromFile()`: Tải borrow records từ file

### Trong `BorrowRecord` class:
- `getBorrowDateString()`: Lấy ngày mượn dạng string
- `getReturnDateString()`: Lấy ngày trả dạng string
- `getDueDateString()`: Lấy hạn trả dạng string
- `getDaysOverdue()`: Tính số ngày quá hạn
- `isOverdue()`: Kiểm tra có quá hạn không
- `toFileString()`: Chuyển thành string để lưu file
- `fromFileString()`: Tạo từ string trong file

## Cách sử dụng

### 1. **Mượn sách**
1. Đăng nhập với tài khoản độc giả
2. Chọn "1. Muon sach"
3. Nhập **tên sách** (không cần ID)
4. Hệ thống tự động tạo record mượn sách

### 2. **Trả sách**
1. Chọn "2. Tra sach"
2. Nhập **tên sách** (không cần ID)
3. Hệ thống tự động cập nhật record trả sách

### 3. **Xem lịch sử mượn trả**
1. Chọn "3. Xem lich su muon sach"
2. Hiển thị bảng với:
   - Tên sách
   - Ngày mượn
   - Hạn trả
   - Ngày trả
   - Trạng thái
   - Cảnh báo quá hạn

### 4. **Thêm sách mới**
1. Đăng nhập với tài khoản thủ thư
2. Chọn "1. Them sach moi"
3. Hệ thống tự động tạo Book ID
4. Chỉ cần nhập thông tin sách

### 5. **Thêm độc giả mới**
1. Chọn "2. Them doc gia moi"
2. Hệ thống tự động tạo Reader ID
3. Chỉ cần nhập thông tin cá nhân

## Lợi ích

1. **Dễ sử dụng**: Không cần nhớ ID, chỉ cần nhớ tên sách
2. **Tự động hóa**: ID được tạo tự động, không bị trùng
3. **Theo dõi đầy đủ**: Lưu trữ toàn bộ lịch sử mượn trả
4. **Cảnh báo thông minh**: Hiển thị sách quá hạn
5. **Dữ liệu bền vững**: Lưu trữ trong file .txt để dễ quản lý

## Kiểm tra

Để kiểm tra tính năng hoạt động:
1. Thêm sách mới và kiểm tra ID tự động
2. Thêm độc giả mới và kiểm tra ID tự động
3. Mượn sách bằng tên và kiểm tra record được tạo
4. Trả sách và kiểm tra record được cập nhật
5. Xem lịch sử mượn trả
6. Kiểm tra file `borrow_records.txt` trong thư mục `data/`

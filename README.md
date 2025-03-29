# Họ và tên: Lê Bá Sơn
# Mã số sinh viên: 24020294

# 🚀 Space Ship War

Space Ship War được phát triển bằng C++ và SDL2.
Space Ship War là trò chơi được lấy cảm hứng từ tựa game bắn gà nổi đình đám vào thời điểm những năm 2000. Tựa game sử dụng bối cảnh ngoài không gian, người chơi sẽ điều khiển một phi thuyền và tiêu diệt các kẻ địch xuất hiện.

## Điểm số mong muốn: >= 9

## Lý do
- Thời gian em bỏ ra để làm game là tương đối nhiều
- Game của em có đồ họa, âm thanh, hiệu ứng khá mượn mà
- Cách tổ chức và thực hiện của code cũng như logic game rõ ràng, dễ hiểu

## Yêu cầu hệ thống
- Hệ điều hành: Windows
- Trình biên dịch: `g++` (GCC)
- Thư viện: SDL2, SDL2_image, SDL2_mixer, SDL2_ttf

## Cách chơi
1. Biên dịch game bằng:
    build system trên sublime text:
    {
        "shell_cmd": "g++ -I\"F:/SDL2/SDL2-devel-2.30.9-mingw/SDL2-2.30.9/x86_64-w64-mingw32/include/SDL2\" -L\"F:/SDL2/SDL2-devel-2.30.9-mingw/SDL2-2.30.9/x86_64-w64-mingw32/lib\" -o \"${file_path}/game.exe\" \"${file_path}/*.cpp\" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -mconsole && start cmd /k \"${file_path}/game.exe\"",
        "file_regex": "^(...*?):([0-9]*):?([0-9]*)",
        "working_dir": "${file_path}",
        "selector": "source.cpp"
    }
    
2. Chạy game:
   - Mở file ssw.exe

3. Dùng chuột để di chuyển nhân vật

## Video demo game
    - https://drive.google.com/file/d/1iUWZqRWv0uRgaaYOpWgUedF5HtsHJvsZ/view?usp=sharing

## ✨ Tính năng nổi bật
- Đồ họa 2D đơn giản nhưng hấp dẫn
- Âm thanh chân thực
- Điều khiển mượt mà
- Hiệu ứng đặc sắc

## 📂 Cấu trúc thư mục
```
Space-Ship-War/
│-- assets/       # Chứa hình ảnh, âm thanh, dữ liệu
│-- headers/      # Chứa file header (.h)
│-- src/          # Chứa mã nguồn chính
│-- README.md     # File mô tả dự án
```

## Tham khảo
- Nguỗn tài nguyên game:
    - https://ansimuz.itch.io/spaceship-shooter-environment
    - https://foozlecc.itch.io/void-environment-pack
    - https://pixel-by-pixel.itch.io/alcwilliam-space-ship-pack
    - https://fonttiengviet.com/?s=Protest
    - https://tiengdong.com/tieng-sung-laser-ban-trong-phim-khoa-hoc-vien-tuong

## Hỗ trợ từ AI
- Hỗ trợ debug
- Hỗ trợ giải thích công dụng, cách sử dụng của hàm, câu lệnh
- Hỗ trợ hướng dẫn cách sử dụng github, SDL2
- Hỗ trợ cung cấp build system chạy SDL2 trên sublime text
- Hỗ trợ giới thiệu cách tổ chức file
- Hỗ trợ xây dựng khung sườn chương trình
- Hỗ trợ tăng tốc game

## Phần mềm sử dụng
- Sublime text 3
- Gimp
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

### Yêu cầu hệ thống
- Hệ điều hành: Windows / Linux / macOS
- Trình biên dịch: `g++` (GCC)
- Thư viện: SDL2, SDL2_image, SDL2_mixer, SDL2_ttf

### Cài đặt SDL2 trên Ubuntu
```sh
sudo apt update
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

## 🎮 Cách chơi
1. Biên dịch game bằng:
    build system trên sublime text:
    {
        "shell_cmd": "gnome-terminal -- bash -c 'g++ *.cpp -o game `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_mixer -lSDL2_ttf && ./game; read -p \"Press enter to exit...\"'",
        "working_dir": "$file_path",
        "selector": "source.c, source.cpp",
        "file_regex": "^(.*?):([0-9]*):?([0-9]*)?"
    }
    
2. Chạy game:
   game.exe
3. Dùng chuột để di chuyển nhân vật

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

## Hỗ trợ từ AI
- Hỗ trợ debug
- Hỗ trợ giải thích công dụngAI, cách sử dụng của hàm, câu lệnh
- Hỗ trợ hướng dẫn cách sử dụng github, SDL2
- Hỗ trợ cung cấp build system chạy SDL2 trên sublime text
- Hỗ trợ giới thiệu cách tổ chức file
- Hỗ trợ xây dựng khung sườn chương trình và readme
- Hỗ trợ tăng tốc game
## Phần mềm sử dụng
- Sublime text 3
- Gimp


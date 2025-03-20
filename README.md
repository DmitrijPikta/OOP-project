# Test of v1.0 version

### System parametrs:

CPU - Intel Core i5-12450H

RAM - 16 GB DDR4

M.2 512GB Nvme PCIe 4.0 Write - 5000 MB/s, Read - 6900 MB/s

![Screenshot 2025-03-19 123407](https://github.com/user-attachments/assets/dbd25244-b349-4a36-b400-0b4aa7cd6018)

Result: the program works fastest with a vector container

### Test of vertions for dividing with vector, list and deque container

![Screenshot 2025-03-20 233835](https://github.com/user-attachments/assets/1fbd8f18-2c28-4301-8844-017dbda6e889)
### Test of vertions for dividing with vector container

![Screenshot 2025-03-20 232457](https://github.com/user-attachments/assets/c04c5a3d-98b6-4354-8a0d-0aa9b204ef6f) 
1 version

![Screenshot 2025-03-20 232618](https://github.com/user-attachments/assets/afdfedb3-d655-4fb4-94d5-ce7c2a9da1e6)
2 version

![Screenshot 2025-03-20 232755](https://github.com/user-attachments/assets/c1b904c9-14e0-4a87-b337-adfe698a921f)
3 version


Result: the first version of dividing is the fastest, the third is the slowest. But first vertion uses the most memory.


# Instructions for working with project:

1. Download v1.0 release.
2. Instal C++ compiliator that supports at least C++20.
3. Instal cmake at least 3.31.6 version.
4. Open project folder in command prompt.
5. In project folder you see 3 folders for different containers (Vector, List, Deque). Choose with which container you want to work and open it's folder in command prompt.
6. Enter: mkdir build
7. Enter: cd build
8. Enter: cmake ..
9. Enter: cmake --build . --config Release
10. Enter: cd Release
11. Enter: OOP-project

After completing these steps, the project's executable file will start running


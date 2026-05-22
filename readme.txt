Student Grade Management System - Compilation & Execution Guide

Author : Bilal Mohammed Ghani
ID : 2526402447
Group : Computer Science A

How to Compile & Run : (Using CodeBlocks IDE)
1. Launch CodeBlocks and go to File - Open - then select the file (name main.cpp).
2. Click the "Build and Run" icon on the top toolbar (or press F9).

NB: If you're using an older version of the CodeBlocks IDE; Ensure C++11 is enabled:
1. Go to Settings - Compiler...
2. Check the box for "Have g++ follow the C++11 ISO C++ language standard".
Do this because of the the presence of std::stoi () that safely parse the student ID 
(where I used it)  

Known Limitations
1. Volatile Memory : Data is stored in RAM and resets when the application exits.
2. Static Capacity : Maximum student registry is capped at a fixed limit of 30.

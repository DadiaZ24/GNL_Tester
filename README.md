
# **Get Next Line (GNL) Tester**

This repository contains a **C program** designed to **automatically test your implementation of the `get_next_line()` function**. It provides a comprehensive testing suite to ensure your `get_next_line` works as expected under various conditions, with memory leak checks and detailed error reporting.

## **Features**
- Test your `get_next_line()` function with different **buffer sizes**.
- Automatically checks for **memory leaks** using **Valgrind**.
- Prints detailed test results, including any discrepancies between your program's output and the expected output.
- The final message will notify you if the tests have passed or if there are errors in your implementation.

### **Tested Scenarios**
- **Empty files**
- **Single-line files**
- **Long-line files**
- **Multi-line files**
- **Files with no final newline**

Additionally, it runs tests for:
- Different **buffer sizes** (e.g., 1, 2, 16, 32, 128, 1024, 4096, 16384).
- **Memory leaks** via Valgrind.
- **Compilation errors** and checks for expected behavior under each buffer size.

## **Prerequisites**
- **gcc** (GNU Compiler Collection) for compiling C code.
- **Valgrind** for memory leak checking (optional but recommended).

### **Install Valgrind** (if needed)
On **Ubuntu/Debian**:
```bash
sudo apt-get install valgrind
```

On **macOS** (using Homebrew):
```bash
brew install valgrind
```

## **Setup**
1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/gnl-tester.git
   cd gnl-tester
   ```

2. Make sure your `get_next_line.c` and `get_next_line_utils.c` files are in the parent directory or adjust the paths in the script to match the location of your source files.

3. Compile the tester:
   ```bash
   gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c tester.c -o gnl_test
   ```

## **Usage**

### Run the Tests
The script will automatically compile the necessary files, run the tests for each buffer size, and check for any errors or memory leaks. Run the tester script with the following command:

```bash
./run.sh
```

### Example Output
If all tests pass, you'll see:
```bash
You have passed all the tests! May the force be with you
```

If there are errors or memory leaks, you'll see:
```bash
Your GNL has errors! Do not join the dark side, you don't need it!
```

## **Buffer Sizes**
The script tests your implementation using a variety of **buffer sizes**, including some edge cases:
- **1, 2, 16, 32, 128, 1024, 4096, 16384**

## **How the Tests Work**
For each buffer size:
1. The script compiles the source code with the specified `BUFFER_SIZE`.
2. It runs a series of tests, checking various input files (including empty, one-line, multi-line files, and files with no final newline).
3. It compares the output of your `get_next_line()` function against expected output.
4. It runs **Valgrind** to check for memory leaks.
5. The script prints the results and, at the end, shows a message about the overall status of your tests.

## **Final Message**
- If no errors or memory leaks are detected and all tests pass, you will see:  
  `"You have passed all the tests! May the force be with you"`
  
- If there are errors or memory leaks, the final message will be:  
  `"Your GNL has errors! Do not join the dark side, you don't need it!"`

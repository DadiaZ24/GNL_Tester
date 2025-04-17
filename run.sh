#!/bin/bash

# Shell colors
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[1;33m"
NC="\033[0m"

BUFFER_SIZES=(1 2 16 32 128 1024 4096 16384)

SRC="../get_next_line.c ../get_next_line_utils.c tester.c"
TEST_FAILED=0 

for BS in "${BUFFER_SIZES[@]}"; do
    echo -e "${YELLOW}🔧 Testing with BUFFER_SIZE=$BS${NC}"

    cc -Wall -Wextra -Werror -D BUFFER_SIZE=$BS $SRC -o gnl_test
    if [ $? -ne 0 ]; then
        echo -e "${RED}❌ Compilation failed for BUFFER_SIZE=$BS${NC}"
        TEST_FAILED=1
        continue
    fi

    echo -e "${GREEN}🚀 Running tests with BUFFER_SIZE=$BS${NC}"
    ./gnl_test
    TEST_RESULT=$?

    echo -e "${YELLOW}🔍 Running Valgrind (BUFFER_SIZE=$BS)...${NC}"
    valgrind --leak-check=full ./gnl_test > valgrind_output.txt 2>&1
    if grep -q "ERROR SUMMARY: 0 errors from 0 contexts" valgrind_output.txt; then
        echo -e "${GREEN}✅ No leaks detected${NC}"
    else
        echo -e "${RED}⚠️ Memory leaks or errors detected! Please review valgrind_output.txt${NC}"
        TEST_FAILED=1
    fi
    echo -e "------------------------------------------"
done

if [ $TEST_FAILED -eq 0 ]; then
    echo -e "${GREEN}✅ You have passed all the tests! May the force be with you ✅${NC}"
else
    echo -e "${RED}⚠️ Your GNL has errors! Do not join the dark side, you don't need to do it to pass this!$ ⚠️{NC}"
fi

// gnl_tester.c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../get_next_line.h"

#define MAX_LINE_LEN 4096

int compare_files(const char *file1, const char *file2)
{
	FILE *f1 = fopen(file1, "r");
	FILE *f2 = fopen(file2, "r");
	if (!f1 || !f2)
	{
		perror("Failed to open file for comparison");
		return -1;
	}

	char line1[MAX_LINE_LEN];
	char line2[MAX_LINE_LEN];
	int line_num = 1;

	while (fgets(line1, MAX_LINE_LEN, f1) && fgets(line2, MAX_LINE_LEN, f2))
	{
		if (strcmp(line1, line2) != 0)
		{
			printf("❌ Difference at line %d:\n", line_num);
			printf("Expected: %s", line2);
			printf("Got     : %s", line1);
			fclose(f1);
			fclose(f2);
			return 1;
		}
		line_num++;
	}

	if ((fgets(line1, MAX_LINE_LEN, f1) != NULL) || (fgets(line2, MAX_LINE_LEN, f2) != NULL))
	{
		printf("❌ One file has extra lines\n");
		fclose(f1);
		fclose(f2);
		return 1;
	}

	fclose(f1);
	fclose(f2);
	return 0;
}

int run_test(const char *test_name, const char *input_path, const char *expected_path)
{
	int fd = open(input_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening input file");
		return -1;
	}

	FILE *tmp_out = fopen("tmp_output.txt", "w");
	if (!tmp_out)
	{
		perror("Error creating temp output file");
		close(fd);
		return -1;
	}

	char *line;
	while ((line = get_next_line(fd)))
	{
		fputs(line, tmp_out);
		free(line);
	}

	fclose(tmp_out);
	close(fd);

	int cmp = compare_files("tmp_output.txt", expected_path);

	if (cmp == 0)
		printf("✅ %s passed\n", test_name);
	else
		printf("❌ %s failed\n", test_name);

	return cmp;
}

void print_ascii_art(const char *file_path)
{
	int fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return;
	}

	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line); // Print the line (ASCII art)
		free(line);			// Don't forget to free the memory!
	}

	close(fd);
}

int main(void)
{
	int fails = 0;

	fails += run_test("Empty file", "test_files/empty.txt", "test_files/empty_expected.txt");
	fails += run_test("One line", "test_files/simple.txt", "test_files/simple_expected.txt");
	fails += run_test("Long line", "test_files/long_line.txt", "test_files/long_line_expected.txt");
	fails += run_test("Multiline", "test_files/multiline.txt", "test_files/multiline_expected.txt");
	fails += run_test("No final newline", "test_files/no_newline.txt", "test_files/no_newline_expected.txt");
	fails += run_test("Script", "test_files/script.txt", "test_files/script_expected.txt");

	print_ascii_art("test_files/darthvader.txt");
	printf("\n\n\n\n\n");
	usleep(1000000);
	print_ascii_art("test_files/yoda.txt");
	printf("\n\n\n\n\n");
	usleep(1000000);
	print_ascii_art("test_files/falcon.txt");
	printf("\n\n\n\n\n");
	usleep(1000000);
	print_ascii_art("test_files/mandalore.txt");
	printf("\n\n\n\n\n");
	usleep(1000000);
	printf("\n---\nTotal failed tests: %d\n", fails);
	printf("\n\n\n\n\n");
	usleep(1000000);
	return fails;
}

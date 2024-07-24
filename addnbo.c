#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{   //인자 값 제대로 안들어갔을 때
    if (argc != 3)
    {
        printf("[*] Usage: add-nbo <file1> <file2>\n");
        return 0;
    }

    FILE* file1 = fopen(argv[1], "rb");
    FILE* file2 = fopen(argv[2], "rb");
    //파일이 제대로 안열릴 때
    if (!file1 || !file2)
    {
        printf("[*] Opening file Error\n");
        fclose(file1);
        fclose(file2);
        return 0;
    }
    // 파일 크기 확인
    fseek(file1, 0, SEEK_END);
    long size1 = ftell(file1);
    fseek(file1, 0, SEEK_SET);

    fseek(file2, 0, SEEK_END);
    long size2 = ftell(file2);
    fseek(file2, 0, SEEK_SET);

    if (size1 < sizeof(uint32_t) || size2 < sizeof(uint32_t))
    {
        printf("[*] Under 4bytes Error\n");
        fclose(file1);
        fclose(file2);
        return 0;
    }

    uint32_t num1, num2;
    fread(&num1, 1, sizeof(uint32_t), file1);
    fread(&num2, 1, sizeof(uint32_t), file2);
    fclose(file1);
    fclose(file2);
    num1 = ntohl(num1);
    num2 = ntohl(num2);

    uint32_t sum = num1 + num2;

    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", num1, num1, num2, num2, sum, sum);

    return 0;
}


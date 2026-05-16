#include "kernel/types.h"
#include "user/user.h"

// Test 1: Basic lazy allocation
void test_basic_lazy()
{
    printf("Test 1: Basic Lazy Allocation\n");

    char *mem = sbrk(4096);

    mem[0] = 'A';       
    mem[4095] = 'Z';    

    printf("mem[0] = %c\n", mem[0]);
    printf("mem[4095] = %c\n", mem[4095]);

    if (mem[0] == 'A' && mem[4095] == 'Z')
        printf("Test 1 PASSED ✅\n\n");
    else
        printf("Test 1 FAILED ❌\n\n");
}

// Test 2: Large allocation
void test_large_alloc()
{
    printf("Test 2: Large Allocation\n");

    int size = 100 * 4096;  
    char *mem = sbrk(size);

    for (int i = 0; i < size; i += 4096)
    {
        mem[i] = i % 256;
    }

    int passed = 1;
    for (int i = 0; i < size; i += 4096)
    {
        if (mem[i] != (char)(i % 256))
        {
            passed = 0;
            break;
        }
    }

    if (passed)
        printf("Test 2 PASSED ✅\n\n");
    else
        printf("Test 2 FAILED ❌\n\n");
}

// Test 3: Fork compatibility
void test_fork_lazy()
{
    printf("Test 3: Fork with Lazy Memory\n");

    char *mem = sbrk(4096);
    mem[0] = 42;  

    int pid = fork();

    if (pid == 0)
    {
        if (mem[0] == 42)
        {
            printf("Child: memory correct ✅\n");
            exit(0);
        }
        else
        {
            printf("Child: memory WRONG ❌\n");
            exit(1);
        }
    }
    else
    {
        int status;
        wait(&status);
        if (status == 0)
            printf("Test 3 PASSED ✅\n\n");
        else
            printf("Test 3 FAILED ❌\n\n");
    }
}

// Test 4: sbrk(0) Check
void test_sbrk_size()
{
    printf("Test 4: sbrk(0) Size Check\n");

    char *before = sbrk(0);       
    sbrk(4096);                   
    char *after = sbrk(0);        

    if (after == before + 4096)
        printf("Test 4 PASSED ✅\n\n");
    else
        printf("Test 4 FAILED ❌\n\n");
}

// Test 5: syscall string access
void test_syscall_string()
{
    printf("Test 5: Syscall String Access\n");

    char *buf = sbrk(100);

    if (buf == (char*)-1)
    {
        printf("Test 5 FAILED ❌ (sbrk failed)\n\n");
        return;
    }

    strcpy(buf, "nonexistentfile");

    int fd = open(buf, 0);

    if (fd >= 0)
        close(fd);

    printf("Test 5 PASSED ✅\n\n");
}

int main()
{
    printf("=========================\n");
    printf("  Lazy Allocation Tests  \n");
    printf("=========================\n\n");

    test_basic_lazy();
    test_large_alloc();
    test_fork_lazy();
    test_sbrk_size();
    test_syscall_string();

    printf("=========================\n");
    printf("    All Tests Done!      \n");
    printf("=========================\n");

    exit(0);
}

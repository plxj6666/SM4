#include "sm4.h"
#include "benchmark.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 生成随机IV
static void generate_random_iv(unsigned char *iv) {
    for (int i = 0; i < SM4_IV_SIZE; i++) {
        iv[i] = (unsigned char)rand();
    }
}

// 测试不同大小数据的CBC模式性能
void test_sm4_cbc_performance() {
    const size_t sizes[] = {64, 2048, 10*1024*1024}; // 64B, 2KB, 10MB
    const char *size_names[] = {"64B", "2KB", "10MB"};
    const int BENCHS = 5;
    const int ROUNDS = 1;
    
    unsigned char key[SM4_KEY_SIZE];
    unsigned char iv[SM4_IV_SIZE];
    
    // 生成随机密钥
    for (int i = 0; i < SM4_KEY_SIZE; i++) {
        key[i] = (unsigned char)rand();
    }
    
    for (size_t i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        size_t test_size = sizes[i];
        printf("\nTesting SM4-CBC with data size: %s\n", size_names[i]);
        
        // 分配测试数据空间
        unsigned char *plaintext = (unsigned char *)malloc(test_size + SM4_BLOCK_SIZE);
        unsigned char *ciphertext = (unsigned char *)malloc(test_size + SM4_BLOCK_SIZE);
        unsigned char *decrypted = (unsigned char *)malloc(test_size + SM4_BLOCK_SIZE);
        
        // 生成随机测试数据
        for (size_t j = 0; j < test_size; j++) {
            plaintext[j] = (unsigned char)rand();
        }
        
        // 加密性能测试
        generate_random_iv(iv);
        BPS_BENCH_START("SM4-CBC encryption", BENCHS);
        BPS_BENCH_ITEM(generate_random_iv(iv), 
                       sm4_cbc_encrypt(plaintext, test_size, key, iv, ciphertext), 
                       ROUNDS);
        BPS_BENCH_FINAL(test_size * 8);
        
        // 解密性能测试
        BPS_BENCH_START("SM4-CBC decryption", BENCHS);
        BPS_BENCH_ITEM(generate_random_iv(iv), 
                       sm4_cbc_decrypt(ciphertext, test_size, key, iv, decrypted), 
                       ROUNDS);
        BPS_BENCH_FINAL(test_size * 8);
        
        free(plaintext);
        free(ciphertext);
        free(decrypted);
    }
}

int main() {
    srand(time(NULL));
    printf(">> Performing SM4-CBC performance test...\n");
    test_sm4_cbc_performance();
    return 0;
} 
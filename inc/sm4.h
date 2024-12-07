#ifndef SM4_H
#define SM4_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#define SM4_BLOCK_BITS 128 /* bits of AES algoithm block */
#define SM4_BLOCK_SIZE 16  /* bytes of AES algoithm block 16 * 8 = 128 */
#define SM4_KEY_SIZE 16    /* bytes of AES algoithm double key 16 * 8 = 128  */
#define SM4_ROUNDS 32

    /**
     * @brief Generate encryption subkeys
     * @param[in] key original key
     * @param[out] encSubKeys generated subkeys
     * @return 0 OK
     * @return 1 Failed
     */
    int sm4_make_enc_subkeys(const unsigned char key[SM4_KEY_SIZE], uint32_t encSubKeys[SM4_ROUNDS]);

    /**
     * @brief Generate decryption subkeys
     * @param[in] key original key
     * @param[out] decSubKeys generated subkeys
     * @return 0 OK
     * @return 1 Failed
     */
    int sm4_make_dec_subkeys(const unsigned char key[SM4_KEY_SIZE], uint32_t decSubKeys[SM4_ROUNDS]);

    /**
     * @brief SM4 encrypt single block
     * @param[in] input plaintext, [length = SM4_BLOCK_SIZE]
     * @param[in] encSubKeys encryption subKeys
     * @param[out] output ciphertext, [length = SM4_BLOCK_SIZE]
     */
    void sm4_encrypt_block(const unsigned char *input, const uint32_t encSubKeys[SM4_ROUNDS], unsigned char *output);

    /**
     * @brief SM4 decrypt single block
     * @param[in] input ciphertext, [length = SM4_BLOCK_SIZE]
     * @param[in] decSubKeys decryption subKeys
     * @param[out] output plaintext, [length = SM4_BLOCK_SIZE]
     */
    void sm4_decrypt_block(const unsigned char *input, const uint32_t decSubKeys[SM4_ROUNDS], unsigned char *output);

// CBC 模式相关定义和接口
#define SM4_IV_SIZE SM4_BLOCK_SIZE

/**
 * @brief Initialize encryption subkeys with a key
 * @param[in] key original key
 * @param[out] encSubKeys generated subkeys
 */
void encInit(const unsigned char key[SM4_KEY_SIZE], uint32_t encSubKeys[SM4_ROUNDS]);

/**
 * @brief Initialize decryption subkeys with a key
 * @param[in] key original key
 * @param[out] decSubKeys generated subkeys
 */
void decInit(const unsigned char key[SM4_KEY_SIZE], uint32_t decSubKeys[SM4_ROUNDS]);

/**
 * @brief SM4-CBC 加密
 * @param[in] plaintext 明文数据
 * @param[in] length 数据长度(字节)
 * @param[in] key 密钥 [length = SM4_KEY_SIZE]
 * @param[in] iv 初始向量 [length = SM4_IV_SIZE]
 * @param[out] ciphertext 密文输出
 * @return 实际加密的字节数
 */
size_t sm4_cbc_encrypt(const unsigned char *plaintext, size_t length,
                      const unsigned char *key, const unsigned char *iv,
                      unsigned char *ciphertext);

/**
 * @brief SM4-CBC 解密
 * @param[in] ciphertext 密文数据
 * @param[in] length 数据长度(字节)
 * @param[in] key 密钥 [length = SM4_KEY_SIZE]
 * @param[in] iv 初始向量 [length = SM4_IV_SIZE]
 * @param[out] plaintext 明文输出
 * @return 实际解密的字节数
 */
size_t sm4_cbc_decrypt(const unsigned char *ciphertext, size_t length,
                      const unsigned char *key, const unsigned char *iv,
                      unsigned char *plaintext);

#ifdef __cplusplus
}
#endif

#endif // SM4_H

#include <iostream>
#include <openssl/evp.h>
#include <openssl/kdf.h>
//#include <common.h>

int hkdf(const EVP_MD* md, const char* secret, const int secret_len, const unsigned char* salt, const int salt_len, const unsigned char* info, const int info_len, size_t key_len, unsigned char* key) {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_HKDF, NULL);
    int result = 0;
    result = EVP_PKEY_derive_init(ctx);
    if (result <= 0) {
        return result;
    }
    result = EVP_PKEY_CTX_set_hkdf_md(ctx, md);
    if (result <= 0) {
        return result;
    }
    result = EVP_PKEY_CTX_set1_hkdf_salt(ctx, salt, salt_len);
    if (result <= 0) {
        return result;
    }
    result = EVP_PKEY_CTX_set1_hkdf_key(ctx, secret, secret_len);
    if (result <= 0) {
        return result;
    }
    result = EVP_PKEY_CTX_add1_hkdf_info(ctx, info, info_len);
    if (result <= 0) {
        return result;
    }
    return EVP_PKEY_derive(ctx, key, &key_len);
}

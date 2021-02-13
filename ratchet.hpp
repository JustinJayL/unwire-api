#ifndef RATCHET_HPP_
#define RATCHET_HPP_
namespace ratchet {
    void runTemp();
    unsigned char* mx_hmac_sha256(const void* key, int keylen,
        const unsigned char* data, int datalen,
        unsigned char* result, unsigned int* resultlen);
}
#endif
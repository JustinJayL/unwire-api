/*C++ implementation of wireapp's flavor of the axolotl protocol.
* Currently WIP.
* 
* 
* 
*/
#include <string>
#include "ratchet.hpp"
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/kdf.h>
#include <openssl/sha.h>
#include <vector>
#include <iostream>
#include "util.hpp"

#include <openssl/evp.h>
#include <openssl/kdf.h>

#include <stdio.h>
#include <stdlib.h>
#include "testing.cpp"

using std::vector;
namespace ratchet {
    using std::string;
    //using string = std::string;
    struct ConversationState {
        //32-byes, updated by DH ratchet
        std::string rootKey;
        //32-bytes, one key per inwards (receive) and outwards (send) channel
        std::string chainKeySend;
        std::string chainKeyReceive;
        std::string ratchetKeySend;
        std::string ratchetKeyReceive;
        //reset to 0 for every new ratchet
        int msgNoSend;
        int msgNoReceive;
        //sent under previous ratchet?
        vector<int> previousMsgNums;
        //will send a new ratchet key in next msg
        bool ratchetFlag;
        //if we get a message with an out of order id number
        struct missingMsg {
            std::string msgKey;
            int msgNo;
            //todo: type?
            std::string timestamp;
        };
        vector<missingMsg> missing;
    };

    unsigned char* mx_hmac_sha256(const void* key, int keylen,
        const unsigned char* data, int datalen,
        unsigned char* result, unsigned int* resultlen) {
        return HMAC(EVP_sha256(), key, keylen, data, datalen, result, resultlen);
    }


    //return a string object with the binary sha256 result of string input.
inline string sha256(string input)
    {
        unsigned char* inputBytes = (unsigned char*)strdup(input.c_str());
        const int inputLength = input.length();

        const int hashLength = 32;
        unsigned char hash[hashLength];

        SHA256_CTX context;
        SHA256_Init(&context);
        SHA256_Update(&context, inputBytes, inputLength);
        SHA256_Final(hash, &context);

        //TODO: Test to see if it works
        string ret = string((char *)hash, 32);
        delete hash;
        delete inputBytes;
        return ret;
    }

    string test2(string ikm, string salt, string info, int outputLength) {

        const EVP_MD* md = EVP_sha256();

        unsigned char *outputBytes = new unsigned char[outputLength];
        hkdf(md, ikm.c_str(), ikm.length(), (const unsigned char*)salt.c_str(), salt.length(), (const unsigned char*)info.c_str(), info.length(), outputLength, outputBytes);







        //std::cout << hexlify(string((const char*)outputBytes, outputLength));
        string ret((const char*)outputBytes, outputLength);
        delete outputBytes;
        return ret;
    }
    void runTemp() {

        string IKM1 = unhexlify("0x0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b");
        string salt1 = unhexlify("0x000102030405060708090a0b0c");
        string info1 = unhexlify("0xf0f1f2f3f4f5f6f7f8f9");
        int l1 = 42;

        string IKM2 = unhexlify(
            "0x000102030405060708090a0b0c0d0e0f"
            "101112131415161718191a1b1c1d1e1f"
            "202122232425262728292a2b2c2d2e2f"
            "303132333435363738393a3b3c3d3e3f"
            "404142434445464748494a4b4c4d4e4f"
        );
        string salt2 = unhexlify(
            "0x606162636465666768696a6b6c6d6e6f"
            "707172737475767778797a7b7c7d7e7f"
            "808182838485868788898a8b8c8d8e8f"
            "909192939495969798999a9b9c9d9e9f"
            "a0a1a2a3a4a5a6a7a8a9aaabacadaeaf"
        );
        string info2 = unhexlify(
            "0xb0b1b2b3b4b5b6b7b8b9babbbcbdbebf"
            "c0c1c2c3c4c5c6c7c8c9cacbcccdcecf"
            "d0d1d2d3d4d5d6d7d8d9dadbdcdddedf"
            "e0e1e2e3e4e5e6e7e8e9eaebecedeeef"
            "f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"
        );

        int l2 = 82;

            std::cout << "Result: " << hexlify(test2(IKM1, salt1, info1, l1)) << std::endl;
            std::cout << "Result: " << hexlify(test2(IKM2, salt2, info2, l2)) << std::endl;

        }
}
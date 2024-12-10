#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <ctime>
#include <functional>
#include <openssl/sha.h>

class block
{
public:
    block(int, std::string, const unsigned char *);
    // block(int, std::string, size_t = 0);
    std::string getData();
    // size_t getHash();
    // size_t hash() const;
    // size_t getPrevHash();
    const unsigned char *getHash() const;
    const unsigned char *hash() const;
    const unsigned char *getPrevHash() const;

private:
    std::string data;
    time_t nonce;
    // size_t prevHash;
    // size_t currentHash;
    unsigned char prevHash[SHA256_DIGEST_LENGTH];
    unsigned char currentHash[SHA256_DIGEST_LENGTH];
    int blockNum;
    void calculateHash();
};
#endif
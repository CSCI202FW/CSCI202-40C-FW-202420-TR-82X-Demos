#include "block.h"

/* block::block(int blockNum, std::string data, size_t prevHash) : blockNum(blockNum), prevHash(prevHash), data(data)
{
    this->nonce = time(NULL);
    calculateHash();
} */

void block::calculateHash()
{

    /* std::hash<std::string> str_hash;
    std::string hashString = std::to_string(blockNum) + std::to_string(nonce) + data + std::to_string(prevHash);
    currentHash = str_hash(hashString); */
    std::string phash(prevHash, prevHash + sizeof(prevHash) / sizeof(prevHash[0]));
    std::string hashString = std::to_string(blockNum) + std::to_string(nonce) + data + phash;
    SHA256((unsigned char *)hashString.c_str(), hashString.length(), currentHash);
}

block::block(int blockNum, std::string data, const unsigned char *prevHash)
{
    this->blockNum = blockNum;
    this->data = data;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        this->prevHash[i] = prevHash[i];
    }
    calculateHash();
}

std::string block::getData()
{
    return data;
}

const unsigned char *block::getHash() const
{
    return currentHash;
}

const unsigned char *block::hash() const
{
    unsigned char *h = new unsigned char[SHA256_DIGEST_LENGTH];
    std::string phash(prevHash, prevHash + sizeof(prevHash) / sizeof(prevHash[0]));
    std::string hashString = std::to_string(blockNum) + std::to_string(nonce) + data + phash;
    SHA256((unsigned char *)hashString.c_str(), hashString.length(), h);
    return h;
}

const unsigned char *block::getPrevHash() const
{
    return prevHash;
}

/* size_t block::getHash()
{
    // calculateHash();
    return currentHash;
}

size_t block::hash() const
{
    std::hash<std::string> str_hash;
    std::string hashString = std::to_string(blockNum) + std::to_string(nonce) + data + std::to_string(prevHash);
    return str_hash(hashString);
}

size_t block::getPrevHash()
{
    return prevHash;
}
 */
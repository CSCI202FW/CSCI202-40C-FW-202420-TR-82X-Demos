#include "blockchain.h"

blockChain::blockChain()
{
    numBlocks = 0;
    unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
    block genesis(numBlocks++, "Genesis Block", hash);
    chain.enqueue(genesis);
}

void blockChain::insert(std::string message)
{
    block newBlock(numBlocks++, message, chain.back().getHash());
    chain.enqueue(newBlock);
}

/* void blockChain::verify()
{
    linkedQueue<block> cpy(chain);
    // unsigned char *currentHash;
    // unsigned char *recalculatedHash;
    unsigned char prevH[SHA256_DIGEST_LENGTH] = {0};
    const unsigned char *prevHash = nullptr;
    int count = 0;
    while (!cpy.isEmptyQueue())
    {
        block current(cpy.dequeue());
        /* if (count == 2)
        {
            current.data = "hello it";
        }
        count++;
        const unsigned char *currentHash = current.getHash();
        const unsigned char *recalculatedHash = current.hash();
        if (currentHash != recalculatedHash)
        {
            throw std::runtime_error("Block has been changed");
        }

        if (prevHash == nullptr && prevH != current.getPrevHash())
        {
            throw std::runtime_error("Block has been changed");
        }
        prevHash = recalculatedHash;
    }
}
 */
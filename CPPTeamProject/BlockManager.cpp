#include "BlockManager.h"

const char(*BlockManager::getBlock())[4][4][4]
{
    return this->block;
}

const char(*BlockManager::getFirstBlock())[4][4][4]
{
    return this->firstbock;
}

const char(*BlockManager::getSecondBlock())[4][8][8]
{
    return this->secondblock;
}

const char(*BlockManager::getThirdBlock())[4][8][8]
{
    return this->thirdblock;
}


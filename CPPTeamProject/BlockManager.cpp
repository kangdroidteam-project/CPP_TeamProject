#include "BlockManager.h"

const char(*BlockManager::getBlock())[4][4][4]
{
    return this->block;
}

const char(*BlockManager::getFirstBlock())[4][4][4]
{
    return this->firstbock;
}

const char(*BlockManager::getSecondBlock())[4][5][5]
{
    return this->secondblock;
}

const char(*BlockManager::getThirdBlock())[4][5][5]
{
    return this->thirdblock;
}


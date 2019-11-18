#include "BlockManager.h"

char(*BlockManager::getBlock())[4][4][4]
{
    return this->block;
}

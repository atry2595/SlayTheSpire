#include "FileManager.h"

FileManager::FileManager()
{
    nextId = 1001;
    loggedInPlayerIndex = -1;
}

int FileManager::generateId()
{
    return nextId++;
}
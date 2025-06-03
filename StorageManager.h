#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <memory>
#include <unordered_map>
#include <map>
#include "StoredItem.h"
#include "DuplicateItemException.h"
#include "ItemNotFoundException.h"

class StorageManager {
private:
    std::unordered_map<std::string, std::shared_ptr<StoredItem>> itemMap;

public:
    void addItem(const std::string &id, const std::string &description, const std::string &location);
    std::shared_ptr<StoredItem> findById(const std::string &id) const;
    void removeItem(const std::string &id);
    std::map<std::string, std::shared_ptr<StoredItem>> listItemsByDescription() const;
};

#endif

#include "StorageManager.h"

void StorageManager::addItem(const std::string &id, const std::string &description, const std::string &location) {
    if (itemMap.find(id) != itemMap.end()) {
        throw DuplicateItemException("Item with ID already exists.");
    }
    itemMap[id] = std::make_shared<StoredItem>(id, description, location);
}

std::shared_ptr<StoredItem> StorageManager::findById(const std::string &id) const {
    auto it = itemMap.find(id);
    if (it == itemMap.end()) {
        throw ItemNotFoundException("Item not found.");
    }
    return it->second;
}

void StorageManager::removeItem(const std::string &id) {
    if (itemMap.erase(id) == 0) {
        throw ItemNotFoundException("Item not found.");
    }
}

std::map<std::string, std::shared_ptr<StoredItem>> StorageManager::listItemsByDescription() const {
    std::map<std::string, std::shared_ptr<StoredItem>> sorted;
    for (const auto &pair : itemMap) {
        sorted[pair.second->getDescription()] = pair.second;
    }
    return sorted;
}

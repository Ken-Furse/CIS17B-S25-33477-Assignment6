#include "StoredItem.h"

StoredItem::StoredItem(const std::string &id, const std::string &description, const std::string &location)
    : id(id), description(description), location(location) {}

std::string StoredItem::getId() const { return id; }
std::string StoredItem::getDescription() const { return description; }
std::string StoredItem::getLocation() const { return location; }

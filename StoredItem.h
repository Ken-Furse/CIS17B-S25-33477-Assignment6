#ifndef STOREITEM_H
#define STOREITEM_H

#include <string>

class StoredItem {
private:
    std::string id;
    std::string description;
    std::string location;

public:
    StoredItem(const std::string &id, const std::string &description, const std::string &location);
    std::string getId() const;
    std::string getDescription() const;
    std::string getLocation() const;
};

#endif

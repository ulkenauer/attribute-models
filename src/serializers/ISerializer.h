//
// Created by ulkenauer on 14.11.2020.
//

#ifndef UNTITLED_ISERIALIZER_H
#define UNTITLED_ISERIALIZER_H


#include <string>
#include "../attribute/AttributeTree.h"

typedef std::string (* AttributeSerializer)(AttributeNode node);

/**
 * TODO: create ISerializable interface, that has getAttributeTree method
 */
class ISerializer {
public:
    virtual std::string serialize(AttributeTree attributes) = 0;
    virtual AttributeTree deserialize(std::string serialized) = 0;
};


#endif //UNTITLED_ISERIALIZER_H

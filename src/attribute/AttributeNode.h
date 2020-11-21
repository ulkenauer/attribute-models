//
// Created by ulkenauer on 14.11.2020.
//

#ifndef UNTITLED_ATTRIBUTENODE_H
#define UNTITLED_ATTRIBUTENODE_H


#include <string>
#include <memory>

class AttributeNode {
public:
    std::string nodeType;
    std::shared_ptr<void> data;
};


#endif //UNTITLED_ATTRIBUTENODE_H

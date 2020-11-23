//
// Created by ulkenauer on 23.11.2020.
//

#ifndef UNTITLED_IATTRIBUTEMODEL_H
#define UNTITLED_IATTRIBUTEMODEL_H

#include "AttributeTree.h"

class IAttributeModel {
public:
    virtual AttributeTree toAttributeTree() = 0;
    virtual void fromAttributeTree(AttributeTree attributeTree) = 0;
};

#endif //UNTITLED_IATTRIBUTEMODEL_H

#include "Model.h"

AttributeTree Model::toAttributeTree()
{
    AttributeTree attributeTree = AttributeTree();

    attributeTree[Model::ATTR_NAME] = AttributeNode();
    attributeTree[Model::ATTR_NAME].nodeType = __TYPE_STRING__;
    attributeTree[Model::ATTR_NAME].data = std::make_shared<std::string>(this->name);

    attributeTree[Model::ATTR_QUANTITY] = AttributeNode();
    attributeTree[Model::ATTR_QUANTITY].nodeType = __TYPE_INTEGER__;
    attributeTree[Model::ATTR_QUANTITY].data = std::make_shared<int>(this->quantity);

    attributeTree[Model::ATTR_CHILD] = AttributeNode();
    attributeTree[Model::ATTR_CHILD].nodeType = __TYPE_NODE__;
    attributeTree[Model::ATTR_CHILD].data = nullptr;

    if (this->child != nullptr) {
        attributeTree[Model::ATTR_CHILD].data = std::make_shared<AttributeTree>(this->child->toAttributeTree());
    }

    return attributeTree;
}

void Model::fromAttributeTree(AttributeTree attributeTree)
{
    this->name = std::string(*((std::string*) attributeTree[Model::ATTR_NAME].data.get()));
    this->quantity = int(*((int*) attributeTree[Model::ATTR_QUANTITY].data.get()));
    AttributeTree* childPtr = (AttributeTree*) attributeTree[Model::ATTR_CHILD].data.get();

    if(childPtr != nullptr) {
        this->child = std::make_shared<Model>();

        this->child->fromAttributeTree(*childPtr);
    }
}

const std::string Model::ATTR_NAME = "ATTR_NAME";
const std::string Model::ATTR_QUANTITY = "ATTR_QUANTITY";
const std::string Model::ATTR_CHILD = "ATTR_CHILD";
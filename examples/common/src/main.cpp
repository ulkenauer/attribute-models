#include <iostream>
#include "../../../library.h"

class Model : public virtual IAttributeModel {
public:
    const std::string ATTR_NAME = "ATTR_NAME";
    const std::string ATTR_QUANTITY = "ATTR_QUANTITY";
    const std::string ATTR_CHILD = "ATTR_CHILD";

    int quantity;
    std::string name;
    std::shared_ptr<Model> child;

    void fromAttributeTree(AttributeTree attributeTree) override
    {
        this->name = std::string(*((std::string*) attributeTree[Model::ATTR_NAME].data.get()));
        this->quantity = int(*((int*) attributeTree[Model::ATTR_QUANTITY].data.get()));
        AttributeTree* childPtr = (AttributeTree*) attributeTree[Model::ATTR_CHILD].data.get();

        if(childPtr != nullptr) {
            this->child = std::make_shared<Model>();
            this->child->fromAttributeTree(*childPtr);
        }
    }

    AttributeTree toAttributeTree() override
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
};

int main()
{
    Model model;
    Model templateModel;
    auto child = std::make_shared<Model>();

    Model second;

    model.name = "asdfg";
    model.quantity = 4;

    templateModel.name = "qwerty";
    templateModel.quantity = 3;

    child->name = "child model";
    child->quantity = 1336;

    model.child = child;

    std::cout << model.name << " " << model.quantity << std::endl;
    model.fromAttributeTree(templateModel.toAttributeTree());
    std::cout << model.name << " " << model.quantity << std::endl;

    std::map<std::string, ISerializer*> knownSerializers;

    knownSerializers["plain"] = new PlainSerializer();

    try {
        std::cout << knownSerializers["plain"]->serialize(model.toAttributeTree()) << std::endl;
    } catch (int ex) {
        std::cout << ex << std::endl;
    }

    second.fromAttributeTree(model.toAttributeTree());
    second.name = "CLONED";
    second.child->name = "FOOBAR";

    child = std::make_shared<Model>();
    child->name = "child's child model";
    child->quantity = 22;

    second.child->child = child;

    std::cout << "second" << std::endl;
    std::cout << knownSerializers["plain"]->serialize(second.toAttributeTree()) << std::endl;

    std::cout << "first again" << std::endl;
    std::cout << knownSerializers["plain"]->serialize(model.toAttributeTree()) << std::endl;

    return 0;
}
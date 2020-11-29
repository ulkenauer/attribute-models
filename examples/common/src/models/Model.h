#include "../../../../library.h"

class Model : public virtual IAttributeModel {
public:
    static const std::string ATTR_NAME;
    static const std::string ATTR_QUANTITY;
    static const std::string ATTR_CHILD;

    int quantity;
    std::string name;
    std::shared_ptr<Model> child;

    void fromAttributeTree(AttributeTree attributeTree) override;

    AttributeTree toAttributeTree() override;
};
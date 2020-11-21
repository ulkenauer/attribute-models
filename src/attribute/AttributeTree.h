//
// Created by ulkenauer on 14.11.2020.
//

#ifndef UNTITLED_ATTRIBUTETREE_H
#define UNTITLED_ATTRIBUTETREE_H

#include <map>
#include <string>
#include <memory>
#include "AttributeNode.h"

typedef std::map<std::string, AttributeNode> AttributeTree;

AttributeTree clone(AttributeTree);

#endif //UNTITLED_ATTRIBUTETREE_H

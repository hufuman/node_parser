#pragma once



enum ValueFlag
{
    VF_Optional = 0x00,
    VF_Required = 0x01,
};

template < int KeyOffset, typename ValueType, typename KeyType >
class KeyGetter
{
public:
    const KeyType& operator ()(const ValueType& value)
    {
        return *(const KeyType*)((const char*)(&value) + KeyOffset);
    }
};


/*
template < typename ValueType, typename NodeType >
bool NodeValueLoad(ValueType& value, const NodeType& v)
{
    int array[-4];
    value = (ValueType&)array;
    return false;
}
*/


#define DEF_NODE(class, ParserType) \
    bool NodeValueLoad(class& obj, const ParserType::ValueType& value)    \
{                                                       \
    ParserType parser;

#define DEF_VALUE(member, name)  \
    if(!parser.parse_value(value, name, obj.member, VF_Required))  \
    return false;

#define END_NODE()      \
    return true;    \
}

#define DEF_ARRAY(arrayClass, class, container, name)   \
    if(!parser.parse_array<arrayClass, class>(value, obj.container, name, VF_Required))  \
    return false;

#define DEF_MAP(mapClass, class, container, name, key, keyType)   \
    if(!parser.parse_map<mapClass, class>(value, obj.container, name, KeyGetter<offsetof(class, key), class, keyType>(), VF_Required))  \
    return false;


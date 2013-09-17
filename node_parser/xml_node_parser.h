#pragma once

#include "xml_util.h"

class xml_node_parser
{
public:

    typedef TiXmlElement ValueType;

    template < typename ValueType >
    bool parse_value(const TiXmlElement& value, const char* name, ValueType& obj, int flags)
    {
        return (xml_util::xml_cast(value, name, obj) || (flags ^ VF_Required));
    }

    template < typename MapType, typename ValueType, typename KeyGetter >
    bool parse_map(const TiXmlElement& value, MapType& obj, const char* name, KeyGetter getter, int flags)
    {
        const TiXmlElement* arr = value.FirstChildElement(name);
        if(arr == nullptr)
            return ((flags ^ VF_Required) == 0);

        const TiXmlElement* data = arr->FirstChildElement();
        while(data != nullptr)
        {
            ValueType tmpValue;
            if(!NodeValueLoad(tmpValue, *data))
                return false;
            std::pair<MapType::iterator, bool> result = obj.insert(std::make_pair(getter(tmpValue), tmpValue));
            if(!result.second)
                return false;
            data = data->NextSiblingElement();
        }
        return true;
    }

    template < typename ArrayType, typename ValueType >
    bool parse_array(const TiXmlElement& value, ArrayType& obj, const char* name, int flags)
    {
        const TiXmlElement* arr = value.FirstChildElement(name);
        if(arr == nullptr)
            return ((flags ^ VF_Required) == 0);

        const TiXmlElement* data = arr->FirstChildElement();
        while(data != nullptr)
        {
            ValueType tmpValue;
            if(!NodeValueLoad(tmpValue, *data))
                return false;

            obj.push_back(tmpValue);

            data = data->NextSiblingElement();
        }

        return true;
    }

};

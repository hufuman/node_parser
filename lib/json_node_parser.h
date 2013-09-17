#pragma once

#include "json_util.h"

class json_node_parser
{
public:

    typedef Json::Value ValueType;

    template < typename ValueType >
    bool parse_value(const Json::Value& value, const char* name, ValueType& obj, int flags)
    {
        return (json_util::json_cast(value, name, obj) || (flags ^ VF_Required));
    }

    template < typename MapType, typename ValueType, typename KeyGetter >
    bool parse_map(const Json::Value& value, MapType& obj, const char* name, KeyGetter getter, int flags)
    {
        if(!value.isMember(name))
            return ((flags & VF_Required) == 0);

        const Json::Value& arr = value[name];
        if(!arr.isArray())
            return false;

        Json::Value::const_iterator ite = arr.begin();
        for(; ite != arr.end(); ++ ite)
        {
            ValueType tmpValue;
            const Json::Value& v = *ite;
            if(!NodeValueLoad<json_node_parser>(tmpValue, v))
                return false;
            std::pair<MapType::iterator, bool> result = obj.insert(std::make_pair(getter(tmpValue), tmpValue));
            if(!result.second)
                return false;
        }
        return true;
    }

    template < typename ArrayType, typename ValueType >
    bool parse_array(const Json::Value& value, ArrayType& obj, const char* name, int flags)
    {
        if(!value.isMember(name))
            return ((flags & VF_Required) == 0);

        const Json::Value& arr = value[name];
        if(!arr.isArray())
            return false;

        size_t count = arr.size();
        size_t index = 0;
        obj.resize(count);
        Json::Value::const_iterator ite = arr.begin();
        for(; ite != arr.end(); ++ ite)
        {
            const Json::Value& v = *ite;
            if(!NodeValueLoad<json_node_parser>(obj[index], v))
                return false;
            ++ index;
        }
        return true;
    }

};

#pragma once

#include <string>
#include <cassert>
#include "../3rdlib/json/json/json.h"

#include <boost/lexical_cast.hpp>
#include <boost/locale.hpp>
#include <boost/tokenizer.hpp>

#include "data_def.h"

namespace json_util
{

    template < typename T >
    bool json_cast(const Json::Value& v, const char* name, T& target)
    {
        int array[-4];
        target = (T&)array;
        return false;
    }

    template <>
    bool json_cast(const Json::Value& value, const char* name, bool& target)
    {
        const Json::Value& v = value[name];
        if(&v == &Json::Value::null || !v.isConvertibleTo(Json::booleanValue))
        {
            XALERT(L"json_cast, incompatible value");
            return false;
        }

        target = v.asBool();
        return true;
    }

    template <>
    bool json_cast(const Json::Value& value, const char* name, std::string& target)
    {
        const Json::Value& v = value[name];
        if(&v == &Json::Value::null || !v.isConvertibleTo(Json::stringValue))
        {
            XALERT(L"json_cast, incompatible value");
            return false;
        }

        target = v.asString();
        return true;
    }

    template <>
    bool json_cast(const Json::Value& value, const char* name, int& target)
    {
        const Json::Value& v = value[name];
        if(&v == &Json::Value::null || !v.isConvertibleTo(Json::intValue))
        {
            XALERT(L"json_cast, incompatible value");
            return false;
        }

        target = v.asInt();
        return true;
    }

    template <>
    bool json_cast(const Json::Value& value, const char* name, const Utf8Char*& target)
    {
        const Json::Value& v = value[name];
        if(&v == &Json::Value::null || !v.isString())
        {
            XALERT(L"json_cast, incompatible value");
            return false;
        }

        target = static_cast<const Utf8Char*>(v.asCString());
        return true;
    }

    template <>
    bool json_cast(const Json::Value& value, const char* name, uint32_t& target)
    {
        const Json::Value& v = value[name];
        if(&v == &Json::Value::null)
            return false;

        if(v.isInt())
            target = v.asInt();
        else if(v.isUInt())
            target = v.asUInt();
        else if(v.isString())
            target = boost::lexical_cast<uint32_t>(v.asCString());
        else if(v.isDouble())
            target = v.asUInt();
        else
        {
            XALERT(L"json_cast, incompatible value");
            return false;
        }
        return true;
    }

    template <>
    bool json_cast(const Json::Value& value, const char* name, uint64_t& target)
    {
        const Json::Value& v = value[name];
        if(&v == &Json::Value::null)
            return false;

        if(v.isInt())
            target = static_cast<uint32_t>(v.asInt());
        else if(v.isUInt())
            target = v.asUInt();
        else if(v.isString())
            target = boost::lexical_cast<uint64_t>(v.asCString());
        else
        {
            XALERT(L"json_cast, incompatible value");
            return false;
        }
        return true;
    }

    template <>
    bool json_cast(const Json::Value& value, const char* name, Utf16String& target)
    {
        const Json::Value& v = value[name];
        if(&v == &Json::Value::null || !v.isString())
            return false;

        try
        {
            target = boost::locale::conv::utf_to_utf<wchar_t>(v.asCString(), boost::locale::conv::stop);
        }
        catch (boost::locale::conv::conversion_error&)
        {
            XALERT(L"json_cast, incompatible value");
            return false;
        }
        return true;
    }

    const Json::Value* find_value(const Json::Value& value, const char* path)
    {
        typedef boost::tokenizer<boost::char_separator<char> > 
            tokenizer;
        boost::char_separator<char> sep("\\/");
        std::string path_string(path);
        tokenizer tokens(path_string, sep);

        const Json::Value* v = &value;

        bool ok = true;
        for (tokenizer::iterator ite = tokens.begin();
            ite != tokens.end(); ++ite)
        {
            ok = v->isMember(*ite);
            if(ok)
                v = &((*v)[*ite]);
            else
                break;
        }
        return ok ? v : nullptr;
    }

    template < typename T >
    bool get_value(const Json::Value& value, const char* path, const char* name, T& result)
    {
        const Json::Value* v = find_value(value, path);
        if(v)
            return json_util::json_cast(*v, name, result);
        else
            return false;
    }

}
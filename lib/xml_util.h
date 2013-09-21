#pragma once

#include <string>
#include <cassert>

#include <boost/lexical_cast.hpp>
#include <boost/locale.hpp>
#include <boost/tokenizer.hpp>


#include "data_def.h"

namespace xml_util
{

    template < typename T >
    bool xml_cast(const TiXmlElement& v, const char* name, T& target)
    {
        int array[-4];
        target = (T&)array;
        return false;
    }

    template <>
    bool xml_cast(const TiXmlElement& value, const char* name, bool& target)
    {
        const char* result = value.Attribute(name);
        if(result == nullptr)
            return false;

        target = !(stricmp(result, "false") == 0 || stricmp(result, "0") == 0);
        return true;
    }

    template <>
    bool xml_cast(const TiXmlElement& value, const char* name, std::string& target)
    {
        const char* result = value.Attribute(name);
        if(result == nullptr)
            return false;

        target = boost::locale::conv::from_utf<char>(result, "GB2312");
        return true;
    }

    template <>
    bool xml_cast(const TiXmlElement& value, const char* name, int& target)
    {
        const char* result = value.Attribute(name);
        if(result == nullptr)
            return false;

        target = boost::lexical_cast<int>(result);
        return true;
    }

    template <>
    bool xml_cast(const TiXmlElement& value, const char* name, const Utf8Char*& target)
    {
        const char* result = value.Attribute(name);
        if(result == nullptr)
            return false;

        target = result;
        return true;
    }

    template <>
    bool xml_cast(const TiXmlElement& value, const char* name, uint32_t& target)
    {
        const char* result = value.Attribute(name);
        if(result == nullptr)
            return false;

        target = boost::lexical_cast<uint32_t>(result);
        return true;
    }

    template <>
    bool xml_cast(const TiXmlElement& value, const char* name, uint64_t& target)
    {
        const char* result = value.Attribute(name);
        if(result == nullptr)
            return false;

        target = boost::lexical_cast<uint64_t>(result);
        return true;
    }

    template <>
    bool xml_cast(const TiXmlElement& value, const char* name, Utf16String& target)
    {
        const char* result = value.Attribute(name);
        if(result == nullptr)
            return false;

        target = boost::locale::conv::utf_to_utf<wchar_t>(result, boost::locale::conv::stop);
        return true;
    }

    const TiXmlElement* find_value(const TiXmlElement& value, const char* path)
    {
        typedef boost::tokenizer<boost::char_separator<char> > 
            tokenizer;
        boost::char_separator<char> sep("\\/");
        std::string path_string(path);
        tokenizer tokens(path_string, sep);

        const TiXmlElement* v = &value;

        for (tokenizer::iterator ite = tokens.begin();
            ite != tokens.end() && v != nullptr; ++ite)
        {
            v = v->FirstChildElement(ite->c_str());
        }
        return v;
    }

    template < typename T >
    bool get_value(const TiXmlElement& value, const char* path, const char* name, T& result)
    {
        const TiXmlElement* v = find_value(value, path);
        if(v)
            return xml_util::xml_cast(*v, name, result);
        else
            return false;
    }

}
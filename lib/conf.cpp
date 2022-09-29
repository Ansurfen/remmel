#include "../include/lib/conf.hpp"

using namespace remmel;

#define SetIValue(val) \
    SStream ss;        \
    ss << val;         \
    this->val = ss.str();

IValue::IValue()
{
}

IValue::~IValue() {}

IValue::IValue(bool val)
{
    this->val = val ? "true" : "false";
}

IValue::IValue(int val)
{
    SetIValue(val);
}

IValue::IValue(long val)
{
    SetIValue(val);
}

IValue::IValue(long long val)
{
    SetIValue(val);
}

IValue::IValue(float val)
{
    SetIValue(val);
}

IValue::IValue(double val)
{
    SetIValue(val);
}

IValue::IValue(const char *_val) : val(_val){};

IValue::IValue(const Str &_val) : val(_val){};

IValue::IValue(const FStr &_val) : val(_val){};

IValue::operator bool() const
{
    if (this->val == "true")
        return true;
    return false;
}

IValue::operator int() const
{
    return std::atoi(this->val.data());
}

IValue::operator long() const
{
    return std::atol(this->val.data());
}

IValue::operator long long() const
{
    return std::atoll(this->val.data());
}

IValue::operator float() const
{
    return std::atof(this->val.data());
}

IValue::operator double() const
{
    return std::atof(this->val.data());
}

IValue::operator const char *() const
{
    return this->val.data();
}

IValue::operator Str() const
{
    return this->val.data();
}

IValue::operator FStr() const
{
    return this->val.data();
}

void IValue::operator=(bool val)
{
    this->val = val ? "true" : "false";
}

void IValue::operator=(int val)
{
    SetIValue(val);
}

void IValue::operator=(long val)
{
    SetIValue(val);
}

void IValue::operator=(long long val)
{
    SetIValue(val);
}

void IValue::operator=(float val)
{
    SetIValue(val);
}

void IValue::operator=(double val)
{
    SetIValue(val);
}

void IValue::operator=(const char *val)
{
    this->val = val;
}

void IValue::operator=(const Str &val)
{
    this->val = val;
}

void IValue::operator=(const FStr &val)
{
    this->val = val;
}

IniEngine::IniEngine() {}

IniEngine::IniEngine(const char *filename)
{
    this->Reset();
    Ifstream fp(filename);
    if (!fp.is_open())
    {
        Cout << "fail to open the file" << Endl;
        return;
    }
    Str line, name;
    while (std::getline(fp, line))
    {
        line = Strip(line);
        // skip empty line and comment
        if (!line.length() || line[0] == '#')
            continue;
        if (line[0] == '[') // it's section like [SECTION]
        {
            int pos = line.find_first_of(']');
            if (pos < 0)
                return;
            name = Strip(line.substr(1, pos - 1));
            this->sections[name] = section();
        }
        else // it's key and value like key=value
        {
            int pos = line.find_first_of('=');
            if (pos < 0)
                return;
            Str k = Strip(line.substr(0, pos));
            Str v = Strip(line.substr(pos + 1, line.size() - pos - 1));
            this->sections[name][k] = IValue(v.data());
        }
    }
    fp.close();
}

IniEngine::~IniEngine() {}

IniEngine::section &IniEngine::operator[](const char *section)
{
    return this->sections[section];
}

bool IniEngine::Has(const char *section)
{
    return this->sections.find(section) == this->sections.end() ? false : true;
}

bool IniEngine::Has(const char *section, const char *key)
{
    return this->sections[section].find(key) == this->sections[section].end() ? false : true;
}

void IniEngine::Set(const char *k, IValue v)
{
    FStr str(k);
    int pos = str.find_first_of('.');
    if (pos < 0)
        return;
    this->Set(str.substr(0, pos).data(), str.substr(pos + 1, str.size() - pos - 1).data(), v);
}

void IniEngine::Set(const char *s, const char *key, IValue v)
{
    if (!this->Has(s))
        this->sections[s] = section();
    this->sections[s][key] = v;
}

FStr IniEngine::ToStr()
{
    SStream ss;
    for (Map<FStr, section>::iterator it = this->sections.begin(); it != this->sections.end(); it++)
    {
        ss << "[" << it->first << "]" << Endl;
        for (section::iterator sub_it = it->second.begin(); sub_it != it->second.end(); sub_it++)
            ss << sub_it->first << "=" << sub_it->second.operator const char *() << Endl;
        ss << Endl;
    }
    return ss.str();
}

void IniEngine::Reset()
{
    this->sections.clear();
}

void IniEngine::Del(const char *section)
{
    this->sections.erase(section);
}

void IniEngine::Del(const char *section, const char *key)
{
    this->sections[key].erase(section);
}
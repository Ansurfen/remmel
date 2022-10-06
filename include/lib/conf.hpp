#ifndef __REMMEL_CONF__
#define __REMMEL_CONF__

#include "io.hpp"

namespace remmel
{
    class IValue
    {
    private:
        Str val;

    public:
        IValue();
        IValue(bool);
        IValue(int);
        IValue(long);
        IValue(long long);
        IValue(float);
        IValue(double);
        IValue(CStr);
        IValue(const Str &);
        IValue(const FStr &);
        ~IValue();

        void operator=(bool);
        void operator=(int);
        void operator=(long);
        void operator=(long long);
        void operator=(float);
        void operator=(double);
        void operator=(CStr);
        void operator=(const Str &);
        void operator=(const FStr &);

        operator bool() const;
        operator int() const;
        operator long() const;
        operator long long() const;
        operator float() const;
        operator double() const;
        operator CStr() const;
        operator Str() const;
        operator FStr() const;
    };

    class IniEngine : public FileEngine
    {
        using section = HashMap<FStr, IValue>;

    private:
        Map<FStr, section> sections;

    public:
        IniEngine();
        IniEngine(CStr);
        ~IniEngine();
        section &operator[](CStr);
        FStr ToStr();
        bool Has(CStr);
        bool Has(CStr, CStr);
        void Set(CStr, IValue);
        void Set(CStr, CStr, IValue);
        void Reset();
        void Del(CStr);
        void Del(CStr, CStr);
        void Write();
        void Write(CStr);
    };
}

#endif
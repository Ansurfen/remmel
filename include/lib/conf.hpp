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
        IValue(const char *);
        IValue(const Str &);
        IValue(const FStr &);
        ~IValue();

        void operator=(bool);
        void operator=(int);
        void operator=(long);
        void operator=(long long);
        void operator=(float);
        void operator=(double);
        void operator=(const char *);
        void operator=(const Str &);
        void operator=(const FStr &);

        operator bool() const;
        operator int() const;
        operator long() const;
        operator long long() const;
        operator float() const;
        operator double() const;
        operator const char *() const;
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
        IniEngine(const char *);
        ~IniEngine();
        section &operator[](const char *);
        FStr ToStr();
        bool Has(const char *);
        bool Has(const char *, const char *);
        void Set(const char *, IValue);
        void Set(const char *, const char *, IValue);
        void Reset();
        void Del(const char *);
        void Del(const char *, const char *);
        void Write();
        void Write(const char *);
    };
}

#endif
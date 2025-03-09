const int mod;

struct intmod{
    int a;
    intmod() : a(0){}
    intmod(int a) : a(a){}
    intmod operator + (const intmod & c) const {
        return (a + c.a >= mod) ? a + c.a - mod : a + c.a;
    }
    intmod operator += (const intmod & c){
        *this = *this + c;
        return *this;
    }
    intmod operator - (const intmod & c) const {
        return (a - c.a < 0) ? a - c.a + mod : a - c.a;
    }
    intmod operator -= (const intmod & c){
        *this = *this - c;
        return *this;
    }
    intmod operator * (const intmod & c) const {
        return int((ll(a) * ll(c.a)) % mod);
    }
    intmod operator *= (const intmod & c){
        *this = *this * c;
        return *this;
    }
};

istream &operator>>(istream &is, intmod & p){return is >> p.a;}
ostream &operator<<(ostream &os, const intmod & p){return os << p.a;}

intmod expbin(intmod b, ll e){
    intmod a(1);
    while(e){
        if(e & 1LL) a *= b;
        b *= b;
        e >>= 1LL;
    }
    return a;
}

intmod inverse(intmod a){
    return expbin(a, mod - 2);
}

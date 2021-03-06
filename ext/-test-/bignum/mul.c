#include "ruby.h"
#include "internal.h"

static VALUE
big(VALUE x)
{
    if (FIXNUM_P(x))
        return rb_int2big(FIX2LONG(x));
    if (RB_TYPE_P(x, T_BIGNUM))
        return x;
    rb_raise(rb_eTypeError, "can't convert %s to Bignum",
            rb_obj_classname(x));
}

static VALUE
mul_normal(VALUE x, VALUE y)
{
    return rb_big_norm(rb_big_mul_normal(big(x), big(y)));
}

static VALUE
mul_balance(VALUE x, VALUE y)
{
    return rb_big_norm(rb_big_mul_balance(big(x), big(y)));
}

static VALUE
mul_karatsuba(VALUE x, VALUE y)
{
    return rb_big_norm(rb_big_mul_karatsuba(big(x), big(y)));
}

void
Init_mul(VALUE klass)
{
    rb_define_const(rb_cBignum, "SIZEOF_BDIGITS", INT2NUM(SIZEOF_BDIGITS));
    rb_define_const(rb_cBignum, "BITSPERDIG", INT2NUM(SIZEOF_BDIGITS * CHAR_BIT));
    rb_define_method(rb_cInteger, "big_mul_normal", mul_normal, 1);
    rb_define_method(rb_cInteger, "big_mul_balance", mul_balance, 1);
    rb_define_method(rb_cInteger, "big_mul_karatsuba", mul_karatsuba, 1);
}

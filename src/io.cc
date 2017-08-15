#include "io.h"

#include <xemmai/derived.h>
#include <xemmai/engine.h>

namespace xemmaix
{

namespace libxml
{

size_t t_http::f_read(t_bytes& a_bytes, size_t a_offset, size_t a_size)
{
	if (a_offset + a_size > a_bytes.f_size()) t_throwable::f_throw(L"out of range.");
	t_safe_region region;
	return t_curl::f_read(reinterpret_cast<char*>(&a_bytes[0] + a_offset), a_size);
}

}

}

namespace xemmai
{

void t_type_of<xemmaix::libxml::t_http>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::libxml;
	t_define<t_http, t_object>(a_extension, L"Http")
		(t_construct<const std::wstring&>())
		(L"close", t_member<void(t_http::*)(), &t_http::f_close, t_with_lock_for_write>())
		(L"read", t_member<size_t(t_http::*)(t_bytes&, size_t, size_t), &t_http::f_read, t_with_lock_for_write>())
	;
}

t_type* t_type_of<xemmaix::libxml::t_http>::f_derive(t_object* a_this)
{
	return new t_derived<t_type_of>(v_module, a_this);
}

void t_type_of<xemmaix::libxml::t_http>::f_finalize(t_object* a_this)
{
	delete &f_as<xemmaix::libxml::t_http&>(a_this);
}

t_scoped t_type_of<xemmaix::libxml::t_http>::f_construct(t_object* a_class, t_stacked* a_stack, size_t a_n)
{
	return t_construct<const std::wstring&>::t_bind<xemmaix::libxml::t_http>::f_do(a_class, a_stack, a_n);
}

}

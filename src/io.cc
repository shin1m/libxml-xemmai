#include "io.h"

#include <xemmai/derived.h>
#include <xemmai/engine.h>

namespace xemmaix::libxml
{

size_t t_http::f_read(t_bytes& a_bytes, size_t a_offset, size_t a_size)
{
	if (a_offset + a_size > a_bytes.f_size()) f_throw(L"out of range."sv);
	t_safe_region region;
	return t_curl::f_read(reinterpret_cast<char*>(&a_bytes[0] + a_offset), a_size);
}

}

namespace xemmai
{

void t_type_of<xemmaix::libxml::t_http>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::libxml;
	t_define<t_http, t_object>(a_extension, L"Http"sv)
		(t_construct<false, std::wstring_view>())
		(L"close"sv, t_member<void(t_http::*)(), &t_http::f_close, t_with_lock_for_write>())
		(L"read"sv, t_member<size_t(t_http::*)(t_bytes&, size_t, size_t), &t_http::f_read, t_with_lock_for_write>())
	;
}

t_scoped t_type_of<xemmaix::libxml::t_http>::f_do_construct(t_stacked* a_stack, size_t a_n)
{
	return t_construct<false, std::wstring_view>::t_bind<xemmaix::libxml::t_http>::f_do(this, a_stack, a_n);
}

}

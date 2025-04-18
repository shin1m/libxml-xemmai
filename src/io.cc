#include "io.h"

#include <xemmai/engine.h>

namespace xemmaix::libxml
{

size_t t_http::f_read(t_bytes& a_bytes, size_t a_offset, size_t a_size)
{
	f_owned_or_throw();
	if (a_offset + a_size > a_bytes.f_size()) f_throw(L"out of range."sv);
	t_safe_region region;
	return t_curl::f_read(reinterpret_cast<char*>(&a_bytes[0] + a_offset), a_size);
}

}

namespace xemmai
{

void t_type_of<xemmaix::libxml::t_http>::f_define(t_library* a_library)
{
	using namespace xemmaix::libxml;
	t_define{a_library}
	(L"close"sv, t_member<void(t_http::*)(), &t_http::f_close>())
	(L"read"sv, t_member<size_t(t_http::*)(t_bytes&, size_t, size_t), &t_http::f_read>())
	.f_derive<t_http, t_object>();
}

t_pvalue t_type_of<xemmaix::libxml::t_http>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_construct<std::wstring_view>::t_bind<xemmaix::libxml::t_http>::f_do(this, a_stack, a_n);
}

}

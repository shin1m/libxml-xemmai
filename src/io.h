#ifndef XEMMAIX__LIBXML__IO_H
#define XEMMAIX__LIBXML__IO_H

#include "libxml.h"
#include "curl.h"

namespace xemmaix
{

namespace libxml
{

class t_http : t_utf8_converter, t_curl
{
	friend struct xemmai::t_type_of<t_http>;

public:
	t_http(const std::wstring& a_uri) : t_curl(f_convert(a_uri).c_str())
	{
	}
	void f_close()
	{
		t_curl::f_close();
	}
	size_t f_read(t_bytes& a_bytes, size_t a_offset, size_t a_size);
};

}

}

namespace xemmai
{

template<>
struct t_type_of<xemmaix::libxml::t_http> : t_type
{
	typedef xemmaix::libxml::t_extension t_extension;

	static void f_define(t_extension* a_extension);

	using t_type::t_type;
	virtual t_type* f_derive(t_object* a_this);
	virtual void f_finalize(t_object* a_this);
	virtual t_scoped f_construct(t_object* a_class, t_stacked* a_stack, size_t a_n);
};

}

#endif

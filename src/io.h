#ifndef XEMMAIX__LIBXML__IO_H
#define XEMMAIX__LIBXML__IO_H

#include "libxml.h"
#include "curl.h"

namespace xemmaix::libxml
{

class t_http : t_owned, t_utf8_converter, t_curl
{
	friend struct xemmai::t_type_of<t_http>;

public:
	t_http(std::wstring_view a_uri) : t_curl(f_convert(a_uri).c_str())
	{
	}
	void f_close()
	{
		f_owned_or_throw();
		t_curl::f_close();
	}
	size_t f_read(t_bytes& a_bytes, size_t a_offset, size_t a_size);
};

}

namespace xemmai
{

template<>
struct t_type_of<xemmaix::libxml::t_http> : t_derivable<t_holds<xemmaix::libxml::t_http>>
{
	using t_library = xemmaix::libxml::t_library;

	static void f_define(t_library* a_library);

	using t_base::t_base;
	t_pvalue f_do_construct(t_pvalue* a_stack, size_t a_n);
};

}

#endif

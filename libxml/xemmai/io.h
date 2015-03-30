#ifndef LIBXML__XEMMAI__IO_H
#define LIBXML__XEMMAI__IO_H

#include "libxml.h"

namespace libxml
{

namespace xemmai
{

class t_http : t_utf8_converter
{
	friend struct xemmai::t_type_of<t_http>;

	void* v_stream;

public:
	t_http(const std::wstring& a_uri);
	~t_http()
	{
		if (v_stream != NULL) xmlIOHTTPClose(v_stream);
	}
	void f_close();
	size_t f_read(t_bytes& a_bytes, size_t a_offset, size_t a_size);
};

}

}

namespace xemmai
{

using libxml::xemmai::t_http;

template<>
struct t_type_of<t_http> : t_type
{
	typedef libxml::xemmai::t_extension t_extension;

	static void f_define(t_extension* a_extension);

	using t_type::t_type;
	virtual t_type* f_derive(t_object* a_this);
	virtual void f_finalize(t_object* a_this);
	virtual t_scoped f_construct(t_object* a_class, t_scoped* a_stack, size_t a_n);
};

}

#endif

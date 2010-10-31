#ifndef LIBXML__XEMMAI__IO_H
#define LIBXML__XEMMAI__IO_H

#include "libxml.h"

namespace libxml
{

namespace xemmai
{

class t_http
{
	friend struct t_type_of<t_http>;

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

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_type(a_module, a_super)
	{
	}
	virtual t_type* f_derive(t_object* a_this);
	virtual void f_finalize(t_object* a_this);
	virtual void f_construct(t_object* a_class, size_t a_n);
};

}

#endif

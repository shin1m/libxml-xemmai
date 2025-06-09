#ifndef XEMMAIX__LIBXML__LIBXML_H
#define XEMMAIX__LIBXML__LIBXML_H

#include <xemmai/convert.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>

namespace xemmaix::libxml
{

using namespace xemmai;

class t_library;
class t_text_reader;
class t_text_writer;
class t_http;

template<typename C0, typename C1>
struct t_converter : private portable::t_iconv
{
	using portable::t_iconv::t_iconv;
	int f_to(char** a_p, size_t* a_n, auto a_out) const
	{
		char cs[16];
		char* p = cs;
		size_t n = sizeof(cs);
		while (iconv(v_cd, a_p, a_n, &p, &n) == size_t(-1)) {
			auto e = errno;
			if (e == EINTR) continue;
			a_out(reinterpret_cast<const C1*>(cs), (p - cs) / sizeof(C1));
			if (e != E2BIG) return e;
			p = cs;
			n = sizeof(cs);
		}
		a_out(reinterpret_cast<const C1*>(cs), (p - cs) / sizeof(C1));
		return 0;
	}
	std::basic_string<C1> operator()(std::basic_string_view<C0> a_x) const
	{
		std::basic_string<C1> s;
		auto p = reinterpret_cast<char*>(const_cast<C0*>(a_x.data()));
		size_t n = a_x.size() * sizeof(C0);
		auto append = [&](auto a_p, auto a_n)
		{
			s.append(a_p, a_p + a_n);
		};
		auto e = f_to(&p, &n, append);
		if (e == 0) e = f_to(nullptr, nullptr, append);
		if (e == 0) return s;
		throw std::system_error(e, std::generic_category());
	}
};

class t_utf8_converter
{
	t_converter<wchar_t, char> v_to;
	t_converter<char, wchar_t> v_from;

public:
	t_utf8_converter() : v_to("utf-8", "wchar_t"), v_from("wchar_t", "utf-8")
	{
	}
	std::string f_convert(std::wstring_view a_x) const
	{
		return v_to(a_x);
	}
	std::wstring f_convert(std::string_view a_x) const
	{
		return v_from(a_x);
	}
};

/*
class t_entry
{
protected:
	t_entry* v_previous;
	t_entry* v_next;

	t_entry(bool) : v_previous(this), v_next(this)
	{
	}
	t_entry();
	void f_unlink()
	{
		v_previous->v_next = v_next;
		v_next->v_previous = v_previous;
		v_previous = v_next = nullptr;
	}

public:
	virtual void f_dispose();
};

class t_session : public t_entry
{
	friend class t_proxy;

	static XEMMAI__PORTABLE__THREAD t_session* v_instance;

	t_library* v_library;

public:
	static t_session* f_instance()
	{
		if (!v_instance) f_throw(L"must be inside main."sv);
		return v_instance;
	}

	t_session(t_library* a_library);
	~t_session();
	t_library* f_library() const
	{
		return v_library;
	}
};

class t_proxy : public t_entry
{
	t_session* v_session;
	t_scoped v_object;

protected:
	static void f_destroy(void* a_p)
	{
		static_cast<t_proxy*>(a_p)->f_destroy();
	}
	static t_scoped f_transfer(t_proxy* a_proxy)
	{
		++a_proxy->v_n;
		return a_proxy->v_object;
	}

	size_t v_n = 0;

	t_proxy(t_type* a_class) : v_session(t_session::f_instance()), v_object(t_object::f_allocate(a_class, false))
	{
		v_object.f_pointer__(this);
	}
	virtual void f_destroy();

public:
	virtual ~t_proxy() = default;
	bool f_valid() const
	{
		return v_session == t_session::v_instance;
	}
	t_object* f_object() const
	{
		return v_object;
	}
};
*/

class t_library : public xemmai::t_library
{
	t_slot_of<t_type> v_type_parser_severities;
	t_slot_of<t_type> v_type_text_reader_mode;
	t_slot_of<t_type> v_type_parser_properties;
	t_slot_of<t_type> v_type_reader_types;
	t_slot_of<t_type> v_type_text_reader;
	t_slot_of<t_type> v_type_text_writer;
	t_slot_of<t_type> v_type_http;

public:
	using xemmai::t_library::t_library;
	virtual ~t_library();
	XEMMAI__LIBRARY__MEMBERS
};

XEMMAI__LIBRARY__BASE(t_library, t_global, f_global())
XEMMAI__LIBRARY__TYPE_AS(t_library, xmlParserSeverities, parser_severities)
XEMMAI__LIBRARY__TYPE_AS(t_library, xmlTextReaderMode, text_reader_mode)
XEMMAI__LIBRARY__TYPE_AS(t_library, xmlParserProperties, parser_properties)
XEMMAI__LIBRARY__TYPE_AS(t_library, xmlReaderTypes, reader_types)
XEMMAI__LIBRARY__TYPE(t_library, text_reader)
XEMMAI__LIBRARY__TYPE(t_library, text_writer)
XEMMAI__LIBRARY__TYPE(t_library, http)

}

#endif

#ifndef XEMMAIX__LIBXML__LIBXML_H
#define XEMMAIX__LIBXML__LIBXML_H

#include <codecvt>
#include <iterator>
#include <locale>
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

class t_utf8_converter
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> v_convert;

public:
	std::string f_convert(std::wstring_view a_x)
	{
		return v_convert.to_bytes(a_x.data(), a_x.data() + a_x.size());
	}
	std::wstring f_convert(std::string_view a_x)
	{
		return v_convert.from_bytes(a_x.data(), a_x.data() + a_x.size());
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
	virtual void f_scan(t_scan a_scan);
	virtual std::vector<std::pair<t_root, t_rvalue>> f_define();
	template<typename T>
	const T* f_library() const
	{
		return f_global();
	}
	template<typename T>
	t_slot_of<t_type>& f_type_slot()
	{
		return f_global()->f_type_slot<T>();
	}
	template<typename T>
	t_type* f_type() const
	{
		return const_cast<t_library*>(this)->f_type_slot<T>();
	}
	template<typename T>
	t_pvalue f_as(T&& a_value) const
	{
		typedef t_type_of<typename t_fundamental<T>::t_type> t;
		return t::f_transfer(f_library<typename t::t_library>(), std::forward<T>(a_value));
	}
};

template<>
inline const t_library* t_library::f_library<t_library>() const
{
	return this;
}

XEMMAI__LIBRARY__TYPE_AS(t_library, xmlParserSeverities, parser_severities)
XEMMAI__LIBRARY__TYPE_AS(t_library, xmlTextReaderMode, text_reader_mode)
XEMMAI__LIBRARY__TYPE_AS(t_library, xmlParserProperties, parser_properties)
XEMMAI__LIBRARY__TYPE_AS(t_library, xmlReaderTypes, reader_types)
XEMMAI__LIBRARY__TYPE(t_library, text_reader)
XEMMAI__LIBRARY__TYPE(t_library, text_writer)
XEMMAI__LIBRARY__TYPE(t_library, http)

}

#endif

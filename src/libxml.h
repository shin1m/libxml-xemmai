#ifndef XEMMAIX__LIBXML__LIBXML_H
#define XEMMAIX__LIBXML__LIBXML_H

#include <codecvt>
#include <iterator>
#include <locale>
#include <xemmai/convert.h>
#include <xemmai/array.h>
#include <xemmai/bytes.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>

namespace xemmaix::libxml
{

using namespace xemmai;

class t_extension;
class t_text_reader;
class t_text_writer;
class t_http;

class t_utf8_converter
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> v_convert;

public:
	std::string f_convert(const std::wstring& a_string)
	{
		return v_convert.to_bytes(a_string);
	}
	std::wstring f_convert(const std::string& a_string)
	{
		return v_convert.from_bytes(a_string);
	}
};

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

	t_extension* v_extension;

public:
	static t_session* f_instance()
	{
		if (!v_instance) t_throwable::f_throw(L"must be inside main.");
		return v_instance;
	}

	t_session(t_extension* a_extension);
	~t_session();
	t_extension* f_extension() const
	{
		return v_extension;
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

	t_proxy(t_object* a_class) : v_session(t_session::f_instance()), v_object(t_object::f_allocate(a_class))
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

class t_extension : public xemmai::t_extension
{
	template<typename T, typename T_super> friend class xemmai::t_define;

	t_slot v_type_parser_severities;
	t_slot v_type_text_reader_mode;
	t_slot v_type_parser_properties;
	t_slot v_type_reader_types;
	t_slot v_type_text_reader;
	t_slot v_type_text_writer;
	t_slot v_type_http;

	template<typename T>
	void f_type__(t_scoped&& a_type);

public:
	t_extension(t_object* a_module);
	virtual ~t_extension();
	virtual void f_scan(t_scan a_scan);
	template<typename T>
	const T* f_extension() const
	{
		return f_global();
	}
	template<typename T>
	t_object* f_type() const
	{
		return f_global()->f_type<T>();
	}
	template<typename T>
	t_scoped f_as(T&& a_value) const
	{
		typedef t_type_of<typename t_fundamental<T>::t_type> t;
		return t::f_transfer(f_extension<typename t::t_extension>(), std::forward<T>(a_value));
	}
};

template<>
inline void t_extension::f_type__<xmlParserSeverities>(t_scoped&& a_type)
{
	v_type_parser_severities = std::move(a_type);
}

template<>
inline void t_extension::f_type__<xmlTextReaderMode>(t_scoped&& a_type)
{
	v_type_parser_severities = std::move(a_type);
}

template<>
inline void t_extension::f_type__<xmlParserProperties>(t_scoped&& a_type)
{
	v_type_parser_severities = std::move(a_type);
}

template<>
inline void t_extension::f_type__<xmlReaderTypes>(t_scoped&& a_type)
{
	v_type_parser_severities = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_text_reader>(t_scoped&& a_type)
{
	v_type_text_reader = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_text_writer>(t_scoped&& a_type)
{
	v_type_text_writer = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_http>(t_scoped&& a_type)
{
	v_type_http = std::move(a_type);
}

template<>
inline const t_extension* t_extension::f_extension<t_extension>() const
{
	return this;
}

template<>
inline t_object* t_extension::f_type<xmlParserSeverities>() const
{
	return v_type_parser_severities;
}

template<>
inline t_object* t_extension::f_type<xmlTextReaderMode>() const
{
	return v_type_parser_severities;
}

template<>
inline t_object* t_extension::f_type<xmlParserProperties>() const
{
	return v_type_parser_severities;
}

template<>
inline t_object* t_extension::f_type<xmlReaderTypes>() const
{
	return v_type_parser_severities;
}

template<>
inline t_object* t_extension::f_type<t_text_reader>() const
{
	return v_type_text_reader;
}

template<>
inline t_object* t_extension::f_type<t_text_writer>() const
{
	return v_type_text_writer;
}

template<>
inline t_object* t_extension::f_type<t_http>() const
{
	return v_type_http;
}

}

#endif

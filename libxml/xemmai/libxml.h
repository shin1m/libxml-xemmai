#ifndef LIBXML__XEMMAI__LIBXML_H
#define LIBXML__XEMMAI__LIBXML_H

#include <xemmai/convert.h>
#include <xemmai/array.h>
#include <xemmai/bytes.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>

namespace libxml
{

namespace xemmai
{

using ::xemmai::t_object;
using ::xemmai::t_scan;
using ::xemmai::t_value;
using ::xemmai::t_transfer;
using ::xemmai::t_scoped;
using ::xemmai::t_slot;
using ::xemmai::t_fundamental;
using ::xemmai::t_type_of;
using ::xemmai::f_check;
using ::xemmai::f_as;
using ::xemmai::t_define;
using ::xemmai::f_global;
using ::xemmai::t_throwable;
using ::xemmai::t_array;
using ::xemmai::t_bytes;
using ::xemmai::portable::f_convert;

class t_extension;
class t_text_reader;
class t_text_writer;
class t_http;

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
		v_previous = v_next = 0;
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
	static t_transfer f_transfer(t_proxy* a_proxy)
	{
		++a_proxy->v_n;
		return a_proxy->v_object;
	}

	size_t v_n;

	t_proxy(t_object* a_class) : v_session(t_session::f_instance()), v_object(t_object::f_allocate(a_class)), v_n(0)
	{
		v_object.f_pointer__(this);
	}
	virtual void f_destroy();

public:
	virtual ~t_proxy();
	bool f_valid() const
	{
		return v_session == t_session::v_instance;
	}
	t_object* f_object() const
	{
		return v_object.f_object();
	}
};

class t_extension : public ::xemmai::t_extension
{
	template<typename T, typename T_super> friend class t_define;

	t_slot v_type_parser_severities;
	t_slot v_type_text_reader_mode;
	t_slot v_type_parser_properties;
	t_slot v_type_reader_types;
	t_slot v_type_text_reader;
	t_slot v_type_text_writer;
	t_slot v_type_http;

	template<typename T>
	void f_type__(const t_transfer& a_type);

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
	t_transfer f_as(const T& a_value) const
	{
		typedef t_type_of<typename t_fundamental<T>::t_type> t;
		return t::f_transfer(f_extension<typename t::t_extension>(), a_value);
	}
};

template<>
inline void t_extension::f_type__<xmlParserSeverities>(const t_transfer& a_type)
{
	v_type_parser_severities = a_type;
}

template<>
inline void t_extension::f_type__<xmlTextReaderMode>(const t_transfer& a_type)
{
	v_type_parser_severities = a_type;
}

template<>
inline void t_extension::f_type__<xmlParserProperties>(const t_transfer& a_type)
{
	v_type_parser_severities = a_type;
}

template<>
inline void t_extension::f_type__<xmlReaderTypes>(const t_transfer& a_type)
{
	v_type_parser_severities = a_type;
}

template<>
inline void t_extension::f_type__<t_text_reader>(const t_transfer& a_type)
{
	v_type_text_reader = a_type;
}

template<>
inline void t_extension::f_type__<t_text_writer>(const t_transfer& a_type)
{
	v_type_text_writer = a_type;
}

template<>
inline void t_extension::f_type__<t_http>(const t_transfer& a_type)
{
	v_type_http = a_type;
}

template<>
inline const t_extension* t_extension::f_extension<t_extension>() const
{
	return this;
}

template<>
inline t_object* t_extension::f_type<xmlParserSeverities>() const
{
	return v_type_parser_severities.f_object();
}

template<>
inline t_object* t_extension::f_type<xmlTextReaderMode>() const
{
	return v_type_parser_severities.f_object();
}

template<>
inline t_object* t_extension::f_type<xmlParserProperties>() const
{
	return v_type_parser_severities.f_object();
}

template<>
inline t_object* t_extension::f_type<xmlReaderTypes>() const
{
	return v_type_parser_severities.f_object();
}

template<>
inline t_object* t_extension::f_type<t_text_reader>() const
{
	return v_type_text_reader.f_object();
}

template<>
inline t_object* t_extension::f_type<t_text_writer>() const
{
	return v_type_text_writer.f_object();
}

template<>
inline t_object* t_extension::f_type<t_http>() const
{
	return v_type_http.f_object();
}

}

}

#endif

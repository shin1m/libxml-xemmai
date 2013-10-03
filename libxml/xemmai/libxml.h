#ifndef LIBXML__XEMMAI__LIBXML_H
#define LIBXML__XEMMAI__LIBXML_H

#include <cerrno>
#include <iterator>
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
using ::xemmai::t_slot;
using ::xemmai::t_scoped;
using ::xemmai::t_fundamental;
using ::xemmai::t_type_of;
using ::xemmai::f_check;
using ::xemmai::f_as;
using ::xemmai::t_define;
using ::xemmai::f_global;
using ::xemmai::t_throwable;
using ::xemmai::t_array;
using ::xemmai::t_bytes;

class t_extension;
class t_text_reader;
class t_text_writer;
class t_http;

template<typename C0, typename C1, size_t N = 256>
class t_converter
{
	iconv_t v_cd;

public:
	t_converter(const char* a_from, const char* a_to) : v_cd(iconv_open(a_to, a_from))
	{
	}
	~t_converter()
	{
		iconv_close(v_cd);
	}
	template<typename I, typename O>
	O operator()(I f, I l, O d) const;
};

template<typename C0, typename C1, size_t N>
template<typename I, typename O>
O t_converter<C0, C1, N>::operator()(I f, I l, O d) const
{
	char cs0[N];
	char cs1[N];
	char* p0 = cs0;
	while (f != l || p0 > cs0) {
		while (f != l && p0 + sizeof(C0) <= cs0 + sizeof(cs0)) {
			*reinterpret_cast<C0*>(p0) = *f;
			p0 += sizeof(C0);
			++f;
		}
		size_t n0 = p0 - cs0;
		p0 = cs0;
		char* p1 = cs1;
		size_t n1 = sizeof(cs1);
		do {
			size_t n = iconv(v_cd, &p0, &n0, &p1, &n1);
			if (n == static_cast<size_t>(-1)) {
				if (errno == EILSEQ) {
					if (n1 < sizeof(C1)) break;
					*reinterpret_cast<C1*>(p1) = '?';
					p1 += sizeof(C1);
					n1 -= sizeof(C1);
				} else if (errno == EINVAL) {
					if (p0 > cs0) break;
				} else {
					break;
				}
				p0 += sizeof(C0);
				n0 -= sizeof(C0);
			}
		} while (n0 > 0);
		d = std::copy(reinterpret_cast<const C1*>(cs1), reinterpret_cast<const C1*>(p1), d);
		p0 = std::copy(p0, p0 + n0, static_cast<char*>(cs0));
	}
	char* p1 = cs1;
	size_t n1 = sizeof(cs1);
	if (iconv(v_cd, NULL, NULL, &p1, &n1) != static_cast<size_t>(-1)) d = std::copy(reinterpret_cast<const C1*>(cs1), reinterpret_cast<const C1*>(p1), d);
	return d;
}

class t_utf8_converter
{
	t_converter<wchar_t, char> v_encoder{"wchar_t", "utf-8"};
	t_converter<char, wchar_t> v_decoder{"utf-8", "wchar_t"};

public:
	std::string f_convert(const std::wstring& a_string) const
	{
		std::vector<char> cs;
		v_encoder(a_string.begin(), a_string.end(), std::back_inserter(cs));
		return std::string(cs.begin(), cs.end());
	}
	std::wstring f_convert(const std::string& a_string) const
	{
		std::vector<wchar_t> cs;
		v_decoder(a_string.begin(), a_string.end(), std::back_inserter(cs));
		return std::wstring(cs.begin(), cs.end());
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

	static thread_local t_session* v_instance;

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
	virtual ~t_proxy();
	bool f_valid() const
	{
		return v_session == t_session::v_instance;
	}
	t_object* f_object() const
	{
		return v_object;
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
	t_scoped f_as(const T& a_value) const
	{
		typedef t_type_of<typename t_fundamental<T>::t_type> t;
		return t::f_transfer(f_extension<typename t::t_extension>(), a_value);
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

}

#endif

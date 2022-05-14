#include "reader.h"
#include "writer.h"
#include "io.h"

namespace xemmaix::libxml
{

/*
t_entry::t_entry() : v_previous(t_session::f_instance()), v_next(v_previous->v_next)
{
	v_previous->v_next = v_next->v_previous = this;
}

void t_entry::f_dispose()
{
	f_unlink();
}

XEMMAI__PORTABLE__THREAD t_session* t_session::v_instance;

t_session::t_session(t_library* a_library) : t_entry(false), v_library(a_library)
{
	if (v_instance) f_throw(L"already inside main."sv);
	v_instance = this;
}

t_session::~t_session()
{
	while (v_next != this) v_next->f_dispose();
	v_instance = nullptr;
}

void t_proxy::f_destroy()
{
	if (v_previous) f_unlink();
	v_object = nullptr;
}

namespace
{

void f_main(t_library* a_library, const t_pvalue& a_callable)
{
	t_session session(a_library);
	a_callable();
}

}
*/

t_library::~t_library()
{
	xmlCleanupParser();
}

void t_library::f_scan(t_scan a_scan)
{
	a_scan(v_type_parser_severities);
	a_scan(v_type_text_reader_mode);
	a_scan(v_type_parser_properties);
	a_scan(v_type_reader_types);
	a_scan(v_type_text_reader);
	a_scan(v_type_text_writer);
	a_scan(v_type_http);
}

std::vector<std::pair<t_root, t_rvalue>> t_library::f_define()
{
	xmlInitParser();
	t_type_of<t_text_reader>::f_define(this);
	t_type_of<t_text_writer>::f_define(this);
	t_type_of<t_http>::f_define(this);
	return t_define(this)
		(L"ParserSeverities"sv, t_type_of<xmlParserSeverities>::f_define(this))
		(L"TextReaderMode"sv, t_type_of<xmlTextReaderMode>::f_define(this))
		(L"ParserProperties"sv, t_type_of<xmlParserProperties>::f_define(this))
		(L"ReaderTypes"sv, t_type_of<xmlReaderTypes>::f_define(this))
		(L"TextReader"sv, static_cast<t_object*>(v_type_text_reader))
		(L"TextWriter"sv, static_cast<t_object*>(v_type_text_writer))
		(L"Http"sv, static_cast<t_object*>(v_type_http))
//		(L"main"sv, t_static<void(*)(t_library*, const t_pvalue&), f_main>())
	;
}

}

XEMMAI__MODULE__FACTORY(xemmai::t_library::t_handle* a_handle)
{
	return xemmai::f_new<xemmaix::libxml::t_library>(a_handle);
}

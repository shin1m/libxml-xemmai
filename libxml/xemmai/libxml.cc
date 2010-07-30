#include "reader.h"
#include "writer.h"
#include "io.h"

namespace libxml
{

namespace xemmai
{

using ::xemmai::f_define;

t_entry::t_entry()
{
	v_previous = t_session::f_instance();
	v_next = v_previous->v_next;
	v_previous->v_next = v_next->v_previous = this;
}

void t_entry::f_dispose()
{
	f_unlink();
}

XEMMAI__PORTABLE__THREAD t_session* t_session::v_instance;

t_session::t_session(t_extension* a_extension) : t_entry(false), v_extension(a_extension)
{
	if (v_instance) t_throwable::f_throw(L"already inside main.");
	v_instance = this;
}

t_session::~t_session()
{
	while (v_next != this) v_next->f_dispose();
	v_instance = 0;
}

void t_proxy::f_destroy()
{
	if (v_previous) f_unlink();
	v_object = 0;
}

t_proxy::~t_proxy()
{
}

namespace
{

void f_main(t_extension* a_extension, const t_value& a_callable)
{
	t_session session(a_extension);
	a_callable();
}

}

t_extension::t_extension(t_object* a_module) : ::xemmai::t_extension(a_module)
{
	xmlInitParser();
	t_type_of<xmlParserSeverities>::f_define(this);
	t_type_of<xmlTextReaderMode>::f_define(this);
	t_type_of<xmlParserProperties>::f_define(this);
	t_type_of<xmlReaderTypes>::f_define(this);
	t_type_of<t_text_reader>::f_define(this);
	t_type_of<t_text_writer>::f_define(this);
	t_type_of<t_http>::f_define(this);
	f_define<void (*)(t_extension*, const t_value&), f_main>(this, L"main");
}

t_extension::~t_extension()
{
	xmlCleanupParser();
}

void t_extension::f_scan(t_scan a_scan)
{
	a_scan(v_type_parser_severities);
	a_scan(v_type_text_reader_mode);
	a_scan(v_type_parser_properties);
	a_scan(v_type_reader_types);
	a_scan(v_type_text_reader);
	a_scan(v_type_text_writer);
	a_scan(v_type_http);
}

}

}

#ifdef _MSC_VER
extern "C" __declspec(dllexport) xemmai::t_extension* f_factory(xemmai::t_object* a_module)
#else
extern "C" xemmai::t_extension* f_factory(xemmai::t_object* a_module)
#endif
{
	return new libxml::xemmai::t_extension(a_module);
}

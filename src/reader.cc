#include "reader.h"

namespace xemmaix::libxml
{

namespace
{

struct t_context
{
	static int f_try(auto a_do, const char* a_at)
	{
		try {
			try {
				return a_do();
			} catch (const t_rvalue& thrown) {
				if (auto p = f_string_or_null(thrown)) {
					auto& s = p->f_as<t_string>();
					std::fprintf(stderr, "t_context::%s: caught: %.*ls\n", a_at, static_cast<int>(s.f_size()), static_cast<const wchar_t*>(s));
				} else {
					std::fprintf(stderr, "t_context::%s: caught <unprintable>\n", a_at);
				}
			}
		} catch (std::exception& e) {
			std::fprintf(stderr, "t_context::%s: caught %s\n", a_at, e.what());
		} catch (...) {
			std::fprintf(stderr, "t_context::%s: caught <unexpected>\n", a_at);
		}
		return -1;
	}
	static int f_read(void* a_context, char* a_p, int a_n)
	{
		return f_try([&]
		{
			auto p = static_cast<t_context*>(a_context);
			auto& bytes = f_as<t_bytes&>(p->v_bytes);
			if (a_n > bytes.f_size()) a_n = bytes.f_size();
			auto n = p->v_read(p->v_bytes, 0, a_n);
			f_check<int>(n, L"result of read");
			a_n = f_as<int>(n);
			std::copy_n(&bytes[0], a_n, a_p);
			return a_n;
		}, "f_read");
	}
	static int f_close(void* a_context)
	{
		auto p = static_cast<t_context*>(a_context);
		auto n = f_try([&]
		{
			p->v_close();
			return 0;
		}, "f_close");
		delete p;
		return n;
	}

	t_rvalue v_read;
	t_rvalue v_close;
	t_root v_bytes = t_bytes::f_instantiate(1024);
};

}

t_text_reader::t_text_reader(const t_pvalue& a_read, const t_pvalue& a_close, std::wstring_view a_url, std::wstring_view a_encoding, int a_options) : v_reader(xmlReaderForIO(t_context::f_read, t_context::f_close, new t_context{a_read, a_close}, f_convert(a_url).c_str(), f_convert(a_encoding).c_str(), a_options))
{
}

}

namespace xemmai
{

t_object* t_type_of<xmlParserSeverities>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"VALIDITY_WARNING"sv, XML_PARSER_SEVERITY_VALIDITY_WARNING)
		(L"VALIDITY_ERROR"sv, XML_PARSER_SEVERITY_VALIDITY_ERROR)
		(L"WARNING"sv, XML_PARSER_SEVERITY_WARNING)
		(L"ERROR"sv, XML_PARSER_SEVERITY_ERROR)
		;
	});
}

t_object* t_type_of<xmlTextReaderMode>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"INITIAL"sv, XML_TEXTREADER_MODE_INITIAL)
		(L"INTERACTIVE"sv, XML_TEXTREADER_MODE_INTERACTIVE)
		(L"ERROR"sv, XML_TEXTREADER_MODE_ERROR)
		(L"EOF"sv, XML_TEXTREADER_MODE_EOF)
		(L"CLOSED"sv, XML_TEXTREADER_MODE_CLOSED)
		(L"READING"sv, XML_TEXTREADER_MODE_READING)
		;
	});
}

t_object* t_type_of<xmlParserProperties>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"LOADDTD"sv, XML_PARSER_LOADDTD)
		(L"DEFAULTATTRS"sv, XML_PARSER_DEFAULTATTRS)
		(L"VALIDATE"sv, XML_PARSER_VALIDATE)
		(L"SUBST_ENTITIES"sv, XML_PARSER_SUBST_ENTITIES)
		;
	});
}

t_object* t_type_of<xmlReaderTypes>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"NONE"sv, XML_READER_TYPE_NONE)
		(L"ELEMENT"sv, XML_READER_TYPE_ELEMENT)
		(L"ATTRIBUTE"sv, XML_READER_TYPE_ATTRIBUTE)
		(L"TEXT"sv, XML_READER_TYPE_TEXT)
		(L"CDATA"sv, XML_READER_TYPE_CDATA)
		(L"ENTITY_REFERENCE"sv, XML_READER_TYPE_ENTITY_REFERENCE)
		(L"ENTITY"sv, XML_READER_TYPE_ENTITY)
		(L"PROCESSING_INSTRUCTION"sv, XML_READER_TYPE_PROCESSING_INSTRUCTION)
		(L"COMMENT"sv, XML_READER_TYPE_COMMENT)
		(L"DOCUMENT"sv, XML_READER_TYPE_DOCUMENT)
		(L"DOCUMENT_TYPE"sv, XML_READER_TYPE_DOCUMENT_TYPE)
		(L"DOCUMENT_FRAGMENT"sv, XML_READER_TYPE_DOCUMENT_FRAGMENT)
		(L"NOTATION"sv, XML_READER_TYPE_NOTATION)
		(L"WHITESPACE"sv, XML_READER_TYPE_WHITESPACE)
		(L"SIGNIFICANT_WHITESPACE"sv, XML_READER_TYPE_SIGNIFICANT_WHITESPACE)
		(L"END_ELEMENT"sv, XML_READER_TYPE_END_ELEMENT)
		(L"END_ENTITY"sv, XML_READER_TYPE_END_ENTITY)
		(L"XML_DECLARATION"sv, XML_READER_TYPE_XML_DECLARATION)
		;
	});
}

void t_type_of<xemmaix::libxml::t_text_reader>::f_define(t_library* a_library)
{
	using namespace xemmaix::libxml;
	t_define{a_library}
	(L"free"sv, t_member<void(t_text_reader::*)(), &t_text_reader::f_free>())
	(L"read"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_read>())
#ifdef LIBXML_WRITER_ENABLED
	(L"read_inner_xml"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_read_inner_xml>())
	(L"read_outer_xml"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_read_outer_xml>())
#endif
	(L"read_string"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_read_string>())
	(L"read_attribute_value"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_read_attribute_value>())
	(L"attribute_count"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_attribute_count>())
	(L"depth"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_depth>())
	(L"has_attributes"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_has_attributes>())
	(L"has_value"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_has_value>())
	(L"is_default"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_is_default>())
	(L"is_empty_element"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_is_empty_element>())
	(L"node_type"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_node_type>())
	(L"quote_character"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_quote_character>())
	(L"read_state"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_read_state>())
	(L"is_namespace_decl"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_is_namespace_decl>())
	(L"base_uri"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_base_uri>())
	(L"local_name"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_local_name>())
	(L"name"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_name>())
	(L"namespace_uri"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_namespace_uri>())
	(L"prefix"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_prefix>())
	(L"xml_lang"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_xml_lang>())
	(L"value"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_value>())
	(L"close"sv, t_member<void(t_text_reader::*)(), &t_text_reader::f_close>())
	(L"get_attribute_no"sv, t_member<std::wstring(t_text_reader::*)(int), &t_text_reader::f_get_attribute_no>())
	(L"get_attribute"sv, t_member<std::wstring(t_text_reader::*)(std::wstring_view), &t_text_reader::f_get_attribute>())
	(L"get_attribute_ns"sv, t_member<std::wstring(t_text_reader::*)(std::wstring_view, std::wstring_view), &t_text_reader::f_get_attribute_ns>())
	(L"lookup_namespace"sv, t_member<std::wstring(t_text_reader::*)(std::wstring_view), &t_text_reader::f_lookup_namespace>())
	(L"move_to_attribute_no"sv, t_member<bool(t_text_reader::*)(int), &t_text_reader::f_move_to_attribute_no>())
	(L"move_to_attribute"sv, t_member<bool(t_text_reader::*)(std::wstring_view), &t_text_reader::f_move_to_attribute>())
	(L"move_to_attribute_ns"sv, t_member<bool(t_text_reader::*)(std::wstring_view, std::wstring_view), &t_text_reader::f_move_to_attribute_ns>())
	(L"move_to_first_attribute"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_move_to_first_attribute>())
	(L"move_to_next_attribute"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_move_to_next_attribute>())
	(L"move_to_element"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_move_to_element>())
	(L"normalization"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_normalization>())
	(L"encoding"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_encoding>())
	(L"set_parser_property"sv, t_member<void(t_text_reader::*)(int, int), &t_text_reader::f_set_parser_property>())
	(L"get_parser_property"sv, t_member<int(t_text_reader::*)(int), &t_text_reader::f_get_parser_property>())
	(L"get_parser_line_number"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_get_parser_line_number>())
	(L"get_parser_column_number"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_get_parser_column_number>())
	(L"next"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_next>())
	(L"next_sibling"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_next_sibling>())
	(L"is_valid"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_is_valid>())
#ifdef LIBXML_SCHEMAS_ENABLED
	(L"relax_ng_validate"sv, t_member<void(t_text_reader::*)(std::wstring_view), &t_text_reader::f_relax_ng_validate>())
	(L"schema_validate"sv, t_member<void(t_text_reader::*)(std::wstring_view), &t_text_reader::f_schema_validate>())
#endif
	(L"xml_version"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_xml_version>())
	(L"standalone"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_standalone>())
	(L"byte_consumed"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_byte_consumed>())
	(L"new_file"sv, t_member<void(t_text_reader::*)(std::wstring_view, std::wstring_view, int), &t_text_reader::f_new_file>())
	.f_derive<t_text_reader, t_object>();
}

t_pvalue t_type_of<xemmaix::libxml::t_text_reader>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_overload<
		t_construct<std::wstring_view>,
		t_construct<std::wstring_view, std::wstring_view, int>,
		t_construct<const t_pvalue&, const t_pvalue&, std::wstring_view, std::wstring_view, int>
	>::t_bind<xemmaix::libxml::t_text_reader>::f_do(this, a_stack, a_n);
}

}

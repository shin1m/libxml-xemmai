#include "reader.h"

#include <algorithm>

namespace xemmaix::libxml
{

namespace
{

struct t_context
{
	static int f_read(void* a_context, char* a_p, int a_n)
	{
		auto p = static_cast<t_context*>(a_context);
		auto& bytes = f_as<t_bytes&>(p->v_bytes);
		if (a_n > bytes.f_size()) a_n = bytes.f_size();
		auto n = p->v_read(p->v_bytes, f_global()->f_as(0), f_global()->f_as(a_n));
		f_check<int>(n, L"result of read");
		a_n = f_as<int>(n);
		std::copy_n(&bytes[0], a_n, a_p);
		return a_n;
	}
	static int f_close(void* a_context)
	{
		auto p = static_cast<t_context*>(a_context);
		p->v_close();
		delete p;
		return 0;
	}

	t_scoped v_read;
	t_scoped v_close;
	t_scoped v_bytes = t_bytes::f_instantiate(1024);
};

}

t_text_reader::t_text_reader(const t_value& a_read, const t_value& a_close, std::wstring_view a_url, std::wstring_view a_encoding, int a_options) : v_reader(xmlReaderForIO(t_context::f_read, t_context::f_close, new t_context{a_read, a_close}, f_convert(a_url).c_str(), f_convert(a_encoding).c_str(), a_options))
{
}

}

namespace xemmai
{

void t_type_of<xmlParserSeverities>::f_define(t_extension* a_extension)
{
	t_define<xmlParserSeverities, intptr_t>(a_extension, L"ParserSeverities"sv)
		(L"VALIDITY_WARNING"sv, XML_PARSER_SEVERITY_VALIDITY_WARNING)
		(L"VALIDITY_ERROR"sv, XML_PARSER_SEVERITY_VALIDITY_ERROR)
		(L"WARNING"sv, XML_PARSER_SEVERITY_WARNING)
		(L"ERROR"sv, XML_PARSER_SEVERITY_ERROR)
	;
}

void t_type_of<xmlTextReaderMode>::f_define(t_extension* a_extension)
{
	t_define<xmlTextReaderMode, intptr_t>(a_extension, L"TextReaderMode"sv)
		(L"INITIAL"sv, XML_TEXTREADER_MODE_INITIAL)
		(L"INTERACTIVE"sv, XML_TEXTREADER_MODE_INTERACTIVE)
		(L"ERROR"sv, XML_TEXTREADER_MODE_ERROR)
		(L"EOF"sv, XML_TEXTREADER_MODE_EOF)
		(L"CLOSED"sv, XML_TEXTREADER_MODE_CLOSED)
		(L"READING"sv, XML_TEXTREADER_MODE_READING)
	;
}

void t_type_of<xmlParserProperties>::f_define(t_extension* a_extension)
{
	t_define<xmlParserProperties, intptr_t>(a_extension, L"ParserProperties"sv)
		(L"LOADDTD"sv, XML_PARSER_LOADDTD)
		(L"DEFAULTATTRS"sv, XML_PARSER_DEFAULTATTRS)
		(L"VALIDATE"sv, XML_PARSER_VALIDATE)
		(L"SUBST_ENTITIES"sv, XML_PARSER_SUBST_ENTITIES)
	;
}

void t_type_of<xmlReaderTypes>::f_define(t_extension* a_extension)
{
	t_define<xmlReaderTypes, intptr_t>(a_extension, L"ReaderTypes"sv)
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
}

void t_type_of<xemmaix::libxml::t_text_reader>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::libxml;
	t_define<t_text_reader, t_object>(a_extension, L"TextReader"sv)
		(
			t_construct<false, std::wstring_view>(),
			t_construct<false, std::wstring_view, std::wstring_view, int>(),
			t_construct<false, const t_value&, const t_value&, std::wstring_view, std::wstring_view, int>()
		)
		(L"free"sv, t_member<void(t_text_reader::*)(), &t_text_reader::f_free, t_with_lock_for_write>())
		(L"read"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_read, t_with_lock_for_write>())
#ifdef LIBXML_WRITER_ENABLED
		(L"read_inner_xml"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_read_inner_xml, t_with_lock_for_write>())
		(L"read_outer_xml"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_read_outer_xml, t_with_lock_for_write>())
#endif
		(L"read_string"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_read_string, t_with_lock_for_write>())
		(L"read_attribute_value"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_read_attribute_value, t_with_lock_for_write>())
		(L"attribute_count"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_attribute_count, t_with_lock_for_write>())
		(L"depth"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_depth, t_with_lock_for_write>())
		(L"has_attributes"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_has_attributes, t_with_lock_for_write>())
		(L"has_value"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_has_value, t_with_lock_for_write>())
		(L"is_default"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_is_default, t_with_lock_for_write>())
		(L"is_empty_element"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_is_empty_element, t_with_lock_for_write>())
		(L"node_type"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_node_type, t_with_lock_for_write>())
		(L"quote_character"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_quote_character, t_with_lock_for_write>())
		(L"read_state"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_read_state, t_with_lock_for_write>())
		(L"is_namespace_decl"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_is_namespace_decl, t_with_lock_for_write>())
		(L"base_uri"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_base_uri, t_with_lock_for_write>())
		(L"local_name"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_local_name, t_with_lock_for_write>())
		(L"name"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_name, t_with_lock_for_write>())
		(L"namespace_uri"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_namespace_uri, t_with_lock_for_write>())
		(L"prefix"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_prefix, t_with_lock_for_write>())
		(L"xml_lang"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_xml_lang, t_with_lock_for_write>())
		(L"value"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_value, t_with_lock_for_write>())
		(L"close"sv, t_member<void(t_text_reader::*)(), &t_text_reader::f_close, t_with_lock_for_write>())
		(L"get_attribute_no"sv, t_member<std::wstring(t_text_reader::*)(int), &t_text_reader::f_get_attribute_no, t_with_lock_for_write>())
		(L"get_attribute"sv, t_member<std::wstring(t_text_reader::*)(std::wstring_view), &t_text_reader::f_get_attribute, t_with_lock_for_write>())
		(L"get_attribute_ns"sv, t_member<std::wstring(t_text_reader::*)(std::wstring_view, std::wstring_view), &t_text_reader::f_get_attribute_ns, t_with_lock_for_write>())
		(L"lookup_namespace"sv, t_member<std::wstring(t_text_reader::*)(std::wstring_view), &t_text_reader::f_lookup_namespace, t_with_lock_for_write>())
		(L"move_to_attribute_no"sv, t_member<bool(t_text_reader::*)(int), &t_text_reader::f_move_to_attribute_no, t_with_lock_for_write>())
		(L"move_to_attribute"sv, t_member<bool(t_text_reader::*)(std::wstring_view), &t_text_reader::f_move_to_attribute, t_with_lock_for_write>())
		(L"move_to_attribute_ns"sv, t_member<bool(t_text_reader::*)(std::wstring_view, std::wstring_view), &t_text_reader::f_move_to_attribute_ns, t_with_lock_for_write>())
		(L"move_to_first_attribute"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_move_to_first_attribute, t_with_lock_for_write>())
		(L"move_to_next_attribute"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_move_to_next_attribute, t_with_lock_for_write>())
		(L"move_to_element"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_move_to_element, t_with_lock_for_write>())
		(L"normalization"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_normalization, t_with_lock_for_write>())
		(L"encoding"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_encoding, t_with_lock_for_write>())
		(L"set_parser_property"sv, t_member<void(t_text_reader::*)(int, int), &t_text_reader::f_set_parser_property, t_with_lock_for_write>())
		(L"get_parser_property"sv, t_member<int(t_text_reader::*)(int), &t_text_reader::f_get_parser_property, t_with_lock_for_write>())
		(L"get_parser_line_number"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_get_parser_line_number, t_with_lock_for_write>())
		(L"get_parser_column_number"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_get_parser_column_number, t_with_lock_for_write>())
		(L"next"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_next, t_with_lock_for_write>())
		(L"next_sibling"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_next_sibling, t_with_lock_for_write>())
		(L"is_valid"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_is_valid, t_with_lock_for_write>())
#ifdef LIBXML_SCHEMAS_ENABLED
		(L"relax_ng_validate"sv, t_member<void(t_text_reader::*)(std::wstring_view), &t_text_reader::f_relax_ng_validate, t_with_lock_for_write>())
		(L"schema_validate"sv, t_member<void(t_text_reader::*)(std::wstring_view), &t_text_reader::f_schema_validate, t_with_lock_for_write>())
#endif
		(L"xml_version"sv, t_member<std::wstring(t_text_reader::*)(), &t_text_reader::f_xml_version, t_with_lock_for_write>())
		(L"standalone"sv, t_member<bool(t_text_reader::*)(), &t_text_reader::f_standalone, t_with_lock_for_write>())
		(L"byte_consumed"sv, t_member<int(t_text_reader::*)(), &t_text_reader::f_byte_consumed, t_with_lock_for_write>())
		(L"new_file"sv, t_member<void(t_text_reader::*)(std::wstring_view, std::wstring_view, int), &t_text_reader::f_new_file, t_with_lock_for_write>())
	;
}

t_scoped t_type_of<xemmaix::libxml::t_text_reader>::f_do_construct(t_stacked* a_stack, size_t a_n)
{
	return t_overload<
		t_construct<false, std::wstring_view>,
		t_construct<false, std::wstring_view, std::wstring_view, int>,
		t_construct<false, const t_value&, const t_value&, std::wstring_view, std::wstring_view, int>
	>::t_bind<xemmaix::libxml::t_text_reader>::f_do(this, a_stack, a_n);
}

}

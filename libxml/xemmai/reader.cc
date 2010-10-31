#include "reader.h"

#include <xemmai/derived.h>

namespace xemmai
{

void t_type_of<xmlParserSeverities>::f_define(t_extension* a_extension)
{
	t_define<xmlParserSeverities, int>(a_extension, L"ParserSeverities")
		(L"VALIDITY_WARNING", XML_PARSER_SEVERITY_VALIDITY_WARNING)
		(L"VALIDITY_ERROR", XML_PARSER_SEVERITY_VALIDITY_ERROR)
		(L"WARNING", XML_PARSER_SEVERITY_WARNING)
		(L"ERROR", XML_PARSER_SEVERITY_ERROR)
	;
}

void t_type_of<xmlTextReaderMode>::f_define(t_extension* a_extension)
{
	t_define<xmlTextReaderMode, int>(a_extension, L"TextReaderMode")
		(L"INITIAL", XML_TEXTREADER_MODE_INITIAL)
		(L"INTERACTIVE", XML_TEXTREADER_MODE_INTERACTIVE)
		(L"ERROR", XML_TEXTREADER_MODE_ERROR)
		(L"EOF", XML_TEXTREADER_MODE_EOF)
		(L"CLOSED", XML_TEXTREADER_MODE_CLOSED)
		(L"READING", XML_TEXTREADER_MODE_READING)
	;
}

void t_type_of<xmlParserProperties>::f_define(t_extension* a_extension)
{
	t_define<xmlParserProperties, int>(a_extension, L"ParserProperties")
		(L"LOADDTD", XML_PARSER_LOADDTD)
		(L"DEFAULTATTRS", XML_PARSER_DEFAULTATTRS)
		(L"VALIDATE", XML_PARSER_VALIDATE)
		(L"SUBST_ENTITIES", XML_PARSER_SUBST_ENTITIES)
	;
}

void t_type_of<xmlReaderTypes>::f_define(t_extension* a_extension)
{
	t_define<xmlReaderTypes, int>(a_extension, L"ReaderTypes")
		(L"NONE", XML_READER_TYPE_NONE)
		(L"ELEMENT", XML_READER_TYPE_ELEMENT)
		(L"ATTRIBUTE", XML_READER_TYPE_ATTRIBUTE)
		(L"TEXT", XML_READER_TYPE_TEXT)
		(L"CDATA", XML_READER_TYPE_CDATA)
		(L"ENTITY_REFERENCE", XML_READER_TYPE_ENTITY_REFERENCE)
		(L"ENTITY", XML_READER_TYPE_ENTITY)
		(L"PROCESSING_INSTRUCTION", XML_READER_TYPE_PROCESSING_INSTRUCTION)
		(L"COMMENT", XML_READER_TYPE_COMMENT)
		(L"DOCUMENT", XML_READER_TYPE_DOCUMENT)
		(L"DOCUMENT_TYPE", XML_READER_TYPE_DOCUMENT_TYPE)
		(L"DOCUMENT_FRAGMENT", XML_READER_TYPE_DOCUMENT_FRAGMENT)
		(L"NOTATION", XML_READER_TYPE_NOTATION)
		(L"WHITESPACE", XML_READER_TYPE_WHITESPACE)
		(L"SIGNIFICANT_WHITESPACE", XML_READER_TYPE_SIGNIFICANT_WHITESPACE)
		(L"END_ELEMENT", XML_READER_TYPE_END_ELEMENT)
		(L"END_ENTITY", XML_READER_TYPE_END_ENTITY)
		(L"XML_DECLARATION", XML_READER_TYPE_XML_DECLARATION)
	;
}

void t_type_of<t_text_reader>::f_define(t_extension* a_extension)
{
	t_define<t_text_reader, t_object>(a_extension, L"TextReader")
		(L"free", t_member<void (t_text_reader::*)(), &t_text_reader::f_free, t_with_lock_for_write>())
		(L"read", t_member<bool (t_text_reader::*)(), &t_text_reader::f_read, t_with_lock_for_write>())
#ifdef LIBXML_WRITER_ENABLED
		(L"read_inner_xml", t_member<std::wstring (t_text_reader::*)(), &t_text_reader::f_read_inner_xml, t_with_lock_for_write>())
		(L"read_outer_xml", t_member<std::wstring (t_text_reader::*)(), &t_text_reader::f_read_outer_xml, t_with_lock_for_write>())
#endif
		(L"read_string", t_member<std::wstring (t_text_reader::*)(), &t_text_reader::f_read_string, t_with_lock_for_write>())
		(L"read_attribute_value", t_member<bool (t_text_reader::*)(), &t_text_reader::f_read_attribute_value, t_with_lock_for_write>())
		(L"attribute_count", t_member<int (t_text_reader::*)(), &t_text_reader::f_attribute_count, t_with_lock_for_write>())
		(L"depth", t_member<int (t_text_reader::*)(), &t_text_reader::f_depth, t_with_lock_for_write>())
		(L"has_attributes", t_member<bool (t_text_reader::*)(), &t_text_reader::f_has_attributes, t_with_lock_for_write>())
		(L"has_value", t_member<bool (t_text_reader::*)(), &t_text_reader::f_has_value, t_with_lock_for_write>())
		(L"is_default", t_member<bool (t_text_reader::*)(), &t_text_reader::f_is_default, t_with_lock_for_write>())
		(L"is_empty_element", t_member<bool (t_text_reader::*)(), &t_text_reader::f_is_empty_element, t_with_lock_for_write>())
		(L"node_type", t_member<int (t_text_reader::*)(), &t_text_reader::f_node_type, t_with_lock_for_write>())
		(L"quote_character", t_member<int (t_text_reader::*)(), &t_text_reader::f_quote_character, t_with_lock_for_write>())
		(L"read_state", t_member<int (t_text_reader::*)(), &t_text_reader::f_read_state, t_with_lock_for_write>())
		(L"is_namespace_decl", t_member<bool (t_text_reader::*)(), &t_text_reader::f_is_namespace_decl, t_with_lock_for_write>())
		(L"base_uri", t_member<std::wstring (t_text_reader::*)(), &t_text_reader::f_base_uri, t_with_lock_for_write>())
		(L"local_name", t_member<std::wstring (t_text_reader::*)(), &t_text_reader::f_local_name, t_with_lock_for_write>())
		(L"name", t_member<std::wstring (t_text_reader::*)(), &t_text_reader::f_name, t_with_lock_for_write>())
		(L"namespace_uri", t_member<std::wstring (t_text_reader::*)(), &t_text_reader::f_namespace_uri, t_with_lock_for_write>())
		(L"prefix", t_member<std::wstring (t_text_reader::*)(), &t_text_reader::f_prefix, t_with_lock_for_write>())
		(L"xml_lang", t_member<std::wstring (t_text_reader::*)(), &t_text_reader::f_xml_lang, t_with_lock_for_write>())
		(L"value", t_member<std::wstring (t_text_reader::*)(), &t_text_reader::f_value, t_with_lock_for_write>())
		(L"close", t_member<void (t_text_reader::*)(), &t_text_reader::f_close, t_with_lock_for_write>())
		(L"get_attribute_no", t_member<std::wstring (t_text_reader::*)(int), &t_text_reader::f_get_attribute_no, t_with_lock_for_write>())
		(L"get_attribute", t_member<std::wstring (t_text_reader::*)(const std::wstring&), &t_text_reader::f_get_attribute, t_with_lock_for_write>())
		(L"get_attribute_ns", t_member<std::wstring (t_text_reader::*)(const std::wstring&, const std::wstring&), &t_text_reader::f_get_attribute_ns, t_with_lock_for_write>())
		(L"lookup_namespace", t_member<std::wstring (t_text_reader::*)(const std::wstring&), &t_text_reader::f_lookup_namespace, t_with_lock_for_write>())
		(L"move_to_attribute_no", t_member<bool (t_text_reader::*)(int), &t_text_reader::f_move_to_attribute_no, t_with_lock_for_write>())
		(L"move_to_attribute", t_member<bool (t_text_reader::*)(const std::wstring&), &t_text_reader::f_move_to_attribute, t_with_lock_for_write>())
		(L"move_to_attribute_ns", t_member<bool (t_text_reader::*)(const std::wstring&, const std::wstring&), &t_text_reader::f_move_to_attribute_ns, t_with_lock_for_write>())
		(L"move_to_first_attribute", t_member<bool (t_text_reader::*)(), &t_text_reader::f_move_to_first_attribute, t_with_lock_for_write>())
		(L"move_to_next_attribute", t_member<bool (t_text_reader::*)(), &t_text_reader::f_move_to_next_attribute, t_with_lock_for_write>())
		(L"move_to_element", t_member<bool (t_text_reader::*)(), &t_text_reader::f_move_to_element, t_with_lock_for_write>())
		(L"normalization", t_member<bool (t_text_reader::*)(), &t_text_reader::f_normalization, t_with_lock_for_write>())
		(L"encoding", t_member<std::wstring (t_text_reader::*)(), &t_text_reader::f_encoding, t_with_lock_for_write>())
		(L"set_parser_property", t_member<void (t_text_reader::*)(int, int), &t_text_reader::f_set_parser_property, t_with_lock_for_write>())
		(L"get_parser_property", t_member<int (t_text_reader::*)(int), &t_text_reader::f_get_parser_property, t_with_lock_for_write>())
		(L"get_parser_line_number", t_member<int (t_text_reader::*)(), &t_text_reader::f_get_parser_line_number, t_with_lock_for_write>())
		(L"get_parser_column_number", t_member<int (t_text_reader::*)(), &t_text_reader::f_get_parser_column_number, t_with_lock_for_write>())
		(L"next", t_member<bool (t_text_reader::*)(), &t_text_reader::f_next, t_with_lock_for_write>())
		(L"next_sibling", t_member<bool (t_text_reader::*)(), &t_text_reader::f_next_sibling, t_with_lock_for_write>())
		(L"is_valid", t_member<bool (t_text_reader::*)(), &t_text_reader::f_is_valid, t_with_lock_for_write>())
#ifdef LIBXML_SCHEMAS_ENABLED
		(L"relax_ng_validate", t_member<void (t_text_reader::*)(const std::wstring&), &t_text_reader::f_relax_ng_validate, t_with_lock_for_write>())
		(L"schema_validate", t_member<void (t_text_reader::*)(const std::wstring&), &t_text_reader::f_schema_validate, t_with_lock_for_write>())
#endif
		(L"xml_version", t_member<std::wstring (t_text_reader::*)(), &t_text_reader::f_xml_version, t_with_lock_for_write>())
		(L"standalone", t_member<bool (t_text_reader::*)(), &t_text_reader::f_standalone, t_with_lock_for_write>())
		(L"byte_consumed", t_member<int (t_text_reader::*)(), &t_text_reader::f_byte_consumed, t_with_lock_for_write>())
		(L"new_file", t_member<void (t_text_reader::*)(const std::wstring&, const std::wstring&, int), &t_text_reader::f_new_file, t_with_lock_for_write>())
	;
}

t_type* t_type_of<t_text_reader>::f_derive(t_object* a_this)
{
	return new t_derived<t_type_of>(v_module, a_this);
}

void t_type_of<t_text_reader>::f_finalize(t_object* a_this)
{
	delete f_as<t_text_reader*>(a_this);
}

void t_type_of<t_text_reader>::f_construct(t_object* a_class, size_t a_n)
{
	t_overload<t_construct<t_text_reader, const std::wstring&>,
	t_overload<t_construct<t_text_reader, const std::wstring&, const std::wstring&, int>
	> >::f_call(a_class, a_n);
}

}

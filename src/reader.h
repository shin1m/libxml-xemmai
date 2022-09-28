#ifndef XEMMAIX__LIBXML__READER_H
#define XEMMAIX__LIBXML__READER_H

#include "libxml.h"

namespace xemmaix::libxml
{

class t_text_reader : t_owned, t_utf8_converter
{
	xmlTextReaderPtr v_reader;

	const xmlChar* f_cast(const std::string& a_string)
	{
		return reinterpret_cast<const xmlChar*>(a_string.c_str());
	}
	void f_void(int a_code)
	{
		if (a_code != 0) f_throw(L"error occurred."sv);
	}
	bool f_boolean(int a_code)
	{
		if (a_code == -1) f_throw(L"error occurred."sv);
		return a_code != 0;
	}
	int f_integer(int a_code)
	{
		if (a_code == -1) f_throw(L"error occurred."sv);
		return a_code;
	}
	std::wstring f_string(const xmlChar* a_p)
	{
		return a_p == NULL ? std::wstring() : f_convert(reinterpret_cast<const char*>(a_p));
	}
	std::wstring f_string(xmlChar* a_p)
	{
		if (a_p == NULL) return std::wstring();
		std::wstring s = f_convert(reinterpret_cast<char*>(a_p));
		xmlFree(a_p);
		return s;
	}

public:
	t_text_reader(xmlParserInputBufferPtr a_input, std::wstring_view a_uri) : v_reader(xmlNewTextReader(a_input, f_convert(a_uri).c_str()))
	{
	}
	t_text_reader(std::wstring_view a_uri) : v_reader(xmlNewTextReaderFilename(f_convert(a_uri).c_str()))
	{
	}
	t_text_reader(xmlDocPtr a_document) : v_reader(xmlReaderWalker(a_document))
	{
	}
	t_text_reader(const xmlChar* a_current, const char* a_url, const char* a_encoding, int a_options) : v_reader(xmlReaderForDoc(a_current, a_url, a_encoding, a_options))
	{
	}
	t_text_reader(std::wstring_view a_filename, std::wstring_view a_encoding, int a_options) : v_reader(xmlReaderForFile(f_convert(a_filename).c_str(), f_convert(a_encoding).c_str(), a_options))
	{
	}
	t_text_reader(const char* a_buffer, int a_size, const char* a_url, const char* a_encoding, int a_options) : v_reader(xmlReaderForMemory(a_buffer, a_size, a_url, a_encoding, a_options))
	{
	}
	t_text_reader(int a_fd, const char* a_url, const char* a_encoding, int a_options) : v_reader(xmlReaderForFd(a_fd, a_url, a_encoding, a_options))
	{
	}
	t_text_reader(xmlInputReadCallback a_ioread, xmlInputCloseCallback a_ioclose, void* a_ioctx, const char* a_url, const char* a_encoding, int a_options) : v_reader(xmlReaderForIO(a_ioread, a_ioclose, a_ioctx, a_url, a_encoding, a_options))
	{
	}
	t_text_reader(const t_pvalue& a_read, const t_pvalue& a_close, std::wstring_view a_url, std::wstring_view a_encoding, int a_options);
	~t_text_reader()
	{
		xmlFreeTextReader(v_reader);
	}
	void f_free()
	{
		f_owned_or_throw();
		xmlFreeTextReader(v_reader);
		v_reader = NULL;
	}
	void f_setup(xmlParserInputBufferPtr a_input, const char* a_uri, const char* a_encoding, int a_options)
	{
		f_void(xmlTextReaderSetup(v_reader, a_input, a_uri, a_encoding, a_options));
	}
	bool f_read()
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderRead(v_reader));
	}
#ifdef LIBXML_WRITER_ENABLED
	std::wstring f_read_inner_xml()
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderReadInnerXml(v_reader));
	}
	std::wstring f_read_outer_xml()
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderReadOuterXml(v_reader));
	}
#endif
	std::wstring f_read_string()
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderReadString(v_reader));
	}
	bool f_read_attribute_value()
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderReadAttributeValue(v_reader));
	}
	int f_attribute_count()
	{
		f_owned_or_throw();
		return f_integer(xmlTextReaderAttributeCount(v_reader));
	}
	int f_depth()
	{
		f_owned_or_throw();
		return f_integer(xmlTextReaderDepth(v_reader));
	}
	bool f_has_attributes()
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderHasAttributes(v_reader));
	}
	bool f_has_value()
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderHasValue(v_reader));
	}
	bool f_is_default()
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderIsDefault(v_reader));
	}
	bool f_is_empty_element()
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderIsEmptyElement(v_reader));
	}
	int f_node_type()
	{
		f_owned_or_throw();
		return f_integer(xmlTextReaderNodeType(v_reader));
	}
	int f_quote_character()
	{
		f_owned_or_throw();
		return f_integer(xmlTextReaderQuoteChar(v_reader));
	}
	int f_read_state()
	{
		f_owned_or_throw();
		return f_integer(xmlTextReaderReadState(v_reader));
	}
	bool f_is_namespace_decl()
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderIsNamespaceDecl(v_reader));
	}
	std::wstring f_base_uri()
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderConstBaseUri(v_reader));
	}
	std::wstring f_local_name()
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderConstLocalName(v_reader));
	}
	std::wstring f_name()
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderConstName(v_reader));
	}
	std::wstring f_namespace_uri()
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderConstNamespaceUri(v_reader));
	}
	std::wstring f_prefix()
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderConstPrefix(v_reader));
	}
	std::wstring f_xml_lang()
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderConstXmlLang(v_reader));
	}
	const xmlChar* f_const_string(const xmlChar* a_string)
	{
		return xmlTextReaderConstString(v_reader, a_string);
	}
	std::wstring f_value()
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderConstValue(v_reader));
	}
	void f_close()
	{
		f_owned_or_throw();
		f_void(xmlTextReaderClose(v_reader));
	}
	std::wstring f_get_attribute_no(int a_no)
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderGetAttributeNo(v_reader, a_no));
	}
	std::wstring f_get_attribute(std::wstring_view a_name)
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderGetAttribute(v_reader, f_cast(f_convert(a_name))));
	}
	std::wstring f_get_attribute_ns(std::wstring_view a_name, std::wstring_view a_uri)
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderGetAttributeNs(v_reader, f_cast(f_convert(a_name)), f_cast(f_convert(a_uri))));
	}
	xmlParserInputBufferPtr get_remainder()
	{
		return xmlTextReaderGetRemainder(v_reader);
	}
	std::wstring f_lookup_namespace(std::wstring_view a_prefix)
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderLookupNamespace(v_reader, f_cast(f_convert(a_prefix))));
	}
	bool f_move_to_attribute_no(int a_no)
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderMoveToAttributeNo(v_reader, a_no));
	}
	bool f_move_to_attribute(std::wstring_view a_name)
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderMoveToAttribute(v_reader, f_cast(f_convert(a_name))));
	}
	bool f_move_to_attribute_ns(std::wstring_view a_name, std::wstring_view a_uri)
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderMoveToAttributeNs(v_reader, f_cast(f_convert(a_name)), f_cast(f_convert(a_uri))));
	}
	bool f_move_to_first_attribute()
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderMoveToFirstAttribute(v_reader));
	}
	bool f_move_to_next_attribute()
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderMoveToNextAttribute(v_reader));
	}
	bool f_move_to_element()
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderMoveToElement(v_reader));
	}
	bool f_normalization()
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderNormalization(v_reader));
	}
	std::wstring f_encoding()
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderConstEncoding(v_reader));
	}
	void f_set_parser_property(int a_property, int a_value)
	{
		f_owned_or_throw();
		f_void(xmlTextReaderSetParserProp(v_reader, a_property, a_value));
	}
	int f_get_parser_property(int a_property)
	{
		f_owned_or_throw();
		return f_integer(xmlTextReaderGetParserProp(v_reader, a_property));
	}
	xmlNodePtr f_current_node()
	{
		return xmlTextReaderCurrentNode(v_reader);
	}
	int f_get_parser_line_number()
	{
		f_owned_or_throw();
		return xmlTextReaderGetParserLineNumber(v_reader);
	}
	int f_get_parser_column_number()
	{
		f_owned_or_throw();
		return xmlTextReaderGetParserColumnNumber(v_reader);
	}
	xmlNodePtr f_preserve()
	{
		return xmlTextReaderPreserve(v_reader);
	}
#ifdef LIBXML_PATTERN_ENABLED
	void f_preserve_pattern(const xmlChar* a_pattern, const xmlChar** a_namespaces)
	{
		f_void(xmlTextReaderPreservePattern(v_reader, a_pattern, a_namespaces));
	}
#endif
	xmlDocPtr f_current_document()
	{
		return xmlTextReaderCurrentDoc(v_reader);
	}
	xmlNodePtr f_expand()
	{
		return xmlTextReaderExpand(v_reader);
	}
	bool f_next()
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderNext(v_reader));
	}
	bool f_next_sibling()
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderNextSibling(v_reader));
	}
	bool f_is_valid()
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderIsValid(v_reader));
	}
#ifdef LIBXML_SCHEMAS_ENABLED
	void f_relax_ng_validate(std::wstring_view a_rng)
	{
		f_owned_or_throw();
		f_void(xmlTextReaderRelaxNGValidate(v_reader, f_convert(a_rng).c_str()));
	}
	void f_relax_ng_set_schema(xmlRelaxNGPtr a_schema)
	{
		f_void(xmlTextReaderRelaxNGSetSchema(v_reader, a_schema));
	}
	void f_schema_validate(std::wstring_view a_xsd)
	{
		f_owned_or_throw();
		f_void(xmlTextReaderSchemaValidate(v_reader, f_convert(a_xsd).c_str()));
	}
	void f_schema_validate_context(xmlSchemaValidCtxtPtr a_context, int a_options)
	{
		f_void(xmlTextReaderSchemaValidateCtxt(v_reader, a_context, a_options));
	}
	void f_set_schema(xmlSchemaPtr a_schema)
	{
		f_void(xmlTextReaderSetSchema(v_reader, a_schema));
	}
#endif
	std::wstring f_xml_version()
	{
		f_owned_or_throw();
		return f_string(xmlTextReaderConstXmlVersion(v_reader));
	}
	bool f_standalone()
	{
		f_owned_or_throw();
		return f_boolean(xmlTextReaderStandalone(v_reader));
	}
	int f_byte_consumed()
	{
		f_owned_or_throw();
		return xmlTextReaderByteConsumed(v_reader);
	}
	void f_new_walker(xmlDocPtr a_document)
	{
		f_void(xmlReaderNewWalker(v_reader, a_document));
	}
	void f_new_document(const xmlChar* a_current, const char* a_url, const char* a_encoding, int a_options)
	{
		f_void(xmlReaderNewDoc(v_reader, a_current, a_url, a_encoding, a_options));
	}
	void f_new_file(std::wstring_view a_filename, std::wstring_view a_encoding, int a_options)
	{
		f_owned_or_throw();
		f_void(xmlReaderNewFile(v_reader, f_convert(a_filename).c_str(), f_convert(a_encoding).c_str(), a_options));
	}
	void f_new_memory(const char* a_buffer, int a_size, const char* a_url, const char* a_encoding, int a_options)
	{
		f_void(xmlReaderNewMemory(v_reader, a_buffer, a_size, a_url, a_encoding, a_options));
	}
	void f_new_fd(int a_fd, const char* a_url, const char* a_encoding, int a_options)
	{
		f_void(xmlReaderNewFd(v_reader, a_fd, a_url, a_encoding, a_options));
	}
	void f_new_io(xmlInputReadCallback a_ioread, xmlInputCloseCallback a_ioclose, void* a_ioctx, const char* a_url, const char* a_encoding, int a_options)
	{
		f_void(xmlReaderNewIO(v_reader, a_ioread, a_ioclose, a_ioctx, a_url, a_encoding, a_options));
	}
	void f_set_error_handler(xmlTextReaderErrorFunc a_function, void* a_argument)
	{
		xmlTextReaderSetErrorHandler(v_reader, a_function, a_argument);
	}
	void f_set_structured_error_handler(xmlStructuredErrorFunc a_function, void* a_argument)
	{
		xmlTextReaderSetStructuredErrorHandler(v_reader, a_function, a_argument);
	}
	void f_get_error_handler(xmlTextReaderErrorFunc* a_function, void** a_argument)
	{
		xmlTextReaderGetErrorHandler(v_reader, a_function, a_argument);
	}
};

}

namespace xemmai
{

template<>
struct t_type_of<xmlParserSeverities> : t_enum_of<xmlParserSeverities, xemmaix::libxml::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<xmlTextReaderMode> : t_enum_of<xmlTextReaderMode, xemmaix::libxml::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<xmlParserProperties> : t_enum_of<xmlParserProperties, xemmaix::libxml::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<xmlReaderTypes> : t_enum_of<xmlReaderTypes, xemmaix::libxml::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<xemmaix::libxml::t_text_reader> : t_derivable<t_holds<xemmaix::libxml::t_text_reader>>
{
	using t_library = xemmaix::libxml::t_library;

	static void f_define(t_library* a_library);

	using t_base::t_base;
	t_pvalue f_do_construct(t_pvalue* a_stack, size_t a_n);
};

}

#endif

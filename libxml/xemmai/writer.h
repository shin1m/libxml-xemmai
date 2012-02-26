#ifndef LIBXML__XEMMAI__WRITER_H
#define LIBXML__XEMMAI__WRITER_H

#include "libxml.h"

namespace libxml
{

namespace xemmai
{

class t_text_writer : t_utf8_converter
{
	xmlTextWriterPtr v_writer;

	const xmlChar* f_cast(const std::string& a_string)
	{
		return reinterpret_cast<const xmlChar*>(a_string.c_str());
	}
	void f_void(int a_code)
	{
		if (a_code != 0) t_throwable::f_throw(L"error occurred.");
	}
	int f_integer(int a_code)
	{
		if (a_code == -1) t_throwable::f_throw(L"error occurred.");
		return a_code;
	}

public:
	t_text_writer(xmlOutputBufferPtr a_output) : v_writer(xmlNewTextWriter(a_output))
	{
	}
	t_text_writer(const std::wstring& a_uri, bool a_compression) : v_writer(xmlNewTextWriterFilename(f_convert(a_uri).c_str(), a_compression ? 1 : 0))
	{
	}
	t_text_writer(xmlBufferPtr a_buffer, bool a_compression) : v_writer(xmlNewTextWriterMemory(a_buffer, a_compression ? 1 : 0))
	{
	}
	t_text_writer(xmlParserCtxtPtr a_context, bool a_compression) : v_writer(xmlNewTextWriterPushParser(a_context, a_compression ? 1 : 0))
	{
	}
	t_text_writer(xmlDocPtr* a_document, bool a_compression) : v_writer(xmlNewTextWriterDoc(a_document, a_compression ? 1 : 0))
	{
	}
	t_text_writer(xmlDocPtr a_document, xmlNodePtr a_node, bool a_compression) : v_writer(xmlNewTextWriterTree(a_document, a_node, a_compression ? 1 : 0))
	{
	}
	~t_text_writer()
	{
		f_free();
	}
	void f_free()
	{
		xmlFreeTextWriter(v_writer);
		v_writer = NULL;
	}
	int f_start_document(const std::wstring* a_version, const std::wstring* a_encoding, const std::wstring* a_standalone)
	{
		return f_integer(xmlTextWriterStartDocument(v_writer, a_version ? f_convert(*a_version).c_str() : NULL, a_encoding ? f_convert(*a_encoding).c_str() : NULL, a_standalone ? f_convert(*a_standalone).c_str() : NULL));
	}
	int f_end_document()
	{
		return f_integer(xmlTextWriterEndDocument(v_writer));
	}
	int f_start_comment()
	{
		return f_integer(xmlTextWriterStartComment(v_writer));
	}
	int f_end_comment()
	{
		return f_integer(xmlTextWriterEndComment(v_writer));
	}
	int f_write_format_comment(const char* a_format, ...)
	{
		va_list arguments;
		va_start(arguments, a_format);
		int n = f_write_vformat_comment(a_format, arguments);
		va_end(arguments);
		return n;
	}
	int f_write_vformat_comment(const char* a_format, va_list a_arguments)
	{
		return xmlTextWriterWriteVFormatComment(v_writer, a_format, a_arguments);
	}
	int f_write_comment(const std::wstring& a_content)
	{
		return f_integer(xmlTextWriterWriteComment(v_writer, f_cast(f_convert(a_content))));
	}
	int f_start_element(const std::wstring& a_name)
	{
		return f_integer(xmlTextWriterStartElement(v_writer, f_cast(f_convert(a_name))));
	}
	int f_start_element_ns(const std::wstring& a_prefix, const std::wstring& a_name, const std::wstring& a_uri)
	{
		return f_integer(xmlTextWriterStartElementNS(v_writer, f_cast(f_convert(a_prefix)), f_cast(f_convert(a_name)), f_cast(f_convert(a_uri))));
	}
	int f_end_element()
	{
		return f_integer(xmlTextWriterEndElement(v_writer));
	}
	int f_full_end_element()
	{
		return f_integer(xmlTextWriterFullEndElement(v_writer));
	}
	int f_write_format_element(const xmlChar* a_name, const char* a_format, ...)
	{
		va_list arguments;
		va_start(arguments, a_format);
		int n = f_write_vformat_element(a_name, a_format, arguments);
		va_end(arguments);
		return n;
	}
	int f_write_vformat_element(const xmlChar* a_name, const char* a_format, va_list a_arguments)
	{
		return xmlTextWriterWriteVFormatElement(v_writer, a_name, a_format, a_arguments);
	}
	int f_write_element(const std::wstring& a_name, const std::wstring& a_content)
	{
		return f_integer(xmlTextWriterWriteElement(v_writer, f_cast(f_convert(a_name)), f_cast(f_convert(a_content))));
	}
	int f_write_format_element_ns(const xmlChar* a_prefix, const xmlChar* a_name, const xmlChar* a_uri, const char* a_format, ...)
	{
		va_list arguments;
		va_start(arguments, a_format);
		int n = f_write_vformat_element_ns(a_prefix, a_name, a_uri, a_format, arguments);
		va_end(arguments);
		return n;
	}
	int f_write_vformat_element_ns(const xmlChar* a_prefix, const xmlChar* a_name, const xmlChar* a_uri, const char* a_format, va_list a_arguments)
	{
		return xmlTextWriterWriteVFormatElementNS(v_writer, a_prefix, a_name, a_uri, a_format, a_arguments);
	}
	int f_write_element_ns(const std::wstring& a_prefix, const std::wstring& a_name, const std::wstring& a_uri, const std::wstring& a_content)
	{
		return f_integer(xmlTextWriterWriteElementNS(v_writer, f_cast(f_convert(a_prefix)), f_cast(f_convert(a_name)), f_cast(f_convert(a_uri)), f_cast(f_convert(a_content))));
	}
	int f_write_format_raw(const char* a_format, ...)
	{
		va_list arguments;
		va_start(arguments, a_format);
		int n = f_write_vformat_raw(a_format, arguments);
		va_end(arguments);
		return n;
	}
	int f_write_vformat_raw(const char* a_format, va_list a_arguments)
	{
		return xmlTextWriterWriteVFormatRaw(v_writer, a_format, a_arguments);
	}
	int f_write_raw(const xmlChar* a_content, int a_length)
	{
		return xmlTextWriterWriteRawLen(v_writer, a_content, a_length);
	}
	int f_write_raw(const std::wstring& a_content)
	{
		return f_integer(xmlTextWriterWriteRaw(v_writer, f_cast(f_convert(a_content))));
	}
	int f_write_format_string(const char* a_format, ...)
	{
		va_list arguments;
		va_start(arguments, a_format);
		int n = f_write_vformat_string(a_format, arguments);
		va_end(arguments);
		return n;
	}
	int f_write_vformat_string(const char* a_format, va_list a_arguments)
	{
		return xmlTextWriterWriteVFormatString(v_writer, a_format, a_arguments);
	}
	int f_write_string(const std::wstring& a_content)
	{
		return f_integer(xmlTextWriterWriteString(v_writer, f_cast(f_convert(a_content))));
	}
	int f_write_base64(const char* a_data, int a_start, int a_length)
	{
		return xmlTextWriterWriteBase64(v_writer, a_data, a_start, a_length);
	}
	int f_write_bin_hex(const char* a_data, int a_start, int a_length)
	{
		return xmlTextWriterWriteBinHex(v_writer, a_data, a_start, a_length);
	}
	int f_start_attribute(const std::wstring& a_name)
	{
		return f_integer(xmlTextWriterStartAttribute(v_writer, f_cast(f_convert(a_name))));
	}
	int f_start_attribute_ns(const std::wstring& a_prefix, const std::wstring& a_name, const std::wstring& a_uri)
	{
		return f_integer(xmlTextWriterStartAttributeNS(v_writer, f_cast(f_convert(a_prefix)), f_cast(f_convert(a_name)), f_cast(f_convert(a_uri))));
	}
	int f_end_attribute()
	{
		return f_integer(xmlTextWriterEndAttribute(v_writer));
	}
	int f_write_format_attribute(const xmlChar* a_name, const char* a_format, ...)
	{
		va_list arguments;
		va_start(arguments, a_format);
		int n = f_write_vformat_attribute(a_name, a_format, arguments);
		va_end(arguments);
		return n;
	}
	int f_write_vformat_attribute(const xmlChar* a_name, const char* a_format, va_list a_arguments)
	{
		return xmlTextWriterWriteVFormatAttribute(v_writer, a_name, a_format, a_arguments);
	}
	int f_write_attribute(const std::wstring& a_name, const std::wstring& a_content)
	{
		return f_integer(xmlTextWriterWriteAttribute(v_writer, f_cast(f_convert(a_name)), f_cast(f_convert(a_content))));
	}
	int f_write_format_attribute_ns(const xmlChar* a_prefix, const xmlChar* a_name, const xmlChar* a_uri, const char* a_format, ...)
	{
		va_list arguments;
		va_start(arguments, a_format);
		int n = f_write_vformat_attribute_ns(a_prefix, a_name, a_uri, a_format, arguments);
		va_end(arguments);
		return n;
	}
	int f_write_vformat_attribute_ns(const xmlChar* a_prefix, const xmlChar* a_name, const xmlChar* a_uri, const char* a_format, va_list a_arguments)
	{
		return xmlTextWriterWriteVFormatAttributeNS(v_writer, a_prefix, a_name, a_uri, a_format, a_arguments);
	}
	int f_write_attribute_ns(const std::wstring& a_prefix, const std::wstring& a_name, const std::wstring& a_uri, const std::wstring& a_content)
	{
		return f_integer(xmlTextWriterWriteAttributeNS(v_writer, f_cast(f_convert(a_prefix)), f_cast(f_convert(a_name)), f_cast(f_convert(a_uri)), f_cast(f_convert(a_content))));
	}
	int f_start_pi(const std::wstring& a_target)
	{
		return f_integer(xmlTextWriterStartPI(v_writer, f_cast(f_convert(a_target))));
	}
	int f_end_pi()
	{
		return f_integer(xmlTextWriterEndPI(v_writer));
	}
	int f_write_format_pi(const xmlChar* a_target, const char* a_format, ...)
	{
		va_list arguments;
		va_start(arguments, a_format);
		int n = f_write_vformat_pi(a_target, a_format, arguments);
		va_end(arguments);
		return n;
	}
	int f_write_vformat_pi(const xmlChar* a_target, const char* a_format, va_list a_arguments)
	{
		return xmlTextWriterWriteVFormatPI(v_writer, a_target, a_format, a_arguments);
	}
	int f_write_pi(const std::wstring& a_target, const std::wstring& a_content)
	{
		return f_integer(xmlTextWriterWritePI(v_writer, f_cast(f_convert(a_target)), f_cast(f_convert(a_content))));
	}
	int f_start_cdata()
	{
		return f_integer(xmlTextWriterStartCDATA(v_writer));
	}
	int f_end_cdata()
	{
		return f_integer(xmlTextWriterEndCDATA(v_writer));
	}
	int f_write_format_cdata(const char* a_format, ...)
	{
		va_list arguments;
		va_start(arguments, a_format);
		int n = f_write_vformat_cdata(a_format, arguments);
		va_end(arguments);
		return n;
	}
	int f_write_vformat_cdata(const char* a_format, va_list a_arguments)
	{
		return xmlTextWriterWriteVFormatCDATA(v_writer, a_format, a_arguments);
	}
	int f_write_cdata(const std::wstring& a_content)
	{
		return f_integer(xmlTextWriterWriteCDATA(v_writer, f_cast(f_convert(a_content))));
	}
	int f_start_dtd(const std::wstring& a_name, const std::wstring& a_public, const std::wstring& a_system)
	{
		return f_integer(xmlTextWriterStartDTD(v_writer, f_cast(f_convert(a_name)), f_cast(f_convert(a_public)), f_cast(f_convert(a_system))));
	}
	int f_end_dtd()
	{
		return f_integer(xmlTextWriterEndDTD(v_writer));
	}
	int f_write_format_dtd(const xmlChar* a_name, const xmlChar* a_public, const xmlChar* a_system, const char* a_format, ...)
	{
		va_list arguments;
		va_start(arguments, a_format);
		int n = f_write_vformat_dtd(a_name, a_public, a_system, a_format, arguments);
		va_end(arguments);
		return n;
	}
	int f_write_vformat_dtd(const xmlChar* a_name, const xmlChar* a_public, const xmlChar* a_system, const char* a_format, va_list a_arguments)
	{
		return xmlTextWriterWriteVFormatDTD(v_writer, a_name, a_public, a_system, a_format, a_arguments);
	}
	int f_write_dtd(const std::wstring& a_name, const std::wstring& a_public, const std::wstring& a_system, const std::wstring& a_subset)
	{
		return f_integer(xmlTextWriterWriteDTD(v_writer, f_cast(f_convert(a_name)), f_cast(f_convert(a_public)), f_cast(f_convert(a_system)), f_cast(f_convert(a_subset))));
	}
	int f_start_dtd_element(const std::wstring& a_name)
	{
		return f_integer(xmlTextWriterStartDTDElement(v_writer, f_cast(f_convert(a_name))));
	}
	int f_end_dtd_element()
	{
		return f_integer(xmlTextWriterEndDTDElement(v_writer));
	}
	int f_write_format_dtd_element(const xmlChar* a_name, const char* a_format, ...)
	{
		va_list arguments;
		va_start(arguments, a_format);
		int n = f_write_vformat_dtd_element(a_name, a_format, arguments);
		va_end(arguments);
		return n;
	}
	int f_write_vformat_dtd_element(const xmlChar* a_name, const char* a_format, va_list a_arguments)
	{
		return xmlTextWriterWriteVFormatDTDElement(v_writer, a_name, a_format, a_arguments);
	}
	int f_write_dtd_element(const std::wstring& a_name, const std::wstring& a_content)
	{
		return f_integer(xmlTextWriterWriteDTDElement(v_writer, f_cast(f_convert(a_name)), f_cast(f_convert(a_content))));
	}
	int f_start_dtd_attlist(const std::wstring& a_name)
	{
		return f_integer(xmlTextWriterStartDTDAttlist(v_writer, f_cast(f_convert(a_name))));
	}
	int f_end_dtd_attlist()
	{
		return f_integer(xmlTextWriterEndDTDAttlist(v_writer));
	}
	int f_write_format_dtd_attlist(const xmlChar* a_name, const char* a_format, ...)
	{
		va_list arguments;
		va_start(arguments, a_format);
		int n = f_write_vformat_dtd_attlist(a_name, a_format, arguments);
		va_end(arguments);
		return n;
	}
	int f_write_vformat_dtd_attlist(const xmlChar* a_name, const char* a_format, va_list a_arguments)
	{
		return xmlTextWriterWriteVFormatDTDAttlist(v_writer, a_name, a_format, a_arguments);
	}
	int f_write_dtd_attlist(const std::wstring& a_name, const std::wstring& a_content)
	{
		return f_integer(xmlTextWriterWriteDTDAttlist(v_writer, f_cast(f_convert(a_name)), f_cast(f_convert(a_content))));
	}
	int f_start_dtd_entity(bool a_parameter, const std::wstring& a_name)
	{
		return f_integer(xmlTextWriterStartDTDEntity(v_writer, a_parameter ? 1 : 0, f_cast(f_convert(a_name))));
	}
	int f_end_dtd_entity()
	{
		return f_integer(xmlTextWriterEndDTDEntity(v_writer));
	}
	int f_write_format_dtd_internal_entity(bool a_parameter, const xmlChar* a_name, const char* a_format, ...)
	{
		va_list arguments;
		va_start(arguments, a_format);
		int n = f_write_vformat_dtd_internal_entity(a_parameter, a_name, a_format, arguments);
		va_end(arguments);
		return n;
	}
	int f_write_vformat_dtd_internal_entity(bool a_parameter, const xmlChar* a_name, const char* a_format, va_list a_arguments)
	{
		return xmlTextWriterWriteVFormatDTDInternalEntity(v_writer, a_parameter ? 1 : 0, a_name, a_format, a_arguments);
	}
	int f_write_dtd_internal_entity(bool a_parameter, const std::wstring& a_name, const std::wstring& a_content)
	{
		return f_integer(xmlTextWriterWriteDTDInternalEntity(v_writer, a_parameter ? 1 : 0, f_cast(f_convert(a_name)), f_cast(f_convert(a_content))));
	}
	int f_write_dtd_external_entity(bool a_parameter, const std::wstring& a_name, const std::wstring& a_public, const std::wstring& a_system, const std::wstring& a_notation)
	{
		return f_integer(xmlTextWriterWriteDTDExternalEntity(v_writer, a_parameter ? 1 : 0, f_cast(f_convert(a_name)), f_cast(f_convert(a_public)), f_cast(f_convert(a_system)), f_cast(f_convert(a_notation))));
	}
	int f_write_dtd_external_entity(const std::wstring& a_public, const std::wstring& a_system, const std::wstring& a_notation)
	{
		return f_integer(xmlTextWriterWriteDTDExternalEntityContents(v_writer, f_cast(f_convert(a_public)), f_cast(f_convert(a_system)), f_cast(f_convert(a_notation))));
	}
	int f_write_dtd_entity(bool a_parameter, const std::wstring& a_name, const std::wstring& a_public, const std::wstring& a_system, const std::wstring& a_notation, const std::wstring& a_content)
	{
		return f_integer(xmlTextWriterWriteDTDEntity(v_writer, a_parameter ? 1 : 0, f_cast(f_convert(a_name)), f_cast(f_convert(a_public)), f_cast(f_convert(a_system)), f_cast(f_convert(a_notation)), f_cast(f_convert(a_content))));
	}
	int f_write_dtd_notation(const std::wstring& a_name, const std::wstring& a_public, const std::wstring& a_system)
	{
		return f_integer(xmlTextWriterWriteDTDNotation(v_writer, f_cast(f_convert(a_name)), f_cast(f_convert(a_public)), f_cast(f_convert(a_system))));
	}
	void f_set_indent(bool a_indent)
	{
		f_void(xmlTextWriterSetIndent(v_writer, a_indent ? 1 : 0));
	}
	void f_set_indent_string(const std::wstring& a_string)
	{
		f_void(xmlTextWriterSetIndentString(v_writer, f_cast(f_convert(a_string))));
	}
	int f_flush()
	{
		return f_integer(xmlTextWriterFlush(v_writer));
	}
};

}

}

namespace xemmai
{

using libxml::xemmai::t_text_writer;

template<>
struct t_type_of<t_text_writer> : t_type
{
	typedef libxml::xemmai::t_extension t_extension;

	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_type(a_module, a_super)
	{
	}
	virtual t_type* f_derive(t_object* a_this);
	virtual void f_finalize(t_object* a_this);
	virtual t_transfer f_construct(t_object* a_class, t_slot* a_stack, size_t a_n);
};

}

#endif

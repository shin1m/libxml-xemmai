#include "writer.h"

namespace xemmaix::libxml
{

namespace
{

struct t_context
{
	static int f_write(void* a_context, const char* a_p, int a_n)
	{
		auto p = static_cast<t_context*>(a_context);
		auto& bytes = f_as<t_bytes&>(p->v_bytes);
		if (a_n > bytes.f_size()) a_n = bytes.f_size();
		std::copy_n(a_p, a_n, &bytes[0]);
		try {
			p->v_write(p->v_bytes, f_global()->f_as(0), f_global()->f_as(a_n));
			return a_n;
		} catch (...) {
			return -1;
		}
	}
	static int f_close(void* a_context)
	{
		auto p = static_cast<t_context*>(a_context);
		p->v_close();
		delete p;
		return 0;
	}

	t_rvalue v_write;
	t_rvalue v_close;
	t_root v_bytes = t_bytes::f_instantiate(1024);
};

}

t_text_writer::t_text_writer(const t_pvalue& a_write, const t_pvalue& a_close) : v_writer(xmlNewTextWriter(xmlOutputBufferCreateIO(t_context::f_write, t_context::f_close, new t_context{a_write, a_close}, NULL)))
{
}

}

namespace xemmai
{

void t_type_of<xemmaix::libxml::t_text_writer>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::libxml;
	t_define<t_text_writer, t_object>(a_extension, L"TextWriter"sv)
		(
			t_construct<false, std::wstring_view, bool>(),
			t_construct<false, const t_pvalue&, const t_pvalue&>()
		)
		(L"free"sv, t_member<void(t_text_writer::*)(), &t_text_writer::f_free, t_with_lock_for_write>())
		(L"start_document"sv, t_member<int(t_text_writer::*)(const t_string*, const t_string*, const t_string*), &t_text_writer::f_start_document, t_with_lock_for_write>())
		(L"end_document"sv, t_member<int(t_text_writer::*)(), &t_text_writer::f_end_document, t_with_lock_for_write>())
		(L"start_comment"sv, t_member<int(t_text_writer::*)(), &t_text_writer::f_start_comment, t_with_lock_for_write>())
		(L"end_comment"sv, t_member<int(t_text_writer::*)(), &t_text_writer::f_end_comment, t_with_lock_for_write>())
		(L"write_comment"sv, t_member<int(t_text_writer::*)(std::wstring_view), &t_text_writer::f_write_comment, t_with_lock_for_write>())
		(L"start_element"sv, t_member<int(t_text_writer::*)(std::wstring_view), &t_text_writer::f_start_element, t_with_lock_for_write>())
		(L"start_element_ns"sv, t_member<int(t_text_writer::*)(std::wstring_view, std::wstring_view, std::wstring_view), &t_text_writer::f_start_element_ns, t_with_lock_for_write>())
		(L"end_element"sv, t_member<int(t_text_writer::*)(), &t_text_writer::f_end_element, t_with_lock_for_write>())
		(L"full_end_element"sv, t_member<int(t_text_writer::*)(), &t_text_writer::f_full_end_element, t_with_lock_for_write>())
		(L"write_element"sv, t_member<int(t_text_writer::*)(std::wstring_view, std::wstring_view), &t_text_writer::f_write_element, t_with_lock_for_write>())
		(L"write_element_ns"sv, t_member<int(t_text_writer::*)(std::wstring_view, std::wstring_view, std::wstring_view, std::wstring_view), &t_text_writer::f_write_element_ns, t_with_lock_for_write>())
		(L"write_raw"sv, t_member<int(t_text_writer::*)(std::wstring_view), &t_text_writer::f_write_raw, t_with_lock_for_write>())
		(L"write_string"sv, t_member<int(t_text_writer::*)(std::wstring_view), &t_text_writer::f_write_string, t_with_lock_for_write>())
//		(L"write_base64"sv, t_member<int(t_text_writer::*)(const char*, int, int), &t_text_writer::f_write_base64, t_with_lock_for_write>())
//		(L"write_bin_hex"sv, t_member<int(t_text_writer::*)(const char*, int, int), &t_text_writer::f_write_bin_hex, t_with_lock_for_write>())
		(L"start_attribute"sv, t_member<int(t_text_writer::*)(std::wstring_view), &t_text_writer::f_start_attribute, t_with_lock_for_write>())
		(L"start_attribute_ns"sv, t_member<int(t_text_writer::*)(std::wstring_view, std::wstring_view, std::wstring_view), &t_text_writer::f_start_attribute_ns, t_with_lock_for_write>())
		(L"end_attribute"sv, t_member<int(t_text_writer::*)(), &t_text_writer::f_end_attribute, t_with_lock_for_write>())
		(L"write_attribute"sv, t_member<int(t_text_writer::*)(std::wstring_view, std::wstring_view), &t_text_writer::f_write_attribute, t_with_lock_for_write>())
		(L"write_attribute_ns"sv, t_member<int(t_text_writer::*)(std::wstring_view, std::wstring_view, std::wstring_view, std::wstring_view), &t_text_writer::f_write_attribute_ns, t_with_lock_for_write>())
		(L"start_pi"sv, t_member<int(t_text_writer::*)(std::wstring_view), &t_text_writer::f_start_pi, t_with_lock_for_write>())
		(L"end_pi"sv, t_member<int(t_text_writer::*)(), &t_text_writer::f_end_pi, t_with_lock_for_write>())
		(L"write_pi"sv, t_member<int(t_text_writer::*)(std::wstring_view, std::wstring_view), &t_text_writer::f_write_pi, t_with_lock_for_write>())
		(L"start_cdata"sv, t_member<int(t_text_writer::*)(), &t_text_writer::f_start_cdata, t_with_lock_for_write>())
		(L"end_cdata"sv, t_member<int(t_text_writer::*)(), &t_text_writer::f_end_cdata, t_with_lock_for_write>())
		(L"write_cdata"sv, t_member<int(t_text_writer::*)(std::wstring_view), &t_text_writer::f_write_cdata, t_with_lock_for_write>())
		(L"start_dtd"sv, t_member<int(t_text_writer::*)(std::wstring_view, std::wstring_view, std::wstring_view), &t_text_writer::f_start_dtd, t_with_lock_for_write>())
		(L"end_dtd"sv, t_member<int(t_text_writer::*)(), &t_text_writer::f_end_dtd, t_with_lock_for_write>())
		(L"write_dtd"sv, t_member<int(t_text_writer::*)(std::wstring_view, std::wstring_view, std::wstring_view, std::wstring_view), &t_text_writer::f_write_dtd, t_with_lock_for_write>())
		(L"start_dtd_element"sv, t_member<int(t_text_writer::*)(std::wstring_view), &t_text_writer::f_start_dtd_element, t_with_lock_for_write>())
		(L"end_dtd_element"sv, t_member<int(t_text_writer::*)(), &t_text_writer::f_end_dtd_element, t_with_lock_for_write>())
		(L"write_dtd_element"sv, t_member<int(t_text_writer::*)(std::wstring_view, std::wstring_view), &t_text_writer::f_write_dtd_element, t_with_lock_for_write>())
		(L"start_dtd_attlist"sv, t_member<int(t_text_writer::*)(std::wstring_view), &t_text_writer::f_start_dtd_attlist, t_with_lock_for_write>())
		(L"end_dtd_attlist"sv, t_member<int(t_text_writer::*)(), &t_text_writer::f_end_dtd_attlist, t_with_lock_for_write>())
		(L"write_dtd_attlist"sv, t_member<int(t_text_writer::*)(std::wstring_view, std::wstring_view), &t_text_writer::f_write_dtd_attlist, t_with_lock_for_write>())
		(L"start_dtd_entity"sv, t_member<int(t_text_writer::*)(bool, std::wstring_view), &t_text_writer::f_start_dtd_entity, t_with_lock_for_write>())
		(L"end_dtd_entity"sv, t_member<int(t_text_writer::*)(), &t_text_writer::f_end_dtd_entity, t_with_lock_for_write>())
		(L"write_dtd_internal_entity"sv, t_member<int(t_text_writer::*)(bool, std::wstring_view, std::wstring_view), &t_text_writer::f_write_dtd_internal_entity, t_with_lock_for_write>())
		(L"write_dtd_external_entity"sv, t_member<int(t_text_writer::*)(bool, std::wstring_view, std::wstring_view, std::wstring_view, std::wstring_view), &t_text_writer::f_write_dtd_external_entity, t_with_lock_for_write>())
		(L"write_dtd_external_entity"sv, t_member<int(t_text_writer::*)(std::wstring_view, std::wstring_view, std::wstring_view), &t_text_writer::f_write_dtd_external_entity, t_with_lock_for_write>())
		(L"write_dtd_entity"sv, t_member<int(t_text_writer::*)(bool, std::wstring_view, std::wstring_view, std::wstring_view, std::wstring_view, std::wstring_view), &t_text_writer::f_write_dtd_entity, t_with_lock_for_write>())
		(L"write_dtd_notation"sv, t_member<int(t_text_writer::*)(std::wstring_view, std::wstring_view, std::wstring_view), &t_text_writer::f_write_dtd_notation, t_with_lock_for_write>())
		(L"set_indent"sv, t_member<void(t_text_writer::*)(bool), &t_text_writer::f_set_indent, t_with_lock_for_write>())
		(L"set_indent_string"sv, t_member<void(t_text_writer::*)(std::wstring_view), &t_text_writer::f_set_indent_string, t_with_lock_for_write>())
		(L"flush"sv, t_member<int(t_text_writer::*)(), &t_text_writer::f_flush, t_with_lock_for_write>())
	;
}

t_pvalue t_type_of<xemmaix::libxml::t_text_writer>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_overload<
		t_construct<false, std::wstring_view, bool>,
		t_construct<false, const t_pvalue&, const t_pvalue&>
	>::t_bind<xemmaix::libxml::t_text_writer>::f_do(this, a_stack, a_n);
}

}

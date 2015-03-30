#include "writer.h"

#include <xemmai/derived.h>

namespace xemmai
{

void t_type_of<t_text_writer>::f_define(t_extension* a_extension)
{
	t_define<t_text_writer, t_object>(a_extension, L"TextWriter")
		(t_construct<const std::wstring&, bool>())
		(L"free", t_member<void (t_text_writer::*)(), &t_text_writer::f_free, t_with_lock_for_write>())
		(L"start_document", t_member<int (t_text_writer::*)(const std::wstring*, const std::wstring*, const std::wstring*), &t_text_writer::f_start_document, t_with_lock_for_write>())
		(L"end_document", t_member<int (t_text_writer::*)(), &t_text_writer::f_end_document, t_with_lock_for_write>())
		(L"start_comment", t_member<int (t_text_writer::*)(), &t_text_writer::f_start_comment, t_with_lock_for_write>())
		(L"end_comment", t_member<int (t_text_writer::*)(), &t_text_writer::f_end_comment, t_with_lock_for_write>())
		(L"write_comment", t_member<int (t_text_writer::*)(const std::wstring&), &t_text_writer::f_write_comment, t_with_lock_for_write>())
		(L"start_element", t_member<int (t_text_writer::*)(const std::wstring&), &t_text_writer::f_start_element, t_with_lock_for_write>())
		(L"start_element_ns", t_member<int (t_text_writer::*)(const std::wstring&, const std::wstring&, const std::wstring&), &t_text_writer::f_start_element_ns, t_with_lock_for_write>())
		(L"end_element", t_member<int (t_text_writer::*)(), &t_text_writer::f_end_element, t_with_lock_for_write>())
		(L"full_end_element", t_member<int (t_text_writer::*)(), &t_text_writer::f_full_end_element, t_with_lock_for_write>())
		(L"write_element", t_member<int (t_text_writer::*)(const std::wstring&, const std::wstring&), &t_text_writer::f_write_element, t_with_lock_for_write>())
		(L"write_element_ns", t_member<int (t_text_writer::*)(const std::wstring&, const std::wstring&, const std::wstring&, const std::wstring&), &t_text_writer::f_write_element_ns, t_with_lock_for_write>())
		(L"write_raw", t_member<int (t_text_writer::*)(const std::wstring&), &t_text_writer::f_write_raw, t_with_lock_for_write>())
		(L"write_string", t_member<int (t_text_writer::*)(const std::wstring&), &t_text_writer::f_write_string, t_with_lock_for_write>())
//		(L"write_base64", t_member<int (t_text_writer::*)(const char*, int, int), &t_text_writer::f_write_base64, t_with_lock_for_write>())
//		(L"write_bin_hex", t_member<int (t_text_writer::*)(const char*, int, int), &t_text_writer::f_write_bin_hex, t_with_lock_for_write>())
		(L"start_attribute", t_member<int (t_text_writer::*)(const std::wstring&), &t_text_writer::f_start_attribute, t_with_lock_for_write>())
		(L"start_attribute_ns", t_member<int (t_text_writer::*)(const std::wstring&, const std::wstring&, const std::wstring&), &t_text_writer::f_start_attribute_ns, t_with_lock_for_write>())
		(L"end_attribute", t_member<int (t_text_writer::*)(), &t_text_writer::f_end_attribute, t_with_lock_for_write>())
		(L"write_attribute", t_member<int (t_text_writer::*)(const std::wstring&, const std::wstring&), &t_text_writer::f_write_attribute, t_with_lock_for_write>())
		(L"write_attribute_ns", t_member<int (t_text_writer::*)(const std::wstring&, const std::wstring&, const std::wstring&, const std::wstring&), &t_text_writer::f_write_attribute_ns, t_with_lock_for_write>())
		(L"start_pi", t_member<int (t_text_writer::*)(const std::wstring&), &t_text_writer::f_start_pi, t_with_lock_for_write>())
		(L"end_pi", t_member<int (t_text_writer::*)(), &t_text_writer::f_end_pi, t_with_lock_for_write>())
		(L"write_pi", t_member<int (t_text_writer::*)(const std::wstring&, const std::wstring&), &t_text_writer::f_write_pi, t_with_lock_for_write>())
		(L"start_cdata", t_member<int (t_text_writer::*)(), &t_text_writer::f_start_cdata, t_with_lock_for_write>())
		(L"end_cdata", t_member<int (t_text_writer::*)(), &t_text_writer::f_end_cdata, t_with_lock_for_write>())
		(L"write_cdata", t_member<int (t_text_writer::*)(const std::wstring&), &t_text_writer::f_write_cdata, t_with_lock_for_write>())
		(L"start_dtd", t_member<int (t_text_writer::*)(const std::wstring&, const std::wstring&, const std::wstring&), &t_text_writer::f_start_dtd, t_with_lock_for_write>())
		(L"end_dtd", t_member<int (t_text_writer::*)(), &t_text_writer::f_end_dtd, t_with_lock_for_write>())
		(L"write_dtd", t_member<int (t_text_writer::*)(const std::wstring&, const std::wstring&, const std::wstring&, const std::wstring&), &t_text_writer::f_write_dtd, t_with_lock_for_write>())
		(L"start_dtd_element", t_member<int (t_text_writer::*)(const std::wstring&), &t_text_writer::f_start_dtd_element, t_with_lock_for_write>())
		(L"end_dtd_element", t_member<int (t_text_writer::*)(), &t_text_writer::f_end_dtd_element, t_with_lock_for_write>())
		(L"write_dtd_element", t_member<int (t_text_writer::*)(const std::wstring&, const std::wstring&), &t_text_writer::f_write_dtd_element, t_with_lock_for_write>())
		(L"start_dtd_attlist", t_member<int (t_text_writer::*)(const std::wstring&), &t_text_writer::f_start_dtd_attlist, t_with_lock_for_write>())
		(L"end_dtd_attlist", t_member<int (t_text_writer::*)(), &t_text_writer::f_end_dtd_attlist, t_with_lock_for_write>())
		(L"write_dtd_attlist", t_member<int (t_text_writer::*)(const std::wstring&, const std::wstring&), &t_text_writer::f_write_dtd_attlist, t_with_lock_for_write>())
		(L"start_dtd_entity", t_member<int (t_text_writer::*)(bool, const std::wstring&), &t_text_writer::f_start_dtd_entity, t_with_lock_for_write>())
		(L"end_dtd_entity", t_member<int (t_text_writer::*)(), &t_text_writer::f_end_dtd_entity, t_with_lock_for_write>())
		(L"write_dtd_internal_entity", t_member<int (t_text_writer::*)(bool, const std::wstring&, const std::wstring&), &t_text_writer::f_write_dtd_internal_entity, t_with_lock_for_write>())
		(L"write_dtd_external_entity", t_member<int (t_text_writer::*)(bool, const std::wstring&, const std::wstring&, const std::wstring&, const std::wstring&), &t_text_writer::f_write_dtd_external_entity, t_with_lock_for_write>())
		(L"write_dtd_external_entity", t_member<int (t_text_writer::*)(const std::wstring&, const std::wstring&, const std::wstring&), &t_text_writer::f_write_dtd_external_entity, t_with_lock_for_write>())
		(L"write_dtd_entity", t_member<int (t_text_writer::*)(bool, const std::wstring&, const std::wstring&, const std::wstring&, const std::wstring&, const std::wstring&), &t_text_writer::f_write_dtd_entity, t_with_lock_for_write>())
		(L"write_dtd_notation", t_member<int (t_text_writer::*)(const std::wstring&, const std::wstring&, const std::wstring&), &t_text_writer::f_write_dtd_notation, t_with_lock_for_write>())
		(L"set_indent", t_member<void (t_text_writer::*)(bool), &t_text_writer::f_set_indent, t_with_lock_for_write>())
		(L"set_indent_string", t_member<void (t_text_writer::*)(const std::wstring&), &t_text_writer::f_set_indent_string, t_with_lock_for_write>())
		(L"flush", t_member<int (t_text_writer::*)(), &t_text_writer::f_flush, t_with_lock_for_write>())
	;
}

t_type* t_type_of<t_text_writer>::f_derive(t_object* a_this)
{
	return new t_derived<t_type_of>(v_module, a_this);
}

void t_type_of<t_text_writer>::f_finalize(t_object* a_this)
{
	delete f_as<t_text_writer*>(a_this);
}

t_scoped t_type_of<t_text_writer>::f_construct(t_object* a_class, t_scoped* a_stack, size_t a_n)
{
	return t_construct<const std::wstring&, bool>::t_bind<t_text_writer>::f_do(a_class, a_stack, a_n);
}

}

system = Module("system"
print = system.out.write_line
libxml = Module("libxml"
assert = @(x) x || throw Throwable("Assertion failed."

test = @(Writer)
	target = ""
	writer = Writer(
		@(buffer, offset, size)
			while size > 0
				:target = target + String.from_code(buffer[offset])
				offset = offset + 1
				size = size - 1
		@ null
	try
		writer.start_document("1.0", "utf-8", "yes"
		writer.start_element("foo"
		writer.write_string("bar"
		writer.end_element(
		writer.end_document(
	finally
		writer.free(
	print(target
	assert(target == "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<foo>bar</foo>\n"

test(libxml.TextWriter
test(libxml.TextWriter + @

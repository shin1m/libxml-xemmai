system = Module("system"
print = system.out.write_line
libxml = Module("libxml"
assert = @(x) x || throw Throwable("Assertion failed."

array_equals = @(x, y)
	n = x.size()
	n == y.size() || return false
	for i = 0; i < n; i = i + 1; x[i] == y[i] || return false
	true

source = @(bytes)
	n = bytes.size(
	i = 0
	@(buffer, offset, size)
		size > n && (size = n)
		for j = 0; j < size; j = j + 1
			buffer[offset] = bytes.code_at(i
			:i = i + 1
			offset = offset + 1
		:n = n - size
		size

test = @(Reader)
	reader = Reader(source("<foo>bar</foo>"), @ null, "urn:foo", "utf-8", 0
	try
		nodes = [
		while reader.read()
			nodes.push('(
				reader.node_type(
				reader.name(
				reader.value(
	finally
		reader.free(
	print(nodes
	assert(array_equals(nodes, '(
		'(libxml.ReaderTypes.ELEMENT, "foo", ""
		'(libxml.ReaderTypes.TEXT, "#text", "bar"
		'(libxml.ReaderTypes.END_ELEMENT, "foo", ""

test(libxml.TextReader
test(libxml.TextReader + @

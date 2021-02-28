add_library(libxml MODULE reader.cc writer.cc io.cc libxml.cc)
target_link_libraries(libxml xemmai LibXml2::LibXml2 CURL::libcurl)
set_property(TARGET libxml PROPERTY PREFIX "")

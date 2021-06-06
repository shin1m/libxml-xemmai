#ifndef XEMMAIX__LIBXML__CURL_H
#define XEMMAIX__LIBXML__CURL_H

#include <algorithm>
#include <deque>
#include <stdexcept>
#include <curl/curl.h>

namespace xemmaix::libxml
{

class t_curl
{
	static size_t f_write(char* a_p, size_t a_size, size_t a_n, void* a_user)
	{
		auto& buffer = static_cast<t_curl*>(a_user)->v_buffer;
		a_size *= a_n;
		buffer.insert(buffer.end(), a_p, a_p + a_size);
		return a_size;
	}

	CURL* v_curl = curl_easy_init();
	CURLM* v_curlm = curl_multi_init();
	std::deque<char> v_buffer;
	int v_running;

public:
	t_curl(const char* a_url)
	{
		curl_easy_setopt(v_curl, CURLOPT_WRITEFUNCTION, f_write);
		curl_easy_setopt(v_curl, CURLOPT_WRITEDATA, this);
		curl_easy_setopt(v_curl, CURLOPT_URL, a_url);
		curl_easy_setopt(v_curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(v_curl, CURLOPT_TIMEOUT, 180L);
		curl_multi_add_handle(v_curlm, v_curl);
		if (curl_multi_perform(v_curlm, &v_running) != CURLM_OK) throw std::runtime_error("curl_multi_perform");
	}
	~t_curl()
	{
		if (v_curl != NULL) f_close();
	}
	void f_close()
	{
		if (v_curl == NULL) throw std::runtime_error("already closed.");
		curl_multi_remove_handle(v_curlm, v_curl);
		curl_multi_cleanup(v_curlm);
		v_curlm = NULL;
		curl_easy_cleanup(v_curl);
		v_curl = NULL;
	}
	operator bool() const
	{
		return !v_buffer.empty() || v_running > 0;
	}
	size_t f_read(char* a_p, size_t a_n)
	{
		if (v_curl == NULL) throw std::runtime_error("already closed.");
		if (v_running > 0 && v_buffer.size() < a_n)
			while (true) {
				if (curl_multi_perform(v_curlm, &v_running) != CURLM_OK) throw std::runtime_error("curl_multi_perform");
				if (v_running <= 0 || v_buffer.size() >= a_n) break;
				if (curl_multi_wait(v_curlm, NULL, 0, 60000, NULL) != CURLM_OK) throw std::runtime_error("curl_multi_wait");
			}
		if (v_buffer.empty()) return 0;
		if (v_buffer.size() < a_n) a_n = v_buffer.size();
		std::copy_n(v_buffer.begin(), a_n, a_p);
		v_buffer.erase(v_buffer.begin(), v_buffer.begin() + a_n);
		return a_n;
	}
};

}

#endif

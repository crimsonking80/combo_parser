#include "data_provider.hpp"

#include <curl/curl.h>

DataProvider::DataProvider()
{
  static class curl_init
  {
  public:
    curl_init() { curl_global_init(CURL_GLOBAL_DEFAULT); }
    ~curl_init() { curl_global_cleanup(); }
  } inited;

  handle = curl_easy_init();
  if(!handle)
    std::cerr << "curl_easy_init() failed." << std::endl;
}

DataProvider::~DataProvider()
{
  curl_easy_cleanup(handle);
}

std::string DataProvider::escape(const std::string &url) const
{
  std::string result;

  if(handle)
  {
    char *const escaped = curl_easy_escape(handle, url.c_str(), static_cast<int>(url.size()));
    if(escaped)
    {
      result = escaped;

      curl_free(escaped);
    }
  }

  return result;
}

static size_t callback(void *buffer, size_t size, size_t count, void *ptr)
{
  size_t result = 0;

  std::ostream *const stream = static_cast<std::ostream *>(ptr);
  if(stream)
  {
    result = size*count;

    if(!stream->write(reinterpret_cast<const char *>(buffer), result))
    {
      std::cerr << "std::ostream::write() failed." << std::endl;
      return 0;
    }
  }

  return result;
}

bool DataProvider::get(const std::string &url, std::ostream &out)
{
  if(!handle)
    return false;

  curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
  curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, true);
  curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, false);
  curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, false);
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, callback);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, &out);

  const CURLcode code = curl_easy_perform(handle);
  if(code != CURLE_OK)
  {
    std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(code) << "." << std::endl;
    return false;
  }

  return true;
}

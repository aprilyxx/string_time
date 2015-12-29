uint64 StrToInt(const std::string& s){
uint64 v=0;
for(uint32 i = 0; i<s.size(); ++i)
{
  char c = s[i];
  CHECK(c >= '0' && c <= '9) << "invalid value for interger:" << s;
  v *= 10;
  v += (c - '0');
}
return v;
}
template<typename T>
std::string IntToStr(T v){
  std::string s;
  if (v >= 0) {
    do {
     s += (v % 10 + '0');
     v /= 10;
    }while(v != 0);
    std::reverse(s.begin(), s.end());
    return s;
  }
  return '-' + IntToString(-v);
}
bool ConvertToUTF8(char const* s, size_t bytes, std::string*d){
  if (bytes == 0) return true;
   const wchar_t* ws = (const wchar_t*) s;
   uint32 len = bytes / sizeof(wchar_t);
   int size = ::WideCharToMultiByte(CP_UTF8, 0, ws, len, NULL, 0, NULL, NULL);
   d->resize(size);
   int ret = ::WideCharToMultiByte(CP_UTF8, 0, ws, len, &d->at(0), size, NULL, NULL);
   return true;
}
bool ConvertToUTF16(std::string const& s, std::string* d){
  if(s.empty()) return true;
  int size = ::MultiByteToWideChar(CP_UTF8, 0, s.data(), s.size(), NULL, 0);
  d->resize(size * sizeof(wchar_t));
  int ret = ::MultiByteToWideChar(CP_UTF8, 0, s.data(), s.size(), (wchar_t*)&d->at(0), size);
  return true;
}

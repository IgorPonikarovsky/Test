#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "netapi32.lib")

#include <napi.h>
#include <string>
#include <windows.h>
#include <lm.h>
#include <iostream>
#include <fstream>

wchar_t* StringToWcharT(std::string str){
  char *cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());
  wchar_t* wchar;
  wchar = (wchar_t*)calloc(str.length() + 1, sizeof(wchar_t));
  MultiByteToWideChar(CP_UTF8, 0, cstr, -1, wchar, str.length()+1);
  return wchar;
}

Napi::Boolean UserCheck(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string userName = info[0].As<Napi::String>().ToString();
  //Проверяем есть ли пользователь
  DWORD dwLevel = 0; // 0 - вернеться только имя пользователя
  LPUSER_INFO_0 pBuf = NULL;//Информация о пользователе
  if(NetUserGetInfo(NULL, StringToWcharT(userName), dwLevel, (LPBYTE *) & pBuf) == NERR_UserNotFound){
      return Napi::Boolean::New(env, false);
  }
  return Napi::Boolean::New(env, true);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "UserCheck"),
              Napi::Function::New(env, UserCheck));
  return exports;
}

NODE_API_MODULE(UserCheck, Init)
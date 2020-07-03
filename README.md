# DetoursLibrary
Little detours library.
-----
# Little Detours Library.

Возвращает true в случае успеха.
long* source - указатель на оригинальную функцию.
long* destination - указатель на вашу функцию для перехвата.
```cpp
bool	Install(long* source, long* destination);
```
Возвращает true в случае успеха.
Используется для повторной установки хука.
```cpp
bool	ReInstall();
```
Возвращает true в случае успеха.
Снимает хук с функции.
```cpp
bool	UnInstall();
```
Возвращает адрес функции szFunctionName из библиотеки szLibName если та найдена.
В противном случае возвращает NULL.
```cpp
long*	FindFunction(LPCWSTR szLibName, LPCSTR szFunctionName);
```
Возвращает статус хука.
```cpp
bool	IsInstalled();
```

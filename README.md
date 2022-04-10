# Self-Implemented Exceptions

В файле `achtung.hpp` представлена реализация исключений.

Макросы `TRY`, `CATCH` и `THROW` позволяют реализовывать все базовые сценарии их использования. Например, можно использовать разные обработчики на разные типы исключений (они все представлены в `AchtungType`, можно добавлять новые).

В качестве демонстрации поставляется файл `test.cpp`. При запуске скрипта `run.sh` ожидается следующий вывод:

```
Test A: handled AchtungType::DOES_NOT_EXIST
File doesntexist does not exist

Test B: unhandled AchtungType::MEMORY
Failed with achtung 20

Test C: handled AchtungType::FD_LIMIT
No more file descriptors available
```

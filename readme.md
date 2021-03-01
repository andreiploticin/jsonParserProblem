В классе парсера 2 конструтора:

`JsonParser(std::istream &)` для разбора из файла и потока ввода,

`JsonParser(const std::string &)` для разбора строки.


В данной реализации строки (JSON string) не могут содежать escape-последовательность **\\"** (строка разбирается от символа " до символа ").
Вне строк пробелы и символы **\t \n \r** игнорируются.

Вызов `JsonParser::parse()` производит разбор.

Наличие ошибок при разборе проверяется `JsonParser::isError()`.

Результатом разбора является объект **JsonValue**. Тип **JsonValue** синоним JSON value для упрощённой граматики.
Для доступа к данным объекта применимы операторы `JsonValue::stringValue()`, `objectValue()`, `arrayValue`, операторы индексирования.

В **example** показан пример разбора строки и пользовательского ввода с последующим выводом результата.
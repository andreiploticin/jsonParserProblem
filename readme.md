Упрощённая JSON грамматика на основе полной (https://www.crockford.com/mckeeman.html). 

В классе парсера 2 конструктора:

`JsonParser(std::istream &)` для разбора из файла и потока ввода,

`JsonParser(const std::string &)` для разбора строки.

В данной реализации строки (JSON string) не могут содержать escape-последовательность **\\"** (строка разбирается от символа " до символа ").
Вне строк пробелы и символы **\t \n \r** игнорируются.

Вызов `JsonParser::parse()` производит разбор.

Наличие ошибок при разборе проверяется `JsonParser::isError()`.

Результатом разбора является объект **JsonValue**. Тип **JsonValue** синоним JSON value для упрощённой грамматики.
Для доступа к данным объекта применимы операторы `JsonValue::stringValue()`, `objectValue()`, `arrayValue`, операторы индексирования.

Доступно следующее обращение:
```
JsonParser parser1("{\"name1\":[\"a1\", \"a2\", {\"name2\":\"value1\", \"name3\":\"value2\"}]}");
std::cout << parser1.parse()["name1"][2]["name3"].stringValue();
```
В **example** показан пример разбора строки и пользовательского ввода с последующим выводом результата.

В тесте `(JsonTests, ReadFromFile)` разбирается файл `test.json`
# Вычислительная математика

## Нелинейные уравнения и системы уравнений

### Лабораторная работа №1. Распад разрыва в механике сплошной среды.

Лабораторная работа выполнена при помощи C++20 и дополнительной библиотеки nlohmann-json, позволяющей работать с json-файлами и представляет собой консольное приложение, решающее задачу при помощи итерационного процесса Ньютона. Результат работы приложение выводится в консоли.

#### Структура проекта

```
| release
|──|log
|  |── output.log - лог работы программы
|
|──|system
|  |──|config
|     |──|model
|        |── config.json
|
|─── project.exe - исполняемый файл
```

Здесь:

- log - папка с логом работы программы, создаётся автоматически при первом запуске (нет в репозитории)
- output.log - лог работы программы
- [config.json](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/release/system/config/model/config.json) - файл с параметрами задачи. На данный момент поддерживается только первый вариант, поэтому рекомендуется изменять только числа в зависимости от выбранной задачи.
- [project.exe](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/release/project.exe) - исполняемый файл

#### Структура кода

```
|project - содержит дополнительные файлы, генерируемые MSVS
|source - исходники проекта
|───|source
|   |───|model
|   |   |───|wave
|   |   |   |─── wave.cpp
|   |   |   |─── wave.hpp
|   |   |
|   |   |─── model.cpp
|   |   |─── model.hpp
|   |
|   |───|polynom
|       |───|solver
|       |   |───|localizer
|       |   |   |─── localizer.cpp
|       |   |   |─── localizer.hpp
|       |   |
|       |   |─── solver.cpp
|       |   |─── solver.hpp
|       |
|       |─── polynom.hpp
|
|───|system
|   |─── system.cpp
|   |─── system.hpp
|
|───|utility
|   |───|logger - содержит класс Logger, работающий с логгером программы
|       |─── logger.cpp
|       |─── logger.hpp
|
|─── main.cpp - основной файл
```

Здесь:

- project - содержит дополнительные файлы, генерируемые MSVS
- source - исходники проекта
- wave - представляет простую структуру волны
	- [wave.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/source/model/wave/wave.cpp)
	- [wave.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/source/model/wave/wave.hpp)
- model - представляет класс рассматриваемой физической модели. Содержит определения всех коэффициентов задачи
	- [model.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/source/model/model.cpp)
	- [model.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/source/model/model.hpp)
- polynom - представляет шаблон полинома. В работе используется double
	- [polynom.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/source/polynom/polynom.hpp)
- solver - вспомогательный класс, решающий уравнение P(x) = 0 при помощи итерационного процесса Ньютона.
	- [solver.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/source/polynom/solver/solver.cpp)
	- [solver.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/source/polynom/solver/solver.hpp)
- localizer - вспомогательный класс, локализующий решения уравнения P(x) = 0
	- [localizer.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/source/polynom/solver/localizer/localizer.cpp)
	- [localizer.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/source/polynom/solver/localizer/localizer.hpp)
- system - класс, отвечающий за запуск приложение и работу с доступными ресурсами
	- [system.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/system/system.cpp)
	- [system.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/system/system.hpp)
- logger - класс, работающий с логом программы
	- [logger.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/utility/logger/logger.cpp)
	- [logger.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/utility/logger/logger.hpp)
- [main.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/main.cpp) - основной файл программы
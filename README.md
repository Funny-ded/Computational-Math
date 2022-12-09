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
- system - класс, отвечающий за запуск приложения и работу с доступными ресурсами
	- [system.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/system/system.cpp)
	- [system.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/system/system.hpp)
- logger - класс, работающий с логом программы
	- [logger.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/utility/logger/logger.cpp)
	- [logger.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/utility/logger/logger.hpp)
- [main.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/source/main.cpp) - основной файл программы

## Аналитическое приближение функций

### Лабораторная работа №2. Интерполяция. Сплайны

Лабораторная работа выполнена при помощи C++20 и дополнительной библиотеки nlohmann-json, позволяющей работать с json-файлами и представляет собой консольное приложение, решающее задачу интерполяции при помощи построения многочленов в форме Лагранжа и Ньютона. Результат работы приложение выводится в консоли.

#### Структура проекта

```
| release
|──|log
|  |── output.log - лог работы программы
|
|──|system
|  |──|config
|     |── values.json
|
|─── project.exe - исполняемый файл
```

Здесь:

- log - папка с логом работы программы, создаётся автоматически при первом запуске (нет в репозитории)
- output.log - лог работы программы
- [values.json](https://github.com/Funny-ded/Computational-Math/blob/master/lab_2/release/system/config/values.json) - файл с параметрами задачи. На данный момент записаны данные для 16 варианта работы, но поддерживается любой вариант.
- [project.exe](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/release/project.exe) - исполняемый файл

#### Структура кода

```
|project - содержит дополнительные файлы, генерируемые MSVS
|source - исходники проекта
|───|source
|   |───|interpolate
|   |   |─── interpolate.cpp
|   |   |─── interpolate.hpp
|   |
|   |───|spline
|   |   |─── spline.cpp
|   |   |─── spline.hpp
|   |
|   |───|polynom
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
- polynom - представляет шаблон полинома. В работе используется double
	- [polynom.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_2/source/source/polynom/polynom.hpp)
- interpolation - базовый класс интерполяции. От него наследуются классы Newton и Lagrange, которые вычисляют многочлены Ньютона и Лагранжа соответственно.
	- [interpolation.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_2/source/interpolation/interpolation.cpp)
	- [interpolation.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_2/source/interpolation/interpolation.hpp)
- spline - базовый класс сплайна. От него наследуется класс Cubic, который выполняет построение кубического сплайна по заданным парам чисел. (пара узлов сетки, пара значений функции и пара производных)
	- [spline.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_2/source/spline/spline.cpp)
	- [spline.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_2/source/spline/spline.hpp)
- system - класс, отвечающий за запуск приложения и работу с доступными ресурсами и модулями.
	- [system.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_2/source/system/system.cpp)
	- [system.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_2/source/system/system.hpp)
- logger - класс, работающий с логом программы
	- [logger.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_2/source/utility/logger/logger.cpp)
	- [logger.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_2/source/utility/logger/logger.hpp)
- [main.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_2/source/main.cpp) - основной файл программы

## Обыкновенные дифференциальные уравнения

### Лабораторная работа №3. Метод Рунге-Кутты решения задачи Коши для обыкновенных дифференциальных уравнений первого порядка.

Лабораторная работа выполнена при помощи C++20 и представляет собой консольное приложение, решающее задачу Коши при помощи метода Эйлера с пересчётом для уравнения №5. Результат работы приложение выводится в консоли.

#### Структура проекта

```
| release
|──|log
|  |── output.log - лог работы программы
|
|─── project.exe - исполняемый файл
```

Здесь:

- log - папка с логом работы программы, создаётся автоматически при первом запуске (нет в репозитории)
- output.log - лог работы программы
- [project.exe](https://github.com/Funny-ded/Computational-Math/blob/master/lab_1/release/project.exe) - исполняемый файл

#### Структура кода

```
|project - содержит дополнительные файлы, генерируемые MSVS
|source - исходники проекта
|───|source
|   |───|cauchy_problem
|       |───|diff_equation
|       |   |─── diff_equation.cpp
|       |   |─── diff_equation.hpp
|       |
|       |───|solver
|       |   |───|butcher_table
|       |   |   |─── butcher_table.hpp
|       |   |
|       |   |─── solver.cpp
|       |   |─── solver.hpp
|       |
|       |─── cauchy_problem.cpp
|       |─── cauchy_problem.hpp
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
- cauchy_problem - представляет основной класс задачи Коши для некторого дифференциального уравнения
	- [cauchy_problem.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_3/source/source/cauchy_problem/cauchy_problem.cpp)
	- [cauchy_problem.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_3/source/source/cauchy_problem/cauchy_problem.hpp)
- diff_equation - структура обыкновенного дифференциального уравнения
	- [diff_equation.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_3/source/source/cauchy_problem/diff_equation/diff_equation.hpp)
- solver - иерархия, базовый класс которой решает задачу Коши в общем виде. От него наследуется класс, решающий задачу при помощи метода Эйлера с пересчётом.
	- [solver.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_3/source/source/cauchy_problem/solver/solver.cpp)
	- [solver.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_3/source/source/cauchy_problem/solver/solver.hpp)
- butcher_table - структура таблицы Бутчера
	- [butcher_table.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_3/source/source/cauchy_problem/solver/butcher_table/butcher_table.hpp)
- system - класс, отвечающий за запуск приложения и работу с доступными ресурсами и модулями.
	- [system.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_3/source/system/system.cpp)
	- [system.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_3/source/system/system.hpp)
- logger - класс, работающий с логом программы
	- [logger.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_3/source/utility/logger/logger.cpp)
	- [logger.hpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_3/source/utility/logger/logger.hpp)
- [main.cpp](https://github.com/Funny-ded/Computational-Math/blob/master/lab_3/source/main.cpp) - основной файл программы
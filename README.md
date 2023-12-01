# Logger

### data

name:string,
level:LogLevel,
appender:vector< LogAppender >
formatter:LogFormatter

### functions

log
warn
error
fatal
addAppender
delAppender
clearAppender
setFormatter
setLevel


# LogAppender

控制log呈现方式

### data

level:LogLevel
formatter:LogFormatter

### functions

log
toYamlString

---

# LogFormatter

控制log格式

### data

formatter:string
items:vector< FormatItem >

### functions

format

# FileLogAppender ：继承 LogAppender

log到文件，提供输出为yaml格式的配置文件

### data

file:string

### functions

log
toYamlString

# StdoutLogAppender ：继承 LogAppender

log到控制台，提供输出为yaml格式的配置文件

### functions

log
toYamlString

# FormatItem ：被LogFomatter拥有

### functions

format

## XXFormatIten ：继承 FormatIten

### functions

format

提供：
XX(m, MessageFormatItem),
XX(p, LevelFormatItem),
XX(r, ElapseFormatItem),
XX(c, NameFormatItem),
XX(t, ThreadIdFormatItem),
XX(n, NewLineFormatItem),
XX(d, DateTimeFormatItem),
XX(f, FilenameFormatItem),
XX(l, LineFormatItem),
XX(T, TabFormatItem),
XX(F, FiberIdFormatItem),

实现各种格式灵活组合

---

---

# Config

静态初始化，初始配置
提供Lookup实现输入输出和修改配置情况

### data

variables:map<>

### function

Lookup

# ConfigVarBase

配置属性基类

### data

name:string
description:string

### functions

fromString
toString

# template< T > ConfigVar ：继承 ConfigVarBase

控制各配置类型与string之间的转换

### data

val:T

### function

fromString
toString
getValue

# template< F, T > LexicalCast

以各种偏特化实现各种类型与string的转换

### functions

operator()(F):T



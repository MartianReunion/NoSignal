# Classe CppDoc

## Fonction `gendoc_auto()`

**Description:** 自动生成文档，无需选择语言

**Paramètre** `path` : 文件路径

## Fonction `gendoc()`

**Description:** 生成文档，手动选择语言

**Paramètre** `path` : 文件路径

**Paramètre** `lang` : 语言

## Fonction `gendoc_all()`

**Description:** 生成一个目录下的所有文件的文档，甚至是递归遍历

**Paramètre** `path` : 目录

**Paramètre** `lang` : 语言

## Fonction `gendoc_all_auto()`

**Description:** 自动生成一个目录下的所有文件的文档，甚至是递归遍历，而且无需选择语言

**Paramètre** `path` : 目录

## Fonction `iscomment()`

**Description:** 判断一行代码是不是注释

**Paramètre** `x` : 代码

## Fonction `isclass()`

**Description:** 判断一行代码是不是类的声明

**Paramètre** `x` : 代码

## Fonction `getnames()`

**Description:** 获取一行代码中函数的名字，参数的变量类型，以及参数名字

**Paramètre** `x` : 代码

## Fonction `isgood()`

**Description:** 判断字符ch是不是0~9或A~Z或a~z

**Paramètre** `ch` : 字符

## Fonction `getbetween()`

**Description:** 获取一个字符串中l字符串到r字符串之间的部分，不包含l和r

**Paramètre** `x` : 字符串

**Paramètre** `l` : 字符串

**Paramètre** `r` : 字符串

## Fonction `substring()`

**Description:** 获取字符串中l下标到r下标之间的部分，包含l但不包含r

**Paramètre** `x` : 字符串

**Paramètre** `l` : 下标

**Paramètre** `r` : 下标

## Fonction `getbetween_auto()`

**Description:** 自动获取字符串中l字符串到r字符串之间的部分，包含l但不包含r，如果r找不到，默认为字符串尾部

**Paramètre** `x` : 字符串

**Paramètre** `l` : 字符串

**Paramètre** `r` : 字符串

## Fonction `getclass()`

**Description:** 获取一行代码中的类的声明

**Paramètre** `x` : 代码


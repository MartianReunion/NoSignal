# Class FileManager

## Function `isconverted()`

**Description:** 判断路径是否是转换后的

**Parameter** `path` : 路径

## Function `convertpath()`

**Description:** 转换路径格式，转换失败返回GAMEDIRROOT，注意如果你把已经转换的输进去也会转换失败

**Parameter** `x` : 待转换的路径

## Function `getallfile()`

**Description:** 获取一个目录下的所有文件并把路径装进vector里

**Parameter** `path` : 目录

**Parameter** `&x` : vector

## Function `getallfile_todo()`

**Description:** 对一个目录下的包括子目录的所有文件的目录进行操作

**Parameter** `path` : 目录（可以为未转换的）

## Function `getallfile_todo_byhand()`

**Description:** 对一个目录下的包括子目录的所有文件的目录进行操作，由func决定是否向下遍历，true=向下

**Parameter** `path` : 目录（可以为未转换的）


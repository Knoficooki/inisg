![inisg logo](inisg_small.png)

Logo-font: Overpass Mono designed by Delve Withrington, Dave Bailey, Thomas Jockin 

# inisg
This is a commandline program which allows you to load, save and create files with ini syntax. Get and set key values.

## License
This project is under the [GNU GPL v2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html) licence.

[GNU GENERAL PUBLIC LICENSE Version 2](./LICENSE)

## Syntax:

---
> __[Normal-Mode](#normal-mode):__
>
>> [inisg load -f {file} (--force)](#load)
>>
>> [inisg save (-f {file}) (--keep)](#save)
>>
>> [inisg set (-s {section}) -k {key} -v {value}](#set)
>>
>> [inisg get (-s {section}) -k {key} (-v {default value}) (-f {file}) (--delete) (--trunc)](#get)
>>
>> [inisg del (-s {section} &// -k {key})](#del)
>>
>> [inisg new (-f {file}) (--force)](#new)
>>
>> [inisg clear (--force)](#clear)

---

> __[Inside-Mode](#inside-mode)__:
>
>> [inisg inside set -f {file} (-s {section}) -k {key} -v {value}](#set-1)
>>
>> [inisg inside get -f {file} (-s {section}) -k {key} (-v {default value}) (--out (-f {output file}) (--trunc))](#get-1)
>>
>> [inisg inside del -f {file} (-s {section} &// -k {key})](#del-1)
>>
>> [inisg inside new -f {file} (--from -f {from file})](#new-1)
---

<br>
<br>
<br>

## How does it Work?

### Flags

> #### -f {file}
> `-f` means there is a filepath in the next argument.

> #### -s {section}
> Sets the section. Can be ignored, if you want to select the global(or empty) section (aka section="").

> #### -k {key}
> Sets the key which referes to the value.

> #### -v {value}
> Can be used to set a key to this value or to return it if the get didn't work or the get-key is empty.

<br>
<br>
<br>

## Normal-Mode

### load
> ```
> inisg load -f {file} (--force)
> ```
>  
> It loads all the sections in there own directories in the .inisg/ folder and creates a file("[key].val") for every key in the section, then it writes the value of key in the key file.
> Saves the ini-filename in the .inisg.season.info file.
> 
>> #### `--force`
>> Normaly when the inisg directory exists it means that there is something not saved. With --force you can override the existing structures and load a new ini file.
  
### save
> ```
> inisg save (-f {file}) (--keep)
> ```
>
> Loads every section directory with all its key-files in and outputs them in a file of the provided ini-filepath. If the `-f` flag isn't set, it takes the filepath from the .inisg.season.info file.
> 
> It also deletes the ./.inisg/ directory.
> 
>> #### `--keep`
>> Activates the keep functionality. Doesn't delete the ./.inisg/ folder.

### set
> ```
> inisg set (-s {section}) -k {key} -v {value}
> ```
> Sets the value of the key in the section. If the value should become empty use `-v -`.

### get
> ```
> inisg get (-s {section}) -k {key} (-v {default value}) (-f {file}) (--delete) (--trunc)
> ```
>
> Outputs the the value of key in section, but if the value is empty it outputs the default value. Also output it to a file if `-f` is set.
> 
>> #### `--delete`
>> With `--delete` it deletes the [key].val file after the output.
>
>> #### `--trunc`
>> If `--trunc` is set it clears the output file before writing to it.
>> Doesn't throw an error if `-f` flag isn't set. Just ignores it.

### new
> ```
> inisg del (-s {section} &// -k {key})
> ```
> 
> Creates a new setup for `inisg` and writes the filepath to the .inisg.season.info if `-f` is set.
> 
>> #### `--force`
>> Overrides the .inisg/ directory if it is existing and doesn't throw an error. 

### clear
> ```
> inisg new (-f {file}) (--force)
> ```
>
> Deletes the `.inisg/` directory if it is empty.
>
>> #### `--force`
>> Delets the directory also when there is something in it.

<br>
<br>
<br>

## Inside-Mode
> Changes the values directly inside the ini file

### set
> ```
> inisg inside set -f {file} (-s {section}) -k {key} -v {value}
> ```
> Loads the ini-file (internally), changes the value of the key and saves the ini-file

### get
> ```
> inisg inside get -f {file} (-s {section}) -k {key} (-v {default value}) (--out (-f {output file}) (--trunc))
> ```
> Loads the ini-file (internally), ouputs the value (or default value)
>
>> #### `--out`
>> changes `-f` from input file to output file. Means every `-f` after `--out` is interpreted not as `[file]` but as `[output file]`
>> #### `--trunc`
>> If `--trunc` is set it clears the output file before writing to it.
>> Doesn't throw an error if `-f` flag isn't set. Just ignores it.

### del
> ```
> inisg inside del -f {file} (-s {section} &// -k {key})
> ```
> Loads the ini-file (internally), deletes the section or key, saves the ini-file
>> #### `&//`
>> One or both. (and or or)

### new
> ```
> inisg inside new -f {file} (--from -f {from file})
> ```
> creates a new ini-file at `file`.
>> #### `--from`
>> changes `-f` from output file to copy file. Means every `-f` after `--out` is interpreted not as `[file]` but as `[from file]`
>> `-f` : all contents get loaded and saved to the new file.

<br>
<br>
<br>

## File Structure:
>
> &ensp;. <br>
> └── .inisig/ <br>
> &emsp;&emsp;&emsp;├── .inisg.season.info <br>
> &emsp;&emsp;&emsp;└── [SectionName]/ <br>
> &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;└── [Key].val <br>
> 

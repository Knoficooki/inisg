# inisg
This is a commandline program which allows you to load, save and create files with ini syntax. Get and set key values.

## Syntax:
>
>> #### inisg load -f [file] (--force)
>
>> #### inisg save ([-f [file]) (--keep)
>
>> #### inisg set (-s [section]) -k [key] -v [value]
>
>> #### inisg get (-s [section]) -k [key] (-v [default value]) (-f [file]) (--delete) (--trunc)
>
>> #### inisg new (-f [file]) (--force)
>
>> #### inisg clear (--force)

## How does it Work?

### Flags

> #### -f [file]
> `-f` means there is a filepath in the next argument.

> #### -s [section]
> Sets the section. Can be ignored, if you want to select the global(or empty) section (aka section="").

> #### -k [key]
> Sets the key which referes to the value.

> #### -v [value]
> Can be used to set a key to this value or to return it if the get didn't work or the get-key is empty.

<br>

### Operators

### load
> ```applescript
> inisg load -f [file] (--force)
> ```
>  
> It loads all the sections in there own directories in the .inisg/ folder and creates a file("[key].val") for every key in the section, then it writes the value of key in the key file.
> Saves the ini-filename in the .inisg.season.info file.
> 
>> #### `--force`
>> Normaly when the inisg directory exists it means that there is something not saved. With --force you can override the existing structures and load a new ini file.
  
### save
> ```applescript
> inisg save (-f [file]) (--keep)
> ```
>
> Loads every section directory with all its key-files in and outputs them in a file of the provided ini-filepath. If the `-f` flag isn't set, it takes the filepath from the .inisg.season.info file.
> 
> It also deletes the ./.inisg/ directory.
> 
>> #### `--keep`
>> Activates the keep functionality. Doesn't delete the ./.inisg/ folder.

### set
> ```applescript
> inisg set (-s [section]) -k [key] -v [value]
> ```
> Sets the value of the key in the section. If the value should become empty use `-v -`.

### get
> ```applescript
> inisg get (-s [section]) -k [key] (-v [default value]) (-f [file]) (--delete) (--trunc)
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
> ```applescript
> inisg new (-f [file]) (--force)
> ```
> 
> Creates a new setup for `inisg` and writes the filepath to the .inisg.season.info if `-f` is set.
> 
>> #### `--force`
>> Overrides the .inisg/ directory if it is existing and doesn't throw an error. 

### clear
> ```applescript
> inisg clear (--force)
> ```
>
> Deletes the `.inisg/` directory if it is empty.
>
>> #### `--force`
>> Delets the directory also when there is something in it.

## File Structure:
>
> &ensp;. <br>
> └── .inisig/ <br>
> &emsp;&emsp;&emsp;├── .inisg.season.info <br>
> &emsp;&emsp;&emsp;└── [SectionName]/ <br>
> &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;└── [Key].val <br>
> 

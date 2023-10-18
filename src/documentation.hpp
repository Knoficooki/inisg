/***********************************
 *   ',:'/¯/`:,          .:':'`:·          ,:´'`;' ‘      ',:'/¯/`:,                      __  '                            __'             
 *  /:/_/::::/';'      /:::::::/`·,      /::::/;‘      /:/_/::::/';'              ,·:'´/::::/'`;·.,                 ,.·:'´::::::::`'·-.      
 * /:'     '`:/::;‘    /:·*'`·:/:::::' , /·´'`;/::';'    /:'     '`:/::;‘         .:´::::/::::/:::::::`;             '/::::::::::::::::::';     
 * ;         ';:';‘  ,'         `:;::::'`i    ';:::';    ;         ';:';‘        /:;:· '´ ¯¯'`^·-;::::/' ‘          /;:· '´ ¯¯  `' ·-:::/'     
 * |         'i::i   ;            '`;:::'i    'i::::i    |         'i::i        /·´           _   '`;/‘           /.'´      _         ';/' ‘    
 * ';        ;'::i   i               `;:';    'i:::i'    ';        ;'::i       'i            ;::::'`;*           ,:     ,:'´::;'`·.,_.·'´.,    ‘ 
 * 'i        'i::i'   i      ,          \|     '|:::i°   'i        'i::i'        `;           '`;:::::'`:,       /     /':::::/;::::_::::::::;‘  
 *  ;       'i::;'   |     ,'`,                i:;'' ‚    ;       'i::;'          `·,           '`·;:::::';   ,'     ;':::::'/·´¯     ¯'`·;:::¦‘ 
 *  ';       i:/'    'i    'i:::i',             ';/'       ';       i:/'         ,~:-'`·,           `:;::/'   'i     ';::::::'\             ';:';‘ 
 *   ';     ;/ °    'i     ;::/ \           ;/'          ';     ;/ °        /:::::::::';           ';/      ;      '`·:;:::::`'*;:'´      |/'  
 *    ';   / °       \    'i/    '`·,      ,''             ';   / °        ,:~·- . -·'´          ,'´         \          '`*^*'´         /'  ‘ 
 *     `'´       °    '`~´         '`·–·'´'               `'´       °    '`·,               , ·'´             `·.,               ,.-·´      
 *      ‘                               ‘                  ‘                  '`*^·–·^*'´'           ‘            '`*^~·~^*'´            
 * inisg-text created here: http://www.patorjk.com/software/taag
 *  Big thanks i love this webside.
 * 
 * 
 * DOCUMENTATION:
 * Importent: not always up to date, because of... well, the thing is... you know?... i dont want do take care of 3 documentations.
 * 
 * GIT:
 * 
 * https://github.com/Knoficooki/inisg.git
 * 
 * 
 * LICENSE:
 * GNU General Public License v2.0
 * 
 * https://github.com/Knoficooki/inisg/blob/main/LICENSE
 * 
 * 
 * README:
 * 
 * https://github.com/Knoficooki/inisg/blob/main/README.md
 * 
 * 
 * SYNTAX:
 * 		NORMAL-MODE:
 * 									/// "/" means "or" and "&" means "and" so "&//" means "and or or"
 * 
 *		inisg load -f {file} (--force)
 *
 *		inisg save (-f {file}) (--keep)
 *
 *		inisg set (-s {section}) -k {key} -v {value}
 *
 *		inisg get (-s {section}) -k {key} (-v {default value}) (-f {file}) (--delete) (--trunc)
 *
 *		inisg del (-s {section} &// -k {key})
 *
 *		inisg new (-f {file}) (--force)
 *
 *		inisg clear (--force)
 *
 * 
 * 		INSIDE-MODE:
 * 
 *		inisg inside set -f {file} (-s {section}) -k {key} -v {value}
 * 
 *		inisg inside get -f {file} (-s {section}) -k {key} (-v {default value}) (--out (-f {output file}) (--trunc))
 * 
 *		inisg inside del -f {file} (-s {section} &// -k {key})
 * 
 *		inisg inside new -f {file} (--from -f {from file})
 * 
 * How does it Work?:
 * FLAGS:
 * 
 *     -f {file}
 * 
 *     -f means there is a filepath in the next argument.
 * 
 *     -s {section}
 * 
 *     Sets the section. Can be ignored, if you want to select the global(or empty) section (aka section="").
 * 
 *     -k {key}
 * 
 *     Sets the key which referes to the value.
 * 
 *     -v {value}
 * 
 *     Can be used to set a key to this value or to return it if the get didn't work or the get-key is empty.
 * 
 * 
 * 
 * 
 * NORMAL:
 * load
 * 
 *     inisg load -f {file} (--force)
 * 
 *     It loads all the sections in there own directories in the .inisg/ folder and creates a file("[key].val") for every key in the section, then it writes the value of key in the key file. Saves the ini-filename in the .inisg.season.info file.
 * 
 *         --force
 * 
 *         Normaly when the inisg directory exists it means that there is something not saved. With --force you can override the existing structures and load a new ini file.
 * 
 * save
 * 
 *     inisg save (-f {file}) (--keep)
 * 
 *     Loads every section directory with all its key-files in and outputs them in a file of the provided ini-filepath. If the -f flag isn't set, it takes the filepath from the .inisg.season.info file.
 * 
 *     It also deletes the ./.inisg/ directory.
 * 
 *         --keep
 * 
 *         Activates the keep functionality. Doesn't delete the ./.inisg/ folder.
 * 
 * set
 * 
 *     inisg set (-s {section}) -k {key} -v {value}
 * 
 *     Sets the value of the key in the section. If the value should become empty use -v -.
 * 
 * get
 * 
 *     inisg get (-s {section}) -k {key} (-v {default value}) (-f {file}) (--delete) (--trunc)
 * 
 *     Outputs the the value of key in section, but if the value is empty it outputs the default value. Also output it to a file if -f is set.
 * 
 *         --delete
 * 
 *         With --delete it deletes the [key].val file after the output.
 * 
 *         --trunc
 * 
 *         If --trunc is set it clears the output file before writing to it. Doesn't throw an error if -f flag isn't set. Just ignores it.
 * 
 * new
 * 
 *     inisg del (-s {section} &// -k {key})
 * 
 *     Creates a new setup for inisg and writes the filepath to the .inisg.season.info if -f is set.
 * 
 *         --force
 * 
 *         Overrides the .inisg/ directory if it is existing and doesn't throw an error.
 * 
 * clear
 * 
 *     inisg new (-f {file}) (--force)
 * 
 *     Deletes the .inisg/ directory if it is empty.
 * 
 *         --force
 * 
 *         Delets the directory also when there is something in it.
 * 
 * 
 * 
 * 
 * INSIDE:
 * 
 *     Changes the values directly inside the ini file
 * 
 * set
 * 
 *     inisg inside set -f {file} (-s {section}) -k {key} -v {value}
 * 
 *     Loads the ini-file (internally), changes the value of the key and saves the ini-file
 * 
 * get
 * 
 *     inisg inside get -f {file} (-s {section}) -k {key} (-v {default value}) (--out (-f {output file}) (--trunc))
 * 
 *     Loads the ini-file (internally), ouputs the value (or default value)
 * 
 *         --out
 * 
 *         changes -f from input file to output file. Means every -f after --out is interpreted not as [file] but as [output file]
 *         --trunc
 * 
 *         If --trunc is set it clears the output file before writing to it. Doesn't throw an error if -f flag isn't set. Just ignores it.
 * 
 * del
 * 
 *     inisg inside del -f {file} (-s {section} &// -k {key})
 * 
 *     Loads the ini-file (internally), deletes the section or key, saves the ini-file
 * 
 *         &//
 * 
 *         One or both. (and or or)
 * 
 * new
 * 
 *     inisg inside new -f {file} (--from -f {from file})
 * 
 *     creates a new ini-file at file.
 * 
 *         --from
 * 
 *         changes -f from output file to copy file. Means every -f after --out is interpreted not as [file] but as [from file] -f : all contents get loaded and saved to the new file.
 * 
 * 
 * STRUCTURE:
 *	.
 *	└── .inisig/
 *	    ├── sys.ini.info
 *	    └── [SectionName]/
 *	        └── [Key].val
 * 
 * 
***********************************/
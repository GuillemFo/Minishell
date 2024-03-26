Hello :)

The link of the project pdf online:
https://cdn.intra.42.fr/pdf/pdf/114775/en.subject.pdf

Readline library docs
https://tiswww.case.edu/php/chet/readline/readline.html
https://tiswww.case.edu/php/chet/readline/README

Info:
https://github.com/jotavare/42-resources#03-minishell

https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html

https://github.com/toni-schmitt/minishell

https://www.youtube.com/watch?v=oxuRxtrO2Ag

https://www.youtube.com/@johnalexandersanabriaordon1851/videos


You should limit yourself to the subject description. Anything that
is not asked is not required.
If you have any doubt about a requirement, take bash as a reference.


Guille:
-- Signals
-- Expansor $var // $? redirs heredock
-- builtins
-- Heredock
-- Enviroment Variables (on main)
-- PERROR & return code

--reminder to check echo with "$PATH""$PATH" || "$PATH" "$PATH" || "ls""|""cat"

15/1/2024 ->
DONE	working signals: 
						ctrl-D END OF FILE To RDLINE -> kills minishell
						ctrl-C recalls prompt minihell
						ctrl-\ does nothing
15/1/2024 to 16/1/2024
		Implement the builtins:
								◦ echo with option -n
								◦ cd with only a relative or absolute path
								◦ pwd with no options
								◦ export with no options "Create enviroments or modify em"
								◦ unset with no options "Delete enviroments"
								◦ env with no options or arguments
								◦ exit with no options

31/01/24 load env to a list and be able to add remove and modify its contetn


06/02/24 Expansor->
been trying to understand anna's code for 3h now. Been told to focus on my part and then merge the codes.
might need a flag to check if it has a $ so we might need to expand

existencial crisis. Should redo my way to interpret data in order to be more useful in one function or adapt and extend what i have...? I know the answer but dont want to do it :(

07/02/24 NEEDS TO BE READAPTED TO ANNA'S CODE
	All info is gonna be stored at parser->cmd[i] and next node when encountering pipes.

08/02/24 Time to get back to builtins and finish the env_add, env_rem, when cd change pwd and oldpwd env, create a new env to store the return value for exit... ???

CD PWD AND OLD PWD prepared, but not tested. Modified env_add and env_del. Still dont
know how ill manage them. 

In this commit i changed libft functions to compile with codespace compiler. Changed minishell.h Makefile libft/Makefile libft/ft_memchr.c and libft/ft_memmove.c

Fixed issues with makefile, should work in codespace too.
Fixed issues with the functions i modified before.
Imported anna's work to play with her code and start to build the shell itself.

expansor has to expand after redirections and heredock

Expansor env OK
Expansor wrong OK
Expansor heredock X
Expansor redirection OK

fighting expansor issues

19/02/24 07.46 ---> Lets try to fix expansor or redo it enitrely if needed but today
					HAS to be working as expected !!!

19/02/24 09.48 ---> Looks like is working so now i migt start with quotes 

28/02/24 08.49 ---> been dealing with quotes the wrong way. Since i was looping all strings
					, i was clearing the other quotes i could encounter also due the loop.
					so need to know if the input / token / parser handles strings separated by quotes.
28/02/24 12.22 ---> quotes working.
okay so quotes are working but now i have to implement expansions always except if text is inside single quotes.



MISSING TODAY 07/02/24 -->>
Heredock	(create files on ./tmp/ and name change with ft_strjoin of name and int number changing)

Export	(need to fix if edit_env and add_env to confirm a proper management of first nodes, last nodes and existing nodes) ------------ THIS OK

Unset	(confirm deletes top and bottom nodes correctly and links to proper next nodes); 
-----THIS OK

ShellLVL	(every time we execute the program we will increase the shell level on the env and can do up to 100 so when over that level, we restart to level 1)
Expansion in clear_input if no quotes and if double quotes;
Exit	(get the execute codes return values)

Norminette
MPANIC tester??

12/03/24 (unkown) -->Hopefully i solved the loop when only 1 builtin is called and the control + C
	comand acting twice


12/03/24 10.14 --> Found issues with export and unset.
	when using unset containing anything else than the name should result in an error. this means we have to check valid characters when trying to create or remove variables from enviroment list.
	also, when i do unset alone, it crashes the program.
when export has value wont be shown at env list;

I had to send &env so i can modify the 1st node... had to modify all code for it.
check export when has = and no

Fixed buch of non protected functions on libft for null strings.

expansor is pure trash, ill have to redo it entirely

all builtin return and errnos are not okay

export with \a\a \\ etc

13/03/24 01.51 pm -->>
	Working on expansor and quotes situation.
What does:		echo $USER$USER$a$'USER'
				gforns-sgforns-s$USER
What should do:	echo $USER$USER$a$'USER'
					gforns-sgforns-sUSER
Also	"'$USER'" wont work correctly (missing end) 02.50 pm WORKING!!!
		"'$USER'$PATH" missing ' after $USER 
		(the env name is correct but its not copying correcly the data)

with this code:
 SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [echo]                           12      5      1     18
  [export]                          2     14      0     16
  [env]                             2      6      0      8
  [exit]                           32     23      0     55
  [directory]                      12     11      0     23
  [dollars]                        17     12      4     33
  [quotes]                         42     10      0     52
  [spaces]                          6      4      0     10
  [tilde]                           3      6      0      9
  [syntax_error]                    4     14      9     27
  [pipe]                           25     15      9     49
  [redirection]                    13     16     38     67
  [status]                          5     22      0     27
  [shlvl]                           0      7      2      9
  [panic mandatory]                 2      9      1     12
  [your]                            0      0      0      0

  total                          [0173] [0160] [0055] [0388]


Added iteration for exort unset.

need to contemplate ~ so expands to home and only works if alone like ~ or ~///////..//

export wont add "" at start or end!!!
when i added the "" to the print function i failed 2 tests.
so i need to evaluate when i need "" if env has content or not initialized. (check if export something= or something so i add "" or not)
maybe with a flag on the structure??

imma delete "" from env prints , lets see whats the score

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [echo]                           12      5      1     18
  [export]                          2     14      0     16
  [env]                             2      6      0      8
  [exit]                           32     23      0     55
  [directory]                      12     11      0     23
  [dollars]                        17     12      4     33
  [quotes]                         43      9      0     52
  [spaces]                          6      4      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                    4     14      9     27
  [pipe]                           25     15      9     49
  [redirection]                    13     16     38     67
  [status]                          5     22      0     27
  [shlvl]                           0      7      2      9
  [panic mandatory]                 2      9      1     12
  [your]                            0      0      0      0

  total                          [0175] [0158] [0055] [0388]



FOR TOMORROW 14/03/24
!!!!!!!! fuck
minishell: echo $USER$ua3 |
gforns-s3                 |Fixed
minishell: echo $USER$ua3 |

hello2=ehho2              |Fixed
minishell: echo $hello2   |
2                         |

How should be |
echo "'$'"    |FIXED
'$'           |
How it is     |
echo "'$'"    |
''            |
  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [echo]                           12      5      1     18
  [export]                          2     14      0     16
  [env]                             2      6      0      8
  [exit]                           32     23      0     55
  [directory]                      12     11      0     23
  [dollars]                        19     10      4     33
  [quotes]                         44      8      0     52
  [spaces]                          6      4      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                    4     14      9     27
  [pipe]                           25     15      9     49
  [redirection]                    13     16     38     67
  [status]                          5     22      0     27
  [shlvl]                           0      7      2      9
  [panic mandatory]                 2      9      1     12
  [your]                            0      0      0      0

  total                          [0178] [0155] [0055] [0388]

So, need to add the filter for numbers on env only if the first char is number,
$NONEXISTANT wont work if alone or before an existant env.


Expansor, line 80. preparing to filter ? but im missing the env or var where i should pull the info from.

Env_1, preparing to set shell level or increase it if exists. Taking care for a possible situation where is the first var of the env list and also if it wont exist. 

(aparently is kinda hard t obe teh first only so i went fully skiping that fact. might be an issue in the future and we will need to send &env and work with **env  in its function: t_env	*shell_level(t_env *env))

With  this push, this is the score.
|============================================================|

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [echo]                           12      5      1     18
  [export]                          2     14      0     16
  [env]                             2      6      0      8
  [exit]                           32     23      0     55
  [directory]                      12     11      0     23
  [dollars]                        19     10      4     33
  [quotes]                         44      8      0     52
  [spaces]                          6      4      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                    4     14      9     27
  [pipe]                           25     15      9     49
  [redirection]                    13     16     38     67
  [status]                          5     22      0     27
  [shlvl]                           5      3      1      9
  [panic mandatory]                 2      9      1     12
  [your]                            0      0      0      0

  total                          [0183] [0151] [0054] [0388]


With  this push, this is the score.
|============================================================|

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [echo]                           13      5      0     18
  [export]                          2     14      0     16
  [env]                             2      6      0      8
  [exit]                           32     23      0     55
  [directory]                      12     11      0     23
  [dollars]                        22     10      1     33
  [quotes]                         44      8      0     52
  [spaces]                          6      4      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                    4     14      9     27
  [pipe]                           25     15      9     49
  [redirection]                    13     16     38     67
  [status]                          5     22      0     27
  [shlvl]                           5      4      0      9
  [panic mandatory]                 2      9      1     12
  [your]                            0      0      0      0

  total                          [0187] [0152] [0049] [0388]


With  this push, this is the score.
|============================================================|
  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [echo]                           14      4      0     18
  [export]                          2     14      0     16
  [env]                             2      6      0      8
  [exit]                           32     23      0     55
  [directory]                      12     11      0     23
  [dollars]                        23      9      1     33
  [quotes]                         44      8      0     52
  [spaces]                          6      4      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                    4     14      9     27
  [pipe]                           25     15      9     49
  [redirection]                    13     16     38     67
  [status]                          5     22      0     27
  [shlvl]                           6      3      0      9
  [panic mandatory]                 2      9      1     12
  [your]                            0      0      0      0

  total                          [0190] [0149] [0049] [0388]


Strarts to be pretty clean. 

Main issues to focus on:

bash-3.2$ echo $USER $?       minishell: echo $USER $?                   
gforns-s 0                    gforns-s 0?       
bash-3.2$ echo $              minishell: echo $             
$                             $
bash-3.2$ echo $k             minishell: echo $k               

bash-3.2$ echo $" t hi t "    minishell: echo $" t hi t "      
 t hi t                       $ t hi t 


With  this push, this is the score.
 |============================================================|

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [echo]                           14      4      0     18
  [export]                          2     14      0     16
  [env]                             2      6      0      8
  [exit]                           32     23      0     55
  [directory]                      12     11      0     23
  [dollars]                        23      9      1     33
  [quotes]                         44      8      0     52
  [spaces]                          6      4      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                    4     14      9     27
  [pipe]                           25     15      9     49
  [redirection]                    13     16     38     67
  [status]                         15     12      0     27
  [shlvl]                           6      3      0      9
  [panic mandatory]                 2      9      1     12
  [your]                            0      0      0      0

  total                          [0200] [0139] [0049] [0388]

  echo $" t hi t " Still an issue;



  |============================================================|

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [echo]                           14      4      0     18
  [export]                          1     15      0     16
  [env]                             2      6      0      8
  [exit]                           19     36      0     55
  [directory]                      10     13      0     23
  [dollars]                        21     12      0     33
  [quotes]                         42     10      0     52
  [spaces]                          8      2      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                    4     14      9     27
  [pipe]                           25     15      9     49
  [redirection]                    37     26      4     67
  [status]                         15     12      0     27
  [shlvl]                           6      3      0      9
  [panic mandatory]                 3      9      0     12
  [your]                            0      0      0      0

  total                          [0207] [0168] [0013] [0388]

  |============================================================|

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [echo]                           14      4      0     18
  [export]                          2     14      0     16
  [env]                             2      6      0      8
  [exit]                           32     23      0     55
  [directory]                      12     11      0     23
  [dollars]                        24      8      1     33
  [quotes]                         44      8      0     52
  [spaces]                          6      4      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                    4     14      9     27
  [pipe]                           25     15      9     49
  [redirection]                    46     17      4     67
  [status]                         15     12      0     27
  [shlvl]                           6      3      0      9
  [panic mandatory]                 2     10      0     12
  [your]                            0      0      0      0

  total                          [0234] [0140] [0014] [0388]


  All test i bee doing where wrongly executed, its worse thatn that socre.

  Actual status:

|============================================================|

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [echo]                           14      4      0     18
  [export]                          6     10      0     16
  [env]                             6      2      0      8
  [exit]                           19     36      0     55
  [directory]                      12     11      0     23
  [dollars]                        21     12      0     33
  [quotes]                         42     10      0     52
  [spaces]                          8      2      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                    4     14      9     27
  [pipe]                           25     15      9     49
  [redirection]                    37     26      4     67
  [status]                         15     12      0     27
  [shlvl]                           6      3      0      9
  [panic mandatory]                 3      9      0     12
  [your]                            0      0      0      0

  total                          [0218] [0157] [0013] [0388]

Also, the heck is this issue? @ANNA??
$NONEXIST $NONEXIST
bash: : Permission denied
while actual bash does nothing...




|============================================================|

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [echo]                           14      4      0     18
  [export]                          6     10      0     16
  [env]                             6      2      0      8
  [exit]                           19     36      0     55
  [directory]                      12     11      0     23
  [dollars]                        21     12      0     33
  [quotes]                         42     10      0     52
  [spaces]                          8      2      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                    4     14      9     27
  [pipe]                           25     15      9     49
  [redirection]                    37     26      4     67
  [status]                         15     12      0     27
  [shlvl]                           6      3      0      9
  [panic mandatory]                 3      9      0     12
  [your]                            0      0      0      0

  total                          [0218] [0157] [0013] [0388]

  |============================================================|

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [echo]                           14      4      0     18
  [export]                          6     10      0     16
  [env]                             6      2      0      8
  [exit]                           19     36      0     55
  [directory]                      12     11      0     23
  [dollars]                        20     13      0     33
  [quotes]                         42     10      0     52
  [spaces]                          8      2      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                    4     14      9     27
  [pipe]                           25     15      9     49
  [redirection]                    37     26      4     67
  [status]                         13     14      0     27
  [shlvl]                           6      3      0      9
  [panic mandatory]                 3      9      0     12
  [your]                            0      0      0      0

  total                          [0215] [0160] [0013] [0388]

Heredock << 

To do today 20/03/24 
    All error returns.
    word split o expansion for non "" exppansions so wont add extra spaces
    


To Anna 25/03/24 02.16 pm
vale te digo cosas que estan mal. || deberia petar en el parser y me salta en el clean_input con segfault porque no esta protegido. |ls funciona, cuando no deberia porque las pipes no estan cerradas.

minishell: mkdir testfolder
minishell: echo hi > testfolder
bash: testfolder: Permission denied
y hace exit por alguna razon...

las redirecciones no van bien, hay que comprobar si es folder o no y si tiene permisos etc.
error issues from Anna when command or env does not exist or empty string due non initialized env



Status-->> 25/03/24 04.46 pm
Export ok, Env ok (error issues from Anna when command or env does not exist or empty string due non initialized env), Echo ok, Cd ok (without ~ only 4 bonus), 

Missing that i know:
SHLVL over 1000 and over that, Exit (can have multiple args,if args are numbers will return error and exit with 255, double check that)!!!
Heredock (Redo)

Status-->> 25/03/24 06.26 pm
Fixed oldpwd and pwd (at some point they disapeared ...)

should i do and ft_strtrim custom to clear better the echo? now only clears space at both ends.
07.38 pm -->>NOW NOT CLEARING SPACESre(was clearing spaces on env and not on echo perse)



// Added ft_strtrim to remove leading and trailing whitespaces 2024/03/25 19:44:33
|============================================================|

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [echo]                           15      3      0     18
  [export]                          7      9      0     16
  [env]                             6      2      0      8
  [exit]                           50      5      0     55
  [directory]                      12     11      0     23
  [dollars]                        21     12      0     33
  [quotes]                         41     11      0     52
  [spaces]                          8      2      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                    4     22      1     27
  [pipe]                           25     23      1     49
  [redirection]                    51     16      0     67
  [status]                         15     12      0     27
  [shlvl]                           6      3      0      9
  [panic mandatory]                 2     10      0     12
  [your]                            0      0      0      0

  total                          [0263] [0124] [0001] [0388]



  without the trim on the echo. 
  it only fix a dollar so is something with expansor and not echo or anything else


|============================================================|

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [echo]                           15      3      0     18
  [export]                          7      9      0     16
  [env]                             6      2      0      8
  [exit]                           50      5      0     55
  [directory]                      12     11      0     23
  [dollars]                        20     13      0     33
  [quotes]                         44      8      0     52
  [spaces]                          8      2      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                    4     22      1     27
  [pipe]                           25     23      1     49
  [redirection]                    51     16      0     67
  [status]                         15     12      0     27
  [shlvl]                           6      3      0      9
  [panic mandatory]                 2     10      0     12
  [your]                            0      0      0      0

  total                          [0265] [0122] [0001] [0388]

  do i exit with last exit code i had?

Here is the result when the error = 0 is in the loop. (just under the while (str))

  |=========================[ STATUS ]=========================|


  1.   |echo $?|                                        [OK]
  2.   |" "|                                            [K0]
  3.   |echo $?|                                        [OK]
  4.   |echo $?|                                        [OK]
  5.   |cat < noexiste|                                 [K0]
  6.   | echo $?|                                       [K0]
  7.   |echo hola > noperm|                             [OK]
  8.   | echo $?|                                       [K0]
  9.   |echo hola < noperm|                             [OK]
  10.  |echo $?|                                        [OK]
  11.  |sleep 1 | ls | cat -n|                          [OK]
  12.  |echo $?|                                        [K0]
  13.  |sleep 1 | dddd|                                 [K0]
  14.  | echo $?|                                       [OK]
  15.  |nonexistcmd|                                    [K0]
  16.  | echo $?|                                       [OK]
  17.  |nonexistcmd | echo hi|                          [OK]
  18.  | echo $?|                                       [OK]
  19.  |echo hi | nonexistcmd|                          [K0]
  20.  | echo $?|                                       [OK]
  21.  |echo hi < nofile | nonexistcmd|                 [K0]
  22.  | echo $?|                                       [OK]
  23.  |echo hi < nofile | echo hii|                    [OK]
  24.  |echo $?|                                        [K0]
  25.  |/Users/nonexist/directory|                      [K0]
  26.  |echo $?|                                        [OK]
  27.  |cat /Users/nonexist/directory|                  [K0]


  It seems that there are some tests that have not passed...

  To see full failure traces -> traces/status_trace.txt


|============================================================|

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [status]                         15     12      0     27

  total                          [0015] [0012] [0000] [0027]


 Here is the result when the error = 0 is out of the loop. (at the top defined on first lines)

|=========================[ STATUS ]=========================|


  1.   |echo $?|                                        [K0]
  2.   |" "|                                            [OK]
  3.   |echo $?|                                        [OK]
  4.   |echo $?|                                        [K0]
  5.   |cat < noexiste|                                 [OK]
  6.   | echo $?|                                       [K0]
  7.   |echo hola > noperm|                             [OK]
  8.   | echo $?|                                       [K0]
  9.   |echo hola < noperm|                             [OK]
  10.  |echo $?|                                        [OK]
  11.  |sleep 1 | ls | cat -n|                          [OK]
  12.  |echo $?|                                        [K0]
  13.  |sleep 1 | dddd|                                 [K0]
  14.  | echo $?|                                       [K0]
  15.  |nonexistcmd|                                    [OK]
  16.  | echo $?|                                       [OK]
  17.  |nonexistcmd | echo hi|                          [OK]
  18.  | echo $?|                                       [K0]
  19.  |echo hi | nonexistcmd|                          [OK]
  20.  | echo $?|                                       [K0]
  21.  |echo hi < nofile | nonexistcmd|                 [OK]
  22.  | echo $?|                                       [OK]
  23.  |echo hi < nofile | echo hii|                    [OK]
  24.  |echo $?|                                        [K0]
  25.  |/Users/nonexist/directory|                      [K0]
  26.  |echo $?|                                        [K0]
  27.  |cat /Users/nonexist/directory|                  [OK]


  It seems that there are some tests that have not passed...

  To see full failure traces -> traces/status_trace.txt


|============================================================|

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [status]                         15     12      0     27

  total                          [0015] [0012] [0000] [0027]


25.03.24 09.05 pm
Take a look at expansor, maybe we can trim " " there instead??
Wont help. I think the issue is with the trim before and after.

26.03.24 01.42 am
broke something with $? (been trying to trim before after and in itself of expansor)

01.49
fixed stupid issue with $?

01.53

Added clear_spaces on utils but not in use.
Best state rn.

|==========================[ ECHO ]==========================|


  1.   |echo|                                           [OK]
  2.   |echo ñ|                                         [OK]
  3.   |echo hi|                                        [OK]
  4.   |/bin/echo hi|                                   [OK]
  5.   |echo $PATH|                                     [OK]
  6.   |echo $NONEXIST|                                 [OK]
  7.   |echoecho|                                       [K0]
  8.   |echo -n|                                        [OK]
  9.   |echo -n hi|                                     [OK]
  10.  |echo --n hi|                                    [OK]
  11.  |echo -nn hi|                                    [OK]
  12.  |echo -n -n hi|                                  [OK]
  13.  |echo hi -n|                                     [OK]
  14.  |echo "-n -n -n" -n hi|                          [OK]
  15.  |check if launch execve|                         [OK]
  16.  |check if builtin is not correct|                [K0]
  17.  |EXECVE THE ECHO?|                               [OK]
  18.  |not builtin without PATH|                       [K0]


  It seems that there are some tests that have not passed...

  To see full failure traces -> traces/echo_trace.txt


|=========================[ EXPORT ]=========================|


  19.  |export 1A=value|                                [K0]
  20.  |export /A=value|                                [K0]
  21.  |export A/=value|                                [K0]
  22.  |export 'A=value'|                               [OK]
  23.  |export ' A=value'|                              [K0]
  24.  |export 'A =value'|                              [K0]
  25.  |export TEST=test|                               [OK]
  26.  |export TEST=test TESTT=test2|                   [OK]
  27.  |export TEST=test W:RON:G=wrong TESTT=test2|     [K0]
  28.  |export EMPTY EMPTY_TOO= NOT_EMPTY=contnent|     [OK]
  29.  |export TEST=value TEST=value2|                  [OK]
  30.  |export TEST+=" added value"|                    [K0]
  31.  |export existing variable|                       [OK]
  32.  |export correct=correct wrong%=wrong|            [K0]
  33.  |export wrong%=wrong correct=correct|            [K0]
  34.  | whoami|                                        [OK]


  It seems that there are some tests that have not passed...

  To see full failure traces -> traces/export_trace.txt


|===========================[ ENV ]==========================|


  35.  |env with export TESTVAR|                        [K0]
  36.  |env with export TESTVAR=|                       [OK]
  37.  |env with export TESTVAR=""|                     [OK]
  38.  |env with export TESTVAR="value"|                [OK]
  39.  |env with export TESTVAR (in mini)|              [K0]
  40.  |env with export TESTVAR= (in mini)|             [OK]
  41.  |env with export TESTVAR="" (in mini)|           [OK]
  42.  |env with export TESTVAR"value" (in mini)|       [OK]


  It seems that there are some tests that have not passed...

  To see full failure traces -> traces/env_trace.txt


|==========================[ EXIT ]==========================|


  43.  |exit|                                           [OK]
  44.  |exit ""|                                        [OK]
  45.  |exit " "|                                       [OK]
  46.  |exit "  "|                                      [OK]
  47.  |exit "	"|                                       [OK]
  48.  |exit 42network|                                 [OK]
  49.  |exit +|                                         [OK]
  50.  |exit ++|                                        [OK]
  51.  |exit -|                                         [OK]
  52.  |exit ---|                                       [OK]
  53.  |exit 0|                                         [OK]
  54.  |exit +0|                                        [OK]
  55.  |exit ++0|                                       [OK]
  56.  |exit -0|                                        [OK]
  57.  |exit --0|                                       [OK]
  58.  |exit 1|                                         [OK]
  59.  |exit +1|                                        [OK]
  60.  |exit ++1|                                       [OK]
  61.  |exit -1|                                        [OK]
  62.  |exit --1|                                       [OK]
  63.  |exit ' 3'|                                      [OK]
  64.  |exit '3 '|                                      [OK]
  65.  |exit 255|                                       [OK]
  66.  |exit -255|                                      [OK]
  67.  |exit 256|                                       [OK]
  68.  |exit -256|                                      [OK]
  69.  |exit 2147483647|                                [OK]
  70.  |exit 2147483648|                                [OK]
  71.  |exit -2147483648|                               [OK]
  72.  |exit -2147483649|                               [OK]
  73.  |exit 4294967295|                                [OK]
  74.  |exit 4294967296|                                [OK]
  75.  |exit -4294967296|                               [OK]
  76.  |exit -4294967297|                               [OK]
  77.  |exit 9223372036854775807|                       [OK]
  78.  |exit 9223372036854775808|                       [OK]
  79.  |exit -9223372036854775808|                      [OK]
  80.  |exit -9223372036854775809|                      [OK]
  81.  |exit 18446744073709551615|                      [OK]
  82.  |exit 18446744073709551616|                      [OK]
  83.  |exit -18446744073709551616|                     [OK]
  84.  |exit -18446744073709551617|                     [OK]
  85.  |exit 9999999999999999999999|                    [OK]
  86.  |exit 0000000000000000000000|                    [OK]
  87.  |exit 0000000000000000000001|                    [OK]
  88.  |exit 1 2 3|                                     [K0]
  89.  |echo should not exit|                           [OK]
  90.  |exit 1 not numeric bro|                         [K0]
  91.  |exit not numeric bro 2|                         [K0]
  92.  |exit 42 | cat|                                  [OK]
  93.  |echo is not a buildin!|                         [OK]
  94.  |not found then exit|                            [K0]
  95.  |not found then exit 1|                          [OK]
  96.  |permission deny then exit|                      [K0]
  97.  |permission deny then exit 1|                    [OK]


  It seems that there are some tests that have not passed...

  To see full failure traces -> traces/exit_trace.txt


|========================[ DIRECTORY ]=======================|


  98.  |pwd|                                            [OK]
  99.  |cd|                                             [OK]
  100. |cd ""|                                          [OK]
  101. |cd " "|                                         [K0]
  102. |cd "" ""|                                       [OK]
  103. |cd / non_existent|                              [OK]
  104. |cd /.|                                          [OK]
  105. |cd //|                                          [OK]
  106. |cd ' / '|                                       [K0]
  107. |pwd|                                            [OK]
  108. |pwd argument|                                   [OK]
  109. |pwd argument1 argument2|                        [OK]
  110. |cd file|                                        [K0]
  111. |cd file (no permission)|                        [K0]
  112. |cd file/non_existent|                           [K0]
  113. |cd non_exist|                                   [K0]
  114. |cd ..|                                          [OK]
  115. |cd ~|                                           [K0]
  116. |cd ~|                                           [K0]
  117. |cd .|                                           [OK]
  118. |cd testdirtest(no permision)|                   [K0]
  119. |cd maxpathlen|                                  [K0]
  120. |cd maxpathlen + 1|                              [K0]


  It seems that there are some tests that have not passed...

  To see full failure traces -> traces/directory_trace.txt


|=========================[ PARSER ]=========================|

    ----------------------[ dollar ]---------------------

  121. |echo $?|                                        [OK]
  122. |echo $|                                         [OK]
  123. |echo hi$|                                       [OK]
  124. |echo '$ '|                                      [OK]
  125. |echo $/|                                        [OK]
  126. |echo "'$'"|                                     [OK]
  127. |echo $'\n'|                                     [K0]
  128. |echo $'\r'|                                     [K0]
  129. |echo $'\t'|                                     [K0]
  130. |echo $USER|                                     [OK]
  131. |echo $NONEXIST|                                 [OK]
  132. |echo $USER$PATH$PWD|                            [OK]
  133. |echo "$USER$PATH$PWD"|                          [OK]
  134. |echo '$USER$PATH$PWD'|                          [OK]
  135. |echo '$USER",$PATH,$PWD'|                       [OK]
  136. |echo $USER"$PATH"$PWD"USER"$PATH"$PWD"|         [OK]
  137. |echo $USER'$PATH'$PWD'USER'$PATH'$PWD'|         [OK]
  138. |$NONEXIST|                                      [K0]
  139. |$NONEXIST $NONEXIST|                            [K0]
  140. |VAR: export TMPENVVAR|                          [K0]
  141. |VAR: export TMPENVVAR=echo|                     [OK]
  142. |VAR: export TMPENVVAR="  echo"|                 [K0]
  143. |VAR: export TMPENVVAR="    EcHO   hi"|          [K0]
  144. |VAR: export TMPENVVAR="-n"|                     [OK]
  145. |VAR: export TMPENVVAR="-n -n"|                  [K0]
  146. |echo $A"$B"$C"A"$B"$C"|                         [OK]
  147. |echo $A'$B'$C'A'$B'$C'|                         [OK]
  148. |echo $A"$B"$C"A"$B"$C"|                         [OK]
  149. |echo $A'$B'$C'A'$B'$C'|                         [OK]
  150. |echo $A|                                        [K0]
  151. |echo $A$B|                                      [K0]
  152. |echo $A$B$C|                                    [K0]
  153. |echo $A$B$C$AA|                                 [K0]

    ----------------------[ quotes ]---------------------

  154. |echo "~"ups|                                    [OK]
  155. |echo '~'ups|                                    [OK]
  156. |echo "'$'"|                                     [OK]
  157. |echo '"$"'|                                     [OK]
  158. |echo "|$USER|"|                                 [OK]
  159. |echo "|$USE|"|                                  [OK]
  160. |echo "|$USER_|"|                                [OK]
  161. |echo '|$USER|'|                                 [OK]
  162. |echo '|$USE|'|                                  [OK]
  163. |echo '|$USER_|'|                                [OK]
  164. |'echo' hi|                                      [OK]
  165. |'''echo' hi|                                    [OK]
  166. |'echo' 'hi'|                                    [OK]
  167. |'echo' 'hi'''|                                  [OK]
  168. |'echo' 'hi' ''|                                 [OK]
  169. |"echo" hi|                                      [OK]
  170. |"""echo" hi|                                    [OK]
  171. |"echo" "hi"|                                    [OK]
  172. |"echo" "hi"""|                                  [OK]
  173. |"echo" "hi" ""|                                 [OK]
  174. |echo '""""""""""""'|                            [OK]
  175. |'echo' "hi"'' " ' "' "' "" ''''''""|            [OK]
  176. |echo hi"hi" hi'h"i'|                            [OK]
  177. |echo "hi" "hi"|                                 [OK]
  178. |echo "hi"  "hi"|                                [OK]
  179. |echo "hi"tab"hi"|                               [OK]
  180. |" echo"|                                        [K0]
  181. |' echo'|                                        [K0]
  182. |""echo|                                         [OK]
  183. |" "echo|                                        [K0]
  184. |''echo|                                         [OK]
  185. |' 'echo|                                        [K0]
  186. |''''''''''echo hi|                              [OK]
  187. |""""""""""echo hi|                              [OK]
  188. |"e"'c'h"o" hi|                                  [OK]
  189. |ec""ho hi|                                      [OK]
  190. |ec""h''o hi|                                    [OK]
  191. |EcHo hi|                                        [OK]
  192. |ECHO hi|                                        [OK]
  193. |"ECHO" hi|                                      [OK]
  194. |'ECHO' hi|                                      [OK]
  195. |echo    t  hi   t|                              [OK]
  196. |echo "   t  hi   t    "|                        [OK]
  197. |echo '   t  hi   t    '|                        [OK]
  198. |echo $"   t  hi   t    "|                       [K0]
  199. |echo $'   t  hi   t    '|                       [K0]
  200. |echo $'   r  hi   t    '|                       [K0]
  201. |echo hi > "fi le"|                              [OK]
  202. |echo hi > 'fi le'|                              [OK]
  203. |echo $ANA_VAR with spaces in var value|         [K0]
  204. |echo "$ANA_VAR" with spaces in var value|       [OK]
  205. |echo '$ANA_VAR' with spaces in var value|       [OK]

    ----------------------[ spaces ]---------------------

  206. |""|                                             [K0]
  207. |" "|                                            [K0]
  208. |\techo hi|                                      [OK]
  209. |echo\thi|                                       [OK]
  210. |\techo\thi|                                     [OK]
  211. |\techo\thi|                                     [OK]
  212. |  \techo\thi|                                   [OK]
  213. |\techo\t   hi|                                  [OK]
  214. |many tabs|                                      [OK]
  215. |many spaces|                                    [OK]

    -----------------------[ tilde ]---------------------

  216. |~|                                              [K0]
  217. |echo hi~|                                       [OK]
  218. |echo ~|                                         [K0]
  219. |echo ~/path|                                    [K0]
  220. |echo ~$USER|                                    [OK]
  221. |echo ~false|                                    [OK]
  222. |echo ~|                                         [K0]
  223. |echo ~$USER/sdfsfsfdsfs|                        [OK]
  224. | echo ~|                                        [K0]

    -------------------[ syntax_error ]------------------

  225. |test|                                           [K0]
  226. ||test|                                          [K0]
  227. || test|                                         [K0]
  228. |< | test|                                       [K0]
  229. |<< | test|                                      [K0]
  230. |> | test|                                       [K0]
  231. |>> | test|                                      [K0]
  232. || < test|                                       [K0]
  233. || << test|                                      [K0]
  234. || > test|                                       [K0]
  235. || >> test|                                      [K0]
  236. || test|                                         [K0]
  237. |test | >|                                       [K0]
  238. |test | >>|                                      [K0]
  239. |test | <|                                       [K0]
  240. |echo hiecho hi|                                 [OK]
  241. |echo hi|echo hi|                                [OK]
  242. |echo hi |echo hi|                               [OK]
  243. |echo hi| echo hi|                               [OK]
  244. |echo hi | | echo hi|                            [K0]
  245. |echo hi ||| echo hi|                            [SF]
  246. |echo >|                                         [K0]
  247. |echo >>|                                        [K0]
  248. |echo <|                                         [K0]
  249. |echo >>>|                                       [K0]
  250. |echo <<<|                                       [K0]
  251. |echo hi >< file|                                [K0]


  It seems that there are some tests that have not passed...
  and your minishell gives segmentation fault at tests:
  [ 245 ]

  To see full failure traces -> traces/parse/*.txt


|=========================[ PIPES ]==========================|


  252. |echo | /bin/cat|                                [OK]
  253. |echo hi | /bin/cat|                             [OK]
  254. |cat /etc/shells | head -c 10|                   [OK]
  255. |cat -e /etc/shells | head -c 10|                [OK]
  256. |cat -e /etc/shells | cat -e | head -c 10|       [OK]
  257. |cat -e /etc/shells | cat -e | cat -e | h...|    [OK]
  258. |echo hola | cat|                                [OK]
  259. |echo hola | cat -e|                             [OK]
  260. |echo hola | cat -e | cat -n|                    [OK]
  261. |echo hola with many pipes cat -e|               [OK]
  262. |ls | cat -e|                                    [OK]
  263. |ls -l | cat -e|                                 [OK]
  264. |ls -l | cat -e | cat | cat | cat|               [OK]
  265. |ls -l | cat -e | cat -e | cat -e | cat -e|      [OK]
  266. |echo hola | asdf|                               [K0]
  267. |asdf | echo hola|                               [OK]
  268. |cat | cat | cat | ls|                           [OK]
  269. |sleep 1 | ls | cat -n|                          [OK]
  270. |cd folder | pwd|                                [OK]
  271. |ls pipes (255)|                                 [OK]
  272. |ls pipes (256)|                                 [OK]
  273. |ls pipes (257)|                                 [OK]


  It seems that there are some tests that have not passed...

  To see full failure traces -> traces/pipes_trace.txt


|======================[ REDIRECTIONS ]======================|


  274. |> no_cmd_file|                                  [OK]
  275. |>> no_cmd_test|                                 [OK]
  276. |echo hola | > filepipe|                         [OK]
  277. |> file_first | > file_second|                   [OK]
  278. |echo hi > file|                                 [OK]
  279. |echo hi >> file|                                [OK]
  280. |echo hi > *.txt|                                [OK]
  281. |echo >> file hi|                                [OK]
  282. |echo >> file2 hi|                               [OK]
  283. |> file echo hi|                                 [OK]
  284. |>> file echo hi|                                [OK]
  285. |echo hi > file2 > file hi|                      [OK]
  286. |echo hi >> file2 > file hi|                     [OK]
  287. |echo hi > file2 >> file hi|                     [OK]
  288. |echo hi > file2 > file hi|                      [OK]
  289. |echo hi >> file2 >> file hi|                    [OK]
  290. |echo hi>file2>file hi|                          [OK]
  291. |echo hi>>file2>>file hi|                        [OK]
  292. |echo hi > file3 > file2 > file hi|              [OK]
  293. |echo hi > file3 >> file2 > file hi|             [OK]
  294. |echo hi > file3 > file2 >> file hi|             [OK]
  295. |echo hi >> file3 > file2 > file hi|             [OK]
  296. |echo hi >> file3 > file2 >> file hi|            [OK]
  297. |echo hi >> file3 >> file2 > file hi|            [OK]
  298. |echo hi>file3>file2>file hi|                    [OK]
  299. |> file3 echo hi > file2 > file hi|              [OK]
  300. |> file3 echo hi > file2 >> file hi|             [OK]
  301. |>> file3 echo hi > file2 > file hi|             [OK]
  302. |> file3 echo hi >> file2 > file hi|             [OK]
  303. |>file3 echo hi>file2>file hi|                   [OK]
  304. |echo hi >filea>fileb>filec hi|                  [OK]
  305. |echo hi >filea>>fileb>filec hi|                 [OK]
  306. |echo hi >filea>fileb>>filec hi|                 [OK]
  307. |echo hi >>filea>fileb>filec hi|                 [OK]
  308. |echo hi > "doble"quote|                         [OK]
  309. |echo hi >"doble"quote|                          [OK]
  310. |echo -n hi >>"doble"quote|                      [OK]
  311. |echo hi > 'simple'quote|                        [OK]
  312. |echo hi >'simple'quote|                         [OK]
  313. |echo -n hi >>'simple'quote|                     [OK]
  314. |echo hi > 'with spaces'|                        [OK]
  315. |echo hi >>'with spaces'|                        [OK]
  316. |echo hi > "mixed"'file 'name|                   [OK]
  317. |echo hi >> "mixed"'file 'name|                  [OK]
  318. |echo hi 0> file|                                [OK]
  319. |4> file|                                        [K0]
  320. |echo hi > testfolder|                           [K0]
  321. |echo hi >> testfolder|                          [K0]
  322. |echo hi 2> testfolder|                          [K0]
  323. |echo hi 2>> testfolder|                         [K0]
  324. |echo hi > testfolder|                           [K0]
  325. |echo hi >> testfolder|                          [K0]
  326. |echo hi 2> testfolder|                          [K0]
  327. |echo hi 2>> testfolder|                         [K0]
  328. |echo > file hi (no permision)|                  [OK]
  329. |echo >> file2 hi (no permision)|                [OK]
  330. |> file echo hi (no permision)|                  [OK]
  331. |>> file3 echo hi (no permision)|                [OK]
  332. |cat < file|                                     [OK]
  333. |< file cat < file2|                             [OK]
  334. |cat < nonexist|                                 [K0]
  335. |cat < $USER|                                    [K0]
  336. |cat < file3 (no permision)|                     [K0]
  337. |echo hi 2> error_outp < non_exist|              [K0]
  338. |echo hi < non_exist > wrong|                    [K0]
  339. |< non_exist echo hi > wrong|                    [K0]
  340. |> correct echo hi < non_exist|                  [K0]


  It seems that there are some tests that have not passed...

  To see full failure traces -> traces/redirection_trace.txt


|=========================[ STATUS ]=========================|


  341. |echo $?|                                        [OK]
  342. |" "|                                            [K0]
  343. |echo $?|                                        [OK]
  344. |echo $?|                                        [OK]
  345. |cat < noexiste|                                 [K0]
  346. | echo $?|                                       [K0]
  347. |echo hola > noperm|                             [OK]
  348. | echo $?|                                       [K0]
  349. |echo hola < noperm|                             [OK]
  350. |echo $?|                                        [OK]
  351. |sleep 1 | ls | cat -n|                          [OK]
  352. |echo $?|                                        [K0]
  353. |sleep 1 | dddd|                                 [K0]
  354. | echo $?|                                       [OK]
  355. |nonexistcmd|                                    [K0]
  356. | echo $?|                                       [OK]
  357. |nonexistcmd | echo hi|                          [OK]
  358. | echo $?|                                       [OK]
  359. |echo hi | nonexistcmd|                          [K0]
  360. | echo $?|                                       [OK]
  361. |echo hi < nofile | nonexistcmd|                 [K0]
  362. | echo $?|                                       [OK]
  363. |echo hi < nofile | echo hii|                    [OK]
  364. |echo $?|                                        [K0]
  365. |/Users/nonexist/directory|                      [K0]
  366. |echo $?|                                        [OK]
  367. |cat /Users/nonexist/directory|                  [K0]


  It seems that there are some tests that have not passed...

  To see full failure traces -> traces/status_trace.txt


|=======================[ SHLVL TESTS ]======================|


  368. |echo $SHLVL 'entry value 20'|                   [OK]
  369. |echo $SHLVL 'entry value 50'|                   [OK]
  370. |echo $SHLVL 'entry value 99'|                   [OK]
  371. |echo $SHLVL 'entry value -20'|                  [OK]
  372. |echo $SHLVL 'entry value 800'|                  [OK]
  373. |echo $SHLVL 'entry value 1000'|                 [K0]
  374. |echo $SHLVL 'entry value 5000000'|              [K0]
  375. |echo $SHLVL 'unset SHLVL before ./minishell'|   [OK]
  376. |echo $SLVL 'export SHLVL='' before ./minishell'|[K0]


  It seems that there are some tests that have not passed...

  To see full failure traces -> traces/shlvl_trace.txt


|====================[ PANIC MANDATORY ]=====================|


  377. |rm -rf actual dir and cd .|                     [K0]
  378. |exit --|                                        [K0]
  379. |echo all &> file|                               [OK]
  380. |cd - (at start the minishell, OLDPWD sho...|    [K0]
  381. |cd - (deleted old path dir)|                    [K0]
  382. |cd -|                                           [K0]
  383. |echo ~ (without $HOME in env)|                  [K0]
  384. |playing with PWD an OLD|                        [K0]
  385. |playing with PWD an OLD|                        [K0]
  386. |echo <> file|                                   [K0]
  387. |cat < file 3< file2|                            [K0]
  388. |file with permission named echo|                [OK]


  It seems that there are some tests that have not passed...

  To see full failure traces -> traces/panic/panic_mandatory.txt


|=======================[ YOUR TESTS ]=======================|


 there goes your tests!


  All your test passed successfully!!

|============================================================|

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [echo]                           15      3      0     18
  [export]                          7      9      0     16
  [env]                             6      2      0      8
  [exit]                           50      5      0     55
  [directory]                      12     11      0     23
  [dollars]                        20     13      0     33
  [quotes]                         44      8      0     52
  [spaces]                          8      2      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                    4     22      1     27
  [pipe]                           25     23      1     49
  [redirection]                    51     16      0     67
  [status]                         15     12      0     27
  [shlvl]                           6      3      0      9
  [panic mandatory]                 2     10      0     12
  [your]                            0      0      0      0

  total                          [0265] [0122] [0001] [0388]

  Best state so far  //  have not fixed the error starting at 0 on the loop, maybe at expansor use error instead of exit_code.

05:35 am still cant figure out how to sort $'a' or $"a" due me clearing quotes before. The idea i been trying to implement is to filter that type of possibilities at the find_dollar function. where i should not have any issue.
been trying for long time now and cant find a way.
right now the code is working worse than before due not expanding the env correctly (forceing to do it first, but will do all)
starting to not care so much about it since is not that big deal. Problem is, i have no idea if it might be a issue at some point apart than expanding on echo or not.
I feel like  wasted so much time again with this part of the minishell ... it feels impossible and time consuming.
ill keep trying, this seems impotant...
since its 10 good things less, ill retype the best way i had so far.



To keep doing:
SHLVL, EXIT, ECHO (-n -n *etc) , HEREDOCK & (if affects ill try fix the $'a' and $"a")

*ECHO (-n -n, vars containing -n affecting the functionality of it)

Started preparing for leaks. i broke all. if u see this, check if it has 265 ok and 122 ko or might need to pull from before.

Leaks at root from str. readline creates leaks x each command / input it recieves
 10:30 am 26.03.24 
looks more like parser or lexer
rn only leaks from that and still 265 ok.

still need to do readme line 1231, but is stable



with error = 0;
|=========================[ PARSER ]=========================|

    ----------------------[ dollar ]---------------------

  1.   |echo $?|                                        [OK]
  2.   |echo $|                                         [OK]
  3.   |echo hi$|                                       [OK]
  4.   |echo '$ '|                                      [OK]
  5.   |echo $/|                                        [OK]
  6.   |echo "'$'"|                                     [OK]
  7.   |echo $'\n'|                                     [K0]
  8.   |echo $'\r'|                                     [K0]
  9.   |echo $'\t'|                                     [K0]
  10.  |echo $USER|                                     [OK]
  11.  |echo $NONEXIST|                                 [OK]
  12.  |echo $USER$PATH$PWD|                            [OK]
  13.  |echo "$USER$PATH$PWD"|                          [OK]
  14.  |echo '$USER$PATH$PWD'|                          [OK]
  15.  |echo '$USER",$PATH,$PWD'|                       [OK]
  16.  |echo $USER"$PATH"$PWD"USER"$PATH"$PWD"|         [OK]
  17.  |echo $USER'$PATH'$PWD'USER'$PATH'$PWD'|         [OK]
  18.  |$NONEXIST|                                      [K0]
  19.  |$NONEXIST $NONEXIST|                            [K0]
  20.  |VAR: export TMPENVVAR|                          [K0]
  21.  |VAR: export TMPENVVAR=echo|                     [OK]
  22.  |VAR: export TMPENVVAR="  echo"|                 [OK]
  23.  |VAR: export TMPENVVAR="    EcHO   hi"|          [K0]
  24.  |VAR: export TMPENVVAR="-n"|                     [OK]
  25.  |VAR: export TMPENVVAR="-n -n"|                  [K0]
  26.  |echo $A"$B"$C"A"$B"$C"|                         [K0]
  27.  |echo $A'$B'$C'A'$B'$C'|                         [K0]
  28.  |echo $A"$B"$C"A"$B"$C"|                         [K0]
  29.  |echo $A'$B'$C'A'$B'$C'|                         [K0]
  30.  |echo $A|                                        [OK]
  31.  |echo $A$B|                                      [OK]
  32.  |echo $A$B$C|                                    [OK]
  33.  |echo $A$B$C$AA|                                 [OK]

    ----------------------[ quotes ]---------------------

  34.  |echo "~"ups|                                    [OK]
  35.  |echo '~'ups|                                    [OK]
  36.  |echo "'$'"|                                     [OK]
  37.  |echo '"$"'|                                     [OK]
  38.  |echo "|$USER|"|                                 [OK]
  39.  |echo "|$USE|"|                                  [OK]
  40.  |echo "|$USER_|"|                                [OK]
  41.  |echo '|$USER|'|                                 [OK]
  42.  |echo '|$USE|'|                                  [OK]
  43.  |echo '|$USER_|'|                                [OK]
  44.  |'echo' hi|                                      [OK]
  45.  |'''echo' hi|                                    [OK]
  46.  |'echo' 'hi'|                                    [OK]
  47.  |'echo' 'hi'''|                                  [OK]
  48.  |'echo' 'hi' ''|                                 [OK]
  49.  |"echo" hi|                                      [OK]
  50.  |"""echo" hi|                                    [OK]
  51.  |"echo" "hi"|                                    [OK]
  52.  |"echo" "hi"""|                                  [OK]
  53.  |"echo" "hi" ""|                                 [OK]
  54.  |echo '""""""""""""'|                            [OK]
  55.  |'echo' "hi"'' " ' "' "' "" ''''''""|            [OK]
  56.  |echo hi"hi" hi'h"i'|                            [OK]
  57.  |echo "hi" "hi"|                                 [OK]
  58.  |echo "hi"  "hi"|                                [OK]
  59.  |echo "hi"tab"hi"|                               [OK]
  60.  |" echo"|                                        [K0]
  61.  |' echo'|                                        [K0]
  62.  |""echo|                                         [OK]
  63.  |" "echo|                                        [K0]
  64.  |''echo|                                         [OK]
  65.  |' 'echo|                                        [K0]
  66.  |''''''''''echo hi|                              [OK]
  67.  |""""""""""echo hi|                              [OK]
  68.  |"e"'c'h"o" hi|                                  [OK]
  69.  |ec""ho hi|                                      [OK]
  70.  |ec""h''o hi|                                    [OK]
  71.  |EcHo hi|                                        [OK]
  72.  |ECHO hi|                                        [OK]
  73.  |"ECHO" hi|                                      [OK]
  74.  |'ECHO' hi|                                      [OK]
  75.  |echo    t  hi   t|                              [OK]
  76.  |echo "   t  hi   t    "|                        [OK]
  77.  |echo '   t  hi   t    '|                        [OK]
  78.  |echo $"   t  hi   t    "|                       [K0]
  79.  |echo $'   t  hi   t    '|                       [K0]
  80.  |echo $'   r  hi   t    '|                       [K0]
  81.  |echo hi > "fi le"|                              [OK]
  82.  |echo hi > 'fi le'|                              [OK]
  83.  |echo $ANA_VAR with spaces in var value|         [OK]
  84.  |echo "$ANA_VAR" with spaces in var value|       [OK]
  85.  |echo '$ANA_VAR' with spaces in var value|       [OK]

    ----------------------[ spaces ]---------------------

  86.  |""|                                             [K0]
  87.  |" "|                                            [K0]
  88.  |\techo hi|                                      [OK]
  89.  |echo\thi|                                       [OK]
  90.  |\techo\thi|                                     [OK]
  91.  |\techo\thi|                                     [OK]
  92.  |  \techo\thi|                                   [OK]
  93.  |\techo\t   hi|                                  [OK]
  94.  |many tabs|                                      [OK]
  95.  |many spaces|                                    [OK]

    -----------------------[ tilde ]---------------------

  96.  |~|                                              [K0]
  97.  |echo hi~|                                       [OK]
  98.  |echo ~|                                         [K0]
  99.  |echo ~/path|                                    [K0]
  100. |echo ~$USER|                                    [OK]
  101. |echo ~false|                                    [OK]
  102. |echo ~|                                         [K0]
  103. |echo ~$USER/sdfsfsfdsfs|                        [OK]
  104. | echo ~|                                        [K0]

    -------------------[ syntax_error ]------------------

  105. |test|                                           [K0]
  106. ||test|                                          [K0]
  107. || test|                                         [K0]
  108. |< | test|                                       [K0]
  109. |<< | test|                                      [K0]
  110. |> | test|                                       [K0]
  111. |>> | test|                                      [K0]
  112. || < test|                                       [K0]
  113. || << test|                                      [K0]
  114. || > test|                                       [K0]
  115. || >> test|                                      [K0]
  116. || test|                                         [K0]
  117. |test | >|                                       [K0]
  118. |test | >>|                                      [K0]
  119. |test | <|                                       [K0]
  120. |echo hiecho hi|                                 [OK]
  121. |echo hi|echo hi|                                [OK]
  122. |echo hi |echo hi|                               [OK]
  123. |echo hi| echo hi|                               [OK]
  124. |echo hi | | echo hi|                            [K0]
  125. |echo hi ||| echo hi|                            [SF]
  126. |echo >|                                         [K0]
  127. |echo >>|                                        [K0]
  128. |echo <|                                         [K0]
  129. |echo >>>|                                       [K0]
  130. |echo <<<|                                       [K0]
  131. |echo hi >< file|                                [K0]


  It seems that there are some tests that have not passed...
  and your minishell gives segmentation fault at tests:
  [ 125 ]

  To see full failure traces -> traces/parse/*.txt


|============================================================|

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [dollars]                        21     12      0     33
  [quotes]                         45      7      0     52
  [spaces]                          8      2      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                    4     22      1     27

  total                          [0082] [0048] [0001] [0131]


without error = 0;

  |=========================[ PARSER ]=========================|

    ----------------------[ dollar ]---------------------

  1.   |echo $?|                                        [OK]
  2.   |echo $|                                         [OK]
  3.   |echo hi$|                                       [OK]
  4.   |echo '$ '|                                      [OK]
  5.   |echo $/|                                        [OK]
  6.   |echo "'$'"|                                     [OK]
  7.   |echo $'\n'|                                     [K0]
  8.   |echo $'\r'|                                     [K0]
  9.   |echo $'\t'|                                     [K0]
  10.  |echo $USER|                                     [OK]
  11.  |echo $NONEXIST|                                 [OK]
  12.  |echo $USER$PATH$PWD|                            [OK]
  13.  |echo "$USER$PATH$PWD"|                          [OK]
  14.  |echo '$USER$PATH$PWD'|                          [OK]
  15.  |echo '$USER",$PATH,$PWD'|                       [OK]
  16.  |echo $USER"$PATH"$PWD"USER"$PATH"$PWD"|         [OK]
  17.  |echo $USER'$PATH'$PWD'USER'$PATH'$PWD'|         [OK]
  18.  |$NONEXIST|                                      [K0]
  19.  |$NONEXIST $NONEXIST|                            [K0]
  20.  |VAR: export TMPENVVAR|                          [K0]
  21.  |VAR: export TMPENVVAR=echo|                     [K0]
  22.  |VAR: export TMPENVVAR="  echo"|                 [K0]
  23.  |VAR: export TMPENVVAR="    EcHO   hi"|          [K0]
  24.  |VAR: export TMPENVVAR="-n"|                     [OK]
  25.  |VAR: export TMPENVVAR="-n -n"|                  [K0]
  26.  |echo $A"$B"$C"A"$B"$C"|                         [K0]
  27.  |echo $A'$B'$C'A'$B'$C'|                         [K0]
  28.  |echo $A"$B"$C"A"$B"$C"|                         [K0]
  29.  |echo $A'$B'$C'A'$B'$C'|                         [K0]
  30.  |echo $A|                                        [OK]
  31.  |echo $A$B|                                      [OK]
  32.  |echo $A$B$C|                                    [OK]
  33.  |echo $A$B$C$AA|                                 [OK]

    ----------------------[ quotes ]---------------------

  34.  |echo "~"ups|                                    [OK]
  35.  |echo '~'ups|                                    [OK]
  36.  |echo "'$'"|                                     [OK]
  37.  |echo '"$"'|                                     [OK]
  38.  |echo "|$USER|"|                                 [OK]
  39.  |echo "|$USE|"|                                  [OK]
  40.  |echo "|$USER_|"|                                [OK]
  41.  |echo '|$USER|'|                                 [OK]
  42.  |echo '|$USE|'|                                  [OK]
  43.  |echo '|$USER_|'|                                [OK]
  44.  |'echo' hi|                                      [OK]
  45.  |'''echo' hi|                                    [OK]
  46.  |'echo' 'hi'|                                    [OK]
  47.  |'echo' 'hi'''|                                  [OK]
  48.  |'echo' 'hi' ''|                                 [OK]
  49.  |"echo" hi|                                      [OK]
  50.  |"""echo" hi|                                    [OK]
  51.  |"echo" "hi"|                                    [OK]
  52.  |"echo" "hi"""|                                  [OK]
  53.  |"echo" "hi" ""|                                 [OK]
  54.  |echo '""""""""""""'|                            [OK]
  55.  |'echo' "hi"'' " ' "' "' "" ''''''""|            [OK]
  56.  |echo hi"hi" hi'h"i'|                            [OK]
  57.  |echo "hi" "hi"|                                 [OK]
  58.  |echo "hi"  "hi"|                                [OK]
  59.  |echo "hi"tab"hi"|                               [OK]
  60.  |" echo"|                                        [OK]
  61.  |' echo'|                                        [OK]
  62.  |""echo|                                         [K0]
  63.  |" "echo|                                        [OK]
  64.  |''echo|                                         [K0]
  65.  |' 'echo|                                        [OK]
  66.  |''''''''''echo hi|                              [OK]
  67.  |""""""""""echo hi|                              [OK]
  68.  |"e"'c'h"o" hi|                                  [OK]
  69.  |ec""ho hi|                                      [OK]
  70.  |ec""h''o hi|                                    [OK]
  71.  |EcHo hi|                                        [OK]
  72.  |ECHO hi|                                        [OK]
  73.  |"ECHO" hi|                                      [OK]
  74.  |'ECHO' hi|                                      [OK]
  75.  |echo    t  hi   t|                              [OK]
  76.  |echo "   t  hi   t    "|                        [OK]
  77.  |echo '   t  hi   t    '|                        [OK]
  78.  |echo $"   t  hi   t    "|                       [K0]
  79.  |echo $'   t  hi   t    '|                       [K0]
  80.  |echo $'   r  hi   t    '|                       [K0]
  81.  |echo hi > "fi le"|                              [OK]
  82.  |echo hi > 'fi le'|                              [OK]
  83.  |echo $ANA_VAR with spaces in var value|         [OK]
  84.  |echo "$ANA_VAR" with spaces in var value|       [OK]
  85.  |echo '$ANA_VAR' with spaces in var value|       [OK]

    ----------------------[ spaces ]---------------------

  86.  |""|                                             [K0]
  87.  |" "|                                            [OK]
  88.  |\techo hi|                                      [OK]
  89.  |echo\thi|                                       [OK]
  90.  |\techo\thi|                                     [OK]
  91.  |\techo\thi|                                     [OK]
  92.  |  \techo\thi|                                   [OK]
  93.  |\techo\t   hi|                                  [OK]
  94.  |many tabs|                                      [OK]
  95.  |many spaces|                                    [OK]

    -----------------------[ tilde ]---------------------

  96.  |~|                                              [K0]
  97.  |echo hi~|                                       [OK]
  98.  |echo ~|                                         [K0]
  99.  |echo ~/path|                                    [K0]
  100. |echo ~$USER|                                    [OK]
  101. |echo ~false|                                    [OK]
  102. |echo ~|                                         [K0]
  103. |echo ~$USER/sdfsfsfdsfs|                        [OK]
  104. | echo ~|                                        [K0]

    -------------------[ syntax_error ]------------------

  105. |test|                                           [OK]
  106. ||test|                                          [K0]
  107. || test|                                         [K0]
  108. |< | test|                                       [OK]
  109. |<< | test|                                      [OK]
  110. |> | test|                                       [OK]
  111. |>> | test|                                      [OK]
  112. || < test|                                       [K0]
  113. || << test|                                      [K0]
  114. || > test|                                       [K0]
  115. || >> test|                                      [K0]
  116. || test|                                         [K0]
  117. |test | >|                                       [K0]
  118. |test | >>|                                      [K0]
  119. |test | <|                                       [K0]
  120. |echo hiecho hi|                                 [OK]
  121. |echo hi|echo hi|                                [OK]
  122. |echo hi |echo hi|                               [OK]
  123. |echo hi| echo hi|                               [OK]
  124. |echo hi | | echo hi|                            [K0]
  125. |echo hi ||| echo hi|                            [SF]
  126. |echo >|                                         [K0]
  127. |echo >>|                                        [K0]
  128. |echo <|                                         [K0]
  129. |echo >>>|                                       [OK]
  130. |echo <<<|                                       [K0]
  131. |echo hi >< file|                                [OK]


  It seems that there are some tests that have not passed...
  and your minishell gives segmentation fault at tests:
  [ 125 ]

  To see full failure traces -> traces/parse/*.txt


|============================================================|

  SUMARY                         [ OK ] [ KO ] [ SF ] [ TT ]
  [dollars]                        19     14      0     33
  [quotes]                         47      5      0     52
  [spaces]                          9      1      0     10
  [tilde]                           4      5      0      9
  [syntax_error]                   11     15      1     27

  total                          [0090] [0040] [0001] [0131]

11.53 am
  Redo errors for --> !NO error = 0 !
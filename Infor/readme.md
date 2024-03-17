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


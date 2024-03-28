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

Added iteration for exort unset.

need to contemplate ~ so expands to home and only works if alone like ~ or ~///////..//

export wont add "" at start or end!!!
when i added the "" to the print function i failed 2 tests.
so i need to evaluate when i need "" if env has content or not initialized. (check if export something= or something so i add "" or not)
maybe with a flag on the structure??


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

So, need to add the filter for numbers on env only if the first char is number,
$NONEXISTANT wont work if alone or before an existant env.


Expansor, line 80. preparing to filter ? but im missing the env or var where i should pull the info from.

Env_1, preparing to set shell level or increase it if exists. Taking care for a possible situation where is the first var of the env list and also if it wont exist. 

(aparently is kinda hard t obe teh first only so i went fully skiping that fact. might be an issue in the future and we will need to send &env and work with **env  in its function: t_env	*shell_level(t_env *env))


Strarts to be pretty clean. 

Main issues to focus on:

bash-3.2$ echo $USER $?       minishell: echo $USER $?                   
gforns-s 0                    gforns-s 0?       
bash-3.2$ echo $              minishell: echo $             
$                             $
bash-3.2$ echo $k             minishell: echo $k               

bash-3.2$ echo $" t hi t "    minishell: echo $" t hi t "      
 t hi t                       $ t hi t 

  echo $" t hi t " Still an issue;


All test i bee doing where wrongly executed, its worse thatn that socre.


Also, the heck is this issue? @ANNA??
$NONEXIST $NONEXIST
bash: : Permission denied
while actual bash does nothing...


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

  without the trim on the echo. 
  it only fix a dollar so is something with expansor and not echo or anything else


25.03.24 09.05 pm
Take a look at expansor, maybe we can trim " " there instead??
Wont help. I think the issue is with the trim before and after.

26.03.24 01.42 am
broke something with $? (been trying to trim before after and in itself of expansor)

01.49
fixed stupid issue with $?

01.53

Added clear_spaces on utils but not in use.

have not fixed the error starting at 0 on the loop, maybe at expansor use error instead of exit_code.

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

26.03.24 05.08 pm
MISSING:
Check exit for failed cd, 
*ECHO (-n -n, vars containing -n affecting the functionality of it)
HEREDOCK

27.03.24 8.42 pm
Trim EXPANSOR ALL SPACES?
HEREDOCK

https://linuxize.com/post/bash-heredoc/

28.03.24 03.06 pm Exit 1 a 3 should not exit!!
heredock not working properly.
when we try to redir a folder, non existing file or no permissions, the program exit or crash. 

The exit code from child process is not working properly. 
the exit status is wrong, probably because of exit code from child process


minishell: " "
bash: : command not found
minishell: echo $?
0
====================================
minishell: cd test.txt
bash: cd: test.txt: Not a directory
minishell: exit
➜  Minishell git:(guille2) ✗ echo $?
0
=====================================
➜  Minishell git:(guille2) ✗ bash
bash-3.2$ cd test.txt
bash: cd: test.txt: Not a directory
bash-3.2$ exit
exit
➜  Minishell git:(guille2) ✗ echo $?
1
===================================

Leak on lexer
Leak on parser
Leak on clear_quotes

Heredock not working properly.
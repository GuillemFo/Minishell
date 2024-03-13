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
Also	"'$USER'" wont work correctly (missing end)
		"'$USER'$PATH" missing ' after $USER 
		(the env name is correct but its not copying correcly the data)

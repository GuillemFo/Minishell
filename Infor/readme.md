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
-- Expansor {1,} // $var // $((1 + 1)) // Wildcard or Globbing Expansion // $(command) or 'command' 
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
								◦ export with no options
								◦ unset with no options "Delete variables"
								◦ env with no options or arguments
								◦ exit with no options

31/01/24 load env to a list and be able to add remove and modify its contetn


06/02/24 Expansor->
been trying to understand anna's code for 3h now. Been told to focus on my part and then merge the codes.
might need a flag to check if it has a $ so we might need to expand

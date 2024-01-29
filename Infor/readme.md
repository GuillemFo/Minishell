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


								
# Little Tool for changing to existed directory
## Objective
- Practice redirection and shell script

## Description
1. cdex set <existing paths>
	- set path chosen to cdex target
	- flag: -s

2. cdex show
	- show all existed paths (can also work with "-s")

3. cdex
	- cd to chosen path (top path)

4. cdex add <new_path_name> <new_path>

5. cdex del <existing paths>

6. cdex setn <index from 0>
	- set using "n"umber (also can work using "-sn")
	- flag: -sn

7. cdex recover
	- set to previous path

## Problem
- **SLOW** !
- try write .cpp edition, remove some command in shell scripts
	- still slow
- about 0.5s for a command
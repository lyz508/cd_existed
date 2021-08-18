# Little Tool for changing to existed directory
## Objective
- Practice redirection and shell script

## Description
![intro](https://github.com/lyz508/cdex/blob/master/repo/cdex_update_2021_8_18.gif)

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
	- ![scale_intro](https://github.com/lyz508/cdex/blob/master/repo/cdex_intro.gif)
- (2021.8.18) change to WSL 2
	- ![intro](https://github.com/lyz508/cdex/blob/master/repo/cdex_update_2021_8_18.gif)

## Updation
### 2021.8.18
- changed Linux distro & version of WSL to 2
	- have big speedup on **cdex**
- renew on introduction

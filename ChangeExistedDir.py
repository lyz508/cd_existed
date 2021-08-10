import sys

def main(argv):
    source_dir = "/home/yzlin/Shells/cdex"
    error_output = ""
    std_output = ""
    action_output = "None"
    dict_name = f"{source_dir}/path_set.txt"
    action_file = f"{source_dir}/action"
    

    # @ dictionary for path settings
    path_names = []
    paths = []


    # TODO: Reed Settings
    try:
        f = open(f"{dict_name}", "r")
    except FileNotFoundError:
        error_output += f"Cant find {dict_name}\n"
    except:
        error_output += "Some exceptions exist...\n"

    else:
        lines = f.readlines()

        for now_line in lines:
            name, path = [str(val) for val in now_line.split()]
            path_names.append(name)
            paths.append(path)

        f.close()



    # TODO: judge argv for actions
    if len(argv) == 4:
        # ! for add proportion
        if argv[1] == "add":
            new_path_name = argv[2]
            new_path = argv[3]
            path_names.append(new_path_name)
            paths.append(new_path)

            with open(dict_name, "w") as fw:
                for i, names in enumerate(path_names):
                    fw.write(f"{names} {paths[i]}\n")
            std_output += f"Success add {new_path_name}: {new_path}\n"
        else:
            error_output += "WRONGG"
    elif len(argv) == 3:
        # ! for set proportion
        if argv[1] == "set":
            taget_index = -1
            for i, names in enumerate(path_names):
                if names == argv[2]:
                    taget_index = i
                    break
            if taget_index == -1:
                error_output += f"Cant find {argv[2]} in {dict_name}\n"
            else:
                tmp = [path_names[0], paths[0]]
                path_names[0], paths[0] = path_names[taget_index], paths[taget_index]
                path_names[taget_index], paths[taget_index] = tmp[0], tmp[1]
                std_output += f"Complete set on {path_names[0]}: {paths[0]}\n"

            # update dict
            with open(dict_name, "w") as fw:
                for i, names in enumerate(path_names):
                    fw.write(f"{names} {paths[i]}\n")
        # ! set using number
        elif argv[1] == "setn" or argv[1] == "-sn":
            if int(argv[2]) >= len(path_names) or int(argv[2]) < 0:
                std_output = "Index out of range (setn)\n"
            else:
                taget_index = int(argv[2])
                tmp = [path_names[0], paths[0]]
                path_names[0], paths[0] = path_names[taget_index], paths[taget_index]
                path_names[taget_index], paths[taget_index] = tmp[0], tmp[1]
                std_output += f"Complete set on {path_names[0]}: {paths[0]}\n"

            # update dict
            with open(dict_name, "w") as fw:
                for i, names in enumerate(path_names):
                    fw.write(f"{names} {paths[i]}\n")
        # ! for deletion
        elif argv[1] == "del":
            taget_index = -1
            for i, names in enumerate(path_names):
                if names == argv[2]:
                    taget_index = i
                    break
            if taget_index == -1:
                error_output += f"Cant find {argv[2]} in {dict_name}\n"
            else:
                tmp = [path_names[-1], paths[-1]]
                path_names[-1], paths[-1] = path_names[taget_index], paths[taget_index]
                path_names[taget_index], paths[taget_index] = tmp[0], tmp[1]
                
                std_output += f"Success delete {path_names[-1]}: {paths[-1]}\n"
                path_names = path_names[:-1]
                paths = paths[:-1]
                

            # update dict
            with open(dict_name, "w") as fw:
                for i, names in enumerate(path_names):
                    fw.write(f"{names} {paths[i]}\n")
        # ! Wrong proportion
        else:
            error_output += "WRONG on commands...\n"
    # ! for single imput commad
    elif len(argv) == 2:
        # ! Show existed paths
        if argv[1] == "show" or argv[1] == "-s":
            for i, names in enumerate(path_names):
                std_output += f"({i}) {names}: {paths[i]}\n"
        elif argv[1] == "help":
            std_output += "\
                \n1.cdex set <existing paths>\n  set path chosen to cdex target\n\
                \n2.cdex show\n  show all existed paths (can also work with \"-s\")\n\
                \n3.cdex\n  cd to chosen path (top path)\n\
                \n4.cdex add <new_path_name> <new_path>\n\
                \n5.cdex del <existing paths>\n\
                \n6.cdex setn <index from 0>\n set using \"n\"umber (also can work using \"-sn\")\n\
                \n7.cdex recover\n  set to previous path\n"
        else:
            error_output += "WRONG on commands...\n"
    # ! for cdex
    elif len(argv) == 1:
        action_output = "go"
        std_output = f"{paths[0]}"


    # TODO: send stderr and stdout
    sys.stdout.write(std_output)
    sys.stderr.write(error_output)

    # TODO: output action
    with open(action_file, "w") as fw:
        fw.write(action_output)


if __name__ == "__main__":
    main(sys.argv)
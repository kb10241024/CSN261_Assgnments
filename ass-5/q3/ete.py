from ete3 import Tree
x = Tree("((((G:9)E:5)C:7)B:7,(F:6)D:5)A;", format=1)
print(x.get_ascii(show_internal = True))

#!/bin/bash

# Compile and run make re
make re
./ft_container > ft_output.txt

# Compile and run make re NS=std
make re NS=std
./ft_container > std_output.txt

# Check the difference between the two output files
diff ft_output.txt std_output.txt

rm ft_output.txt
rm std_output.txt

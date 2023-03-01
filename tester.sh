g++ -g -std=c++98 -Wall -Werror -Wextra srcs/realtest.cpp -Iincludes/ -DNS=ft -o fttest && ./fttest > ft_resultat 
g++ -g -std=c++98 -Wall -Werror -Wextra srcs/realtest.cpp -Iincludes/ -DNS=std -o stdtest && ./stdtest > std_resultat 
diff ft_resultat std_resultat

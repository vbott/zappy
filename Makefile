all	:
	make -C server_dir
	make -C client_dir
	make -C viewer_dir

clean	:
	make clean -C server_dir
	make clean -C client_dir
	make clean -C viewer_dir

fclean	:
	make fclean -C server_dir
	make fclean -C client_dir
	make fclean -C viewer_dir

re	:
	make re -C server_dir
	make re -C client_dir
	make re -C viewer_dir

Bootstrap: docker
From: ufscar/ubuntu_ompi:latest


%help
Exemplo para o uso do cluster UFSCar.


%files
	/home/user/Area_trab/Aciepe_ICC/* /opt


%post
	echo "COMPILANDO PROGRAMAS ..."
	cd /opt && \
		mpicc -fopenmp projeto_final.c -o projeto_final

%runscript
	/opt/projeto_final


%test
	[ -f /opt/projeto_final ] && echo "Arquivo projeto_final existe" || \
		echo "\aERRO: Arquivo projeto_final NÃO EXISTE ! "

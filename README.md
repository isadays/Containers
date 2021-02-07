# Containers
Projeto Final - Introdução a Computação Científica. Computação de Alto Desempenho ou  High Performance Computing (HPC), na Nuvem. Criação de Container e Job paralelo utilizando OpenMP e MPI. Para isto, utilizou-se um programa escrito em C.


---
# "Projeto Final : Job Paralelo" 

"Este projeto final é requisito da Aciepe Introdução a Computação Científica. O trabalho consistiu na criação de um \"job\" paralelo, jobu600172.sh, a ser executado no cluster da UFSCar. A aplicação alvo, projeto_final.c, escrita em código c, é o produto escalar entre matrizes utilizando MPI, com a divisão das iterações no código utilizando um for paralelo com OpenMP. O serviço remoto utilizado foi o Google Drive, que foi configurado através do comando rclone config, no ambiente ssh do Cluster."

Seja bem vindo! Abaixo se encontra a tabela para identificação dos arquivos anexados à esta pasta.

{
  "data": {
    "h-0": "Arquivo",
    "h-1": "Descrição",
    "0-0": "projeto_final.c",
    "0-1": "Este programa escrito em linguagem c, utiliza MPI e OpenMP, para calcular um produto escalar.",
    "1-0": "jobu600172.sh",
    "1-1": "Job paralelo a ser executado no cluster da Ufscar.",
    "2-0": "Recipe",
    "2-1": "Recipe para a criação do Container .",
    "3-0": "exemplosaida.out",
    "3-1": "Arquivo de saída obtido após submissão do job no Cluster."
  }
# "Tutorial para execução do Job no Cluster"

# "A Criação do Container"

Para a execução de nosso job no Cluster, é essencial que o container já esteja criado, e alocado em uma pasta no ambiente remoto. Além disso, o container deve ser configurado para executar o programa em paralelo. Para criar o container, basta utilizar a "receita" contida na pasta, a qual está nomeada por Singularity. Para isto executa-se o comando no ambiente da máquina local:

      $ sudo singularity build Singularity.simg Singularity",
      
    
Após a criação deste container, Singularity.simg, deve ser feito o seu upload no serviço remoto, em um caminho tal que conste posteriormente em nosso job. Por exemplo, para a execução deste job, utilizou-se o caminho hpc/containers/ .

# "Caminhos"

## "Criação de Pastas no Google Drive ou outro serviço remoto",
  "É importante a criação de caminhos corretos para o Google Drive, isto porque os arquivos de hpc/input devem constar na pasta input e o container deve existir no caminho hpc/containers para que se faça uma cópia do container para execução do job. Ademais, o arquivo de saída é enviado ao caminho hpc/output. Não importa a denominação das pastas, deste que os caminhos no serviço remoto e local estejam corretos no job."


Faz-se necessário para a execução do job que o usuário tenha acesso ao cluster. Isto se dará através *do* comando;

  
       $ ssh u<numeroufscar>@openhpc.ufscar.br
      
  
Agora, com o acesso **permitido** ao Cluster, criaremos um job com extensão .sh , de acordo com o padrão sugerido e também sob vista dos recursos utilizados pelo programa a ser executado, através do comando:

       $ nano job<usuario>.sh
     
  
Uma outra maneira é enviarmos o arquivo do job, em nossa máquina local, para o nosso ambiente ssh,  desta forma, não precisaremos criar um novo arquivo, e sim utilizar este mesmo. Isto é feito através do comando:

      $ scp <arquivo_job> u<nro_ufscar>@openhpc.ufscar.br:~/
     
    
Antes de mais nada, é essencial checar se os caminhos estão corretos e se os arquivos de input estão contidos nos devidos caminhos.

 ## Observação sobre os Caminhos no Job,
  "body": "service=<perfil_remoto>                             # Nome do perfil remoto no rclone\n\nremote_in=<caminho_pasta_servico_remoto_input>                        # Pasta no serviço remoto para input\n\nremote_out=<<caminho_pasta_servico_remoto_output>                      # Pasta no serviço remoto para output\n\nremote_sing=hpc/containers                  # Pasta no serviço remoto para os containers\n\ncontainer_in=/opt/input                     # Pasta no cluster para input\n\ncontainer_out=/opt/output                   # Pasta no cluster para output\n\nlocal_sing=.                                # Pasta local para o container singularity\n\nlocal_job=\"/scratch/job.${SLURM_JOB_ID}\"   # Pasta temporária local\n\nlocal_in=\"${local_job}/input/\"              # Pasta local para arquivos de entrada\n\nlocal_out=\"${local_job}/output/\"            # Pasta local para arquivos de saída"

Por fim, executamos o nosso job através do comando:

      $ sbatch  job600172.sh
     
    
É esperado que após a execução deste comando, apareça a seguinte mensagem na tela:

      Submitted batch job <id_job>
      
# "Por fim..."

Uma vez submetido um job para a fila, podemos verificar o
status deste , através do comando

    $ squeue
      
    
## "Arquivo de Saída"

O arquivo de saída está contido na devida pasta do serviço remoto, tal como mostra a figura

        "https://files.readme.io/e7ffcd3-Captura_de_tela_de_2021-01-20_15-49-01.png",
        "Captura de tela de 2021-01-20 15-49-01.png",
        
